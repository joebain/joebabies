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
	dir = b.dir;
	texture = b.texture;
	is_driven = b.is_driven;
	offset = b.offset;
}

void Block3D::move(Vector3f move)
{
	Vector3f move_tmp(move);
	if (is_driven) {
		move_tmp.rotate(-dir);	
	}
		pos.x += move_tmp.x;
		pos.z += move_tmp.z;
		pos.y += move_tmp.y;
}

void Block3D::nudge(Vector3f nudge)
{
	Vector3f move_tmp(nudge);
	if (is_driven) {
		move_tmp.rotate(-dir);	
	}
		offset.x += move_tmp.x;
		offset.z += move_tmp.z;
		offset.y += move_tmp.y;
}

void Block3D::rotate(Vector3f plus_rot)
{
	rot += plus_rot;
}

void Block3D::change_dir(Vector3f plus_dir)
{
	dir += plus_dir;
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
	object->translate(pos+offset);
	object->rotate(rot+dir);
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
	bb_min = &object->min;
	bb_max = &object->max;
}

void Block3D::set_tex(Texture *texture)
{
	this->texture = texture;
}

void Block3D::set_driven()
{
	is_driven = true;
}

Vector3f Block3D::get_bb_min() 
{
	Vector3f v(bb_min->x,bb_min->y,bb_min->z);
	
	v += pos;
	
	return v;
}

Vector3f Block3D::get_bb_max()
{
	Vector3f v(bb_max->x,bb_max->y,bb_max->z);
	
	v += pos;
	
	return v;
}

bool Block3D::collide(Block3D* other)
{	
	Vector3f omax = other->get_bb_max();
	Vector3f omin = other->get_bb_min();
	
	if (collide_x(&omax,&omin) && collide_y(&omax,&omin) && collide_z(&omax,&omin))
		return true;
	else
		return false;
}

bool Block3D::collide_x(Vector3f* omax, Vector3f* omin)
{
	if ((omax->x > bb_min->x && omin->x < bb_max->x ) ||
		 (omax->x < bb_min->x && omin->x > bb_max->x ))
		return true;
	else
		return false;
}

bool Block3D::collide_y(Vector3f* omax, Vector3f* omin)
{
	if ((omax->y > bb_min->y && omin->y < bb_max->y ) ||
		 (omax->y < bb_min->y && omin->y > bb_max->y ))
		return true;
	else
		return false;
}

bool Block3D::collide_z(Vector3f* omax, Vector3f* omin)
{
	if ((omax->z > bb_min->z && omin->z < bb_max->z ) ||
		 (omax->z < bb_min->z && omin->z > bb_max->z ))
		return true;
	else
		return false;
}
