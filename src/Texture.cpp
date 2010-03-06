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
#include <FreeImage.h>

using namespace std;

Texture::Texture()
{	
	data = (BYTE*) malloc(1);
	
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
		//free(data); //--this should really be here but its causing errors and i dont know what to do!
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
	dib = t.dib;
	data = t.data;
	has_mask = t.has_mask;
}

Texture& Texture::operator=(const Texture& t)
{
	if (this == &t)
		return *this;
	
	sizeX = t.sizeX;
    sizeY = t.sizeY;
    tex_num = t.tex_num;
	mask_num = t.mask_num;
	transparent = t.transparent;
	name = t.name;
	has_mask = t.has_mask;
	dib = t.dib;
	data = t.data;
	
	return *this;
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
				
		int size = sizeX * sizeY * 4;
		char* mask_data = (char*)malloc(size*sizeof(char));
		for (int i = 0; i < size; i+= 4) {
			//cout << "data" << (uint)data[i] << "," << (uint)data[i+1] << "," << (uint)data[i+2] << endl;
			if ((int)data[i] == 0 && (int)data[i+1] == 0 && (int)data[i+2] == 0) {
				mask_data[i] = (char)-1;
				mask_data[i+1] = (char)-1;
				mask_data[i+2] = (char)-1;
				mask_data[i+3] = (char)-1;
			} else {
				mask_data[i] = (char)0;
				mask_data[i+1] = (char)0;
				mask_data[i+2] = (char)0;
				mask_data[i+3] = (char)0;
			}
		}
		
// 		FIBITMAP* mask_dib = FreeImage_Clone(dib);
// 		BYTE* mask_bytes = FreeImage_GetBits(mask_dib);
// 		int w = FreeImage_GetWidth(mask_dib);
// 		int h = FreeImage_GetHeight(mask_dib);
// 		RGBQUAD* colour;
// 		for (int i = 0 ; i < w ; i++) {
// 			for (int j = 0 ; j < h ; j++) {
// 				FreeImage_GetPixelColor(mask_dib,i,j,colour);
// 				
// 			}
// 		}

		glGenTextures(1, &mask_num);
		glBindTexture(GL_TEXTURE_2D, mask_num);   // 2d texture (x and y size)

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); // scale linearly when image bigger than texture
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); // scale linearly when image smalled than texture

		// 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
		// border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
		glTexImage2D(GL_TEXTURE_2D, 0, 4, sizeX, sizeY, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
		
		free(mask_data);

		has_mask = true;

		return 1;
	} else {
		cout << "no texture loaded yet" << endl;		
		return 0;
	}
}

bool Texture::set_data(FIBITMAP *dib) {
	this->dib = dib;
	
	//retrieve the image data
	data = FreeImage_GetBits(dib);
	//get the image width and height
	sizeX = FreeImage_GetWidth(dib);
	sizeY = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if((data == 0) || (sizeX == 0) || (sizeY == 0))
		return false;
     
    // Create Texture name
    glGenTextures(1, &tex_num);
    glBindTexture(GL_TEXTURE_2D, tex_num);   // 2d texture (x and y size)

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // scale linearly when image smalled than texture

    // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image, 
    // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
	glTexImage2D(GL_TEXTURE_2D, 0, 4, sizeX, sizeY, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
    // we're done.
    return true;
}

void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message) {
   printf("\n*** ");
   if(fif != FIF_UNKNOWN) {
     printf("%s Format\n", FreeImage_GetFormatFromFIF(fif));
   }
   printf(message);
   printf(" ***\n");
}

FIBITMAP* Texture::load(string filename_s) {
	
	// In your main program ...
	FreeImage_SetOutputMessage(FreeImageErrorHandler);
	
	const char* filename = filename_s.c_str();
	
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		
    //check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if(fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if(fif == FIF_UNKNOWN)
		return NULL;

	FIBITMAP* dib;
	
	//check that the plugin has reading capabilities and load the file
	if(FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if(!dib)
		return NULL;
	
	return dib;
}

void Texture::set_name(string name)
{
	this->name = name;
}
