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
//#include "Vector3f_wrap.cxx"

World::World(Display *d)
{
	this->d = d;
	d->init();
	
	L = lua_open();
	
	luaL_openlibs(L);
	
	//luaL_dofile(L,"lua/vector.lua");
	//send_vector();
	//run_lua("test.lua");
	
	//luaL_dofile(L,"lua/grind.lua");

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

list<Block>* World::get_blocks()
{
	return &(d->blocks);
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
	d->translate(move);
	
	//call a lua function	
	/*
	lua_getglobal(L, "daily_grind");
	lua_pushnumber(L, 1); //this will be a 'time passed' float eventually
	lua_call(L, 1, 0);
	*/
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

Display* World::get_display()
{
	return d;
}

void World::send_vector()
{
	lua_getglobal(L, "number");
	lua_pushnumber(L, 5);
	lua_call(L, 1, 0);

	lua_getglobal(L, "number");
	lua_pushnumber(L, 7);
	lua_call(L, 1, 0);

	//lua_getglobal(L, "vector");
	//Vector3f *v = new Vector3f();
	//SWIG_NewPointerObj(L,v,SWIGTYPE_p_Vector3f,1);
	//lua_setglobal (L, "v");
	//lua_call(L, 1, 0);
}
