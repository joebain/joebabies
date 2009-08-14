/* Holds all the info for a vertex in a 3d model, used by Obj objects but shouldn't
 * be used on its own.
 */
#ifndef VERTEX_H_
#define VERTEX_H_

#include "Vector3f.h"
#include "Vector2f.h"

class Vertex
{
public:
	Vector3f *pos;
	Vector3f *normal;
	Vector2f *text;
	Vertex();
	virtual ~Vertex();
};

#endif /*VERTEX_H_*/
