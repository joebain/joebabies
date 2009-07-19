#ifndef WORLD_H_
#define WORLD_H_

#include "Display.h"
#include "Vector3f.h"
#include "Vector2f.h"
#include "Block.h"
#include "Block3D.h"
#include "Block2D.h"
#include "Obj.h"
#include "Texture.h"
#include "Controller.h"

#include <string>
#include <list>
#include <time.h>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

class World
{
private:
	bool running;
	Display* d;
	lua_State *l;
	list<Texture> textures;
	list<Obj> objects;
	list<Block3D> blocks3d;
	list<Block2D> blocks2d;
	Controller *left, *right, *up, *down;
public:
	World(Display *d, lua_State *l);
	virtual ~World();
	void main_loop();
	Block3D* new_block3d(string object, string texture);
	Block3D* new_character(string object, string texture);
	Block2D* new_block2d(Vector2f size, string texture);
	Display* get_display();
	void reg_key_left(Controller* c);
	void reg_key_right(Controller* c);
	void reg_key_down(Controller* c);
	void reg_key_up(Controller* c);
};

#endif /*WORLD_H_*/
