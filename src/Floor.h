/* Lovely floor. Uses a heightmap to render axesome hills.
 */

#ifndef FLOOR_H
#define FLOOR_H

#include "Vector2f.h"
#include "Vector2i.h"
#include "Block3D.h"
#include "Obj.h"

#include <string>

using namespace std;

class Floor : public Block3D {
private:
	Obj perm_obj;
	float scale;
	Vector2i size;
public:
	Floor() : Block3D(0) {}
	void set_perm_obj(Obj obj);
	void set_perm_tex(Texture* tex);
	float get_height(Vector2f pos);
	void set_scale(float scale) {this->scale = scale;}
	void set_size(Vector2i size) {this->size = size;}
	Vector2i get_size() {return size;}
};

#endif
