#pragma once
#include "DisplayableObject.h"
#include "MovementPosition.h"
#include "TDTileManager.h"
#include "TDPlayState.h"
#include <iostream>
#include <string>
#include <list>

using namespace std; 

class TDBaseEnemy :
	public DisplayableObject
{
public:
	struct mapSquare {
		int x;   // Declare member types  
		int y;
	};

	TDBaseEnemy(BaseEngine* pEngine, int iMapX, int iMapY, int delay);
	~TDBaseEnemy();
	list<mapSquare> FindPath();
	mapSquare AddCurrentSquareToOpen();
	void Draw();
	void SetMovement(int iStartTime, int iEndTime, int iCurrentTime,
		int iStartX, int iStartY, int iEndX, int iEndY);
	MovementPosition getMovementPosition();
	void SetPosition(double dX, double dY);
	void SetSpeed(int newSpeed);
	void DoUpdate(int iCurrentTime);
	int ManhattanDist(int iX1, int iY1, int iX2, int iY2);
	bool CheckInBounds(int tileX, int tileY);
	mapSquare GetSquareWithLowestF();
	bool Contains(list<TDBaseEnemy::mapSquare>squareList, TDBaseEnemy::mapSquare square);
	list<mapSquare> PopulateAdjacentSquares(mapSquare currentSquare);
	void FollowPath();
	void ReduceHealth(int damage);
	
	void TDBaseEnemy::PrintClassType(){
		string s = typeid(this).name();
		cout << "class created, type = " << s << endl;
	}

private:
	MovementPosition m_oMover;
	BaseEngine* m_pMainEngine;
	TDPlayState* playStateEngine = dynamic_cast<TDPlayState*>(GetEngine());
	int m_iDir = 0;
	list<mapSquare> open;
	list<mapSquare> closed;
	list<mapSquare>adjacentSquares;
	list<mapSquare>::iterator moveToSquare;
	list<mapSquare>::iterator itAdjacent;
	TDTileManager* m_oTiles = playStateEngine->GetTileManager();
	int g = 0;
	int delay = 0;
protected:
	double m_dSX = 0;
	double m_dSY = 0;
	int speed = 500;
	int health = 5;

public:
	int GetDrawWidth();
	void SetTargetY();
	int GetTargetX();
	int GetTargetY();
};

