#include "Obj.h"

#include <GL/glu.h>
#include <iostream>
#include <string>
#include <GL/gl.h>

#include "ModelLoader.h"

Obj::Obj()
{
	name = "unamed";
	offset = *(new Vector3f());
	clear = false;
	rotation.init(0,0,0);
}

Obj::~Obj()
{
}

Obj::Obj(const Obj& o)
{
	v_poss = o.v_poss;
	v_norms = o.v_norms;
	v_texts = o.v_texts;
	vertices = o.vertices;
	faces = o.faces;
	texture = o.texture;
	face_count = o.face_count;
	offset = o.offset;
	rotation = o.rotation;
	name = o.name;
}

void Obj::load(string filename)
{
	this->name = filename;
	
	ModelLoader m;
	m.load_obj(filename, this);
}

bool Obj::operator==(const Obj& obj)
{
	return name == obj.name;
}

void Obj::setClear()
{
	clear = true;
}

void Obj::set_texture(Texture* t)
{
	texture = t;
}

void Obj::display()
{	
	if (clear) {
		glEnable(GL_BLEND);              //activate blending mode
    	glBlendFunc(GL_ONE, GL_ONE);  //define blending factors	
	}
	
	int f,i;
	//cout << "displaying object " << name << endl;
	glBindTexture(GL_TEXTURE_2D, texture->get_tex_num());

	//save the world matrix to the stack
	glPushMatrix();
	
	//translate the object
	glTranslatef(offset.x,offset.y,offset.z);
	
	//rotate the object
	glRotatef(rotation.y,0,1,0);
	glRotatef(rotation.x,1,0,0);
	//don't do z rotation cos it smells
	//glRotatef(rotation.z,0,0,1);
	
	//cout << "bound texture" << endl;
	for (f = 0 ; f < face_count ; f++) {
	//cout << "face no " << f << endl;	
		Face face = faces[f];
		
		glBegin(GL_TRIANGLE_FAN);
		
		for (i = 0; i < face.vertex_count ; i++) {
			glTexCoord2f(face.vertices[i].text->x,face.vertices[i].text->y);
			glVertex3f(face.vertices[i].pos->x,face.vertices[i].pos->y,face.vertices[i].pos->z);
			glNormal3f(face.vertices[i].normal->x,face.vertices[i].normal->y,face.vertices[i].normal->z);
		}

		glEnd();
		
	}
	
	if (clear) glDisable(GL_BLEND);

	//load the world matrix back
	glPopMatrix();

}

void Obj::translate(Vector3f t)
{
	//t.multiply(2);
	//cout << "translated\n";
	//Vector3f o;//= *t.copy();
	offset = t;
	//cout << "assigned!\n";
}

void Obj::rotate(Vector3f r)
{
	rotation = r;
}
