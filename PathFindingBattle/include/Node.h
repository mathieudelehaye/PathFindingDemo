#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "Position.h"

class Node { 
	Position pos;	
	int distance;
	int priority;
public:
	/** constructor **/
	Node(int x,int y, int d, int p); 

	/** getters for variables **/
	//current node xPosition
	int getxPos() const; 

	//current node yPosition
	int getyPos() const;

	//gscore
	int getDistance() const; 
 
	//fscore
	int getPriority () const;  

	int getNeighborX ();
	int getNeighborY ();
	int getNeighborDir();
	void resetNeighborSearch(); 
	bool foundNeighbor();

	/** Updates the priority; the lower the fscore the higer the priority
	* the fscore is the sum of:
	* -path-cost (gscore) (which is the distance from the starting node to the current node)
	* -heuristic estimate (hscore) (which is an estimate of the distance from the current node to the destination node)
	*
	**/
	void updatePriority(int xDest, int yDest); 

	void updateDistance(); 

	/** Estimate function for the remaining distance to the goal
	* here it's based on the Manhattan distance;
	* which is the distance between two points in a grid based on a strictly horizontal & veritcal path;
	* => sum of vertical & horizontal components
	**/
	int estimateDistance(int xDest, int yDest); 

	/** class functor (I think) to compare elements using:
	* operator overloading: "<" gets overloaded which we are going to use in our priority queue
	* to determine priority of a node in our queue;
	* returns true if node a has a lower fscore compared to node b
	*
	* there is an ambiguity here: < -- >; better to make both >
	* also prototype is now friend which could probably be replaced with this for the first
	* argument; it advantage is that because of the friend function the operand order can be reversed
	* this doesn't really looks to favor our application; so should I use it or not?
	**/
	//friend bool operator<(const Node & a, const Node & b); 
	friend bool operator<(const Node & a, const Node & b); 
};  
