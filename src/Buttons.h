/* This just wraps the SDL key capturing to make it easily accessible in Lua.
 */

#ifndef BUTTONS_H
#define BUTTONS_H

#include <SDL/SDL.h>

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
	
	bool lmb;
	bool rmb;
	
	int mouse_x;
	int mouse_x_move;
	int mouse_y;
	int mouse_y_move;
	
	bool req_quit;
	bool req_fullscreen;
	
	void update();
	void clear();
	void handle_keydown(SDL_keysym *key);
	void handle_keyup(SDL_keysym *key);
    void handle_mousedown ( SDL_MouseButtonEvent* e );
    void handle_mouseup ( SDL_MouseButtonEvent* e );
    void handle_mousemove ( SDL_MouseMotionEvent* e );
};

#endif
