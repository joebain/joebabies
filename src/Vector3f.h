#ifndef VECTOR3F_H_
#define VECTOR3F_H_

#include "consts.h"

#include <iostream>

using namespace std;

class Vector3f
{
private:
	
public:
	float x, y, z;
	Vector3f();
	Vector3f(float x, float y, float z);
	Vector3f(const Vector3f& v);
	Vector3f copy();
	Vector3f & operator=(const Vector3f &rhs);
	void normalise();
	Vector3f dir_between(Vector3f other);
	float dist_between(Vector3f other);
	Vector3f angle_between(Vector3f other);
	Vector3f angle_to();
	void operator+=(Vector3f rhs);
	void operator-=(Vector3f rhs);
	Vector3f operator+(Vector3f rhs);
	Vector3f operator-(Vector3f rhs);
	Vector3f operator-();
	Vector3f operator*(float i);
	void operator*=(float i);
	virtual ~Vector3f();
	void init(float x, float y, float z);
	void multiply(float f);
	void print();
	Vector3f matrix_multiply(float (&matrix)[3][3]);
	void rotate(Vector3f rot);
	void abs();
	void snap();
	void point_up();
	float magnitude();
	friend ostream &operator<<(ostream &stream, Vector3f v);
};

#endif /*VECTOR3F_H_*/
