#ifndef BLOCK2D_H_
#define BLOCK2D_H_

#include <string>

#include "Vector3f.h"
#include "Vector2f.h"
#include "Texture.h"
#include "Block.h"

class Block2D : public Block
{
private:

protected:
	Texture* texture;
	Vector3f pos;
	Vector2f size;
	float tex_coords[4][2];
	Vector3f rot;
	bool is_driven;
	bool is_masked;
	bool is_2d;
public:
	Block2D();
	~Block2D();
	Block2D(const Block2D& b);
	bool operator==(const Block2D& b);
	void set_tex(Texture *texture);
	void set_mask(bool t);
	void set_pos(Vector2f pos);
	void set_pos(Vector3f pos);
	void set_size(Vector2f size);
	Vector2f get_pos_2d();
	Vector3f get_pos();
	float get_rot_2d();
	Vector3f get_rot();
	void move(Vector2f move);
	void move(Vector3f move);
	void scale(float s);
	void scale(Vector2f s);
	void rotate(float rot);
	void rotate(Vector3f rot);
	void display();
	void set_driven();
	void set_depth(float d);
	void set_tex_size(Vector2f s);
};

#endif
