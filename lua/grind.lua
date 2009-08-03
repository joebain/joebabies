
w = nil
display = nil
bf = nil
hedgey = nil
bs = nil
f = nil
s = nil
ts = {}
block = nil
scale = 100
collided = false

player_turn_speed = 40.0
player_travel_speed = 10.0
player_wobble_counter = 0.0
player_wobble_factor = 0.5
player_bounce_factor = 5.0

x_l_bound = 100
z_l_bound = 100
x_u_bound = 200
z_u_bound = 200

function start (world)

	w = world
	bf = w:get_block_factory()
	bs = w:get_buttons()
	
	f = bf:new_floor("simple_hmap","grass.bmp",5)
	s = bf:new_sky("sky.bmp")
	s:set_scale(200)
	
	hedgey = bf:new_character("hedgehog.obj","hedgehog.bmp")
	v = Vector3f(x_l_bound+2,0,z_l_bound+2)
	v.y = f:get_height(Vector2f(v.x,v.z))
	hedgey:set_pos(v)
	v = Vector3f(0,45,0)
	hedgey:set_dir(v)
	
	for i=1,40 do
		b2 = bf:new_block3d("tree.obj","tree.bmp")
		v = Vector3f(math.random(x_l_bound,x_u_bound),0,math.random(z_l_bound,z_u_bound))
		v.y = f:get_height(Vector2f(v.x,v.z))
		b2:move(v)
	end
	
	for i=1,60 do
		b2 = bf:new_character("turtle.obj","turtle.bmp")
		v = Vector3f(math.random(x_l_bound,x_u_bound),0,math.random(z_l_bound,z_u_bound))
		v.y = f:get_height(Vector2f(v.x,v.z))
		b2:move(v)
		v = Vector3f(0,math.random(0,360),0)
		b2:change_dir(v)
		table.insert(ts,b2)
	end
	
	block = bf:new_block3d("block.obj","red_block.bmp")
	v = Vector3f(x_l_bound+20,0,z_l_bound+20)
	v.y = f:get_height(Vector2f(v.x,v.z))
	block:move(v)
	
	display = w:get_display()
	c = display:get_camera()
	
	c:follow(hedgey)
	
	music = world:new_audio_file("main", true);
	sound = world:new_audio_file("bugsbunny2", false);
	--music:play();
	--sound:play();
end

function step (delta)
	for i = 1,#ts do
		m = Vector3f(0,0,3.0*delta)
		ts[i]:move(m)
		if (ts[i]:get_pos().x < x_l_bound or ts[i]:get_pos().z < z_l_bound or
		    ts[i]:get_pos().x > x_u_bound or ts[i]:get_pos().z > z_u_bound) then
			m = Vector3f(0,0,-6.0*delta)
			ts[i]:move(m)
			r = Vector3f(0,45.0,0)
			ts[i]:change_dir(r)
		end
		height = f:get_height(Vector2f(ts[i]:get_pos().x,ts[i]:get_pos().z))
		v = Vector3f(ts[i]:get_pos().x,height,ts[i]:get_pos().z)
		ts[i]:set_pos(v)
		rand = math.random(0,200)
		if (rand == 1) then
			r = Vector3f(0,45.0,0)
			ts[i]:change_dir(r)
		elseif (rand == 2) then
			r = Vector3f(0,-45.0,0)
			ts[i]:change_dir(r)
		end
	end
	
	if (bs.up) then up(delta) end
	if (bs.down) then down(delta) end
	if (bs.left) then left(delta) end
	if (bs.right) then right(delta) end
	
	if hedgey:collide(block) and not collided then
		put_dialogue("Hello, my name is Hedgey the Hedgehog. I like cheese and fast cars. Do you have a cracker for me?","hedgehog")
		collided = true
	end
	
end

function right (delta)
	v = Vector3f(0,-delta*player_turn_speed,0)
	hedgey:change_dir(v)
end

function left (delta)
	v = Vector3f(0,delta*player_turn_speed,0)
	hedgey:change_dir(v)
end

function up (delta)
	v = Vector3f(0,0,delta*player_travel_speed)
	hedgey:move(v)
	
	position_hedgey(delta)
end

function down (delta)
	v = Vector3f(0,0,-delta*player_travel_speed)
	hedgey:move(v)
	
	position_hedgey(delta)
end

function position_hedgey(delta)
	
	if hedgey:get_pos().x < x_l_bound then
		m = Vector3f(x_l_bound,0,hedgey:get_pos().z)
		hedgey:set_pos(m)
	elseif hedgey:get_pos().x > x_u_bound then
		m = Vector3f(x_u_bound,0,hedgey:get_pos().z)
		hedgey:set_pos(m)
	end
	if hedgey:get_pos().z < z_l_bound then
		m = Vector3f(hedgey:get_pos().x,0,z_l_bound)
		hedgey:set_pos(m)
	elseif hedgey:get_pos().z > z_u_bound then
		m = Vector3f(hedgey:get_pos().x,0,z_u_bound)
		hedgey:set_pos(m)
  	end
	
	height = f:get_height(Vector2f(hedgey:get_pos().x,hedgey:get_pos().z))
	v = Vector3f(hedgey:get_pos().x,height,hedgey:get_pos().z)
	hedgey:set_pos(v)
	
	wobble = math.sin(player_wobble_counter)
	r = Vector3f(0,wobble/player_wobble_factor,0)
	player_wobble_counter = player_wobble_counter + delta*15
	hedgey:rotate(r)
	
	v = Vector3f(0,math.abs(wobble/player_bounce_factor),0)
	hedgey:set_offset(v)

end

function put_dialogue(text,character)
	
	length = text:len()
	
	text_size = Vector2f(20,20)
	
	line_length = ((display:get_width()-100)/text_size.x)-4
	
	height = math.ceil(length/line_length)
	length = line_length
	
	t_table = {}
	
	backing_size = Vector2f((length+3)*text_size.x,(height+1.5)*text_size.y*1.2)
	
	backing_pos = Vector2f((display:get_width()/2) - (backing_size.x/2) + 50,text_size.y*2)
	
	backing = bf:new_blockHUD(backing_size,"dialogue.bmp")
	backing:move(backing_pos)
	
	table.insert(t_table,backing)
	
	text_pos = Vector2f(backing_pos.x + text_size.x*2,(backing_pos.y + backing_size.y) - text_size.y*2)
	
	for i = 1,height do
		line = text:sub(length*(i-1)+1,length*i)
		if (line:sub(1,1) == " ") then
			line = line:sub(2)
		end
		table.insert(t_table,bf:new_blockText(text_pos,text_size,line,"font_wbg.bmp"))
		text_pos.y = text_pos.y - text_size.y*1.2
	end
	
	v = Vector2f(200,100)
	hud = bf:new_blockHUD(v,character .. "_hud.bmp")
	
	return t_table
	
end

