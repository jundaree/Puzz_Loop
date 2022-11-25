#pragma once
#include<iostream>
#include<GL/glut.h>
#include <vector>
#include "Material.h"

using namespace std;

class Marble{
public:
	Marble();
	Marble(float r, int sl, int st);
	void setRadius(float r);
	float getRadius() const;
	void setSlice(int sl);
	void setStack(int st);
	
	void setCenter(float x, float y, float z);
	float getCenterX() const;
	float getCenterY() const;
	float getCenterZ() const;
	vector<float> getCenter() const;

	void setVelocity(float x, float y, float z);
	float getVelocityX() const;
	float getVelocityY() const;
	float getVelocityZ() const;
	vector<float> getVelocity() const;
	
	void move();
	void setMTL(const Material& m, int _mtl_idx);
	void draw() const;

	float radius;
	int slice;
	int stack;
	int loopPointIdx;
	float center[3];
	float velocity[3];

	Material mtl;

	int mtl_idx;

};


