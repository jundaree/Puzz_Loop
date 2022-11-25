#include "Material.h"

Material::Material(){}

Material::Material(float r, float g, float b) {
	setEmission(r * 0.1, g * 0.1, b * 0.1, 1.0f);
	setAmbient(r * 0.4, g * 0.4, b * 0.4, 1.0f);
	setDiffuse(r * 0.7, g * 0.7, b * 0.7, 1.0f);
	setSpecular(0.7f, 0.7f, 0.7f, 1.0f);
	setShininess(60.0f);
}

void Material::setEmission(float r, float g, float b, float a) {
	emission[0] = r;
	emission[1] = g;
	emission[2] = b;
	emission[3] = a;
}
void Material::setAmbient(float r, float g, float b, float a) {
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;
}
void Material::setDiffuse(float r, float g, float b, float a) {
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;
}
void Material::setSpecular(float r, float g, float b, float a) {
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;
}
void Material::setShininess(float sh) {
	shininess[0] = sh;
}

const float* Material::getEmission() const {
	return emission;
}
const float* Material::getAmbient() const {
	return ambient;
}
const float* Material::getDiffuse() const {
	return diffuse;
}
const float* Material::getSpecular() const {
	return specular;
}
const float* Material::getShininess() const {
	return shininess;
}
