world = nil
display = nil
camera = nil
block_factory = nil
buttons = nil

me = nil
magnum_house = nil
me_moving = false
me_dir = true

speed = 10
followed = nil
camera_distance = 30

picked_object = nil
mouse_object_offset = nil

function start (_world)
	world = _world
	
	block_factory = _world:get_block_factory()
	buttons = world:get_buttons()
	display = _world:get_display()
	camera = display:get_camera()
		
	me = load_me()
	
	camera:follow(me)
	camera:set_distance(camera_distance)
	followed = me
		
	scenery = load_scenery()
	
end

function step (_delta)
	me_moving = false
	if (buttons.up) then
		followed:move(Vector3f(0,speed*_delta,0))
		me_moving = true
	end
	if (buttons.down) then
		followed:move(Vector3f(0,-speed*_delta,0))
		me_moving = true
	end
	if (buttons.left) then
		followed:move(Vector3f(speed*_delta,0,0))
		me_moving = true
		me_dir = true
	end
	if (buttons.right) then
		followed:move(Vector3f(-speed*_delta,0,0))
		me_moving = true
		me_dir = false
	end
	if (me_moving) then
		me:start()
	else
		me:stop()
		me:reset()
	end
	me:set_facing(me_dir)
	
	if (buttons.w) then
		camera_distance = camera_distance - 50*_delta
		camera:set_distance(camera_distance)
	end
	if (buttons.s) then
		camera:set_distance(camera_distance)
		camera_distance = camera_distance + 50*_delta
	end
	
	handle_mouse()
end

function handle_mouse()
	--deal with scrolling
	if (buttons.mouse_wheel_move ~= 0) then
		tmp_object = display:pick()
		if (tmp_object == nil) then
			picked_object = nil
			return
		end
		--move the object in z space
		tmp_object:move(Vector3f(0,0,buttons.mouse_wheel_move))
	end

	--once we have dealt with scrolling we only care about lmb
	if (not buttons.lmb) then
		picked_object = nil
		return
	end
	
	--if we didnt get the object before try now
	if (tmp_object == nil) then
		tmp_object = display:pick()
	end
	
	--early exit if there was nothing under the cursor or it was me
	if (tmp_object == nil or tmp_object == me) then
		picked_object = nil
		return
	end
	
	--get the mouse coords in world space
	mouse_pos = display:project_xy(buttons.mouse_x, buttons.mouse_y, tmp_object:get_pos().z)
	--if we have had the same object twice we move it
	if (picked_object == tmp_object) then
		tmp_object:set_pos(mouse_pos + mouse_object_offset)
	end
	--save this stuff for next time
	picked_object = tmp_object
	mouse_object_offset = picked_object:get_pos() - mouse_pos
	--globals?
	tmp_object = nil
end

function load_me()
	size = Vector2f(10,10)
	frame_size = Vector2f(0.25,1)
	times = {0.2,0.2,0.2,0.2}
	me = block_factory:new_animated_flat_block("me_walk.png", size, frame_size, 4, 1, times, false, true, true)
	offset = Vector3f(0,0,-1)
	me:move(offset)
	return me
end

function load_scenery()
	size = Vector2f(40,20)
	magnum_house = block_factory:new_flat_block("magnum_house.png", size, false, true)
	magnum_house:set_facing(false)
	road = block_factory:new_flat_block("road.png", size, false, true)
	road:set_facing(false)
	road2 = block_factory:new_flat_block("road2.png", size, false, true)
	road2:set_facing(false)
	scenery = {}
	offset = Vector3f(15,0,0)
	magnum_house:move(offset)
	scenery[1] = magnum_house
	offset = Vector3f(-15,0,0)
	road:move(offset)
	scenery[2] = road
	offset = Vector3f(0,0,1)
	road2:move(offset)
	scenery[3] = road2
	return scenery
end
