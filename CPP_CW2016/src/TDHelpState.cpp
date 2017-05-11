#include "header.h"
#include "templates.h"
#include "TDHelpState.h"

int background1X = 0;
int background2X = 800;

TDHelpState::TDHelpState(TDStateManager* sm) : TDIntroState(sm)
{
	stateManager = sm;
	background1.LoadImage("background_snow.png");
	background2.LoadImage("background_snow.png");
	helpDialogue.LoadImage("help_dialogue.png");
}

TDHelpState::~TDHelpState()
{
}

void TDHelpState::SetupBackgroundBuffer()
{


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

	background1.RenderImageWithMask(GetBackground(),
		0, 0,
		background1X, 0,
		1280, 600);
	Redraw(false);
	background2.RenderImageWithMask(GetBackground(),
		0, 0,
		background2X, 0,
		1280, 600);
	Redraw(false);
	helpDialogue.RenderImageWithMask(GetBackground(), 0, 0, 90, 80,
		helpDialogue.GetWidth(), helpDialogue.GetHeight());

}


void TDHelpState::KeyDown(int iKeyCode)
{
	if (iKeyCode == SDLK_ESCAPE){
		stateManager->SetState(1, NULL);
	}
}

void TDHelpState::MouseMoved(int iX, int iY)
{

}


void TDHelpState::GameAction()
{
	background1X --;
	
	//if (abs(background1X) >= (GetScreenWidth())){
	if ((GetScreenWidth() - background1X) >= 1280){
		background2X--;
	}
	if ((GetScreenWidth() - background2X) >= 1280){
		printf("true");
		background2X = GetScreenWidth();
		background1X = 0;
	}
	SetupBackgroundBuffer(); 
}
