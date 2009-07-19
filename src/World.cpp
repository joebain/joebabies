#include "World.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <luabind/luabind.hpp>

#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include <vector>

#include "Block3D.h"
#include "Controller.h"


World::World(Display *d, lua_State *l)
{
	this->d = d;	
	d->init();
	
	this->l = l;
}

World::~World()
{
}

Block3D* World::new_character(string object, string texture)
{
	Block3D* character = new_block3d(object, texture);
	character->set_driven();
	
	return character;
}

Block3D* World::new_block3d(string object, string texture)
{
	Block3D new_block;
	Obj new_obj;
	Texture new_tex;
	new_obj.load("obj/" + object);
	new_tex.load("img/" + texture);
	
	//check if this texture has already been loaded
	bool found_texture = false;
	list<Texture>::iterator t_iter;
	for( t_iter = textures.begin(); t_iter != textures.end(); t_iter++ ) {
		if (new_tex == *t_iter) {
			new_block.set_tex(&(*t_iter));
			found_texture = true;
			break;
		}
	}
	if (!found_texture) {
		textures.push_back(new_tex);
		new_block.set_tex(&(textures.back()));
	}

	//check if this object has already been loaded
	bool found_object = false;
	list<Obj>::iterator o_iter;
	for( o_iter = objects.begin(); o_iter != objects.end(); o_iter++ ) {
		if (new_obj == *o_iter) {
			new_block.set_obj(&(*o_iter));
			found_object = true;
			break;
		}
	}
	if (!found_object) {
		objects.push_back(new_obj);
		new_block.set_obj(&(objects.back()));
	}
	
	blocks3d.push_back(new_block);

	d->blocks.push_back(&(blocks3d.back()));

	return &(blocks3d.back());

}

Block2D* World::new_block2d(Vector2f size, string texture)
{
	Block2D new_block;
	Texture new_tex;
	new_tex.load("img/" + texture);
	
	//check if this texture has already been loaded
	bool found_texture = false;
	list<Texture>::iterator t_iter;
	for( t_iter = textures.begin(); t_iter != textures.end(); t_iter++ ) {
		if (new_tex == *t_iter) {
			new_block.set_tex(&(*t_iter));
			found_texture = true;
			break;
		}
	}
	if (!found_texture) {
		textures.push_back(new_tex);
		new_block.set_tex(&(textures.back()));
	}
	
	new_block.set_size(size);
	
	blocks2d.push_back(new_block);

	d->hud_blocks.push_back(&(blocks2d.back()));

	return &(blocks2d.back());
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
		luabind::call_function<void>(l, "step",1);
	} catch(const std::exception &TheError) {
		cerr << TheError.what() << endl;
	}
	
	glutPostRedisplay();
}

Display* World::get_display()
{
	return d;
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
