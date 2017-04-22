#include "header.h"
#include "templates.h"
#include "Psyjm6Enemy.h"


Psyjm6Enemy::Psyjm6Enemy(BaseEngine* pEngine, int iMapX, int iMapY) 
: DisplayableObject(pEngine)
{
	m_iDrawWidth = 30;
	m_iDrawHeight = 30;
}


Psyjm6Enemy::~Psyjm6Enemy()
{
}


void Psyjm6Enemy::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	/*GetEngine()->DrawScreenOval(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0xff3300);*/

	GetEngine()->DrawScreenShortenedArrow(m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1, 20, 30, 0xff3300, 5, 7);
	
	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.	
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}


void Psyjm6Enemy::SetMovement(int iStartTime, int iEndTime, int iCurrentTime,
	int iStartX, int iStartY, int iEndX, int iEndY)
{
	m_oMover.Setup(iStartX, iStartY, iEndX, iEndY, iStartTime, iEndTime);
	m_oMover.Calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMover.GetX();
	m_iCurrentScreenY = m_oMover.GetY();

}

MovementPosition Psyjm6Enemy::getMovementPosition(){
	return m_oMover;
}

void Psyjm6Enemy::SetPosition(double dX, double dY)
{
	m_iCurrentScreenX = dX;
	m_iCurrentScreenY = dY;
}

void Psyjm6Enemy :: SetSpeed(double dSX, double dSY)
{
	m_dSX = dSX;
	m_dSY = dSY;
}

void Psyjm6Enemy::DoUpdate(int iCurrentTime)
{/*

	// Work out current position
	m_oMover.Calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMover.GetX();
	m_iCurrentScreenY = m_oMover.GetY();

	// If movement has finished then request instructions
	if (m_oMover.HasMovementFinished(iCurrentTime))
	{
		m_oMover.Reverse();
		m_oMover.Calculate(iCurrentTime);
		m_iCurrentScreenX = m_oMover.GetX();
		m_iCurrentScreenY = m_oMover.GetY();
	}

	
	if (m_iCurrentScreenX < 0)
		m_oMover.Reverse();
	if (m_iCurrentScreenX >= GetEngine()->GetScreenWidth() - m_iDrawWidth)
		m_oMover.Reverse();
	if (m_iCurrentScreenY < 0)
		m_oMover.Reverse();
	if (m_iCurrentScreenY >= GetEngine()->GetScreenHeight() - m_iDrawHeight)
		m_oMover.Reverse();
		*/

	m_iCurrentScreenX += m_dSX;
	m_iCurrentScreenY += m_dSY;

	if ((m_iCurrentScreenX + m_iStartDrawPosX) < 0)
	{
		m_iCurrentScreenX = -m_iStartDrawPosX;				//make it positive
		if (m_dSX < 0)
			m_dSX = -m_dSX;
	}

	if ((m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth) >(GetEngine()->GetScreenWidth() - 1))
	{
		m_iCurrentScreenX = GetEngine()->GetScreenWidth() - 1 - m_iStartDrawPosX - m_iDrawWidth;
		if (m_dSX > 0)
			m_dSX = -m_dSX;
	}

	if ((m_iCurrentScreenY + m_iStartDrawPosY) < 0)
	{
		m_iCurrentScreenY = -m_iStartDrawPosY;
		if (m_dSY < 0)
			m_dSY = -m_dSY;
	}

	if ((m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight) >(GetEngine()->GetScreenHeight() - 1))
	{
		m_iCurrentScreenY = GetEngine()->GetScreenHeight() - 1 - m_iStartDrawPosY - m_iDrawHeight;
		if (m_dSY > 0)
			m_dSY = -m_dSY;
	}


	// Work out current position
	m_iCurrentScreenX = (int)(m_iCurrentScreenX + 0.5);
	m_iCurrentScreenY = (int)(m_iCurrentScreenY + 0.5);

	RedrawObjects();

}

