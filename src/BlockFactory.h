#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

#include "Display.h"
#include "Block2D.h"
#include "Block3D.h"
#include "Block2DText.h"
#include "Sky.h"
#include "Floor.h"
#include "Texture.h"
#include "Obj.h"

class BlockFactory
{
private:
	list<Texture> textures;
	list<Obj> objects;
	list<Block3D> blocks3d;
	list<Block2D> blocks2d;
	list<Block2DText> blocks2dtext;
	Floor floor;
	Sky sky;
	Display* d;
	Texture* new_texture(string file);
	Obj* new_obj(string file);
public:
	void set_display(Display* d);
	Block3D* new_block3d(string object, string texture);
	Block3D* new_character(string object, string texture);
	Block2D* new_blockHUD(Vector2f size, string texture);
	Block2DText* new_blockText(Vector2f pos, Vector2f size, string text, string font);
	Floor* new_floor(string height_map, string texture, float scale);
	Sky* new_sky(string texture);

};

#endif
