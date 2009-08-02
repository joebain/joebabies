
w = nil
bf = nil
b = nil
bs = nil
f = nil
s = nil
ts = {}
scale = 100

player_turn_speed = 40.0
player_travel_speed = 10.0

--~ buttons = {
	--~ ["up"] = up(),
	--~ ["down"] = down(),
	--~ ["right"] = right(),
	--~ ["left"] = left()
--~ }

function start (world)

	w = world
	bf = w:get_block_factory()
	bs = w:get_buttons()
	
	f = bf:new_floor("simple_hmap","grass.bmp",5)
	s = bf:new_sky("sky.bmp")
	s:set_scale(200)
	
	b = bf:new_character("hedgehog.obj","hedgehog.bmp")
	v = Vector3f(2,0,2)
	v.y = f:get_height(Vector2f(v.x,v.z))
	b:set_pos(v)
	v = Vector3f(0,45,0)
	b:rotate(v)
	
	for i=1,20 do
		b2 = bf:new_block3d("tree.obj","tree.bmp")
		v = Vector3f(math.random(0,100),0,math.random(0,40))
		v.y = f:get_height(Vector2f(v.x,v.z))
		b2:move(v)
	end
	
	for i=1,20 do
		b2 = bf:new_character("turtle.obj","turtle.bmp")
		v = Vector3f(math.random(0,40),0,math.random(0,40))
		v.y = f:get_height(Vector2f(v.x,v.z))
		b2:move(v)
		v = Vector3f(0,math.random(0,360),0)
		b2:rotate(v)
		table.insert(ts,b2)
	end
	
	v = Vector2f(200,100)
	hud = bf:new_blockHUD(v,"hedgehog_hud.bmp")
	--v = Vector3f(0,0,1)
	--hud:move(v)
	
	--v = Vector2f(400,40)
	--hud = bf:new_blockHUD(v,"blank.bmp")
	--v = Vector3f(200,200,0)
	--hud:move(v)
	
	v = Vector2f(300,0)
	s = Vector2f(20,20)
	text = bf:new_blockText(v,s,"zoo babies!","font_wbg.bmp")
	
	d = w:get_display()
	c = d:get_camera()
	
	c:follow(b)
	
	--~ c_l = Controller("left")
	--~ w:reg_key_left(c_l)
	--~ 
	--~ c_r = Controller("right")
	--~ w:reg_key_right(c_r)
	--~ 
	--~ c_u = Controller("up")
	--~ w:reg_key_up(c_u)
	--~ 
	--~ c_d = Controller("down")
	--~ w:reg_key_down(c_d)
	music = world:new_audio_file("main", true);
	sound = world:new_audio_file("bugsbunny2", false);
	music:play();
	sound:play_loop(3);
end

function step (delta)
	for i = 1,#ts do
		m = Vector3f(0,0,1.0*delta)
		ts[i]:move(m)
		height = f:get_height(Vector2f(ts[i]:get_pos().x,ts[i]:get_pos().z))
		v = Vector3f(ts[i]:get_pos().x,height,ts[i]:get_pos().z)
		ts[i]:set_pos(v)
		if (math.random(0,10) == 1) then
			r = Vector3f(0,math.random(-20,20),0)
			ts[i]:rotate(r)
		end
	end
	
	if (bs.up) then up(delta) end
	if (bs.down) then down(delta) end
	if (bs.left) then left(delta) end
	if (bs.right) then right(delta) end
	
end

function right (delta)
	v = Vector3f(0,-delta*player_turn_speed,0)
	b:rotate(v)
end

function left (delta)
	v = Vector3f(0,delta*player_turn_speed,0)
	b:rotate(v)
end

function up (delta)
	v = Vector3f(0,0,delta*player_travel_speed)
	b:move(v)
	height = f:get_height(Vector2f(b:get_pos().x,b:get_pos().z))
	v = Vector3f(b:get_pos().x,height,b:get_pos().z)
	b:set_pos(v)
end

function down (delta)
	v = Vector3f(0,0,-delta*player_travel_speed)
	b:move(v)
	height = f:get_height(Vector2f(b:get_pos().x,b:get_pos().z))
	v = Vector3f(b:get_pos().x,height,b:get_pos().z)
	b:set_pos(v)
end

