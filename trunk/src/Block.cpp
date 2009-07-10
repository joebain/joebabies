#include "Block.h"

#include <iostream>

#include "Vector3f.h"
#include "World.h"

Block::Block()
{
	aim.init(0,0,0);
	pos.init(0,0,0);
	
	null = true;
	falling = false;
	picked = false;
	has_shadow = false;
	
	type = PLAIN;
}

void Block::display() {
	
	//translate and show the block
	object->translate(pos);
	object->display();
	
	//show the shadow if we are picking
	if (picked) {
		shadow->translate(shadow_pos*GAP);
		shadow->display();
	} else {
		
		if (aim.x*GAP < pos.x-POS_ERR) pos.x -= FALL_SPEED;
		else if (aim.x*GAP > pos.x+POS_ERR) pos.x += FALL_SPEED;
		else grid_pos.x = aim.x;
		 
		if (aim.y*GAP < pos.y-POS_ERR) pos.y -= FALL_SPEED;
		else if (aim.y*GAP > pos.y+POS_ERR) pos.y += FALL_SPEED;
		else grid_pos.y = aim.y;
		 
		if (aim.z*GAP < pos.z-POS_ERR) pos.z -= FALL_SPEED;
		else if (aim.z*GAP > pos.z+POS_ERR) pos.z += FALL_SPEED;
		else grid_pos.z = aim.z;
		
		if ((aim.x == grid_pos.x) && (aim.y == grid_pos.y) && (aim.z == grid_pos.z)) {
			//cout << "done falling" << endl;	
			falling = false;
		}
		/*
		if (falling) {
			cout << "still falling" << endl;
			cout << "two ys " << (int)(aim.y*GAP*10) << "," << (int)(pos.y*10) << endl;
			cout << "two xs " << (int)(aim.x*GAP*10) << "," << (int)(pos.x*10) << endl;
			cout << "two zs " << (int)(aim.z*GAP*10) << "," << (int)(pos.z*10) << endl;
		}
		*/
	}
}

Block::~Block()
{
}

void Block::move(Vector3f move)
{
	pos.x += move.x;
	pos.z += move.z;
	pos.y += move.y;
}

void Block::fall_to(Vector3i new_gp) {
	//cout << "block is going for the fall, aim ";
	//new_gp.print();
	//cout << " pos ";
	//grid_pos.print();
	//cout << endl;
	aim = new_gp;
	falling = true;
}

void Block::set_pos(Vector3f pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
	this->pos.z = pos.z;
	
	grid_pos.x = pos.x/GAP;
	grid_pos.y = pos.y/GAP;
	grid_pos.z = pos.z/GAP;
}

void Block::set_shadow_pos(Vector3i pos)
{
	//set the shadow to the nearest grid position
	//shadow_pos = snap(pos);
	
	shadow_pos.init(pos.x,pos.y,pos.z);// = shadow_pos.x/GAP, y = shadow_pos.y/GAP, z = shadow_pos.z/GAP;
	
	aim = pos;
}

Obj* Block::get_obj()
{
	return object;
}

void Block::set_obj(Obj *object)
{
	this->object = object;
}

void Block::set_shadow(Obj *shadow)
{
	this->shadow = shadow;
}

Vector3f Block::snap(Vector3f loc)
{
	Vector3f pos;
	
	pos.x = (int)((loc.x+(GAP/2)) / GAP) * GAP;
	pos.y = (int)((loc.y+(GAP/2)) / GAP) * GAP;
	pos.z = (int)((loc.z+(GAP/2)) / GAP) * GAP;
	
	return pos;
}

Block Block::copy(Vector3f p)
{
	Block new_block;
	new_block.object = this->object;
	new_block.pos = p.copy();
	return new_block;
}

Block Block::copy()
{
	Block new_block;
	new_block.object = this->object;
	new_block.pos = pos.copy();
	return new_block;
}