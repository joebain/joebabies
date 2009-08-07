function animal_send(animal, direction)
	
	animal.moving = true
	
	if (direction == "n") then
		print("sending it north")
		animal.direction.x = 0
		animal.direction.y = 1
	elseif (direction == "s") then
		animal.direction.x = 0
		animal.direction.y = -1
	elseif (direction == "e") then
		animal.direction.x = 1
		animal.direction.y = 0
	elseif (direction == "w") then
		animal.direction.x = -1
		animal.direction.y = 0
	end
	
	animal.next_square = animal_next_square(animal)
		
end

function animal_next_square(animal)
	
	pos = animal.block:get_pos()
	
	--myx = pos.x - (level.size/2)*animal.direction.x
  --myz = pos.z - (level.size/2)*animal.direction.y
	
	x,y = act_to_grid(pos.x,pos.z)
	
	print("at " .. x .. "," .. y)
	
	x = x + animal.direction.x
	y = y + animal.direction.y
	
	print("going " .. x .. "," .. y)

	return level.map[x][y]
end

function animal_cur_square(animal)
	
	pos = animal.block:get_pos()
	
  --myx = pos.x - (level.size/2)*animal.direction.x
  --myz = pos.z - (level.size/2)*animal.direction.y
	
	x,y = act_to_grid(pos.x,pos.z)
	
	return level.map[x][y]
end

function animals_update(delta)

	for i,animal in ipairs(animals) do
	
		if (animal.moving) then
			--print("there is an animal moving")
		
			cur_square = animal_cur_square(animal)
			next_square = animal_next_square(animal)
			--if the animal is heading for the square it is on (ie it has just got here)
			--print(animal.next_square == nil)
			--print(cur_square == nil)
			if (animal.next_square == cur_square) then
				print("he is fine now")
				--deal with what is coming up
				
				--just carry on
				if (next_square == nil) then
				  animal.next_square = next_square
				elseif (next_square.type == "block") then
				  animal.moving = false
				elseif (next_square.type == "rock") then
				  animal.moving = false
				else
				  animal.next_square = next_square
				end
				
			--if the animal is heading for a different square
			elseif (animal.next_square == next_square) then
				--just update the position
				print("he is moving")
				animal.block:move(Vector3f(animal.direction.x*animal.speed*delta,0,animal.direction.y*animal.speed*delta))
				height = f:get_height(Vector2f(animal.block:get_pos().x,animal.block:get_pos().z))
		    v = Vector3f(animal.block:get_pos().x,height,animal.block:get_pos().z)
		    animal.block:set_pos(v)
			end
		
		end
		
	end

end
