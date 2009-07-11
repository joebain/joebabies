#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/gl.h>
#include <string>

using namespace std;

class Texture
{
private:
	unsigned long sizeX;
    unsigned long sizeY;
    char *data;
    GLuint tex_num;
	string name;
public:
	Texture();
	virtual ~Texture();
	int load(string filename_s);
	GLuint get_tex_num();
	bool operator== (const Texture& tex);
};

#endif /*TEXTURE_H_*/
