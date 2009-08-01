#include "World.h"

#ifdef WIN32
#include <windows.h>
#endif
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <vector>

#include <GL/glut.h>

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <luabind/luabind.hpp>
#include <luabind/object.hpp>

World::World(Display *d, lua_State *l)
{
	this->d = d;	
	d->init();
	
	this->l = l;
	
	bf.set_display(d);
	
	time.get_time();
}

World::~World()
{
}

void World::main_loop()
{	
	Vector3f move, view;
	if (d->key_up) {
		if (up != NULL)
			up->call();
		else
			move.z = 0.2;
	}
	if (d->key_down) {
		if (down != NULL)
			down->call();
		else
			move.z = -0.2;
	}
	if (d->key_left) {
		if (left != NULL)
			left->call();
		else
			view.y = -5;
	}
	if (d->key_right) {
		if (right != NULL)
			right->call();
		else
			view.y = 5;
	}
	d->reset_keys();
	d->translate(move);
	d->rotate(view);
	
	try {
		//call a lua function
		luabind::call_function<void>(l, "step",time.time_since_last());
	} catch(const std::exception &TheError) {
		cerr << TheError.what() << endl;
		cerr << lua_tostring(l, -1) << endl;
	}
	
	glutPostRedisplay();
}

Display* World::get_display()
{
	return d;
}

BlockFactory* World::get_block_factory()
{
	return &bf;
}

void World::reg_key_left(Controller* c)
{
	left = c;
	c->set_lua(l);
}

void World::reg_key_right(Controller* c)
{
	right = c;
	c->set_lua(l);
}

void World::reg_key_up(Controller* c)
{
	up = c;
	c->set_lua(l);
}

void World::reg_key_down(Controller* c)
{
	down = c;
	c->set_lua(l);
}
