#include "Block2DText.h"

#include <GL/glut.h>

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
	glColor3f(1.0,1.0,1.0);
	
	glRasterPos2f(pos.x, pos.y);
	int i;
	for (i=0; i<text.length(); i++) {
    	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int) text[i]);
	}
}
