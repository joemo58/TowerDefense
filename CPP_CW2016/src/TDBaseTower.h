#pragma once
#include "DisplayableObject.h"
#include "TDPlayState.h"
#include "JPGImage.h"
#include <string>
#include <iostream>

using namespace std;
class TDBaseTower :
	public DisplayableObject
{
public:
	TDBaseTower(BaseEngine* pEngine, int iMapX, int iMapY);
	~TDBaseTower();
	void Draw();	
	void TDBaseTower::PrintClassType(){
		string s = typeid(this).name();
		cout << "class created, type = " << s << endl;
	}
	void DoUpdate(int iCurrentTime);
	int GetTowerType();

private:
	TDPlayState* playStateEngine = dynamic_cast<TDPlayState*>(GetEngine());
	TDPlayState* mainEngine = dynamic_cast<TDPlayState*>(GetEngine());
	int m_iCurrentScreenX;
	int m_iCurrentScreenY;
	int m_iCurrentMapSquareX = 0;
	int m_iCurrentMapSquareY = 0;
	int towerType = 1;
	int damage = 1;
	int health = 10;
	int range = 190;
	int fireRate = 300;
	int closestEnemyX = 102;
	int closestEnemyY = 102;
	ImageData towerImage, towerImageS;
public:
	void moveTower(int iX, int iY);
	bool EnemyInRange();
	void IsOnMap(bool onMap);
	void moveUp(int moves);
	void moveDown(int moves);
	void moveLeft(int moves);
	void moveRight(int moves);
	int fixXBounds(int iX);
	int fixYBounds(int iY);
};

