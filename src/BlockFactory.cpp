#include "BlockFactory.h"

Block3D* BlockFactory::new_character(string object, string texture)
{
	Block3D* character = new_block3d(object, texture);
	character->set_driven();
	
	return character;
}

Block3D* BlockFactory::new_block3d(string object, string texture)
{
	Block3D new_block(++new_name);
	
	blocks3d.push_back(new_block);
	
	names_to_blocks3d[new_name] = &(blocks3d.back());
	
	blocks3d.back().set_tex(new_texture(texture));

	blocks3d.back().set_obj(new_obj(object));
	
	blocks.push_back(&(blocks3d.back()));

	return &(blocks3d.back());

}

Block3DFlat* BlockFactory::new_flat_block(string texture, Vector2f size, bool mask, bool transparent)
{
	Block3DFlat new_block(++new_name);
	
	blocks3dflat.push_back(new_block);
	
	names_to_blocks3dflat[new_name] = &(blocks3dflat.back());
	
	if (mask) blocks3dflat.back().set_mask(true);
	if (transparent) blocks3dflat.back().set_transparent(true);
	
	blocks3dflat.back().set_tex(new_texture(texture));
	
	blocks3dflat.back().set_size(size);
	
	if (transparent || mask) transparent_blocks.push_back(&(blocks3dflat.back()));
	else blocks.push_back(&(blocks3dflat.back()));

	return &(blocks3dflat.back());

}

Block3DFlat* BlockFactory::new_animated_flat_block(string texture, Vector2f size, Vector2f frame_size, int width, int height, list<float> times, bool mask, bool transparent, bool bounce)
{
	Block3DFlat new_block(++new_name);
	
	blocks3dflat.push_back(new_block);
	
	names_to_blocks3dflat[new_name] = &(blocks3dflat.back());
	
	if (mask) blocks3dflat.back().set_mask(true);
	if (transparent) blocks3dflat.back().set_transparent(true);
	
	blocks3dflat.back().set_tex(new_texture(texture));
	blocks3dflat.back().set_size(size);
	blocks3dflat.back().set_animation(frame_size, width, height, times, bounce);
	
	if (transparent || mask) transparent_blocks.push_back(&(blocks3dflat.back()));
	else blocks.push_back(&(blocks3dflat.back()));

	return &(blocks3dflat.back());
}

Block3DFlat* BlockFactory::new_distance_block(string texture, Vector2f size)
{
	Block3DFlat new_block(++new_name);
	
	blocks3dflat.push_back(new_block);
	
	names_to_blocks3dflat[new_name] = &(blocks3dflat.back());

	blocks3dflat.back().set_tex(new_texture(texture));

	blocks3dflat.back().set_size(size);

	distance_blocks.push_back(&(blocks3dflat.back()));

	return &(blocks3dflat.back());

}

Block2D* BlockFactory::new_blockHUD(Vector2f size, string texture)
{
	Block2D new_block(++new_name);
		
	blocks2d.push_back(new_block);
	
	blocks2d.back().set_tex(new_texture(texture));
	
	blocks2d.back().set_size(size);
	
	hud_blocks.push_back(&(blocks2d.back()));

	return &(blocks2d.back());
}

Block2DText* BlockFactory::new_blockText(Vector2f pos, Vector2f size, string text, string font)
{
	Block2DText new_block;
	
	blocks2dtext.push_back(new_block);
	
	blocks2dtext.back().set_pos(pos);
	blocks2dtext.back().set_text(text);
	blocks2dtext.back().set_size(size);
	
	blocks2dtext.back().set_tex(new_texture(font));
	
	hud_blocks.push_back(&(blocks2dtext.back()));

	return &(blocks2dtext.back());
}

Floor* BlockFactory::new_floor(string height_map, string texture, float scale)
{
	Obj new_obj;
	
	floor.set_scale(scale);
	
	Vector2i size = new_obj.load_heightmap(height_map, scale); //must load heightmap before we set the perm obj on the floor
	floor.set_size(size);
	floor.set_perm_obj(new_obj);
	
	Texture* new_tex = new_texture("img/" + texture);
		
	floor.set_perm_tex(new_tex);
	
	floor_exists = true;
	
	return &floor;
}

Sky* BlockFactory::new_sky(string texture)
{
	Texture* new_tex = new_texture("img/" + texture);
		
	sky.set_perm_tex(new_tex);
	
	sky_exists = true;
	
	return &sky;
}

Block3DImaginary* BlockFactory::new_imaginary_block(Vector3f size)
{
	blocks3dimag.push_back(Block3DImaginary(size));
	blocks.push_back(&blocks3dimag.back());
	return &blocks3dimag.back();
}

Texture* BlockFactory::new_texture(string file)
{
	file = "img/" + file;
	
	Texture new_tex;
	new_tex.set_name(file);
	Texture* ret_tex;
	
	//check if this texture has already been loaded
	bool found_texture = false;
	list<Texture>::iterator t_iter;
	for( t_iter = textures.begin(); t_iter != textures.end(); t_iter++ ) {
		if (new_tex == *t_iter) {
			ret_tex = &(*t_iter);
			found_texture = true;
			break;
		}
	}
	if (!found_texture) {
		FIBITMAP* new_dib = Texture::load(file);
		new_tex.set_data(new_dib);
		textures.push_back(new_tex);
		ret_tex = &(textures.back());
	}
	
	return ret_tex;
}

Obj* BlockFactory::new_obj(string file)
{
	file = "obj/" + file;
	
	Obj new_obj;
	new_obj.set_name(file);
	Obj* ret_obj;
	
	//check if this object has already been loaded
	bool found_object = false;
	list<Obj>::iterator o_iter;
	for( o_iter = objects.begin(); o_iter != objects.end(); o_iter++ ) {
		if (new_obj == *o_iter) {
			ret_obj = &(*o_iter);
			found_object = true;
			break;
		}
	}
	if (!found_object) {
		new_obj.load(file);
		objects.push_back(new_obj);
		ret_obj = &(objects.back());
	}
	
	return ret_obj;
}

void BlockFactory::remove_blockText(Block2DText* text)
{
	hud_blocks.remove(text);
	blocks2dtext.remove(*text);
}

void BlockFactory::remove_blockHUD(Block2D* hud)
{
	hud_blocks.remove(hud);
	blocks2d.remove(*hud);
}

void BlockFactory::remove_3d_block(Block3D* block)
{
	blocks.remove(block);
	blocks3d.remove(*block);
}

void BlockFactory::remove_flat_block(Block3DFlat* block)
{
	if (block->is_transparent()) {
		cout << "number of transparent blocks was: " << transparent_blocks.size() << endl;
		transparent_blocks.remove(block);
		cout << "now is: " << transparent_blocks.size() << endl;
	}
	else {
		blocks.remove(block);
	}
	//blocks3dflat.remove(*block);
}

void BlockFactory::clear_all()
{
	
	textures.clear();
	objects.clear();
	blocks3d.clear();
	blocks2d.clear();
	blocks2dtext.clear();
	blocks3dimag.clear();
	blocks3dflat.clear();
	
	blocks.clear();
	distance_blocks.clear();
	hud_blocks.clear();
	transparent_blocks.clear();
	
}
