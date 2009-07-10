#ifndef BLOCK_H_
#define BLOCK_H_

#include "Vector3f.h"
#include "Vector3i.h"
#include "Obj.h"

#define FALL_SPEED 0.4
#define POS_ERR 0.3

class Block
{
private:
public:
	bool falling;
	bool null;
	Obj* object;
	Obj* shadow;
	Vector3f pos;
	Vector3i grid_pos;
	Block();
	Vector3i shadow_pos;
	virtual ~Block();
	void set_obj(Obj *object);
	void set_pos(Vector3f pos);
	void display();
	Block copy(Vector3f p);
	Block copy();
	Obj* get_obj();
	bool picked;
	void move(Vector3f move);
	bool has_shadow;
	void set_shadow(Obj *shadow);
	void set_shadow_pos(Vector3i loc);
	Vector3f snap(Vector3f loc);
	Vector3i aim;
	void fall_to(Vector3i new_gp);
	enum {PLAIN, T_RIGHT, T_LEFT, S_HIGH, S_FAR} type;
};

#endif /*BLOCK_H_*/
