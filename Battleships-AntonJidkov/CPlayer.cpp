#include <iostream>
#include "CPlayer.h"
#include "CBoard.h"
using namespace std;

Coordinate CPlayer::GetTurnInput(CBoard ComputerBoard){
	char playerinput[3];
	Coordinate Cplayerinput;

	cout << "Your turn!" << endl << "Enter square to hit (eg. B3): " << endl;
	bool correctinput = true;
	do{
		cin >> playerinput;
		Cplayerinput.x = playerinput[0] - 'A';
		Cplayerinput.y = playerinput[1] - '0';
		if (Cplayerinput.x<0 || Cplayerinput.x>9 || Cplayerinput.y<0 || Cplayerinput.y>9){
			cout << "Error!" << endl << "Make sure input is within range and in the form: eg. C4." << endl << "Please Re-enter: " << endl;
			correctinput = false;
		}
		else if (ComputerBoard.Board[Cplayerinput.y][Cplayerinput.x] == 3 || ComputerBoard.Board[Cplayerinput.y][Cplayerinput.x] == 2){
			cout << "You have taken a shot there already! Choose another one: " << endl;
			correctinput = false;
		}
		else{
			correctinput = true;
		}
	} while (correctinput == false);

	return Cplayerinput;
}