#ifndef VECTOR3I_H_
#define VECTOR3I_H_

#include "Vector3f.h"

class Vector3i
{
public:
	int x, y, z;
	Vector3i();
	virtual ~Vector3i();
	Vector3f to_real();
	Vector3f to_f();
	Vector3i operator+(Vector3i rhs);
	Vector3i operator-(Vector3i rhs);
	Vector3i operator*(Vector3i rhs);
	Vector3f operator*(float f);
	float sum();
	void init(int nx, int ny, int nz);
	void print();
};

#endif /*VECTOR3I_H_*/