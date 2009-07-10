#include "Main.h"

#include <iostream>
#include <GL/glut.h>
#include <pthread.h>

#include "Display.h"
#include "ModelLoader.h"
#include "Obj.h"
#include "Texture.h"
#include "Snake.h"

Display *d;
World w;

int main (int argc, char** argv)
{
	d = new Display(argc, argv);
	
	ModelLoader m;
	
	Obj red_block_o;
	red_block_o.set_name("Red block");
	Block red_block;
	Texture red_tex;
	m.load_obj("obj/block.obj",&red_block_o);
	red_tex.load("img/red_block.bmp");
	red_block_o.texture = &red_tex;
	red_block.set_obj(&red_block_o);
	red_block.type = red_block.PLAIN;
	
	Obj blue_block_o = red_block_o;
	blue_block_o.set_name("Blue block");
	Block blue_block;
	Texture blue_tex;
	//m.load_obj("block.obj",&blue_block_o);
	blue_tex.load("img/blue_block.bmp");
	blue_block_o.texture = &blue_tex;
	blue_block.set_obj(&blue_block_o);
	blue_block.type = blue_block.T_LEFT;
	
	Obj green_block_o = red_block_o;
	green_block_o.set_name("Green block");
	Block green_block;
	Texture green_tex;
	//m.load_obj("block.obj",&blue_block_o);
	green_tex.load("img/green_block.bmp");
	green_block_o.texture = &green_tex;
	green_block.set_obj(&green_block_o);
	green_block.type = green_block.T_RIGHT;
	
	Obj clear_block_o = blue_block_o;
	clear_block_o.set_name("Clear block");
	Block clear_block;
	Texture clear_tex;
	//m.load_obj("block.obj",&blue_block_o);
	clear_tex.load("img/clear_block.bmp");
	clear_block_o.texture = &clear_tex;
	clear_block_o.setClear();
	clear_block.set_obj(&clear_block_o);
	
	Obj snake_head;
	snake_head.set_name("Snake head");
	m.load_obj("obj/head.obj",&snake_head);
	Texture head_tex;
	head_tex.load("img/head.bmp");
	snake_head.texture = &head_tex;
	Obj snake_body;
	snake_body.set_name("Snake body");
	m.load_obj("obj/body.obj",&snake_body);
	Texture body_tex;
	body_tex.load("img/body.bmp");
	snake_body.texture = &body_tex;
	Obj snake_tail;
	snake_tail.set_name("Snake tail");
	m.load_obj("obj/tail.obj",&snake_tail);
	Texture tail_tex;
	tail_tex.load("img/tail.bmp");
	snake_tail.texture = &tail_tex;
	
	Snake snake;
	snake.head = &snake_head;
	snake.body = &snake_body;
	snake.tail = &snake_tail;
		
	cout << "loading world\n";

	w.red_block = &red_block;
	w.blue_block = &blue_block;
	w.green_block = &green_block;
	w.clear_block = &clear_block;
	w.snake = &snake;
	
	Texture floor_tex;
	floor_tex.load("img/floor.bmp");
	w.floor_tex = &floor_tex;

	w.load("poop");
		
	cout << "initialising display\n";
	
	d->init(&w);
	
	cout << "Entering main loop\n";
	
	//pthread_t thread1;
	glutTimerFunc(30,&call_timer,0);
	//pthread_create( &thread1, NULL, &threadFunc1, NULL);
	//pthread_create( &thread2, NULL, &threadFunc2, NULL);
	glutMainLoop();
	
	//pthread_join( thread2, NULL);
	//pthread_join( thread1, NULL);
	
	return 0;
}

void *threadFunc1(void*) {
	w.main_loop();
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
	w.main_loop();
	glutTimerFunc(30,&call_timer,0);
}
