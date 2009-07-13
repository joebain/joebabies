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
	
	w = new World(d);
	
	Block* b1 = w->new_block("block.obj","red_block.bmp");
	Vector3f *v1 = new Vector3f(1.2,0,-5);
	b1->move(*v1);
	
	Block* b2 = w->new_block("block.obj","blue_block.bmp");
	Vector3f *v2 = new Vector3f(-1.2,0,-5);
	b2->move(*v2);
	
	cout << "Entering main loop\n";
	
	glutTimerFunc(30,&call_timer,0);
	
	glutMainLoop();

	return 0;
}

void start()
{
	char* argv[] = {"start"};
	
	d = new Display(1, argv);
	
	w = new World(d);
	/*
	Block* b = w->new_block("block.obj","red_block.bmp");
	Vector3f *v = new Vector3f(1.2,0,-5);
	b->move(*v);
	
	Block* b2 = w->new_block("block.obj","blue_block.bmp");
	Vector3f *v2 = new Vector3f(-1.2,0,-5);
	b2->move(*v2);
	*/
	cout << "Using Lua eh, you fucking cunt?!?!?\n";
	
	glutTimerFunc(30,&call_timer,0);
	
	pthread_t thread1;
	pthread_create( &thread1, NULL, &threadFunc1, NULL);
}

void *threadFunc1(void*) {
	glutMainLoop();
	return NULL;
}

World* get_world()
{
	return w;
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
