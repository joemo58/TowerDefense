#pragma once
#include "TDIntroState.h"
#include "JPGImage.h"
class TDHelpState :
	public TDIntroState
{
public:
	TDHelpState(TDStateManager* sm);
	~TDHelpState();
	void SetupBackgroundBuffer();
	void KeyDown(int iKeyCode);

private:
	TDStateManager* stateManager = NULL;
	ImageData background1, background2, helpDialogue;
public:
	void MouseMoved(int iX, int iY);
	void GameAction();
};

