#ifndef OBJ_H_
#define OBJ_H_

#include <string>

#include "Vertex.h"
#include "Face.h"
#include "Vector3f.h"
#include "Vector2f.h"
#include "Vector2i.h"
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
	void set_name(string name);
	Vector2i load_heightmap(string filename, float scale);
	string name;
	Vector3f *v_poss, *v_norms;
	Vector2f *v_texts;
	Vertex *vertices;
	Face *faces;
	Texture *texture;
	int face_count;
	Vector3f offset;
	Vector3f rotation;
};

#endif /*OBJ_H_*/
