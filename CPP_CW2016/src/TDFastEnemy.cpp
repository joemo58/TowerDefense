#include "header.h"
#include "templates.h"
#include "TDFastEnemy.h"
#include "JPGImage.h"


TDFastEnemy::TDFastEnemy(BaseEngine* pEngine, int delay) : TDBaseEnemy(pEngine, delay)
{
	speed = 700;
}


TDFastEnemy::~TDFastEnemy()
{
}

void TDFastEnemy::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	string healthStr = to_string(health);
	const char *healthCstr = healthStr.c_str();
	GetEngine()->DrawScreenString(m_iCurrentScreenX, m_iCurrentScreenY - 10, healthCstr, 0xFF0000,
		GetEngine()->GetFont("Cornerstone Regular.ttf", 11));

	GetEngine()->DrawScreenOval(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0x9e41ff);

	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.	
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}
