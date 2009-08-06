

function level1_setup()
  character.main = bf:new_character("hedgehog.obj","hedgehog.bmp")
	v = Vector3f(x_l_bound+2,0,z_l_bound+2)
	v.y = f:get_height(Vector2f(v.x,v.z))
	character.main:set_pos(v)
	whisker_size = 0.5
	character.whisker_r = bf:new_imaginary_block(Vector3f(whisker_size,whisker_size,whisker_size))
	character.whisker_r:nudge(Vector3f(0.2,1,0.5))
	character.main:add_child(character.whisker_r)
	character.whisker_l = bf:new_imaginary_block(Vector3f(whisker_size,whisker_size,whisker_size))
	character.whisker_l:nudge(Vector3f(0.2,1,-0.5))
	character.main:add_child(character.whisker_l)
	
	v = Vector3f(0,45,0)
	character.main:set_dir(v)
	
	c:follow(character.main)
	
	scenery = {}
	
	-- ne
	cage1 = bf:new_flat_block("fence.bmp",Vector2f(60,8),true)
	cage1:move(Vector3f(x_l_bound+20,0,z_l_bound+80))
	cage1:set_tex_size(Vector2f(-0.9,20))
	cage1ff = bf:new_imaginary_block(Vector3f(62,8,1))
	cage1ff:move(Vector3f(x_l_bound+19,0,z_l_bound+80))
	--cage1ff:toggle_debug()
	table.insert(scenery, cage1ff)
	
	
	-- sw
  cage2 = bf:new_flat_block("bricks.bmp",Vector2f(60,8),false)
	cage2:move(Vector3f(x_l_bound+20,0,z_l_bound+20))
	cage2:set_tex_size(Vector2f(2,20))
	cage2ff = bf:new_imaginary_block(Vector3f(62,8,1))
	cage2ff:move(Vector3f(x_l_bound+19,0,z_l_bound+19))
	--cage2ff:toggle_debug()
	table.insert(scenery, cage2ff)
	
	-- se
	cage3 = bf:new_flat_block("fence.bmp",Vector2f(60,8),true)
	cage3:move(Vector3f(x_l_bound+20,0,z_l_bound+80))
	cage3:set_tex_size(Vector2f(-0.9,20))
	cage3:rotate(Vector3f(0,90,0))
	cage3ff = bf:new_imaginary_block(Vector3f(62,8,1))
	cage3ff:move(Vector3f(x_l_bound+19,0,z_l_bound+81))
  cage3ff:change_dir(Vector3f(0,90,0))
	--cage3ff:toggle_debug()
	table.insert(scenery, cage3ff)
	
	-- nw
  cage4 = bf:new_flat_block("bricks.bmp",Vector2f(60,8),false)
	cage4:move(Vector3f(x_l_bound+80,0,z_l_bound+20))
	cage4:set_tex_size(Vector2f(2,20))
	cage4:rotate(Vector3f(0,270,0))
	cage4ff = bf:new_imaginary_block(Vector3f(62,8,1))
	cage4ff:move(Vector3f(x_l_bound+81,0,z_l_bound+19))
  cage4ff:change_dir(Vector3f(0,270,0))
	--cage4ff:toggle_debug()
	table.insert(scenery, cage4ff)
	
	
	--lower x
	fence1 = bf:new_flat_block("fence.bmp",Vector2f(x_u_bound-x_l_bound+2,2),true)
	fence1:move(Vector3f(x_l_bound-1,0,z_l_bound-1))
	fence1:set_tex_size(Vector2f(-0.9,20))
	--lower z
	fence2 = bf:new_flat_block("fence.bmp",Vector2f(z_u_bound-z_l_bound+2,2),true)
	fence2:move(Vector3f(x_l_bound-1,0,z_u_bound+1))
	fence2:set_tex_size(Vector2f(1,20))
	fence2:rotate(Vector3f(0,90,0))
	--upper x
	fence3 = bf:new_flat_block("fence.bmp",Vector2f(x_u_bound-x_l_bound+2,2),true)
	fence3:move(Vector3f(x_u_bound+1,0,z_u_bound+1))
	fence3:set_tex_size(Vector2f(1,20))
	fence3:rotate(Vector3f(0,90,0))
	--upper z
	fence4 = bf:new_flat_block("fence.bmp",Vector2f(z_u_bound-z_l_bound+2,2),true)
	fence4:move(Vector3f(x_l_bound-1,0,z_u_bound+1))
	fence4:set_tex_size(Vector2f(1,20))
	
	for i=1,50 do
		b2 = bf:new_character("gorilla.obj","gorilla.bmp")
		v = Vector3f(math.random(x_l_bound,x_u_bound),0,math.random(z_l_bound,z_u_bound))
		v.y = f:get_height(Vector2f(v.x,v.z))
		b2:move(v)
		v = Vector3f(0,math.random(0,360),0)
		b2:change_dir(v)
		table.insert(ts,b2)
	end
end

function level1_step(delta)

end
