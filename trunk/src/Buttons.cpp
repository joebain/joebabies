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
		display->set_fullscreen();
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

void Buttons::set_display(Display * d)
{
	this->display = d;
}
