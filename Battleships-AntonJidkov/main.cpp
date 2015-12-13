#include <iostream>
#include <time.h>
#include "Coordinate.h"
#include "CShip.h"
#include "CBoard.h"
#include "CBoardships.h"
#include "CPlayer.h"
#include "COpponent.h"
#include "CDisplay.h"
using namespace std;

int main(){
		
	srand(time(NULL));//random seed

	//Pre-Game
	CBoardShips PlayerBoardShips;
	CBoard PlayerBoard;
	CShip Plship1=PlayerBoard.addship(4,0);
	CShip Plship2=PlayerBoard.addship(4,1);
	CShip Plship3=PlayerBoard.addship(5,2);
	PlayerBoardShips.RecordShips(Plship1, Plship2, Plship3);

	CBoardShips ComputerBoardShips;
	CBoard ComputerBoard;
	CShip Coship1=ComputerBoard.addship(4,0);
	CShip Coship2=ComputerBoard.addship(4,1);
	CShip Coship3=ComputerBoard.addship(5,2);
	ComputerBoardShips.RecordShips(Coship1, Coship2, Coship3);

	CPlayer player;
	COpponent opponent;
	CDisplay display;

	bool GameOver = false;
	bool PlayersTurn = true;

	display.StartGame(PlayerBoard);

	//Gameplay
	do{
		//Temp Variables
		CBoard activeBoard;
		Coordinate input;
		CBoardShips activeBoardShips;
		char playerinput [3] ;
		Coordinate Cplayerinput;
		Coordinate ComputerInput;

		if(PlayersTurn){		
			input=player.GetTurnInput(ComputerBoard);
			activeBoard = ComputerBoard;
			activeBoardShips = ComputerBoardShips;
		}
		else{//Computer's Turn					
			input = opponent.GetTurnInput(PlayerBoard);
			activeBoard = PlayerBoard;
			activeBoardShips = PlayerBoardShips;
		}

		//TAKING A TURN A hit ship id is returned or -1 if nothing is hit
		int hitid = activeBoard.TakeTurn(input.x, input.y);
				
		if(hitid!=-1){//Hit! An id is returned
			activeBoard.ProcessHit(input);

			//Check if the ship has sunk
			CShip hitship = activeBoardShips.ShipDetails(hitid); //Get the details of the hit ship
			bool sunk = activeBoard.CheckShipSunk(hitship.x, hitship.y, hitship.size, hitship.direction);//Check if the ship is sunk
			if(sunk==true){								
				//check if game over
				if (activeBoard.AnyShipsLeft() == true){//Game not over
					
				}
				else {//Game over
					GameOver=true;
				}
			}
		}

		if(PlayersTurn){
			ComputerBoard = activeBoard;
			Cplayerinput=input;
			ComputerBoardShips = activeBoardShips;
			cout<<"Computer's Board:"<<endl;//Display Board
			ComputerBoard.Display(false);
		}
		else{
			PlayerBoard = activeBoard;
			ComputerInput=input;
			PlayerBoardShips = activeBoardShips;
			cout<<"Your Board:"<<endl;//Display Board
			PlayerBoard.Display(true);
		}
		
		//if MISS, change turns 
		if(hitid==-1){
			if(PlayersTurn){
				PlayersTurn=false;
			}
			else{
				PlayersTurn=true;
			}
		}
	}while(!GameOver);

	display.HandleGameOver(PlayersTurn);

	return 0;
}