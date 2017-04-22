#include "ScoreText.h"
#include <string>


ScoreText::ScoreText(BaseEngine* pEngine ) : DisplayableObject(pEngine)
{
	score = 0;
}


ScoreText::~ScoreText()
{
}




void ScoreText::Draw()
{
	std::string score_str = std::to_string(score);
	char const *score_char = score_str.c_str();
	GetEngine()->DrawScreenString(290, 80, score_char, 0x1a0000, NULL);
}


void ScoreText::DoUpdate(int iCurrentTime)
{
	GetEngine()->Redraw(false);
	std::string score_str = std::to_string(score);
	char const *score_char = score_str.c_str();
	GetEngine()->DrawScreenString(290, 80, score_char, 0x1a0000, NULL);
}
