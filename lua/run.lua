#!/usr/bin/lua5.1

require("babies")

babies.start()

w = babies.get_world()

--os.execute("sleep 1")

--[[
	//this fucking works!
	Block* b = w->new_block("block.obj","red_block.bmp");
	Vector3f *v = new Vector3f(1.2,0,-5);
	b->move(*v);
	
	Block* b2 = w->new_block("block.obj","blue_block.bmp");
	Vector3f *v2 = new Vector3f(-1.2,0,-5);
	b2->move(*v2);
--]]

b1 = w:new_block("block.obj", "red_block.bmp")
v1 = babies.Vector3f(1.2,0,-5)
b1:move(v1)

b2 = w:new_block("block.obj", "blue_block.bmp")
v2 = babies.Vector3f(-1.2,0,-5)
b2:move(v2)

--d = w:get_display()

--v.z = 5

--d:translate(v)

while true do
os.execute("sleep 1")
end
