#include "node.h"

Node::Node(int x,int y, int d, int p) : pos(x, y) {
	distance=d;
	priority=p;
}

int Node::getxPos() const { return pos.getX(); }
int Node::getyPos() const { return pos.getY(); }
int Node::getDistance() const { return distance; }
int Node::getPriority() const { return priority; }

int Node::getNeighborX() { return pos.getNeighborX(); }
int Node::getNeighborY() { return pos.getNeighborY(); }
int Node::getNeighborDir() { return pos.getNeighborDir(); }

void Node::resetNeighborSearch() { pos.resetNeighborSearch(); } 
bool Node::foundNeighbor() { return pos.foundNeighbor(); }

void Node::updatePriority(int xDest, int yDest) {
	priority = distance + estimateDistance(xDest,yDest)*10;
}

void Node::updateDistance() { //const int & direction
	distance +=10;
}

int Node::estimateDistance(int xDest, int yDest) {
	int xDistance, yDistance, totalDistance;
	xDistance=xDest-pos.getX();
	yDistance=yDest-pos.getY();
	totalDistance=abs(xDistance)+abs(yDistance);
	return (totalDistance);
}

bool operator<(const Node & a, const Node & b) {
	return a.getPriority() > b.getPriority();
}
