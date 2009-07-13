#include "Texture.h"

#include <stdlib.h>
#include <iostream>
#include <GL/gl.h>
#include <string>
#include <sstream>
#include <cstring>


using namespace std;

Texture::Texture()
{
	data = NULL;
	//cout << "alocating texture memory" << endl;
	//data = (char *) malloc(1);
	//data[0] = '0';
	//cout << "memory holds " << data[0] << endl;
	//cout << "freeing memory" << endl;
	//free(data);
	tex_num = 0;

	stringstream out;
	int* num = (int*) malloc(1);
	out << "unnamed_" << num;
	free(num);
	name = out.str();
	cout << "new texture: " << name << endl;
}

Texture::~Texture()
{
	if (data != NULL) {
		cout << "deleting texture data for " << name << endl;
		name = "deleted";
		//cout << "memory holds " << data[0] << endl;
		free(data);
	}
}

Texture::Texture(const Texture& t)
{
	cout << "copying over here, tex num is " << t.tex_num << endl;
	sizeX = t.sizeX;
    sizeY = t.sizeY;
    tex_num = t.tex_num;
	name = t.name;
	if (t.data == NULL) {
		data = NULL;
	} else {
		int size = sizeX * sizeY * 3; //as below
		data = (char*) malloc(size);
		memcpy(data,t.data,size);
	}
}

bool Texture::operator==(const Texture& tex)
{
	return name == tex.name;
}

GLuint Texture::get_tex_num() {
	//cout << "get tex num, psst its " << tex_num << endl;
	if (tex_num > 0) return tex_num;
	else return 0;
}

// quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.  
// See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.
int Texture::load(string filename_s) {
    FILE *file;
    unsigned long size;                 // size of the img in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in img (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp;                          // temporary color storage for bgr-rgb conversion.

	name = filename_s;
	const char * filename = filename_s.c_str();

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL)
    {
	printf("File Not Found : %s\n",filename);
	return 0;
    }
    
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);

    // read the width
    if ((i = fread(&sizeX, 4, 1, file)) != 1) {
	printf("Error reading width from %s.\n", filename);
	return 0;
    }
    printf("Width of %s: %lu\n", filename, sizeX);
    
    // read the height 
    if ((i = fread(&sizeY, 4, 1, file)) != 1) {
	printf("Error reading height from %s.\n", filename);
	return 0;
    }
    printf("Height of %s: %lu\n", filename, sizeY);
    
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = sizeX * sizeY * 3;

    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
	printf("Error reading planes from %s.\n", filename);
	return 0;
    }
    if (planes != 1) {
	printf("Planes from %s is not 1: %u\n", filename, planes);
	return 0;
    }

    // read the bpp
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
	printf("Error reading bpp from %s.\n", filename);
	return 0;
    }
    if (bpp != 24) {
	printf("Bpp from %s is not 24: %u\n", filename, bpp);
	return 0;
    }
	
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);

    // read the data. 
    data = (char *) malloc(size);
    if (data == NULL) {
	printf("Error allocating memory for color-corrected img data");
	return 0;	
    }

    if ((i = fread(data, size, 1, file)) != 1) {
	printf("Error reading img data from %s.\n", filename);
	return 0;
    }

    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
	temp = data[i];
	data[i] = data[i+2];
	data[i+2] = temp;
    }
     
     
    // Create Texture name
    glGenTextures(1, &tex_num);  
    cout << "got texture num " << tex_num << endl;  
    glBindTexture(GL_TEXTURE_2D, tex_num);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, sizeX, sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    // we're done.
    return 1;
}
