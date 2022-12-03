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
#include "Stage.h"
#include "Interface.h"


using namespace std;


Light light(boundaryX, boundaryY, boundaryX / 2, 0);

Interface interface;
InterStage intro(Texture(8, "Intro_1.jpg"),Texture(9, "Intro_2.png"), boundaryX/2,boundaryY/2,330.f,110.f);
InterStage win(Texture(10, "black_background.png"), Texture(11, "win.jpg"),0.0f, 0.0f, boundaryX, boundaryY);
InterStage lose(Texture(12, "black_background.png"), Texture(13, "lose.jpg"), 0.0f, 0.0f, boundaryX / 2, boundaryY / 2);
InterStage clear(Texture(14, "white_background.jpg"), Texture(15, "clear.jpg"), 0.0f, 0.0f, boundaryX / 2, boundaryY / 2);

vector<Stage> stages;

bool start=0;
int total_score = 0;
enum {INTRO,STAGE1,STAGE2,STAGE3,CLEAR1,CLEAR2,WIN,LOSE} sequence;
int clear_frame = 120;
int current_frame = 0;

clock_t start_clock = clock();
clock_t end_clock;
clock_t key_start_clock = clock();  //keyboardDown 함수에서 사용
clock_t key_end_clock;

void displayCharacters(void* font, string str, float x, float y) {
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++)
		glutBitmapCharacter(font, str[i]);
}

void initialize() {
	srand(unsigned int(time(0)));

	// Light
	light.setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
	light.setDiffuse(0.7f, 0.7f, 0.7f, 1.0f);
	light.setSpecular(1.0f, 1.0f, 1.0f, 1.0f);

	//stage
	sequence = INTRO;
	interface.initialize();
	intro.initialize();
	win.initialize();
	lose.initialize();
	clear.initialize();

	


	// game marble color assignment

	vector<Material> marble_mat;
	marble_mat.push_back(Material(1.0f, 0.0f, 0.0f));
	marble_mat.push_back(Material(0.0f, 1.0f, 0.0f));
	marble_mat.push_back(Material(0.0f, 0.0f, 1.0f));

	
	MarbleInRow MR1(1,10,1);
	MarbleInRow MR2(2, 10, 1);
	MarbleInRow MR3(1, 5, 1);
	MarbleInRow MR4(2, 5, 1);
	
	Canon canon(-200.0f, 0.0f, 0.0f, 25.0f);
	MarbleFly marbleFly;

	vector<MarbleInRow> vecMR1;
	vector<MarbleInRow> vecMR2;
	vector<MarbleInRow> vecMR3;
	vecMR1.push_back(MR1);
	vecMR2.push_back(MR2);
	vecMR3.push_back(MR3);
	vecMR3.push_back(MR4);

	stages.push_back(Stage(vecMR1,marble_mat,canon,marbleFly));
	marble_mat.push_back(Material(0.0f, 1.0f, 1.0f));
	stages.push_back(Stage(vecMR2, marble_mat, canon, marbleFly));
	stages.push_back(Stage(vecMR3, marble_mat, canon, marbleFly));

	for (auto& stage : stages)
		stage.initialize();

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
	
	switch (sequence) {
	case INTRO :
		intro.draw();
		break;
	case STAGE1:
	case STAGE2:
	case STAGE3:
		stages[sequence-1].draw();
		interface.draw();
		break;
	case CLEAR1:
	case CLEAR2:
		clear.draw();
		break;
	case WIN:
		win.draw();
		break;
	case LOSE:
		lose.draw();
		break;
	default:
		break;

	}

	//----draw-----

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	glutSwapBuffers();
	
}





void idle() {

	end_clock = clock();
	if (end_clock - start_clock > fps) {

		//-----idle start--------
	
	

		switch (sequence) {
		case INTRO:
			intro.idle();
			break;
		case STAGE1:
			
			if (stages[0].mode==Stage::WIN) {
				sequence = CLEAR1;
				total_score += stages[0].score;
				break;
			}
			else if (stages[0].mode == Stage::LOSE) {
				sequence = LOSE;
				break;
			}
		case STAGE2:
			
			if (stages[1].mode == Stage::WIN) {
				sequence = CLEAR2;
				total_score += stages[1].score;
				break;
			}
			else if (stages[1].mode == Stage::LOSE) {
				sequence = LOSE;
				break;
			}
			
				
		case STAGE3:
			
			if (stages[2].mode == Stage::WIN) {
				sequence = WIN;
				break;
			}
			else if (stages[2].mode == Stage::LOSE) {
				sequence = LOSE;
				break;
			}
			
			stages[sequence-1].idle();
			interface.setScore(total_score+stages[sequence-1].score);

			break;


		case CLEAR1:
			if (current_frame == clear_frame) {
				current_frame = 0;
				sequence = STAGE2;
				break;
			}
		case CLEAR2:
			if (current_frame == clear_frame) {
				current_frame = 0;
				sequence = STAGE3;
				break;
			}
			clear.idle();
			current_frame++;
			
			break;
		case WIN:
			win.idle();
			break;
		case LOSE:
			lose.idle();
			break;
		default:
			break;
		}
		
		
		

		//-------idle end-------------		
		start_clock = end_clock;
	}

	glutPostRedisplay();
}


void keyboardDown(unsigned char key, int x, int y) {
	key_end_clock = clock();
	if (key_end_clock - key_start_clock > fps) {
		// ------start------------

		
		switch (sequence) {
		case INTRO:
			sequence = STAGE1;
			break;
		case STAGE1:
		case STAGE2:
		case STAGE3:
			stages[sequence - 1].keyboardDown(key);
			interface.keyboardDown(key);
			break;
		case CLEAR1:
		case CLEAR2:
			break;
		case WIN:
			break;
		case LOSE:
			break;
		default:
			break;
		}
		

		//------- end-------------
		key_start_clock = end_clock;
	}


}

void keyboardUp(unsigned char key, int x, int y) {
	switch (sequence) {
	case INTRO:
		break;
	case STAGE1:
	case STAGE2:
	case STAGE3:
		stages[sequence - 1].keyboardUp(key);
		interface.keyboardUp(key);
		break;
		break;
	case CLEAR1:
	case CLEAR2:
		break;
	case WIN:
		break;
	case LOSE:
		break;
	default:
		break;

	}
	
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

