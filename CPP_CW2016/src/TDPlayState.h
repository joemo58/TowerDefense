#pragma once
#include "TDState.h"
#include "TDTileManager.h"
#include "TDStateManager.h"
#include "JPGImage.h"
#include <string>


class TDPlayState :
	public TDState
{
public:
	TDPlayState(TDStateManager* stateManager, bool newGame);
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
	void ReducePlayerHealth(int damage);
	int TDPlayState::GetMapWidth(){
		return mapWidth;
	}
	int TDPlayState::GetMapHeight(){
		return mapHeight;
	}
	TDTileManager* GetTileManager();

	
	
private:
	int health = 0;
	int item_number = 0;
	int money = 0;
	int enemiesLeft = 0;
	int score = 0;
	
	int towerBarXS = (800/4) - 20;
	int towerBarYS = 0;
	int towerBarX = 800;
	int towerBarY = 600;
	int statusBarXS = 0;
	int statusBarYS = 0;
	int statusBarX = towerBarX - 10;
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
	int wave1EnemyNo = 6;
	int wave2EnemyNo = 12;
	int wave3EnemyNo = 20;
	bool waveSent = false;
	int targetX = 0;
	int targetY = 0;
	int chosenY = 0;
	TDTileManager m_oTiles;
	ImageData tower1Image, heartIcon, moneyIcon, heartIconS, moneyIconS, sideNavImage, sandBackground;
public:
	int GetTowerBarXS();
	void SpawnBullet(int startX, int startY, int targetX, int targetY, int damage);
	void SetScore(int score);
	int GetScore();
	void SetMoney(int amount);
	int GetMoney();
	void LoadScoresFromFile();
	void SetTileColour(int iTileX, int iTileY, unsigned int colour);
	void CheckIfOverTower(int iX, int iY);
	int GetPlayerHealth();
	void WriteGameStateToFile();
};

