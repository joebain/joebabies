last_time_call_pressed = 0

function animal_send(animal, direction)
	
	animal.moving = true
	
	if (direction == "n") then
		animal.direction.x = 0
		animal.direction.y = 1
		animal.facing = 0
	elseif (direction == "s") then
		animal.direction.x = 0
		animal.direction.y = -1
		animal.facing = 180
	elseif (direction == "e") then
		animal.direction.x = 1
		animal.direction.y = 0
		animal.facing = 270
	elseif (direction == "w") then
		animal.direction.x = -1
		animal.direction.y = 0
		animal.facing = 90
	end
	
end

function send_east()
	try_send('e')
end

function send_west()
	try_send('w')
end

function send_south()
	try_send('s')
end

function send_north()
	try_send('n')
end

function try_send(dir)
	cpos = character.main:get_pos()
	cx,cy = act_to_grid(cpos.x,cpos.z)

    -- This assumes way too much.
    if (not animals[1].moving) then
      animal_send(animals[1],dir)
    end
    --[[
	for i,animal in ipairs(animals) do

        ax,ay = act_to_grid(apos.x,apos.z)
        apos = animal.block:get_pos()
		if (ax == cx) then
			if (ay-1 == cy) or (ay+1 == cy) then
				animal_send(animal,dir)
				break;
			end
		elseif (ay == cy) then
			if (ax-1 == cx) or (ax+1 == cx) then
				animal_send(animal,dir)
				break;
			end
		end
  	
	end
    ]]--
    -- HI
end

function send_animal(animal,x,y)

	x,y = grid_to_act(x,y)
	
	animal.target = {}
	animal.target.x = x
	animal.target.y = y
	
	pos = animal.block:get_pos()
	x,y = act_to_grid(pos.x,pos.z)
	
	level.map[x][y].symbol = '0'
	level.map[x][y].thing = "empty"
	
end

function call_animal()

	cpos = character.main:get_pos()
	cx,cy = act_to_grid(cpos.x,cpos.z)

	for i,animal in ipairs(animals) do
	
		if not animal.moving then
			apos = animal.block:get_pos()
			ax,ay = act_to_grid(apos.x,apos.z)
            time_call_pressed = os.time()
            if (time_call_pressed - last_time_call_pressed > 0) then
		      w.audio.wolfwhistle:play()
              last_time_call_pressed = time_call_pressed
            end
			if (ax == cx) then
				if (ay > cy) then
					animal_send(animal,'s')
				else
					animal_send(animal,'n')
				end
			elseif (ay == cy) then
				if (ax > cx) then
					animal_send(animal,'w')
				else
					animal_send(animal,'e')
				end
			end
		end
	
	end

end


function animal_get_facing(animal)

	rot = animal.block:get_rot()
	
	return rot.y%360
end

