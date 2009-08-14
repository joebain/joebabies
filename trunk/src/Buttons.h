/* This just wraps the SDL key capturing to make it easily accessible in Lua.
 */

#ifndef BUTTONS_H
#define BUTTONS_H

#include <SDL/SDL.h>

#include "Display.h"

class Buttons
{
public:
	Buttons();
	
	bool up;
	bool down;
	bool left;
	bool right;
	bool space;
	bool s;
	bool a;
	bool d;
	bool w;
	
	bool req_quit;
	void clear();
	void handle_keydown(SDL_keysym *key);
	void handle_keyup(SDL_keysym *key);
	void set_display(Display * d);
private:
	Display* display;

};

#endif
