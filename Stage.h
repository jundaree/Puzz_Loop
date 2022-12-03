#pragma once
#include "Constants.h"
#include "Light.h"
#include "MarbleInRow.h"
#include "MarbleFly.h"
#include "Canon.h"



class InterStage
{
public:
	InterStage(Texture _texture, Texture f_texture, float x, float y, float x_size, float y_size);

	void initialize();
	void draw();
	void idle();
	
	
	enum F_MODE {OFF, ON} f_mode;
	int current_frame;
	int flicker_frame;
	Texture texture;
	Texture flickeringTexture;

	float fsize[2];
	float fpos[3];
};

class Stage {
public :
	
	Stage(vector<MarbleInRow> _vecMR, vector<Material> _marble_mat,Canon _canon, MarbleFly _marblefly);


	void keyboardDown(unsigned char key);
	void keyboardUp(unsigned char key);
	void initialize();
	void idle(); 
	void draw();

	bool CollisionDetectionWithHandling();
	void MarbleFlyControl();


	enum {NONE,WIN,LOSE} mode;
	int score;
	vector<MarbleInRow> vecMR;
	vector<Material> marble_mat;
	Canon canon;
	MarbleFly marblefly;
	
};



