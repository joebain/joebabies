#ifndef WORLD_H_
#define WORLD_H_

#include "Display.h"
#include "Vector3f.h"
#include "Block.h"
#include "Obj.h"
#include "Texture.h"

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
public:
	World(Display *d, lua_State *l);
	virtual ~World();
	void main_loop();
	Block* new_block(string object, string texture);
};

#endif /*WORLD_H_*/
