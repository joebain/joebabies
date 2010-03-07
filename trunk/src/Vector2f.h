#ifndef VECTOR2F_H_
#define VECTOR2F_H_

#include <iostream>

#include "consts.h"

using namespace std;

class Vector2f
{
public:
	float x, y;
	Vector2f();
	Vector2f(float x, float y);
	Vector2f(const Vector2f& v);
	~Vector2f();
	Vector2f & operator=(const Vector2f &rhs);
	bool operator==(const Vector2f& rhs);
	void init(float x, float y);
	void operator*=(float f);
	Vector2f operator*(float f);
	Vector2f operator+(Vector2f & v);
	void operator*=(Vector2f rhs);
	void rotate(float r);
	friend ostream &operator<<(ostream &stream, Vector2f v);
};

#endif /*VECTOR2F_H_*/
