
w = nil
b = nil
f = nil
s = nil
ts = {}
scale = 100

function start (world)

	w = world
	
	f = w:new_floor("simple_hmap","grass.bmp",5)
	s = w:new_sky("sky.bmp")
	s:set_scale(70)
	
	b = w:new_character("hedgehog.obj","hedgehog.bmp")
	v = Vector3f(2,0,2)
	v.y = f:get_height(Vector2f(v.x,v.z))
	b:set_pos(v)
	v = Vector3f(0,45,0)
	b:rotate(v)
	
	for i=1,20 do
		b2 = w:new_block3d("tree.obj","tree.bmp")
		v = Vector3f(math.random(0,100),0,math.random(0,40))
		v.y = f:get_height(Vector2f(v.x,v.z))
		b2:move(v)
	end
	
	for i=1,20 do
		b2 = w:new_character("turtle.obj","turtle.bmp")
		v = Vector3f(math.random(0,40),0,math.random(0,40))
		v.y = f:get_height(Vector2f(v.x,v.z))
		b2:move(v)
		v = Vector3f(0,math.random(0,360),0)
		b2:rotate(v)
		table.insert(ts,b2)
	end
	
	v = Vector2f(0.5,0.25) -- size of the sprite
	hud = w:new_blockHUD(v,"hedgehog_hud.bmp")
	v = Vector3f(0.12,-0.42,0) -- position on screen
	hud:move(v)
	
	d = w:get_display()
	c = d:get_camera()
	
	c:follow(b)
	
	c_l = Controller("left")
	w:reg_key_left(c_l)
	
	c_r = Controller("right")
	w:reg_key_right(c_r)
	
	c_u = Controller("up")
	w:reg_key_up(c_u)
	
	c_d = Controller("down")
	w:reg_key_down(c_d)
	
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
end

function right ()
	v = Vector3f(0,-1,0)
	b:rotate(v)
end

function left ()
	v = Vector3f(0,1,0)
	b:rotate(v)
end

function up ()
	v = Vector3f(0,0,0.2)
	b:move(v)
	height = f:get_height(Vector2f(b:get_pos().x,b:get_pos().z))
	v = Vector3f(b:get_pos().x,height,b:get_pos().z)
	b:set_pos(v)
	
	--~ scale = scale + 1
	--~ s:set_scale(scale)
	--~ print("scale is " .. scale)
end

function down ()
	v = Vector3f(0,0,-0.2)
	b:move(v)
	height = f:get_height(Vector2f(b:get_pos().x,b:get_pos().z))
	v = Vector3f(b:get_pos().x,height,b:get_pos().z)
	b:set_pos(v)
	
	--~ scale = scale - 1
	--~ s:set_scale(scale)
	--~ print("scale is " .. scale)
end

