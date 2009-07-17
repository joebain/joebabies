#!/usr/bin/lua5.1

--require("babies")
--require("run.lua")

function step (amount)
	v = babies.Vector3f(0,0,-0,1)

	b1:rotate(v)
	b2:rotate(v)
end
