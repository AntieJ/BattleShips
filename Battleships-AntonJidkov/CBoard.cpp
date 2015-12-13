#include <iostream>
#include <time.h>
#include "CBoard.h"
#include "CShip.h"
using namespace std;

CShip CBoard::addship(int size, int id){
	
	bool shipfound=false;
	bool shipoverlap=true;
	int direction;
	int startx;
	int starty;	

	//--------Create ship, avoiding overlaps or offboard positions
	do{
		startx=rand()%10;
		starty=rand()%10;

		//Direction 
		if(startx>(10-size) && starty<(10-size)){//Constrain to avoid off board
			direction=1;
		}
		else if(starty>(10-size) && startx<(10-size)){
			direction=0;
		}
		else{
			direction=rand()%2;		
		}

		//Check for overlaps
		if(startx<(10-size) || starty<(10-size)){
			shipoverlap=false;
			//ship horizontal
			if(direction==0){
				for(int x=startx; x<startx+size;x++){
						if((Board[starty][x]-1)%10==0){
							shipoverlap=true;
						}
				}
			}
			//ship vertical
			if(direction==1){
				for(int y=starty; y<starty+size;y++){
					if((Board[y][startx]-1)%10==0){
						shipoverlap=true;
					}
				}
			}
			if(!shipoverlap){
				shipfound=true;
			}
		}
	} while(!shipfound); 

	//-------Add the ship to the board
	//ship horizontal
	if(direction==0){
		for(int x=startx; x<startx+size;x++){
			Board[starty][x]=id*10+1;				
		}
	}
	//ship vertical
	if(direction==1){
		for(int y=starty; y<starty+size;y++){
			Board[y][startx]=id*10+1;
		}
	}

	CShip returnship;
	returnship.x=startx;
	returnship.y=starty;
	returnship.direction=direction;
	returnship.id=id;
	returnship.size=size;
	return returnship;
}

void CBoard::Display(bool revealall){//Display the Board
	
	cout<<"   A   B   C   D   E   F   G   H   I   J"<< endl;
	cout<<"   -------------------------------------"<< endl;
	for(int i=0;i<10;i++){
		printf("%i| ", i);
		for(int c=0;c<10;c++){
			char displaycharacter [1];
			if(Board[i][c]==2){
				displaycharacter[0]='H';//for hit
			}
			else if(Board[i][c]==3){
				displaycharacter[0]='M';//for miss
			}
			else if(Board[i][c]==0){
				if(revealall==true){
					displaycharacter[0]='~';//for empty
				}
				else{
					displaycharacter[0]='?';//HIDDEN!
				}					
			}
			else{
				if(revealall==true){
					displaycharacter[0]='S';//for ship
				}
				else{
					displaycharacter[0]='?';//HIDDEN!
				}					
			}
			printf("%c   ", displaycharacter[0]);		
		}
		cout<< endl;
	}
	cout<< endl;
}
	
int CBoard::TakeTurn(int x, int y){
	
	if((Board[y][x]-1)%10==0){
		cout<<"HIT!"<<endl;
		int hitid=(Board[y][x]-1)/10;//record the ship id
		Board[y][x]=2;//Signify a hit
		LastShotMiss=false;			
		//Return the ship id
		return hitid;
	}
	else{
		cout<<"MISS!"<<endl;
		Board[y][x]=3;//Signify a miss.
		LastShotMiss=true;
		return -1;
	}
}

bool CBoard::CheckShipSunk(int x, int y, int size, int direction){ //Returns true if sunk, false if not sunk		
	bool shipsunk=true;
	if(direction==0){//Horizontal Ship
		for(int i=x; i<x+size; i++){
			if(Board[y][i]!=2){
				shipsunk=false;
			}
		}
	}
	else{//Vertical Ship
		for(int i=y; i<y+size; i++){
			if(Board[i][x]!=2){
				shipsunk=false;
			}
		}
	}

	if(shipsunk==true){
		cout<<"The ship has been sunk!"<<endl;
		ShipDamaged=false;//The ship is damaged beyond repair! The computer no longer tries to destroy it.
		return true;
	}
	else{
		ShipDamaged=true;
		return false;
	}
}

bool CBoard::AnyShipsLeft(){//Checks the board for remaining ships
	for(int y=0;y<10;y++){
		for(int x=0;x<10;x++){
			if(Board[y][x]!=0 && Board[y][x]!= 2 && Board[y][x]!= 3){
				return true;								
			}
		}
	}
	return false;
}

