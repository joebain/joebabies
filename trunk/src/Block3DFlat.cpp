#include "Block3DFlat.h"

#ifdef WIN32
#include <windows.h>
#endif
#include <iostream>
#include <string>
#include <algorithm>

#include "Vector2f.h"
#include "Texture.h"

Block3DFlat::Block3DFlat()
{
	is_driven = false;
	
	is_2d = false;
	
	shown = MASKED;
	
	tex_coords[0][0] = 0;
	tex_coords[0][1] = 0;
	tex_coords[1][0] = 0;
	tex_coords[1][1] = 1;
	tex_coords[2][0] = 1;
	tex_coords[2][1] = 1;
	tex_coords[3][0] = 1;
	tex_coords[3][1] = 0;
}

Block3DFlat::~Block3DFlat()
{
}

Block3DFlat::Block3DFlat(const Block3DFlat& b)
{
	shown = b.shown;
	pos = b.pos;
	size = b.size;
	rot = b.rot;
	texture = b.texture;
	is_driven = b.is_driven;
	is_2d = b.is_2d;
	
	for (int i = 0; i < 4 ; i++) {
		tex_coords[i][0] = b.tex_coords[i][0];
		tex_coords[i][1] = b.tex_coords[i][1];
	}
}

bool Block3DFlat::operator==(const Block3DFlat& b)
{
	if (pos == b.pos && size == b.size && texture == b.texture)
		return true;
	else
		return false;
}

void Block3DFlat::move(Vector3f move)
{
	Vector3f move_tmp(move);
	if (is_driven) {
		move_tmp.rotate(-rot);	
	}
	pos.x += move.x;
	pos.y += move.y;
	pos.z += move.z;
}

void Block3DFlat::rotate(Vector3f plus_rot)
{
	rot += plus_rot;
}

void Block3DFlat::set_pos(Vector3f pos)
{
	this->pos = pos;
}

void Block3DFlat::set_size(Vector2f size)
{
	this->size = size;
}

void Block3DFlat::scale(Vector2f s)
{
	this->size *= s;
}

void Block3DFlat::scale(float s)
{
	this->size *= s;
}

void Block3DFlat::set_transparency(float t)
{
	transparency = t;
	if (t == 0.0)
		shown = NEITHER;
	else
		shown = TRANSP;
}

void Block3DFlat::display()
{
	glPushMatrix();
	
	glTranslatef(pos.x, pos.y, pos.z);
		
	glRotatef(rot.z,0,0,1);
	glRotatef(rot.y,0,1,0);
	glRotatef(rot.x,1,0,0);
	
	//grab the z pos
	if (shown != NEITHER) {
		float new_t[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, new_t);
		
		//Vector3f np;
		//np.init(new_t[12],new_t[13],new_t[14]);
		
		float z_depth1 = new_t[14];
		
		glPushMatrix();
		
		glTranslatef(size.x, size.y, 0);
		glGetFloatv(GL_MODELVIEW_MATRIX, new_t);
		
		float z_depth2 = new_t[14];
		
		glPopMatrix();
		
		z_depth += (min(z_depth1,z_depth2));
	}
	
	if (shown == MASKED) {
		
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		if (!is_2d) glDisable(GL_LIGHTING);
		
		glBlendFunc(GL_DST_COLOR,GL_ZERO);
		
		//first the mask
		glBindTexture(GL_TEXTURE_2D, texture->get_mask_num());
		
		glBegin(GL_QUADS);
			
		glTexCoord2f(tex_coords[0][0],tex_coords[0][1]);
		glNormal3f(0,0,1);
		glVertex3f(0,0,0);

		glTexCoord2f(tex_coords[1][0],tex_coords[1][1]);
		glNormal3f(0,0,1);
		glVertex3f(0,size.y,0);
		
		glTexCoord2f(tex_coords[2][0],tex_coords[2][1]);
		glNormal3f(0,0,1);
		glVertex3f(size.x,size.y,0);
		
		glTexCoord2f(tex_coords[3][0],tex_coords[3][1]);
		glNormal3f(0,0,1);
		glVertex3f(size.x,0,0);

		glEnd();
		
		glBlendFunc(GL_ONE, GL_ONE);
		if (!is_2d)	glEnable(GL_LIGHTING);
		
	} else if (shown == TRANSP) {
		
		//glDepthMask(GL_FALSE);
		glEnable (GL_BLEND);
		glColor4f(1.0,1.0,1.0,transparency);
		glBlendFunc (GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
		
		//glBlendFunc(GL_DST_COLOR,GL_ONE_MINUS_DST_ALPHA);
	}
	
	glBindTexture(GL_TEXTURE_2D, texture->get_tex_num());
	
	glBegin(GL_QUADS);
		
	glTexCoord2f(tex_coords[0][0],tex_coords[0][1]);
	glNormal3f(0,0,1);
	glVertex3f(0,0,0);

	glTexCoord2f(tex_coords[1][0],tex_coords[1][1]);
	glNormal3f(0,0,1);
	glVertex3f(0,size.y,0);
	
	glTexCoord2f(tex_coords[2][0],tex_coords[2][1]);
	glNormal3f(0,0,1);
	glVertex3f(size.x,size.y,0);
	
	glTexCoord2f(tex_coords[3][0],tex_coords[3][1]);
	glNormal3f(0,0,1);
	glVertex3f(size.x,0,0);

	glEnd();
	
	if (shown == MASKED) {
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	} else if (shown == TRANSP) {
		glDisable(GL_BLEND);
	}
	
	glPopMatrix();
}

void Block3DFlat::set_mask(bool t)
{
	if (t)
		shown = MASKED;
	else
		shown = NEITHER;
}

Vector3f Block3DFlat::get_pos()
{
	return pos;
}

Vector3f Block3DFlat::get_rot()
{
	return rot;
}

void Block3DFlat::set_tex(Texture *texture)
{
	if (shown == MASKED) texture->make_mask();
	this->texture = texture;
}

void Block3DFlat::set_driven()
{
	is_driven = true;
}

void Block3DFlat::set_tex_size(Vector2f s)
{
	
	tex_coords[0][0] = 0;
	tex_coords[0][1] = 0;
	tex_coords[1][0] = 0;
	tex_coords[1][1] = s.x;
	tex_coords[2][0] = s.y;
	tex_coords[2][1] = s.x;
	tex_coords[3][0] = s.y;
	tex_coords[3][1] = 0;
	
}
