#include "Block3DFlat.h"

#ifdef WIN32
#include <windows.h>
#endif
#include <iostream>
#include <string>
#include <algorithm>

#include "Vector2f.h"
#include "Texture.h"

Block3DFlat::Block3DFlat()
{
	is_driven = false;
	
	is_2d = false;
	
	shown = HAS_ALPHA;
	
	rel_centre = true;
	
	anim_dir = 1;
}

Block3DFlat::~Block3DFlat()
{
}

Block3DFlat::Block3DFlat(const Block3DFlat& b)
{
	shown = b.shown;
	pos = b.pos;
	size = b.size;
	anim_dir= b.anim_dir;
	texture = b.texture;
	is_driven = b.is_driven;
	is_2d = b.is_2d;
	rel_centre = b.rel_centre;
	tex_coords = b.tex_coords;
	current_coords = b.current_coords;
	flip_y = b.flip_y;
	animating = b.animating;
	bounce = b.bounce;
	anim_dir = b.anim_dir;
}

bool Block3DFlat::operator==(const Block3DFlat& b)
{
	if (pos == b.pos && size == b.size && texture == b.texture)
		return true;
	else
		return false;
}

void Block3DFlat::move(Vector3f move)
{
	Vector3f move_tmp(move);
	if (is_driven) {
		move_tmp.rotate(-dir);	
	}
	pos.x += move.x;
	pos.y += move.y;
	pos.z += move.z;
	
	centre = (pos + Vector3f(size*0.5f,0));
}

void Block3DFlat::rotate(Vector3f plus_rot)
{
	dir += plus_rot;
}

void Block3DFlat::set_size(Vector2f size)
{
	this->size = size;
}

void Block3DFlat::scale(Vector2f s)
{
	this->size *= s;
}

void Block3DFlat::scale(float s)
{
	this->size *= s;
}

void Block3DFlat::set_transparency(float t)
{
	transparency = t;
	if (t == 0.0)
		shown = NEITHER;
	else
		shown = TRANSP;
}

bool Block3DFlat::is_transparent()
{
	if (shown == NEITHER)
		return false;
	else 
		return true;
}

