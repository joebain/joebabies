#ifndef BUTTONS_H
#define BUTTONS_H

#ifdef WIN32
#include <SDL/SDL.h>
#else
#include "SDL.h"
#endif

#include "Display.h"

class Buttons
{
public:
	Buttons();
	bool up;
	bool down;
	bool left;
	bool right;
	bool req_quit;
	void clear();
	void handle_keydown(SDL_keysym *key);
	void handle_keyup(SDL_keysym *key);
	void set_display(Display * d);
private:
	Display* d;

};

#endif
