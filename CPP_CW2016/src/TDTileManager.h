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
	void SetColour(BaseEngine* pEngine,
		SDL_Surface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY, int colour);
	unsigned int GetColour();
};

