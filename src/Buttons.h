#ifndef BUTTONS_H
#define BUTTONS_H

#include "SDL.h"

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
