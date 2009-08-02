#ifndef WORLD_H_
#define WORLD_H_

#include <string>
#include <list>
#include <time.h>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include <luabind/luabind.hpp>

#include "Display.h"
#include "Controller.h"
#include "Timer.h"
#include "Buttons.h"

#include "BlockFactory.h"

#include "Vector3f.h"
#include "Vector2f.h"
#include "Vector2i.h"

class World
{
private:
	bool running;
	Display* d;
	lua_State *l;
	BlockFactory bf;
	Controller *left, *right, *up, *down;
	Timer time;
	Buttons buttons;
public:
	World(Display *d, lua_State *l);
	virtual ~World();
	void main_loop();
	BlockFactory* get_block_factory();
	Display* get_display();
	Buttons* get_buttons();
	void reg_key_left(Controller* c);
	void reg_key_right(Controller* c);
	void reg_key_down(Controller* c);
	void reg_key_up(Controller* c);
};

#endif /*WORLD_H_*/
