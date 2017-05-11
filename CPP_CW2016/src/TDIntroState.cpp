#include "header.h"
#include "templates.h"
#include "TDIntroState.h"
#include "TDIntroMenu.h"


TDIntroState::TDIntroState(TDStateManager* sm) : TDState()
{
	stateManager = sm;
	dialogue.LoadImage("IntroDialogue.png");
	playButton.LoadImage("play_button.png");
	helpButton.LoadImage("help_button.png");
	loadButton.LoadImage("load_button.png");
	playButtonS.ShrinkFrom(&playButton, 2);
	helpButtonS.ShrinkFrom(&helpButton, 2);
	loadButtonS.ShrinkFrom(&loadButton, 2);
	zombie.LoadImage("zombie_cartoon.png");
	background.LoadImage("background_blood");
}

TDIntroState::~TDIntroState()
{
}

void TDIntroState::SetupBackgroundBuffer()
{


	//FillBackground blue
	FillBackground(0xffffff);

	/*Status bar (top)*/
	DrawBackgroundRectangle(0, 0, GetScreenWidth(), 40, 0x3e8ff2);

	dialogue.RenderImageWithMask(GetBackground(), 0, 0, 10, 50,
		dialogue.GetWidth(), dialogue.GetHeight());
	zombie.RenderImageWithMask(GetBackground(), 0, 0, 540, 250,
		zombie.GetWidth(), zombie.GetHeight());	
	playButtonS.RenderImageWithMask(GetBackground(), 0, 0, 280, 400,
		playButtonS.GetWidth(), playButtonS.GetHeight());
	loadButtonS.RenderImageWithMask(GetBackground(), 0, 0, 280, 460,
		loadButtonS.GetWidth(), loadButtonS.GetHeight());
	helpButtonS.RenderImageWithMask(GetBackground(), 0, 0, 280, 520,
		helpButtonS.GetWidth(), helpButtonS.GetHeight());
	
}

void TDIntroState::DrawStringsUnderneath()
{
	// First clear the area where they were originally drawn - i.e. undraw previous text
	CopyAllBackgroundBuffer();

}

void TDIntroState::KeyDown(int iKeyCode)
{
	if (iKeyCode == SDLK_SPACE){
		printf("continuing game");
		//Deinitialise();
		//SetExitWithCode(0);
		stateManager->SetState(2, NULL);
	}
	if (iKeyCode == SDLK_n){
		printf("New game starting");
		//Deinitialise();
		//SetExitWithCode(0);
		stateManager->SetState(2, true);
	}
	if (iKeyCode == SDLK_h){
		stateManager->SetState(3, NULL);
	}
}

int TDIntroState::InitialiseObjects()
{
	return 0;
}


void TDIntroState::MouseDown(int iButton, int iX, int iY)
{
	//if (iX < 10 && iX < )
}
