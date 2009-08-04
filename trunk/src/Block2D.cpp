#include "Block2D.h"

#ifdef WIN32
#include <windows.h>
#endif
#include <iostream>
#include <string>

#include "Vector2f.h"
#include "Texture.h"

Block2D::Block2D()
{
	pos.init(0,0,1);
	
	is_driven = false;
	
	is_masked = true;
	is_2d = true;
	
	tex_coords[0][0] = 0;
	tex_coords[0][1] = 0;
	tex_coords[1][0] = 0;
	tex_coords[1][1] = 1;
	tex_coords[2][0] = 1;
	tex_coords[2][1] = 1;
	tex_coords[3][0] = 1;
	tex_coords[3][1] = 0;
}

Block2D::~Block2D()
{
}

Block2D::Block2D(const Block2D& b)
{
	is_masked = b.is_masked;
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

bool Block2D::operator==(const Block2D& b)
{
	if (pos == b.pos && size == b.size && texture == b.texture)
		return true;
	else
		return false;
}

void Block2D::move(Vector2f move)
{
	Vector2f move_tmp(move);
	if (is_driven) {
		move_tmp.rotate(-rot.z);
	}
	pos.x += move.x;
	pos.y += move.y;
}

void Block2D::move(Vector3f move)
{
	Vector3f move_tmp(move);
	if (is_driven) {
		move_tmp.rotate(-rot);	
	}
	pos.x += move.x;
	pos.y += move.y;
	pos.z += move.z;
}

void Block2D::rotate(float plus_rot)
{
	rot.z += plus_rot;
}

void Block2D::rotate(Vector3f plus_rot)
{
	rot += plus_rot;
}

void Block2D::set_pos(Vector2f pos)
{
	this->pos.init(pos.x,pos.y,this->pos.z);
}

void Block2D::set_pos(Vector3f pos)
{
	this->pos = pos;
}

void Block2D::set_size(Vector2f size)
{
	this->size = size;
}

void Block2D::scale(Vector2f s)
{
	this->size *= s;
}

void Block2D::scale(float s)
{
	this->size *= s;
}

void Block2D::display()
{
	glPushMatrix();
	
	glTranslatef(pos.x, pos.y, pos.z);
		
	glRotatef(rot.z,0,0,1);
	glRotatef(rot.y,0,1,0);
	glRotatef(rot.x,1,0,0);
	
	if (is_masked) {
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		
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
		
	if (is_masked) {
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}
	
	glPopMatrix();
}

void Block2D::set_mask(bool t)
{
	is_masked = t;
}

Vector2f Block2D::get_pos_2d()
{
	return Vector2f(pos.x,pos.y);
}

Vector3f Block2D::get_pos()
{
	return pos;
}

float Block2D::get_rot_2d()
{
	return rot.z;
}

Vector3f Block2D::get_rot()
{
	return rot;
}

void Block2D::set_tex(Texture *texture)
{
	if (is_masked) texture->make_mask();
	this->texture = texture;
}

void Block2D::set_driven()
{
	is_driven = true;
}

void Block2D::set_depth(float depth)
{
	pos.z = -depth;
}

void Block2D::set_tex_size(Vector2f s)
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
