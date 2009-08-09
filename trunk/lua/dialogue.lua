
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
		else
			put_lines()
		end
	end
end

function put_dialogue(text,character)
	
	if dialogue.text_up == false and dialogue.trigger == false and dialogue.big_trigger == false then
	
		dialogue.trigger_counter = 0.5
		dialogue.trigger = true
		dialogue.big_trigger = true
	
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
		dialogue.character = bf:new_blockHUD(v,character .. "_hud.bmp")
		
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
	if (dialogue.trigger == false) then
		remove_text()
		dialogue.trigger = true
		dialogue.trigger_counter = 0.5
	end
end
