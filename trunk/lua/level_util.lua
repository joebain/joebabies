function do_border_fences ()

	--lower x
	fence1 = bf:new_flat_block("fence.bmp",Vector2f(level.width*level.size+2,2),true)
	fence1:move(Vector3f(level.off_x*level.size-1,0,level.off_y*level.size-1))
	fence1:set_tex_size(Vector2f(1,20))
	--lower z
	fence2 = bf:new_flat_block("fence.bmp",Vector2f(level.height*level.size+2,2),true)
	fence2:move(Vector3f(level.off_x*level.size -1,0,(level.height + level.off_y)*level.size +1))
	fence2:set_tex_size(Vector2f(1,20))
	fence2:rotate(Vector3f(0,90,0))
	--upper x
	fence3 = bf:new_flat_block("fence.bmp",Vector2f(level.width*level.size+2,2),true)
	fence3:move(Vector3f((level.off_x + level.width)*level.size +1,0,(level.off_y + level.height)*level.size+1))
	fence3:set_tex_size(Vector2f(1,20))
	fence3:rotate(Vector3f(0,90,0))
	--upper z
	fence4 = bf:new_flat_block("fence.bmp",Vector2f(level.height*level.size+2,2),true)
	fence4:move(Vector3f(level.off_x*level.size-1,0,(level.off_y  +level.height)*level.size+1))
	fence4:set_tex_size(Vector2f(1,20))

end

function do_mountains ()

	size = f:get_size()
	--xsize = 
	--lower x
	mountains1 = bf:new_distance_block("bg_mountains.bmp",Vector2f(((size.y -1) * level.size),((size.y -1) * level.size)))
	mountains1:move(Vector3f(0,0,0))
	mountains1:set_tex_size(Vector2f(1,1))
	--lower z
	mountains2 = bf:new_distance_block("bg_mountains2.bmp",Vector2f(((size.x -1) * level.size),((size.x -1) * level.size)))
	mountains2:move(Vector3f(0,0,0))
	mountains2:rotate(Vector3f(0,-90,0))
	mountains2:set_tex_size(Vector2f(1,1))
	--upper x
	mountains3 = bf:new_distance_block("bg_mountains2.bmp",Vector2f(((size.x -1) * level.size),((size.x -1) * level.size)))
	mountains3:move(Vector3f((size.y -1) * level.size,0,(size.x -1) * level.size))
	mountains3:rotate(Vector3f(0,90,0))
	mountains3:set_tex_size(Vector2f(1,1))
	--upper z
	mountains4 = bf:new_distance_block("bg_trees.bmp",Vector2f(((size.y -1) * level.size),((size.y -1) * level.size)))
	mountains4:move(Vector3f(0,0,(size.x -1) * level.size))
	mountains4:set_tex_size(Vector2f(1,1))

end


function act_to_grid(x,y)

	x = level.off_x + level.cage.x + level.cage.width - math.floor((x-0.5)/level.size)
	y = math.floor((y-0.5)/level.size) - (level.off_y + level.cage.y)

	return x,y

end

function grid_to_act(x,y)

	x = ((level.cage.width - x) + level.off_x + level.cage.x + 0.5)*level.size
	y = (y + level.off_y + level.cage.y + 0.5)*level.size

	return x,y

end

function in_cage(x,y)
	return x <= level.cage.width and x > 0 and y <= level.cage.height and y > 0
end

function read_facts(file)
  facts = {}
  local i = 1
  for line in io.lines("misc/"..file..".txt") do
    facts[i] = line
    i = i + 1
  end
  return facts
end
