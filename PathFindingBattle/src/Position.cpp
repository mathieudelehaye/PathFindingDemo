#include "Position.h"

Position::Position(int px, int py) { 
	xValue = px;
	yValue = py;
}

int Position::dirX[nbrDir] = {1,0,-1,0}; 
int Position::dirY[nbrDir] = {0,-1,0,1}; 

int Position::getX() const { return xValue; }
int Position::getY() const { return yValue; }

int Position::getNeighborX() { return xValue+dirX[neighborDir]; }
int Position::getNeighborY() { return yValue+dirY[neighborDir]; }
int Position::getNeighborDir() { return neighborDir; }
	
bool Position::isNeighborOf(Position neighborPos) {
	bool rValue = false;
	if(neighborPos.getX() == xValue) {
		if((neighborPos.getY() == yValue +1)||(neighborPos.getY() == yValue -1)) {
			rValue = true; 
		}
	} else if(neighborPos.getY() == yValue) {
		if((neighborPos.getX() == xValue +1)||(neighborPos.getX() == xValue -1)) {
			rValue = true; 
		}
	}
	return rValue; 
}

void Position::change(int px, int py) { 
	xValue = px; 
	yValue = py; 
}

void Position::resetNeighborSearch() {
	while(!dir.empty()) 
	{
		dir.pop();	// empty queue
	}
	dir.push(DIR_RIGHT);dir.push(DIR_DOWN);dir.push(DIR_LEFT);dir.push(DIR_UP);	// then fill it with the four directions
}

bool Position::foundNeighbor() {
	if(!dir.empty()) {
		neighborDir = dir.top(); //read next available direction
		dir.pop(); 
		return true; 
	}
	else return false;
}
