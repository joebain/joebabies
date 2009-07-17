#ifndef OBJ_H_
#define OBJ_H_

#include <string>

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
	Obj();
	virtual ~Obj();
	Obj(const Obj& o);
	bool operator==(const Obj& obj);
	void load(string filename);
	void display();
	void translate(Vector3f t);
	void rotate(Vector3f r);
	void setClear();
	void set_texture(Texture* t);
	Vector3f *v_poss, *v_norms;
	Vector2f *v_texts;
	Vertex *vertices;
	Face *faces;
	Texture *texture;
	int face_count;
	Vector3f offset;
	Vector3f rotation;
	string name;
};

#endif /*OBJ_H_*/
