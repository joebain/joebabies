#ifndef FACE_H_
#define FACE_H_

#include <list>

#include "Vertex.h"

using namespace std;

class Face
{
public:
	Vertex *vertices;
	int vertex_count;
	Face();
	virtual ~Face();
};

#endif /*FACE_H_*/
