/* The block factory has a selection of methods for creating and deleting
 * objects in the game world. It also keeps track of all the objects and
 * textures so they are not multiply loaded. Most of these methods are
 * designed just to be exported to lua to make it easier that end.
 */

#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <map>

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
protected:
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
	bool sky_exists;
	bool floor_exists;
	
	Texture* new_texture(string file);
	bool load_texture(string filename_s, FIBITMAP *dib);
	Obj* new_obj(string file);
	int new_name;
	map<int, Block3D*> names_to_blocks3d;
	map<int, Block3DFlat*> names_to_blocks3dflat;
public:
	BlockFactory();
	Sky* get_sky() { return &sky; }
	Floor* get_floor() { return &floor; }
	bool has_sky() { return sky_exists; }
	bool has_floor() { return floor_exists; }
	
	list<Block*> blocks;
	list<Block*> transparent_blocks;
	list<Block*> distance_blocks;
	list<Block*> hud_blocks;
	
	Block3D* new_block3d(string object, string texture); //standard 3d object
	Block3D* new_character(string object, string texture); //driven 3d object, see Block3D.h
	Block2D* new_blockHUD(Vector2f size, string texture); //2d block to appear as a hud item
	Block2DText* new_blockText(Vector2f pos, Vector2f size, string text, string font); //text on the hud
	Floor* new_floor(string height_map, string texture, float scale); //the floor
	Sky* new_sky(string texture); //the sky box (broken)
	Block3DImaginary* new_imaginary_block(Vector3f size); //collision box
	Block3DFlat* new_flat_block(string texture, Vector2f size, bool mask, bool transparent); //flat textured thing
	Block3DFlat* new_animated_flat_block(string texture, Vector2f size, Vector2f frame_size, int width, int height, list<float> times, bool mask, bool transparent, bool bounce);
	Block3DFlat* new_distance_block(string texture, Vector2f size); //flat textured thing that lies in the distance but we always want to draw regardless of how far away it is
	void remove_blockText(Block2DText* text);
	void remove_blockHUD(Block2D* hud);
	void remove_flat_block(Block3DFlat* block);
	void remove_3d_block(Block3D* block);
	void clear_all();
	Block3D* get_block3d_from_name(int name) { map<int, Block3D*>::iterator i = names_to_blocks3d.find(name); return i == names_to_blocks3d.end() ? NULL : i->second; }
	Block3DFlat* get_block3dflat_from_name(int name) { map<int, Block3DFlat*>::iterator i = names_to_blocks3dflat.find(name); return i == names_to_blocks3dflat.end() ? NULL : i->second; }

	//luabind madness
	Block3DFlat* new_animated_flat_block_lua(string texture, Vector2f size, Vector2f frame_size, int width, int height, luabind::object const& times, bool mask, bool transparent, bool bounce) {
		list<float> list_times;
		for (luabind::iterator it(times) , end ; it != end ; ++it) {
			list_times.push_back(luabind::object_cast<float>(*it));
		}
		return new_animated_flat_block(texture, size, frame_size, width, height, list_times, mask, transparent, bounce);
	}
};

#endif
