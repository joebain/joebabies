#include "Display.h"

#ifdef WIN32
#include <windows.h>
#endif
#include <iostream>

#include <GL/glu.h>
#include <GL/glut.h>

#include "Main.h"


Display::Display(int argc, char** argv)
{	
	glutInit (&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowPosition (50, 50);
	win_width = 600;
	win_height = 400;
	glutInitWindowSize (win_width, win_height);
	glutCreateWindow ("Joebabies");

    glutDisplayFunc (call_update);
    glutKeyboardFunc(call_keys);
	glutSpecialFunc(call_s_keys);
	glutSpecialUpFunc(call_s_keys_up);
	glutMouseFunc(call_mouse);
	glutMotionFunc(call_active_mouse);
	glutReshapeFunc(call_resize);
	
	camera = new Camera();

}

void Display::update()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(45,win_ratio,near_vp,far_vp*100);
    
	camera->position();
	
	if (sky != NULL) sky->display();
	
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	camera->position();
	
	glEnable(GL_LIGHTING);
	
	glLightfv(GL_LIGHT1, GL_POSITION, pos_light);
	
	glPushMatrix();
	glColor3f(0,0,1);
	glTranslatef(pos_light[0],pos_light[1],pos_light[2]);
	glutSolidSphere(1,10,10);
	glColor3f(1,1,1);
	glPopMatrix();
	
    if (pick_flag) {
    	//cout << "tracing\n";
    	
    }
    else {
    	//cout << "drawing " << blocks.size() << " blocks" << endl;
		if (floor != NULL) floor->display();
		list<Block*>::iterator iter;
		for( iter = blocks.begin(); iter != blocks.end(); iter++ ) {
			(*iter)->display();
		}
    	
    }
	
	glDisable(GL_LIGHTING);
	
	glLoadIdentity();
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	gluOrtho2D(0,win_width,0,win_height);
	
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glLoadIdentity();
	
	//~ glLineWidth(5);
	//~ glColor3f(1.0,0.0,0.0);
	//~ glBegin(GL_LINES);
	//~ 
	//~ glVertex3f(0,0,1);
	//~ glVertex3f(0,20,1);
	//~ glVertex3f(20,0,1);
	//~ glVertex3f(win_width,win_height,1);
	//~ 
	//~ glEnd();
	//~ glColor3f(1.0,1.0,1.0);
	
	
	glDisable(GL_DEPTH_TEST);
	
	list<Block*>::iterator iter;
	for( iter = hud_blocks.begin(); iter != hud_blocks.end(); iter++ ) {
		(*iter)->display();
	}
	
	glEnable(GL_DEPTH_TEST);
	
	glPopMatrix();
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	
	
	glFlush();
	
    glutSwapBuffers();
	
}

Camera* Display::get_camera()
{
	return camera;
}

void Display::translate(Vector3f t)
{
	tra += t;
}

void Display::rotate(Vector3f r)
{
	rot += r;
}

void Display::pick()
{
	cout << "picking" << endl;
	
	GLint hits, view[4];
	GLuint selectBuf[BUFSIZE];

	glSelectBuffer (BUFSIZE, selectBuf);
	
	glGetIntegerv(GL_VIEWPORT, view);
	
	glRenderMode (GL_SELECT);
	
	glInitNames();
	
    glPushName(0);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	
	gluPickMatrix(mouse_x, win_height-mouse_y, 1.0, 1.0, view);	
	
	gluPerspective(45,win_ratio,near_vp,far_vp);
		
	
	glMatrixMode(GL_MODELVIEW);
	
	glutSwapBuffers();
	
	pick_flag = 1;
	update();
	pick_flag = 0;
	
	glMatrixMode(GL_PROJECTION);
 	glPopMatrix();
	
	hits = glRenderMode (GL_RENDER);
	cout <<"hits: " << hits << endl;
	
	glMatrixMode(GL_MODELVIEW);
	
	if (hits > 0) {
		GLuint close_name = getClosestHit(selectBuf, hits);	
	}
}

GLuint Display::getClosestHit(GLuint* selectBuf, GLint hits)
{
	int i, j, num_names, sb_ptr = 0;
	GLuint close_name, min_depth = 0xffffffff;
	for (i = 0 ; i < hits ; i++) {
		num_names = selectBuf[sb_ptr++];
		if (selectBuf[sb_ptr] < min_depth) {
			min_depth = selectBuf[sb_ptr];
			sb_ptr += 2; // +2 to get to the first name
			close_name = selectBuf[sb_ptr];
			//cout << "at ptr: " << sb_ptr << " new min depth: " << min_depth << " name: " << close_name << endl;
		} else {
			sb_ptr += 2;	
		}
		for (j = 0; j < num_names ; j++) sb_ptr++; // now go past all the names (there should only be one but hey)
	}
	return close_name;
}

