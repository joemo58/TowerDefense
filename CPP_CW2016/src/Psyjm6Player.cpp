#include "Psyjm6Player.h"

int speed;

Psyjm6Player::Psyjm6Player(BaseEngine* pEngine, int iMapX, int iMapY)
: DisplayableObject(pEngine)
{
	m_iDrawWidth = 30;
	m_iDrawHeight = 30;
	speed = 10;
}


Psyjm6Player::~Psyjm6Player()
{
}



void Psyjm6Player::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	GetEngine()->DrawScreenRectangle(m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1, 0x6600ff);
	
		/*GetEngine()->DrawScreenOval(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0xff3300);*/

	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.	
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}


void Psyjm6Player::DoUpdate(int iCurrentTime)
{
	// Change position if player presses a key
	if (GetEngine()->IsKeyPressed(SDLK_UP))
		m_iCurrentScreenY -= 0.5 * speed;
	if (GetEngine()->IsKeyPressed(SDLK_DOWN))
		m_iCurrentScreenY += 0.5 * speed;
	if (GetEngine()->IsKeyPressed(SDLK_LEFT))
		m_iCurrentScreenX -= 0.5 * speed;
	if (GetEngine()->IsKeyPressed(SDLK_RIGHT))
		m_iCurrentScreenX += 0.5 * speed;

	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	if (m_iCurrentScreenX >= GetEngine()->GetScreenWidth() - m_iDrawWidth)
		m_iCurrentScreenX = GetEngine()->GetScreenWidth() - m_iDrawWidth;
	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = 0;
	if (m_iCurrentScreenY >= GetEngine()->GetScreenHeight() - m_iDrawHeight)
		m_iCurrentScreenY = GetEngine()->GetScreenHeight() - m_iDrawHeight;
	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}
