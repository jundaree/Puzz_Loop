#include "Stage.h"


InterStage::InterStage(Texture _texture, Texture f_texture, float x, float y, float x_size, float y_size)
	: texture(_texture), flickeringTexture(f_texture), f_mode(ON), flicker_frame(30), current_frame(0), fpos{ x, y, 0 }, fsize{ x_size,y_size } {
	
}

void InterStage::initialize() {
	texture.initTexture();
	flickeringTexture.initTexture();
}
void InterStage::draw() {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture.textureID);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-boundaryX, -boundaryY, -50.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-boundaryX, boundaryY, -50.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(boundaryX, boundaryY, -50.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(boundaryX, -boundaryY, -50.0f);

	glEnd();
	if (f_mode) {
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, flickeringTexture.textureID);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f); glVertex3f(fpos[0] - fsize[0] / 2, fpos[1] -fsize[1] / 2, -40.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(fpos[0] -fsize[0]/2, fpos[1]+fsize[1]/2, -40.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(fpos[0]+fsize[0]/2, fpos[1]+fsize[1]/2, -40.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(fpos[0]+fsize[0]/2, fpos[1] -fsize[1]/2, -40.0f);

		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

}
void InterStage::idle() {
	current_frame++;
	if (current_frame == flicker_frame) {
		current_frame = 0;
		if (f_mode == ON)
			f_mode = OFF;
		else
			f_mode = ON;
	}
		
}


//--------------------------------------------------------------------------------------------------------------------


Stage::Stage(vector<MarbleInRow> _vecMR, vector<Material> _marble_mat, Canon _canon, MarbleFly _marblefly)
	: vecMR(_vecMR),marble_mat(_marble_mat),canon(_canon),marblefly(_marblefly), mode(NONE), score(0)
{
}
void Stage::keyboardDown(unsigned char key) {
	canon.keyboardDown(key);
}
void Stage::keyboardUp(unsigned char key) {
	canon.keyboardUp(key);
}
void Stage::initialize() {
	//Canon
	canon.initialize(marble_mat);

	// Loop
	for (auto& MR : vecMR) {
		MR.setMTLlist(marble_mat);
		MR.createLoopMarble();
	}
}
void Stage::idle() {
	for (auto& MR : vecMR)
		MR.move();

	marblefly.move();

	if (canon.idle()) {  //return true if the marble needs to be transfered
		marblefly.setMarble(canon.shoot());
	}

	MarbleFlyControl();

	bool win = 1;
	for (auto& MR : vecMR) {
		if (MR.RowList.size() != 0)
			win = 0;
	}
	if (win)
		mode = WIN;

	for (auto& MR : vecMR) {
		if (MR.Mode == MarbleInRow::InRowMode::GAME_OVER)
			mode = LOSE;
	}

	score = 0;
	for (auto& MR : vecMR) {
		score += MR.score;
	}
	

}
void Stage::draw() {
	canon.draw();
	marblefly.draw();
	for (auto& MR : vecMR) {
		MR.draw();
	}
}

bool Stage::CollisionDetectionWithHandling() {
	for (auto& MR : vecMR) {
		for (int i = 0; i < MR.RowList.size(); i++) {
			vector<float> row_marble_center = MR.RowList[i].getCenter();
			float distance = getDistance(MR.RowList[i].getCenter(), marblefly.marble.getCenter());
			if (distance <= 2 * marblefly.marble.getRadius()) {
				int loopidx = MR.RowList[i].loopPointIdx;
				vector<float> imaginary_center_back = MR.loopPoints[loopidx - 2 * MR.RowList[i].getRadius()];
				vector<float> imaginary_center_front = MR.loopPoints[loopidx + 2 * MR.RowList[i].getRadius()];
				float distance_front = getDistance(imaginary_center_front, marblefly.marble.getCenter());
				float distance_back = getDistance(imaginary_center_back, marblefly.marble.getCenter());
				if (distance_front < distance_back) {
					marblefly.Reposition(imaginary_center_front, MR.RowList[i].getCenter());
					MR.receiveMarble(marblefly.Return(), i, i + 1);
				}
				else {
					marblefly.Reposition(MR.RowList[i].getCenter(), imaginary_center_back);
					MR.receiveMarble(marblefly.Return(), i - 1, i);
				}
				return true;
			}
		}
		
	}
	return false;
	

}

void Stage::MarbleFlyControl() {
	if (marblefly.isFlying()) {
		if (!marblefly.OutofBound()) {
			if (CollisionDetectionWithHandling()) {
				canon.shoot_mode = canon.READY;
				marblefly.setMode(MarbleFly::Mode::OFF);
			}
		}
		else {
			canon.shoot_mode = canon.READY;
		}
	}
}





