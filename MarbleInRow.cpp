#include "MarbleInRow.h"

MarbleInRow::MarbleInRow() : loopType(1), startMarbleNum(20), radius(25), linewidth(10), Mode(InRowMode::OFF), insertframe(0) {}

MarbleInRow::MarbleInRow(int loopTypeNum, int start, int gamespeed) : radius(25), linewidth(10), Mode(InRowMode::OFF), insertframe(0) {
	loopType = loopTypeNum;
	startMarbleNum = start;
	idx_speed[1] = gamespeed; 
}

void MarbleInRow::setMTLlist(vector<Material> marble_mat) {
	for(int i =0; i<marble_mat.size(); i++)
		MTLlist.push_back(marble_mat[i]);
}

void MarbleInRow::setTotalLength() {
	int hidedLength = startMarbleNum * radius * 2;
	totalLength = hidedLength;
	switch (loopType) {
	case 1: totalLength += (2100 + 2 * radius); break;
	case 2: break;
	}
}

vector<float> MarbleInRow::savedLoopInfo(float length) {
	vector<float> coord(3);
	int hidedLength = startMarbleNum * radius * 2;
	switch (loopType) {
	case 1:
		if (length < hidedLength + 800) {
			coord[0] = -boundaryX + length - hidedLength; coord[1] = 250; coord[2] = 0;
		}
		else if (length < hidedLength + 1300) {
			coord[0] = -boundaryX + 800; coord[1] = 250 - (length - hidedLength - 800);  coord[2] = 0;
		}
		else {
			coord[0] = (-boundaryX + 800) - (length - hidedLength - 1300); coord[1] = -250;  coord[2] = 0;
		}
		//else if (length < hidedLength + 2100) {
		//	coord[0] = (-boundaryX + 800) - (length - hidedLength - 1300); coord[1] = -250;  coord[2] = 0;
		//}
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
	
	cout << "loopPoints front point (x,y,z) = " << loopPoints.front()[0] << ", "
												<< loopPoints.front()[1] << ", "
												<< loopPoints.front()[2] << endl;
	cout << "loopPoints last point (x,y,z) = " << loopPoints.back()[0] << ", "
												<< loopPoints.back()[1] << ", " 
												<< loopPoints.back()[2] << endl;

	// set Marble radius, slice/stack, and initial center
	srand(unsigned int(time(0))); 
	int MTLtypeNum = MTLlist.size();
	for (int i = 0; i < startMarbleNum; i++) {
		int mtlType = rand() % MTLtypeNum;
		Marble M;
		M.setMTL(MTLlist[mtlType], mtlType);
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

	if (Mode == InRowMode::INSERT)
		collisionMarble.draw();

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

void MarbleInRow::receiveMarble(Marble M, int idx_s, int idx_b) {
	cout << "receiveMarble() called! | idx_s, idx_b = " << idx_s << ", " << idx_b << endl;
	collisionMarble = M;
	collisionIdx[0] = idx_s; collisionIdx[1] = idx_b;
	Mode = InRowMode::COLLISION;
	cout << "Mode changed to COLLISION" << endl;
}

void MarbleInRow::isEraseOrInsert() {
	cout << "isEraseOrInsert() called! | " ;
	int cnt1 = 0, cnt2 = 0;
	for (int i = collisionIdx[1]; i < RowList.size(); i++) {
		if (collisionMarble.mtl_idx == RowList[i].mtl_idx) {
			cnt1++;
		}
		else break;
	}
	for (int i = collisionIdx[0]; i >= 0; i--) {
		if (collisionMarble.mtl_idx == RowList[i].mtl_idx) {
			cnt2++;
		}
		else break;
	}
	if (cnt1 + cnt2 >= 2) {
		Mode = InRowMode::ERASE;
		cout << "Mode changed to ERASE" << endl;
		sameColorIdx[0] = collisionIdx[0] - (cnt2 - 1);
		sameColorIdx[1] = collisionIdx[1] + (cnt1 - 1) ;
		cout << "sameColor index : " << sameColorIdx[0] << " ~ " << sameColorIdx[1] << endl;
	}
	else { 
		Mode = InRowMode::INSERT;
		cout << "Mode changed to INSERT" << endl;
		posInsert.push_back( collisionMarble.getCenter() );
		if (collisionIdx[1] > RowList.size() - 1) {
			posInsert.push_back(loopPoints[ RowList[collisionIdx[0]].loopPointIdx + 2 * radius ]);
		}
		else posInsert.push_back(loopPoints[RowList[collisionIdx[1]].loopPointIdx]);
		cout << "Collision index : " << collisionIdx[0] << " ~ " << collisionIdx[1] << endl;
	}
}

void MarbleInRow::InsertMarble() {
	int frameBound = 2 * radius / idx_speed[0];
	if(insertframe == 0 ) cout << "InsertMarble() called!" << endl;

	if (insertframe < frameBound) {
		collisionMarble.setCenter(posInsert[0][0] + (posInsert[1][0] - posInsert[0][0]) * insertframe / frameBound,
						  		  posInsert[0][1] + (posInsert[1][1] - posInsert[0][1]) * insertframe / frameBound,
								  posInsert[0][2] + (posInsert[1][2] - posInsert[0][2]) * insertframe / frameBound);

		for (int i = collisionIdx[1]; i < RowList.size(); i++) {
			RowList[i].loopPointIdx += idx_speed[0];
			RowList[i].setCenter(loopPoints[RowList[i].loopPointIdx][0],
								loopPoints[RowList[i].loopPointIdx][1],
								loopPoints[RowList[i].loopPointIdx][2]);
		}
		insertframe++;
	}
	else {
		Mode = InRowMode::OFF;
		cout << "Mode changed to OFF" << endl;

		if (collisionIdx[1] > RowList.size() - 1) {
			collisionMarble.loopPointIdx = RowList[collisionIdx[0]].loopPointIdx + 2 * radius;
			cout << "1" << endl;
		}
		else {
			cout << "2" << endl;
			collisionMarble.loopPointIdx = RowList[collisionIdx[1]].loopPointIdx - 2 * radius;
		}
		RowList.insert(RowList.begin() + collisionIdx[1], collisionMarble);

		insertframe = 0;
		posInsert.pop_back();
		posInsert.pop_back();
		cout << "Updated RowList.size() : " << RowList.size() << endl;

	}
}

void MarbleInRow::EraseMarble() {

}

void MarbleInRow::moveByIndex(int start, int end) {

}

