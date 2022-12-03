#include "Constants.h"
#include "Texture.h"


class Interface {
public:
	Interface();
	void setScore(int _score);
	void displayCharacters(void* font, string str, float x, float y);\
	void keyboardDown(unsigned char key);
	void keyboardUp(unsigned char key);
	void initialize();
	void draw();
	//void idle(score);

	bool q_down;
	bool w_down;
	int score;

	Texture q;
	Texture w;
	Texture q_pressed;
	Texture w_pressed;
	Texture spacebar;

};