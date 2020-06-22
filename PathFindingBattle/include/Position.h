/*
 *	Class that allows to manipulate position of a node or character. 
 */
#pragma once

#include <queue>
using namespace std;

#define DIR_RIGHT 0
#define DIR_DOWN 1 
#define DIR_LEFT 2
#define DIR_UP 3

class Position { 
public: 
    static const int nbrDir=4;	//dimensions 
	static int dirX[nbrDir], dirY[nbrDir];
private: 
	int xValue, yValue; 
	priority_queue<int> dir;	//priority list for neighbor directions 
	int neighborDir; 
public:
	Position(int x, int y);
	int getX () const;
	int getY () const;
	int getNeighborX ();
	int getNeighborY ();
	int getNeighborDir();
	bool isNeighborOf (Position neighborPos); 
	void change(int px, int py);
	void resetNeighborSearch();
	bool foundNeighbor();
};  
