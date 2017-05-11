#include "header.h"
#include "templates.h"
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

TDPlayState::TDPlayState(TDStateManager* stateManager, bool newGame) : TDState(),
towerBarXS(601),
towerBarYS(0),
towerBarX(800),
towerBarY(600),
statusBarXS(0),
statusBarYS(0),
statusBarX(800),
statusBarY(40)
{
	health = 40;
	
	if (!newGame){
		LoadScoresFromFile();
	}
	else {
		cout << "Unable to open scores file - no previous game \n";
		score = 0;
		health = 40;
		money = 0;
	}
	tower1Image.LoadImage("base_tower_paint.png");
	heartIcon.LoadImage("heart_icon.png");
	moneyIcon.LoadImage("dollar_icon.png");
	sideNavImage.LoadImage("sidebar.png");
	sandBackground.LoadImage("background_sand.png");
	heartIconS.ShrinkFrom(&heartIcon, 2);
	moneyIconS.ShrinkFrom(&moneyIcon, 2);
}

TDPlayState::~TDPlayState()
{
}

TDBaseTower* newTower = NULL; 
TDBaseEnemy* newEnemy = NULL;
int wave1[4] = {1, 3, 1, 2, /*1, 3*/};
int wave2[12] = { 1, 2, 1, 2, 1, 3, 1, 1, 2, 3, 1, 1 };
int wave3[20] = { 1, 2, 1, 2, 1, 3, 1, 1, 2, 3, 1, 1, 2, 2, 1, 2, 1, 1, 3, 3 };
bool wave1Sent = false;
bool wave2Sent = false;
bool wave3Sent = false;

unsigned int backgroundColour = 0xeff9bd;
unsigned int towerTileColour = 0xffffff;
int previousTileX = 0;
int previousTileY = 0;

void TDPlayState::LoadScoresFromFile()
{
	/*Load data from file*/
	string moneyText;
	string scoreText;
	string healthText;
	string line;
	ifstream myfile("score.txt");
	char word[50];
	if (myfile.good())
	{
		/**/
		while (myfile >> moneyText >> scoreText >> healthText){
			cout << moneyText << scoreText << healthText << endl;
		}
		printf("end of file reached");
		myfile.close();

		money = stoi(moneyText, NULL, NULL);
		score = stoi(scoreText, NULL, NULL);
		health = stoi(healthText, NULL, NULL);
	}
}


void TDPlayState::SetupBackgroundBuffer()
{
	towerBarXS = 600.3;
	towerBarYS = 0;
	towerBarX = GetScreenWidth();
	towerBarY = GetScreenHeight();
	statusBarXS = 0;
	statusBarYS = 0;
	statusBarX = GetScreenWidth();
	statusBarY = 40;
	towerTileSize = 40;
	towerTile1X = towerBarXS + 17;
	towerTile1Y = towerTile2Y = towerTile3Y = towerBarYS + 140;
	towerTile2X = towerTile1X + 60;
	towerTile3X = towerTile2X + 60;
	mapWidth = 30;
	mapHeight = 25;

	FillBackground(backgroundColour);

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
	DrawBackgroundRectangle(statusBarXS, statusBarYS, statusBarX, statusBarY, 0xeff9bd);
	/*towers bar*/
	DrawBackgroundRectangle(towerBarXS, towerBarYS, towerBarX, towerBarY, 0xeff9bd);
	/*SIDE BAR IMAGE*/
	sideNavImage.RenderImageWithMask(GetBackground(), 0, 0, towerBarXS + 1, 5,
		sideNavImage.GetWidth(), sideNavImage.GetHeight());
	/*replace these with images of the towers*/
	DrawBackgroundRectangle(towerTile1X, towerTile1Y, towerTile1X + towerTileSize, towerTile1Y + towerTileSize, towerTileColour);
	DrawBackgroundRectangle(towerTile2X, towerTile1Y, towerTile2X + towerTileSize, towerTile1Y + towerTileSize, towerTileColour);
	DrawBackgroundRectangle(towerTile3X, towerTile1Y, towerTile3X + towerTileSize, towerTile1Y + towerTileSize, towerTileColour);
	tower1Image.RenderImageWithMask(GetBackground(), 0, 0, towerTile1X + 3, towerTile1Y + 3,
		tower1Image.GetWidth(), tower1Image.GetHeight());
	tower1Image.RenderImageWithMask(GetBackground(), 0, 0, towerTile2X + 3, towerTile2Y + 3,
		tower1Image.GetWidth(), tower1Image.GetHeight());
	tower1Image.RenderImageWithMask(GetBackground(), 0, 0, towerTile3X + 3, towerTile3Y + 3,
		tower1Image.GetWidth(), tower1Image.GetHeight());
	/*ICONS FOR HEALTH AND MONEY*/
	heartIconS.RenderImageWithMask(GetBackground(), 0, 0, GetScreenWidth() - 350, 0,
		heartIconS.GetWidth(), heartIconS.GetHeight());
	moneyIconS.RenderImageWithMask(GetBackground(), 0, 0, GetScreenWidth() - 542, 0,
		moneyIconS.GetWidth(), moneyIconS.GetHeight());
	/*SAND BACKGROUND FOR MAP
	sandBackground.RenderImage(GetBackground(), 0, 0, 0, statusBarY,
		sandBackground.GetWidth(), sandBackground.GetHeight());
	Redraw(true);*/
}

