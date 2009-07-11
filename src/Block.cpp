#include "Block.h"

#include <iostream>
#include <string>

#include "Vector3f.h"
#include "ModelLoader.h"
#include "Texture.h"

Block::Block()
{
	pos.init(0,0,0);
	grid_pos.init(0,0,0);
	
}

Block::~Block()
{
}

void Block::move(Vector3f move)
{
	pos.x += move.x;
	pos.z += move.z;
	pos.y += move.y;
	
	object->translate(pos);
}

void Block::set_pos(Vector3f pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
	this->pos.z = pos.z;
	
	object->translate(pos);
}

Vector3f Block::get_pos()
{
	return pos;
}

Obj* Block::get_obj()
{
	return object;
}

void Block::set_obj(Obj *object)
{
	this->object = object;
}
