#include "Floor.h"

#ifdef WIN32
#include <windows.h>
#endif
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <GL/gl.h>

void Floor::set_perm_obj(Obj obj)
{
	perm_obj = obj;
	object = &perm_obj;
	object->name = "floor";
}

float Floor::get_height(Vector2f pos)
{
	float fx = pos.x/scale;// + ((float)size.x)/2.0f;
	float fy = pos.y/scale;// + ((float)size.y)/2.0f;

	int x = (int) fx;
	int y = (int) fy;
	
	if (x > 0 && x < size.y-1 && y > 0 && y < size.x-1) {
		
		float a = object->vertices[x*size.x + y].pos->y;
		float b = object->vertices[(x+1)*size.x + y].pos->y;
		float c = object->vertices[x*size.x + (y+1)].pos->y;
		float d = object->vertices[(x+1)*size.x + (y+1)].pos->y;
		
		float x_fac = fx - (float)x;
		float y_fac = fy - (float)y;
		
		float ab = a * (1-x_fac) + b * x_fac;
		float cd = c * (1-x_fac) + d * x_fac;
		float abcd = ab * (1-y_fac) + cd * y_fac;
		
		return abcd;
	} else
		//cout << "out of bounds: " << x << "," << y << endl;
		return 0.0;
}
