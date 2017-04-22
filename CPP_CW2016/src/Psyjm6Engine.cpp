#include "header.h"
#include "templates.h"
#include "Psyjm6Engine.h"
#include "Psyjm6Enemy.h"
#include "Psyjm6EnemySphere.h"
#include "Psyjm6Player.h"
#include "ScoreText.h"


Psyjm6Engine::Psyjm6Engine() : BaseEngine(50)
{
	//m_oTiles = new Psyjm6TileManager();
}

Psyjm6Engine::~Psyjm6Engine()
{
	//delete m_oTiles;
}

/*
void generateMap(){
	for (int x = 0; x < tileManagerHeight; x++){
		for (int y = 0; y < tileManagerWidth; y++){
			data[y][x] = 'b';
		}
	}
		
}*/

void Psyjm6Engine::SetupBackgroundBuffer()
{
	int tileManagerWidth = 20;
	int tileManagerHeight = 20;

	char* data[] = {
		"222222222222222",
		"aaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaa",
		"aaaaaaaaaaaaaaa",
		"baaaaaaaaaaaaab",
		"badadadadadadab",
		"baaaaaaaaaaaaab",
		"baaaaaaaaaaaaab",
		"baaaaaaaaaaaaab",
		"baaaaaaaaaaaaab",
		"bbbbbbbbbbbbbbb" };
	
	//FillBackground(0xffaabb); pink
	FillBackground(0x4dff4d);

	/*background painting*/
	int borderSizeY = this->GetScreenHeight() / 8;
	int borderSizeX = this->GetScreenWidth() / 8;
	for (int iX = 0; iX < (this->GetScreenWidth()); iX++)
	for (int iY = 0; iY < borderSizeY; iY++)	
		switch (rand() % 4)
	{
		case 0: SetBackgroundPixel(iX, iY, 0xccff33); break;
		default: SetBackgroundPixel(iX, iY, 0x00e600); break;
	}

	for (int iX = 0; iX < (this->GetScreenWidth()); iX++)
	for (int iY = this->GetScreenHeight()-borderSizeY; iY < (this->GetScreenHeight()); iY++)
		switch (rand() % 4)
	{
		case 0: SetBackgroundPixel(iX, iY, 0xccff33); break;
		default: SetBackgroundPixel(iX, iY, 0x00e600); break;
	}

	for (int iX = 0; iX < (borderSizeX); iX++)
	for (int iY = 0; iY < (this->GetScreenHeight()); iY++)
		switch (rand() % 4)
	{
		case 0: SetBackgroundPixel(iX, iY, 0xccff33); break;
		default: SetBackgroundPixel(iX, iY, 0x00e600); break;
	}

	for (int iX = this->GetScreenWidth() - borderSizeX; iX < this->GetScreenWidth(); iX++)
	for (int iY = 0; iY < (this->GetScreenHeight()); iY++)
		switch (rand() % 4)
	{
		case 0: SetBackgroundPixel(iX, iY, 0xccff33); break;
		default: SetBackgroundPixel(iX, iY, 0x00e600); break;
	}

	DrawBackgroundTriangle(this->GetScreenHeight(), this->GetScreenHeight() - borderSizeY, 550, 425/*height*/, 700, this->GetScreenHeight() - borderSizeY, 0x00ffff);
	DrawBackgroundTriangle(borderSizeX, this->GetScreenHeight() - borderSizeY, 300, 425/*height*/, borderSizeX + 120, this->GetScreenHeight() - borderSizeY, 0x00ffff);
	/*static string*/
	DrawBackgroundString(GetScreenWidth() - 300, 80, "The score is", 0x1a0000, NULL);
	
	// Specify how many tiles wide and high
	m_oTiles.SetSize(tileManagerWidth, tileManagerHeight);
	// Set up the tiles
	for (int x = 0; x < tileManagerWidth; x++)
	for (int y = 0; y < tileManagerHeight; y++)
		m_oTiles.SetValue(x, y, rand() % 31);			//sets value of mPdata array in tilemanager
	// Specify the screen x,y of top left corner
	m_oTiles.SetBaseTilesPositionOnScreen(100, 80);
	// Tell it to draw tiles from x1,y1 to x2,y2 in tile array, to the background of this screen
	m_oTiles.DrawAllTiles(this, this->GetBackground(), 0, 0, tileManagerWidth, tileManagerHeight);
	
	
}

void Psyjm6Engine::DrawStringsUnderneath()
{
	// First clear the area where they were originally drawn - i.e. undraw previous text
	CopyAllBackgroundBuffer();
	score++;
	std::string scoreStr = std::to_string(score);
	const char *cstr = scoreStr.c_str();
	// Then draw the new labels/strings
	DrawScreenString(GetScreenWidth() - 100, 80, cstr, 0x1a0000, NULL);
}


void Psyjm6Engine::MouseDown(int iButton, int iX, int iY)
{
	printf("%d %d\n", iX, iY);
	Psyjm6EnemySphere* newEnemy = new Psyjm6EnemySphere(this, 20, 200);

	if (iButton == SDL_BUTTON_LEFT)
	{
		if (item_number <= 3){	/*fix this*/
			StoreObjectInArray(item_number, newEnemy);
			item_number++;
			DrawableObjectsChanged();
			StoreObjectInArray(item_number, NULL);
			// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
			
			newEnemy->Draw();
			newEnemy->SetMovement(GetTime(), GetTime() + 3000, GetTime(), 0, rand() % (GetScreenHeight() - 30) + 30, rand() % (GetScreenWidth() - 30) + 30, 0 + 25);
		}
		else {
			DrawScreenString(GetScreenWidth() - 100, 80, "Too many enemies", 0x1a0000, NULL);
		}
		Redraw(true);
	}

}


int Psyjm6Engine::InitialiseObjects()
{
	Psyjm6Enemy* enemy1 = new Psyjm6Enemy(this, 50, 50);
	Psyjm6EnemySphere* enemy2 = new Psyjm6EnemySphere(this, 250, 20);
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();
	// Destroy any existing objects
	DestroyOldObjects();
	// Creates an array to store the objects
	// Needs to have room for the NULL at the end
	CreateObjectArray(4);
	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.
	StoreObjectInArray(item_number, enemy1);
	item_number++;
	StoreObjectInArray(item_number, enemy2);
	item_number++;
	StoreObjectInArray(item_number, new Psyjm6Player(this, 20, 200));
	item_number++;
	StoreObjectInArray(item_number, NULL);
	//enemy1->SetMovement(GetTime(), GetTime() + 2600, GetTime(), 20, 10, GetScreenWidth()-25, GetScreenHeight()-25);
	enemy1->SetPosition(100, 100);
	enemy1->SetSpeed(1.1, 1.0);
	enemy2->SetMovement(GetTime(), GetTime() + 2500, GetTime(), 0, GetScreenHeight() - 25, GetScreenWidth() - 25, 0 + 25);
	return 0;
}


