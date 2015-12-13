#include "CGameState.h"
#include "CShip.h"
#include "CBoardShips.h"
#include "CBoard.h"

bool CGameState::CheckIfGameOver(CBoardShips ships, CBoard board, int hitId){
	CShip hitship = ships.ShipDetails(hitId);
	bool sunk = board.CheckShipSunk(hitship.x, hitship.y, hitship.size, hitship.direction);
	if (sunk){
		if (board.AnyShipsLeft()){
			return false;
		}
		else {
			return true;
		}
	}
}

bool CGameState::IsPlayersTurn(int hitId, bool playersTurn){
	if (hitId == -1){
		if (playersTurn){
			return false;
		}
		else{
			return true;
		}
	}
}