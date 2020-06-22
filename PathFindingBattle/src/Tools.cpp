#include "tools.h"

// Throw a dice of faceNumber faces and fill out values into an array 
void Tools::throwDice(int diceNumber, int faceNumber, int* resultArray)
{
	Urand draw(6);
	for(int i=0; i< 10000000; i++);	// wait for several cycles before reading clock value  
	clock_t t = clock(); 
	if(t == clock_t(-1)) {
		cerr << "sorry, no clock\n";
		// return(-1);
		return;
	}
	/*else
	{
		cout << "t: " << t << "\n"; 
	}*/
	for (int i = 0; i < t; i++) { draw(); }
	if(diceNumber>maxDiceNumber) {
		cout<<"Tools::throwDice: no more than "<<maxDiceNumber<<" dices allowed\n"; 
	}
	else {
		for (int i = 0; i < diceNumber; i++)
		{
			resultArray[i] = draw()+1;

		}
	}
}

// Wait for player's keystroke 
void Tools::waitForAKey()
{
	int i; 
	fflush(stdin); 
	while((i = getchar()) != EOF) { break; }
}

string Tools::readAString()
{
	int i; 	
	string outString = ""; 
	fflush(stdin); 
	while((i = getchar()) != EOF) { 		
		if(i == '\n') { break; }
		else { outString += char(i); }
	}
	return outString; 
}
