/* This one is pretty important, all the 3d models and objects are some
 * kind of 3d block object. Links to an Obj object and a Texture object.
 * 
 * Optionally the 3d block can have children, these are designed to be
 * positioned relative to the parent at all times, so they will rotte
 * and translate with the parent. It is unfortunately a bit of a hack
 * though and for example calling 'set_pos()' breaks the position of the
 * children. Parent and children have identical pos and dir vectors.
 * 
 * The block is also defined with two position and two rotation vectors,
 * the reason for this is one will be yracked by the camera and echoed by
 * children (dir and pos) the other is independant, allowing for animation
 * jiggles or for children to be offset from parents.
 */

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
	Obj* object; //the 3d model
	Texture* texture; //the texture data
	Vector3f pos; //the main position
	Vector3f dir; //the main direction
	Vector3f offset; //the offset position 
	Vector3f rot; //the offset direction (poorly named atm)
	Vector3f* bb_min; //bounding box info
	Vector3f* bb_max;
	Vector3f min;
	Vector3f max;
	bool collide_x(Vector3f* omin, Vector3f* omax); //internally used collision checkers
	bool collide_y(Vector3f* omin, Vector3f* omax);
	bool collide_z(Vector3f* omin, Vector3f* omax);
	list<Block3D*> children; //kiddies
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
	void set_driven(); //a 'driven' block moves in local coordinates, moves relative to the direction it is facing
	bool collide(Block3D* other);
	void add_child(Block3D* child);
	void clear_children();
};

#endif /*BLOCK_H_*/
