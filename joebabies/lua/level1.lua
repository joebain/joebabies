
function level1_setup(d)

	difficulty = d

	-- Load and model the level --
	------------------------------
	load_level("misc/level1.csv")
	--load_random_level()
	
	set_level_size(5)
	set_level_offset(x_l_bound/level.size,z_l_bound/level.size)
	set_cage_offset(2,2)
	level.width = (x_u_bound - x_l_bound) / level.size
	level.height = (z_u_bound - z_l_bound) / level.size
	level.off_x = x_l_bound/level.size
	level.off_y = z_l_bound/level.size
	
	model_level()
	put_cage()

	-- Make the characters --
	-------------------------
	--main man
	character = new_character("techie")
	v = Vector3f(x_l_bound+2,0,z_l_bound+2)
	v.y = f:get_height(Vector2f(v.x,v.z))
	character.main:set_pos(v)
	c:follow(character.main)
	
	--add co-star (hedgehog)
	costar = new_character("hedgehog")
	cox,coy = grid_to_act(level.cage.width,0)
	costar.main:move(Vector3f(cox,0,coy))
	
	--add parrot
	big_parrot.block = bf:new_character("parrot.obj","parrot.bmp")
	big_parrot.block:set_scale(25)
	v = Vector3f(x_u_bound - 2,0,z_u_bound - 2 )
	v.y = f:get_height(Vector2f(v.x,v.z))
	big_parrot.block:move(v)
	
	
	
	do_border_fences()
	do_mountains()
	
	high_cam_obj = bf:new_imaginary_block(Vector3f(1,1,1))
	high_cam_obj:move(Vector3f(level.size*(level.cage.width/2 + level.off_x + level.cage.x),
								45,
								level.size*(level.off_y + level.cage.y + 2.3)))
	high_cam_obj:set_dir(Vector3f(60,0,0))
	
	if (first_level1) then
		new_dialogue().put("Hey welcome to what happens when you put an infinite number of monkeys in a room with an infinite amount of rocks and boxes. Not quite Shakespeare, eh? Use the W A S D keys to move the gorilla and guide him to that piece of the internet. Get him to bring it back to you and go talk to the parrot in the corner if you're bored.","hedgehog",nil)
		first_level1 = false
	end
	
end

function parrot_ask_lvl1 ()
	new_dialogue().put("Sure, where'dya wanna go?", "parrot", lvl1parrotchoice)
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
	choices[3].text = "Let's head back"
	choices[3].cb_func = gotointro
	choices[4] = {}
	choices[4].text = "I'm going on break"
	choices[4].cb_func = quit_game
	
	new_menu().put("Lets fly...",choices,"parrot")
end

function quit_game()
	w:quit()
	
end

function a_parrot_fact()

	new_dialogue().put(w.parrot_facts[math.random(1,#w.parrot_facts)], "parrot", lvl1parrotchoice)
end

function level1_step(delta)
	animals_update(delta)
	
	if (character.main:collide(big_parrot.block)) then
		if big_parrot.collide == false and bs.space then
			big_parrot.collide = true
			new_dialogue().put("Hey man, can I hitch a lift?", "person", parrot_ask_lvl1)
		end
	else
		big_parrot.collide = false
	end

	--rotate the internets
	for i,thing in ipairs(internets) do
		thing.block:rotate(Vector3f(0,delta*50,0))
	end
	
	--fade out lit squares
	step_lights(delta)
	
	--step all the particles
	for i,thing in ipairs(particles) do
		particle_step(i,thing,delta)
	end
	
	--adjust the camera if the character is in or out of the triggers
	if (character.in_cam_triggers) then
		c:follow(high_cam_obj)
		if (#display_list == 0) then
			functions.up = cage_move_up
			functions.down = cage_move_down
			functions.right = cage_move_right
			functions.left = cage_move_left
		end
	else
		c:follow(character.main)
		if (#display_list == 0) then
			functions.up = move_up
			functions.down = move_down
			functions.right = move_right
			functions.left = move_left
		end
	end
end

function move_up(delta)
	character.move_up (delta)
end

function move_down(delta)
	character.move_down (delta)
end

function move_right(delta)
	character.move_right (delta)
end

function move_left(delta)
	character.move_left (delta)
end

function cage_move_up(delta)
	character.move_north(delta)
end

function cage_move_down(delta)
	character.move_south(delta)
end

function cage_move_left(delta)
	costar.move_west(delta)
end

function cage_move_right(delta)
	costar.move_east(delta)
end
