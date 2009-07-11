#include <iostream>

#include "Vector3i.h"
#include "World.h"
#include "Vector3f.h"

Vector3i::Vector3i()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3i::~Vector3i()
{
}

Vector3f Vector3i::to_real()
{
	#define GAP 2.2
	Vector3f real;
	real.init(x*GAP,y*GAP,z*GAP);
	
	return real;
}

Vector3i Vector3i::operator+(Vector3i rhs)
{
	Vector3i result;
	result.init(x+rhs.x,y+rhs.y,z+rhs.z);
	return result;
}

Vector3i Vector3i::operator-(Vector3i rhs)
{
	Vector3i result;
	result.init(x-rhs.x,y-rhs.y,z-rhs.z);
	return result;
}

Vector3i Vector3i::operator*(Vector3i rhs)
{
	Vector3i result;
	result.init(x*rhs.x,y*rhs.y,z*rhs.z);
	return result;
}

Vector3f Vector3i::operator*(float f)
{
	Vector3f result;
	result.init(x*f,y*f,z*f);
	return result;
}

float Vector3i::sum()
{
	return x + y + z;
}

Vector3f Vector3i::to_f()
{
	Vector3f f;
	f.init(x,y,z);
	return f;
}

void Vector3i::init(int nx, int ny, int nz)
{
	x = nx;
	y = ny;
	z = nz;
}

void Vector3i::print()
{
	cout << x << "," << y << "," << z;
}
