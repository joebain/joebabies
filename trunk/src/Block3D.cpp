#include "Block3D.h"

#include <iostream>
#include <string>

#include "Vector3f.h"
#include "ModelLoader.h"
#include "Texture.h"

Block3D::Block3D(int name) : Block(name)
{
	pos.init(0,0,0);
	is_driven = false;
	scale = 1;
}

Block3D::~Block3D()
{
	object = NULL;
	texture = NULL;
}

Block3D::Block3D(const Block3D& b) : Block(b)
{
	object = b.object;
	pos = b.pos;
	rot = b.rot;
	dir = b.dir;
	texture = b.texture;
	is_driven = b.is_driven;
	offset = b.offset;
	max = b.max;
	min = b.min;
	scale = b.scale;
	
	children = b.children;
	
	changed = b.changed;
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
	
	changed = true;
	
	for (list<Block3D*>::iterator it = children.begin(); it != children.end() ; it++)  {
		(*it)->set_pos(pos);
	}
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
	
	changed = true;
}

void Block3D::rotate(Vector3f plus_rot)
{
	rot += plus_rot;
	
	changed = true;
}

bool Block3D::operator==(const Block3D& b)
{
	if (pos == b.pos && dir == b.dir && texture == b.texture && object == b.object && rot == b.rot && offset == b.offset)
		return true;
	else
		return false;
}

void Block3D::change_dir(Vector3f plus_dir)
{
	//cout << "changing dir" << endl;
	//cout << "old dir was " << dir << endl;
	dir += plus_dir;
	
	changed = true;
	
	for (list<Block3D*>::iterator it = children.begin(); it != children.end() ; it++)  {
		//cout << "old off was " << (*it)->offset << endl;
		(*it)->change_dir(plus_dir);
		(*it)->offset.rotate(-plus_dir);
		//cout << "new off is " << (*it)->offset << endl;
	}
}

void Block3D::update_bb()
{
	min = (*bb_min);
	min *= scale;
	min.rotate(-dir);
	min += pos + offset;
	
	max = (*bb_max);
	max *= scale;
	max.rotate(-dir);
	max += pos + offset;
	
	if (min.x > max.x) {
		float tmp = max.x;
		max.x = min.x;
		min.x = tmp;
	}
	if (min.y > max.y) {
		float tmp = max.y;
		max.y = min.y;
		min.y = tmp;
	}
	if (min.z > max.z) {
		float tmp = max.z;
		max.z = min.z;
		min.z = tmp;
	}
	
	changed = false;
}

void Block3D::set_dir(Vector3f dir)
{
	//cout << "setting dir" << endl;
	
	Vector3f tmp_dir = this->dir;
	this->dir = dir;
	
	changed = true;
	
	//cout << "old dir was " << tmp_dir << endl;
	/* all broken, no time to fix
	for (list<Block3D*>::iterator it = children.begin(); it != children.end() ; it++)  {
		cout << "old off was " << (*it)->offset << endl;
		(*it)->set_dir(dir);
		(*it)->offset.rotate(tmp_dir*0.5);
		cout << "new off is " << (*it)->offset << endl;
	}
	*/
}

void Block3D::set_pos(Vector3f pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
	this->pos.z = pos.z;
	
	changed = true;
	
	for (list<Block3D*>::iterator it = children.begin(); it != children.end() ; it++)  {
		(*it)->set_pos(pos);
	}
}

void Block3D::display()
{
	object->scale = scale;
	object->translate(pos+offset);
	object->rotate(rot+dir);
	object->texture = texture;
	object->display();
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

void Block3D::clear_children()
{
	children.clear();
}

Vector3f Block3D::get_bb_min() 
{
	if (changed) update_bb();
	return min;
}

Vector3f Block3D::get_bb_max()
{
	if (changed) update_bb();
	return max;
}

bool Block3D::collide(Block3D* other)
{
	Vector3f omax = other->get_bb_max();
	Vector3f omin = other->get_bb_min();
	
	if (changed) update_bb();
	
	//cout << "us " << max << "  " << min << endl;
	//cout << "them " << omax << "  " << omin << endl;;
	
	bool colx = collide_x(&omax,&omin);
	bool coly = collide_y(&omax,&omin);
	bool colz = collide_z(&omax,&omin);
	
	//cout << "x y z " << colx << " " << coly << " " << colz << endl;
	
	if (colx && coly && colz)
		return true;
	else
		return false;
}

bool Block3D::collide_x(Vector3f* omax, Vector3f* omin)
{
	if ((omax->x > min.x && omax->x < max.x ) ||
		 (omin->x > min.x && omin->x < max.x ) ||
		 (omin->x < min.x && omax->x > max.x ))
		return true;
	else
		return false;
}

bool Block3D::collide_y(Vector3f* omax, Vector3f* omin)
{
	if ((omax->y > min.y && omax->y < max.y ) ||
		 (omin->y > min.y && omin->y < max.y ) ||
		 (omin->y < min.y && omax->y > max.y ))
		return true;
	else
		return false;
}

bool Block3D::collide_z(Vector3f* omax, Vector3f* omin)
{
	if ((omax->z > min.z && omax->z < max.z ) ||
		 (omin->z > min.z && omin->z < max.z ) ||
		 (omin->z < min.z && omax->z > max.z ))
		return true;
	else
		return false;
}

void Block3D::add_child(Block3D* child)
{
	child->pos = pos;
	child->dir = dir;
	children.push_back(child);
}
