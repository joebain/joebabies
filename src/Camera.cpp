#include "Camera.h"

#include <math.h>
#include <GL/glu.h>


#include "Vector3f.h"

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
		
			Block3D* subject3d = (Block3D*) subject;
		
			Vector3f r = subject3d->get_rot();
			Vector3f p = subject3d->get_pos();
			
			r.y -= 45; //why? i don't know but it works
			
			Vector3f tmp;
			
			tmp.x = (cos(r.y*D2R) + sin(r.y*D2R));
			tmp.z = (-sin(r.y*D2R) + cos(r.y*D2R));
			tmp.y = 0.5; //some elevation
			
			p.y += 4;
			
			tmp.normalise();
			tmp *= 15; //probably should make this more dynamic or something
			
			tmp.x = p.x - tmp.x;
			tmp.z = p.z - tmp.z;
			
			//cout << "at " << tmp << " them at " << p << endl;
			
			gluLookAt(tmp.x,tmp.y,tmp.z,p.x,p.y,p.z,0,1,0);
			
		}
	}
}
