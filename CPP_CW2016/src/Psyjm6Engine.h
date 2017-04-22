#include "BaseEngine.h"
#include "Psyjm6TileManager.h"
#include <string>

class Psyjm6Engine :
	public BaseEngine
{
public:
	Psyjm6Engine();
	~Psyjm6Engine();
	void Psyjm6Engine::SetupBackgroundBuffer();
	void Psyjm6Engine::DrawStringsUnderneath();
	void MouseDown(int iButton, int iX, int iY);

private:
	Psyjm6TileManager m_oTiles;
	int score = 0;
	int item_number = 0;
public:
	int InitialiseObjects();
};


