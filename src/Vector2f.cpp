#include "Vector2f.h"

#include <math.h>

Vector2f::Vector2f()
{
	this->x = 0;
	this->y = 0;
}

Vector2f::Vector2f(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2f::Vector2f(const Vector2f& v)
{
	x = v.x;
	y = v.y;
}

Vector2f::~Vector2f()
{
}

bool Vector2f::operator==(const Vector2f& rhs)
{
	if (rhs.x == x && rhs.y == y)
		return true;
	else
		return false;
}

Vector2f& Vector2f::operator=(const Vector2f &rhs) {
    
    if (this == &rhs)
    	return *this;
    
    x = rhs.x;
    y = rhs.y;

    return *this;
}

void Vector2f::init(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2f Vector2f::operator*(float f) {
	return Vector2f(x*f,y*f);
}

Vector2f Vector2f::operator+(Vector2f & v) {
	return Vector2f(x*v.x,y*v.y);
}

void Vector2f::operator*=(float f)
{
	x *= f;
	y *= f;
}

void Vector2f::operator*=(Vector2f rhs)
{
	x *= rhs.x;
	y *= rhs.y;
}

void Vector2f::rotate(float r)
{
	x = (cos(r*D2R) + sin(r*D2R));
	y = (-sin(r*D2R) + cos(r*D2R));
}

ostream &operator<<(ostream &stream, Vector2f v)
{
  stream << v.x << " " << v.y;

  return stream;
}
