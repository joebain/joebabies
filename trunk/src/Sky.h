#ifndef SKY_H
#define SKY_H

#include "Block3D.h"

class Sky : public Block3D
{
public:
	Sky();
	void set_scale(float scale);
	void set_perm_tex(Texture tex);
private:
	Obj perm_object;
	Texture perm_texture;
	float scale;
};

#endif
