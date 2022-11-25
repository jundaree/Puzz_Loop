#pragma once

#include <iostream>
#include <vector>
#include <time.h>
#include <GL/glut.h>

#define WINDOW_X 100
#define WINDOW_Y 100

#define WINDOW_WIDTH 1200		// window's width
#define WINDOW_HEIGHT 640		// window's height

#define boundaryX (WINDOW_WIDTH)/2
#define boundaryY (WINDOW_HEIGHT)/2

#define PI 3.1415926
const float fps = 1000 / 60.0f;


inline float getDistance(std::vector<float> a, std::vector<float> b) {
	return sqrt((a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]) + (a[2] - b[2]) * (a[2] - b[2]));
}