Coordinate CBoard::ComputerAI(){
	Coordinate ReturnCoordinate;
	int loopcounter=0;
	do{//Search for clever shots
		if(ShipDamaged==true){//a ship has been damaged but not destroyed. The Computer attempts to sink it!

			//If the last shot was a miss, it was calibrated, and the ship is not destroyed return the lasthit to the first hit on ship.
			if(LastShotMiss==true && LastShotCalibrated==true){
				LastHit.x = FirstHitOnTarget.x;//original ship hit
				LastHit.y = FirstHitOnTarget.y;
			}		

			//Check for Adjacent previous hits. 
			//If a hit exists (2), shoot in the opposite direction to predict the ship

			bool adjacenthits=false;
			//x
			if(Board[LastHit.y][LastHit.x-1]==2 && Board[LastHit.y][LastHit.x+1]!=3){
				adjacenthits=true;
				ReturnCoordinate.x=LastHit.x+1;
				ReturnCoordinate.y=LastHit.y;
			}
			if(Board[LastHit.y][LastHit.x+1]==2 && Board[LastHit.y][LastHit.x-1]!=3){
				adjacenthits=true;
				ReturnCoordinate.x=LastHit.x-1;
				ReturnCoordinate.y=LastHit.y;
			}			
			//y
			if(Board[LastHit.y-1][LastHit.x]==2 && Board[LastHit.y+1][LastHit.x]!=3){
				adjacenthits=true;
				ReturnCoordinate.x=LastHit.x;
				ReturnCoordinate.y=LastHit.y+1;
					
			}
			if(Board[LastHit.y+1][LastHit.x]==2 && Board[LastHit.y-1][LastHit.x]!=3){
				adjacenthits=true;
				ReturnCoordinate.x=LastHit.x;
				ReturnCoordinate.y=LastHit.y-1;
			}
			//If the end of a ship has been reached but no shots can be taken further (blocked by a previous miss or hit), reset the ship hit
			if(adjacenthits==false && (LastHit.x!=FirstHitOnTarget.x) && (LastHit.y!=FirstHitOnTarget.y)){
				LastHit.x = FirstHitOnTarget.x;//original ship hit
				LastHit.y = FirstHitOnTarget.y;

				adjacenthits=true;
				ReturnCoordinate.x=-1;
				ReturnCoordinate.y=-1;
			}
			
			//if there are no previous adjacent hits, take a random adjacent hit.
			if(adjacenthits==false){//|| lastshotfullycalibrated==true
				int randomdirection=rand()%4;

				if(randomdirection==0){
					ReturnCoordinate.x=LastHit.x+1;
					ReturnCoordinate.y=LastHit.y;
				}
				if(randomdirection==1){
					ReturnCoordinate.x=LastHit.x-1;
					ReturnCoordinate.y=LastHit.y;
				}
				if(randomdirection==2){
					ReturnCoordinate.x=LastHit.x;
					ReturnCoordinate.y=LastHit.y+1;
				}
				if(randomdirection==3){
					ReturnCoordinate.x=LastHit.x;
					ReturnCoordinate.y=LastHit.y-1;
				}
				LastShotCalibrated=false;
			}
			else {//If there are previous adjacent hits, the coordinates have been set as above.
				LastShotCalibrated=true;
				//If the coordinates are out of bounds (and this ship is unsunk). return it to the first hit.
				if(ReturnCoordinate.y==-1 || ReturnCoordinate.x==-1 || ReturnCoordinate.y==10 || ReturnCoordinate.x==10){
					LastHit.x = FirstHitOnTarget.x;//original ship hit
					LastHit.y = FirstHitOnTarget.y;
				}
			}
		}
		else{//No partially damaged ships exist. The Computer takes a random shot.
			ReturnCoordinate.x=rand()%10;
			ReturnCoordinate.y=rand()%10;
		}

		if(loopcounter>30){//Prevent any infinite loops
			ReturnCoordinate.x=rand()%10;
			ReturnCoordinate.y=rand()%10;
		}
		loopcounter++;
	}while(Board[ReturnCoordinate.y][ReturnCoordinate.x]==3 || Board[ReturnCoordinate.y][ReturnCoordinate.x]==2 || ReturnCoordinate.y==-1 || ReturnCoordinate.x==-1 || ReturnCoordinate.y==10 || ReturnCoordinate.x==10);
	
	return ReturnCoordinate;		
}

void CBoard::ProcessHit(Coordinate input){
	//Record the Hit
	LastHit.x = input.x;
	LastHit.y = input.y;

	if (!ShipDamaged){
		ShipDamaged = true;//Record that the ship has been damaged
		FirstHitOnTarget = input;//Record the first hit that was on target
	}
}