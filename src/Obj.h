#ifndef OBJ_H_
#define OBJ_H_

#include "Vertex.h"
#include "Face.h"
#include "Vector3f.h"
#include "Vector2f.h"
#include "Texture.h"

class Obj
{
private:
	bool clear;
public:
	Vector3f *v_poss, *v_norms;
	Vector2f *v_texts;
	Vertex *vertices;
	Face *faces;
	Texture *texture;
	int face_count;
	Vector3f offset;
	Obj();
	Vector3f rotation;
	void set_name(char* name);
	virtual ~Obj();
	void display();
	void translate(Vector3f t);
	char* name;
	void setClear();
};

#endif /*OBJ_H_*/
