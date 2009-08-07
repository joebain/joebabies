function load_level(filename)

	level.map = {}
	i = 0
	max_j = 0
	for line in io.lines(filename) do
		level.map[i] = {}
		j = 0
		for w in string.gmatch(line, "[-%d%l]") do
			level.map[i][j] = {}
			level.map[i][j].symbol = w
			j = j + 1
		end
		if j < max_j then j = max_j end
		i = i + 1
	end
	level.cage = {}
	level.cage.width = j
	level.cage.height = i
	
end

function set_level_size(s)
	level.size = s
end

function set_level_offset(x,y)
	level.off_x = x
	level.off_y = y
end

function set_cage_offset(x,y)
	level.cage.x = x
	level.cage.y = y
end

function model_level()
	for i=1,#level.map do
		for j=1,#level.map[i] do
			place_model(level.map[i][j].symbol,i,j)
		end
	end
end

function place_model(symbol,x,y)

	if (symbol ~= '0') then

		print("placing " .. symbol .. " at " .. x .. "," .. y)

		x,y = grid_to_act(x,y)
		--x = ((level.cage.width - x) + level.off_x + level.cage.x)*level.size
		--y = (y + level.off_y + level.cage.y)*level.size
		
		print("actual " .. symbol .. " at " .. x .. "," .. y)
		
		i,j = act_to_grid(x,y)
		
		print("checking " .. symbol .. " at " .. i .. "," .. j)
		
		if (symbol == 'g') then
			
			g = bf:new_character("gorilla.obj","gorilla.bmp")
			v = Vector3f(x,0,y)
			v.y = f:get_height(Vector2f(v.x,v.z))
			g:move(v)
			
			animal_g = {}
			animal_g.block = g
			animal_g.direction = {}
			animal_g.direction.x = 0
			animal_g.direction.y = 0
			animal_g.moving = false
			animal_g.speed = 3
			
			table.insert(animals,animal_g)
			
			level.map[i][j] = nil
			
		elseif (symbol == 'b') then
			
			b = bf:new_block3d("box.obj","box.bmp")
			v = Vector3f(x,0,y)
			v.y = f:get_height(Vector2f(v.x,v.z))
			b:move(v)
			v = Vector3f(0,math.random(-30,30),0)
			b:change_dir(v)
			
			item_b = {}
			item_b.block = b
			item_b.type = "block"
			
			level.map[i][j] = item_b
			
		elseif (symbol == 'r') then
		
		  b = bf:new_block3d("rock.obj","rock.bmp")
		  v = Vector3f(x,0,y)
		  v.y = f:get_height(Vector2f(v.x,v.z))
		  b:move(v)
		  v = Vector3f(math.random(-20,20),math.random(-20,20),math.random(-20,20))
		  b:change_dir(v)
		  
		  item_b = {}
		  item_b.block = b
		  item_b.type = "rock"
		  
		  level.map[i][j] = item_b
			
		else
		
		  level.map[i][j] = nil
		
		end
	
	end
end

function put_cage()

	lx = (level.cage.x + level.off_x)*level.size
	ly = (level.cage.y + level.off_y)*level.size
	ux = (level.cage.x + level.cage.width + level.off_x)*level.size
	uy = (level.cage.y + level.cage.height + level.off_y)*level.size
	wx = level.cage.width*level.size
	wy = level.cage.height*level.size

	--print (lx .. "," .. ly .. "," .. ux .. "," .. uy .. "," .. wx .. "," .. wy)

	-- ne
	cage1 = bf:new_flat_block("cage.bmp",Vector2f(wx,8),true)
	cage1:move(Vector3f(lx,0,uy))
	cage1:set_tex_size(Vector2f(1,5))
	cage1ff = bf:new_imaginary_block(Vector3f(wx,8,1))
	cage1ff:move(Vector3f(lx,0,uy-1))
	--cage1ff:toggle_debug()
	table.insert(scenery, cage1ff)
	
	
	-- sw
	cage2 = bf:new_flat_block("bricks.bmp",Vector2f(wx,8),false)
	cage2:move(Vector3f(lx,0,ly))
	cage2:set_tex_size(Vector2f(1,5))
	cage2ff = bf:new_imaginary_block(Vector3f(wx,8,1))
	cage2ff:move(Vector3f(lx,0,ly))
	--cage2ff:toggle_debug()
	table.insert(scenery, cage2ff)
	
	-- se
	cage3 = bf:new_flat_block("cage.bmp",Vector2f(wy,8),true)
	cage3:move(Vector3f(lx,0,uy))
	cage3:set_tex_size(Vector2f(1,5))
	cage3:rotate(Vector3f(0,90,0))
	cage3ff = bf:new_imaginary_block(Vector3f(wy,8,1))
	cage3ff:move(Vector3f(lx,0,uy))
	cage3ff:change_dir(Vector3f(0,90,0))
	--cage3ff:toggle_debug()
	table.insert(scenery, cage3ff)
	
	-- nw
	cage4 = bf:new_flat_block("bricks.bmp",Vector2f(wy,8),false)
	cage4:move(Vector3f(ux,0,uy))
	cage4:set_tex_size(Vector2f(1,5))
	cage4:rotate(Vector3f(0,90,0))
	cage4ff = bf:new_imaginary_block(Vector3f(wy,8,1))
	cage4ff:move(Vector3f(ux-1,0,uy))
	cage4ff:change_dir(Vector3f(0,90,0))
	--cage4ff:toggle_debug()
	table.insert(scenery, cage4ff)

end

