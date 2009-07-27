#include "World.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <luabind/luabind.hpp>
#include <luabind/object.hpp>

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <time.h>
#include <math.h>
#include <vector>



World::World(Display *d, lua_State *l)
{
	this->d = d;	
	d->init();
	
	this->l = l;
	
	time.get_time();
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
	
	blocks3d.push_back(new_block);
	
	//check if this texture has already been loaded
	bool found_texture = false;
	list<Texture>::iterator t_iter;
	for( t_iter = textures.begin(); t_iter != textures.end(); t_iter++ ) {
		if (new_tex == *t_iter) {
			blocks3d.back().set_tex(&(*t_iter));
			found_texture = true;
			break;
		}
	}
	if (!found_texture) {
		textures.push_back(new_tex);
		blocks3d.back().set_tex(&(textures.back()));
	}

	//check if this object has already been loaded
	bool found_object = false;
	list<Obj>::iterator o_iter;
	for( o_iter = objects.begin(); o_iter != objects.end(); o_iter++ ) {
		if (new_obj == *o_iter) {
			blocks3d.back().set_obj(&(*o_iter));
			found_object = true;
			break;
		}
	}
	if (!found_object) {
		objects.push_back(new_obj);
		blocks3d.back().set_obj(&(objects.back()));
	}
	
	d->blocks.push_back(&(blocks3d.back()));

	return &(blocks3d.back());

}

Block2D* World::new_blockHUD(Vector2f size, string texture)
{
	Block2D new_block;
	Texture new_tex;
	new_tex.load("img/" + texture);
	
	blocks2d.push_back(new_block);
	
	//check if this texture has already been loaded
	bool found_texture = false;
	list<Texture>::iterator t_iter;
	for( t_iter = textures.begin(); t_iter != textures.end(); t_iter++ ) {
		if (new_tex == *t_iter) {
			blocks2d.back().set_tex(&(*t_iter));
			found_texture = true;
			break;
		}
	}
	if (!found_texture) {
		textures.push_back(new_tex);
		blocks2d.back().set_tex(&(textures.back()));
	}
	
	blocks2d.back().set_size(size);
	blocks2d.back().set_depth(1);
	
	d->hud_blocks.push_back(&(blocks2d.back()));

	return &(blocks2d.back());
}

Floor* World::new_floor(string height_map, string texture, float scale)
{
	Obj new_obj;
	Texture new_tex;
	Vector2i size = new_obj.load_heightmap(height_map, scale);
	new_tex.load("img/" + texture);
	
	floor.set_perm_obj(new_obj);
	floor.set_scale(scale);
	floor.set_size(size);
	
	//check if this texture has already been loaded
	bool found_texture = false;
	list<Texture>::iterator t_iter;
	for( t_iter = textures.begin(); t_iter != textures.end(); t_iter++ ) {
		if (new_tex == *t_iter) {
			floor.set_tex(&(*t_iter));
			found_texture = true;
			break;
		}
	}
	if (!found_texture) {
		textures.push_back(new_tex);
		floor.set_tex(&(textures.back()));
	}
	
	d->floor = &floor;
	return &floor;
}

Sky* World::new_sky(string texture)
{
	Texture new_tex;
	new_tex.load("img/" + texture);
	
	//check if this texture has already been loaded
	bool found_texture = false;
	list<Texture>::iterator t_iter;
	for( t_iter = textures.begin(); t_iter != textures.end(); t_iter++ ) {
		if (new_tex == *t_iter) {
			sky.set_tex(&(*t_iter));
			found_texture = true;
			break;
		}
	}
	if (!found_texture) {
		textures.push_back(new_tex);
		sky.set_tex(&(textures.back()));
	}
	
	d->sky = &sky;
	return &sky;
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
