#pragma once
#include "TDBaseEnemy.h"

class TDFastEnemy :
	public TDBaseEnemy
{
public:
	TDFastEnemy(BaseEngine* pEngine, int delay);
	~TDFastEnemy();
	void Draw();
private: 
};

