#pragma once
#include <iostream>
#include <vector>
#include <time.h>
#include<GL/glut.h>
#include "Marble.h"
#include "Constants.h"

using namespace std;

class MarbleInRow{
public:
	// Functions =====================================================
	MarbleInRow();
	MarbleInRow(int stage, int start, int gamespeed);

	// Functions for Loop
	vector<float> savedLoopInfo(float length);
	void setTotalLength();
	void createLoopMarble();

	// Functions for Marble
	void setMTLlist(vector<Material> marble_mat);
	void movePreProgress();
	void moveAll();
	
	void receiveMarble(Marble M, int idx_s, int idx_b);

	void isEraseOrInsert();

	void InsertMarble();

	void EraseCollisionMarble();
	void checkPullErase();
	void Pull_Erase();

	void draw() const;

	void move();	// Asemmble

	// Variables =====================================================
	vector <Marble> RowList;
	vector <Material> MTLlist;
	int idx_speed[3] = { 2,1,5 };	// [0] : Initial speed to bring marble from hided area / [1] : Normal Speed / [2] : Pulling speed 
	vector<vector<float>> loopPoints;

	enum class InRowMode { GAME_OVER, PRE_PROGRESS, OFF, COLLISION, INSERT, ERASE, PULL, PULLERASE};
	InRowMode Mode;
	Marble collisionMarble;
	vector<vector<float>> posInsert;

	int collisionIdx[2];
	int sameColorIdx[2];
	int pullCheckIdx;
	int pullIdx[2];

	int insertframe;

	int totalLength;
	int loopType;
	int startMarbleNum;
	int score;

	float radius;
	float linewidth;

	bool make_canon_ready;

};

