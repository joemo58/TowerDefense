#include "header.h"
#include "templates.h"
#include "TDStrongEnemy.h"
#include "JPGImage.h"

int spriteOffsetX = 15;
int spriteOffsetY = 24;

TDStrongEnemy::TDStrongEnemy(BaseEngine* pEngine, int delay) : TDBaseEnemy(pEngine, delay)
{
	this->LoadImages();
	speed = 300;
	health = 10;
}


TDStrongEnemy::~TDStrongEnemy()
{
}

void TDStrongEnemy::LoadImages()
{
	sLlama1.LoadImage("strong_llama0.png");
	sLlama2.LoadImage("strong_llama1.png");
	sLlama3.LoadImage("strong_llama2.png");
	sLlama4.LoadImage("strong_llama3.png");
	sLlama5.LoadImage("strong_llama4.png");
	sLlama6.LoadImage("strong_llama5.png");
}

void TDStrongEnemy::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	string healthStr = to_string(health);
	const char *healthCstr = healthStr.c_str();
	GetEngine()->DrawScreenString(m_iCurrentScreenX, m_iCurrentScreenY - 30, healthCstr, 0xFF0000,
		GetEngine()->GetFont("Cornerstone Regular.ttf", 15));

	switch (spriteNumber){
	case 0:
		sLlama1.RenderImageWithMask(GetEngine()->GetForeground(),
			0, 0,
			m_iCurrentScreenX - spriteOffsetX, m_iCurrentScreenY - spriteOffsetY,
			sLlama1.GetWidth(), sLlama1.GetHeight());
		break;
	case 1:
		sLlama2.RenderImageWithMask(GetEngine()->GetForeground(),
			0, 0,
			m_iCurrentScreenX - spriteOffsetX, m_iCurrentScreenY - spriteOffsetY,
			sLlama2.GetWidth(), sLlama2.GetHeight());
		break;
	case 2:
		sLlama3.RenderImageWithMask(GetEngine()->GetForeground(),
			0, 0,
			m_iCurrentScreenX - spriteOffsetX, m_iCurrentScreenY - spriteOffsetY,
			sLlama3.GetWidth(), sLlama3.GetHeight());
		break;
	case 3:
		sLlama4.RenderImageWithMask(GetEngine()->GetForeground(),
			0, 0,
			m_iCurrentScreenX - spriteOffsetX, m_iCurrentScreenY - spriteOffsetY,
			sLlama4.GetWidth(), sLlama4.GetHeight());
		break;
	case 4:
		sLlama5.RenderImageWithMask(GetEngine()->GetForeground(),
			0, 0,
			m_iCurrentScreenX - spriteOffsetX, m_iCurrentScreenY - spriteOffsetY,
			sLlama5.GetWidth(), sLlama5.GetHeight());
		break;
	case 5:
		sLlama6.RenderImageWithMask(GetEngine()->GetForeground(),
			0, 0,
			m_iCurrentScreenX - spriteOffsetX, m_iCurrentScreenY - spriteOffsetY,
			sLlama6.GetWidth(), sLlama6.GetHeight());
		break;
	}

	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.	
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}



