#ifndef CAMERA_H
#define CAMERA_H

#include "Block3D.h"

#define FOLLOW_TYPE_3D 1
#define FOLLOW_TYPE_2D 2

class Camera
{
public:
	void follow(Block3D* subject);
	void position();
private:
	bool is_following;
	Block* subject;
	int follow_type;
};

#endif
