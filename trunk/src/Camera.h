#ifndef CAMERA_H
#define CAMERA_H

#include "Block.h"

class Camera
{
public:
	void follow(Block* subject);
	void position();
private:
	bool is_following;
	Block* subject;
};

#endif
