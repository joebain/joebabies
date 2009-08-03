#include "BlockFactory.h"

void BlockFactory::set_display(Display* d)
{
	this->d = d;
}

Block3D* BlockFactory::new_character(string object, string texture)
{
	Block3D* character = new_block3d(object, texture);
	character->set_driven();
	
	return character;
}

Block3D* BlockFactory::new_block3d(string object, string texture)
{
	Block3D new_block;
	
	blocks3d.push_back(new_block);
	
	blocks3d.back().set_tex(new_texture(texture));

	blocks3d.back().set_obj(new_obj(object));
	
	d->blocks.push_back(&(blocks3d.back()));

	return &(blocks3d.back());

}

Block2D* BlockFactory::new_blockHUD(Vector2f size, string texture)
{
	Block2D new_block;
		
	blocks2d.push_back(new_block);
	
	blocks2d.back().set_tex(new_texture(texture));
	
	blocks2d.back().set_size(size);
	//blocks2d.back().set_depth(1);
	
	d->hud_blocks.push_back(&(blocks2d.back()));

	return &(blocks2d.back());
}

Block2DText* BlockFactory::new_blockText(Vector2f pos, Vector2f size, string text, string font)
{
	Block2DText new_block;
	
	blocks2dtext.push_back(new_block);
	
	blocks2dtext.back().set_pos(Vector2f(pos.x,pos.y));
	//blocks2dtext.back().set_mask(false);
	blocks2dtext.back().set_text(text);
	blocks2dtext.back().set_size(size);
	
	blocks2dtext.back().set_tex(new_texture(font));
	
	d->hud_blocks.push_back(&(blocks2dtext.back()));

	return &(blocks2dtext.back());
}

Floor* BlockFactory::new_floor(string height_map, string texture, float scale)
{
	Obj new_obj;
	
	floor.set_scale(scale);
	
	Vector2i size = new_obj.load_heightmap(height_map, scale); //must load heightmap before we set the perm obj on the floor
	floor.set_size(size);
	floor.set_perm_obj(new_obj);
	
	floor.set_tex(new_texture(texture));
	
	d->floor = &floor;
	
	return &floor;
}

Sky* BlockFactory::new_sky(string texture)
{
	sky.set_tex(new_texture(texture));
	
	d->sky = &sky;
	
	return &sky;
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
		new_tex.load(file);
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
