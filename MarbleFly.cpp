#include "MarbleFly.h"


MarbleFly::MarbleFly() : mode(MarbleFlyMode::OFF), insertion_frame(10), speed(10.0f), frame_count(0) {

}

void MarbleFly::setMarble(Marble _marble) {
	marble = _marble;
	//speed.x=speed*cos(Angle) = speed * center.x / (2*getRadius())
	marble.setVelocity(speed * marble.getCenterX() / 2 / marble.getRadius(), speed * marble.getCenterY() / 2 / marble.getRadius(),0.0f);
	mode = MarbleFlyMode::FLY;
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

void MarbleFly::Reposition(float* front_center, float* back_center) {
	/*
	*/
}
void MarbleFly::Insertion(float* front_center) {
	/*
	*/
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



