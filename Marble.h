#pragma once
#include<iostream>
#include<GL/glut.h>
#include "Material.h"

#ifndef WINDOW_WIDTH

#define WINDOW_WIDTH 640		// window's width
#define WINDOW_HEIGHT 640		// window's height

#endif

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

	void setVelocity(float x, float y, float z);
	float getVelocityX() const;
	float getVelocityY() const;
	float getVelocityZ() const;
	
	void move();
	void setMTL(const Material& m);
	void draw() const;

	float radius;
	int slice;
	int stack;
	int loopPointIdx;
	float center[3];
	float velocity[3];

	Material mtl;
};


