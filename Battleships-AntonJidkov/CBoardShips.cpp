#include <iostream>
#include <time.h>
#include "CBoardShips.h"
#include "CShip.h"

void CBoardShips::RecordShips(CShip ONE, CShip TWO, CShip THREE){
		Ship1=ONE;
		Ship2=TWO;
		Ship3=THREE;
	}

CShip CBoardShips::ShipDetails(int id){
	if(id==0){
		return Ship1;
	}
	if(id==1){
		return Ship2;
	}
	if(id==2){
		return Ship3;
	}
	return ShipNull;
}