#ifndef HASPOSROT3D_H
#define HASPOSROT3D_H

#include "Vector3f.h"

class HasPosDir3D
{
	protected:
		Vector3f pos;
		Vector3f dir;
	public:
		virtual void set_pos(Vector3f pos) { this->pos = pos; }
		virtual void set_dir(Vector3f dir) { this->dir = dir; }
		virtual Vector3f get_pos() { return pos; }
		virtual Vector3f get_dir() { return dir; }
};

#endif // HASPOSROT3D_H
