#include <iostream>
#include "COpponent.h"
#include "CBoard.h"
using namespace std;

Coordinate COpponent::GetTurnInput(CBoard PlayerBoard){
	Coordinate ComputerInput;
	cout << "Computer's turn!" << endl;
	//Chose a Square. If a ship has been located, the computer attempts to sink it. Otherwise a random shot is fired.
	ComputerInput = PlayerBoard.ComputerAI();

	//Display Computer output in the form eg. c4
	char computerx[1];
	computerx[0] = 'A' + ComputerInput.x;
	cout << "It Chooses: " << computerx[0] << ComputerInput.y << endl;

	return ComputerInput;
}

