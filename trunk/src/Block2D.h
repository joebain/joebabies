#ifndef BLOCK2D_H_
#define BLOCK2D_H_

#include <string>

#include "Vector2f.h"
#include "Block3DFlat.h"

class Block2D : public Block3DFlat
{
private:

protected:
	
public:
	Block2D();
	void set_pos(Vector2f pos);
	Vector2f get_pos();
	float get_rot();
	void move(Vector2f move);
	void rotate(float rot);
	void set_depth(float d);
};

#endif
