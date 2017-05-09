#include "header.h"
#include "templates.h"
#include "TDBullet.h"
#include "TDBaseEnemy.h"

TDBullet::TDBullet(BaseEngine* pEngine, int iMapX, int iMapY) : DisplayableObject(pEngine)
{
	m_iDrawWidth = 8;
	m_iDrawHeight = 8;
	m_iPreviousScreenX = m_iCurrentScreenX = iMapX;
	m_iPreviousScreenY = m_iCurrentScreenY = iMapY;

}


TDBullet::~TDBullet()
{
}

void TDBullet::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	GetEngine()->DrawScreenOval(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		GetEngine()->GetColour(0));

	StoreLastScreenPositionForUndraw();
}

void TDBullet::SetMovement(int iStartTime, int iEndTime, int iCurrentTime,
	int iStartX, int iStartY, int iEndX, int iEndY)
{
	m_oMover.Setup(iStartX, iStartY, iEndX, iEndY, iStartTime, iEndTime);
	m_oMover.Calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMover.GetX();
	m_iCurrentScreenY = m_oMover.GetY();
}

void TDBullet::DoUpdate(int iCurrentTime)
{
	// Work out current position
	m_oMover.Calculate(iCurrentTime);
	m_iCurrentScreenX = m_oMover.GetX();
	m_iCurrentScreenY = m_oMover.GetY();

	// Work out current position
	m_iCurrentScreenX = (int)(m_iCurrentScreenX + 0.5);
	m_iCurrentScreenY = (int)(m_iCurrentScreenY + 0.5);
	RedrawObjects();

	if (m_oMover.HasMovementFinished(iCurrentTime))
	{
		SetVisible(false);//also deletes it....
	}

	/********** EXTRA STUFF FOR COLLISIONS *******/

	// Iterate through the objects
	// We are looking for one which is too close to us
	DisplayableObject* pObject;
	for (int iObjectId = 0; (pObject = GetEngine()->GetDisplayableObject(iObjectId)) != NULL; iObjectId++)
	{
		TDBaseEnemy* enemy = dynamic_cast<TDBaseEnemy*>(pObject);
		if (enemy == NULL)
		{
			// This object is not an enemy so skip it
			continue;
		}

		int iXDiff = abs(enemy->GetXCentre() - m_iCurrentScreenX);
		int iYDiff = abs(enemy->GetYCentre() - m_iCurrentScreenY);
		int iSizeOther = enemy->GetDrawWidth();

		// Pythagorus' theorum:
		if (((iXDiff*iXDiff) + (iYDiff*iYDiff))
			<= ((m_iDrawWidth + iSizeOther)*(m_iDrawWidth + iSizeOther)))		//change the size to be same as enemy
		{
			/*delete bullet*/
			printf("Collision!!");
			/*Reduce the life of the enemy by whatever hitpoint the current bullet has*/
			enemy->ReduceHealth(2);
			//RedrawObjects();
			return;
		}
	}
	/********* END EXTRA STUFF FOR COLLISIONS********/

}

void TDBullet::SetDamage(int damage)
{
	this->damage = damage;
}
