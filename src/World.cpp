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

#include "Block.h"


World::World(Display *d, lua_State *l)
{
	this->d = d;	
	d->init();
	
	this->l = l;
}

World::~World()
{
}

Block* World::new_block(string object, string texture)
{
	cout << "adding a new block" << endl;
	
	Block new_block;
	Obj new_obj;
	Texture new_tex;
	new_obj.load("obj/" + object);
	new_tex.load("img/" + texture);
	
	cout << "checking for duplicates" << endl;
	
	//check if this texture has already been loaded
	bool found_texture = false;
	list<Texture>::iterator t_iter;
	int i = 0;
	cout << "checking... ";
	for( t_iter = textures.begin(); t_iter != textures.end(); t_iter++ ) {
		cout << i;
		if (new_tex == *t_iter) {
			new_block.set_tex(&(*t_iter));
			found_texture = true;
			cout << endl << "found the same texture" << endl;
			break;
		}
		i++;
	}
	if (!found_texture) {
		cout << endl << "didnt find the same texture" << endl;
		textures.push_back(new_tex);
		cout << "settting texture" << endl;
		new_block.set_tex(&(textures.back()));
	}

	//check if this object has already been loaded
	bool found_object = false;
	list<Obj>::iterator o_iter;
	i = 0;
	cout << "checking... ";
	for( o_iter = objects.begin(); o_iter != objects.end(); o_iter++ ) {
		cout << i;
		if (new_obj == *o_iter) {
			new_block.set_obj(&(*o_iter));
			found_object = true;
			cout << endl << "found the same object" << endl;
			break;
		}
		i++;
	}
	if (!found_object) {
		objects.push_back(new_obj);
		new_block.set_obj(&(objects.back()));
		cout << endl << "didnt find the same object" << endl;
	}

	d->blocks.push_back(new_block);

	cout << "added a new block" << endl;

	return &(d->blocks.back());

}

void World::main_loop()
{	
	Vector3f move, view;
	if (d->key_up) {
		move.z = 0.2;
	} else if (d->key_down) {
		move.z = -0.2;
	}
	if (d->key_left) {
		view.y = -5;
	} else if (d->key_right) {
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
