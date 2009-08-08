function load_level(filename)

	level.map = {}
	i = 1
	max_j = 0
	for line in io.lines(filename) do
		level.map[i] = {}
		j = 1
		for w in string.gmatch(line, "[-%d%l]") do
			level.map[i][j] = {}
			level.map[i][j].symbol = w
			level.map[i][j].thing = "empty"
			--io.write(i,",",j,": ",w,", ")
			j = j + 1
		end
		if j < max_j then j = max_j end
		i = i + 1
		--print()
	end
	level.cage = {}
	level.cage.width = i
	level.cage.height = j
	
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

		i = x
		j = y

		x,y = grid_to_act(x,y)
		
		if (symbol == 'g') then
			
			g = bf:new_character("gorilla.obj","gorilla.bmp")
			v = Vector3f(x,0,y)
			--v.y = f:get_height(Vector2f(v.x,v.z))
			g:move(v)
			
			animal_g = {}
			animal_g.block = g
			animal_g.direction = {}
			animal_g.direction.x = 0
			animal_g.direction.y = 0
			animal_g.moving = false
			animal_g.speed = 6
			animal_g.name = "gorilla"
			animal_g.symbol = "g"
			animal_g.target = {}
			animal_g.target.x = x
			animal_g.target.y = y
			
			table.insert(animals,animal_g)
			
			level.map[i][j].thing = "gorilla"
			level.map[i][j].symbol = "g"
			
		elseif (symbol == 'b') then
			
			b = bf:new_block3d("box.obj","box.bmp")
			v = Vector3f(x,0,y)
			v.y = f:get_height(Vector2f(v.x,v.z))
			b:move(v)
			v = Vector3f(0,math.random(-30,30),0)
			b:change_dir(v)
			
			item_b = {}
			item_b.block = b
			item_b.thing = "box"
			item_b.symbol = "b"
			
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
			item_b.thing = "rock"
			item_b.symbol = "r"

			level.map[i][j] = item_b
			
		elseif (symbol == 'i') then
		
			b = bf:new_block3d("internet.obj","internet.bmp")
			v = Vector3f(x,0,y)
			v.y = f:get_height(Vector2f(v.x,v.z))
			b:move(v)
			v = Vector3f(math.random(-20,20),math.random(-20,20),math.random(-20,20))
			b:change_dir(v)

			item_b = {}
			item_b.block = b
			item_b.thing = "internet"
			item_b.symbol = "i"

			level.map[i][j] = item_b
			table.insert(internets,item_b)
		
		else
		
			level.map[i][j].thing = "empty"
			level.map[i][j].symbol = "0"
		
		end
	
	end
end

