/* An imaginary block, used to allow collision detection in arbitrary areas.
 */
#ifndef BLOCK_3D_IMAGINARY_H_
#define BLOCK_3D_IMAGINARY_H_

#include "Block3D.h"
#include "Vector3f.h"

class Block3DImaginary : public Block3D {
public:
	Block3DImaginary(Vector3f size);
	Block3DImaginary(const Block3DImaginary& b);
	void display();
	void toggle_debug();
private:
	Vector3f perm_bb_min; //usually the block3d just points to its object for the bb, as this has no object it must keep its bb values itself
	Vector3f perm_bb_max;
	bool in_debug;
};

#endif
