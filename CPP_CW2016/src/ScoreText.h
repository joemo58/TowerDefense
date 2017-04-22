#pragma once
#include "header.h"
#include "templates.h"

#include "DisplayableObject.h"
class ScoreText :
	public DisplayableObject
{
public:
	ScoreText(BaseEngine* pEngine);
	~ScoreText();
	int score;
	void Draw();
	void DoUpdate(int iCurrentTime);
};



