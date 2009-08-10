
dialogue = {}
dialogue.text_up = false
dialogue.text = {}
dialogue.line_length = 0
dialogue.blocks = {}
dialogue.lines_removed = 0
dialogue.lines_shown = 0
dialogue.trigger_counter = 0
dialogue.trigger = false
dialogue.big_trigger = false


menu = {}

function remove_text ()
	if (dialogue.text_up == true) then
		len = math.min(dialogue.lines_removed + 5,dialogue.lines_shown)
		--print("removing lines from " .. dialogue.lines_removed+1 .. " to " .. len)
		for i = dialogue.lines_removed+1,len do
			--print("line " .. i .. ": " .. dialogue.text[i])
			bf:remove_blockText(dialogue.blocks[i])
			dialogue.blocks[i] = nil
		end
		dialogue.lines_removed = len
		--print("lines shown is " .. dialogue.lines_shown .. ", removed " .. dialogue.lines_removed)
		--print("lines total is " .. #dialogue.text)
		if (dialogue.lines_removed == #dialogue.text) then
			dialogue.blocks = {}
			bf:remove_blockHUD(dialogue.backing)
			bf:remove_blockHUD(dialogue.character)
			dialogue.backing = nil
			dialogue.character = nil
			dialogue.text_up = false
			dialogue.text = {}
			dialogue.lines_removed = 0
			dialogue.lines_shown = 0
			dialogue.trigger_counter = 0
			dialogue.trigger = false
			
			dialogue.big_trigger = false
			
			functions.up = dialogue.old_up
			functions.down = dialogue.old_down
			functions.space = dialogue.old_space
			
			dialogue.cb_func()
		else
			put_lines()
		end
	end
end

function put_dialogue(text,character,cb_func)
	
	if dialogue.text_up == false and dialogue.trigger == false and dialogue.big_trigger == false then
	
		dialogue.old_up = functions.up
		functions.up = nil
		dialogue.old_down = functions.down
		functions.down = nil
		dialogue.old_space = functions.space
		functions.space = cycle_text
		dialogue.cb_func = cb_func
		dialogue.trigger_counter = 0.5
		dialogue.trigger = true
		dialogue.big_trigger = true
		dialogue.time_start = os.time()
	
		--print("putting up text")
	
		sound:play()
		
		dialogue.text_size = Vector2f(20,20)
		
		dialogue.line_length = ((display:get_width()-250)/dialogue.text_size.x)-4
		
		split_lines(text)
		
		height = math.min(#dialogue.text,5)
		
		backing_size = Vector2f((dialogue.line_length+7)*dialogue.text_size.x,(height+3)*dialogue.text_size.y*1.2)
		
		backing_pos = Vector2f((display:get_width()/2) - (backing_size.x/2) + 50,120)
		
		dialogue.backing = bf:new_blockHUD(backing_size,"dialogue.bmp")
		dialogue.backing:move(backing_pos)
		
		dialogue.text_pos = Vector2f(backing_pos.x + dialogue.text_size.x*3,(backing_pos.y + backing_size.y) - dialogue.text_size.y*3)
		
		v = Vector2f(300,300)
		dialogue.character = bf:new_blockHUD(v,character .. "-big.bmp")
		
		dialogue.text_up = true
		
		put_lines()
	end
end

function put_lines()

	text_pos = Vector2f(dialogue.text_pos.x,dialogue.text_pos.y)
	--print("text pos is " .. text_pos.x .. "," .. text_pos.y)
	--print("text size is " .. dialogue.text_size.x .. "," .. dialogue.text_size.y)
	
	len = math.min(dialogue.lines_shown+5,#dialogue.text)
	for i = dialogue.lines_shown+1,len do
		--print ("is is " .. i)
		--print ("adding line " .. dialogue.text[i])
		dialogue.blocks[i] = bf:new_blockText(text_pos,dialogue.text_size,dialogue.text[i],"font_wbg.bmp")
		text_pos.y = text_pos.y - dialogue.text_size.y*1.2
	end

	dialogue.lines_shown = len

end

function split_lines(text)
	
	close_index = 1
	far_index = dialogue.line_length + 1
	repeat
		
		a_line = text:sub(close_index,far_index)
	
		
		if (a_line:sub(1,1) == " ") then
			close_index = close_index + 1
			far_index = far_index + 1
			a_line = text:sub(close_index,far_index)
	
		end
		line_end = 0
		if (#a_line > dialogue.line_length) then
			b_line = a_line:reverse()
			line_end = b_line:find(" ")
	
			
			a_line = a_line:sub(0,-(line_end+1))
		end
		
		far_index = close_index + #a_line + dialogue.line_length + 1
		close_index = close_index + #a_line
		
		if (far_index > #text) then
			far_index = #text
		end
		
		table.insert(dialogue.text,a_line)
		
		--print("added line at " .. #dialogue.text)
		--print(a_line)
		
		
	until close_index >= #text

end

function update_dialogue(delta)
	if (dialogue.trigger_counter > 0) then
		dialogue.trigger_counter = dialogue.trigger_counter - delta
	else
		dialogue.trigger_counter = 0
		dialogue.trigger = false
	end
end

function cycle_text ()
	if (os.time() - dialogue.time_start) > 0 then
		remove_text()
		dialogue.time_start = os.time()
	end
end

function put_menu(question,choices,character)

	menu.last_time = os.time()

	menu.text_size = Vector2f(20,20)
	
	menu.choices = choices
	
	menu.height = menu.text_size.y * (#menu.choices+5) * 1.3
	menu.width = display:get_width()-200
		
	menu.text_pos = Vector2f((display:get_width()/2 - menu.width/2) + 120, menu.height-20)
	
	backing_size = Vector2f(menu.width*1.1,menu.height*1.1)
	menu.backing = bf:new_blockHUD(backing_size,"dialogue.bmp")
	v = Vector2f((display:get_width()/2 - menu.width/2) + 30, 80)
	menu.backing:move(v)

	v = Vector2f(300,300)
	menu.character = bf:new_blockHUD(v,character .. "-big.bmp")	
	
	menu.selector = bf:new_blockHUD(Vector2f(menu.width-100,menu.text_size.y),"outline-red.bmp")
	
	pos = Vector2f((display:get_width()/2 - menu.width/2) + 80,menu.height+20)
	menu.question = bf:new_blockText(pos,Vector2f(20,20),question,"font_wbg.bmp")
	
	pos = Vector2f(menu.text_pos.x,menu.text_pos.y)
	for i = 1,#menu.choices do
		menu.choices[i].block = bf:new_blockText(pos,menu.text_size,menu.choices[i].text,"font_wbg.bmp")
		pos.y = pos.y - menu.text_size.y*1.3
	end
	
	menu.selected = 0
	
	update_menu()
	
	menu.old_up = functions.up
	menu.old_down = functions.down
	menu.old_space = functions.space 
	
	functions.up = menu_up
	functions.down = menu_down
	functions.space = menu_select
	
end

function update_menu()
	--print(menu.selected .. " is selected")
	menu.selector:set_pos(menu.choices[menu.selected+1].block:get_pos())
	menu.last_time = os.time()
end

function menu_up()
	if (os.time()-menu.last_time) > 0 then
		menu.selected = menu.selected - 1
		menu.selected = menu.selected%(#menu.choices)
		update_menu()
	end
end

function menu_down()
	if (os.time()-menu.last_time) > 0 then
		menu.selected = menu.selected + 1
		menu.selected = menu.selected%(#menu.choices)
		update_menu()
	end
end

function menu_select()
	if (os.time()-menu.last_time) > 0 then
		menu.choices[menu.selected+1].cb_func()
		
		for i = 1,#menu.choices do
			bf:remove_blockText(menu.choices[i].block)
		end
		
		bf:remove_blockText(menu.question)
		bf:remove_blockHUD(menu.selector)
		bf:remove_blockHUD(menu.character)
		bf:remove_blockHUD(menu.backing)
		
		functions.up = menu.old_up
		functions.down = menu.old_down
		functions.space = menu.old_space
	end
end
