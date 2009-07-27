#ifndef SKY_H
#define SKY_H

#include "Block3D.h"

class Sky : public Block3D
{
public:
	Sky();
	void set_scale(float scale);
private:
	Obj perm_object;
	float scale;
};

#endif
