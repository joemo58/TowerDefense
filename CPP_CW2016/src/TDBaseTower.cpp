#include "header.h"
#include "templates.h"
#include "TDBaseTower.h"
#include "TDBaseEnemy.h"

int lastTick = 0;
int newTick = 0;
bool cursorOverMap = false;

TDBaseTower::TDBaseTower(BaseEngine* pEngine, int iMapX, int iMapY) : DisplayableObject(pEngine)
{
	m_iDrawWidth = 17;
	m_iDrawHeight = 17;
	m_iPreviousScreenX = m_iCurrentScreenX = iMapX;
	m_iPreviousScreenY = m_iCurrentScreenY = iMapY;
	lastTick = GetEngine()->GetTime();
	range = 190;
	damage = 1;
	towerImage.LoadImage("base_tower_paint.png");
	towerImageS.ShrinkFrom(&towerImage, 2);
}

TDBaseTower::~TDBaseTower()
{
}

void TDBaseTower::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;

	/*GetEngine()->DrawScreenRectangle(m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1, 0xff3300);*/

	/*currentScreenX -2 for the offset of the image - bad bitmap*/
	towerImage.RenderImageWithMask(GetEngine()->GetForeground(), 0, 0, m_iCurrentScreenX - 5, m_iCurrentScreenY - 5,
		towerImage.GetWidth(), towerImage.GetHeight());

	// This will store the position at which the object was drawn
	// so that the background can be drawn over the top.	
	// This will then remove the object from the screen.
	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;
	RedrawObjects();
}

void TDBaseTower::DoUpdate(int iCurrentTime){

	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;

	if (EnemyInRange()){
		printf("in range\n");
		newTick = GetEngine()->GetTime();
		if (newTick >= (lastTick + fireRate)){
			//printf("spawn bullet\n");
			playStateEngine->SpawnBullet(m_iCurrentScreenX + m_iDrawWidth/2, m_iCurrentScreenY+m_iDrawWidth/2, closestEnemyX, closestEnemyY, damage);
			lastTick = newTick;
		}
	}

	if (m_iCurrentScreenX > GetEngine()->GetScreenWidth()){
		m_iCurrentScreenX = m_iPreviousScreenX;
	}
	if(m_iCurrentScreenY > GetEngine()->GetScreenHeight()){
		m_iCurrentScreenY = m_iPreviousScreenY;
	}
}


bool TDBaseTower::EnemyInRange()
{
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

		
		if (enemy->IsVisible()){
			//printf("Checking in range");
			//printf("enemy found");
			int iXDiff = abs(enemy->GetXCentre() - m_iCurrentScreenX);
			int iYDiff = abs(enemy->GetYCentre() - m_iCurrentScreenY);

			int sum = iXDiff + iYDiff;
			//printf("Sum = %d\n", sum);

			if (sum < range)		//within the range of the tower
			{
			//	printf("SUM LESS TAHN RANGE\n");
			//	printf("ENEMY IS VISIBLE too!!!!\n");
				closestEnemyX = enemy->GetXCentre();
				closestEnemyY = enemy->GetYCentre();
				return true;
			}
		}
		else {
			return false;
		}
	}
	return false;	
}

/*ARGS = x,y coordinate of the current square cursor is over/square is to move to*/
void TDBaseTower::moveTower(int iX, int iY)
{
	iX = fixXBounds(iX);
	iY = fixYBounds(iY);
	
	/*Used for arrow key movement of tower*/
	m_iCurrentMapSquareX = iX;
	m_iCurrentMapSquareY = iY;
	/*takes the tile x,y from tile manager and uses it to snap tower to grid*/
	m_iCurrentScreenX = mainEngine->GetTileWidth() * iX + 2;
	m_iCurrentScreenY = mainEngine->GetTileWidth() * iY + 40 + 2;
	RedrawObjects();
}


int TDBaseTower::GetTowerType(){
	return towerType;
}


void TDBaseTower::IsOnMap(bool onMap)
{
	if (onMap){
		cursorOverMap = true;
	}
	else {
		cursorOverMap = false;
	}
}


void TDBaseTower::moveUp(int moves)
{
	moveTower(m_iCurrentMapSquareX, (m_iCurrentMapSquareY - moves));
}


void TDBaseTower::moveDown(int moves)
{
	moveTower(m_iCurrentMapSquareX, (m_iCurrentMapSquareY + moves));
}


void TDBaseTower::moveLeft(int moves)
{
	moveTower((m_iCurrentMapSquareX - moves), m_iCurrentMapSquareY);
}


void TDBaseTower::moveRight(int moves)
{
	moveTower((m_iCurrentMapSquareX + moves), m_iCurrentMapSquareY);
}


int TDBaseTower::fixXBounds(int iX)
{
	if (iX < 0)
		iX = 0;
	if (iX > 29)
		iX = 29;
	return iX;
}

int TDBaseTower::fixYBounds(int iY)
{
	if (iY < 0)
		iY = 0;
	if (iY > 24)
		iY = 24;
	return iY;
}
