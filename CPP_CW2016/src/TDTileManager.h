#pragma once
#include "TileManager.h"
class TDTileManager :
	public TileManager
{
public:
	TDTileManager();
	~TDTileManager();
	void DrawTileAt(BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;
};

