#include "Texture.h"


Texture::Texture(int _id, const char* _filename) : id(_id), filename(_filename) {

}

FIBITMAP* Texture::createBitMap() {
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
	if (format == -1) {
		cout << "Could not find image: " << filename << " - Aborting." << endl;
		exit(-1);
	}
	else if (format == FIF_UNKNOWN) {
		cout << "Couldn't determine file format - attempting to get from file extension..." << endl;
		format = FreeImage_GetFIFFromFilename(filename);
		if (!FreeImage_FIFSupportsReading(format)) {
			cout << "Detected image format cannot be read!" << endl;
			exit(-1);
		}
	}
	FIBITMAP* bitmap = FreeImage_Load(format, filename);
	int bitsPerPixel = FreeImage_GetBPP(bitmap);
	FIBITMAP* bitmap32;
	if (bitsPerPixel == 32) {
		cout << "Source image has " << bitsPerPixel << " bits per pixel. Skipping conversion." << endl;
		bitmap32 = bitmap;
	}
	else {
		cout << "Source image has " << bitsPerPixel << " bits per pixel. Converting to 32-bit colour." << endl;
		bitmap32 = FreeImage_ConvertTo32Bits(bitmap);
	}
	return bitmap32;
}


void Texture::generateTexture() {
	glGenTextures(1, &textureID);   
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight,
		0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, textureData);
}

void Texture::initTexture() {
	FIBITMAP* bitmap32 = createBitMap();
	imageWidth = FreeImage_GetWidth(bitmap32);
	imageHeight = FreeImage_GetHeight(bitmap32);
	textureData = FreeImage_GetBits(bitmap32);
	generateTexture();
}