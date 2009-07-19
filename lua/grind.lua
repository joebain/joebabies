
w = nil
b = nil

function start (world)

	w = world
	
	b = w:new_character("hedgehog.obj","hedgehog.bmp")
	v = Vector3f(0,0,-12)
	b:move(v)
	
	
	for i=1,10 do
		b2 = w:new_block3d("block.obj","blue_block.bmp")
		v = Vector3f(math.random(-20,20),0,math.random(-20,20))
		b2:move(v)
	end
	
	for i=1,5 do
		b2 = w:new_block3d("turtle.obj","turtle.bmp")
		v = Vector3f(math.random(-20,20),0,math.random(-20,20))
		b2:move(v)
		v = Vector3f(0,math.random(0,360),0)
		b2:rotate(v)
	end
	
	for x=-10,10 do
		for y=-10,10 do
			t = w:new_block3d("square.obj","grass.bmp")
			v = Vector3f(x*2,-1,y*2)
			t:move(v)
			v = Vector3f(0,0,-90)
			t:rotate(v)
		end
	end
	
	v = Vector2f(0.5,0.25)
	hh = w:new_block2d(v,"hedgehog_hud.bmp")
	depth = 1
	v = Vector2f(0.12,-0.42)
	hh:move(v)
	
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

function step (amount)
	
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
end

function down()
	v = Vector3f(0,0,-0.2)
	b:move(v)
end

