#ifndef MODELLOADER_H_
#define MODELLOADER_H_

#define LINE_LENGTH 200

#include "Vertex.h"
#include "Face.h"
#include "Vector3f.h"
#include "Vector2f.h"
#include "Obj.h"

#include <stdio.h>
#include <string>

class ModelLoader
{
private:
	FILE *file;
	bool texture;
	int face_count, v_norm_count, v_text_count, v_pos_count;
	char *line;
	void read_floats(char* line, Vector3f* p);
	void read_tex_coords(char* line, Vector2f* t);
	void link_face(char* line, Face* f, Obj* o);
public:
	ModelLoader();
	virtual ~ModelLoader();
	void load_obj(string f_name, Obj *o);
};

#endif /*MODELLOADER_H_*/
