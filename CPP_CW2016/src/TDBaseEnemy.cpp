#include "header.h"
#include "templates.h"
#include "TDBaseEnemy.h"
#include "TDBaseTower.h"
#include "JPGImage.h"
#include <list>
#include <stdlib.h>

#include <time.h>

TDBaseEnemy::TDBaseEnemy(BaseEngine* pEngine, int iMapX, int iMapY, int delay) : DisplayableObject(pEngine)
{
	this->delay = delay;
	m_iDrawWidth = 17;
	m_iDrawHeight = 17;
	m_pEngine = pEngine;
	m_iPreviousScreenX = m_iCurrentScreenX = iMapX;
	m_iPreviousScreenY = m_iCurrentScreenY = iMapY;
	SetTargetY();
	//SetTargetY();
	FindPath();
	moveToSquare = closed.begin();
	FollowPath();
}

TDBaseEnemy::~TDBaseEnemy()
{
}

/*Target for the enemies to aim towards*/
int enemyTargetY = 0;
int minYTarget = 250;
int maxYTarget = 400;

/*path finding: A* algorithm using Manhattan distance as heurisic-h(n)*/
list<TDBaseEnemy::mapSquare> TDBaseEnemy::FindPath(){
	/*F(n) = G(n) + H(n)  <-- choose square with the lowest f score.*/
	mapSquare destination;
	destination.x = GetTargetX();
	destination.y = GetTargetY();
	printf("destination: %d, %d", destination.x, destination.y);
	mapSquare currentSquare = AddCurrentSquareToOpen();	//add current square to front of open and assign to current square

	do {
		PopulateAdjacentSquares(currentSquare);			//add to open
		g++;											//increase counter of searched squares
		open.pop_front();								//pop currentSquare
		closed.push_back(currentSquare);				//add to closed

		if (Contains(closed, destination)) {
			printf("Destination reached-finish\n");
			break;	//path is found
		}
		else {
			currentSquare = GetSquareWithLowestF();		//lowest f in open queue
			printf("lowest f = %d, %d pushed to closed\n", currentSquare.x, currentSquare.y);
		}
	} while (!open.empty());

	return closed;
}

TDBaseEnemy::mapSquare TDBaseEnemy::AddCurrentSquareToOpen(){
	/*store the current square that the enemy is over*/
	//TDTileManager* m_oTiles = playStateEngine->GetTileManager();
	int tileX = m_oTiles->GetTileXForPositionOnScreen(m_iCurrentScreenX);
	int tileY = m_oTiles->GetTileYForPositionOnScreen(m_iCurrentScreenY);


	//int tileValue = m_oTiles->GetValue(tileX, tileY);
	mapSquare currentSquare;
	currentSquare.x = tileX;
	currentSquare.y = tileY;
	printf("Enemy current tile = %d,%d\n", currentSquare.x, currentSquare.y);
	open.push_front(currentSquare);
	return currentSquare;
}

list<TDBaseEnemy::mapSquare> TDBaseEnemy::PopulateAdjacentSquares(mapSquare currentSquare){
	//list<mapSquare>adjacentSquares;
	open.clear();						//remove any old nodes from the open list
	for (int i = -1; i <= 1; i++){
		for (int j = -1; j <= 1; j++){
			mapSquare nextSquare;
			int tileX = currentSquare.x + i;
			int tileY = currentSquare.y + j;
			if (CheckInBounds(tileX, tileY)){
				if (i == 0 && j == 0)			//current square
					continue;
				nextSquare.x = tileX;
				nextSquare.y = tileY;
				open.push_back(nextSquare);
			}
		}
	}
	return adjacentSquares;
}

bool TDBaseEnemy::CheckInBounds(int tileX, int tileY){

	int tileValue = m_oTiles->GetValue(tileX, tileY);

	if (tileX < 0 || tileX >= playStateEngine->GetMapWidth()){
		return false;
	}
	if (tileY < 0 || tileY >= playStateEngine->GetMapHeight()){
		return false;
	}
	if (tileValue > 0){
		printf("Tower here: %d, %d", tileX, tileY);
		return false;	//if tile contains a tower, ignore it
	}

	return true;
}


TDBaseEnemy::mapSquare TDBaseEnemy::GetSquareWithLowestF(){
	int f;	//g declared in header
	int h;
	int minF = 500;
	mapSquare lowestF;

	//PopulateAdjacentSquares(currentSquare);			//fill open list with adjacent squares
	//for each item in adsquares
	for (list<mapSquare>::iterator singleSquare = open.begin(); singleSquare != open.end(); ++singleSquare){
		if (Contains(closed, *singleSquare)){	//square already visited
			continue;
		}
		h = ManhattanDist(singleSquare->x, singleSquare->y, GetTargetX(), GetTargetY());
		f = h + g;
		if (f < minF){
			minF = f;
			lowestF.x = singleSquare->x;
			lowestF.y = singleSquare->y;
			singleSquare = open.erase(singleSquare);
		}
		else if (f == minF)
		{
			int coinToss = (rand() % 2) + 1;			//introduce some randomness-if f is equal, either keep the old square or use new one
			switch (coinToss){
			case 1:
				minF = f;
				lowestF.x = singleSquare->x;
				lowestF.y = singleSquare->y;
				singleSquare = open.erase(singleSquare);
				break;
			case 2:
				break;
			}
		}
	}
	if (minF == 500){
		printf("No path found, DEAD END!!!\n");
		return lowestF;		//change this to return something that notifies function of dead end
	}


	open.push_front(lowestF);
	return lowestF;
}

