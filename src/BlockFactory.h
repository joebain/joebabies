#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

#include "Display.h"
#include "Block2D.h"
#include "Block3D.h"
#include "Block2DText.h"
#include "Block3DImaginary.h"
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
	list<Block3DImaginary> blocks3dimag;
	list<Block3DFlat> blocks3dflat;
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
	Block3DImaginary* new_imaginary_block(Vector3f size);
	Block3DFlat* new_flat_block(string texture, Vector2f size, bool transparent);
	Block3DFlat* new_distance_block(string texture, Vector2f size);
	void remove_blockText(Block2DText* text);
	void remove_blockHUD(Block2D* hud);
	void clear_all();

};

#endif
