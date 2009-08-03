#include "ModelLoader.h"

#include <iostream>
#include <stdlib.h>
#include <cctype>

#include "Vector3f.h"
#include "Vector2f.h"
#include "Vertex.h"
#include "Face.h"

ModelLoader::ModelLoader()
{
	line = new char[LINE_LENGTH];
	
}

ModelLoader::~ModelLoader()
{
	delete line;
}

//read floats (i.e. the xyz for a vector3f or normal)
void ModelLoader::read_floats(char* line, Vector3f* p) {
	
	int i = 0;
	
	while (!isspace(line[i++]));
	p->x = strtod(line+i,NULL);
	
	while (!isdigit(line[i++]));
	while (!isspace(line[i++]));
	p->y = strtod(line+i,NULL);
	
	while (!isdigit(line[i++]));
	while (!isspace(line[i++]));
	p->z = strtod(line+i,NULL);
}


void ModelLoader::read_tex_coords(char* line, Vector2f* t) {
	
	int i = 0;
	
	while (!isspace(line[i++]));
	t->x = strtod(line+i,NULL);
	
	while (!isdigit(line[i++]));
	while (!isspace(line[i++]));
	t->y = strtod(line+i,NULL);
	
}

//link each face to the right vertices and normals
void ModelLoader::link_face(char* line, Face *f, Obj *o) {
	
	int i;
	
	int v_count = 0;

	for( i = 0 ; line[i] != '\n' ; i++) {
		if (line[i] == '/') v_count ++;
	}
	
	f->vertex_count = v_count/2;
	f->vertices = new Vertex[f->vertex_count];

	i = 0;
	v_count = 0;

	while (true) {
		while (!isspace(line[i++]));
		if (!isdigit(line[i])) return;
		
		Vertex v;

		v.pos = &o->v_poss[atoi(line+i)-1];
		while (isdigit(line[i++]));
		while (line[i++] == '/');
		if (texture) {
			v.text = &o->v_texts[atoi(line+i-1)-1];
			while (isdigit(line[i++]));
			while (line[i++] == '/');
		}
		v.normal = &o->v_norms[atoi(line+i-1)-1];
		
		//set size
		if (v.pos->x > o->max.x) o->max.x = v.pos->x;
		else if (v.pos->x < o->min.x) o->min.x = v.pos->x;
		if (v.pos->y > o->max.y) o->max.y = v.pos->y;
		else if (v.pos->y < o->min.y) o->min.y = v.pos->y;
		if (v.pos->z > o->max.z) o->max.z = v.pos->z;
		else if (v.pos->z < o->min.z) o->min.z = v.pos->z;
		//cout << "v.pos " << v.pos->x << "," << v.pos->y << " v.text " << v.text->x << "," << v.text->y << " v.norm " << v.normal->x << "," << v.normal->y << endl;
		
		f->vertices[v_count++] = v;
		
	}
	
}

//load in an object file to a set of pointfs
void ModelLoader::load_obj(string f_name, Obj *o) {
	
	file = fopen(f_name.c_str(), "r");
	
	if (file == NULL) {
		cout << "File " << f_name << " is not there!" << endl;
    	exit(0);
    }

	v_pos_count = 0;
	v_norm_count = 0;
	v_text_count = 0;
	face_count = 0;

	while (fgets(line, LINE_LENGTH, file) != NULL) {
		if (line[0] == 'v') {
			if (line[1] == 'n')
				v_norm_count++;
			else if (line[1] == 't')
				v_text_count++;
			else
				v_pos_count++;
		}
		else if (line[0] == 'f')
			face_count++;
	}
	
	//printf("Vertices: %d, Normals: %d, Faces: %d, Texture points: %d\n",v_pos_count,v_norm_count,face_count,v_text_count);
	
	if (v_text_count > 0)
		texture = true;
	else
		texture = false;
	
	o->face_count = face_count;
	
	o->v_poss = new Vector3f[v_pos_count];
	o->v_norms = new Vector3f[v_norm_count];
	o->v_texts = new Vector2f[v_text_count];
	o->faces = new Face[face_count];

	fclose(file);
	
	file = fopen(f_name.c_str(), "r");
	
	v_pos_count = 0;
	v_norm_count = 0;
	v_text_count = 0;
	face_count = 0;
	
	while (fgets(line, LINE_LENGTH, file) != NULL) {
		if (line[0] == 'v') {
			if (line[1] == 'n')
				read_floats(line, &o->v_norms[v_norm_count++]);
			else if (line[1] == 't')
				read_tex_coords(line, &o->v_texts[v_text_count++]);
			else
				read_floats(line, &o->v_poss[v_pos_count++]);
		}
		else if (line[0] == 'f')
			link_face(line, &o->faces[face_count++], o);
	}
	
}
