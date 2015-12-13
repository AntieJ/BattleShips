#ifndef CDISPLAY_H
#define CDISPLAY_H

#include "CBoard.h"

class CDisplay
{
public:
	void HandleGameOver(bool playersTurn);
	void StartGame(CBoard playerBoard);
};

#endif