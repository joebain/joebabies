#include "Texture.h"

#ifdef WIN32
#include <windows.h>
#endif
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <limits.h>
#include <stdio.h>

#include <GL/gl.h>

using namespace std;

Texture::Texture()
{	
	data = (char*) malloc(1);
	
	tex_num = 0;
	has_mask = false;

	stringstream out;
	int* num = (int*) malloc(1);
	out << "unnamed_" << num;
	free(num);
	name = out.str();
}

Texture::~Texture()
{
	if (data != NULL) {
		name = "deleted";
		//cout << "memory holds " << data[0] << endl;
		free(data); //--this should really be here but its causing errors and i dont know what to do!
		data = NULL;
	}
}

Texture::Texture(const Texture& t)
{
	sizeX = t.sizeX;
    sizeY = t.sizeY;
    tex_num = t.tex_num;
	mask_num = t.mask_num;
	transparent = t.transparent;
	name = t.name;
	has_mask = t.has_mask;
	if (t.data == NULL) {
		data = NULL;
	} else {
		int size = sizeX * sizeY * 3; //as below
		data = (char*) malloc(size);
		memcpy(data,t.data,size);
		if (data==NULL)
			cout << "oh no, couldnt allocate memory fo texture" << endl;
	}
}

bool Texture::operator==(const Texture& tex)
{
	return name == tex.name;
}

GLuint Texture::get_tex_num() {
	return tex_num;
}

GLuint Texture::get_mask_num() {
	return mask_num;
}

int Texture::make_mask() {
	
	if (has_mask) return 1;
	
	if (tex_num != 0) {
				
		int size = sizeX * sizeY * 3;
		char* mask_data = (char*)malloc(size*sizeof(char));
		for (int i = 0; i < size; i+= 3) {
			//cout << "data" << (uint)data[i] << "," << (uint)data[i+1] << "," << (uint)data[i+2] << endl;
			if ((int)data[i] == 0 && (int)data[i+1] == 0 && (int)data[i+2] == 0) {
				mask_data[i] = (char)-1;
				mask_data[i+1] = (char)-1;
				mask_data[i+2] = (char)-1;
			} else {
				mask_data[i] = (char)0;
				mask_data[i+1] = (char)0;
				mask_data[i+2] = (char)0;
			}
		}

		glGenTextures(1, &mask_num);
		glBindTexture(GL_TEXTURE_2D, mask_num);   // 2d texture (x and y size)

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

		// 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
		// border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
		glTexImage2D(GL_TEXTURE_2D, 0, 3, sizeX, sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, mask_data);
		
		free(mask_data);

		has_mask = true;

		return 1;
	} else {
		cout << "no texture loaded yet" << endl;		
		return 0;
	}
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
    
    // read the height 
    if ((i = fread(&sizeY, 4, 1, file)) != 1) {
	printf("Error reading height from %s.\n", filename);
	return 0;
    }
    
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
    glBindTexture(GL_TEXTURE_2D, tex_num);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
    glTexImage2D(GL_TEXTURE_2D, 0, 3, sizeX, sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    // we're done.
    return 1;
}

void Texture::set_name(string name)
{
	this->name = name;
}
