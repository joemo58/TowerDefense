#include "header.h"
#include "templates.h"
#include "TDHelpState.h"


TDHelpState::TDHelpState(TDStateManager* sm) : TDIntroState(sm)
{
	stateManager = sm;
}


TDHelpState::~TDHelpState()
{
}

void TDHelpState::SetupBackgroundBuffer()
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
	char* description = "HERES HOW TO PLAY:::;";
	DrawBackgroundRectangle(100, 100, GetScreenWidth() - 100, GetScreenHeight() - 200, 0x3e8ff2);
	DrawBackgroundString(GetScreenWidth() / 4, 140, "Dirty Zombie Horde Defense", 0x1a0000, NULL);
	DrawBackgroundString(GetScreenWidth() / 4, 200, description, 0x1a0000, NULL);
	DrawBackgroundString(120, GetScreenHeight() - 185, "Escape = Back", 0x1a0000, NULL);

}


void TDHelpState::KeyDown(int iKeyCode)
{
	if (iKeyCode == SDLK_ESCAPE){
		stateManager->SetState(1);
	}
}
