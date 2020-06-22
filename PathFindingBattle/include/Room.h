#pragma once

#include <iostream>
#include "Tools.h"
using namespace std;

class Room { 
public: 
	int horizontalSize, verticalSize; 
	BArray<int> obstacle_map; // map of obstacles  
	Room(int hs, int vs);
}; 
