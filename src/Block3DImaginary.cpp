#include "Block3DImaginary.h"

Block3DImaginary::Block3DImaginary (Vector3f size)
{
	perm_bb_min.init(0,0,0);
	perm_bb_max = size;
	
	bb_min = &perm_bb_min;
	bb_max = &perm_bb_max;
}

Block3DImaginary::Block3DImaginary(const Block3DImaginary& b)
: Block3D(b)
{
	perm_bb_min = b.perm_bb_min;
	perm_bb_max = b.perm_bb_max;
	
	bb_min = &perm_bb_min;
	bb_max = &perm_bb_max;
}

void Block3DImaginary::display()
{
	//nothing
	
	//~ glPushMatrix();
	//~ glTranslatef(offset.x+pos.x,offset.y+pos.y,offset.z+pos.z);
	//~ 
	//~ glRotatef(rot.z+dir.z,0,0,1);
	//~ glRotatef(rot.y+dir.y,0,1,0);
	//~ glRotatef(rot.x+dir.x,1,0,0);
	//~ 
	//~ glBegin(GL_QUAD_STRIP);
	//~ 
	//~ glVertex3f(0,0,0);
	//~ glVertex3f(0,0,bb_max->z);
	//~ glVertex3f(0,bb_max->y,0);
	//~ glVertex3f(0,bb_max->y,bb_max->z);
	//~ glVertex3f(bb_max->x,bb_max->y,0);
	//~ glVertex3f(bb_max->x,bb_max->y,bb_max->z);
	//~ glVertex3f(bb_max->x,0,0);
	//~ glVertex3f(bb_max->x,0,bb_max->z);
	//~ 
	//~ 
	//~ glEnd();
	//~ 
	//~ glPopMatrix();
}