void TDPlayState::DrawStrings()
{
	// First clear the area where they were originally drawn - i.e. undraw previous text
	CopyAllBackgroundBuffer();
	
	string scoreStr = "Score = " + to_string(score);
	const char *scoreCstr = scoreStr.c_str();
	string healthStr = to_string(health);
	const char *healthCstr = healthStr.c_str();
	string moneyStr = to_string(money);
	const char *moneyCstr = moneyStr.c_str();
	// Then draw the new labels/strings

	DrawScreenString(GetScreenWidth() - 750, 5, scoreCstr, 0x1a0000, NULL);
	DrawScreenString(GetScreenWidth() - 500, 5, moneyCstr, 0x1a0000, NULL);
	DrawScreenString(GetScreenWidth() - 300, 5, /*intToString(money)*/ healthCstr, 0x1a0000, NULL);

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
			SetTileColour(tileX, tileY, 0xfbaa16);
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
		Redraw(true);
		SetTileColour(previousTileX, previousTileY, m_oTiles.GetColour());
		// Using the base tiles position, work out which tile the point is over
		int tileX = m_oTiles.GetTileXForPositionOnScreen(iX);
		int tileY = m_oTiles.GetTileYForPositionOnScreen(iY);

		CheckIfOverTower(tileX, tileY);
		//printf("coords: %d, %d = sqare: %d + %d\n", iX, iY, tileX, tileY);
		if (towerSelected){
			if (waveSent != true){
				if (tileX != previousTileX || tileY != previousTileY){
					SetTileColour(tileX, tileY, 0xffffff);
				}
			}
			newTower->IsOnMap(true);
			newTower->moveTower(tileX, tileY);
		}
		previousTileX = tileX;
		previousTileY = tileY;
	}

}

void TDPlayState::CheckIfOverTower(int iX, int iY)
{
	int squareVal = m_oTiles.GetValue(iX, iY);
	if (squareVal == 1){
		printf("over a tower");
		SetTileColour(iX, iY, 0xfbaa16);
	}
}


void TDPlayState::SetTileColour(int iTileX, int iTileY, unsigned int colour)
{
	m_oTiles.SetColour(this, this->GetBackground(), 0, statusBarY, iTileX, iTileY, colour);
}


void TDPlayState::KeyDown(int iKeyCode)
{
	/*SPAWN FOR EACH WAVE SET*/
	if (waveSent == false){
		if (iKeyCode == SDLK_SPACE){
			printf("SPAWN1\n");
			/*START FIRST WAVE*/
			for (int i = 0; i < /*wave1EnemyNo*/4; i++) {
				
				SpawnEnemy(wave1[i], 0);
			}
			waveSent = true;
			wave1Sent = true;
			return;
		}
	}
	if (wave1Sent && wave2Sent == false){
		if (iKeyCode == SDLK_SPACE){
			printf("SPAWN2\n");
			/*START FIRST WAVE*/
			for (int i = 0; i < wave2EnemyNo; i++) {
				
				SpawnEnemy(wave2[i], 0);
			}
			wave2Sent = true;
			return;
		}
	}
	if (wave2Sent && wave3Sent == false){
		if (iKeyCode == SDLK_SPACE){
			printf("SPAWN3\n");
			/*START FIRST WAVE*/
			for (int i = 0; i < wave3EnemyNo; i++) {
				
				SpawnEnemy(wave3[i], 0);
			}
			wave3Sent = true;
			return;
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
		WriteGameStateToFile();
		SetExitWithCode(0);
		exit(0);
	}
}

void TDPlayState::WriteGameStateToFile()
{
	DisplayableObject* pObject;
	ofstream myfile;
	myfile.open("score.txt", ios::out);
	myfile << money << "\n" << score << "\n" << health << "\n";

	for (int iObjectId = 0; (pObject = GetDisplayableObject(iObjectId)) != NULL; iObjectId++)
	{
		TDBaseTower* tower = dynamic_cast<TDBaseTower*>(pObject);
		if (tower == NULL)
		{
			// This object is not a tower so skip it
			continue;
		}

		int tileX = tower->getTileX();
		int tileY = tower->GetTileY();

		myfile << tileX << " " << tileY << "\n";
	}
	myfile.close();
	printf("file created and written to");
}

void TDPlayState::SpawnEnemy(int enemyType, float delay){

	switch (enemyType){
	case 1:
		newEnemy = new TDBaseEnemy(this, delay);	
		break;
	case 2:
		newEnemy = new TDFastEnemy(this, delay);
		break;
	case 3:
		newEnemy = new TDStrongEnemy(this, delay);
		break;
	}
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();
	StoreObjectInArray(item_number, newEnemy);
	item_number++;
	StoreObjectInArray(item_number, NULL);
	Redraw(false);
}

void TDPlayState::SpawnBullet(int startX, int startY, int targetX, int targetY, int damage)
{
	TDBullet* bullet = new TDBullet(this, startX, startY);
	bullet->SetDamage(damage);
	DrawableObjectsChanged();
	StoreObjectInArray(item_number, bullet);
	item_number++;
	StoreObjectInArray(item_number, NULL);
	bullet->SetMovement(GetTime(), GetTime() + 800, GetTime(), startX, startY, targetX, targetY);
	Redraw(true);
}

int TDPlayState::InitialiseObjects(){
	DrawableObjectsChanged();
	// Destroy any existing objects
	DestroyOldObjects();
	// Creates an array to store the objects
	// Needs to have room for the NULL at the end
	CreateObjectArray(2000); //make bigger if need be
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

int TDPlayState::GetPlayerHealth()
{
	return health;
}

