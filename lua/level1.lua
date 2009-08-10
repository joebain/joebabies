
function level1_setup(d)


	
	difficulty = d

	make_character()
	
	v = Vector3f(0,45,0)
	--character.main:set_dir(v)
	
	c:follow(character.main)
	
	--~ for i=1,50 do
		--~ b2 = bf:new_character("gorilla.obj","gorilla.bmp")
		--~ v = Vector3f(math.random(x_l_bound,x_u_bound),0,math.random(z_l_bound,z_u_bound))
		--~ v.y = f:get_height(Vector2f(v.x,v.z))
		--~ b2:move(v)
		--~ v = Vector3f(0,math.random(0,360),0)
		--~ b2:change_dir(v)
		--~ table.insert(ts,b2)
	--~ end
	
	--add parrot
	big_parrot.block = bf:new_character("parrot.obj","parrot.bmp")
	big_parrot.block:set_scale(25)
	v = Vector3f(x_u_bound - 2,0,z_u_bound - 2 )
	v.y = f:get_height(Vector2f(v.x,v.z))
	big_parrot.block:move(v)
		
	--load_level("misc/level1.csv")
    level.map = nil
    ts = 0
    td = 0
    if (difficulty == 1) then
      ts = 6
      td = 3
    elseif (difficulty == 2) then
      ts = 8
      td = 5
    else 
      ts = 10
      td = 7
    end
    while (level.map == nil) do
      level.map = world_gen(ts,ts,td)
    end
    level.cage = {}
    level.cage.width = ts
    level.cage.height = ts
    io.write("==========\n")
    io.write("Final Map:\n")
    io.write("==========\n")
    for i=1,level.cage.width do
      for j=1,level.cage.height do
        io.write(level.map[i][j].symbol, " ")
      end
      io.write("\n")
    end
	
	set_level_size(5)
	set_level_offset(x_l_bound/level.size,z_l_bound/level.size)
	set_cage_offset(2,2)
	level.width = (x_u_bound - x_l_bound) / level.size
	level.height = (z_u_bound - z_l_bound) / level.size
	level.off_x = x_l_bound/level.size
	level.off_y = z_l_bound/level.size
	
	model_level()
	put_cage()
	
	do_border_fences()
	do_mountains()
	
	high_cam_obj = bf:new_imaginary_block(Vector3f(1,1,1))
	high_cam_obj:move(Vector3f(level.size*(level.cage.width/2 + level.off_x + level.cage.x),
								40,
								level.size*(level.off_y + level.cage.y + 1.5)))
	high_cam_obj:set_dir(Vector3f(40,0,0))
	
	--new_smoke(Vector3f(level.size*(level.off_x + 2),1,level.size*(level.off_y + 2)))
	
end

function parrot_ask_lvl1 ()
	put_dialogue("Sure, where'dya wanna go?", "parrot", lvl1parrotchoice)
end

function lvl1parrotchoice ()
	choices = {}
	
	choices[1] = {}
	choices[1].text = "Actually, tell me something..."
	choices[1].cb_func = a_parrot_fact
	choices[2] = {}
	choices[2].text = "Any more gorillas to help?"
	choices[2].cb_func = fly_level1
	choices[3] = {}
	choices[3].text = "I'm going on break"
	choices[3].cb_func = quit_game
	
	put_menu("U",choices,"parrot")
end

function quit_game()
	w:quit()
	
end

function a_parrot_fact()

	put_dialogue(w.parrot_facts[math.random(1,#w.parrot_facts)], "parrot", lvl1parrotchoice)
end

function level1_step(delta)
	animals_update(delta)
	
	--update_dialogue(delta)
	
		
	if (character.main:collide(big_parrot.block)) then
		if big_parrot.collide == false then
			big_parrot.collide = true
			put_dialogue("Hey man, can I hitch a lift?", "person", parrot_ask_lvl1)
		end
	else
	
		big_parrot.collide = false
		
	end

	
	for i,thing in ipairs(internets) do
		thing.block:rotate(Vector3f(0,delta*50,0))
	end
	
	for i,thing in ipairs(camera_triggers) do
		step_trigger(thing,delta)
	end
	
	for i,thing in ipairs(particles) do
		particle_step(i,thing,delta)
	end
end
