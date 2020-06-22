#include "Character.h"

Enemy::Enemy(int px, int py, int ap, int dp, int hp, int md) : Character(px, py, ap, dp, hp) {
	type = "monster"; 
	moveDistance = md;
}

int Enemy::getMD() { return moveDistance; }
