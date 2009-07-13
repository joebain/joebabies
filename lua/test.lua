#!/usr/bin/lua5.1

require("babies")

babies.start()

w = babies.get_world()

b1 = w:new_block("block.obj", "red_block.bmp")
v1 = babies.Vector3f(1.2,0,-5)
b1:move(v1)

b2 = w:new_block("block.obj", "blue_block.bmp")
v2 = babies.Vector3f(-1.2,0,-5)
b2:move(v2)
