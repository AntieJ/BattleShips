#ifndef CBOARD_H
#define CBOARD_H

#include <iostream>
#include "CShip.h"
#include "Coordinate.h"

using namespace std;
class CBoard
{
public:
	CBoard(){
		for(int i=0;i<10;i++){
			for(int c=0;c<10;c++){
				Board[i][c] = 0;
			}
		}
		ShipDamaged=false;
		LastShotCalibrated=false;
	}

	int Board[10][10];

	//-----Computer AI Variables
	bool ShipDamaged;
	Coordinate LastHit;//ontarget of ship
	Coordinate FirstHitOnTarget;//of ship
	bool LastShotMiss;
	bool LastShotCalibrated;//ie, the previous shot was going along the predicted length of a ship
	//------
	
	CShip addship(int size, int id);
	void Display(bool revealall);
	int TakeTurn(int x, int y);
	bool CheckShipSunk(int x, int y, int size, int direction);
	bool AnyShipsLeft();
	Coordinate ComputerAI();

	void ProcessHit(Coordinate input);

};

#endif