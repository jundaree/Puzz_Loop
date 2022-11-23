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
	void moveAll();
	void moveByIndex(int start, int end);
	void insertMarble(Marble M, int idx);

	void draw() const;

	// Variables =====================================================
	vector <Marble> RowList;
	vector <Material> MTLlist;
	int idx_speed[3] = { 2,1,3 };	// [0] : Initial speed to bring marble from hided area / [1] : Normal Speed / [2] : Pulling speed 
	float radius;

	vector<vector<float>> loopPoints;

	float linewidth;
	int totalLength;

	int stageNum;
	int startNum;
};

