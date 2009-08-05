#ifndef TEXTURE_H_
#define TEXTURE_H_

#ifdef WIN32
#include <windows.h>
#endif
#include <stdlib.h>

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
	bool transparent;
	GLuint mask_num;
	bool has_mask;
public:
	Texture();
	~Texture();
	Texture(const Texture& t);
	Texture& operator=(const Texture& t);
	int load(string filename_s);
	void set_name(string name);
	int make_mask();
	GLuint get_tex_num();
	GLuint get_mask_num();
	bool operator== (const Texture& tex);
};

#endif /*TEXTURE_H_*/
