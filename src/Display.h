/* This is a pretty h/c class. It manages displaying all the objects, doing
 * transformations, lighting, display set up. It's probably gotten a bit
 * too big and definately needs a clear out.
 */
#ifndef DISPLAY_H_
#define DISPLAY_H_

#define BUFSIZE 512

#ifdef WIN32
#include <windows.h>
#endif

#include <SDL/SDL.h>
#include <stdlib.h>

#include <list>

#include <GL/gl.h>
#include <GL/glu.h>

#include "Block.h"
#include "Camera.h"
#include "Floor.h"
#include "Sky.h"
#include "Buttons.h"
#include "BlockFactory.h"

class Display
{
public:
	Buttons* buttons;
	BlockFactory* bfac;
	Display();
	void update(float delta);
	Block3DFlat* pick();
	Vector3f project_xy(int x, int y, float z);
	void init();
	void set_fullscreen();
	Camera* get_camera();
	int get_width() {return win_width;}
	int get_height() {return win_height;}
private:
	SDL_Surface *surface;
	Camera* camera;
	float win_ratio;
	int window_id;
	int win_width, win_height;
	string win_name, win_icon;
	float near_vp, far_vp;
	float amb_light[4];
	float dif_light[4];
	float pos_light[4];
	float spec_light[4];
	bool pick_flag;
	bool is_fullscreen;
	GLuint getClosestHit(GLuint* selectBuf, GLint hits); //again to do with picking, not used atm
	static bool depth_sort2(Block* one, Block* two); //used to depth sort objects
	static bool depth_sort(Block* one, Block* two); //used to depth sort objects
};

#endif /*DISPLAY_H_*/

