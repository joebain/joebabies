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
	float distance;
	float height;
private:
	bool is_following;
	Vector3f pos;
	Vector3f dir;
	void set_distance(float distance) {this->distance = distance;}
	void set_height(float height) {this->height = height;}
	Block* subject;
	int follow_type;
};

#endif
