#pragma once
#include "TileManager.h"
class Psyjm6TileManager :
	public TileManager
{
public:
	Psyjm6TileManager();
	Psyjm6TileManager(int iTileHeight, int iTileWidth);
	~Psyjm6TileManager();

	void DrawTileAt(
		BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY
		) const;

};
