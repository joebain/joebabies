
display_list = {}

function display_list_push(thing)

	functions.space = thing.space
	functions.up = thing.up
	functions.down = thing.down
	
	table.insert(display_list,thing)
	--print(#display_list .. " items in display list")

end

function display_list_pop()
	--remove this dialogue from the display list
	table.remove(display_list,#display_list)
	--print(#display_list .. " items in display list")
	
	--nothing on display list, return control
	if (#display_list == 0) then
		functions.up = move_up
		functions.down = move_down
		functions.space = nil
	else
	--pass control back to last item
		functions.up = display_list[#display_list].up
		functions.down = display_list[#display_list].down
		functions.space = display_list[#display_list].space
	end
end

dialogue = {}

menu = {}

function new_dialogue()
	local dialogue = {}
	
	dialogue.text_up = false --is text being shown
	dialogue.text = {} -- an array of the lines of dialogue
	dialogue.line_length = 0 --max length of each line
	dialogue.blocks = {} -- the block objects stored for later removal
	dialogue.lines_removed = 0 --how many lines have been shown and also removed
	dialogue.lines_shown = 0 -- how many lines have been shown
	dialogue.trigger_counter = 0 --checks that enough time has passed before a page is turned
	dialogue.trigger = false --flag to allow a page turn
	
	--this updates or removes the text being shown and returns control at the end
	dialogue.remove_text = function ()
		--if there is dialogue being shown
		if (dialogue.text_up == true) then
			--len is the start of the next set of dialogue to be shown (may not be a multiple of 5)
			len = math.min(dialogue.lines_removed + 5,dialogue.lines_shown)
			--remov old lines
			for i = dialogue.lines_removed+1,len do
				bf:remove_blockText(dialogue.blocks[i])
				dialogue.blocks[i] = nil
			end
			dialogue.lines_removed = len
			
			if (dialogue.lines_removed == #dialogue.text) then
			--if we have removed all the lines
				bf:remove_blockHUD(dialogue.backing)
				bf:remove_blockHUD(dialogue.character)
				
				--what?
				--init_dialogue()
				
				display_list_pop()
				
				--call the call back function if there is one
				if (dialogue.cb_func ~= nil) then 
					dialogue.cb_func()
				end
				
			else
			--otherwise put more lines
				dialogue.put_lines()
			end
		end
	end
	
	dialogue.put = function (text,character,cb_func)
	
		dialogue.cb_func = cb_func
		dialogue.trigger_counter = 0.5
		dialogue.trigger = true
		dialogue.time_start = w:get_timer():get_time()
		
		dialogue.text_size = Vector2f(20,20)
		
		dialogue.line_length = ((display:get_width()-250)/dialogue.text_size.x)-4
		
		dialogue.split_lines(text)
		
		height = math.min(#dialogue.text,5)
		
		backing_size = Vector2f((dialogue.line_length+7)*dialogue.text_size.x,(height+3)*dialogue.text_size.y*1.2)
		
		backing_pos = Vector2f((display:get_width()/2) - (backing_size.x/2) + 50,120)
		
		dialogue.backing = bf:new_blockHUD(backing_size,"dialogue.bmp")
		dialogue.backing:move(backing_pos)
		
		dialogue.text_pos = Vector2f(backing_pos.x + dialogue.text_size.x*3,(backing_pos.y + backing_size.y) - dialogue.text_size.y*3)
		
		v = Vector2f(300,300)
		dialogue.character = bf:new_blockHUD(v,character .. "-big.bmp")
		
		dialogue.text_up = true
		
		dialogue.put_lines()
		
		display_list_push(dialogue)
		
	end
	

	dialogue.put_lines = function()

		text_pos = Vector2f(dialogue.text_pos.x,dialogue.text_pos.y)
		
		len = math.min(dialogue.lines_shown+5,#dialogue.text)
		for i = dialogue.lines_shown+1,len do
			dialogue.blocks[i] = bf:new_blockText(text_pos,dialogue.text_size,dialogue.text[i],"font_wbg.bmp")
			text_pos.y = text_pos.y - dialogue.text_size.y*1.2
		end

		dialogue.lines_shown = len

	end

	dialogue.split_lines = function (text)
	
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
			
		until close_index >= #text

	end

	--this is what the user requests (ie a button press triggers it) it will check enough time
	--has passed then update the text to the next line or remove the dialogue box completely
	dialogue.cycle_text = function()
		if w:get_timer():time_since(dialogue.time_start) > 0.5 then
			dialogue.remove_text()
			dialogue.time_start = w:get_timer():get_time()
		end
	end

	--key press functions
	dialogue.up = nil
	dialogue.down = nil
	dialogue.space = dialogue.cycle_text 

	return dialogue

end




function new_menu()

	menu = {}

	--put up a menu, choices should be a table with each of the elements having fields 'text' and 'cb_func'
	--where text is the text to display and 'cb_func' is the name of the function to be called if that option
	--is selected
	menu.put = function(question,choices,character)

		menu.last_time = w:get_timer():get_time()

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
		
		menu.selector = bf:new_blockHUD(Vector2f(menu.width-100,menu.text_size.y),"outline-dialogue.bmp")
		
		pos = Vector2f((display:get_width()/2 - menu.width/2) + 80,menu.height+20)
		menu.question = bf:new_blockText(pos,Vector2f(20,20),question,"font_wbg.bmp")
		
		pos = Vector2f(menu.text_pos.x,menu.text_pos.y)
		for i = 1,#menu.choices do
			menu.choices[i].block = bf:new_blockText(pos,menu.text_size,menu.choices[i].text,"font_wbg.bmp")
			pos.y = pos.y - menu.text_size.y*1.3
		end
		
		menu.selected = 0
		
		menu.update()
		
		display_list_push(menu)
	end

	menu.update = function()
		menu.selector:set_pos(menu.choices[menu.selected+1].block:get_pos())
		menu.last_time = w:get_timer():get_time()
	end

	menu.menu_up = function()
		if w:get_timer():time_since(menu.last_time) > 0.5 then
			menu.selected = menu.selected - 1
			menu.selected = menu.selected%(#menu.choices)
			menu.update()
		end
	end

	menu.menu_down = function()
		if w:get_timer():time_since(menu.last_time) > 0.5 then
			menu.selected = menu.selected + 1
			menu.selected = menu.selected%(#menu.choices)
			menu.update()
		end
	end

	menu.select = function()
		if w:get_timer():time_since(menu.last_time) > 0.5 then		
			
			--remove graphics
			for i = 1,#menu.choices do
				bf:remove_blockText(menu.choices[i].block)
			end
			
			bf:remove_blockText(menu.question)
			bf:remove_blockHUD(menu.selector)
			bf:remove_blockHUD(menu.character)
			bf:remove_blockHUD(menu.backing)
			
			display_list_pop()
			
			--call the relavent function for the selected choice
			if (menu.choices[menu.selected+1].cb_func ~= nil) then
				menu.choices[menu.selected+1].cb_func()
			end
		end
	end
	
	menu.up = menu.menu_up
	menu.down = menu.menu_down
	menu.space = menu.select
	
	return menu

end
