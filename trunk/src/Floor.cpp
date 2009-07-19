#include "Floor.h"

Floor::Floor()
{
	is_masked = false;
	pos.init(0,0);
	size.init(0,0);
	is_driven = false;
	depth = 1;
	rot = 0;
	tex_size.init(0,0);
	
	tex_coords[0][0] = 0;
	tex_coords[0][1] = 0;
	tex_coords[1][0] = 0;
	tex_coords[1][1] = 1;
	tex_coords[2][0] = 1;
	tex_coords[2][1] = 1;
	tex_coords[3][0] = 1;
	tex_coords[3][1] = 0;
}

void Floor::set_tex_size(Vector2f s)
{

}
