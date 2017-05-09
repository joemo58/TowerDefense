#pragma once
#include "TDState.h"
#include "TDStateManager.h"
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
};

