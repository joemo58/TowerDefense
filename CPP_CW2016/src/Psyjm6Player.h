#include "header.h"
#include "templates.h"

#include "DisplayableObject.h"
class Psyjm6Player :
	public DisplayableObject
{
public:
	Psyjm6Player(BaseEngine* pEngine, int iMapX, int iMapY);
	~Psyjm6Player();
	void Draw();
	void DoUpdate(int iCurrentTime);
};

