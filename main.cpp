/*
수정사항

1. Marble.h에 getCenter(), getVelocity() 함수 추가 (vector<float>반환)
2. MarbleInRow getCenterIdx() 함수 필요없음
3. Constants.h에 GetDistance() 추가

논의사항
1. Loop의 끝부분 경로 연장
2. REPOS Frame과 mode, canon SHOOTED 삭제?
3. Constants.h에 라이브러리 모아놓기

*/


#include <iostream>
#include <vector>
#include <time.h>
#include <GL/glut.h>
#include "Constants.h"
#include "Light.h"
#include "Marble.h"
#include "MarbleInRow.h"
#include "MarbleFly.h"
#include "Canon.h"


using namespace std;

MarbleInRow MR;
vector<Material> marble_mat;

Canon canon(0.f, 0.f, 0.f, 25.0f);
MarbleFly marbleFly;

Light light(boundaryX, boundaryY, boundaryX / 2, 0);
clock_t start_clock = clock();
clock_t end_clock;
clock_t key_start_clock = clock();  //keyboardDown 함수에서 사용
clock_t key_end_clock;

void initialize() {
	// game marble color assignment
	marble_mat.push_back(Material(1.0f, 0.0f, 0.0f));
	marble_mat.push_back(Material(0.0f, 1.0f, 0.0f));
	marble_mat.push_back(Material(0.0f, 0.0f, 1.0f));

	//Canon
	canon.initialize(marble_mat);

	light.setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
	light.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	light.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);

	MR.setMTLlist(marble_mat);
	MR.createLoopMarble();
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


	//----draw-----

	light.draw();
	canon.draw();
	marbleFly.draw();
	
	//--------
	MR.draw();

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
	
}



bool CollisionDetectionWithHandling() {
	/* Implement: collision detection */

	for (int i = 0; i < MR.RowList.size(); i++) {
		vector<float> row_marble_center = MR.RowList[i].getCenter();
		float distance = getDistance(MR.RowList[i].getCenter(), marbleFly.marble.getCenter());
		if (distance <= 2 * marbleFly.marble.getRadius()) {

			if (i == 0) {
				int loopidx = MR.RowList[i].loopPointIdx;
				vector<float> imaginary_center = MR.loopPoints[loopidx - 2 * MR.RowList[i].getRadius()];
				float distance_front = getDistance(MR.RowList[i + 1].getCenter(), marbleFly.marble.getCenter());
				float distance_back = getDistance(imaginary_center, marbleFly.marble.getCenter());
				if (distance_front < distance_back) {
					marbleFly.Reposition(MR.RowList[i + 1].getCenter(), MR.RowList[i].getCenter());
					MR.receiveMarble(marbleFly.Return(),i,i+1);
				}
				else {
					marbleFly.Reposition(MR.RowList[i].getCenter(), imaginary_center);
					MR.receiveMarble(marbleFly.Return(),i-1,i);
				}
			}
			else if (i == MR.RowList.size() - 1) {
				int loopidx = MR.RowList[i].loopPointIdx;
				vector<float> imaginary_center = MR.loopPoints[loopidx + 2 * MR.RowList[i].getRadius()];
				float distance_front = getDistance(imaginary_center, marbleFly.marble.getCenter());
				float distance_back = getDistance(MR.RowList[i - 1].getCenter(), marbleFly.marble.getCenter());
				if (distance_front < distance_back) {
					marbleFly.Reposition(imaginary_center, MR.RowList[i].getCenter());
					MR.receiveMarble(marbleFly.Return(),i,i+1);
				}
				else {
					marbleFly.Reposition(MR.RowList[i].getCenter(), MR.RowList[i - 1].getCenter());
					MR.receiveMarble(marbleFly.Return(),i-1,i);

				}


			}
			else {
				float distance_front = getDistance(MR.RowList[i + 1].getCenter(), marbleFly.marble.getCenter());
				float distance_back = getDistance(MR.RowList[i - 1].getCenter(), marbleFly.marble.getCenter());
				if (distance_front < distance_back) {
					marbleFly.Reposition(MR.RowList[i + 1].getCenter(), MR.RowList[i].getCenter());
					MR.receiveMarble(marbleFly.Return(),i,i+1);
				}
				else {
					marbleFly.Reposition(MR.RowList[i].getCenter(), MR.RowList[i - 1].getCenter());
					MR.receiveMarble(marbleFly.Return(),i-1,i);
				}

			}


			return true;

		}

	}
	return false;

}

void MarbleFlyControl() {
	if(marbleFly.isFlying()){
		if (!marbleFly.OutofBound()) {
			if (CollisionDetectionWithHandling()) {
				canon.shoot_mode = canon.READY;
				marbleFly.setMode(MarbleFly::Mode::OFF);
			}
		}
		else {
			canon.shoot_mode = canon.READY;
		}
	}
}

void idle() {

	end_clock = clock();
	if (end_clock - start_clock > fps) {
		//-----idle start--------

		if (MR.Mode == MarbleInRow::InRowMode::OFF)
			MR.moveAll();
		else if (MR.Mode == MarbleInRow::InRowMode::INSERT)
			MR.InsertMarble();


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

