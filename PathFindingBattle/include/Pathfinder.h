#pragma once 

#include <queue>
#include <ctime>
#include <string>
#include <cstring>

#include "Node.h"
#include "Tools.h"
#include "Room.h"

using namespace std;

// #define DEBUG_PATHFINDING   
// #define DEBUG_PATHFINDING_C_NUMBERS

/** Pathfinding (A* algo) using Manhatten heuristics and assuming a monotonic, consistent
* heuristic (the enemies do not change position)
*
* TODO: add variable terrain cost
**/
class Pathfinder { 
	Room* associatedRoom; 
    BArray<int> openNodes; // the set of nodes to be evaluated; initialy only containing start node
	BArray<int> closedNodes; // the set of nodes already evaluated
    BArray<int> dir_map; // map of directions (contains parentschildren connection)
public:
	Pathfinder(Room* ar); 
    void resetMaps(); 
    bool calculatePath(const int & xStart, const int & yStart,const int & xFinish, const int & yFinish); 
    string computedPath; 
    int computedPathLength; 
    double computingTimeInMs; 
};  
