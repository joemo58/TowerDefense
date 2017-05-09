#pragma once
#include "TDIntroState.h"
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
};

