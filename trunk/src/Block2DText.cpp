#include "Block2DText.h"

#include <math.h>

void Block2DText::set_text(string text)
{
	this->text = text;
}

string Block2DText::get_text()
{
	return text;
}

void Block2DText::display()
{
	glPushMatrix();
	
	glTranslatef(pos.x, pos.y, pos.z);
		
	glRotatef(rot.z,0,0,1);
	
	if (shown == MASKED) {
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		
		glBlendFunc(GL_DST_COLOR,GL_ZERO);
		
		//first the mask
		glBindTexture(GL_TEXTURE_2D, texture->get_mask_num());
		
		glBegin(GL_QUADS);
		
		Vector2f offset;
		for (string::iterator it=text.begin() ; it < text.end(); it++ ) {
			
			Vector2f tc = get_tcs(*it);
			
			glTexCoord2f(tc.x, tc.y);
			glNormal3f(0,0,1);
			glVertex3f(offset.x,offset.y,0);

			glTexCoord2f(tc.x, tc.y + C_SPACE);
			glNormal3f(0,0,1);
			glVertex3f(offset.x,size.y + offset.y,0);
			
			glTexCoord2f(tc.x + C_SPACE, tc.y + C_SPACE);
			glNormal3f(0,0,1);
			glVertex3f(size.x + offset.x,size.y + offset.y,0);
			
			glTexCoord2f(tc.x + C_SPACE, tc.y);
			glNormal3f(0,0,1);
			glVertex3f(size.x + offset.x,offset.y,0);
			
			offset.x += size.x;

		}
		
		glEnd();
		
		glBlendFunc(GL_ONE, GL_ONE);
	}
	
	glBindTexture(GL_TEXTURE_2D, texture->get_tex_num());
	
	glBegin(GL_QUADS);
		
	Vector2f offset;
	for (string::iterator it=text.begin() ; it < text.end(); it++ ) {
		
		Vector2f tc = get_tcs(*it);
		
		glTexCoord2f(tc.x, tc.y);
		glNormal3f(0,0,1);
		glVertex3f(offset.x,offset.y,0);

		glTexCoord2f(tc.x, tc.y + C_SPACE);
		glNormal3f(0,0,1);
		glVertex3f(offset.x,size.y + offset.y,0);
		
		glTexCoord2f(tc.x + C_SPACE, tc.y + C_SPACE);
		glNormal3f(0,0,1);
		glVertex3f(size.x + offset.x,size.y + offset.y,0);
		
		glTexCoord2f(tc.x + C_SPACE, tc.y);
		glNormal3f(0,0,1);
		glVertex3f(size.x + offset.x,offset.y,0);
		
		offset.x += size.x;

	}

	glEnd();
		
	if (shown == MASKED) {
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}
	
	glPopMatrix();
	
}

bool Block2DText::operator==(const Block2DText& rhs)
{
	if (pos == rhs.pos && size == rhs.size && (*texture) == (*rhs.texture) && text == rhs.text)
		return true;
	else
		return false;
}

Vector2f Block2DText::get_tcs(char c)
{
	c = toupper(c);
	
	Vector2f pos;
	
	if (c >= 65 && c <= 90) {
		pos.x = ((c-65)%7)/7.0;
		pos.y = 1.0 - ((float) floor((float)(c-65)/7)+1.0)/7.0;
	} else {
		switch (c) {
			case '!':
			pos.y = C_SPACE;
			pos.x = C_SPACE * 4.0;
			break;
			case '\'':
			pos.y = C_SPACE;
			pos.x = C_SPACE * 5.0;
			break;
			case '"':
			pos.y = C_SPACE;
			pos.x = C_SPACE * 6.0;
			break;
			case '?':
			pos.y = C_SPACE;
			pos.x = C_SPACE * 3.0;
			break;
			case '.':
			pos.y = C_SPACE;
			pos.x = C_SPACE;
			break;
			case ',':
			pos.y = C_SPACE;
			pos.x = C_SPACE * 2.0;
			break;
			case ' ':
			pos.y = 0.0;
			pos.x = 0.0;
			break;
			case '-':
			pos.y = 0.0;
			pos.x = C_SPACE;
			break;
			case '(':
			pos.y = 0.0;
			pos.x = C_SPACE * 2.0;
			break;
			case ')':
			pos.y = 0.0;
			pos.x = C_SPACE * 3.0;
			break;
			case '+':
			pos.y = 0.0;
			pos.x = C_SPACE * 4.0;
			break;
			case '$':
			pos.y = 0.0;
			pos.x = C_SPACE * 5.0;
			break;
			case '&':
			pos.y = 0.0;
			pos.x = C_SPACE * 6.0;
			break;
			default:
			pos.y = C_SPACE;
			pos.x = C_SPACE * 3.0;
		}
	}
	
	return pos;
}
