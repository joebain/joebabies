#include "Snake.h"

#include <iostream>
#include <math.h>
#include "Block.h"

Snake::Snake()
{
	h_pos.init(0,2.2,8.8);

	speed = 0.1;
	min_dist = 2.2;
	
	Vector3f pos, rot;
	pos.init(0,0,6.2);
	rot.init(0,0,0);
		
	//3 body pieces to start
	int i;
	for (i = 0 ; i < 3 ; i ++) {
		b_pos.push_back(pos);
		b_rot.push_back(rot);
		pos.z += 2.2;
	}
	b_pos.push_back(pos);
	b_rot.push_back(rot);
	
	forward.init(0,0,-2.2);
	
	jump_type = NORMAL;
	
}

Snake::~Snake()
{
}

void Snake::wait()
{
	jump_prog = 0.0;
}

void Snake::jump()
{
	
	switch (jump_type) {
		case NORMAL:
			aim = h_pos + forward;
			break;
		case FAR:
			aim = h_pos + forward + forward;
			break;
		case HIGH:
			aim = h_pos + forward;
			break;
	}
}

void Snake::decide(Block* b)
{
	cout << "block is " << b->object->name << endl;
	
	Vector3f rot;
	if (b->type == b->PLAIN) {
		
	}
	else if (b->type == b->T_RIGHT) {
		rot.init(0,0,90);
		forward.rotate(rot);
	}
	else if (b->type == b->T_LEFT) {
		rot.init(0,0,-90);
		forward.rotate(rot);
	}
	else if (b->type == b->S_FAR) {
		jump_type = FAR;
	}
	else if (b->type == b->S_HIGH) {
		jump_type = HIGH;
	}
}

void Snake::step() {
	if (h_pos.dist_between(aim) > 0.2) {
		move(h_pos.dir_between(aim));
	}
}

void Snake::draw() {
	
	head->translate(h_pos);
	head->display();
	/*
	vector<Vector3f>::iterator pos_i = b_pos.begin();
	vector<Vector3f>::iterator rot_i = b_rot.begin();
	int x = 0;
    while (x < (int)(b_pos.size()-1)) {
    	body->translate(*pos_i);
    	body->rotation = *rot_i;
    	body->display();
    	pos_i++;
    	rot_i++;
    	x++;
    }
    
    tail->translate(*pos_i);
    tail->rotation = *rot_i;
    tail->display();
    */
    
    
}

Vector3f Snake::set_speed(Vector3f dir)
{
	dir.multiply(speed);
	
	return dir;
}

void Snake::move(Vector3f dir) {
	
	//move head
	
	// - objects face along z but rotation is with respect to facing xyz unit so for now we add 225 to y rot
	Vector3f heading = dir.angle_to();
	
	//cout << "direction is " << heading.x << "," << heading.y << endl;
	
	if (dir.y > 0.1) heading.x = 90;
	else if (dir.y < -0.1) heading.x = -90;
	else heading.x = 0;
	
	//sort out going up and down
	
	int diffx = ((int)(head->rotation.x - heading.x)+3600)%360;
	int diffy;
	
	if (diffx != 0) {
		if (diffx < 180) head->rotation.x --;
		else if (diffx >= 180) head->rotation.x ++;
	} else {
	
		heading.y += 225;
		
		int diffy = ((int)(head->rotation.y-heading.y)+3600)%360;
		
		//move and turn
		if (diffy != 0) {
			if (diffy < 180) head->rotation.y --;
			else if (diffy >= 180) head->rotation.y ++;
		}
		h_pos += set_speed(dir);
	}
		
	//go through the body pieces
	vector<Vector3f>::iterator bp_i1;
	vector<Vector3f>::iterator bp_i2;
	vector<Vector3f>::iterator br_i1;
	vector<Vector3f>::iterator br_i2;
	
	//first piece done seperately	
	bp_i1 = b_pos.begin();
	br_i1 = b_rot.begin();
	dir = bp_i1->dir_between(h_pos);
	heading = dir.angle_to();
	
	heading.y += 225;
	
	diffy = ((int)(br_i1->y-heading.y)+3600)%360;
	//cout << "body diff is " << diff << endl;
	//either move or turn
	if (diffy > 5) {
		if (diffy < 180) br_i1->y --;
		else if (diffy >= 180) br_i1->y ++;
	}
	else {
		if (bp_i1->dist_between(h_pos) > min_dist) (*bp_i1) += set_speed(dir);
		else (*bp_i1) -= set_speed(dir);
	}
	
	//and the rest
	bp_i2 = b_pos.begin();
	bp_i1 ++;
	br_i2 = b_rot.begin();
	br_i1 ++;
	
	while (bp_i1 != b_pos.end()) {
		
		dir = bp_i1->dir_between(*bp_i2);
		heading = dir.angle_to();
		
		heading.y += 225;
		
		diffy = ((int)(br_i1->y-heading.y)+3600)%360;
		
		//either move or turn
		if (diffy > 5) {
			if (diffy < 180) br_i1->y --;
			else if (diffy >= 180) br_i1->y ++;
		}
		else {
			if (bp_i1->dist_between(*bp_i2) > min_dist) (*bp_i1) += set_speed(dir);
			else (*bp_i1) -= set_speed(dir);
		}
		
		bp_i1++;
		bp_i2++;
		br_i1++;
		br_i2++;
	}
	
}