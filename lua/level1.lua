
function level1_setup()

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
	
		
	load_level("misc/level1.csv")
    level.map = world_gen(12,12,10)
    level.cage = {}
    level.cage.width = 12
    level.cage.height = 12
    io.write("\n\nFinal Map:\n")
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

function level1_step(delta)
	animals_update(delta)
	
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
