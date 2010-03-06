/* The block factory has a selection of methods for creating and deleting
 * objects in the game world. It also keeps track of all the objects and
 * textures so they are not multiply loaded. Most of these methods are
 * designed just to be exported to lua to make it easier that end.
 */

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
	list<FIBITMAP*> texture_data;
	Floor floor;
	Sky sky;
	Display* d;
	Texture* new_texture(string file);
	bool load_texture(string filename_s, FIBITMAP *dib);
	Obj* new_obj(string file);
public:
	void set_display(Display* d);
	Block3D* new_block3d(string object, string texture); //standard 3d object
	Block3D* new_character(string object, string texture); //driven 3d object, see Block3D.h
	Block2D* new_blockHUD(Vector2f size, string texture); //2d block to appear as a hud item
	Block2DText* new_blockText(Vector2f pos, Vector2f size, string text, string font); //text on the hud
	Floor* new_floor(string height_map, string texture, float scale); //the floor
	Sky* new_sky(string texture); //the sky box (broken)
	Block3DImaginary* new_imaginary_block(Vector3f size); //collision box
	Block3DFlat* new_flat_block(string texture, Vector2f size, bool mask, bool transparent); //flat textured thing
	Block3DFlat* new_distance_block(string texture, Vector2f size); //flat textured thing that lies in the distance but we always want to draw regardless of how far away it is
	void remove_blockText(Block2DText* text);
	void remove_blockHUD(Block2D* hud);
	void remove_flat_block(Block3DFlat* block);
	void remove_3d_block(Block3D* block);
	void clear_all();

};

#endif
