#include "Camera.h"

#include <math.h>
#include <GL/glu.h>


#include "Vector3f.h"

void Camera::follow(Block* subject)
{
	this->subject = subject;
	is_following = true;
}

void Camera::position()
{
	if (is_following) {
		
		Vector3f r = subject->get_rot();
		Vector3f p = subject->get_pos();
		
		r.y += 180;
		
		Vector3f tmp;
		
		tmp.x = p.x - (cos(r.y) + sin(r.y));
		tmp.z = p.z - (-sin(r.y) + cos(r.y));
		tmp.y = 3; //some elevation
		
		//tra.x = p.x + tmp.x*8;
		//tra.z = p.z + tmp.z*8;
		
		//rot.y = -r.y;
		
		//cout << "at " << tra << " them at " << p << endl;
		
		gluLookAt( tmp.x,
			  tmp.y,
			  tmp.z,
			  p.x,
			  p.y,
			  p.z,
			  0,
			  1,
			  0);
	}
}
