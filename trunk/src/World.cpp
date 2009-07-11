#include "World.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include <vector>

#include "Block.h"

World::World(Display *d)
{
	this->d = d;
	d->init();
	
	L = lua_open();
	
	luaL_openlibs(L);
	
	//run_lua("test.lua");

}

World::~World()
{
	lua_close(L);
}

void World::add_block(Block* b)
{
	//d->blocks.push_back(*b);
	
	//objects.push_back(b->get_obj());
}

Block* World::new_block(string object, string texture)
{
	Block new_block;
	Obj new_obj;
	Texture new_tex;
	new_obj.load("obj/" + object);
	new_tex.load("img/" + texture);
	
	//check if this texture has already been loaded
	bool found_texture = false;
	vector<Texture>::iterator t_iter;
	for( t_iter = textures.begin(); t_iter != textures.end(); t_iter++ ) {
		if (new_tex == *t_iter) {
			new_obj.texture = &(*t_iter);
			found_texture = true;
		}
	}
	if (!found_texture) {
		//new_obj.texture = &new_tex;
		textures.push_back(new_tex);
		new_obj.texture = &(textures.back());
	}

	//check if this object has already been loaded
	bool found_object = false;
	vector<Obj>::iterator o_iter;
	for( o_iter = objects.begin(); o_iter != objects.end(); o_iter++ ) {
		if (new_obj == *o_iter) {
			new_block.set_obj(&(*o_iter));
			found_object = true;
		}
	}
	if (!found_object) {
		//new_block.set_obj(&new_obj);
		objects.push_back(new_obj);
		new_block.set_obj(&(objects.back()));
	}

	d->blocks.push_back(new_block);

	return &(d->blocks.back());

}

Block* World::get_blocks()
{
	return &(d->blocks[0]);
}

int World::num_blocks()
{
	return d->blocks.size();
}

void World::main_loop()
{
		Vector3f move;
		float delta = 0.2;
		if (d->key_up) {
			move.z = delta;
		} else if (d->key_down) {
			move.z = -delta;
		}
		if (d->key_left) {
			move.x = delta;
		} else if (d->key_right) {
			move.x = -delta;
		}
		d->reset_keys();
		//d->blocks.back().move(move);

		


		glutPostRedisplay();
}

void World::run_lua(string file)
{
	string l_file = "lua/"+file;
	int s = luaL_loadfile(L, l_file.c_str());
	if (s==0) { //if no errors loading file
		// execute Lua program
		s = lua_pcall(L, 0, LUA_MULTRET, 0);
	} else {
		cout << "unable to run file" << endl;
	}
	
	if ( s!=0 ) {
		cerr << "-- " << lua_tostring(L, -1) << endl;
		lua_pop(L, 1); // remove error message
	}
}
