#include <iostream>
#include <vector>
#include <time.h>
#include <GL/glut.h>
#include "Light.h"
#include "Marble.h"

using namespace std;

#define WINDOW_X 650
#define WINDOW_Y 200

#ifndef WINDOW_WIDTH

#define WINDOW_WIDTH 640		// window's width
#define WINDOW_HEIGHT 640		// window's height

#endif

#define boundaryX (WINDOW_WIDTH)/2
#define boundaryY (WINDOW_HEIGHT)/2



vector<Marble> spheres;
Light light(boundaryX, boundaryY, boundaryX / 2, 0);
clock_t start_clock = clock();
clock_t end_clock;
const float fps = 1000 / 30.0f;


void initialize() {

	light.setAmbient(1.0f, 1.0f, 1.0f, 1.0f);
	light.setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
	light.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
	

	spheres.push_back(Marble(50, 15, 15));
	spheres.push_back(Marble(50, 15, 15));
	spheres.push_back(Marble(50, 15, 15));

	spheres[0].setCenter(-100.0f,-40.0f,0.0f);
	spheres[0].setVelocity(0.0f, 8.0f, 0.0f);
	spheres[0].setMTL(Material(0.0f,1.0f,0.5f));

	spheres[1].setCenter(120.0f, -40.0f, 0.0f);
	spheres[1].setVelocity(3.0f, -6.0f, 0.0f);
	spheres[1].setMTL(Material(1.0f, 0.0f, 1.0f));

	spheres[2].setCenter(140.0f, 140.0f, 0.0f);
	spheres[2].setVelocity(-3.0f, 6.0f, 0.0f);
	spheres[2].setMTL(Material(1.0f, 0.0f, 0.5f));

}


	

void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	light.draw();
	
	for (Marble& sp : spheres) // & 안 쓰면 계속 copy constructor 발생
		sp.draw();

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
	
}



float getDistance(const Marble& sph1, const Marble& sph2) {
	float disp_x = sph1.getCenterX() - sph2.getCenterX();
	float disp_y = sph1.getCenterY() - sph2.getCenterY();

	return sqrt(disp_x * disp_x + disp_y * disp_y);
}

bool isCollisionDetected(const Marble& sph1, const Marble& sph2) {
	/* Implement: collision detection */

	float distance = getDistance(sph1, sph2);
	if (distance <= sph1.getRadius() + sph2.getRadius())
		return true;
	else
		return false;
}

void handleCollision(Marble& sph1, Marble& sph2) {
	if (isCollisionDetected(sph1, sph2)) {
		/* Implement: collision handling */
		float distance = getDistance(sph1, sph2);
		float dot_product = (sph1.getVelocityX() - sph2.getVelocityX()) * (sph1.getCenterX() - sph2.getCenterX())
			+(sph1.getVelocityY() - sph2.getVelocityY()) * (sph1.getCenterY() - sph2.getCenterY());

		float v1_x = sph1.getVelocityX() - dot_product / (distance * distance) * (sph1.getCenterX() - sph2.getCenterX());
		float v2_x= sph2.getVelocityX() - dot_product / (distance * distance) * (sph2.getCenterX() - sph1.getCenterX());
		
		float v1_y= sph1.getVelocityY() - dot_product / (distance * distance) * (sph1.getCenterY() - sph2.getCenterY());
		float v2_y = sph2.getVelocityY() - dot_product / (distance * distance) * (sph2.getCenterY() - sph1.getCenterY());

		sph1.setVelocity(v1_x, v1_y,0.0f);
		sph2.setVelocity(v2_x, v2_y,0.0f);

	}
}

void idle() {

	end_clock = clock();
	if (end_clock - start_clock > fps) {
		for (int i = 0; i < spheres.size(); i++) {
			for (int j = i + 1; j < spheres.size(); j++)
				handleCollision(spheres[i], spheres[j]);
		}

		for (Marble& sp : spheres)
			sp.move();

		start_clock = end_clock;
	}

	glutPostRedisplay();
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Move three spheres and handle their collisions");

	initialize();

	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}

