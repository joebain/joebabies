#include "World.h"

#ifdef WIN32
#include <windows.h>
#endif
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <vector>

#include "SDL.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <luabind/luabind.hpp>
#include <luabind/object.hpp>

World::World(Display *d, lua_State *l)
{
	this->d = d;
	buttons.set_display(d);
	
	this->l = l;
	
	bf.set_display(d);
	
	time.get_time();
}

World::~World()
{
}

void World::main_loop()
{
	
	done = false;
	
	while (!done) {
	
		d->update();
		
		try {
			//call a lua function
			luabind::call_function<void>(l, "step",time.time_since_last());
		} catch(const std::exception &TheError) {
			cerr << TheError.what() << endl;
			cerr << lua_tostring(l, -1) << endl;
		}
		//glutPostRedisplay();
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch(event.type){
				case SDL_QUIT:
				quit();
				break;
				case SDL_KEYDOWN:
				buttons.handle_keydown(&event.key.keysym);
				break;
				case SDL_KEYUP:
				buttons.handle_keyup(&event.key.keysym);
				break;
			}
		}
		
		if (buttons.req_quit) quit();
	}
}

void World::quit()
{
	SDL_Quit();
	
	done = true;
}

Display* World::get_display()
{
	return d;
}

BlockFactory* World::get_block_factory()
{
	return &bf;
}

Buttons* World::get_buttons()
{
	return &buttons;
}

void World::reg_key_left(Controller* c)
{
	left = c;
	c->set_lua(l);
}

void World::reg_key_right(Controller* c)
{
	right = c;
	c->set_lua(l);
}

void World::reg_key_up(Controller* c)
{
	up = c;
	c->set_lua(l);
}

void World::reg_key_down(Controller* c)
{
	down = c;
	c->set_lua(l);
}
