#ifndef CPLAYER_H
#define CPLAYER_H

#include "Coordinate.h"
#include "CBoard.h"

class CPlayer
{
public:
	Coordinate GetTurnInput(CBoard ComputerBoard);
};

#endif