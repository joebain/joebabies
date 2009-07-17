
w = nil
b = nil

function start (world)

	w = world
	
	b = w:new_block("block.obj","red_block.bmp")
	
	v = Vector3f(-1.2,0,-5)
	
	b:move(v)

end

function step (amount)
	
	v = Vector3f(-1,0,0)
	
	b:rotate(v)
	
end
