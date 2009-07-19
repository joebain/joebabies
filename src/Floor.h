#ifndef FLOOR_H
#define FLOOR_H

#include "Vector2f.h"
#include "Block2D.h"

class Floor : public Block2D {
private:
	Vector2f tex_size;
public:
	Floor();
	void set_tex_size(Vector2f s);
};

#endif