void Display::init()
{
	//set bg colour
    glClearColor (0.0, 0.0, 0.0, 0.0);
    
    //ensure depth is drawn properly
    glEnable(GL_DEPTH_TEST);
	
	//glShadeModel(GL_FLAT);
	
	//glEnable(GL_LINE_SMOOTH);
	//glEnable(GL_POLYGON_SMOOTH);
    
    //set the view
    win_ratio = ((float)win_height)/((float)win_width);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    near_vp = 1;
	far_vp = 100;
	gluPerspective(45,win_ratio,near_vp,far_vp);
	
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	//init light
	amb_light[0] = 2.5;
	amb_light[1] = 2.5;
	amb_light[2] = 2.5;
	amb_light[3] = 1.0;
	dif_light[0] = 1.0;
	dif_light[1] = 1.0;
	dif_light[2] = 1.0;
	dif_light[3] = 0.5;
	pos_light[0] = 17.0;
	pos_light[1] = 10.0;
	pos_light[2] = 10.0;
	pos_light[3] = 0.0;
	/*
	spec_light[0] = 0.5f;
	spec_light[1] = 0.5f;
	spec_light[2] = 0.5f;
	spec_light[3] = 1.0f;
	*/
	pick_flag = 0;
	mouse_down = 0;

    glLightfv(GL_LIGHT1, GL_AMBIENT, amb_light);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, dif_light);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, spec_light);
    glLightfv(GL_LIGHT1, GL_POSITION, pos_light);
    
    glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	
    glEnable(GL_TEXTURE_2D);
}

void Display::keys(unsigned char key, int x, int y)
{
	float light_move = 1.0;
	
	switch(key) {
		case 'q':
		pos_light[0] += light_move;
		cout << "light at " << pos_light[0] << "," << pos_light[1] << "," << pos_light[2] << endl;
		break;
		case 'w':
		pos_light[0] -= light_move;
		cout << "light at " << pos_light[0] << "," << pos_light[1] << "," << pos_light[2] << endl;
		break;
		case 'a':
		pos_light[1] += light_move;
		cout << "light at " << pos_light[0] << "," << pos_light[1] << "," << pos_light[2] << endl;
		break;
		case 's':
		pos_light[1] -= light_move;
		cout << "light at " << pos_light[0] << "," << pos_light[1] << "," << pos_light[2] << endl;
		break;
		case '1':
		pos_light[2] += light_move;
		cout << "light at " << pos_light[0] << "," << pos_light[1] << "," << pos_light[2] << endl;
		break;
		case '2':
		pos_light[2] -= light_move;
		cout << "light at " << pos_light[0] << "," << pos_light[1] << "," << pos_light[2] << endl;
		break;
		case '[':
		
		break;
		case ']':
		
		break;
		case 'i':
		
		break;
	}
}

void Display::s_keys(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_UP:
		buttons->up = true;
		break;
		case GLUT_KEY_DOWN:
		buttons->down = true;
		break;
		case GLUT_KEY_RIGHT:
		buttons->right = true;
		break;
		case GLUT_KEY_LEFT:
		buttons->left = true;
		break;
		case GLUT_KEY_PAGE_UP:
		
		break;
		case GLUT_KEY_PAGE_DOWN:
		
		break;
	}
}

void Display::s_keys_up(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_UP:
		buttons->up = false;
		break;
		case GLUT_KEY_DOWN:
		buttons->down = false;
		break;
		case GLUT_KEY_RIGHT:
		buttons->right = false;
		break;
		case GLUT_KEY_LEFT:
		buttons->left = false;
		break;
		case GLUT_KEY_PAGE_UP:
		
		break;
		case GLUT_KEY_PAGE_DOWN:
		
		break;
	}
}

void Display::mouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			mouse_x = x;
			mouse_y = y;
			if (!mouse_down) {
	
			}
			//pick();			
		}
		else if (state == GLUT_UP) {
			mouse_down = false;
		}
	} else if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN) {
			
		}
	}
	
}

void Display::activeMouse(int x, int y)
{
	
}

void Display::resizeWindow(int w, int h)
{
	win_width = w;
	win_height = h;
	
	glViewport(0, 0, w, h);
	
	win_ratio = ((float)w)/((float)h);
	
	//set the view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(45,win_ratio,near_vp,far_vp);
	
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

Display::~Display()
{
}
