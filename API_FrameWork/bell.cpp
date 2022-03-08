#include "framework.h"
#include "bell.h"
#include "player.h"
#include "enemyManager.h"
#include "panda.h"
bell::bell()
{
}

bell::~bell()
{
}

HRESULT bell::init(float x, float y)
{
	tagBell bell;
	bell.bellImg = IMAGE->addFrameImage("벨", "images/item/bells.bmp", 216, 288, 4, 6, true);
	bell.x = x;
	bell.y = y;
	bell.rc = RectMake(bell.x, bell.y, bell.bellImg->getFrameWidth(), bell.bellImg->getFrameHeight());
	bell.color = (BELLCOLOR)giveRandomColor();
	bell.count = 0;
	bell.frameCount = 0;
	bell.frameX = 0;
	bell.frameY = 0;
	bell.isHit = true;
	bell.isJump = true;
	bell.jumpPower = 12.0f;
	bell.gravity = 0.5f;

	bell.isinvincible = false;
	_vBell.push_back(bell);

	return S_OK;
}

void bell::release()
{
}

void bell::update()
{
	for (_viBell = _vBell.begin(); _viBell != _vBell.end();   )
	{
		collision(*_viBell);
		afterHit(*_viBell);
		giveframe(*_viBell);
		move(*_viBell);
		//벨제거(1.무적이 아닌 플레이어와 충돌시)
		RECT temp;
		if (_py->getpyState()!=player::PLAYERSTATE::BIG &&
			IntersectRect(&temp, &_viBell->rc, &_py->getRc())) {
			if (_viBell->color == BELLCOLOR::YELLO) {
				_py->plusyellooCount();
			}
			else if (_viBell->color == BELLCOLOR::RED) {
				_py->setVerticalLaser();
			}
			else if (_viBell->color == BELLCOLOR::GREEN) {
				_py->setGreenEffect();
			}
			else if (_viBell->color == BELLCOLOR::WHITE) {
				_py->setMegaphone();
			}
			else if (_viBell->color == BELLCOLOR::BLUE) {
				_py->setBlueExplosion();
			}
			else if (_viBell->color == BELLCOLOR::PURPLE) {
				_em->setPurpleItem();
				_pd->setPurpleItem();
			}
			_viBell = _vBell.erase(_viBell);
		}
		else {
			++_viBell;
		}
	}
	//벨제거(2.화면밖으로 나갈시)
	ifOutOfRengeRemove();
	//체크박스점검
	checkBoxCollision();
}

void bell::render()
{
	for (_viBell = _vBell.begin(); _viBell != _vBell.end(); ++_viBell)
	{
		if (_isDebug) Rectangle(getMemDC(), _viBell->rc.left, _viBell->rc.top, _viBell->rc.right, _viBell->rc.bottom);
		_viBell->bellImg->frameRender(getMemDC(), _viBell->x, _viBell->y, _viBell->frameX, _viBell->frameY);
	}
}

void bell::giveframe(tagBell& bell)
{
	bell.frameCount++;
	if (bell.frameCount % 8 == 0)
	{
		bell.frameCount = 0;
		int currentFrame = bell.frameX;
		currentFrame++;
		if (currentFrame > bell.bellImg->getMaxFrameX()) currentFrame = 0;
		bell.frameX = currentFrame;
	}
	bell.frameY = (int)bell.color;
}

