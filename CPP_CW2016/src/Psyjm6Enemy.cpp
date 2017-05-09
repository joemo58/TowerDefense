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
{

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

	// Work out current position
	m_iCurrentScreenX = (int)(m_iCurrentScreenX + 0.5);
	m_iCurrentScreenY = (int)(m_iCurrentScreenY + 0.5);

	//RedrawObjects();

}

