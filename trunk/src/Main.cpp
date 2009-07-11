#include "Main.h"

#include <iostream>
#include <GL/glut.h>
#include <pthread.h>

#include "Display.h"
#include "World.h"
#include "ModelLoader.h"
#include "Obj.h"
#include "Texture.h"

Display *d;
World *w;

int main (int argc, char** argv)
{
	d = new Display(argc, argv);
	
	/*
	ModelLoader m;
	
	Obj red_block_o;
	red_block_o.set_name("Red block");
	Block red_block;
	Texture red_tex;
	m.load_obj("obj/block.obj",&red_block_o);
	red_tex.load("img/red_block.bmp");
	red_block_o.texture = &red_tex;
	red_block.set_obj(&red_block_o);
	*/
	
	w = new World(d);
	
	//w->add_block(&red_block);
	w->new_block("block.obj","blue_block.bmp");
	
	cout << "Entering main loop\n";
	
	glutTimerFunc(30,&call_timer,0);
	
	glutMainLoop();
	
	return 0;
}

void *threadFunc1(void*) {
	w->main_loop();
	return NULL;
}

void call_update()
{
	d->update();
}

void call_keys(unsigned char key, int x, int y)
{
	d->keys(key,x,y);
}

void call_s_keys(int key, int x, int y)
{
	d->s_keys(key,x,y);
}

void call_mouse(int button, int state, int x, int y)
{
	d->mouse(button,state,x,y);
}

void call_active_mouse(int x, int y)
{
	d->activeMouse(x,y);	
}

void call_resize(int w, int h)
{
	d->resizeWindow(w,h);
}

void call_timer(int v)
{
	w->main_loop();
	glutTimerFunc(30,&call_timer,0);
}
