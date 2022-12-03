#include "Interface.h"

Interface::Interface() : q(2, "keyboard_q.png"),
w(3, "keyboard_w.png"),
q_pressed(4, "keyboard_q_pressed.jpg"),
w_pressed(5, "keyboard_w_pressed.jpg"),
spacebar(6, "keyboard_spacebar.png"), q_down(0), w_down(0) {

}

void Interface::setScore(int _score) {
	score = _score;
}

void Interface::displayCharacters(void* font, string str, float x, float y) {
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++)
		glutBitmapCharacter(font, str[i]);
}

void Interface::keyboardDown(unsigned char key) {
	if (key == 'q' || key == 'Q')
		q_down = 1;
	else if (key == 'w' || key == 'W')
		w_down = 1;
}

void Interface::keyboardUp(unsigned char key) {
	if (key == 'q' || key == 'Q')
		q_down = 0;
	else if (key == 'w' || key == 'W')
		w_down = 0;
}

void Interface::initialize() {
	q.initTexture();
	w.initTexture();
	q_pressed.initTexture();
	w_pressed.initTexture();
	spacebar.initTexture();
}
void Interface::draw() {
	//white board
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(boundaryX * 2 / 3, -boundaryY, -10.0f); // A
	glVertex3f(boundaryX * 2 / 3, boundaryY, -10.0f); // B
	glVertex3f(boundaryX, boundaryY, -10.0f); // C
	glVertex3f(boundaryX, -boundaryY, -10.0f); // D
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);


	displayCharacters(GLUT_BITMAP_HELVETICA_12, "Q : CCW  /  W : CW", 450.0f / 600.0f * boundaryX, 0.0f);
	displayCharacters(GLUT_BITMAP_HELVETICA_12, "PRESS SPACEBAR TO SHOOT", 410.0f / 600.0f * boundaryX, -120.0f / 600.0f * boundaryX);
	displayCharacters(GLUT_BITMAP_HELVETICA_18, "SCORE : "+to_string(score), 450.0f / 600.0f * boundaryX, 200.0f / 320.0f * boundaryY);
	

	glEnable(GL_TEXTURE_2D);

	if (q_down) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, q_pressed.textureID);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(450.0f / 600.0f * boundaryX, 20.f / 600.0f * boundaryX, -5.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(450.f / 600.0f * boundaryX, 70.f / 600.0f * boundaryX, -5.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(500.f / 600.0f * boundaryX, 70.f / 600.0f * boundaryX, -5.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(500.f / 600.0f * boundaryX, 20.f / 600.0f * boundaryX, -5.0f);

		glEnd();

	}
	else {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, q.textureID);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(450.0f / 600.0f * boundaryX, 20.f / 600.0f * boundaryX, -5.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(450.f / 600.0f * boundaryX, 70.f / 600.0f * boundaryX, -5.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(500.f / 600.0f * boundaryX, 70.f / 600.0f * boundaryX, -5.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(500.f / 600.0f * boundaryX, 20.f / 600.0f * boundaryX, -5.0f);

		glEnd();
	}

	if (w_down) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, w_pressed.textureID);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(500.f / 600.0f * boundaryX, 20.f / 600.0f * boundaryX, -5.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(500.f / 600.0f * boundaryX, 70.f / 600.0f * boundaryX, -5.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(550.f / 600.0f * boundaryX, 70.f / 600.0f * boundaryX, -5.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(550.f / 600.0f * boundaryX, 20.f / 600.0f * boundaryX, -5.0f);

		glEnd();

	}
	else {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, w.textureID);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(500.f / 600.0f * boundaryX, 20.f / 600.0f * boundaryX, -5.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(500.f / 600.0f * boundaryX, 70.f / 600.0f * boundaryX, -5.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(550.f / 600.0f * boundaryX, 70.f / 600.0f * boundaryX, -5.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(550.f / 600.0f * boundaryX, 20.f / 600.0f * boundaryX, -5.0f);

		glEnd();

	}

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, spacebar.textureID);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(450.0f / 600.0f * boundaryX, -100.f / 600.0f * boundaryX, -5.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(450.f / 600.0f * boundaryX, -50.f / 600.0f * boundaryX, -5.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(550.f / 600.0f * boundaryX, -50.f / 600.0f * boundaryX, -5.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(550.f / 600.0f * boundaryX, -100.f / 600.0f * boundaryX, -5.0f);

	glEnd();

	glDisable(GL_TEXTURE_2D);

	//MR.sendScore
}