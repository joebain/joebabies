world = nil
display = nil
camera = nil
block_factory = nil
buttons = nil

speed = 0.2
followed = nil
camera_distance = 10

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
	if (buttons.up) then
		followed:move(Vector3f(0,speed,0))
	end
	if (buttons.down) then
		followed:move(Vector3f(0,-speed,0))
	end
	if (buttons.left) then
		followed:move(Vector3f(speed,0,0))
	end
	if (buttons.right) then
		followed:move(Vector3f(-speed,0,0))
	end
	if (buttons.w) then
		camera_distance = camera_distance - 0.5
		camera:set_distance(camera_distance)
	end
	if (buttons.s) then
		camera:set_distance(camera_distance)
		camera_distance = camera_distance + 0.5
	end
end

function load_me()
	size = Vector2f(5,10)
	me = block_factory:new_flat_block("me_standing.png", size, false, true)
	rotate = Vector3f(0,180,0)
	offset = Vector3f(0,0,-1)
	me:move(offset)
	return me
end

function load_scenery()
	size = Vector2f(40,20)
	magnum_house = block_factory:new_flat_block("magnum_house.png", size, false, true)
	road = block_factory:new_flat_block("road.png", size, false, true)
	scenery = {}
	scenery[1] = magnum_house
	offset = Vector3f(40,0,0)
	road:move(offset)
	scenery[2] = road
	return scenery
end
