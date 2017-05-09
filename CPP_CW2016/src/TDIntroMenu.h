#pragma once
#include "DisplayableObject.h"
#include "BaseEngine.h"
class TDIntroMenu :
	public DisplayableObject
{
public:
	TDIntroMenu(BaseEngine* pEngine, int iMapX, int iMapY);
	~TDIntroMenu();
	void Draw();
	void DoUpdate(int iCurrentTime);
};

