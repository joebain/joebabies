
ts = {}
block = nil
scale = 100

turtle_stack = 0
turtle_ring = {}
turtle_ring_counter = 0
turtle_ring_radius = 4
turtle_challenge = false
turlte_challenge_start = 0
turtle_challenge_count = 0

big_tortoise = {}
big_tortoise.collide = false
big_gorilla = {}
big_parrot = {}
big_parrot.collide = false

x_l_bound = 50
z_l_bound = 50
x_u_bound = 150
z_u_bound = 150

block2_collide = false


function intro_setup()
	
	make_character()
	
	v = Vector3f(0,45,0)
	character.main:set_dir(v)
	
	for i=1,40 do
		b2 = bf:new_block3d("tree.obj","tree.bmp")
		
		repeat
			v = Vector3f(math.random(x_l_bound,x_u_bound),0,math.random(z_l_bound,z_u_bound))
			v.y = f:get_height(Vector2f(v.x,v.z))
		until v.y >= 0
		
		b2:move(v)
		
		bounder = bf:new_imaginary_block(Vector3f(2,8,2))
		bounder:nudge(Vector3f(-1,0,-1))
		--bounder:toggle_debug()
		b2:add_child(bounder)
		
		table.insert(scenery,bounder)
	end
	
	----------------
	---big things---
	----------------
	
	big_tortoise.block = bf:new_character("tortoise.obj","tortoise.bmp")
	big_tortoise.block:set_scale(5)
	v = Vector3f(math.random(x_l_bound,x_u_bound),0,math.random(z_l_bound,z_u_bound))
	v.y = f:get_height(Vector2f(v.x,v.z))
	big_tortoise.block:move(v)
	
	--add parrot
	big_parrot.block = bf:new_character("parrot.obj","parrot.bmp")
	big_parrot.block:set_scale(25)
	v = Vector3f(math.random(x_l_bound,x_u_bound),0,math.random(z_l_bound,z_u_bound))
	v.y = f:get_height(Vector2f(v.x,v.z))
	big_parrot.block:move(v)
	
	
	level.size = 5
	
	level.width = (x_u_bound - x_l_bound)/5
	level.height = (z_u_bound - z_l_bound)/5
	level.off_x = x_l_bound/5
	level.off_y = z_l_bound/5
	
	do_border_fences()
	do_mountains()
	
	--[[
	for i = 1,30 do
		cloud = bf:new_distance_block("cloud.bmp",Vector2f(20,15))
		cloud:move(Vector3f(math.random(-100,300),10,math.random(-100,300)))
		cloud:rotate(Vector3f(0,math.random(0,360),0))
	end
	--]]
	
		
	for i=1,50 do
		b2 = bf:new_character("tortoise.obj","tortoise.bmp")
		v = Vector3f(math.random(x_l_bound,x_u_bound),0,math.random(z_l_bound,z_u_bound))
		v.y = f:get_height(Vector2f(v.x,v.z))
		b2:move(v)
		v = Vector3f(0,math.random(0,360),0)
		b2:change_dir(v)
		table.insert(ts,b2)
	end
	

	
	c:follow(character.main)
	
	sound = w:new_audio_file("hello", false);
	
	water = bf:new_flat_block("water.bmp",Vector2f(200,200), true)
	water:move(Vector3f(0,-0.3,0))
	water:rotate(Vector3f(90,0,0))
	water:set_transparency(0.9)
	water:set_tex_size(Vector2f(100,100))
	
	if (first_intro == true) then
		new_dialogue().put("Hi how's it going? So I hear you got a job fixing IT for these dumb animals. (Press space to read more.) They're so stupid, most of 'em couldn't even write their own names if you asked 'em. Not that you should, they just go on and on and .. well you get the picture. Full of useless facts they are. So I hope you enjoy it here, I certainly don't.","hedgehog",nil)
		first_intro = false
	end
	
end

function start_tortoise_challenge()

	turtle_challenge = true
	turtle_challenge_start = os.time()

end

function refuse_tortoise_challenge()

	new_dialogue().put("Fine, be like that!","tortoise",nil)

end

function tortoise_challenge_ask ()
	choices = {}
	choices[1] = {}
	choices[1].text = "OK"
	choices[1].cb_func = start_tortoise_challenge
	choices[2] = {}
	choices[2].text = "No way"
	choices[2].cb_func = refuse_tortoise_challenge
	
	new_menu().put("Um...",choices,"person")
	block2_collide = true
end

function parrot_ask ()
	choices = {}
	choices[1] = {}
	choices[1].text = "OK"
	choices[1].cb_func = fly_level1
	choices[2] = {}
	choices[2].text = "Later, man"
	choices[2].cb_func = nil
	
	new_menu().put("Um...",choices,"person")
