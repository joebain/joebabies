#ifndef BLOCK3D_H_
#define BLOCK3D_H_

#include <string>

#include "Vector3f.h"
#include "Obj.h"
#include "Texture.h"
#include "Block.h"

class Block3D : public Block
{
private:
	Obj* object;
	Texture* texture;
	Vector3f pos;
	Vector3f rot;
	bool is_driven;
public:
	Block3D();
	virtual ~Block3D();
	Block3D(const Block3D& b);
	void set_obj(Obj *object);
	void set_tex(Texture *texture);
	void set_pos(Vector3f pos);
	Obj* get_obj();
	Vector3f get_pos();
	Vector3f get_rot();
	void move(Vector3f move);
	void rotate(Vector3f rot);
	void display();
	void set_driven();
};

#endif /*BLOCK_H_*/
