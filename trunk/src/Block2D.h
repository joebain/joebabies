#ifndef BLOCK2D_H_
#define BLOCK2D_H_

#include <string>

#include "Vector2f.h"
#include "Texture.h"
#include "Block.h"

class Block2D : public Block
{
private:

protected:
	Texture* texture;
	Vector2f pos;
	Vector2f size;
	float tex_coords[4][2];
	float rot;
	float depth;
	bool is_driven;
	bool is_masked;
public:
	Block2D();
	~Block2D();
	Block2D(const Block2D& b);
	void set_tex(Texture *texture);
	void set_mask(bool t);
	void set_pos(Vector2f pos);
	void set_size(Vector2f size);
	Vector2f get_pos();
	float get_rot();
	void move(Vector2f move);
	void scale(float s);
	void scale(Vector2f s);
	void rotate(float rot);
	void display();
	void set_driven();
	void set_depth(float d);
};

#endif
