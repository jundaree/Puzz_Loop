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

	void Reposition(float* front_center, float* back_center);

	void Insertion(float* front_center);
	
	Marble Return(); // velocity 초기화
	
	

	/*
	
	function MarbleFly_idle()
		getMode
		if fly
			if (!OutofBound())
				collision check outside 
					mode=REPOS
			else 
				canon.shoot_mode=READY;
		if REPOS 
			repos
			mode=insertion
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
	int insertion_frame;   // 10 
	int frame_count;  //0 -> 10
	float speed;
	
	
	Marble marble;


};

