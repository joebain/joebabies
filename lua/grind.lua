
w = nil
display = nil
bf = nil
bs = nil
c = nil

functions = {}
character = {}
scenery = {}

require "lua/dialogue"
require "lua/movement"
require "lua/intro"

function start (world)

	w = world
	bf = w:get_block_factory()
	bs = w:get_buttons()
		
	display = w:get_display()
	c = display:get_camera()
	
	functions.load = intro_setup
	functions.step = intro_step
	functions.right = move_right
	functions.left = move_left
	functions.up = move_up
	functions.down = move_down
	functions.space = remove_text
	
	functions.load()
end

function step (delta)
	
	functions.step(delta)
	
	if (bs.up) then functions.up(delta) end
	if (bs.down) then functions.down(delta) end
	if (bs.left) then functions.left(delta) end
	if (bs.right) then functions.right(delta) end
	if (bs.space) then functions.space(delta) end
	if (bs.a) then functions.a_key(delta) end
	if (bs.s) then functions.s_key(delta) end
	
end

function right (delta)
	--move_right (delta)
end

function left (delta)
	--move_left (delta)
end

function up (delta)
	--move_up (delta)
end

function down (delta)
	--move_down (delta)
end

function space (delta)
	--remove_text()
end

function a_key(delta)
	
end

function s_key(delta)
	
end
