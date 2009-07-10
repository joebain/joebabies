#ifndef DISPLAY_H_
#define DISPLAY_H_

#define BUFSIZE 512

#include <GL/gl.h>
#include <GL/glu.h>

#include "World.h"
#include "Vector3i.h"
#include "Vector2i.h"

class Display
{
public:
	Display(int agrc, char** argv);
	void update();
	void pick();
	void init(World *w);
	virtual ~Display();
	void keys(unsigned char key, int x, int y);
	void s_keys(int key, int x, int y);
	void mouse(int button, int state, int x, int y);
	void activeMouse(int x, int y);
	void resizeWindow(int w, int h);
	//Vector3i picked;
private:
	World *w;
	float ratio;
	int win_width, win_height;
	int rot_degs_x, rot_degs_y;
	float near, far;
	float z_trans, y_trans, x_trans;
	Vector2i mouse_down_at;
	float amb_light[4];
	float dif_light[4];
	float pos_light[4];
	int mouse_x, mouse_y;
	bool pick_flag, mouse_down;
	GLuint getClosestHit(GLuint* selectBuf, GLint hits);
};

#endif /*DISPLAY_H_*/