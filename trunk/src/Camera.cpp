#include "Camera.h"

#ifdef WIN32
#include <windows.h>
#endif
#include <stdlib.h>

#include <math.h>
#include <GL/glu.h>


#include "Vector3f.h"

Camera::Camera()
{
	height = 0.3;
	distance = 15.0;
	
	pos.init(0,0,0);
	dir.init(0,0,0);
	
	is_following = false;
}

void Camera::follow(Block3D* subject)
{
	this->subject = subject;
	is_following = true;
	follow_type = FOLLOW_TYPE_3D;
	
}

void Camera::position()
{
	if (is_following) {
		if (follow_type == FOLLOW_TYPE_3D) {
			Vector3f p = ((Block3D*)subject)->get_pos();
			gluLookAt(pos.x,pos.y,pos.z,p.x,p.y,p.z,0,1,0);
		}
	}
}

void Camera::move(float delta)
{
	if (is_following) {
		
		if (follow_type == FOLLOW_TYPE_3D) {
		
			Block3D* subject3d = (Block3D*) subject;
		
			Vector3f r = subject3d->get_dir();
			Vector3f p = subject3d->get_pos();
			
			p.y += 2; //look above/ahead
			
			r.y -= 45; //why? i don't know but it works
			
			//where the camera wants to be
			Vector3f aim;
			
			aim.x = (cos(r.y*D2R) + sin(r.y*D2R));
			aim.z = (-sin(r.y*D2R) + cos(r.y*D2R));
			aim.y = height;
			
			aim.normalise();
			aim *= distance;
			
			aim.x = p.x - aim.x;
			aim.z = p.z - aim.z;
			aim.y = p.y + aim.y;
			
			Vector3f move;
			
			move = aim - pos;
			
			
			float mag = move.magnitude();
			//cout << "mag is " << mag << endl;
			if (mag > delta  * 5.0) {
				move *= delta * 2.0;
			}
			
			pos += move;
			
			//pos = aim;
			
		}
	}
}
