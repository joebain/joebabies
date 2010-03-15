#include "Display.h"

#ifdef WIN32
#include <windows.h>
#endif

#include <iostream>
#include <fstream>

#include "Block3DFlat.h"

Display::Display()
{
	ifstream config_iss ("misc/config");
	if (config_iss.is_open())
	{
		config_iss >> noskipws;
		config_iss >> win_width >> ws >> win_height;
		config_iss >> ws >> win_name;
		config_iss >> ws >> win_icon;
		config_iss.close();
	}

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	
	SDL_WM_SetIcon(SDL_LoadBMP(("img/" + win_icon).c_str()), NULL);
	SDL_WM_SetCaption(win_name.c_str(), win_name.c_str());
	
	const SDL_VideoInfo *videoInfo = SDL_GetVideoInfo( );
	
	int videoFlags;
    /* the flags to pass to SDL_SetVideoMode */
    videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
    videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
    videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */

    /* This checks to see if surfaces can be stored in memory */
    if (videoInfo->hw_available)
		videoFlags |= SDL_HWSURFACE;
    else
		videoFlags |= SDL_SWSURFACE;

    /* This checks if hardware blits can be done */
    if (videoInfo->blit_hw)
		videoFlags |= SDL_HWACCEL;

    /* Sets up OpenGL double buffering */
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    /* get a SDL surface */
	int screen_bpp = 32;
    surface = SDL_SetVideoMode(win_width, win_height, screen_bpp, videoFlags);
	
	camera = new Camera();
	
	init();
}

void Display::update(float delta)
{
	if (buttons->req_fullscreen) {
		set_fullscreen();
		//cout << "setting fullscreen" << endl;
		buttons->req_fullscreen = false;
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	list<Block*>::iterator iter;
	
	//the light
	//~ glPushMatrix();
	//~ glColor3f(0,0,1);
	//~ glTranslatef(pos_light[0],pos_light[1],pos_light[2]);
	//~ glutSolidSphere(1,10,10);
	//~ glColor3f(1,1,1);
	//~ glPopMatrix();
	
    
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(45,win_ratio,near_vp,far_vp*1000);
	
	camera->move(delta);
	camera->position();
	
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT1, GL_POSITION, pos_light);
	
	//draw things which are far away
	//##############################
	if (bfac->has_sky()) {
		//cout << "displaying sky" << endl;
		bfac->get_sky()->display();
	}
	
	for( iter = bfac->distance_blocks.begin(); iter != bfac->distance_blocks.end(); ++iter ) {
		(*iter)->display();
	}
	
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	camera->position();
	
	glLightfv(GL_LIGHT1, GL_POSITION, pos_light);
	
	//draw solid normal things
	//########################
	glEnable(GL_CULL_FACE);
	
	if (bfac->has_floor()) {
		//cout << "displaying floor" << endl;
		bfac->get_floor()->display();
	}
	
	for( iter = bfac->blocks.begin(); iter != bfac->blocks.end(); ++iter ) {
		(*iter)->display();
	}
	
	glDisable(GL_CULL_FACE);
	
	//draw transparent things
	//#######################
	for( iter = bfac->transparent_blocks.begin(); iter != bfac->transparent_blocks.end(); ++iter ) {
		(*iter)->cam_dist = (*iter)->get_centre().dist_between(camera->get_pos());
	}
	bfac->transparent_blocks.sort(Display::depth_sort2);
	for( iter = bfac->transparent_blocks.begin(); iter != bfac->transparent_blocks.end(); ++iter ) {
		(*iter)->display();
	}
	
	//draw hud/gui things
	//###################
	glDisable(GL_LIGHTING);

	glLoadIdentity();
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	gluOrtho2D(0,win_width,0,win_height);
	
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glLoadIdentity();	
	
	glDisable(GL_DEPTH_TEST);
	
	for( iter = bfac->hud_blocks.begin(); iter != bfac->hud_blocks.end(); iter++ ) {
		(*iter)->display();
	}
	
	glEnable(GL_DEPTH_TEST);
	
	glPopMatrix();
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
    
	glFlush();
	
	SDL_GL_SwapBuffers( );
	
}

bool Display::depth_sort2(Block *one, Block* two) {
	if (one->cam_dist > two->cam_dist)
		return true;
	else
		return false;
}

bool Display::depth_sort(Block* one, Block* two)
{
	if (one->get_z_depth() > two->get_z_depth())
		return true;
	else
		return false;
}

Camera* Display::get_camera()
{
	return camera;
}

Block3DFlat* Display::pick()
{
	//cout << "picking" << endl;
	
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
	gluPickMatrix(buttons->mouse_x, win_height-buttons->mouse_y, 1.0, 1.0, view);
	gluPerspective(45,win_ratio,near_vp,far_vp);
	camera->position();
	
	//rendering
	//#########
	list<Block*>::iterator iter;
	//glEnable(GL_CULL_FACE);
	for( iter = bfac->blocks.begin(); iter != bfac->blocks.end(); ++iter ) {
		glLoadName((*iter)->get_name());
		(*iter)->display();
	}
	//glDisable(GL_CULL_FACE);
		
	//we can assume that for picking the camera hasn't moved since we rendered the scene so we don't need to compute distances or resort
	for( iter = bfac->transparent_blocks.begin(); iter != bfac->transparent_blocks.end(); ++iter ) {
		glLoadName((*iter)->get_name());
		(*iter)->display();
	}
		
	glMatrixMode(GL_PROJECTION);
 	glPopMatrix();
	
	hits = glRenderMode (GL_RENDER);
	//cout <<"hits: " << hits << endl;
	
	glMatrixMode(GL_MODELVIEW);
	
	if (hits > 0) {
		GLuint close_name = getClosestHit(selectBuf, hits);	
		return bfac->get_block3dflat_from_name(close_name);
	}
	
	return NULL;
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
    win_ratio = ((float)win_width)/((float)win_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    near_vp = 1;
	far_vp = 200;
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
	dif_light[3] = 1.0;
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
	
    glLightfv(GL_LIGHT1, GL_AMBIENT, amb_light);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, dif_light);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, spec_light);
    glLightfv(GL_LIGHT1, GL_POSITION, pos_light);
    
    glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	
	glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
	
	glAlphaFunc(GL_GREATER, 0.1);
    glEnable(GL_ALPHA_TEST);

}

void Display::set_fullscreen()
{
	SDL_WM_ToggleFullScreen(surface);
	SDL_ShowCursor(SDL_DISABLE);
}

Vector3f Display::project_xy(int x, int y, float z) {
	GLdouble x1, y1, z1;
	
	int viewport[4];
    double mvmatrix[16];
    double projmatrix[16];
    
	glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
		
	float win_z;
	glReadPixels(x, win_height-y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &win_z);
	gluUnProject(x, win_height-y, win_z, mvmatrix, projmatrix, viewport, &x1, &y1, &z1);

	//why is x the wrong way round? i dont know. why is my code always filled with random shit like this? it makes me sad :(
	//also why is the z of the object different from the z i get back? the mysteries of life. hmrph!
	return Vector3f(-x1,y1,z);
}

