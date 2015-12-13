#ifndef CGameState_H
#define CGameState_H

#include "CBoardShips.h"
#include "CBoard.h"

class CGameState
{
public:
	CGameState()
	{
		GameOver = false;
		PlayersTurn = true;
	}
	bool GameOver;
	bool PlayersTurn;
	bool CheckIfGameOver(CBoardShips ships, CBoard board, int hitId);
	bool IsPlayersTurn(int hitId, bool playersTurn);
};

#endif