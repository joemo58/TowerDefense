#pragma once
#include "TDState.h"
#include "TDTileManager.h"
#include "TDStateManager.h"
#include <string>


class TDPlayState :
	public TDState
{
public:
	TDPlayState(TDStateManager* stateManager);
	~TDPlayState();
	void SetupBackgroundBuffer();
	void DrawStrings();
	void MouseDown(int iButton, int iX, int iY);
	void SpawnTower(int towerNumber, int iX, int iY);
	int InitialiseObjects();
	void MouseMoved(int iX, int iY);
	const char* IntToString(int value);
	int GetTileWidth();
	void KeyDown(int iKeyCode);
	void SpawnEnemy(int enemyType, float delay);
	int generateSpawnX();
	int generateSpawnY();
	void ReducePlayerHealth(int damage);
	int TDPlayState::GetMapWidth(){
		return mapWidth;
	}
	int TDPlayState::GetMapHeight(){
		return mapHeight;
	}
	TDTileManager* GetTileManager();

	
	
protected:
	int health = 0;
	int item_number = 0;
	int money = 0;
	int enemiesLeft = 0;
	int score = 0;
	
	int towerBarXS = 800/4;
	int towerBarYS = 0;
	int towerBarX = 800;
	int towerBarY = 600;
	int statusBarXS = 0;
	int statusBarYS = 0;
	int statusBarX = 800;
    int statusBarY = 40;
	int towerTileSize;
	int towerTile1X;
	int towerTile1Y;
	int towerTile2X;
	int towerTile2Y;
	int towerTile3X;
	int towerTile3Y;
	bool towerSelected = false;
	int mapWidth = 0;
	int mapHeight = 0;
	int enemyNo = 6;
	bool waveSent = false;
	int targetX = 0;
	int targetY = 0;
	int chosenY = 0;
	TDTileManager m_oTiles;
public:
	int GetTowerBarXS();
	void SpawnBullet(int startX, int startY, int targetX, int targetY, int damage);
	void SetScore(int score);
	int GetScore();
	void SetMoney(int amount);
	int GetMoney();
};

