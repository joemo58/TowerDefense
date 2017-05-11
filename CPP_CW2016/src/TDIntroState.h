#pragma once
#include "TDState.h"
#include "TDStateManager.h"
#include "JPGImage.h"
class TDIntroState :
	public TDState
{
public:
	TDIntroState(TDStateManager* stateManager);
	~TDIntroState();
	void SetupBackgroundBuffer();
	void DrawStringsUnderneath();
	void KeyDown(int iKeyCode);
	int InitialiseObjects();

	int item_number = 0;

private:
	TDStateManager* stateManager;
	ImageData background, dialogue, playButton, helpButton, loadButton, playButtonS, helpButtonS, loadButtonS, zombie;
public:
	void MouseDown(int iButton, int iX, int iY);
};

