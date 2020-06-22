#include "battle.h"

int Battle::resolve(Character * attacker, Character * defender) {
	int totalAttack = 0, totalDefense = 0; 
	int diceResults[Tools::maxDiceNumber]; 
	for(int i = 0; i < Tools::maxDiceNumber; i++) {
		diceResults[i] = 0;
	}
	Tools::throwDice(attacker->getAP()+defender->getDP(), 6, diceResults);  
	cout << "\nDice throws of the " << attacker->type << ": ";
	for(int i = 0; i<attacker->getAP();i++) {
		totalAttack += diceResults[i]; 
		cout<<diceResults[i]; 
		if(i != attacker->getAP()-1) {
			cout<<", "; 
		}
	}
	cout <<"\n"; 
	cout << "\nDice throws of the " << defender->type << ": ";
	for(int i = 0; i<defender->getDP();i++) {
		totalDefense += diceResults[attacker->getAP()+i]; 
		cout<<diceResults[attacker->getAP()+i]; 
		if(i != defender->getDP()-1) {
			cout<<", "; 
		}
	}
	cout <<"\n"; 
	cout << "\nTotal attack pts: " << totalAttack << ", " << "total defense pts: " << totalDefense << ".\n";
	if (totalAttack > totalDefense) { 
		cout << "\nThe " << attacker->type << " deals 1 dammage point to the " << defender->type << ".\n";
		defender->incrementHPBy(-1); 
	}
	else
	{
		cout << "\nThe " << attacker->type << " misses the " << defender->type << ".\n";
	}
	if(defender->getHP() <= 0) { 
		cout << "\nThe " << attacker->type << " kills the " << defender->type << ".\n";
		return 0; 
	} 
	else { 
		cout << "\nThe " << defender->type << " survives.\n";
		return 1; 
	} 
}
