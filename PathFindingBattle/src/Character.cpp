#include "Character.h"

Character::Character(int px, int py, int ap, int dp, int hp) : pos(px, py) { 
	attackPoints = ap;
	defensePoints = dp;
	hitPoints = hp; 
	type = "player";
}

void Character::move(int px, int py) { 
	pos.change(px, py); 
}

void Character::incrementHPBy(int diff) {
	hitPoints += diff; 
}

int Character::getPosX() { return pos.getX(); }
int Character::getPosY() { return pos.getY(); }
int Character::getAP() { return attackPoints; }
int Character::getDP() { return defensePoints; }
int Character::getHP() { return hitPoints; }

int Character::getNeighborX () { return pos.getNeighborX(); }
int Character::getNeighborY () { return pos.getNeighborY(); }
void Character::resetNeighborSearch() { pos.resetNeighborSearch(); }
bool Character::foundNeighbor() {  return pos.foundNeighbor(); }

bool Character::isNeighborOf (Position p) { return p.isNeighborOf(pos); }
bool Character::isNeighborOf (Character chara) { return isNeighborOf(Position(chara.getPosX(), chara.getPosY())); } 
