#ifndef CBOARDSHIPS_H
#define CBOARDSHIPS_H
#include "CShip.h"

class CBoardShips
{
public:
	CShip Ship1;
	CShip Ship2;
	CShip Ship3;
	CShip ShipNull;

	void RecordShips(CShip ONE, CShip TWO, CShip THREE);
	CShip ShipDetails(int id);
};

#endif