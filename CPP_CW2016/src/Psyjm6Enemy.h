#pragma once
#include "DisplayableObject.h"
#include "MovementPosition.h"

class Psyjm6Enemy :
	public DisplayableObject
{
public:
	Psyjm6Enemy(BaseEngine* pEngine, int iMapX, int iMapY);
	~Psyjm6Enemy();
	void Draw();
	void DoUpdate(int iCurrentTime);
	void SetMovement(int iStartTime, int iEndTime, int iCurrentTime,
		int iStartX, int iStartY, int iEndX, int iEndY);
	MovementPosition getMovementPosition();
	void SetSpeed(double dsX, double dsY);
	void SetPosition(double dX, double dY);

private:
	MovementPosition m_oMover;
	BaseEngine* m_pMainEngine;
	int m_iMapX;
	int m_iMapY;
	int m_iDir;

protected:
	double m_dSX;
	double m_dSY;

};

