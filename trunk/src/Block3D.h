#ifndef BLOCK3D_H_
#define BLOCK3D_H_

#include <string>
#include <list>

#include "Vector3f.h"
#include "Obj.h"
#include "Texture.h"
#include "Block.h"

class Block3D : public Block
{
private:
	bool is_driven;
protected:
	Obj* object;
	Texture* texture;
	Vector3f pos;
	Vector3f rot;
	Vector3f dir;
	Vector3f offset;
	Vector3f* bb_min;
	Vector3f* bb_max;
	Vector3f min;
	Vector3f max;
	bool collide_x(Vector3f* omin, Vector3f* omax);
	bool collide_y(Vector3f* omin, Vector3f* omax);
	bool collide_z(Vector3f* omin, Vector3f* omax);
	list<Block3D*> children;
	void update_bb();
	bool changed;
	float scale;
public:
	Block3D();
	virtual ~Block3D();
	Block3D(const Block3D& b);
	void set_obj(Obj *object);
	void set_tex(Texture *texture);
	void set_pos(Vector3f pos);
	void set_dir(Vector3f dir);
	void change_dir(Vector3f plus_dir);
	void set_scale(float scale) {this->scale = scale;}
	bool operator==(const Block3D& b);
	Obj* get_obj();
	Vector3f get_pos();
	Vector3f get_rot();
	void set_rot(Vector3f rot) {this->rot = rot;}
	Vector3f get_dir() {return dir;}
	void set_offset(Vector3f offset) {this->offset = offset;}
	Vector3f get_bb_min();
	Vector3f get_bb_max();
	void nudge(Vector3f nudge);
	void move(Vector3f move);
	void rotate(Vector3f rot);
	void display();
	void set_driven();
	bool collide(Block3D* other);
	void add_child(Block3D* child);
	void clear_children();
};

#endif /*BLOCK_H_*/
