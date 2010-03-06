/* A pretty rubbish and slightly broken sky box, not much to say. Also
 * hardcoded with OpenGL which is a bit poor.
 */
#ifndef SKY_H
#define SKY_H

#include "Block3D.h"

class Sky : public Block3D
{
public:
	Sky();
	void set_scale(float scale);
	void set_perm_tex(Texture* tex);
private:
	Obj perm_object;
	float scale;
};

#endif
