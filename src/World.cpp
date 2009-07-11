#include "World.h"

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
	cout << "size before: " << objects.size() << ", " << textures.size() << endl;
	objects.resize(10);
	textures.resize(10);
	cout << "size after: " << objects.size() << ", " << textures.size() << endl;
}

World::~World()
{
	
}

void World::add_block(Block* b)
{
	//d->blocks.push_back(*b);
	
	//objects.push_back(b->get_obj());
}

void World::new_block(string object, string texture)
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
			move.x = delta;
		} else if (d->key_down) {
			move.x = -delta;
		}
		if (d->key_left) {
			move.z = delta;
		} else if (d->key_right) {
			move.z = -delta;
		}
		d->reset_keys();
		d->blocks.back().move(move);
		d->blocks.back().get_pos().print();
		cout << endl;
		
		glutPostRedisplay();
}
