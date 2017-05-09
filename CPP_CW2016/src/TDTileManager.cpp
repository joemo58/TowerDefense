#include "header.h"
#include "templates.h"
#include "TDTileManager.h"


TDTileManager::TDTileManager() : TileManager(20, 20)
{

}

TDTileManager::~TDTileManager()
{
}

void TDTileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	pEngine->DrawRectangle(
		iStartPositionScreenX,
		iStartPositionScreenY,
		iStartPositionScreenX + GetTileWidth() - 1,
		iStartPositionScreenY + GetTileWidth() - 1,
		0x52fd52,
		pSurface);
}

void UpdateTileAt(BaseEngine* pEngine,
	int iMapX, int iMapY, int iNewTileValue,
	int iScreenLeftTilePosition, int iScreenTopTilePosition){
}
	