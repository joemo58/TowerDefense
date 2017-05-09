#include "header.h"
#include "templates.h"
#include "TDIntroMenu.h"


TDIntroMenu::TDIntroMenu(BaseEngine* pEngine, int iMapX, int iMapY):DisplayableObject(pEngine)
{
	m_iDrawWidth = 30;
	m_iDrawHeight = 30;
}

TDIntroMenu::~TDIntroMenu()
{
}

void TDIntroMenu::Draw()
{
	// Do not draw if it should not be visible
	if (!IsVisible())
		return;
	char* description = "A Tower Defense strategy game built using C++ 11 and SDL 1.2.\n";
	GetEngine()->DrawBackgroundRectangle(100, 100, GetEngine()->GetScreenWidth() - 100, GetEngine()->GetScreenHeight() - 150, 0x3e8ff2);
	GetEngine()->DrawBackgroundString(GetEngine()->GetScreenWidth() / 4, 140, "Dirty Zombie Horde Defense", 0x1a0000, NULL);
	GetEngine()->DrawBackgroundString(GetEngine()->GetScreenWidth() / 4, 200, description, 0x1a0000, NULL);
	StoreLastScreenPositionForUndraw();
}

void TDIntroMenu::DoUpdate(int iCurrentTime)
{
	RedrawObjects();
}