end

function fly_level1 ()
	--put_dialogue("Here y'are", "parrot", actual_flight)
	--return_control()
	gotolevel1()
end



function intro_step(delta)

	turtle_ring_counter = turtle_ring_counter + delta
	for i,turtle in ipairs(turtle_ring) do
	
		--turtle:rotate(Vector3f(0,delta*10,0))
		pos = (i/#turtle_ring)*math.pi*2 + turtle_ring_counter
		turtle:set_offset(Vector3f((math.cos(pos))*turtle_ring_radius,4,((math.sin(pos)))*turtle_ring_radius))
	
	end
	
	if (character.main:collide(big_parrot.block)) then
		if big_parrot.collide == false and bs.space then
			big_parrot.collide = true
			new_dialogue().put("Fly you off to the gorilla cage? Hear his internet's down...", "parrot", parrot_ask)
		end
	else
	
		big_parrot.collide = false
		
	end
	
	if (character.main:collide(big_tortoise.block)) then
		if bs.space then
			if (turtle_challenge == true) then
				if big_tortoise.collide == false then
					new_dialogue().put("Hey what a good job, you collected " .. #turtle_ring .. " of those little guys in only " .. (os.time()-turtle_challenge_start) .. " seconds. Well done indeed! P.s. Did you know ..... " .. w.tortoise_facts[math.random(1,#w.tortoise_facts)],"tortoise",nil)
				end
				
			
			else
			
				if big_tortoise.collide == false then
					new_dialogue().put("Hello, I am Mortimer the big tortoise. All my friends make fun of me because I am so big, but it's not my fault. You see my mother always wanted a big tortoise for a son so she fed me 36 bowls of porridge every day. Tortoises really like lettuce, that's what I fancy. Actually, could I ask you a favour? Could you gather up as many of the small tortoises as you can and bring them to me? I think that's a fair challenge.","tortoise",tortoise_challenge_ask)
				end
			end
			big_tortoise.collide = true
		end
	else
		dialogue.big_trigger = false
		big_tortoise.collide = false
		---big turtle---
		m = Vector3f(0,0,3.0*delta)
		big_tortoise.block:move(m)
		if (big_tortoise.block:get_pos().x < x_l_bound or big_tortoise.block:get_pos().z < z_l_bound or
			big_tortoise.block:get_pos().x > x_u_bound or big_tortoise.block:get_pos().z > z_u_bound) then
			m = Vector3f(0,0,-6.0*delta)
			big_tortoise.block:move(m)
			r = Vector3f(0,45.0,0)
			big_tortoise.block:change_dir(r)
		end
		height = f:get_height(Vector2f(big_tortoise.block:get_pos().x,big_tortoise.block:get_pos().z))
		v = Vector3f(big_tortoise.block:get_pos().x,height,big_tortoise.block:get_pos().z)
		big_tortoise.block:set_pos(v)
		rand = math.random(0,200)
		if (rand == 1) then
			r = Vector3f(0,45.0,0)
			big_tortoise.block:change_dir(r)
		elseif (rand == 2) then
			r = Vector3f(0,-45.0,0)
			big_tortoise.block:change_dir(r)
		end
		-------------
	end
	
	
	for i,turtle in ipairs(ts) do
		if character.main:collide(turtle) and turtle_challenge == true then
		
			turtle:set_pos(Vector3f(0,0,0))
			character.main:add_child(turtle)
			table.remove(ts,i)
			table.insert(turtle_ring,turtle)
            w.audio.turtleget:play()
			
		
		else
	
			m = Vector3f(0,0,3.0*delta)
			turtle:move(m)
			if (turtle:get_pos().x < x_l_bound or turtle:get_pos().z < z_l_bound or
				turtle:get_pos().x > x_u_bound or turtle:get_pos().z > z_u_bound) then
				m = Vector3f(0,0,-6.0*delta)
				turtle:move(m)
				r = Vector3f(0,45.0,0)
				turtle:change_dir(r)
                
			end
			height = f:get_height(Vector2f(turtle:get_pos().x,turtle:get_pos().z))
			v = Vector3f(turtle:get_pos().x,height,turtle:get_pos().z)
			turtle:set_pos(v)
			rand = math.random(0,200)
			if (rand == 1) then
				r = Vector3f(0,45.0,0)
				turtle:change_dir(r)
			elseif (rand == 2) then
				r = Vector3f(0,-45.0,0)
				turtle:change_dir(r)
			end
		
		end
	end
	
end


