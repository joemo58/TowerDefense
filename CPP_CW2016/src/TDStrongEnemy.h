#pragma once
#include "TDBaseEnemy.h"
class TDStrongEnemy :
	public TDBaseEnemy
{
public:
	TDStrongEnemy(BaseEngine* pEngine, int iMapX, int iMapY, int delays);
	~TDStrongEnemy();
	void Draw();
};

