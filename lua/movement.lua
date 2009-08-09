
player_turn_speed = 40.0
player_travel_speed = 10.0
player_wobble_counter = 0.0
player_wobble_factor = 0.05
player_bounce_factor = 5.0

in_cam_triggers = false

function position_character(delta)
	
	for i,thing in ipairs(scenery) do
		l_collide = character.whisker_l:collide(thing)
		r_collide = character.whisker_r:collide(thing)
		m_collide = character.main:collide(thing)
		
		if (in_cam_triggers) then
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
	
	in_cam_triggers_tmp = false
	for i,thing in ipairs(camera_triggers) do
		if (character.main:collide(thing.block)) then
			c:follow(high_cam_obj)
			in_cam_triggers_tmp = true
			light_up_trigger(thing)
		break;
		end
	end
	if (in_cam_triggers_tmp == false) then
		c:follow(character.main)
	end
	in_cam_triggers = in_cam_triggers_tmp
	
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
	
	wobble = math.sin(player_wobble_counter)
	r = Vector3f(0,(wobble/player_wobble_factor),0)
	player_wobble_counter = player_wobble_counter + delta*15
	character.main:set_rot(r)
	
	v = Vector3f(0,math.abs(wobble/player_bounce_factor),0)
	character.main:set_offset(v)

end


function move_right (delta)
	if (in_cam_triggers) then
		v = character.main:get_dir()
		character.main:change_dir(Vector3f(-v.x,-v.y,-v.z))
		v = Vector3f(-delta*player_travel_speed,0,0)
		character.main:move(v)
		
		position_character(delta)
	else
		v = Vector3f(0,-delta*player_turn_speed,0)
		character.main:change_dir(v)
	end
end

function move_left (delta)
	if (in_cam_triggers) then
		v = character.main:get_dir()
		character.main:change_dir(Vector3f(-v.x,-v.y,-v.z))
		v = Vector3f(delta*player_travel_speed,0,0)
		character.main:move(v)
		
		position_character(delta)
	else
		v = Vector3f(0,delta*player_turn_speed,0)
		character.main:change_dir(v)
	end
end

function move_up (delta)
	if (in_cam_triggers) then
		v = character.main:get_dir()
		character.main:change_dir(Vector3f(-v.x,-v.y,-v.z))
	end
	v = Vector3f(0,0,delta*player_travel_speed)
	character.main:move(v)
	
	position_character(delta)
end

function move_down (delta)
	if (in_cam_triggers) then
		v = character.main:get_dir()
		character.main:change_dir(Vector3f(-v.x,-v.y,-v.z))
	end
	v = Vector3f(0,0,-delta*player_travel_speed)
	character.main:move(v)
	
	position_character(-delta)
end

function light_up_trigger(trigger)
	if (trigger.light_count <= 0) then
		light = bf:new_flat_block("outline-yellow.bmp",Vector2f(level.size,level.size), true)
		light:move(Vector3f(trigger.block:get_pos().x,0.1,trigger.block:get_pos().z))
		light:rotate(Vector3f(90,0,0))
		--light:set_transparency(0.99)
		
		trigger.light = light
	end
	trigger.light_count = 1
	trigger.light_switch = true
	--print("setting to 1")
end

function step_trigger(trigger,delta)
	if trigger.light_switch == true then
		if trigger.light_count > 0 then
			if character.main:collide(trigger.block) then
				trigger.light_count = 1
			else
				trigger.light_count = trigger.light_count - delta*2
				--trigger.light:set_transparency(trigger.light_count)
			end
		elseif trigger.light_count <= 0 then
			trigger.light_count = 0
			trigger.light_switch = false
			bf:remove_flat_block(trigger.light)
		end
	end
end

function make_character()
	character.main = bf:new_character("techie.obj","techie.bmp")
	v = Vector3f(x_l_bound+2,0,z_l_bound+2)
	v.y = f:get_height(Vector2f(v.x,v.z))
	character.main:set_pos(v)
	whisker_size = 0.5
	character.whisker_r = bf:new_imaginary_block(Vector3f(whisker_size/4,whisker_size,whisker_size))
	character.whisker_r:nudge(Vector3f(-0.5,1,0))
	--character.whisker_r:toggle_debug()
	character.main:add_child(character.whisker_r)
	character.whisker_l = bf:new_imaginary_block(Vector3f(whisker_size/4,whisker_size,whisker_size))
	character.whisker_l:nudge(Vector3f(0.5,1,0))
	--character.whisker_l:toggle_debug()
	character.main:add_child(character.whisker_l)
end
