#include "Display.h"

#include "Main.h"

#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>

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
	glutMouseFunc(call_mouse);
	glutMotionFunc(call_active_mouse);
	glutReshapeFunc(call_resize);

}

void Display::update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    
    
    if (pick_flag) {
    	//cout << "tracing\n";
    	
    }
    else {
    	//cout << "drawing\n";
		vector<Block>::iterator iter;
		for( iter = blocks.begin(); iter != blocks.end(); iter++ ) {
			iter->get_obj()->display();
		}
    	
    }
	
	glFlush();
	
    glutSwapBuffers();
	
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
	
	gluPerspective(45,win_ratio,near,far);
		
	
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
    glClearColor (1.0, 1.0, 1.0, 0.0);
    
    //ensure depth is drawn properly
    //glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    
    //glShadeModel(GL_FLAT);
    
    //set the view
    win_ratio = ((float)win_height)/((float)win_width);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    near = 1;
	far = 100;
	gluPerspective(45,win_ratio,near,far);
	
	cout << "set ratio to " << win_ratio << endl;
	
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	//init light
	amb_light[0] = 0.5;// = { 0.5f, 0.5f, 0.5f, 1.0f };
	amb_light[1] = 0.5;
	amb_light[2] = 0.5;
	amb_light[3] = 1.0;
	dif_light[0] = 1.0;//{ 1.0f, 1.0f, 1.0f, 1.0f };
	dif_light[1] = 1.0;
	dif_light[2] = 1.0;
	dif_light[3] = 1.0;
	pos_light[0] = 0.3;//{ 0.3f, 1.0f, 3.0f, 1.0f };
	pos_light[1] = 1.0;
	pos_light[2] = 3.0;
	pos_light[3] = 1.0;
	
	/*
	rot_degs_x = 45;
	rot_degs_y = 0;
	z_trans = -30;
	x_trans = 0;
	y_trans = 0;
	*/
	
	pick_flag = 0;
	mouse_down = 0;

    glLightfv(GL_LIGHT1, GL_AMBIENT, amb_light);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, dif_light);
    glLightfv(GL_LIGHT1, GL_POSITION, pos_light);
    
    glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	
    glEnable(GL_TEXTURE_2D);
}

void Display::keys(unsigned char key, int x, int y)
{
	switch(key) {
		case 'q':
		
		break;
		case 'w':
		
		break;
		case 'a':
		
		break;
		case 's':
		
		break;
		case '1':
		
		break;
		case '2':
		
		break;
		case '[':
		
		break;
		case ']':
		
		break;
		case 'i':
		
		break;
	}
	
	glutPostRedisplay();
}

void Display::s_keys(int key, int x, int y)
{
	
	switch (key) {
		case GLUT_KEY_UP:
		key_up = true;
		break;
		case GLUT_KEY_DOWN:
		key_down = true;
		break;
		case GLUT_KEY_RIGHT:
		key_right = true;
		break;
		case GLUT_KEY_LEFT:
		key_left = true;
		break;
		case GLUT_KEY_PAGE_UP:
		
		break;
		case GLUT_KEY_PAGE_DOWN:
		
		break;
	}

	glutPostRedisplay();
}

void Display::reset_keys()
{
	key_up = false;
	key_down = false;
	key_left = false;
	key_right = false;
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
	gluPerspective(45,win_ratio,near,far);
	
	cout << "set ratio to " << win_ratio << endl;
	
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

Display::~Display()
{
}
