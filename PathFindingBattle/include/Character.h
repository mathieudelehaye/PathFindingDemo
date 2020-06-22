#pragma once

#include <stdio.h>
#include <iostream>

#include "Position.h"

using namespace std;

class Character { 
protected: 
	Position pos;	
	int attackPoints;
	int defensePoints; 
	int hitPoints; 
public:
	Character(int px, int py, int ap, int dp, int hp);
	void move(int px, int py);
	void incrementHPBy(int diff);
	int getPosX();
	int getPosY();
	int getAP();
	int getDP();
	int getHP();
	int getNeighborX ();
	int getNeighborY ();
	void resetNeighborSearch();
	bool foundNeighbor();
	bool isNeighborOf (Position p); 
	bool isNeighborOf (Character chara); 
	string type; 
};  

class Enemy : public Character {	
	int moveDistance; 
public: 
	Enemy(int px, int py, int ap, int dp, int hp, int md);
	int getMD(); 
}; 
