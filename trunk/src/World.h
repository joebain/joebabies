#ifndef WORLD_H_
#define WORLD_H_

#include "Display.h"
#include "Vector3f.h"
#include "Block.h"
#include "Obj.h"
#include "Texture.h"

#include <vector>
#include <time.h>

class World
{
private:
	bool running;
	Display* d;
	Vector3f rot, tran;
	vector<Texture> textures;
	vector<Obj> objects;
public:
	World(Display *d);
	virtual ~World();
	void main_loop();
	void add_block(Block* b);
	void new_block(string object, string texture);
	Block* get_blocks();
	int num_blocks();
};

#endif /*WORLD_H_*/
