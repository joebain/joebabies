#ifndef WORLD_H_
#define WORLD_H_

#include "Display.h"
#include "Vector3f.h"
#include "Block.h"
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
	Controller *left, *right, *up, *down;
public:
	World(Display *d, lua_State *l);
	virtual ~World();
	void main_loop();
	Block* new_block(string object, string texture);
	Display* get_display();
	void reg_key_left(Controller* c);
	void reg_key_right(Controller* c);
	void reg_key_down(Controller* c);
	void reg_key_up(Controller* c);
};

#endif /*WORLD_H_*/
