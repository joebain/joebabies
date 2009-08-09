
ts = {}
block = nil
scale = 100

turtle_stack = 0
turtle_ring = {}
turtle_ring_counter = 0
turtle_ring_radius = 4

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
	
	--~ wall = bf:new_block3d("wall.obj","wall.bmp")
	--~ wall:move(Vector3f(x_l_bound+50,0,z_l_bound+60))
	--~ wall:set_dir(Vector3f(0,90,0))
	--~ table.insert(scenery,wall)
	
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
		b2 = bf:new_character("turtle.obj","turtle.bmp")
		v = Vector3f(math.random(x_l_bound,x_u_bound),0,math.random(z_l_bound,z_u_bound))
		v.y = f:get_height(Vector2f(v.x,v.z))
		b2:move(v)
		v = Vector3f(0,math.random(0,360),0)
		b2:change_dir(v)
		table.insert(ts,b2)
	end
	
	block = bf:new_block3d("box.obj","box.bmp")
	v = Vector3f(x_l_bound+40,0,z_l_bound+40)
	v.y = f:get_height(Vector2f(v.x,v.z))
	block:move(v)
	
	block2 = bf:new_block3d("box.obj","box.bmp")
	v = Vector3f(x_l_bound+80,0,z_l_bound+40)
	v.y = f:get_height(Vector2f(v.x,v.z))
	block2:move(v)

	
	c:follow(character.main)
	
	music = w:new_audio_file("music", true);
	sound = w:new_audio_file("hello", false);
	music:play();
	--sound:play();
	
	water = bf:new_flat_block("water.bmp",Vector2f(200,200), true)
	water:move(Vector3f(0,-0.3,0))
	water:rotate(Vector3f(90,0,0))
	water:set_transparency(0.9)
	water:set_tex_size(Vector2f(100,100))
	
	
end

function eat_pie()
print("eat a pie")
end

function eat_sausage()
print("eat a sausage")
end

function go_town()
print("go to town")
end

function rape_kid()
print("rape it like a polaroid picture")
end 

function intro_step(delta)

	turtle_ring_counter = turtle_ring_counter + delta
	for i,turtle in ipairs(turtle_ring) do
	
		--turtle:rotate(Vector3f(0,delta*10,0))
		pos = (i/#turtle_ring)*math.pi*2 + turtle_ring_counter
		turtle:set_offset(Vector3f((math.cos(pos))*turtle_ring_radius,2,((math.sin(pos)))*turtle_ring_radius))
	
	end

	for i,turtle in ipairs(ts) do
		if character.main:collide(turtle) then
		
			turtle:set_pos(Vector3f(0,0,0))
			character.main:add_child(turtle)
			table.remove(ts,i)
			table.insert(turtle_ring,turtle)
			
		
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
	
	update_dialogue(delta)
	
	if character.main:collide(block) then
		put_dialogue("Hello, my name is Hedgey the Hedgehog. I like cheese and fast cars. Do you have a cracker for me? One thing I really love is crackers. Did you know that one hedgehog like me can get through about 14 crackers in 30 minutes. It's pure madness.","hedgehog")
		--put_dialogue("12345678","hedgehog")
	else
		dialogue.big_trigger = false
	end
	
	if character.main:collide(block2) then
		if block2_collide == false then
			choices = {}
			choices[1] = {}
			choices[1].text = "Eat a pie"
			choices[1].cb_func = eat_pie
			choices[2] = {}
			choices[2].text = "Eat a sausage"
			choices[2].cb_func = eat_sausage
			
			choices[3] = {}
			choices[3].text = "Go to town"
			choices[3].cb_func = go_town
			choices[4] = {}
			choices[4].text = "Rape a child"
			choices[4].cb_func = rape_kid
			
			put_menu("What would you like to do?",choices,"hedgehog")
			block2_collide = true
		end
	else
		block2_collide = false
	end

end


