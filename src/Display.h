#ifndef DISPLAY_H_
#define DISPLAY_H_

#define BUFSIZE 512

#ifdef WIN32
#include <windows.h>
#endif
#include <stdlib.h>

#include <list>

#include <GL/gl.h>
#include <GL/glu.h>

#include "SDL.h"

#include "Block.h"
#include "Camera.h"
#include "Floor.h"
#include "Sky.h"

class Display
{
public:
	list<Block*> blocks;
	list<Block*> hud_blocks;
	Floor* floor;
	Sky* sky;
	Display();
	void update();
	void pick();
	void init();
	void set_fullscreen();
	Camera* get_camera();
private:
	SDL_Surface *surface;
	Camera* camera;
	float win_ratio;
	int window_id;
	int win_width, win_height;
	float near_vp, far_vp;
	float amb_light[4];
	float dif_light[4];
	float pos_light[4];
	float spec_light[4];
	int mouse_x, mouse_y;
	bool pick_flag, mouse_down;
	bool is_fullscreen;
	GLuint getClosestHit(GLuint* selectBuf, GLint hits);
};

#endif /*DISPLAY_H_*/