function animals_update(delta)

	--~ print("level:")
	--~ for i = 1,#level.map do
		--~ for j = 1,#level.map[i] do
			--~ io.write(level.map[i][j].symbol,",")
		--~ end
		--~ print()
	--~ end

	for i,animal in ipairs(animals) do
	
		if (animal.moving) then
			-------------------
			--update rotation--
			-------------------
			actual_rot = animal_get_facing(animal)
			desire_rot = animal.facing
			--print ("rot " .. actual_rot .. " aim " .. desire_rot)
			diff_rot = (360 + actual_rot - desire_rot)%360
			rot_amount = delta*animal.speed*40
			if (diff_rot > rot_amount*2) then
				if (diff_rot < 180) then
					animal.block:rotate(Vector3f(0,-rot_amount,0))
				else
					animal.block:rotate(Vector3f(0,rot_amount,0))
				end
			elseif (diff_rot ~= 0) then
				animal.block:set_rot(Vector3f(0,desire_rot,0))
			else
				----------------
				--not rotating--
				----------------
	
				animal_pos = animal.block:get_pos()
				--print ("animal at " .. animal_pos.x .. "," .. animal_pos.z)
				--print ("animal traget " .. animal.target.x .. "," .. animal.target.y)
				dir = Vector3f(animal.target.x - animal_pos.x,0,animal.target.y - animal_pos.z)
				diff = dir:magnitude()
				if ( diff > delta*animal.speed) then
					
					--print ("animal at " .. animal_pos.x .. "," .. animal_pos.z)
					--print ("animal traget " .. animal.target.x .. "," .. animal.target.y)
					
					dir:normalise()
					dir.x = dir.x * delta * animal.speed
					dir.y = dir.y * delta * animal.speed
					dir.z = dir.z * delta * animal.speed
					animal.block:move(dir)
				elseif (diff ~= 0) then
					--print ("animal at " .. animal_pos.x .. "," .. animal_pos.z)
					--print ("animal traget " .. animal.target.x .. "," .. animal.target.y)
				
					pos = Vector3f(animal.target.x,0,animal.target.y)
					animal.block:set_pos(pos)
					x,y = act_to_grid(pos.x,pos.z)
					level.map[x][y].symbol = animal.symbol
					level.map[x][y].thing = animal.name
				
				else
					-------------------------------------------
					--reached a square, waiting for direction--
					-------------------------------------------
					a_gridx,a_gridy = act_to_grid(animal_pos.x,animal_pos.z)
					
					a_gridx = a_gridx + animal.direction.x
					a_gridy = a_gridy + animal.direction.y
					--print ("done at " .. a_gridx .. "," .. a_gridy)
					--check next square--
					if in_cage(a_gridx,a_gridy) then
						thing = level.map[a_gridx][a_gridy].thing
						--nothing, carry on
						if (thing == "empty") then
							send_animal(animal,a_gridx,a_gridy)
						elseif (thing == "box") then
							if (animal.name == "gorilla") then
                                t = math.random(1,2)
                                if (t == 1) then
                                  w.audio.boxsmash1:play()
                                else
                                  w.audio.boxsmash2:play() 
                                end
								level.map[a_gridx][a_gridy].block:move(Vector3f(0,-5,0))
								coords = level.map[a_gridx][a_gridy].block:get_pos()
								rot = level.map[a_gridx][a_gridy].block:get_dir()
								
								
								b = bf:new_block3d("broken_box.obj","broken_box.bmp")
								v = Vector3f(coords.x,0,coords.z)
								v.y = f:get_height(Vector2f(v.x,v.z))
								b:move(v)
								b:change_dir(rot)

								level.map[a_gridx][a_gridy].symbol = '0'
								level.map[a_gridx][a_gridy].thing = 'empty'
								rx,ry = grid_to_act(a_gridx,a_gridy)
								new_smoke(Vector3f(rx-level.size/1.5,1,ry+level.size/3))
								new_smoke(Vector3f(rx-level.size/3,1,ry+level.size/1.5))
							else
								animal.moving = false
							end
						elseif (thing == "rock") then
							animal.moving = false
						elseif (thing == "internet") then
                            w.audio.puzzleget:play()
							animal.block:add_child(level.map[a_gridx][a_gridy].block)
							level.map[a_gridx][a_gridy].block:nudge(Vector3f(0,4,0))
							level.map[a_gridx][a_gridy].thing = "empty"
							level.map[a_gridx][a_gridy].symbol = "0"
							animal.has_internet = true
						end
					else
					animal.moving = false
					end
				end
				
			end
		else
			if (animal.has_internet) then
					cpos = character.main:get_pos()
					cx,cy = act_to_grid(cpos.x,cpos.z)
					ax,ay = act_to_grid(animal_pos.x,animal_pos.z)
					
					if (cx == ax or cx == ax +1 or cx == ax -1) then
						if (cy == ay or cy == ay +1 or cy == ay -1) then
						w.audio.puzzleget:play()
						animal.has_internet = false
						
						--need to remove old internet
						
						--create new internet
						internet = bf:new_block3d("internet.obj","internet.bmp")
						--internet:move(Vector3f(cpos.x, cpos.y + 5, cpos.z))
						
						character.main:add_child(internet) --give internet to techie
						internet:nudge(Vector3f(0,6,0))
						
						--put_dialogue(#w.facts

						end
					end
					
				
			end
		end
	end

end