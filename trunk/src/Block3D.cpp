#include "Block3D.h"

#include <iostream>
#include <string>

#include "Vector3f.h"
#include "ModelLoader.h"
#include "Texture.h"

Block3D::Block3D()
{
	pos.init(0,0,0);
	is_driven = false;
}

Block3D::~Block3D()
{
	object = NULL;
	texture = NULL;
}

Block3D::Block3D(const Block3D& b)
{
	object = b.object;
	pos = b.pos;
	rot = b.rot;
	texture = b.texture;
}

void Block3D::move(Vector3f move)
{
	Vector3f move_tmp(move);
	if (is_driven) {
		move_tmp.rotate(-rot);	
	}
		pos.x += move_tmp.x;
		pos.z += move_tmp.z;
		pos.y += move_tmp.y;
}

void Block3D::rotate(Vector3f plus_rot)
{
	rot += plus_rot;
}

void Block3D::set_pos(Vector3f pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
	this->pos.z = pos.z;
	
	//object->translate(pos);
}

void Block3D::display()
{
	object->translate(pos);
	object->rotate(rot);
	object->texture = texture;
	object->display();
}

Vector3f Block3D::get_pos()
{
	return pos;
}

Vector3f Block3D::get_rot()
{
	return rot;
}

Obj* Block3D::get_obj()
{
	return object;
}

void Block3D::set_obj(Obj *object)
{
	this->object = object;
}

void Block3D::set_tex(Texture *texture)
{
	this->texture = texture;
}

void Block3D::set_driven()
{
	is_driven = true;
}
