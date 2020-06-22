#pragma once

#include <iostream>
#include <string>

#include "Character.h"
#include "Tools.h"

using namespace std;

class Battle { 
public: 
	static int resolve(Character * attacker, Character * defender);
}; 
