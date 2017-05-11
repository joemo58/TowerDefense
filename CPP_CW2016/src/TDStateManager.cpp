#include "header.h"
#include "templates.h"
#include "TDStateManager.h"
#include "TDPlayState.h"
#include "TDIntroState.h"
#include "TDHelpState.h"
#include "TDState.h"

#define INTRO 1
#define PLAY 2
#define HELP 3

#define BASE_SCREEN_WIDTH 800
#define BASE_SCREEN_HEIGHT 600

TDState* oMain = new TDState();

TDStateManager::TDStateManager()
{
}


TDStateManager::~TDStateManager()
{

}

char buf[1024];

int TDStateManager::SetState(int state, bool newGame)
{
	int iResult;
	if (state == INTRO){
		oMain = new TDIntroState(this);
	} 
	if (state == PLAY){
		oMain = new TDPlayState(this, newGame);
	}

	if (state == HELP){
		oMain = new TDHelpState(this);
	}

	sprintf(buf, "My Demonstration Program : Size %d x %d", BASE_SCREEN_WIDTH, BASE_SCREEN_HEIGHT);
	iResult = oMain->Initialise(buf, BASE_SCREEN_WIDTH, BASE_SCREEN_HEIGHT, "Cornerstone Regular.ttf", 24);
	iResult = oMain->MainLoop();
	oMain->Deinitialise();
	return iResult;
}
