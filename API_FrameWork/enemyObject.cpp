#include "framework.h"
#include "enemyObject.h"
enemyObject::enemyObject()
{
	death1 = IMAGE->addFrameImage("오브젝트사망1", "images/enemy/deadExplosion.bmp", 896, 128, 7, 1, true);
}

enemyObject::~enemyObject()
{
}

HRESULT enemyObject::init()
{
	return S_OK;
}

void enemyObject::release()
{
}

void enemyObject::update()
{
}

void enemyObject::render()
{
}

bool enemyObject::showExplosion(float x, float y, int frameX, int frameY, int deathNum)
{
	switch (deathNum)
	{
	case 1:
		if (frameX > death1->getMaxFrameX()) {
			return true;
		}
		IMAGE->frameRender("오브젝트사망1", getMemDC(), x, y, frameX, frameY);
		break;
	case 2:
		if (frameX > death2->getMaxFrameX()) {
			return true;
		}
		IMAGE->frameRender("몬스터사망2", getMemDC(), x, y, frameX, frameY);
		break;
	default:
		break;
	}
	return false;
}