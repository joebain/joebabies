#include "World.h"

#ifdef WIN32
#include <windows.h>
#endif

#include <SDL/SDL.h>

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <vector>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "AudioFile.h"
#include "AudioMixer.h"

#include <luabind/luabind.hpp>
#include <luabind/object.hpp>

World::World(Display *d, lua_State *l)
{
	this->d = d;
	d->buttons = &buttons;
	d->bfac = &bf;
	
	this->l = l;
	
	time.get_time();
	
	mixer = new AudioMixer();
}

World::~World()
{
}

void World::main_loop()
{
	done = false;
	
	while (!done) {
	
		float delta = time.time_since_last();
		while (delta < 0.033) {
			sleep(0.001);
			delta += time.time_since_last();
		}
		
		buttons.update();
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch(event.type){
				case SDL_QUIT:
					buttons.req_quit = true;
					break;
				case SDL_KEYDOWN:
					buttons.handle_keydown(&event.key.keysym);
					break;
				case SDL_KEYUP:
					buttons.handle_keyup(&event.key.keysym);
					break;
				case SDL_MOUSEBUTTONDOWN:
					buttons.handle_mousedown(&event.button);
					break;
				case SDL_MOUSEBUTTONUP:
					buttons.handle_mouseup(&event.button);
					break;
				case SDL_MOUSEMOTION:
					buttons.handle_mousemove(&event.motion);
					break;
			}
		}
		
		d->update(delta);
		
		try {
			//call a lua function
			luabind::call_function<void>(l, "step",delta);
		} catch(const std::exception &TheError) {
			cerr << TheError.what() << endl;
			cerr << lua_tostring(l, -1) << endl;
		}
		
		if (buttons.req_quit) quit();
		
	}
}

void World::quit()
{
	done = true;
	
	SDL_Quit();	
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

AudioFile* World::new_audio_file(string name, bool is_music) 
{
  AudioFile *af = mixer->new_audio_file(name, is_music);
  return af;
}

