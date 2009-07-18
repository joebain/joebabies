
w = nil
b = nil

function start (world)

	w = world
	
	b = w:new_block("hedgehog.obj","hedgehog.bmp")
	v = Vector3f(0,0,-12)
	b:move(v)
	
	for i=1,10 do
		b2 = w:new_block("block.obj","blue_block.bmp")
		v = Vector3f(math.random(-20,20),0,math.random(-20,20))
		b2:move(v)
	end
	
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
	v = Vector3f(0,1,0)
	b:rotate(v)
end

function left ()
	v = Vector3f(0,-1,0)
	b:rotate(v)
end

function up ()
	--for some reason everything disappears if you remove this print statement
	v = Vector3f(0,0,0.2)
	b:move(v)
end

function down()
	v = Vector3f(0,0,-0.2)
	b:move(v)
end
