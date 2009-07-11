#ifndef DISPLAY_H_
#define DISPLAY_H_

#define BUFSIZE 512

#include <GL/gl.h>
#include <GL/glu.h>

#include <vector>

#include "Vector3i.h"
#include "Vector2i.h"
#include "Block.h"

class Display
{
public:
	vector<Block> blocks;
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
private:
	float win_ratio;
	int win_width, win_height;
	float near, far;
	float amb_light[4];
	float dif_light[4];
	float pos_light[4];
	int mouse_x, mouse_y;
	bool pick_flag, mouse_down;
	GLuint getClosestHit(GLuint* selectBuf, GLint hits);
};

#endif /*DISPLAY_H_*/
