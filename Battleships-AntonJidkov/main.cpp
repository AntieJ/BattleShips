#include <iostream>
#include <time.h>
#include "Coordinate.h"
#include "CShip.h"
#include "CBoard.h"
#include "CBoardships.h"
#include "CPlayer.h"
#include "COpponent.h"
#include "CDisplay.h"
#include "CGameState.h"
using namespace std;

int main(){
	srand(time(NULL));//random seed
	CBoardShips PlayerBoardShips;
	CBoard PlayerBoard;
	PlayerBoardShips.RecordShips(PlayerBoard.addship(4, 0), PlayerBoard.addship(4, 1), PlayerBoard.addship(5, 2));

	CBoardShips ComputerBoardShips;
	CBoard ComputerBoard;
	ComputerBoardShips.RecordShips(ComputerBoard.addship(4, 0), ComputerBoard.addship(4, 1), ComputerBoard.addship(5, 2));
		
	CGameState gameState;
	CDisplay display;
	display.StartGame(PlayerBoard);

	do{
		CBoard activeBoard;
		Coordinate input;
		CBoardShips activeBoardShips;

		if(gameState.PlayersTurn){	
			CPlayer player;
			input=player.GetTurnInput(ComputerBoard);
			activeBoard = ComputerBoard;
			activeBoardShips = ComputerBoardShips;
		}
		else{//Computer's Turn		
			COpponent opponent;
			input = opponent.GetTurnInput(PlayerBoard);
			activeBoard = PlayerBoard;
			activeBoardShips = PlayerBoardShips;
		}

		int hitid = activeBoard.TakeTurn(input.x, input.y);
				
		if(hitid!=-1){//Hit! A positive id is returned
			activeBoard.ProcessHit(input);
			gameState.GameOver = gameState.CheckIfGameOver(activeBoardShips, activeBoard, hitid);
		}

		if (gameState.PlayersTurn){
			ComputerBoard = activeBoard;
			ComputerBoardShips = activeBoardShips;
			cout<<"Computer's Board:"<<endl;
			ComputerBoard.Display(false);
		}
		else{
			PlayerBoard = activeBoard;
			PlayerBoardShips = activeBoardShips;
			cout<<"Your Board:"<<endl;
			PlayerBoard.Display(true);
		}
		
		gameState.PlayersTurn = gameState.IsPlayersTurn(hitid, gameState.PlayersTurn);

	} while (!gameState.GameOver);

	display.HandleGameOver(gameState.PlayersTurn);

	return 0;
}