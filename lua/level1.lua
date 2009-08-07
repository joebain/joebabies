

function level1_setup()
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
	
	set_level_size(5)
	set_level_offset(x_l_bound/5,z_l_bound/5)
	set_cage_offset(2,2)
	
	model_level()
	put_cage()
	
	for i,animal in ipairs(animals) do
		animal_send(animal,"n")
	end
	
end

function level1_step(delta)
	animals_update(delta)
end
