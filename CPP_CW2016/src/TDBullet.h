#pragma once
#include "DisplayableObject.h"
#include "MovementPosition.h"
class TDBullet :
	public DisplayableObject
{
public:
	TDBullet(BaseEngine* pEngine, int iMapX, int iMapY);
	~TDBullet();
	void Draw();
	void DoUpdate(int iCurrentTime);
	void SetMovement(int iStartTime, int iEndTime, int iCurrentTime,
		int iStartX, int iStartY, int iEndX, int iEndY);
private:
	MovementPosition m_oMover;
	int damage = 0;
public:
	void SetDamage(int damage);
};
