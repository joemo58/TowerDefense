#include "header.h"
#include "templates.h"
#include "JPGImage.h"
#include "TDPlayState.h"
#include "TDBaseTower.h"
#include "TDBaseEnemy.h"
#include "TDFastEnemy.h"
#include "TDBullet.h"
#include "TDStrongEnemy.h"

#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
using namespace std;

TDPlayState::TDPlayState(TDStateManager* stateManager) : TDState(),
towerBarXS(800 / 1.4),
towerBarYS(0),
towerBarX(800),
towerBarY(600),
statusBarXS(0),
statusBarYS(0),
statusBarX(800),
statusBarY(40)
{
	health = 40;

	/*Load data from file*/
	string moneyText;
	string scoreText;
	string healthText;
	string line;
	ifstream myfile("score.txt");
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			getline(myfile, line);
			moneyText = line;
			getline(myfile, line);
			scoreText = line;
			getline(myfile, line);
			healthText = line;
		}
		myfile.close();

		money = stoi(moneyText);
		score = stoi(scoreText);
		health = stoi(healthText);
	}
	else cout << "Unable to open scores file - no previous game \n";
}

TDPlayState::~TDPlayState()
{
}

TDBaseTower* newTower = NULL; 
TDBaseEnemy* newEnemy = NULL;
int enemyData[6] = {1, 2, 1, 2, 1, 3};
int minYSpawn = 250;
int maxYSpawn = 400;


void TDPlayState::SetupBackgroundBuffer()
{
	towerBarXS = GetScreenWidth() / 1.3;
	towerBarYS = 0;
	towerBarX = GetScreenWidth();
	towerBarY = GetScreenHeight();
	statusBarXS = 0;
	statusBarYS = 0;
	statusBarX = GetScreenWidth();
	statusBarY = 40;
	towerTileSize = 40;
	towerTile1X = towerBarXS + 10;
	towerTile1Y = towerTile2Y = towerTile3Y = towerBarYS + 120;
	towerTile2X = towerBarXS + 70;
	towerTile3X = towerBarXS + 130;
	mapWidth = 30;
	mapHeight = 25;


	FillBackground(0x3e8ff2);

	// Draw an image loaded from a file.
	ImageData im;
	// Load the image file into an image object - at the normal size
	im.LoadImage("tdmap1small.png");

	/*im.RenderImage(this->GetBackground(),
		0, 0,
		0, 0,
		im.GetWidth(), im.GetHeight());*/

	m_oTiles.SetBaseTilesPositionOnScreen(0, statusBarY);
	// Specify how many tiles wide and high
	m_oTiles.SetSize(mapWidth, mapHeight);
	// Set up the tiles
	for (int x = 0; x < mapWidth; x++)
		for (int y = 0; y < mapHeight; y++)
			m_oTiles.SetValue(x, y, 0);			//0 = nothing, 1 = tower 1 etc..

	// Tell it to draw tiles from x1,y1 to x2,y2 in tile array, to the background of this screen
	m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, mapWidth-1, mapHeight-1);

	/*Status bar (top)*/
	DrawBackgroundRectangle(statusBarXS, statusBarYS, statusBarX, statusBarY, 0x3e8ff2);
	/*towers bar*/
	DrawBackgroundRectangle(towerBarXS, towerBarYS, towerBarX, towerBarY, 0x3e8ff2);
	/*replace these with images of the towers*/
	DrawBackgroundRectangle( towerTile1X, towerTile1Y, towerTile1X + towerTileSize, towerTile1Y + towerTileSize, 0xffffff);
	DrawBackgroundRectangle( towerTile2X, towerTile2Y, towerTile2X + towerTileSize, towerTile2Y + towerTileSize, 0xffffff);
	DrawBackgroundRectangle( towerTile3X, towerTile3Y, towerTile3X + towerTileSize, towerTile3Y + towerTileSize, 0xffffff);
	
}

void TDPlayState::DrawStrings()
{
	// First clear the area where they were originally drawn - i.e. undraw previous text
	CopyAllBackgroundBuffer();
	
	string scoreStr = "score: " + to_string(score);
	const char *scoreCstr = scoreStr.c_str();
	string healthStr ="Health " + to_string(health);
	const char *healthCstr = healthStr.c_str();
	string moneyStr = "Money " + to_string(money);
	const char *moneyCstr = moneyStr.c_str();
	// Then draw the new labels/strings

	DrawScreenString(GetScreenWidth() - 750, 5, /*intToString(enemiesLeft)*/+scoreCstr, 0x1a0000, NULL);
	DrawScreenString(GetScreenWidth() - 550, 5, moneyCstr, 0x1a0000, NULL);
	DrawScreenString(GetScreenWidth() - 350, 5, /*intToString(money)*/ healthCstr, 0x1a0000, NULL);

}

void TDPlayState::MouseDown(int iButton, int iX, int iY){
	if (iX >= towerTile1X && iX <= towerTile1X + towerTileSize){
		if (iY >= towerTile1Y && iY <= towerTile1Y + towerTileSize){
			printf("create tower 1\n");
			if (towerSelected != true)
				SpawnTower(1, iX, iY);	
		}
	}

	if (iX >= towerTile2X && iX <= towerTile2X + towerTileSize){
		if (iY >= towerTile2Y && iY <= towerTile2Y + towerTileSize){
			if (towerSelected != true)
				SpawnTower(2, iX, iY);
		}
	}
	if (iX >= towerTile3X && iX <= towerTile3X + towerTileSize){
		if (iY >= towerTile3Y && iY <= towerTile3Y + towerTileSize){
			if (towerSelected != true)
				SpawnTower(3, iX, iY);
		}
	}

	if (towerSelected){
		if (m_oTiles.IsValidTilePosition(iX, iY)){
			int tileX = m_oTiles.GetTileXForPositionOnScreen(iX);
			int tileY = m_oTiles.GetTileYForPositionOnScreen(iY);
			printf("Tower placed at point: %d, %d", tileX, tileY);
			m_oTiles.SetValue(tileX, tileY, newTower->GetTowerType());
			towerSelected = false;
		}
		else {
			/*if different tower button pressed, change new tower to point at different tower*/
		}
	}
}

