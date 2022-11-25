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
	
	void receiveMarble(Marble M, int idx_s, int idx_b);

	void isEraseOrInsert();

	void InsertMarble();

	void EraseMarble();
	void moveByIndex(int start, int end);

	void draw() const;


	// Variables =====================================================
	vector <Marble> RowList;
	vector <Material> MTLlist;
	int idx_speed[3] = { 2,1,5 };	// [0] : Initial speed to bring marble from hided area / [1] : Normal Speed / [2] : Pulling speed 
	vector<vector<float>> loopPoints;

	enum class InRowMode { OFF, INSERT, ERASE, PULL};
	InRowMode Mode;
	Marble collisionMarble;
	int collisionIdx[2];
	int sameColorIdx[2];

	vector<vector<float>> posInsert;
	int insertframe;

	int totalLength;
	int loopType;
	int startMarbleNum;

	float radius;
	float linewidth;
};

