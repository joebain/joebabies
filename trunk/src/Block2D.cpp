#include "Block2D.h"

#ifdef WIN32
#include <windows.h>
#endif
#include <iostream>
#include <string>

#include "Vector2f.h"
#include "Texture.h"

Block2D::Block2D(int name) : Block3DFlat(name)
{
	pos.z = 1;
	is_2d = true;
}

void Block2D::move(Vector2f move)
{
	Vector2f move_tmp(move);
	if (is_driven) {
		move_tmp.rotate(-dir.z);
	}
	pos.x += move.x;
	pos.y += move.y;
}

void Block2D::rotate(float plus_rot)
{
	dir.z += plus_rot;
}

void Block2D::set_pos(Vector2f pos)
{
	this->pos.init(pos.x,pos.y,this->pos.z);
}

Vector2f Block2D::get_pos_2f()
{
	return Vector2f(pos.x,pos.y);
}

float Block2D::get_dir_1f()
{
	return dir.z;
}

void Block2D::set_depth(float depth)
{
	pos.z = -depth;
}

