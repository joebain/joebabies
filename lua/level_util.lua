function do_border_fences ()

	--lower x
	fence1 = bf:new_flat_block("fence.bmp",Vector2f(level.width+2,2),true)
	fence1:move(Vector3f(level.off_x-1,0,level.off_y-1))
	fence1:set_tex_size(Vector2f(-0.9,20))
	--lower z
	fence2 = bf:new_flat_block("fence.bmp",Vector2f(level.height+2,2),true)
	fence2:move(Vector3f(level.off_x -1,0,level.height + level.off_y +1))
	fence2:set_tex_size(Vector2f(1,20))
	fence2:rotate(Vector3f(0,90,0))
	--upper x
	fence3 = bf:new_flat_block("fence.bmp",Vector2f(level.width+2,2),true)
	fence3:move(Vector3f(level.off_x + level.width +1,0,level.off_y + level.height+1))
	fence3:set_tex_size(Vector2f(1,20))
	fence3:rotate(Vector3f(0,90,0))
	--upper z
	fence4 = bf:new_flat_block("fence.bmp",Vector2f(level.height+2,2),true)
	fence4:move(Vector3f(level.off_x-1,0,level.off_y  +level.height+1))
	fence4:set_tex_size(Vector2f(1,20))

end

function do_mountains ()

	--lower x
	mountains1 = bf:new_distance_block("bg_mountains.bmp",Vector2f(400,30))
	mountains1:move(Vector3f(-90,-10,-90))
	mountains1:set_tex_size(Vector2f(1,4))
	--lower z
	mountains2 = bf:new_distance_block("bg_trees.bmp",Vector2f(400,30))
	mountains2:move(Vector3f(-90,-10,-90))
	mountains2:rotate(Vector3f(0,-90,0))
	mountains2:set_tex_size(Vector2f(1,4))
	--upper x
	mountains3 = bf:new_distance_block("bg_trees.bmp",Vector2f(400,30))
	mountains3:move(Vector3f(290,-10,290))
	mountains3:rotate(Vector3f(0,90,0))
	mountains3:set_tex_size(Vector2f(1,4))
	--upper z
	mountains4 = bf:new_distance_block("bg_trees.bmp",Vector2f(400,30))
	mountains4:move(Vector3f(-90,-10,290))
	mountains4:set_tex_size(Vector2f(1,4))

end


function act_to_grid(x,y)

	--x = ((level.cage.width - x) + level.off_x + level.cage.x)*level.size
	--y = (y + level.off_y + level.cage.y)*level.size
	
	x = level.off_x + level.cage.x + level.cage.width - math.floor(x/level.size + 0.5)
	y = math.floor(y/level.size + 0.5) - (level.off_y + level.cage.y)

	return x,y

end

function grid_to_act(x,y)

	x = ((level.cage.width - x) + level.off_x + level.cage.x)*level.size
	y = (y + level.off_y + level.cage.y)*level.size

	return x,y

end
