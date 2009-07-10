#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/gl.h>

class Texture
{
private:
	unsigned long sizeX;
    unsigned long sizeY;
    char *data;
    GLuint *texture;
public:
	Texture();
	virtual ~Texture();
	int load(char* filename);
	GLuint get_tex_num();
};

#endif /*TEXTURE_H_*/
