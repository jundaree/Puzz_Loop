#pragma once
#include"Constants.h"
#include "Material.h"
#include "Marble.h"



class MarbleFly
{
public :
	enum class Mode { OFF, FLY } mode;

	MarbleFly();
	
	void setMarble(Marble marble); // mode = fly;

	bool OutofBound(); // if OutofBound, mode=off

	void Reposition(vector<float> front_center, vector<float> back_center);
	
	Marble Return(); // velocity ÃÊ±âÈ­	
	

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
	


	bool isFlying();
	void setMode(Mode _mode);

	void move();

	void draw();


	
	int reposition_frame;
	int insertion_frame;   // 10 
	int frame_count;  //0 -> 10
	float speed;
	
	
	Marble marble;


};

