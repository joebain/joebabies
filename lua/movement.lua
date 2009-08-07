
player_turn_speed = 40.0
player_travel_speed = 10.0
player_wobble_counter = 0.0
player_wobble_factor = 0.5
player_bounce_factor = 5.0

function position_character(delta)
	
	for i,thing in ipairs(scenery) do
		l_collide = character.whisker_l:collide(thing)
		r_collide = character.whisker_r:collide(thing)
		if l_collide and r_collide then
			v = Vector3f(0,0,-delta*player_travel_speed)
			character.main:move(v)
			--print("both")
			break
		elseif l_collide then
			v = Vector3f(math.abs(delta)*-player_travel_speed/2,0,-delta*player_travel_speed)
			character.main:move(v)
			--print("left")
			break
		elseif r_collide then
			v = Vector3f(math.abs(delta)*player_travel_speed/2,0,-delta*player_travel_speed)
			character.main:move(v)
			--print("right")
			break
		end
		--~ if hedgey:collide(thing) then
			--~ print("oh no a tree " .. hedgey:get_pos().x)
		--~ end
	end
	
	in_cam_triggers = false
	for i,thing in ipairs(camera_triggers) do
		if (character.main:collide(thing)) then
			c:follow(high_cam_obj)
			--c:set_height(-1)
			in_cam_triggers = true
		break;
		end
	end
	if (in_cam_triggers == false) then
		c:follow(character.main)
		--c:set_height(0.3)
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
	
	wobble = math.sin(player_wobble_counter)
	r = Vector3f(0,100*delta*(wobble/player_wobble_factor),0)
	player_wobble_counter = player_wobble_counter + delta*15
	character.main:rotate(r)
	
	v = Vector3f(0,math.abs(wobble/player_bounce_factor),0)
	character.main:set_offset(v)

end


function move_right (delta)
	v = Vector3f(0,-delta*player_turn_speed,0)
	character.main:change_dir(v)
end

function move_left (delta)
	v = Vector3f(0,delta*player_turn_speed,0)
	character.main:change_dir(v)
end

function move_up (delta)
	v = Vector3f(0,0,delta*player_travel_speed)
	character.main:move(v)
	
	position_character(delta)
end

function move_down (delta)
	v = Vector3f(0,0,-delta*player_travel_speed)
	character.main:move(v)
	
	position_character(-delta)
end
