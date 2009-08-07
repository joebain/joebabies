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
	height = 10;
	distance = 20.0;
	
	min_snap = 2.0;
	
	pos.init(0,50,0);
	
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
			gluLookAt(pos.x,pos.y,pos.z,target_pos.x,target_pos.y,target_pos.z,0,1,0);
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
			
			aim_target_pos = p;
			
			//r.y -= 45; //why? i don't know but it works
			
			glPushMatrix();
			
			//where the camera wants to be
					
			float new_t[16];
			
			glLoadIdentity();
			
			glTranslatef(p.x, p.y, p.z);
			glRotatef(r.z,0,0,1);
			glRotatef(r.y,0,1,0);
			glRotatef(r.x,1,0,0);
			glTranslatef(0,height,-distance);
			
			glGetFloatv(GL_PROJECTION_MATRIX, new_t);
			
			aim_pos.x = new_t[12];
			aim_pos.y = new_t[13];
			aim_pos.z = new_t[14];
			
			glPopMatrix();
			
			//cout << "aim is " << aim_pos << endl;
			
			//~ aim.x = (cos(r.y*D2R) + sin(r.y*D2R));
			//~ aim.z = (-sin(r.y*D2R) + cos(r.y*D2R));
			//~ aim.y = height;
			
			
			 
			//~ aim.normalise();
			//~ aim *= distance;
			
			//~ aim.x = p.x - aim.x;
			//~ aim.z = p.z - aim.z;
			//~ aim.y = p.y + aim.y;
			
			Vector3f move;
			
			//float aim pos
			move = aim_pos - pos;
			float mag = move.magnitude();
			if (mag > delta  * min_snap) {
				move *= delta * 2.0;
			}
			pos += move;
			
			//float aim focus
			move = aim_target_pos - target_pos;
			mag = move.magnitude();
			if (mag > delta  * min_snap) {
				move *= delta * 2.0;
			}
			target_pos += move;
			
		}
	}
}
