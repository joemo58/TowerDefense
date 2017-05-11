#pragma once
#include "TDBaseEnemy.h"
#include "JPGImage.h"
class TDStrongEnemy :
	public TDBaseEnemy
{
public:
	TDStrongEnemy(BaseEngine* pEngine, int delays);
	~TDStrongEnemy();
	void Draw();
private:
	ImageData sLlama1, sLlama2, sLlama3, sLlama4, sLlama5, sLlama6;
protected:
	int lastTickMs = 0;
	int newTickMs = 0;
public:
	void LoadImages();
};

