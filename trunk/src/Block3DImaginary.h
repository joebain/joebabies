#ifndef BLOCK_3D_IMAGINARY_H_
#define BLOCK_3D_IMAGINARY_H_

#include "Block3D.h"
#include "Vector3f.h"

class Block3DImaginary : public Block3D {
public:
	Block3DImaginary(Vector3f size);
	Block3DImaginary(const Block3DImaginary& b);
	void display();
private:
	Vector3f perm_bb_min;
	Vector3f perm_bb_max;
};

#endif
