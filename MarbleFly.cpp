#include "MarbleFly.h"


MarbleFly::MarbleFly() : mode(MarbleFlyMode::OFF), reposition_frame(10),insertion_frame(10), speed(10.0f), frame_count(0) {

}

void MarbleFly::setMarble(Marble _marble) {
	marble = _marble;
	//speed.x=speed*cos(Angle) = speed * center.x / (2*getRadius())
	marble.setVelocity(speed * marble.getCenterX() / 2 / marble.getRadius(), speed * marble.getCenterY() / 2 / marble.getRadius(),0.0f);
	mode = MarbleFlyMode::FLY;
	reposition_frame = 10;
	insertion_frame = 10;
}

bool MarbleFly::OutofBound() {
	float x = marble.getCenterX();
	float y = marble.getCenterY();
	float r = marble.getRadius();

	if ((x > boundaryX + r) || (x < -boundaryX - r) || (y > boundaryY + r) || (y < -boundaryY - r)) {
		mode = MarbleFlyMode::OFF;
		return true;
	}
	return false;
}

void MarbleFly::Reposition(vector<float> front_center, vector<float> back_center) {
	float x1 = back_center[0];
	float y1 = back_center[1];
	float x2 = front_center[0];
	float y2 = front_center[1];


	vector<float> candidate_1;
	candidate_1.push_back( 1.0f/2*(x2 - x1)- sqrt(3.0f) / 2.0f * (y2 - y1) + x1);
	candidate_1.push_back( sqrt(3.0f) / 2 *(x2 - x1) + 1.0f / 2 * (y2 - y1) + y1);
	candidate_1.push_back(0.0f);

	vector<float> candidate_2;
	candidate_2.push_back( 1.0f / 2 * (x2 - x1) + sqrt(3.0f) / 2 * (y2 - y1) + x1);
	candidate_2.push_back(-sqrt(3.0f) / 2 * (x2 - x1) + 1.0f / 2 * (y2 - y1) + y1);
	candidate_2.push_back(0.0f);

	std::cout << " front: " << front_center[0] << " " << front_center[1] << " " << front_center[2] << std::endl;
	std::cout << " back: " << back_center[0] << " " << back_center[1] << " " << back_center[2] << std::endl;
	std::cout << " c1: " << candidate_1[0] << " " << candidate_1[1] << " " << candidate_1[2] << std::endl;
	std::cout << " c2: " << candidate_2[0] << " " << candidate_2[1] << " " << candidate_2[2] << std::endl;


	if (getDistance(candidate_1, this->marble.getCenter()) < getDistance(candidate_2, this->marble.getCenter())) {
		this->marble.setCenter(candidate_1[0], candidate_1[1], candidate_1[2]);
	}
	else {
		this->marble.setCenter(candidate_2[0], candidate_2[1], candidate_2[2]);
	}


	
}


Marble MarbleFly::Return() {
	setMode( MarbleFlyMode::OFF);
	marble.setVelocity(0.0f, 0.0f, 0.0f);
	return marble;
}

MarbleFlyMode MarbleFly::getMode() {
	return mode;
}

void MarbleFly::setMode(MarbleFlyMode _mode) {
	mode = _mode;
}

void MarbleFly::move() {
	if(mode==MarbleFlyMode::FLY)
		marble.move();
}

void MarbleFly::draw() {
	if (mode!=MarbleFlyMode::OFF)
		marble.draw();
}



