#include "Marble.h"

Marble::Marble() {
	
}
Marble::Marble(float r, int sl, int st) : radius(r),slice(sl),stack(st) {
	
}


void Marble::setRadius(float r){
	radius = r;
}
float Marble::getRadius() const {
	return radius;
}
void Marble::setSlice(int sl) {
	slice = sl;
}
void Marble::setStack(int st) {
	stack = st;
}
void Marble::setCenter(float x, float y, float z) {
	center[0] = x;
	center[1] = y;
	center[2] = z;
}

void Marble::setVelocity(float x, float y, float z) {
	velocity[0] = x;
	velocity[1] = y;
	velocity[2] = z;
}

float Marble::getCenterX() const {
	return center[0];
}
float Marble::getCenterY() const {
	return center[1];
}
float Marble::getCenterZ() const {
	return center[2];
}

float Marble::getVelocityX() const {
	return velocity[0];
}
float Marble::getVelocityY() const{
	return velocity[1];
}
float Marble::getVelocityZ() const {
	return velocity[2];
}

void Marble::setMTL(const Material& m) {
	mtl = m;
}
void Marble::move() {

	center[0] += velocity[0];
	center[1] += velocity[1];
	center[2] += velocity[2];
	
}
void Marble::draw() const {
	glPushMatrix();
	
	
	glTranslatef(center[0], center[1], center[2]);
	
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_EMISSION, mtl.getEmission());
	glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, mtl.getShininess());
	glutSolidSphere(getRadius(), slice, stack);

	glPopMatrix();
}