function put_cage()

	lx = (level.cage.x + level.off_x + 1)*level.size
	ly = (level.cage.y + level.off_y + 1)*level.size
	ux = (level.cage.x + level.cage.width + level.off_x)*level.size
	uy = (level.cage.y + level.cage.height + level.off_y)*level.size
	wx = (level.cage.width-1)*level.size
	wy = (level.cage.height-1)*level.size

	startx = level.cage.x + level.off_x
	starty = level.cage.y + level.off_y
	--print (lx .. "," .. ly .. "," .. ux .. "," .. uy .. "," .. wx .. "," .. wy)

	-- north
	cage1 = bf:new_flat_block("cage.bmp",Vector2f(wx,8),true)
	cage1:move(Vector3f(lx,0,uy))
	cage1:set_tex_size(Vector2f(1,5))
	cage1ff = bf:new_imaginary_block(Vector3f(wx,8,1))
	cage1ff:move(Vector3f(lx,0,uy-1))
	--cage1ff:toggle_debug()
	table.insert(scenery, cage1ff)
	
	for i = 0,level.cage.width do
		cage1ft = bf:new_imaginary_block(Vector3f(level.size,8,level.size))
		cage1ft:move(Vector3f((startx + i)*level.size,0,uy))
		--cage1ft:toggle_debug()
		ct = {}
		ct.light_count = 0
		ct.block = cage1ft
		table.insert(camera_triggers, ct)
	end
	
	-- south
	cage2 = bf:new_flat_block("bricks.bmp",Vector2f(wx,8),false)
	cage2:move(Vector3f(lx,0,ly))
	cage2:set_tex_size(Vector2f(1,5))
	cage2ff = bf:new_imaginary_block(Vector3f(wx,8,1))
	cage2ff:move(Vector3f(lx,0,ly))
	--cage2ff:toggle_debug()
	table.insert(scenery, cage2ff)
	--~ cage2ft = bf:new_imaginary_block(Vector3f(wx+level.size*2,8,level.size))
	--~ cage2ft:move(Vector3f(lx-level.size,0,ly-level.size))
	--~ --cage2ft:toggle_debug()
	--~ table.insert(camera_triggers, cage2ft)
	
	for i = 0,level.cage.width do
		cage1ft = bf:new_imaginary_block(Vector3f(level.size,8,level.size))
		cage1ft:move(Vector3f((startx + i)*level.size,0,ly-level.size))
		--cage1ft:toggle_debug()
		ct = {}
		ct.light_count = 0
		ct.block = cage1ft
		table.insert(camera_triggers, ct)
	end
	
	-- east
	cage3 = bf:new_flat_block("cage.bmp",Vector2f(wy,8),true)
	cage3:move(Vector3f(lx,0,uy))
	cage3:set_tex_size(Vector2f(1,5))
	cage3:rotate(Vector3f(0,90,0))
	cage3ff = bf:new_imaginary_block(Vector3f(wy,8,1))
	cage3ff:move(Vector3f(lx,0,uy))
	cage3ff:change_dir(Vector3f(0,90,0))
	--cage3ff:toggle_debug()
	table.insert(scenery, cage3ff)
	--~ cage3ft = bf:new_imaginary_block(Vector3f(wy+level.size*2,8,level.size))
	--~ cage3ft:move(Vector3f(lx-level.size,0,uy+level.size))
	--~ cage3ft:change_dir(Vector3f(0,90,0))
	--~ --cage3ft:toggle_debug()
	--~ table.insert(camera_triggers, cage3ft)
	
	for i = 1,level.cage.height-1 do
		cage1ft = bf:new_imaginary_block(Vector3f(level.size,8,level.size))
		cage1ft:move(Vector3f(lx-level.size,0,(starty + i)*level.size))
		--cage1ft:change_dir(Vector3f(0,90,0))
		--cage1ft:toggle_debug()
		ct = {}
		ct.light_count = 0
		ct.block = cage1ft
		table.insert(camera_triggers, ct)
	end
	
	-- west
	cage4 = bf:new_flat_block("bricks.bmp",Vector2f(wy,8),false)
	cage4:move(Vector3f(ux,0,uy))
	cage4:set_tex_size(Vector2f(1,5))
	cage4:rotate(Vector3f(0,90,0))
	cage4ff = bf:new_imaginary_block(Vector3f(wy,8,1))
	cage4ff:move(Vector3f(ux-1,0,uy))
	cage4ff:change_dir(Vector3f(0,90,0))
	--cage4ff:toggle_debug()
	table.insert(scenery, cage4ff)
	--~ cage4ft = bf:new_imaginary_block(Vector3f(wx+level.size*2,8,level.size))
	--~ cage4ft:move(Vector3f(ux,0,uy+level.size))
	--~ cage4ft:change_dir(Vector3f(0,90,0))
	--~ --cage4ft:toggle_debug()
	--~ table.insert(camera_triggers, cage4ft)
	
	for i = 1,level.cage.height-1 do
		cage1ft = bf:new_imaginary_block(Vector3f(level.size,8,level.size))
		cage1ft:move(Vector3f(ux,0,(starty + i)*level.size))
		--cage1ft:change_dir(Vector3f(0,90,0))
		--cage1ft:toggle_debug()
		ct = {}
		ct.light_count = 0
		ct.block = cage1ft
		table.insert(camera_triggers, ct)
	end

end

