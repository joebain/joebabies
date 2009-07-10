#include "Vector2i.h"

#include <math.h>
#include <iostream>

using namespace std;

Vector2i::Vector2i()
{
}

Vector2i::~Vector2i()
{
}

Vector2i Vector2i::dir_between(Vector2i other)
{
	Vector2i dir;
	
	dir.x = other.x - x;
	dir.y = other.y - y;
	
	return dir;
}

float Vector2i::angle_between(Vector2i other)
{
	float ang;
	/*
	ang = acos((x*other.x + y*other.y)/(mag()*other.mag()));
	
	float grad = x/y;
	
	if (other.y > x*grad) ang = 2*M_PI - ang;
	*/
	ang = atan2(y,x) - atan2(other.y,other.x);
	
	return ang*R2D;
}

float Vector2i::mag()
{
	return sqrt(x*x + y*y);
}