bool TDBaseEnemy::Contains(list<TDBaseEnemy::mapSquare>squareList, TDBaseEnemy::mapSquare square){
	for (list<mapSquare>::iterator it = squareList.begin(); it != squareList.end(); ++it){
		if (square.x == it->x && square.y == it->y){
			//delete *it;
			return true;
		}
	}
	return false;
}

void TDBaseEnemy::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	ImageData im, im2;
	// Load the image file into an image object - at the normal size
	im2.LoadImage("enemy.png");
	// Create a second image from the first, by halving the size
	im.ShrinkFrom(&im2, 2);

	im.RenderImageWithMask(GetEngine()->GetBackground(),
		0, 0,
		100, 100 ,
		im.GetWidth(), im.GetHeight());

	GetEngine()->DrawScreenOval(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0xff3300);

	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.	
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}

void TDBaseEnemy::SetMovement(int iStartTime, int iEndTime, int iCurrentTime,
	int iStartX, int iStartY, int iEndX, int iEndY)
{
	m_oMover.Setup(iStartX, iStartY, iEndX, iEndY, iStartTime, iEndTime);
	m_oMover.Calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMover.GetX();
	m_iCurrentScreenY = m_oMover.GetY();
}

MovementPosition TDBaseEnemy::getMovementPosition(){
	return m_oMover;
}

void TDBaseEnemy::SetPosition(double dX, double dY)
{
	m_iCurrentScreenX = dX;
	m_iCurrentScreenY = dY;
}

void TDBaseEnemy::SetSpeed(int newSpeed)
{
	speed = newSpeed;
}

void TDBaseEnemy::FollowPath(){
	int movePositionX;
	int movePositionY;
	if (moveToSquare != closed.end()){
		movePositionX = playStateEngine->GetTileWidth() * moveToSquare->x;
		movePositionY = playStateEngine->GetTileWidth() * moveToSquare->y + 40;
		SetMovement(GetEngine()->GetTime(), GetEngine()->GetTime() + (1000-speed), GetEngine()->GetTime(), m_iCurrentScreenX, m_iCurrentScreenY, movePositionX, movePositionY);
		moveToSquare++;
	}
	else {
		//delete enemy
		if (IsVisible())
			playStateEngine->ReducePlayerHealth(2);
		/*show -1 on screen*/
			this->SetVisible(false);
	}
}

void TDBaseEnemy::DoUpdate(int iCurrentTime)
{
	/*enemy dead*/
	if (health <= 0){
		if (IsVisible()){
			playStateEngine->SetScore((playStateEngine->GetScore() + 100));
			playStateEngine->SetMoney((playStateEngine->GetMoney() + 10));
			SetVisible(false);
		}
	}

	// Work out current position
	m_oMover.Calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMover.GetX();
	m_iCurrentScreenY = m_oMover.GetY();

	// If movement has finished then request instructions
	if (m_oMover.HasMovementFinished(iCurrentTime))
	{
		FollowPath();
	}

	// Work out current position
	m_iCurrentScreenX = (int)(m_iCurrentScreenX + 0.5);
	m_iCurrentScreenY = (int)(m_iCurrentScreenY + 0.5);
	
	RedrawObjects();
}


int TDBaseEnemy::ManhattanDist(int iX1, int iY1, int iX2, int iY2){
	
	int iXDiff = iX2 - iX1;
	int iYDiff = iY2 - iY1;

	return abs(iXDiff) + abs(iYDiff);
}


int TDBaseEnemy::GetDrawWidth()
{
	return m_iDrawWidth; 
}


void TDBaseEnemy::ReduceHealth(int damage)
{
	health = -damage;
}

void TDBaseEnemy::SetTargetY()
{
	//srand(time(NULL));
	int random = rand() % (maxYTarget - minYTarget + 1) + minYTarget;
	int targetY = random;
	int targetTileY = playStateEngine->GetTileManager()->GetTileYForPositionOnScreen(targetY);
	enemyTargetY = targetTileY;
}


int TDBaseEnemy::GetTargetX()
{
	int targetX = 590;
	int targetTileX = playStateEngine->GetTileManager()->GetTileXForPositionOnScreen(targetX);
	return targetTileX;
}


int TDBaseEnemy::GetTargetY()
{
	return enemyTargetY;
}
