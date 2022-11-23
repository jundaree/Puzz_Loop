#pragma once
#include<iostream>
#include<GL/glut.h>
#include <FreeImage.h>

using namespace std;

class Texture
{
public :
	
	Texture(int _id, const char* _filename);

	FIBITMAP* createBitMap();
	void generateTexture();
	void initTexture();

	/* How to Use
		1. initTexture() in main()
		2. Paste below at drawing function
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, texture.textureID);
		....
		glDisable(GL_TEXTURE_2D);
	
	*/


	int id;
	const char* filename;

	GLuint textureID;
	GLubyte* textureData;
	int imageWidth, imageHeight;

};

