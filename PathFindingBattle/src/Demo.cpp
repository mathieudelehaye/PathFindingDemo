#include "demo.h"

int Demo::Start()
{
	int fsmState = 0; 
	bool willAttack, quitLoop = false; 	
	char wantQuitGame = false;
	Character * j1 = new Character(4, 4, 2, 3, 3);
	Enemy * e1 = new Enemy(2, 1, 3, 2, 1, 8);
	Character * attacker; Character * defender; 
	Room* currentRoom = new Room(5, 4); 
	Pathfinder* pf = new Pathfinder(currentRoom);  
	int maxCaseNumber = 0; 
	int  charNewPosX, charNewPosY;
	string readString; 
	cout<<"\A* pathfinder battle game";
	cout<<"\n*************************\n";
	while(!quitLoop)
	{
		switch(fsmState)
		{
			case 0:	// initial state: describe situation and throw 1D6 
				#ifdef DEBUG_DEMO
                    cout<<"case 0 "; 
                #endif
				cout << "\n> You are in a room of dimensions "<<currentRoom->verticalSize<<" x "<<currentRoom->horizontalSize<<" (rows 1 -> "<<currentRoom->verticalSize<<" , columns 1 -> "<<currentRoom->horizontalSize<< ").\n";
				cout << "An orc stands in position R" << e1->getPosY() << "C" << e1->getPosX() << " (its characteristics: attack pts " << e1->getAP() << ", defense pts " << e1->getDP() << ", ";
				cout << e1->getHP() << " HP, move pts " << e1->getMD() << ").\n";
				cout << "You are in position R" << j1->getPosY() << "C" << j1->getPosX() << " (your characteristics: attack pts " << j1->getAP() << ", defense pts " << j1->getDP() << ", ";
				cout << j1->getHP() << " HP).\n";
				cout << "\nIt's your turn to play (press any key to throw 1 D6).\n";
				Tools::waitForAKey();
				Tools::throwDice(1, 6, &maxCaseNumber); 
				maxCaseNumber = 6; 
				cout<<"You throw a "<<maxCaseNumber<<".  You will: \n";
				fsmState = 1; 
				break;
			case 1: // choose between move and attack, pass turn of quit game
				#ifdef DEBUG_DEMO
                    cout<<"case 1 "; 
                #endif
				cout << "\n   1. Move and attack if an enemy is in next tile.\n";
				cout << "   2. Skip your turn.\n";
				cout << "   3. Quit game.\n";
				int choix;
				cin >> choix;
				switch(choix)
				{
					case 1:
						fsmState = 2; 
						break;
					case 2:
						cout << "\nIt's the orc's turn now.\n";
						j1->resetNeighborSearch(); 
						fsmState = 5; 
						break;
					case 3:
						fsmState = 7; 
						break;
				}
				break;
			case 2:	// enter player's new position and validate 
				#ifdef DEBUG_DEMO
                    cout<<"case 2 "; 
                #endif
				charNewPosX = 0; charNewPosY = 0; 
				cout << "\nEnter the row you wish to move to [now: "<<j1->getPosY()<<"]: ";
				readString = Tools::readAString(); 
				if(readString == "") charNewPosY = j1->getPosY();
				else charNewPosY = atoi(readString.c_str());
				cout << "Enter the column you wish to move to [now: "<<j1->getPosX()<<"]: ";
				readString = Tools::readAString(); 
				if(readString == "") charNewPosX = j1->getPosX();
				else charNewPosX = atoi(readString.c_str());
				// cout << "charNewPosX: "<<charNewPosX << ", charNewPosY: " << charNewPosY << "\n"; 
				if(charNewPosX<1 || charNewPosX>currentRoom->horizontalSize || charNewPosY<1 || charNewPosY>currentRoom->verticalSize || currentRoom->obstacle_map.getValueAt(charNewPosX,charNewPosY)==1 || 
					(charNewPosX==e1->getPosX() && charNewPosY== e1->getPosY()))
				{
					cout<<"\nPosition unavailable.  Please choose again.\n";
				}
				else {
					if (pf->calculatePath(j1->getPosX(), j1->getPosY(), charNewPosX, charNewPosY)) {
						if(pf->computedPathLength <= maxCaseNumber) {
							j1->move(charNewPosX, charNewPosY);
							cout<<"\nYou move to: R"<<charNewPosY<<"C"<<charNewPosX<<"\n";
							fsmState = 3; 
						}
						else {
							cout<<"\nPosition unavailable.  Please choose again.\n";
						}
					}
					else {
						cout<<"Error while computing path\n"; 
						return -1; 
					}
					break; 
				}
				break; 	
			case 3:	// check if monster can be reached given player's attack range 
				#ifdef DEBUG_DEMO
                    cout<<"case 3 "; 
                #endif
                willAttack = false; 
				if(j1->isNeighborOf(*e1)) {
					cout << "\nThe orc is near you.  Will you attack [y]: ";
					readString = Tools::readAString(); 
					if(readString == "" || readString == "y") { 
						cout << "\You attack the monster.\n";
						willAttack = true; 
						attacker = j1; defender = e1;
						fsmState = 4; 
					}
				}
				if(!willAttack) {
					cout << "\nYour turn is over.  It's now orc's turn.\n";
					j1->resetNeighborSearch(); 
					fsmState = 5; 
				}
				break; 
			case 4:	// resolve attack
				#ifdef DEBUG_DEMO
                    cout<<"case 4 "; 
                #endif
				
				if(Battle::resolve(attacker, defender)) { 
					cout << "\nIt's turn of "<<defender->type<<".\n";
					if(attacker->type == "player") {
						j1->resetNeighborSearch(); 
						fsmState = 5;	// if monster survives 
					} else { 
						fsmState = 0;	// if player survives
					}
				}
				else {
					fsmState = 8; 
				}
				break;
			case 5:	// it's monster'turn.  Search next free position round player 
				#ifdef DEBUG_DEMO
                    cout<<"case 5 "; 
                #endif
				if(j1->foundNeighbor()) { 
					if(!(j1->getNeighborX() <1 || j1->getNeighborY() <1 || j1->getNeighborX() > (currentRoom->horizontalSize) || j1->getNeighborY() > (currentRoom->verticalSize) 
						|| currentRoom->obstacle_map.getValueAt(j1->getNeighborX(),j1->getNeighborY())) == 1) {
						if(j1->getNeighborX()==e1->getPosX()&&j1->getNeighborY()==e1->getPosY()) {
							cout << "\Monster attacks the player.\n";
							attacker = e1; defender = j1;
							fsmState = 4;	
						}
						else fsmState = 6; 
					}
				}
				else fsmState = 0; 
				break;
			case 6:	// check if this position can be reached by monster within monster's move distance 
				#ifdef DEBUG_DEMO
                    cout<<"case 6 "; 
					cout <<"j1->getNeighborX(): "<<j1->getNeighborX()<<", j1->getNeighborY(): "<<j1->getNeighborY()<<", currentRoom->horizontalSize: "<<currentRoom->horizontalSize<<", currentRoom->verticalSize: "<<currentRoom->verticalSize<<"\n"; 
				#endif
				if (pf->calculatePath(e1->getPosX(), e1->getPosY(), j1->getNeighborX(), j1->getNeighborX())) {
					if(pf->computedPathLength <= e1->getMD()) {
						cout << "\nMonster moves to R"<<j1->getNeighborY()<<"C"<<j1->getNeighborX()<<" and attacks the player.\n";
						e1->move(j1->getNeighborX(), j1->getNeighborY()); 
						attacker = e1; defender = j1;
						fsmState = 4;	
					} else fsmState = 5; 
				} else {
					cout<<"Error while computing path\n"; 
					return -1; 
				}			
				break; 
			case 7:	// want to quit or not  
				#ifdef DEBUG_DEMO
                    cout<<"case 7 "; 
                #endif
				cout << "\nDo you really want to quit game (y/n): ";
				cin >> wantQuitGame;
				switch(wantQuitGame) 
				{
					case 121:	// 'y'
						fsmState = 8; 
						break;
					default: 
						fsmState = 0;	// if player survives 
						break; 
				}
				break;
			case 8:	// game is over  
				#ifdef DEBUG_DEMO
                    cout<<"case 8 "; 
                #endif
				cout << "\nGame is over.  Press any key to restart.\n";
				Tools::waitForAKey();
				quitLoop = true; 
				break;
		}
	}
	return 0;
}
