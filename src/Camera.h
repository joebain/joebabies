/* Defines easy to specify transformations to set the camera using gluLookAt().
 * Mainly at the moment the camera can be made to 'follow' a block3d, but
 * because this includes imaginary blocks it can be positioned stationary too.
 */

#ifndef CAMERA_H
#define CAMERA_H

#include "HasPosDir3D.h"

#define FOLLOW_TYPE_3D 1
#define FOLLOW_TYPE_2D 2 //currently not implemented

class Camera
{
public:
	Camera();
	void follow(HasPosDir3D* subject);
	void position(); //actually do the camera transformation
	void move(float delta); //update the camera position each frame
	void set_distance(float distance) {this->distance = distance;}
	void set_height(float height) {this->height = height;}
	Vector3f get_pos() { return pos; }
private:
	bool is_following;
	Vector3f pos; //position of the camera currently
	Vector3f target_pos; //where it is looking
	Vector3f aim_target_pos; //where the camera wants to be
	Vector3f aim_pos; //where it wants to be looking
	
	float distance;
	float height;
	float min_snap; //how close do we get before we snap to the exact position / target
	
	HasPosDir3D* subject;
	int follow_type;
};

#endif
