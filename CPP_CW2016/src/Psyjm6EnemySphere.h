#pragma once
#include "header.h"
#include "templates.h"
#include "Psyjm6Enemy.h"
class Psyjm6EnemySphere :
	public Psyjm6Enemy
{
public:
	Psyjm6EnemySphere(BaseEngine* pEngine, int iMapX, int iMapY);
	~Psyjm6EnemySphere();
	void Draw();
	void DoUpdate(int iCurrentTime);
	void SetMovement(int iStartTime, int iEndTime, int iCurrentTime,
		int iStartX, int iStartY, int iEndX, int iEndY);

private :
	MovementPosition m_oMover;
};

