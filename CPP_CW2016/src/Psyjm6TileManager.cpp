#include "header.h"
#include "templates.h"
#include "Psyjm6TileManager.h"


Psyjm6TileManager::Psyjm6TileManager():TileManager(20, 20){
}
Psyjm6TileManager::Psyjm6TileManager(int iTileHeight, int iTileWidth) : TileManager(iTileHeight, iTileWidth)
{
}

Psyjm6TileManager::~Psyjm6TileManager()
{
}

void Psyjm6TileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	pEngine->DrawOval(
		iStartPositionScreenX,
		iStartPositionScreenY,
		iStartPositionScreenX + GetTileWidth() - 1,
		iStartPositionScreenY + GetTileHeight() - 1,
		pEngine->GetColour(GetValue(iMapX, iMapY)),
		pSurface);

}

