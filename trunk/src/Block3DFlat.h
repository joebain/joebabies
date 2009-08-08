#ifndef BLOCK3DFLAT_H_
#define BLOCK3DFLAT_H_

#include <string>

#include "Vector3f.h"
#include "Vector2f.h"
#include "Texture.h"
#include "Block.h"

class Block3DFlat : public Block
{
private:

protected:
	Texture* texture;
	Vector3f pos;
	Vector2f size;
	float tex_coords[4][2];
	Vector3f rot;
	bool is_driven;
	bool is_2d;
	float transparency;
	bool rel_centre;
	enum {MASKED, TRANSP, NEITHER} shown;
public:
	Block3DFlat();
	~Block3DFlat();
	Block3DFlat(const Block3DFlat& b);
	bool operator==(const Block3DFlat& b);
	void set_tex(Texture *texture);
	void set_mask(bool t);
	void set_transparency(float t);
	bool is_transparent();
	void set_pos(Vector3f pos);
	void set_size(Vector2f size);
	void change_size(float s);
	Vector3f get_pos();
	Vector3f get_rot();
	void move(Vector3f move);
	void scale(float s);
	void scale(Vector2f s);
	void rotate(Vector3f rot);
	void display();
	void set_driven();
	void set_tex_size(Vector2f s);
	void set_rel_centre(bool t) {rel_centre = t;}
};

#endif
