#ifndef CAMERA_H
#define CAMERA_H

#include "Block3D.h"

#define FOLLOW_TYPE_3D 1
#define FOLLOW_TYPE_2D 2

class Camera
{
public:
	Camera();
	void follow(Block3D* subject);
	void position();
	void move(float delta);
	void set_distance(float distance) {this->distance = distance;}
	void set_height(float height) {this->height = height;}
private:
	bool is_following;
	Vector3f pos;
	Vector3f target_pos;
	Vector3f aim_target_pos;
	Vector3f aim_pos;
	
	float distance;
	float height;
	float min_snap;
	
	Block* subject;
	int follow_type;
};

#endif
