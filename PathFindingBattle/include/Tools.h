#pragma once

#include <stdio.h>
#include <iostream>
#include <ctime>
#include <sstream>

#include "Randomgen.h"

using namespace std;

class Tools { 
public: 
	static const int maxDiceNumber = 10; // max number of dice for throwDice
	static void throwDice(int diceNumber, int faceNumber, int* resultArray);
	static void waitForAKey(); 
	static string readAString();
	template <typename T> static string NumberToString(T pNumber)
	{
		 ostringstream oOStrStream;
		 oOStrStream << pNumber;
		 return oOStrStream.str();
	}
}; 

// class template for a ("board") array of type T with indices from 1 to WIDTH or 1 to HEIGHT (rather than 0 to WIDTH-1 or 0 to HEIGHT-1)
template <class T> class BArray 
{
	T** board_array; 
	T initialValue; 
public:		
	int horizontalSize;
	int verticalSize;
	BArray(int hs, int vs, T initVal) {
		horizontalSize = hs;
		verticalSize = vs; 
		board_array = new T*[horizontalSize];
		for(int i = 0; i < horizontalSize; ++i)
	    {
	        board_array[i] = new T[verticalSize];
	    }
	    initialValue = initVal; reset();
	}
	~BArray() {
		for(int i = 0; i < horizontalSize; ++i) 
	    {
	        delete [] board_array[i];
	    }
	    delete [] board_array;
	}
	T getValueAt(int x, int y);	//	x must be comprised between 1 and horizontalSize, y between 1 and verticalSize
	void setValueAt(int x, int y, T valueToSet);
	void display();
	void reset(); 
};

// TODO surdefine operators '[]'' and '=' to avoid using get and set functions 
template <class T> T BArray<T>::getValueAt(int x, int y) { return board_array[x-1][y-1]; }	
template <class T> void BArray<T>::setValueAt(int x, int y, T valueToSet) { board_array[x-1][y-1]=valueToSet; } 
template <class T> void BArray<T>::display() { 
	for(int j = 0;j< verticalSize;j++) {
        cout<<"\n"; 
        for(int i = 0; i < horizontalSize;i++) { cout<<board_array[i][j]; }
    }	
}
template <class T> void BArray<T>::reset() { 
	for(int j = 0;j< verticalSize;j++) {
        for(int i = 0; i < horizontalSize;i++) { board_array[i][j] = initialValue; }
    }	
}
