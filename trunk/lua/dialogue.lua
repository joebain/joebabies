
dialogue = {}
dialogue.text_up = false
dialogue.text = {}

function remove_text ()
	if (dialogue.text_up == true) then
		for i,line in pairs(dialogue.text) do
			bf:remove_blockText(line)
		end
		dialogue.text = {}
		bf:remove_blockHUD(dialogue.backing)
		dialogue.backing = nil
		
		dialogue.text_up = false
	end
end

function put_dialogue(text,character)
	
	sound:play()
	
	length = text:len()
	
	text_size = Vector2f(20,20)
	
	line_length = ((display:get_width()-250)/text_size.x)-4
	
	height = math.ceil(length/line_length)
	length = line_length
		
	backing_size = Vector2f((length+5)*text_size.x,(height+3)*text_size.y*1.2)
	
	backing_pos = Vector2f((display:get_width()/2) - (backing_size.x/2) + 50,120)
	
	dialogue.backing = bf:new_blockHUD(backing_size,"dialogue.bmp")
	dialogue.backing:move(backing_pos)
	
	text_pos = Vector2f(backing_pos.x + text_size.x*3,(backing_pos.y + backing_size.y) - text_size.y*3)
	
	for i = 1,height do
		line = text:sub(length*(i-1)+1,length*i)
		if (line:sub(1,1) == " ") then
			line = line:sub(2)
		end
		dialogue.text[i] = bf:new_blockText(text_pos,text_size,line,"font_wbg.bmp")
		text_pos.y = text_pos.y - text_size.y*1.2
	end
	
	--v = Vector2f(200,100)
	--hud = bf:new_blockHUD(v,character .. "_hud.bmp")
	
	dialogue.text_up = true
	
end
