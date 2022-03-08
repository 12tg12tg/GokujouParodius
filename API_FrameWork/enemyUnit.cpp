#include "framework.h"
#include "enemyUnit.h"
enemyUnit::enemyUnit()
{
	death1 = IMAGE->addFrameImage("∏ÛΩ∫≈ÕªÁ∏¡1", "images/enemy/deadExplosion.bmp", 336, 48, 7, 1, true);
	death2 = IMAGE->addFrameImage("∏ÛΩ∫≈ÕªÁ∏¡2", "images/enemy/deadExplosion2.bmp", 180, 60, 3, 1, true);
}

enemyUnit::~enemyUnit()
{
}

HRESULT enemyUnit::init()
{
    return S_OK;
}

void enemyUnit::release()
{
}

void enemyUnit::update()
{
}

void enemyUnit::render()
{
}

bool enemyUnit::showExplosion(float x, float y, int frameX, int frameY, int deathNum)
{
	switch (deathNum)
	{
	case 1:
		if (frameX > death1->getMaxFrameX()) {
			return true;
		}
		IMAGE->frameRender("∏ÛΩ∫≈ÕªÁ∏¡1", getMemDC(), x, y, frameX, frameY);
		break;
	case 2:
		if (frameX > death2->getMaxFrameX()) {
			return true;
		}
		IMAGE->frameRender("∏ÛΩ∫≈ÕªÁ∏¡2", getMemDC(), x, y, frameX, frameY);
		break;
	default:
		break;
	}
	return false;
}
