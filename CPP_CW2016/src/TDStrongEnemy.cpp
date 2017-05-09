#include "header.h"
#include "templates.h"
#include "TDStrongEnemy.h"
#include "JPGImage.h"

TDStrongEnemy::TDStrongEnemy(BaseEngine* pEngine, int iMapX, int iMapY, int delay) : TDBaseEnemy(pEngine, iMapX, iMapY, delay)
{
	speed = 300;
	health = 10;
}


TDStrongEnemy::~TDStrongEnemy()
{
}

void TDStrongEnemy::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	ImageData im, im2;
	// Load the image file into an image object - at the normal size
	im2.LoadImage("enemy.png");
	// Create a second image from the first, by halving the size
	im.ShrinkFrom(&im2, 2);

	im.RenderImageWithMask(GetEngine()->GetBackground(),
		0, 0,
		100, 100,
		im.GetWidth(), im.GetHeight());

	GetEngine()->DrawScreenOval(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0xf4a460);

	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.	
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}
