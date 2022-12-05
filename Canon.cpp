#include "Canon.h"



void Canon::keyboardDown(unsigned char key) {
	switch (key) {
		case 'q':
		case 'Q':
			rot_angle = 5.0f;
			break;
		case 'w':
		case 'W':
			rot_angle = -5.0f;
			break;
		case ' ':
			if(shoot_mode==READY)
				shoot_mode=SHOOTED;
			break;

	}

	rotate();
	
}
void Canon::keyboardUp(unsigned char key) {
	switch (key) {
	case 'q':
	case 'Q':
		rot_angle = 0.0f;
		break;
	case 'w':
	case 'W':
		rot_angle = 0.0f;
		break;
	}
}


bool Canon::idle() {
	
	if (shoot_mode == SHOOTED)
		return true;
	return false;
}

void Canon::ready() {
	shoot_mode = READY;
}

void Canon::initialize(vector<Material> _marblesMtl) {
	//texture init

	texture.initTexture();

	//set marbles mtl
	
	marblesMtl = _marblesMtl;

	srand(unsigned int(time(0)));


	for (int i = 0;i < 2;i++) {
		Marble temp(marble_radius, 20, 20);
		temp.setCenter(0.0f, 0.0f, 0.0f);
		int mtl_idx = rand() % marblesMtl.size();
		temp.setMTL(marblesMtl[mtl_idx], mtl_idx);
		marbles.push(temp);
	}
}

Canon::Canon(float _centerX, float _centerY, float _centerZ, float _marble_radius) : 
	rot_angle(0),angle(0), texture(1, "canon.jpg"), marble_radius(_marble_radius),shoot_mode(BLOCK),speed(10.0f) {
	center[0] = _centerX;
	center[1] = _centerY;
	center[2] = _centerZ;
	
	
	/*
	 initialize Texture
	*/
	
	
}

void Canon::draw() {

	

	glPushMatrix();
	glTranslatef(center[0], center[1], center[2]);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	
	// Texture
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, texture.textureID);
	glBegin(GL_QUADS);

	/*glTexCoord2f(0.0f, 0.0f); glVertex3f(-100.f, -100.f,-50.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-100.f, 100.f,-50.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(100.f, 100.f,-50.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(100.f, -100.f, -50.0f);*/

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-80.f, 75.f, -50.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(80.f, 75.f, -50.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(80.f, -85.f, -50.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-80.f, -85.f, -50.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	

	//marbles

	marbles.back().draw();
	glTranslatef(2*marbles.front().radius, 0.0f, 0.0f);
	marbles.front().draw();

	glPopMatrix();


	
}

Marble Canon::shoot() {
	Marble transfer = marbles.front();
	
	
	marbles.pop();
	
	Marble new_marble(marble_radius, 20, 20);
	int mtl_idx = rand() % marblesMtl.size();
	new_marble.setMTL(marblesMtl[mtl_idx],mtl_idx);
	;
	new_marble.setCenter(0.0f, 0.0f, 0.0f);
	
	marbles.push(new_marble);

	
	shoot_mode = BLOCK;

	cout << "shoot!" << endl;

	float r = 2*transfer.getRadius();
	transfer.setCenter( center[0]+r* cos(angle * PI / 180), center[1] + r * sin(angle * PI / 180), center[2] + 0.0f);
	transfer.setVelocity(speed * (transfer.getCenterX()-center[0]) / 2 / transfer.getRadius(), speed * (transfer.getCenterY()-center[1]) / 2 / transfer.getRadius(), 0.0f);
	return transfer;	
}

void Canon::rotate() {
	angle += rot_angle;

	if (angle == 360.0f || angle == -360.0f)
		angle = 0.0f;

}