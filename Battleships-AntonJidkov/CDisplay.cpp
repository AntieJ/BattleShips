#include "CDisplay.h"
#include "CBoard.h"
using namespace std;
#include <iostream>

void CDisplay::HandleGameOver(bool playersTurn){
	if (playersTurn){
		cout << "YOU WIN! Congrats." << endl;
	}
	else{
		cout << "YOU LOSE! Try Minesweeper instead." << endl;
	}
	
	cout << "GAME OVER!" << endl;
	cin.ignore();
}

void CDisplay::StartGame(CBoard playerBoard){
	cout << "Battleships!\n" << "____________________________________________________\n" << endl;
	cout << "Player Board:" << endl;
	playerBoard.Display(true);
}