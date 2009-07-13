#ifndef BLOCK_H_
#define BLOCK_H_

#include <string>

#include "Vector3f.h"
#include "Vector3i.h"
#include "Obj.h"
#include "Texture.h"

class Block
{
private:
	Obj* object;
	Texture* texture;
	Vector3f pos;
	Vector3i grid_pos;
public:
	Block();
	virtual ~Block();
	Block(const Block& b);
	void set_obj(Obj *object);
	void set_tex(Texture *texture);
	void set_pos(Vector3f pos);
	Obj* get_obj();
	Vector3f get_pos();
	void move(Vector3f move);
	void display();
};

#endif /*BLOCK_H_*/