void bell::collision(tagBell& bell)
{
	//총알과충돌
	RECT temp;
	RECT rc = bell.rc;
	auto _vBullet = _py->getBullet1()->getviperBullet();
	auto _viBullet = _vBullet->begin();
	for (_viBullet; _viBullet != _vBullet->end(); )
	{
		if (!_viBullet->bulletDeath && IntersectRect(&temp, &rc, &_viBullet->rc))
		{
			_viBullet->bulletDeath = true;
			//_viBullet = _vBullet->erase(_viBullet);
			if (!bell.isinvincible) {
				bell.isHit = true;
				bell.isJump = true;
				bell.jumpPower = 12.0f;
				bell.gravity = 0.5f;
			}
		}
		else {
			++_viBullet;
		}
	}
	auto _vBullet2 = _py->getBullet2()->getviperDropMissile();
	auto _viBullet2 = _vBullet2->begin();
	for (_viBullet2; _viBullet2 != _vBullet2->end(); )
	{
		if (!_viBullet2->bulletDeath && IntersectRect(&temp, &rc, &_viBullet2->rc))
		{
			_viBullet2->bulletDeath = true;
			//_viBullet = _vBullet->erase(_viBullet);
			if (!bell.isinvincible) {
				bell.isHit = true;
				bell.isJump = true;
				bell.jumpPower = 12.0f;
				bell.gravity = 0.5f;
			}
		}
		else {
			++_viBullet2;
		}
	}
	auto _vBullet3 = _py->getBullet3()->getviperDigonalBullet();
	auto _viBullet3 = _vBullet3->begin();
	for (_viBullet3; _viBullet3 != _vBullet3->end(); )
	{
		if (!_viBullet3->bulletDeath && IntersectRect(&temp, &rc, &_viBullet3->rc))
		{
			_viBullet3->bulletDeath = true;
			//_viBullet = _vBullet->erase(_viBullet);
			if (!bell.isinvincible) {
				bell.isHit = true;
				bell.isJump = true;
				bell.jumpPower = 12.0f;
				bell.gravity = 0.5f;
			}
		}
		else {
			++_viBullet3;
		}
	}
	auto _vBullet4 = _py->getBullet4()->getviperLaser();
	auto _viBullet4 = _vBullet4->begin();
	for (_viBullet4; _viBullet4 != _vBullet4->end(); )
	{
		if (_viBullet4->hp > 0 && !_viBullet4->bulletDeath && IntersectRect(&temp, &rc, &_viBullet4->rc))
		{
			_viBullet4->hp--;
			//_viBullet = _vBullet->erase(_viBullet);
			if (!bell.isinvincible) {
				bell.isHit = true;
				bell.isJump = true;
				bell.jumpPower = 12.0f;
				bell.gravity = 0.5f;
			}
		}
		else {
			++_viBullet4;
		}
	}
}

int bell::giveRandomColor()
{
	int num = RND->getInt(100) + 1;
	if (num <= 25) return 0;
	else if (num <= 40) return 1;
	else if (num <= 55) return 2;
	else if (num <= 70) return 3;
	else if (num <= 85) return 4;
	else return 5;
}

void bell::afterHit(tagBell& bell)
{
	if (bell.isHit)
	{
		bell.isHit = false;
		bell.isinvincible = true;
		bell.frameX = 0;
		bell.y--;
		if (!(bell.color == BELLCOLOR::YELLO)) bell.color = BELLCOLOR::YELLO;
		else bell.color = (BELLCOLOR)giveRandomColor();
	}
	if (bell.isinvincible) {
		bell.count++;
		if (bell.count % 40 == 0) {
			bell.count = 0;
			bell.isinvincible = false;
		}
	}
}

void bell::move(tagBell& bell)
{
	if (bell.isJump) {
		bell.x += bell.jumpPower;
		bell.jumpPower -= bell.gravity;
		if (bell.jumpPower < 0) {
			bell.isJump = false;
			bell.jumpPower = 0.0f;
		}
	}
	else {
		bell.x -= bell.gravity;
		bell.gravity+=0.15f;
		if (bell.gravity > 9) {
			bell.gravity = 9;
		}
	}
	bell.rc = RectMake(bell.x, bell.y, bell.bellImg->getFrameWidth(), bell.bellImg->getFrameHeight());
}

void bell::ifOutOfRengeRemove()
{
	for (_viBell = _vBell.begin(); _viBell != _vBell.end(); )
	{
		if (_viBell->x + _viBell->bellImg->getFrameWidth() < 0)
		{
			_viBell = _vBell.erase(_viBell);
		}
		else {
			++_viBell;
		}
	}
}

void bell::checkBoxCollision()
{
	RECT temp;
	_viBell = _vBell.begin();
	for (_viBell; _viBell!=_vBell.end(); ++_viBell)
	{
		_icheckBox = _checkBox.begin();
		for (_icheckBox; _icheckBox!= _checkBox.end(); ++_icheckBox)
		{
			if (IntersectRect(&temp, &_viBell->rc, _icheckBox->second))
			{
				if (!_viBell->isinvincible) {
					_viBell->isHit = true;
					_viBell->isJump = true;
					_viBell->jumpPower = 12.0f;
					_viBell->gravity = 0.5f;
				}
			}
		}

	}
}






