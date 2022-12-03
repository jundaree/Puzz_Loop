#pragma once
#include "Constants.h"
#include <queue>
#include <random>
#include <cmath>
#include "Marble.h"
#include "Texture.h"



using namespace std;

class Canon
{
public :
	
	/*
	void keyboardDown(...){
		canon.keyboardDown(key);
	}
	*/

	void keyboardDown(unsigned char key);
	void keyboardUp(unsigned char key);

	/*
	if (canon.idle())  //return true if the marble needs to be transfered
		marbleFly=canon.shoot();
	
	*/

	bool idle(); // placed in idle function, return true if it needs to shoot
	
	void ready(); // called when marblefly vanish
	
	void initialize(vector<Material> _marblesMtl); //when initialize, set marblesmtl, and init texture

	Canon(float _centerX, float _centerY, float _centerZ, float _marble_radius);
	void draw();
	Marble shoot();  // transfer the marble, rearrange the marbles vector, and create new marble using marblesMtl
	void rotate();  
	

	float speed;
	enum { BLOCK, READY, SHOOTED } shoot_mode;  // 0: not ready to shoot, 1: ready to shoot, 2: immediately after pressed 'spacebar'
	float center[3];
	float angle;
	float rot_angle; 
	queue<Marble> marbles;
	Texture texture;
	vector<Material> marblesMtl;
	float marble_radius;
};

