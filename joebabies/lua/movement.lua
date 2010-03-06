
player_turn_speed = 100.0
player_travel_speed = 10.0
player_wobble_factor = 0.05
player_bounce_factor = 5.0

function new_character(name)

	local character = {}

	character.main = bf:new_character(name .. ".obj",name .. ".bmp")
	
	whisker_size = 0.5
	character.whisker_r = bf:new_imaginary_block(Vector3f(whisker_size/4,whisker_size,whisker_size))
	character.whisker_r:nudge(Vector3f(-0.5,1,0))
	--character.whisker_r:toggle_debug()
	character.main:add_child(character.whisker_r)
	character.whisker_l = bf:new_imaginary_block(Vector3f(whisker_size/4,whisker_size,whisker_size))
	character.whisker_l:nudge(Vector3f(0.5,1,0))
	--character.whisker_l:toggle_debug()
	character.main:add_child(character.whisker_l)

	character.in_cam_triggers = false
	character.wobble_counter = 0.0

	character.position = function (delta)
		
		for i,thing in ipairs(scenery) do
			l_collide = character.whisker_l:collide(thing)
			r_collide = character.whisker_r:collide(thing)
			m_collide = character.main:collide(thing)
			
			if (character.in_cam_triggers) then
				if l_collide and r_collide then
					v = Vector3f(0,0,-delta*player_travel_speed*1.1)
					character.main:move(v)
					--print("both")
					break
				elseif l_collide then
					v = Vector3f(math.abs(delta)*(-player_travel_speed)*1.1,0,0)
					character.main:move(v)
					--print("left")
					break
				elseif r_collide then
					v = Vector3f(math.abs(delta)*(player_travel_speed)*1.1,0,0)
					character.main:move(v)
					--print("right")
					break
				end
			else
				if l_collide and r_collide then
					v = Vector3f(0,0,-delta*player_travel_speed)
					character.main:move(v)
					--print("both")
					break
				elseif l_collide then
					v = Vector3f(math.abs(delta)*(-player_travel_speed/2),0,-delta*player_travel_speed)
					character.main:move(v)
					--print("left")
					break
				elseif r_collide then
					v = Vector3f(math.abs(delta)*(player_travel_speed/2),0,-delta*player_travel_speed)
					character.main:move(v)
					--print("right")
					break
				end
			end
		end
		
		character.in_cam_triggers = false
		for i,trigger in ipairs(camera_triggers) do
			if (character.main:collide(trigger.block)) then
				character.in_cam_triggers = true
				gx,gy = act_to_grid(trigger.block:get_pos().x,trigger.block:get_pos().z)
				light_grid(gx,gy)
				--light_up_trigger(thing)
			break;
			end
		end
		
		if character.main:get_pos().x < x_l_bound then
			m = Vector3f(x_l_bound,0,character.main:get_pos().z)
			character.main:set_pos(m)
		elseif character.main:get_pos().x > x_u_bound then
			m = Vector3f(x_u_bound,0,character.main:get_pos().z)
			character.main:set_pos(m)
		end
		if character.main:get_pos().z < z_l_bound then
			m = Vector3f(character.main:get_pos().x,0,z_l_bound)
			character.main:set_pos(m)
		elseif character.main:get_pos().z > z_u_bound then
			m = Vector3f(character.main:get_pos().x,0,z_u_bound)
			character.main:set_pos(m)
		end
		
		height = f:get_height(Vector2f(character.main:get_pos().x,character.main:get_pos().z))
		v = Vector3f(character.main:get_pos().x,height,character.main:get_pos().z)
		character.main:set_pos(v)
		
		wobble = math.sin(character.wobble_counter)
		r = Vector3f(0,(wobble/player_wobble_factor),0)
		character.wobble_counter = character.wobble_counter + delta*15
		character.main:set_rot(r)
		
		v = Vector3f(0,math.abs(wobble/player_bounce_factor),0)
		character.main:set_offset(v)

	end


	character.move_right = function (delta)
		v = Vector3f(0,-delta*player_turn_speed,0)
		character.main:change_dir(v)
	end
	
	character.move_east = function (delta)
		v = character.main:get_dir()
		character.main:change_dir(Vector3f(-v.x,-v.y,-v.z))
		v = Vector3f(-delta*player_travel_speed,0,0)
		character.main:move(v)
		
		cpos = character.main:get_pos()
		gx,gy = act_to_grid(cpos.x,cpos.z)
		
		if (gx > level.cage.width) then
			character.main:move(Vector3f(-v.x,-v.y,-v.z))
		else
			character.position(delta)
		end
	end

	character.move_left = function (delta)
		v = Vector3f(0,delta*player_turn_speed,0)
		character.main:change_dir(v)
	end
	
	character.move_west = function (delta)
		v = character.main:get_dir()
		character.main:change_dir(Vector3f(-v.x,-v.y,-v.z))
		v = Vector3f(delta*player_travel_speed,0,0)
		character.main:move(v)
		
		cpos = character.main:get_pos()
		gx,gy = act_to_grid(cpos.x,cpos.z)
		
		if (gx <= 0) then
			character.main:move(Vector3f(-v.x,-v.y,-v.z))
		else
			character.position(delta)
		end
	end

	character.move_up = function (delta)
		v = Vector3f(0,0,delta*player_travel_speed)
		character.main:move(v)
		
		character.position(delta)
	end

	character.move_north = function (delta)
		v = character.main:get_dir()
		character.main:change_dir(Vector3f(-v.x,-v.y,-v.z))
		
		v = Vector3f(0,0,delta*player_travel_speed)
		character.main:move(v)
		
		cpos = character.main:get_pos()
		gx,gy = act_to_grid(cpos.x,cpos.z)
		
		if (gy > level.cage.height) then
			character.main:move(Vector3f(-v.x,-v.y,-v.z))
		else
			character.position(delta)
		end
	end

	character.move_down = function (delta)
		v = Vector3f(0,0,-delta*player_travel_speed)
		character.main:move(v)
		
		character.position(-delta)
	end
	
	character.move_south = function (delta)
		v = character.main:get_dir()
		character.main:change_dir(Vector3f(-v.x,-v.y,-v.z))
		
		v = Vector3f(0,0,-delta*player_travel_speed)
		character.main:move(v)
		
		cpos = character.main:get_pos()
		gx,gy = act_to_grid(cpos.x,cpos.z)
		
		if (gy <= 0) then
			character.main:move(Vector3f(-v.x,-v.y,-v.z))
		else
			character.position(-delta)
		end
	end
	
	return character
	
end
