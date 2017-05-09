#include "header.h"
#include "templates.h"
#include "TDIntroState.h"
#include "TDIntroMenu.h"


TDIntroState::TDIntroState(TDStateManager* sm) : TDState()
{
	stateManager = sm;
}

TDIntroState::~TDIntroState()
{
}

void TDIntroState::SetupBackgroundBuffer()
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

	//FillBackground green
	FillBackground(0x4dff4d);

	/*Status bar (top)*/
	DrawBackgroundRectangle(0, 0, GetScreenWidth(), 40, 0x3e8ff2);

	/*Menu box (center)*/
	char* description = "A Tower Defense strategy game built using C++ 11 and SDL 2.0.\n";
	DrawBackgroundRectangle(100, 100, GetScreenWidth() - 100, GetScreenHeight() - 200, 0x3e8ff2);
	DrawBackgroundString(GetScreenWidth() / 4, 140, "Dirty Zombie Horde Defense", 0x1a0000, NULL);
	DrawBackgroundString(GetScreenWidth() / 4, 200, description, 0x1a0000, NULL);
	DrawBackgroundString(120, GetScreenHeight() - 185, "Space = Play", 0x1a0000, NULL);
	DrawBackgroundString(GetScreenWidth() - 240, GetScreenHeight() - 185, "H = Help", 0x1a0000, NULL);
	
}

void TDIntroState::DrawStringsUnderneath()
{
	// First clear the area where they were originally drawn - i.e. undraw previous text
	CopyAllBackgroundBuffer();

}

void TDIntroState::KeyDown(int iKeyCode)
{
	if (iKeyCode == SDLK_SPACE){
		printf("enter down");
		//Deinitialise();
		//SetExitWithCode(0);
		stateManager->SetState(2);
	}
	if (iKeyCode == SDLK_h){
		stateManager->SetState(3);
	}
}

int TDIntroState::InitialiseObjects()
{
	/*
	TDIntroMenu* mainMenu = new TDIntroMenu(this, 0, 0);
	DrawableObjectsChanged();
	// Destroy any existing objects
	DestroyOldObjects();
	// Creates an array to store the objects
	// Needs to have room for the NULL at the end
	CreateObjectArray(2);
	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.
	StoreObjectInArray(item_number, mainMenu);
	item_number++;
	StoreObjectInArray(item_number, NULL);
	item_number++;	*/
	return 0;
}
