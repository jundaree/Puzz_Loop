/*
패치노트


*/

/*


*/

#include <vector>
#include <time.h>
#include "Light.h"
#include "Marble.h"
#include "Canon.h"
#include "MarbleFly.h"

using namespace std;


vector<Marble> spheres;
Light light(boundaryX, boundaryY, boundaryX / 2, 0);
clock_t start_clock = clock();
clock_t end_clock;
clock_t key_start_clock = clock();  //keyboardDown 함수에서 사용
clock_t key_end_clock;

vector<Material> marble_mat;

Canon canon(0.f,0.f,0.f,30.0f);
MarbleFly marbleFly;


void initialize() {

	// game marble color assignment
	marble_mat.push_back(Material(1.0f, 0.0f, 0.0f));
	marble_mat.push_back(Material(0.0f, 1.0f, 0.0f));
	marble_mat.push_back(Material(0.0f, 0.0f, 1.0f));
	
	//Canon
	canon.initialize(marble_mat);


	//Light
	light.setAmbient(1.0f, 1.0f, 1.0f, 1.0f);
	light.setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
	light.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
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

	//--------draw start-----------

	light.draw();
	canon.draw();
	marbleFly.draw();

	//--------draw end-----------

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();

}


void MarbleFlyControl() {
	switch (marbleFly.getMode()) {
	case MarbleFlyMode::FLY:
		if (!marbleFly.OutofBound()) {
			//Collision Detection
		}
		else {
			canon.shoot_mode = canon.READY;
		}
		break;
	case MarbleFlyMode::REPOS:
		//marbleFly.Reposition(float* front_center, float* back_center);
		break;
	case MarbleFlyMode::INSERT:
		//marbleFly.Insertion(float* front_center);
		break;
	default:
		break;
	}
}

void idle() {

	end_clock = clock();
	if (end_clock - start_clock > fps) {

		//-----idle start--------
		
		marbleFly.move();

		if (canon.idle()) {  //return true if the marble needs to be transfered
			marbleFly.setMarble(canon.shoot());
		}

		MarbleFlyControl();

		//-------idle end-------------
		start_clock = end_clock; 
	}

	glutPostRedisplay();
}

void keyboardDown(unsigned char key, int x, int y) {
	key_end_clock = clock();
	if (key_end_clock - key_start_clock > fps) {
		// ------start------------

		canon.keyboardDown(key);

		//------- end-------------
		key_start_clock = end_clock;
	}
	
	
}

void keyboardUp(unsigned char key, int x, int y) {
	canon.keyboardUp(key);
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
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);

	glutMainLoop();
	return 0;
}

