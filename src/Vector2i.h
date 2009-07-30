#ifndef VECTOR2I_H_
#define VECTOR2I_H_

#include "consts.h"

class Vector2i
{
public:
	int x, y;
	Vector2i();
	Vector2i(int x, int y);
	virtual ~Vector2i();
	void init(int x, int y);
	float angle_between(Vector2i other);
	Vector2i dir_between(Vector2i other);
	float mag();
	Vector2i & operator=(const Vector2i &rhs);
};

#endif /*VECTOR2I_H_*/
