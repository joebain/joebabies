/* This type of Block is flat and usually textured. basically draws a
 * rectangle and applies the texture to it. This kind of block also can
 * have transparency and be masked (i.e have see through bits).
 */

#ifndef BLOCK3DFLAT_H_
#define BLOCK3DFLAT_H_

#include <string>
#include <list>
#include <utility>

#include "Vector3f.h"
#include "Vector2f.h"
#include "Rectanglef.h"
#include "Texture.h"
#include "Block.h"
#include "HasPosDir3D.h"
#include "Timer.h"

class Block3DFlat : public Block, public HasPosDir3D
{
private:

protected:
	Texture* texture;
	
	Timer timer;
	double last_texture_switch;
	
	Vector2f size;
	list<pair<Rectanglef,float> > tex_coords;
	list<pair<Rectanglef,float> >::iterator current_coords;
	
	Rectanglef get_tex_coords() { return current_coords->first; }
	void draw_rect();
	
	bool is_driven;
	bool is_2d;
	float transparency;
	bool rel_centre;
	enum {MASKED, TRANSP, NEITHER, HAS_ALPHA} shown;
	
	bool animating;
	bool flip_y;
	bool bounce;
	int anim_dir;
public:
	Block3DFlat();
	~Block3DFlat();
	Block3DFlat(const Block3DFlat& b);
	bool operator==(const Block3DFlat& b);
	void set_tex(Texture *texture);
	void set_animation(Vector2f size, int width, int height, std::list< float > times, bool bounce);
	void set_mask(bool t);
	void set_transparent(bool t);
	void set_transparency(float t);
	bool is_transparent();

	//animation
	void stop() { animating = false; }
	void start() { animating = true; }
	void reset() { current_coords = tex_coords.begin(); anim_dir = 1; }
	
	void flipY() { flip_y = !flip_y; }
	void set_facing(bool forward) { flip_y = forward; }
	
	void set_size(Vector2f size);
	void change_size(float s);

	void move(Vector3f move);
	void scale(float s);
	void scale(Vector2f s);
	void rotate(Vector3f rot);
	void display();
	void set_driven();
	void set_tex_size(Vector2f s); // This is porrly named and actually sets the number of times a texture will repeat over the block.
	void set_rel_centre(bool t) {rel_centre = t;} // Whether the object should be rotated relatove to its own centre or the global (0,0,0).
};

#endif
