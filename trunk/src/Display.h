#ifndef DISPLAY_H_
#define DISPLAY_H_

#define BUFSIZE 512

#include <GL/gl.h>
#include <GL/glu.h>

#include <list>

#include "Vector3f.h"
#include "Block.h"
#include "Camera.h"

class Display
{
public:
	list<Block*> blocks;
	list<Block*> hud_blocks;
	bool key_up, key_down, key_left, key_right;
	Display(int agrc, char** argv);
	void update();
	void pick();
	void init();
	virtual ~Display();
	void keys(unsigned char key, int x, int y);
	void s_keys(int key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void activeMouse(int x, int y);
	void resizeWindow(int w, int h);
	void reset_keys();
	void translate(Vector3f t);
	void rotate(Vector3f r);
	Camera* get_camera();
private:
	Camera* camera;
	float win_ratio;
	int win_width, win_height;
	Vector3f tra, rot;
	float near, far;
	float amb_light[4];
	float dif_light[4];
	float pos_light[4];
	int mouse_x, mouse_y;
	bool pick_flag, mouse_down;
	GLuint getClosestHit(GLuint* selectBuf, GLint hits);
};

#endif /*DISPLAY_H_*/