void Block3DFlat::display()
{
	//cycle textures
	if (animating && timer.time_since(last_texture_switch) > current_coords->second && tex_coords.size() > 1) {
		last_texture_switch = timer.get_time();
		if (anim_dir == 1) {
			++current_coords;
			if (current_coords == tex_coords.end()) {
				if (bounce) {
					anim_dir = -1;
					--current_coords;
					--current_coords;
				}
				else {
					current_coords = tex_coords.begin();
					
				}
				
			}
		}
		else if (anim_dir == -1) {
			--current_coords;
			if (current_coords == tex_coords.begin()) {
				if (bounce) {
					anim_dir = 1;
					
				}
				else {
					current_coords = tex_coords.end();
					--current_coords;
					--current_coords;
				}
			}
		}
		
	}
	
	glPushMatrix();
		
	if (rel_centre) {
		glTranslatef(pos.x, pos.y, pos.z);
	}
	
	glRotatef(dir.z,0,0,1);
	glRotatef(dir.y,0,1,0);
	glRotatef(dir.x,1,0,0);
	
	if (!rel_centre) {
		glTranslatef(pos.x, pos.y, pos.z);
	}
	
	//grab the z pos
	if (shown != NEITHER) {
		float new_t[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, new_t);
		
		//Vector3f np;
		//np.init(new_t[12],new_t[13],new_t[14]);
		
		float z_depth1 = new_t[14];
		
		glPushMatrix();
		
		glTranslatef(size.x, size.y, 0);
		glGetFloatv(GL_MODELVIEW_MATRIX, new_t);
		
		float z_depth2 = new_t[14];
		
		glPopMatrix();
		
		z_depth = (max(z_depth1,z_depth2));
	}
	
	if (shown == MASKED) {
		
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		if (!is_2d) glDisable(GL_LIGHTING);
		
		glBlendFunc(GL_DST_COLOR,GL_ZERO);
		
		//first the mask
		glBindTexture(GL_TEXTURE_2D, texture->get_mask_num());
		
		draw_rect();
		
		glBlendFunc(GL_ONE, GL_ONE);
		if (!is_2d)	glEnable(GL_LIGHTING);
		
	} else if (shown == TRANSP) {
		
		//glDepthMask(GL_FALSE);
		glEnable (GL_BLEND);
		glColor4f(1.0,1.0,1.0,transparency);
		glBlendFunc (GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
		
		//glBlendFunc(GL_DST_COLOR,GL_ONE_MINUS_DST_ALPHA);
	} else if (shown == HAS_ALPHA) {
		glEnable (GL_BLEND);
		glColor4f(1.0,1.0,1.0,1.0);
		glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	}
	
	glBindTexture(GL_TEXTURE_2D, texture->get_tex_num());
	
	draw_rect();
	
	if (shown == MASKED) {
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	} else if (shown == TRANSP) {
		glDisable(GL_BLEND);
	}
	
	glPopMatrix();
}

void Block3DFlat::draw_rect() {
	//flip y
	if (flip_y) {
		glBegin(GL_QUADS);
			
		glTexCoord2f(get_tex_coords().right,get_tex_coords().bottom);
		glNormal3f(0,0,1);
		glVertex3f(0,0,0);

		glTexCoord2f(get_tex_coords().right,get_tex_coords().top);
		glNormal3f(0,0,1);
		glVertex3f(0,size.y,0);
		
		glTexCoord2f(get_tex_coords().left,get_tex_coords().top);
		glNormal3f(0,0,1);
		glVertex3f(size.x,size.y,0);
		
		glTexCoord2f(get_tex_coords().left,get_tex_coords().bottom);
		glNormal3f(0,0,1);
		glVertex3f(size.x,0,0);

		glEnd();
	} else {
		glBegin(GL_QUADS);
			
		glTexCoord2f(get_tex_coords().left,get_tex_coords().bottom);
		glNormal3f(0,0,1);
		glVertex3f(0,0,0);

		glTexCoord2f(get_tex_coords().left,get_tex_coords().top);
		glNormal3f(0,0,1);
		glVertex3f(0,size.y,0);
		
		glTexCoord2f(get_tex_coords().right,get_tex_coords().top);
		glNormal3f(0,0,1);
		glVertex3f(size.x,size.y,0);
		
		glTexCoord2f(get_tex_coords().right,get_tex_coords().bottom);
		glNormal3f(0,0,1);
		glVertex3f(size.x,0,0);

		glEnd();
	}
}

void Block3DFlat::change_size(float s)
{
	size *= s;
}

void Block3DFlat::set_mask(bool t)
{
	if (t)
		shown = MASKED;
	else
		shown = NEITHER;
}

void Block3DFlat::set_transparent(bool t) {
	if (t)
		shown = HAS_ALPHA;
	else
		shown = NEITHER;
}

void Block3DFlat::set_tex(Texture *texture)
{
	if (shown == MASKED) texture->make_mask();
	this->texture = texture;
	
	tex_coords.clear();
	tex_coords.push_back(pair<Rectanglef, float>(Rectanglef(1,1),1));
	current_coords = tex_coords.begin();
}

void Block3DFlat::set_driven()
{
	is_driven = true;
}

void Block3DFlat::set_tex_size(Vector2f s)
{
	Rectanglef new_coords = get_tex_coords();
	new_coords.top = s.y;
	new_coords.right = s.x;
	float time = current_coords->second;
	list<pair<Rectanglef,float> >::iterator pos = tex_coords.erase(current_coords);
	tex_coords.insert(pos, pair<Rectanglef,float>(new_coords,time));
	current_coords = pos;
}

void Block3DFlat::set_animation(Vector2f size, int width, int height, std::list< float > times, bool bounce) {
	
	this->bounce = bounce;
	
	tex_coords.clear();
	
	list<float>::iterator time = times.begin();
	for (int y = 0 ; y < height ; y++) {
		for (int x = 0 ; x < width ; x++) {
			Rectanglef rect(x*size.x, (x+1)*size.x, y*size.y, (y+1)*size.y);
			tex_coords.push_back(pair<Rectanglef,float>(rect,*time));
			
			++time;
			if (time == times.end()) return;
		}
	}
}
