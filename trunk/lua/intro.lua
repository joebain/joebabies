
ts = {}
block = nil
scale = 100


x_l_bound = 50
z_l_bound = 50
x_u_bound = 150
z_u_bound = 150


function intro_setup()

	v = Vector2f(300,300)
	hud = bf:new_blockHUD(v,"hedgehog_hud.bmp")
	
	character.main = bf:new_character("hedgehog.obj","hedgehog.bmp")
	v = Vector3f(x_l_bound+2,0,z_l_bound+2)
	v.y = f:get_height(Vector2f(v.x,v.z))
	character.main:set_pos(v)
	whisker_size = 0.5
	character.whisker_r = bf:new_imaginary_block(Vector3f(whisker_size,whisker_size,whisker_size))
	character.whisker_r:nudge(Vector3f(0.2,1,0.5))
	character.main:add_child(character.whisker_r)
	character.whisker_l = bf:new_imaginary_block(Vector3f(whisker_size,whisker_size,whisker_size))
	character.whisker_l:nudge(Vector3f(0.2,1,-0.5))
	character.main:add_child(character.whisker_l)
	
	v = Vector3f(0,45,0)
	character.main:set_dir(v)
	
	for i=1,40 do
		b2 = bf:new_block3d("tree.obj","tree.bmp")
		v = Vector3f(math.random(x_l_bound,x_u_bound),0,math.random(z_l_bound,z_u_bound))
		v.y = f:get_height(Vector2f(v.x,v.z))
		b2:move(v)
		table.insert(scenery,b2)
	end
	
	--~ wall = bf:new_block3d("wall.obj","wall.bmp")
	--~ wall:move(Vector3f(x_l_bound+50,0,z_l_bound+60))
	--~ wall:set_dir(Vector3f(0,90,0))
	--~ table.insert(scenery,wall)
	
	level.width = x_u_bound - x_l_bound
	level.height = z_u_bound - z_l_bound
	level.off_x = x_l_bound
	level.off_y = z_l_bound
	
	do_border_fences()
	do_mountains()
	
	for i = 1,30 do
		cloud = bf:new_distance_block("cloud.bmp",Vector2f(20,15))
		cloud:move(Vector3f(math.random(-100,300),10,math.random(-100,300)))
		cloud:rotate(Vector3f(0,math.random(0,360),0))
	end
	
		
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

	
	c:follow(character.main)
	
	music = w:new_audio_file("main", true);
	sound = w:new_audio_file("hello", false);
	--music:play();
	--sound:play();
	
	water = bf:new_flat_block("water.bmp",Vector2f(200,200), true)
	water:move(Vector3f(0,-0.3,0))
	water:rotate(Vector3f(90,0,0))
	water:set_transparency(0.9)
	water:set_tex_size(Vector2f(100,100))
end


function intro_step(delta)

	for i = 1,#ts do
		m = Vector3f(0,0,3.0*delta)
		ts[i]:move(m)
		if (ts[i]:get_pos().x < x_l_bound or ts[i]:get_pos().z < z_l_bound or
		    ts[i]:get_pos().x > x_u_bound or ts[i]:get_pos().z > z_u_bound) then
			m = Vector3f(0,0,-6.0*delta)
			ts[i]:move(m)
			r = Vector3f(0,45.0,0)
			ts[i]:change_dir(r)
		end
		height = f:get_height(Vector2f(ts[i]:get_pos().x,ts[i]:get_pos().z))
		v = Vector3f(ts[i]:get_pos().x,height,ts[i]:get_pos().z)
		ts[i]:set_pos(v)
		rand = math.random(0,200)
		if (rand == 1) then
			r = Vector3f(0,45.0,0)
			ts[i]:change_dir(r)
		elseif (rand == 2) then
			r = Vector3f(0,-45.0,0)
			ts[i]:change_dir(r)
		end
	end
	
	
	
	if character.main:collide(block) then
	--bf:clear_all()
		if not dialogue.text_up then
			put_dialogue("Hello, my name is Hedgey the Hedgehog. I like cheese and fast cars. Do you have a cracker for me?","hedgehog")
		end
	end

end
