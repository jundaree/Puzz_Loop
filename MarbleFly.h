#pragma once
#include"Constants.h"
#include "Material.h"
#include "Marble.h"



class MarbleFly
{
public :

	/*
	Mode에 Merging 추가
	merging frame
	*/

	MarbleFly();
	
	void setMarble(Marble marble); // mode = fly;

	bool OutofBound(); // if OutofBound, mode=off

	void Reposition(vector<float> front_center, vector<float> back_center);
	
	Marble Return(); // velocity 초기화	
	

	/*
	
	collision check
		for (cosnt marble& mb : marbleinRow.vector)
			collisiondetected



	function MarbleFly_idle()
		marblefly getMode
		
		if fly
			if (!OutofBound())
				collision check outside 
					marblfly.mode=REPOS
					marbleinRow.
			else 
				canon.shoot_mode=READY;
		
		if REPOS 
			marblfly.repos
			marbleinRow.accept(marblfly.Return());
			marblefly.mode=INSERT

		if INSERT
			Insertion
			frame_count++
				if frame_count ==10 
					return marble
						mode=OFF
		if 
		else (OFF)
			nothing

	*/
	
	
	MarbleFlyMode getMode();
	void setMode(MarbleFlyMode _mode);

	void move();

	void draw();


	MarbleFlyMode mode;
	int reposition_frame;
	int insertion_frame;   // 10 
	int frame_count;  //0 -> 10
	float speed;
	
	
	Marble marble;


};

