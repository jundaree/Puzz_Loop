#include "Light.h"

Light::Light(float x, float y, float z, int L_ID) : lightID(L_ID) {
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}

void Light::setAmbient(float r, float g, float b, float a) {
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;
}
void Light::setDiffuse(float r, float g, float b, float a) {
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;
}
void Light::setSpecular(float r, float g, float b, float a) {
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;
}

void Light::draw() const {

	switch (lightID) {
	case 0:
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
		break;
	case 1:
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT1, GL_POSITION, pos);
		break;
	case 2:
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT2, GL_POSITION, pos);
		break;
	case 3:
		glLightfv(GL_LIGHT3, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT3, GL_POSITION, pos);
		break;
	case 4:
		glLightfv(GL_LIGHT4, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT4, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT4, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT4, GL_POSITION, pos);
		break;
	case 5:
		glLightfv(GL_LIGHT5, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT5, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT5, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT5, GL_POSITION, pos);
		break;
	case 6:
		glLightfv(GL_LIGHT6, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT6, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT6, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT6, GL_POSITION, pos);
		break;
	case 7:
		glLightfv(GL_LIGHT7, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT7, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT7, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT7, GL_POSITION, pos);
		break;
	}
	


}

