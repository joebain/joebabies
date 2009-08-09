
w = nil
display = nil
bf = nil
bs = nil
c = nil
high_cam_obj = nil

internets = {}

functions = {}
character = {}
scenery = {}
level = {}
animals = {}
camera_triggers = {}
character = {}
particles = {}

dofile "lua/dialogue.lua"
dofile "lua/movement.lua"
dofile "lua/level_util.lua"
dofile "lua/level_control.lua"
dofile "lua/particles.lua"
dofile "lua/animal_control.lua"
dofile "lua/worldgen.lua"

dofile "lua/intro.lua"
dofile "lua/level1.lua"

function start (world)

    math.randomseed( os.time() )

	w = world
	
	bf = w:get_block_factory()
	bs = w:get_buttons()
	
	display = w:get_display()
	c = display:get_camera()
	
	s = bf:new_sky("grass-pixel.bmp")
	s:set_scale(300)

	
	f = bf:new_floor("misc/intro_hmap.csv","grass-pixel.bmp",5)

	
	functions.load = intro_setup
	functions.step = intro_step
	functions.right = move_right
	functions.left = move_left
	functions.up = move_up
	functions.down = move_down
	functions.space = cycle_text
	functions.a_key = gotolevel1

    w.facts = read_facts("facts_gorilla")

    w.music = w:new_audio_file("music",true)
	w.music:play_loop(-1)
    
    w.audio = {}
    w.audio.boxsmash1 = w:new_audio_file("quitegood-boxsmash",false)
    w.audio.boxsmash2 = w:new_audio_file("othergood-boxsmash",false)
    w.audio.puzzleget = w:new_audio_file("puzzlepiece",false)
    w.audio.turtleget = w:new_audio_file("turtleget",false)
    w.audio.wolfwhistle = w:new_audio_file("wolf_whistle",false)
	--gotolevel1 ()
	
	functions.load()
	
end

function restart()
	bf:clear_all()
	
	high_cam_obj = nil

	character = {}
	scenery = {}
	level = {}
	animals = {}
	camera_triggers = {}
	character = {}
	internets = {}
	
	functions.load()
end

function step (delta)
	
	functions.step(delta)
	--~ 
	if (bs.up) then functions.up(delta) end
	if (bs.down) then functions.down(delta) end
	if (bs.left) then functions.left(delta) end
	if (bs.right) then functions.right(delta) end
	if (bs.space) then functions.space(delta) end
	if (bs.a) then functions.a_key(delta) end
	if (bs.s) then functions.s_key(delta) end
	if (bs.d) then functions.d_key(delta) end
	if (bs.w) then functions.w_key(delta) end
	
end

function gotolevel1 (delta)
	functions.load = level1_setup
	functions.step = level1_step
	--functions.right = nil
	--functions.left = nil
	--functions.up = nil
	--functions.down = nil
	functions.space = call_animal
	functions.a_key = send_west
	functions.d_key = send_east
	functions.s_key = send_south
	functions.w_key = send_north
	
	restart()
end