void TDPlayState::SpawnTower(int towerNumber, int iX, int iY){
	switch (towerNumber){
	case 1:
		towerSelected = true;
		newTower = new TDBaseTower(this, iX, iY);
		DrawableObjectsChanged();
		StoreObjectInArray(item_number, newTower);
		item_number++;
		StoreObjectInArray(item_number, NULL);
		// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
		Redraw(false);
		break;
	}
}

void TDPlayState::MouseMoved(int iX, int iY){
	if (m_oTiles.IsValidTilePosition(iX, iY)){
		// Using the base tiles position, work out which tile the point is over
		int tileX = m_oTiles.GetTileXForPositionOnScreen(iX);
		int tileY = m_oTiles.GetTileYForPositionOnScreen(iY);
		printf("coords: %d, %d = sqare: %d + %d\n",iX, iY, tileX, tileY);
		if (towerSelected){
			newTower->IsOnMap(true);
			newTower->moveTower(tileX, tileY);
		}
	}
}

void TDPlayState::KeyDown(int iKeyCode)
{
	if (waveSent != true){
		if (iKeyCode == SDLK_SPACE){
			/*START FIRST WAVE*/
			for (int i = 0; i < enemyNo; i++) {
				printf("SPAWN\n");
				SpawnEnemy(enemyData[i], 0);
			}
			waveSent = true;
			//generate random number for delay
			//SpawnEnemy(1, 0.0);
			//waveSent = true;
		}
	}

	if (towerSelected){
		if (iKeyCode == SDLK_UP){
			newTower->moveUp(5);
		}
		if (iKeyCode == SDLK_DOWN){
			newTower->moveDown(5);
		}
		if (iKeyCode == SDLK_LEFT){
			newTower->moveLeft(5);
		}
		if (iKeyCode == SDLK_RIGHT){
			newTower->moveRight(5);
		}
	}

	if (iKeyCode == SDLK_ESCAPE){
		/*Save Money, Score and Health to file*/
		ofstream myfile;
		myfile.open("score.txt", ios::in);
		myfile << money << "\n" << score << "\n" << health << "\n";
		myfile.close();
		SetExitWithCode(0);
		exit(0);
	}
}

void TDPlayState::SpawnEnemy(int enemyType, float delay){
	int iX = generateSpawnX();
	int iY = 250; //GenerateRandom;

	switch (enemyType){
	case 1:
		newEnemy = new TDBaseEnemy(this, iX, iY, delay);	
		break;
	case 2:
		newEnemy = new TDFastEnemy(this, iX, iY, delay);
		break;
	case 3:
		newEnemy = new TDStrongEnemy(this, iX, iY, delay);
		break;
	}
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();
	StoreObjectInArray(item_number, newEnemy);
	item_number++;
	StoreObjectInArray(item_number, NULL);
	Redraw(true);
}

void TDPlayState::SpawnBullet(int startX, int startY, int targetX, int targetY, int damage)
{
	TDBullet* bullet = new TDBullet(this, startX, startY);
	bullet->SetDamage(damage);
	DrawableObjectsChanged();
	//printf("item number = %d\n", item_number);
	StoreObjectInArray(item_number, bullet);
	item_number++;
	StoreObjectInArray(item_number, NULL);
	Redraw(false);
	bullet->SetMovement(GetTime(), GetTime() + 800, GetTime(), startX, startY, targetX, targetY);
}




int TDPlayState::generateSpawnX(){
	return 50;
}
int TDPlayState::generateSpawnY(){
	/*random seed from time*/
	unsigned int time_ui = static_cast<unsigned int>(time(NULL));
	srand(time_ui);
	int random = rand() % (maxYSpawn - minYSpawn + 1) + minYSpawn;
	
	targetY = towerBarYS + random;
	return targetY;
}


int TDPlayState::InitialiseObjects(){
	DrawableObjectsChanged();
	// Destroy any existing objects
	DestroyOldObjects();
	// Creates an array to store the objects
	// Needs to have room for the NULL at the end
	CreateObjectArray(200); //make bigger if need be
	StoreObjectInArray(item_number, NULL);
	return 0;
}


int TDPlayState::GetTileWidth(){
	return m_oTiles.GetTileWidth();
}


const char* TDPlayState::IntToString(int value){
	string stringVal = to_string(value);
	const char *cStr = stringVal.c_str();
	return cStr;
}

TDTileManager* TDPlayState::GetTileManager() {
	return &m_oTiles;
}


int TDPlayState::GetTowerBarXS()
{
	return towerBarXS;
}



void TDPlayState::SetScore(int score)
{
	score += score;
}


int TDPlayState::GetScore()
{
	return score;
}


void TDPlayState::SetMoney(int amount)
{
	this->money += amount;
}


int TDPlayState::GetMoney()
{
	return money;
}


void TDPlayState::ReducePlayerHealth(int damage)
{
	health -= damage;
}

