#include "Buttons.h"

#include "SDL.h"

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
		d->set_fullscreen();
		break;
		case SDLK_ESCAPE:
		req_quit = true;
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
		default:
		//do nothing
		break;
	}
}

void Buttons::set_display(Display * d)
{
	this->d = d;
}
