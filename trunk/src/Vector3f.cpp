#include "Vector3f.h"

#include <iostream>
#include <math.h>

using namespace std;

Vector3f::Vector3f()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Vector3f::Vector3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vector3f::init(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;	
}

void Vector3f::print()
{
	cout << x << "," << y << "," << z;	
}

void Vector3f::operator+=(Vector3f rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
}

void Vector3f::operator-=(Vector3f rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
}

Vector3f Vector3f::operator+(Vector3f rhs) {
	Vector3f v;
	
	v.init(x+rhs.x,y+rhs.y,z+rhs.z);
	
	return v;
}

Vector3f Vector3f::operator-(Vector3f rhs) {
	Vector3f v;
	
	v.init(x-rhs.x,y-rhs.y,z-rhs.z);
	
	return v;
}

Vector3f Vector3f::operator-() {
	Vector3f v;
	
	v.init(-x,-y,-z);
	
	return v;
}

Vector3f Vector3f::operator*(float i) {
	Vector3f v;
	
	v.init(x*i,y*i,z*i);
	
	return v;
}

void Vector3f::operator*=(float i) {
	x *= i;
	y *= i;
	z *= i;
}

Vector3f& Vector3f::operator=(const Vector3f &rhs) {
    
    if (this == &rhs)
    	return *this;
    
    //cout << "doing =\n";
    
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;

	//cout << "x y z " << x << "," << y << "," << z < endl;
	//cout << "x y z " << rhs.x << "," << rhs.y << "," << rhs.z < endl;

    return *this;  // Return a reference to myself.
}

Vector3f Vector3f::copy()
{
	Vector3f new_v;
	new_v.x = x;
	new_v.y = y;
	new_v.z = z;
	
	return new_v;
}

Vector3f::~Vector3f()
{
}

void Vector3f::multiply(float f)
{
	x *= f;
	y *= f;
	z *= f;
}

Vector3f Vector3f::dir_between(Vector3f other)
{
	Vector3f dir;
	
	dir.x = other.x - x;
	dir.y = other.y - y;
	dir.z = other.z - z;
	
	dir.normalise();
	
	return dir;
}

float Vector3f::dist_between(Vector3f other)
{
	Vector3f dir;
	
	dir.x = other.x - x;
	dir.y = other.y - y;
	dir.z = other.z - z;
	
	return sqrt(dir.x*dir.x + dir.y*dir.y + dir.z*dir.z);
}

//must be unit vectors
Vector3f Vector3f::angle_between(Vector3f other)
{
	Vector3f ang;
	
	ang.x = acos(x*other.x + y*other.y);
	ang.y = acos(y*other.y + z*other.z);
	ang.z = acos(z*other.z + x*other.x);
	
	return ang;
}

Vector3f Vector3f::angle_to()
{
	Vector3f ang;
	
	ang.z = acos(x*UNIT2D + y*UNIT2D)*R2D;
	ang.x = acos(y*UNIT2D + z*UNIT2D)*R2D;
	ang.y = acos(z*UNIT2D + x*UNIT2D)*R2D;
	
	if (x < z) ang.y = -ang.y;
	//if (z < y) ang.x = -ang.x;
	//if (y < x) ang.z = -ang.z;
	
	return ang;
}

void Vector3f::normalise()
{
	float mag = sqrt(x*x + y*y + z*z);
	
	multiply(1/mag);
}

void Vector3f::rotate(Vector3f rot)
{

	/* x =
	 * [1 0      0]
	 * [0 cos -sin]
	 * [0 sin  cos]
	 * 
	 * y =
	 * [cos  0 sin]
	 * [0    1   0]
	 * [-sin 0 cos]
	 * 
	 * z =
	 * [cos -sin 0]
	 * [sin  cos 0]
	 * [0    0   1]
	 */
	
	float rx[3][3] = {{1,0,0},{0,cos(rot.x*D2R),sin(rot.x*D2R)},{0,-sin(rot.x*D2R),cos(rot.x*D2R)}};
	float ry[3][3] = {{cos(rot.y*D2R),0,-sin(rot.y*D2R)},{0,1,0},{sin(rot.y*D2R),0,cos(rot.y*D2R)}};
	float rz[3][3] = {{cos(rot.z*D2R),sin(rot.z*D2R),0},{-sin(rot.z*D2R),cos(rot.z*D2R),0},{0,0,1}};
	
	Vector3f rv = matrix_multiply(rx).matrix_multiply(ry).matrix_multiply(rz);
	
	//cout << "x " << rv.x << " y " << rv.y << " z " << rv.z << endl;
	
	init(rv.x,rv.y,rv.z);
	
}

void Vector3f::abs()
{
	x *= (x < 0 ? -1 : 1);
	y *= (y < 0 ? -1 : 1);
	z *= (z < 0 ? -1 : 1);
}

void Vector3f::snap()
{
	x = (int)(x+(x < 0 ? -0.5 : 0.5));
	y = (int)(y+(y < 0 ? -0.5 : 0.5));
	z = (int)(z+(z < 0 ? -0.5 : 0.5));
}

Vector3f Vector3f::matrix_multiply(float (&matrix)[3][3])
{
	
	Vector3f rv;
	
	rv.x = matrix[0][0]*x + matrix[0][1]*y + matrix[0][2]*z;
	rv.y = matrix[1][0]*x + matrix[1][1]*y + matrix[1][2]*z;
	rv.z = matrix[2][0]*x + matrix[2][1]*y + matrix[2][2]*z;
	
	return rv; 
}

ostream &operator<<(ostream &stream, Vector3f v)
{
  stream << v.x << " " << v.y << " " << v.z;

  return stream;
}
