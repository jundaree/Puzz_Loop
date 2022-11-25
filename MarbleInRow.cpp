#include "MarbleInRow.h"


MarbleInRow::MarbleInRow() : stageNum(1), startNum(20), radius(25), linewidth(10) {
	//RowList.resize(20);
	cout << "constructor 1 called" << endl;
}

MarbleInRow::MarbleInRow(int stage, int start, int gamespeed) : stageNum(stage), startNum(start), radius(25), linewidth(10) {
	idx_speed[1] = gamespeed; 
	//RowList.resize(startNum);
	cout << "constructor 2 called" << endl;
}

void MarbleInRow::setMTLlist(vector<Material> marble_mat) {
	for(int i =0; i<marble_mat.size(); i++)
		MTLlist.push_back(marble_mat[i]);
}

void MarbleInRow::setTotalLength() {
	int hidedLength = startNum * radius * 2;
	totalLength = hidedLength;
	switch (stageNum) {
	case 1: totalLength += 2100; break;
	case 2: break;
	}
}

vector<float> MarbleInRow::savedLoopInfo(float length) {
	vector<float> coord(3);
	int hidedLength = startNum * radius * 2;
	switch (stageNum) {
	case 1:
		if (length < hidedLength + 800) {
			coord[0] = -boundaryX + length - hidedLength; coord[1] = 250; coord[2] = 0;
		}
		else if (length < hidedLength + 1300) {
			coord[0] = -boundaryX + 800; coord[1] = 250 - (length - hidedLength - 800);  coord[2] = 0;
		}
		else if (length < hidedLength + 2100) {
			coord[0] = (-boundaryX + 800) - (length - hidedLength - 1300); coord[1] = -250;  coord[2] = 0;
		}
		else {
			cout << "Marble center arrived at the last of the loop! Game should be end" << endl;
		}
		break;
	case 2:
		// for stage 2 
		break;
	}
	return coord;
}

void MarbleInRow::createLoopMarble() {

	setTotalLength();
	// create loop points
	for (int i = 0; i < totalLength; i++)
		loopPoints.push_back(savedLoopInfo(i));

	// set Marble radius, slice/stack, and initial center
	srand(unsigned int (time(0)));
	for (int i = 0; i < startNum; i++) {
		int j = rand()%3;
		Marble M;
		M.setMTL(MTLlist[j],j);
		M.setRadius(radius);
		M.setSlice(20);
		M.setStack(20);
		M.loopPointIdx = radius * 2 * i;
		M.setCenter(loopPoints[radius * 2 * i][0], loopPoints[radius * 2 * i][1], loopPoints[radius * 2 * i][2]);
		RowList.push_back(M);
	}
}

void MarbleInRow::draw() const {
	// draw marbles in row
	for (int i = 0; i < RowList.size(); i++)
		RowList[i].draw();

	// draw loop
	glDisable(GL_LIGHTING);
	glLineWidth(linewidth);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.5f, 0.5f, 0.5f);
	for (int i = 0; i < loopPoints.size(); i++)
		glVertex3f(loopPoints[i][0], loopPoints[i][1], loopPoints[i][2]);

	glEnd();
}

void MarbleInRow::moveAll() {
	for (int i = 0; i < RowList.size(); i++) {
		RowList[i].loopPointIdx += idx_speed[1];
		if (RowList[i].loopPointIdx >= loopPoints.size())
			RowList[i].loopPointIdx = 0;
		else {
			RowList[i].setCenter(loopPoints[RowList[i].loopPointIdx][0],
				loopPoints[RowList[i].loopPointIdx][1],
				loopPoints[RowList[i].loopPointIdx][2]);
		}
	}

}
void MarbleInRow::moveByIndex(int start, int end) {

}
void MarbleInRow::insertMarble(Marble M, int idx) {

}

