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
	lua_State *L;
	bool lua_go;
	Vector3f rot, tran;
	list<Texture> textures;
	list<Obj> objects;
	void run_lua(string file);
public:
	World(Display *d);
	virtual ~World();
	void main_loop();
	void add_block(Block* b);
	Block* new_block(string object, string texture);
	list<Block>* get_blocks();
	int num_blocks();
	Display* get_display();
	void send_vector();
	void set_lua(lua_State *L);
};

#endif /*WORLD_H_*/
