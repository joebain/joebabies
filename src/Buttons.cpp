#include "Buttons.h"

Buttons::Buttons()
{
	clear();
}

void Buttons::clear()
{
	up = false;
	down = false;
	left = false;
	right = false;
	space = false;
	a = false;
	s = false;
	w = false;
	d = false;
	
	req_quit = false;
}

void Buttons::update() {
	mouse_x_move = 0;
	mouse_y_move = 0;
}

void Buttons::handle_keydown(SDL_keysym *key)
{
	switch (key->sym) {
		case SDLK_UP:
		up = true;
		break;
		case SDLK_DOWN:
		down = true;
		break;
		case SDLK_RIGHT:
		right = true;
		break;
		case SDLK_LEFT:
		left = true;
		break;
		case SDLK_f:
		req_fullscreen = true;
		break;
		case SDLK_ESCAPE:
		req_quit = true;
		break;
		case SDLK_SPACE:
		space = true;
		break;
		case SDLK_s:
		s = true;
		break;
		case SDLK_a:
		a = true;
		break;
		case SDLK_d:
		d = true;
		break;
		case SDLK_w:
		w = true;
		break;
		default:
		//do nothing
		break;
	}
}

void Buttons::handle_keyup(SDL_keysym *key)
{
	switch (key->sym) {
		case SDLK_UP:
		up = false;
		break;
		case SDLK_DOWN:
		down = false;
		break;
		case SDLK_RIGHT:
		right = false;
		break;
		case SDLK_LEFT:
		left = false;
		break;
		case SDLK_SPACE:
		space = false;
		break;
		case SDLK_f:
		req_fullscreen = false;
		break;
		case SDLK_s:
		s = false;
		break;
		case SDLK_a:
		a = false;
		break;
		case SDLK_d:
		d = false;
		break;
		case SDLK_w:
		w = false;
		break;
		default:
		//do nothing
		break;
	}
}

void Buttons::handle_mousedown ( SDL_MouseButtonEvent* e ) {
	switch (e->button) {
		case SDL_BUTTON_LEFT:
			lmb = true;
			break;
		case SDL_BUTTON_RIGHT:
			rmb = true;
			break;
	}
}
void Buttons::handle_mouseup ( SDL_MouseButtonEvent* e ) {
	switch (e->button) {
		case SDL_BUTTON_LEFT:
			lmb = false;
			break;
		case SDL_BUTTON_RIGHT:
			rmb = false;
			break;
	}
}

void Buttons::handle_mousemove ( SDL_MouseMotionEvent* e ) {
	mouse_x = e->x;
	mouse_x_move = e->xrel;
	mouse_y = e->y;
	mouse_y_move = e->yrel;
}
