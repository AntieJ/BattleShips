#ifndef COPPONENT_H
#define COPPONENT_H

#include "Coordinate.h"
#include "CBoard.h"

class COpponent
{
public:
	Coordinate GetTurnInput(CBoard PlayerBoard);
};

#endif