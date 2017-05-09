#include "Psyjm6EnemySphere.h"



Psyjm6EnemySphere::Psyjm6EnemySphere(BaseEngine* pEngine, int iMapX, int iMapY)
: Psyjm6Enemy(pEngine, iMapX, iMapY)
{
}


Psyjm6EnemySphere::~Psyjm6EnemySphere()
{
}

void Psyjm6EnemySphere::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;
	/*head*/
	GetEngine()->DrawScreenOval(
	m_iCurrentScreenX, m_iCurrentScreenY,
	m_iCurrentScreenX + m_iDrawWidth - 1,
	m_iCurrentScreenY + m_iDrawHeight - 1,
	0xff3300);
	/*eye1*/
	GetEngine()->DrawScreenOval(
		m_iCurrentScreenX + 10, m_iCurrentScreenY + 10,
		m_iCurrentScreenX + m_iDrawWidth - 16,
		m_iCurrentScreenY + m_iDrawHeight - 16,
		0x111111);
	/*eye2*/
	GetEngine()->DrawScreenOval(
		m_iCurrentScreenX + 17, m_iCurrentScreenY + 10,
		m_iCurrentScreenX + m_iDrawWidth - 9,
		m_iCurrentScreenY + m_iDrawHeight - 16,
		0x111111);
	/*mouth*/
	GetEngine()->DrawScreenLine(
		m_iCurrentScreenX + 8, m_iCurrentScreenY + 19,
		m_iCurrentScreenX + 22,
		m_iCurrentScreenY + 19,
		0x111111);
	
	/*icurrentscreenx = WHERE on ScrEEN oBject currentlty is*/
	/*body*/
	GetEngine()->DrawScreenRectangle(
		m_iCurrentScreenX + 8, m_iCurrentScreenY + m_iDrawHeight + 8/*end y*/,
		m_iCurrentScreenX + m_iDrawWidth - 10,
		m_iCurrentScreenY + m_iDrawHeight - 3, /*start y*/
		0xff3300);

	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.	
	// This will then remove the object from the screen.
	StoreLastScreenPositionForUndraw();
}

void Psyjm6EnemySphere::SetMovement(int iStartTime, int iEndTime, int iCurrentTime,
	int iStartX, int iStartY, int iEndX, int iEndY)
{
	m_oMover.Setup(iStartX, iStartY, iEndX, iEndY, iStartTime, iEndTime);
	m_oMover.Calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMover.GetX();
	m_iCurrentScreenY = m_oMover.GetY();
}

void Psyjm6EnemySphere::DoUpdate(int iCurrentTime){

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

	/*
	if (m_iCurrentScreenX < 0)
		m_oMover.Reverse();
	if (m_iCurrentScreenX >= GetEngine()->GetScreenWidth() - m_iDrawWidth)
		m_oMover.Reverse();
	if (m_iCurrentScreenY < 0)
		m_oMover.Reverse();
	if (m_iCurrentScreenY >= GetEngine()->GetScreenHeight() - m_iDrawHeight)
		m_oMover.Reverse();
		*/

	RedrawObjects();
}

