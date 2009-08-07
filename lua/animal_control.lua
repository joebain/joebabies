
function animal_send(animal, direction)
	
	animal.moving = true
	
	if (direction == "n") then
		animal.direction.x = 0
		animal.direction.y = -1
		animal.facing = 180
	elseif (direction == "s") then
		animal.direction.x = 0
		animal.direction.y = 1
		animal.facing = 0
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

	for i,animal in ipairs(animals) do
		apos = animal.block:get_pos()
		ax,ay = act_to_grid(apos.x,apos.z)
	
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
		apos = animal.block:get_pos()
		ax,ay = act_to_grid(apos.x,apos.z)
	
		if (ax == cx) then
			if (ay > cy) then
				animal_send(animal,'n')
			else
				animal_send(animal,'s')
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


function animal_get_facing(animal)

	rot = animal.block:get_rot()
	
	return rot.y%360
end
--[[
function animal_next_square(animal)
	
	pos = animal.block:get_pos()
	
	pos.x = pos.x - (level.size/2)*animal.direction.x
	pos.z = pos.z - (level.size/2)*animal.direction.y
	
	x,y = act_to_grid(pos.x,pos.z)
	
	print("at " .. x .. "," .. y)
	
	x = x + animal.direction.x
	y = y + animal.direction.y
	
	print("going " .. x .. "," .. y)
	
	--~ if x > level.cage.width or x < 0 or y > level.cage.height or y < 0 then
		--~ return nil
	--~ end

	return level.map[x][y]
end

function animal_cur_square(animal)
	
	pos = animal.block:get_pos()
	
	pos.x = pos.x - (level.size/2)*animal.direction.x
	pos.z = pos.z - (level.size/2)*animal.direction.y
	
	x,y = act_to_grid(pos.x,pos.z)
	
	--~ if x > level.cage.width or x < 0 or y > level.cage.height or y < 0 then
		--~ return nil
	--~ end
	
	level.map[x][y].type = animal.name
	level.map[x][y].symbol = animal.symbol
	
	return level.map[x][y]
end

function animal_prev_square(animal)
	
	pos = animal.block:get_pos()
	
	pos.x = pos.x - (level.size/2)*animal.direction.x
	pos.z = pos.z - (level.size/2)*animal.direction.y

	x,y = act_to_grid(pos.x,pos.z)

	x = x - animal.direction.x
	y = y - animal.direction.y
	
	
	--~ if x > level.cage.width or x < 0 or y > level.cage.height or y < 0 then
		--~ return nil
	--~ end
	
	return level.map[x][y]
end
--]]
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
			diff_rot = math.abs(actual_rot - desire_rot)%360
			rot_amount = delta*animal.speed*20
			if (diff_rot > rot_amount*2) then
				if (diff_rot < 180 or diff_rot > -180) then
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
							--what?
						elseif (thing == "rock") then
							--can't go
						end
					end
				end
				
			end
		end
	end

end
