#include "header.h"
#include "templates.h"
#include "TDTileManager.h"


TDTileManager::TDTileManager() : TileManager(20, 20)
{

}

TDTileManager::~TDTileManager()
{
}

unsigned int tileColour = 0x52fd52;

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
		tileColour,
		pSurface);
}

void UpdateTileAt(BaseEngine* pEngine,
	int iMapX, int iMapY, int iNewTileValue,
	int iScreenLeftTilePosition, int iScreenTopTilePosition){
}


void TDTileManager::SetColour(BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int tileX, int tileY, int colour)
{
	// Base class implementation just draws some grey tiles
	unsigned int iColour = colour;
	int startX = tileX * GetTileWidth() + iMapX;		//add the offset for where the tile manager starts (under status bar)
	int startY = tileY * GetTileWidth() + iMapY;
	pEngine->DrawRectangle(
		startX,
		startY,
		startX + GetTileWidth(),
		startY + GetTileHeight(),
		iColour,
		pSurface);
}



unsigned int TDTileManager::GetColour()
{
	return tileColour;
}
