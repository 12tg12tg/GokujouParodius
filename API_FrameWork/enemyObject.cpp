#include "framework.h"
#include "enemyObject.h"
enemyObject::enemyObject()
{
	death1 = IMAGE->addFrameImage("������Ʈ���1", "images/enemy/deadExplosion.bmp", 896, 128, 7, 1, true);
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
		IMAGE->frameRender("������Ʈ���1", getMemDC(), x, y, frameX, frameY);
		break;
	case 2:
		if (frameX > death2->getMaxFrameX()) {
			return true;
		}
		IMAGE->frameRender("���ͻ��2", getMemDC(), x, y, frameX, frameY);
		break;
	default:
		break;
	}
	return false;
}