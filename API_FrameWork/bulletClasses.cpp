#include "framework.h"
#include "bulletClasses.h"
#include "player.h"
/*
===================================
	Find bullet class ctrl+F4
===================================
	bulletname			imagename
1.	viperBullet			/	바이퍼블릿
2.	eagle1Bullet		/	독수리1블릿
3.	eagle2Bullet		/	독수리2블릿
4.	puppet				/	인형
5.	viperDropMissile	/	바이퍼낙하미사일
6.	viperDigonalBullet	/	바이퍼대각선미사일
7.	viperLaser			/	바이퍼레이저
*/
//==============================================================================================
HRESULT bullet::init()
{
	return E_NOTIMPL;
}

void bullet::release()
{
}

void bullet::update()
{
}

void bullet::render()
{
}
//==============================================================================================

viperBullet::viperBullet()
{
	_bulExplosion = IMAGE->addFrameImage("탄폭발", "images/bullet/bulletdeath.bmp", 96, 24, 4, 1, true);
}

viperBullet::~viperBullet()
{
}

HRESULT viperBullet::init()
{

	return S_OK;
}

void viperBullet::release()
{
}

void viperBullet::update() //플레이어 클래스에서 호출
{
	move();
}

void viperBullet::render() //플레이어클래스에서 호출.
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->bulletDeath) {
			if (_isDebug) Rectangle(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->rc.right, _viBullet->rc.bottom);
			_viBullet->bulletImage->render(getMemDC(), _viBullet->x, _viBullet->y);
		}
		else {
			_bulExplosion->frameRender(getMemDC(), _viBullet->x, _viBullet->y, _viBullet->bulletDeathFrameX, 0);
			_viBullet->bulletDeathFrameX++;
			if (_viBullet->bulletDeathFrameX > _bulExplosion->getMaxFrameX())
				_viBullet->afterExpolsion = true;
		}
	}
	
}

void viperBullet::fire(float x, float y) //플레이어클래스에서 호출.
{
	tagBullet viperBull;

	viperBull.bulletImage = IMAGE->addImage("바이퍼블릿", "images/bullet/viperbullet.bmp", 27, 9, true);
	viperBull.x = x;
	viperBull.y = y;
	viperBull.rc = RectMake(viperBull.x, viperBull.y, viperBull.bulletImage->getWidth(), viperBull.bulletImage->getHeight());
	viperBull.speed = 15.0f;
	viperBull.fire = true;
	viperBull.count = 0;
	viperBull.bulletDeath = false;
	viperBull.bulletDeathFrameX = 0;
	viperBull.afterExpolsion = false;
	_vBullet.push_back(viperBull);
}

void viperBullet::move() //여기서 호출
{
	//총알이동
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		//죽지않은총알만 이동
		if (_viBullet->bulletDeath) continue;
		_viBullet->x += _viBullet->speed;
		_viBullet->rc = RectMake(_viBullet->x, _viBullet->y, _viBullet->bulletImage->getWidth(), _viBullet->bulletImage->getHeight());
	}
	//총알 삭제
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); )
	{
		if (_viBullet->x > WINSIZEX+100||_viBullet->afterExpolsion) {
			_viBullet = _vBullet.erase(_viBullet);
		}
		else {
			++_viBullet;
		}
	}
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

eagle1Bullet::eagle1Bullet()
{
}

eagle1Bullet::~eagle1Bullet()
{
}

HRESULT eagle1Bullet::init()
{
	return S_OK;
}

void eagle1Bullet::release()
{
}

void eagle1Bullet::update()
{
	move();
}

void eagle1Bullet::render()
{
	for (_viEagleBullet = _vEagleBullet.begin(); _viEagleBullet != _vEagleBullet.end(); ++_viEagleBullet)
	{
		if (_isDebug) Rectangle(getMemDC(), _viEagleBullet->bulletInfo.rc.left,
			_viEagleBullet->bulletInfo.rc.top, _viEagleBullet->bulletInfo.rc.right,
			_viEagleBullet->bulletInfo.rc.bottom);
		_viEagleBullet->bulletInfo.bulletImage->frameRender(getMemDC(),
			_viEagleBullet->bulletInfo.x, _viEagleBullet->bulletInfo.y,
			_viEagleBullet->frameX, 0);
	}
}

void eagle1Bullet::fire(float x, float y)
{
	tagEagle1Bullet eagleBullet;
	eagleBullet.bulletInfo.bulletImage = IMAGE->addFrameImage("독수리블릿", "images/bullet/eagle1bullet.bmp", 72, 15, 3, 1, true);
	eagleBullet.bulletInfo.x = x;
	eagleBullet.bulletInfo.y = y;
	eagleBullet.bulletInfo.rc = RectMake(eagleBullet.bulletInfo.x, eagleBullet.bulletInfo.y,
		eagleBullet.bulletInfo.bulletImage->getFrameWidth(),
		eagleBullet.bulletInfo.bulletImage->getFrameHeight());
	eagleBullet.bulletInfo.speed = 6.0f;
	eagleBullet.bulletInfo.fire = true;
	eagleBullet.bulletInfo.count = 0;
	eagleBullet.bulletInfo.angle = PI;
	eagleBullet.frameX = 1;
	_vEagleBullet.push_back(eagleBullet);

	ZeroMemory(&eagleBullet, sizeof(eagleBullet));
	eagleBullet.bulletInfo.bulletImage = IMAGE->addFrameImage("독수리블릿", "images/bullet/eagle1bullet.bmp", 72, 15, 3, 1, true);
	eagleBullet.bulletInfo.x = x;
	eagleBullet.bulletInfo.y = y;
	eagleBullet.bulletInfo.rc = RectMake(eagleBullet.bulletInfo.x, eagleBullet.bulletInfo.y,
		eagleBullet.bulletInfo.bulletImage->getFrameWidth(),
		eagleBullet.bulletInfo.bulletImage->getFrameHeight());
	eagleBullet.bulletInfo.speed = 6.0f;
	eagleBullet.bulletInfo.fire = true;
	eagleBullet.bulletInfo.count = 0;
	eagleBullet.bulletInfo.angle = PI - PI/6;
	eagleBullet.frameX = 0;
	_vEagleBullet.push_back(eagleBullet);

	ZeroMemory(&eagleBullet, sizeof(eagleBullet));
	eagleBullet.bulletInfo.bulletImage = IMAGE->addFrameImage("독수리블릿", "images/bullet/eagle1bullet.bmp", 72, 15, 3, 1, true);
	eagleBullet.bulletInfo.x = x;
	eagleBullet.bulletInfo.y = y;
	eagleBullet.bulletInfo.rc = RectMake(eagleBullet.bulletInfo.x, eagleBullet.bulletInfo.y,
		eagleBullet.bulletInfo.bulletImage->getFrameWidth(),
		eagleBullet.bulletInfo.bulletImage->getFrameHeight());
	eagleBullet.bulletInfo.speed = 6.0f;
	eagleBullet.bulletInfo.fire = true;
	eagleBullet.bulletInfo.count = 0;
	eagleBullet.bulletInfo.angle = PI + PI / 6;
	eagleBullet.frameX = 2;
	_vEagleBullet.push_back(eagleBullet);
}

void eagle1Bullet::move()
{
	//총알 패턴 정의 및 삭제
	for (_viEagleBullet = _vEagleBullet.begin(); _viEagleBullet != _vEagleBullet.end(); )
	{
		_viEagleBullet->bulletInfo.x += cosf(_viEagleBullet->bulletInfo.angle) * _viEagleBullet->bulletInfo.speed;
		_viEagleBullet->bulletInfo.y += -sinf(_viEagleBullet->bulletInfo.angle) * _viEagleBullet->bulletInfo.speed;
		_viEagleBullet->bulletInfo.rc = RectMake(_viEagleBullet->bulletInfo.x, _viEagleBullet->bulletInfo.y,
			_viEagleBullet->bulletInfo.bulletImage->getFrameWidth(),
			_viEagleBullet->bulletInfo.bulletImage->getFrameHeight());
		if (_viEagleBullet->bulletInfo.x > WINSIZEX + 100) {
			_viEagleBullet = _vEagleBullet.erase(_viEagleBullet);
		}
		else {
			++_viEagleBullet;
		}
	}
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

eagle2Bullet::eagle2Bullet(){}

eagle2Bullet::~eagle2Bullet(){}

HRESULT eagle2Bullet::init()
{
	return S_OK;
}

void eagle2Bullet::release()
{
}

void eagle2Bullet::update()
{
	move();
}

void eagle2Bullet::render()
{
	for (_viEagleBullet = _vEagleBullet.begin(); _viEagleBullet != _vEagleBullet.end(); ++_viEagleBullet)
	{
		if (_isDebug) Rectangle(getMemDC(), _viEagleBullet->bulletInfo.rc.left,
			_viEagleBullet->bulletInfo.rc.top, _viEagleBullet->bulletInfo.rc.right,
			_viEagleBullet->bulletInfo.rc.bottom);
		_viEagleBullet->bulletInfo.bulletImage->frameRender(getMemDC(),
			_viEagleBullet->bulletInfo.x, _viEagleBullet->bulletInfo.y,
			_viEagleBullet->frameX, 0);
	}
}

void eagle2Bullet::fire(float x, float y)
{
	tagEagle2Bullet eagleBullet;
	eagleBullet.bulletInfo.bulletImage = IMAGE->addFrameImage("독수리초음파", "images/bullet/eagle2bullet.bmp", 192, 120, 4, 1, true);
	eagleBullet.bulletInfo.x = x;
	eagleBullet.bulletInfo.y = y;
	eagleBullet.bulletInfo.rc = RectMake(eagleBullet.bulletInfo.x,
		eagleBullet.bulletInfo.y + eagleBullet.bulletInfo.bulletImage->getFrameHeight()/2 - 9,
		18,	18);
	eagleBullet.bulletInfo.speed = 5.0f;
	eagleBullet.bulletInfo.fire = true;
	eagleBullet.bulletInfo.count = 0;
	eagleBullet.bulletInfo.angle = PI;
	eagleBullet.frameX = 0;
	_vEagleBullet.push_back(eagleBullet);

}

void eagle2Bullet::move()
{
	//총알 패턴 정의 및 삭제 & 프레임설정 및 프레임에 따른 히트박스 수정
	for (_viEagleBullet = _vEagleBullet.begin(); _viEagleBullet != _vEagleBullet.end(); )
	{
		_viEagleBullet->bulletInfo.x += cosf(_viEagleBullet->bulletInfo.angle) * _viEagleBullet->bulletInfo.speed;
		_viEagleBullet->bulletInfo.y += -sinf(_viEagleBullet->bulletInfo.angle) * _viEagleBullet->bulletInfo.speed;
		giveFrameAndHitBox(_viEagleBullet);
		if (_viEagleBullet->bulletInfo.x > WINSIZEX + 100) {
			_viEagleBullet = _vEagleBullet.erase(_viEagleBullet);
		}
		else {
			++_viEagleBullet;
		}
	}
}

void eagle2Bullet::giveFrameAndHitBox(vector<tagEagle2Bullet>::iterator bullet)
{
	bullet->bulletInfo.count++;
	if (bullet->bulletInfo.count % 20 == 0) {
		bullet->bulletInfo.count = 0;
		bullet->frameX++;
		if(bullet->frameX > bullet->bulletInfo.bulletImage->getMaxFrameX())
			bullet->frameX = bullet->bulletInfo.bulletImage->getMaxFrameX();
	}
	if (bullet->frameX == 1) {
		bullet->bulletInfo.rc =
			RectMake(bullet->bulletInfo.x+bullet->bulletInfo.bulletImage->getFrameWidth()/2-12,
				bullet->bulletInfo.y+bullet->bulletInfo.bulletImage->getFrameHeight()/2 - 24,
				24, 48);
	}
	else if (bullet->frameX == 2) {
		bullet->bulletInfo.rc =
			RectMake(bullet->bulletInfo.x + bullet->bulletInfo.bulletImage->getFrameWidth() / 2-12,
				bullet->bulletInfo.y + bullet->bulletInfo.bulletImage->getFrameHeight() / 2 - 42,
				24, 84);
	}
	else if (bullet->frameX == 3) {
		bullet->bulletInfo.rc = 
			RectMake(bullet->bulletInfo.x + bullet->bulletInfo.bulletImage->getFrameWidth() / 2-12,
				bullet->bulletInfo.y + bullet->bulletInfo.bulletImage->getFrameHeight() / 2 - 60,
				24, 120);
	}
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
puppet::puppet(){}

puppet::~puppet(){}

HRESULT puppet::init()
{
	//문어
	_puppet[0].bulletInfo.bulletImage = new image;
	_puppet[0].bulletInfo.bulletImage->init("images/enemy/clawpupet(1).bmp", 156, 72, 2, 1, true);
	_puppet[0].bulletInfo.bulletImage->setFrameX(0);
	_puppet[0].bulletInfo.x = 0;
	_puppet[0].bulletInfo.y = 0;
	_puppet[0].hasMother = true;
	_puppet[0].isExist = false;
	_puppet[0].motherMax = 1;
	_puppet[0].remainMother = 0;
	_puppet[0].bulletInfo.speed = 4.0f;
	_puppet[0].bulletInfo.rc = RectMake(_puppet[0].bulletInfo.x, _puppet[0].bulletInfo.y, 
		_puppet[0].bulletInfo.bulletImage->getFrameWidth(), _puppet[0].bulletInfo.bulletImage->getFrameHeight());
	_puppet[0].bulletInfo.bulletDeath = false;
	_puppet[0].bulletInfo.bulletDeathFrameX = 0;
	_puppet[0].bulletInfo.afterExpolsion = false;
	_puppet[0].bulletInfo.count = 0; //점프카운트
	_puppet[0].hp = 5;

	//주전자
	_puppet[1].bulletInfo.bulletImage = new image;
	_puppet[1].bulletInfo.bulletImage->init("images/enemy/clawpupet(1).bmp", 156, 72, 2, 1, true);
	_puppet[1].bulletInfo.bulletImage->setFrameX(1);
	_puppet[1].bulletInfo.x = 0;
	_puppet[1].bulletInfo.y = 0;
	_puppet[1].hasMother = true;
	_puppet[1].isExist = false;
	_puppet[1].motherMax = 1;
	_puppet[1].remainMother = 0;
	_puppet[1].bulletInfo.speed = 4.0f;
	_puppet[1].bulletInfo.rc = RectMake(_puppet[1].bulletInfo.x, _puppet[1].bulletInfo.y,
		_puppet[1].bulletInfo.bulletImage->getFrameWidth(), _puppet[1].bulletInfo.bulletImage->getFrameHeight());
	_puppet[1].bulletInfo.bulletDeath = false;
	_puppet[1].bulletInfo.bulletDeathFrameX = 0;
	_puppet[1].bulletInfo.afterExpolsion = false;
	_puppet[1].bulletInfo.count = 0; //데스카운트
	_puppet[1].hp = 5;

	//펭귄
	_puppet[2].bulletInfo.bulletImage = new image;
	_puppet[2].bulletInfo.bulletImage->init("images/enemy/clawpupet(2).bmp", 270, 96, 3, 1, true);
	_puppet[2].bulletInfo.bulletImage->setFrameX(0);
	_puppet[2].bulletInfo.x = 0;
	_puppet[2].bulletInfo.y = 0;
	_puppet[2].hasMother = true;
	_puppet[2].isExist = false;
	_puppet[2].motherMax = 1;
	_puppet[2].remainMother = 0;
	_puppet[2].bulletInfo.speed = 4.0f;
	_puppet[2].bulletInfo.rc = RectMake(_puppet[2].bulletInfo.x, _puppet[2].bulletInfo.y,
		_puppet[2].bulletInfo.bulletImage->getFrameWidth(), _puppet[2].bulletInfo.bulletImage->getFrameHeight());
	_puppet[2].bulletInfo.bulletDeath = false;
	_puppet[2].bulletInfo.bulletDeathFrameX = 0;
	_puppet[2].bulletInfo.afterExpolsion = false;
	_puppet[2].bulletInfo.count = 0; //데스카운트
	_puppet[2].hp = 5;

	//마이크
	_puppet[3].bulletInfo.bulletImage = new image;
	_puppet[3].bulletInfo.bulletImage->init("images/enemy/clawpupet(2).bmp", 270, 96, 3, 1, true);
	_puppet[3].bulletInfo.bulletImage->setFrameX(1);
	_puppet[3].bulletInfo.x = 0;
	_puppet[3].bulletInfo.y = 0;
	_puppet[3].hasMother = true;
	_puppet[3].isExist = false;
	_puppet[3].motherMax = 1;
	_puppet[3].remainMother = 0;
	_puppet[3].bulletInfo.speed = 4.0f;
	_puppet[3].bulletInfo.rc = RectMake(_puppet[3].bulletInfo.x, _puppet[3].bulletInfo.y,
		_puppet[3].bulletInfo.bulletImage->getFrameWidth(), _puppet[3].bulletInfo.bulletImage->getFrameHeight());
	_puppet[3].bulletInfo.bulletDeath = false;
	_puppet[3].bulletInfo.bulletDeathFrameX = 0;
	_puppet[3].bulletInfo.afterExpolsion = false;
	_puppet[3].bulletInfo.count = 0; //데스카운트
	_puppet[3].hp = 5;

	//개복치
	_puppet[4].bulletInfo.bulletImage = new image;
	_puppet[4].bulletInfo.bulletImage->init("images/enemy/clawpupet(2).bmp", 270, 96, 3, 1, true);
	_puppet[4].bulletInfo.bulletImage->setFrameX(2);
	_puppet[4].bulletInfo.x = 0;
	_puppet[4].bulletInfo.y = 0;
	_puppet[4].hasMother = true;
	_puppet[4].isExist = false;
	_puppet[4].motherMax = 1;
	_puppet[4].remainMother = 0;
	_puppet[4].bulletInfo.speed = 4.0f;
	_puppet[4].bulletInfo.rc = RectMake(_puppet[4].bulletInfo.x, _puppet[4].bulletInfo.y,
		_puppet[4].bulletInfo.bulletImage->getFrameWidth(), _puppet[4].bulletInfo.bulletImage->getFrameHeight());
	_puppet[4].bulletInfo.bulletDeath = false;
	_puppet[4].bulletInfo.bulletDeathFrameX = 0;
	_puppet[4].bulletInfo.afterExpolsion = false;
	_puppet[4].bulletInfo.count = 0; //데스카운트
	_puppet[4].hp = 5;

	//간판
	_puppet[5].bulletInfo.bulletImage = new image;
	_puppet[5].bulletInfo.bulletImage->init("images/enemy/board.bmp", 336, 96, true);
	_puppet[5].bulletInfo.x = -339;
	_puppet[5].bulletInfo.y = 185;
	_puppet[5].hasMother = true;
	_puppet[5].isExist = true;
	_puppet[5].motherMax = 2;
	_puppet[5].remainMother = 2;
	_puppet[5].bulletInfo.speed = 4.0f;
	_puppet[5].bulletInfo.rc = RectMake(_puppet[5].bulletInfo.x, _puppet[5].bulletInfo.y+9,
		_puppet[5].bulletInfo.bulletImage->getWidth(), _puppet[5].bulletInfo.bulletImage->getHeight()-9);
	_puppet[5].bulletInfo.bulletDeath = false;
	_puppet[5].bulletInfo.bulletDeathFrameX = 0;
	_puppet[5].bulletInfo.afterExpolsion = false;
	_puppet[5].bulletInfo.count = 0; //데스카운트
	_puppet[5].hp = 10000;
	_puppet[5].specialChange = false;

	return S_OK;
}

void puppet::release()
{
	SAFE_DELETE(_puppet[0].bulletInfo.bulletImage);
	SAFE_DELETE(_puppet[1].bulletInfo.bulletImage);
	SAFE_DELETE(_puppet[2].bulletInfo.bulletImage);
	SAFE_DELETE(_puppet[3].bulletInfo.bulletImage);
	SAFE_DELETE(_puppet[4].bulletInfo.bulletImage);
	SAFE_DELETE(_puppet[5].bulletInfo.bulletImage);
}

void puppet::update(player* py)
{
	deathCheck();
	checkMother();
	fall();
	afterDeath();
	plyaerBulletCollision(py);
}

void puppet::render()
{
	for (size_t i = 0; i < 6; i++)
	{
		if (!_puppet[i].isExist) continue;
		if (!_puppet[i].bulletInfo.bulletDeath) {
			if (_isDebug) Rectangle(getMemDC(), _puppet[i].bulletInfo.rc.left, _puppet[i].bulletInfo.rc.top, _puppet[i].bulletInfo.rc.right, _puppet[i].bulletInfo.rc.bottom);
			if (i != 5) {
				_puppet[i].bulletInfo.bulletImage->frameRender(getMemDC(),
					_puppet[i].bulletInfo.x - _puppet[i].bulletInfo.bulletImage->getFrameWidth() / 2,
					_puppet[i].bulletInfo.y - _puppet[i].bulletInfo.bulletImage->getFrameHeight() / 2);
			}
			else {	//간판
				_puppet[i].bulletInfo.bulletImage->render(getMemDC(), _puppet[i].bulletInfo.x, _puppet[i].bulletInfo.y);
			}
		}
		else {
			IMAGE->frameRender("오브젝트사망1", getMemDC(),
				_puppet[i].bulletInfo.x - _puppet[i].bulletInfo.bulletImage->getFrameWidth() / 2,
				_puppet[i].bulletInfo.y - _puppet[i].bulletInfo.bulletImage->getFrameHeight() / 2,
				_puppet[i].bulletInfo.bulletDeathFrameX, 0);
		}
	}
}

void puppet::checkMother()
{
	for (size_t i = 0; i < 6; i++)
	{
		if (_puppet[i].isExist && _puppet[i].remainMother <= 0)
		{
			_puppet[i].hasMother = false;
		}
	}
}

void puppet::fall()
{
	for (size_t i = 0; i < 6; i++)
	{
		//화면에 존재하는데 엄마가 없다면 낙하
		if (_puppet[i].isExist && !_puppet[i].hasMother)
		{
   			_puppet[i].bulletInfo.y += _puppet[i].bulletInfo.speed;
			_puppet[i].bulletInfo.speed+=0.4;
			_puppet[i].bulletInfo.rc = RectMakeCenter(_puppet[i].bulletInfo.x, _puppet[i].bulletInfo.y, _puppet[i].bulletInfo.bulletImage->getFrameWidth(),
				_puppet[i].bulletInfo.bulletImage->getFrameHeight());
		}
	}
}

void puppet::afterDeath()
{
	for (size_t i = 0; i < 5; i++)
	{
		//죽었을때 터지는 이미지 프레임증가
		if (_puppet[i].bulletInfo.bulletDeath) {
			_puppet[i].bulletInfo.count++;
			if (_puppet[i].bulletInfo.count % 5 == 0)
			{
				_puppet[i].bulletInfo.bulletDeathFrameX++;
				if (_puppet[i].bulletInfo.bulletDeathFrameX > IMAGE->findImage("오브젝트사망1")->getMaxFrameX())
				{
					_puppet[i].bulletInfo.afterExpolsion = true;
				}
			}
		}
		//폭발이후 제거(초기화)
		if (_puppet[i].bulletInfo.afterExpolsion)
		{
			indexInit(i);
		}
	}
}

void puppet::deathCheck()
{
	for (size_t i = 0; i < 5; i++)
	{
		if (!_puppet[i].isExist) continue;
		if ((_puppet[i].bulletInfo.rc.right<-150 && i!=5) ||
			_puppet[i].bulletInfo.rc.left>WINSIZEX + 150 ||
			_puppet[i].bulletInfo.rc.top > WINSIZEY)
		{
	 		indexInit(i);
		}
		if (_puppet[i].hp <= 0)
		{
 	 		_puppet[i].bulletInfo.bulletDeath = true;
		}

	}
}

void puppet::plyaerBulletCollision(player* py)
{
	auto vViperbull = py->getBullet1()->getviperBullet();
	auto viViperbull = vViperbull->begin();
	for (viViperbull; viViperbull != vViperbull->end(); ++viViperbull)
	{
		RECT temp;
		for (size_t i = 0; i < 6; i++)
		{
			if (!_puppet[i].isExist) continue;
			if (!viViperbull->bulletDeath && IntersectRect(&temp, &_puppet[i].bulletInfo.rc, &viViperbull->rc))
			{
				viViperbull->bulletDeath = true;
				_puppet[i].hp--;
			}
		}		
	}
	auto vViperbull2 = py->getBullet2()->getviperDropMissile();
	auto viViperbull2 = vViperbull2->begin();
	for (viViperbull2; viViperbull2 != vViperbull2->end(); ++viViperbull2)
	{
		RECT temp;
		for (size_t i = 0; i < 6; i++)
		{
			if (!_puppet[i].isExist) continue;
			if (!viViperbull2->bulletDeath && IntersectRect(&temp, &_puppet[i].bulletInfo.rc, &viViperbull2->rc))
			{
				viViperbull2->bulletDeath = true;
				_puppet[i].hp--;
			}
		}
	}
	auto vViperbull3 = py->getBullet3()->getviperDigonalBullet();
	auto viViperbull3 = vViperbull3->begin();
	for (viViperbull3; viViperbull3 != vViperbull3->end(); ++viViperbull3)
	{
		RECT temp;
		for (size_t i = 0; i < 6; i++)
		{
			if (!_puppet[i].isExist) continue;
			if (!viViperbull3->bulletDeath && IntersectRect(&temp, &_puppet[i].bulletInfo.rc, &viViperbull3->rc))
			{
				viViperbull3->bulletDeath = true;
				_puppet[i].hp--;
			}
		}
	}
	auto vViperbull4 = py->getBullet4()->getviperLaser();
	auto viViperbull4 = vViperbull4->begin();
	for (viViperbull4; viViperbull4 != vViperbull4->end(); ++viViperbull4)
	{
		RECT temp;
		for (size_t i = 0; i < 6; i++)
		{
			if (!_puppet[i].isExist) continue;
			if (viViperbull4->hp > 0 && !viViperbull4->bulletDeath && IntersectRect(&temp, &_puppet[i].bulletInfo.rc, &viViperbull4->rc))
			{
				viViperbull4->hp--;
				_puppet[i].hp--;
			}
		}
	}
}


puppet::tagpuppet* puppet::givePuppet(float x, float y)
{
	int num;
	while (true) {
		num = RND->getInt(5);

		if (_puppet[num].isExist) {
			continue;
		}
		else {
			_puppet[num].hasMother = true;
			_puppet[num].isExist = true;
			_puppet[num].remainMother = 1;
			_puppet[num].bulletInfo.x = x;
			_puppet[num].bulletInfo.y = y;
			_puppet[num].bulletInfo.rc = RectMakeCenter(x, y, _puppet[num].bulletInfo.bulletImage->getFrameWidth(),
				_puppet[num].bulletInfo.bulletImage->getFrameHeight());
			break;
		}
	}	
	return &_puppet[num];
}

void puppet::indexInit(int index)
{
	_puppet[index].bulletInfo.x = 0;
	_puppet[index].bulletInfo.y = 0;
	_puppet[index].hasMother = false;
	_puppet[index].isExist = false;
	_puppet[index].motherMax = 1;
	_puppet[index].remainMother = 0;
	_puppet[index].bulletInfo.speed = 4.0f;
	_puppet[index].bulletInfo.rc = RectMake(_puppet[index].bulletInfo.x, _puppet[index].bulletInfo.y,
		_puppet[index].bulletInfo.bulletImage->getFrameWidth(), _puppet[index].bulletInfo.bulletImage->getFrameHeight());
	_puppet[index].bulletInfo.bulletDeath = false;
	_puppet[index].bulletInfo.bulletDeathFrameX = 0;
	_puppet[index].bulletInfo.afterExpolsion = false;
	_puppet[index].bulletInfo.count = 0; //점프카운트
	_puppet[index].hp = 5;
}

void puppet::setX(tagpuppet& puppet, float x)
{
	puppet.bulletInfo.x = x;
	if (puppet.hp > 50) {
		_puppet[5].bulletInfo.rc = RectMake(_puppet[5].bulletInfo.x, _puppet[5].bulletInfo.y + 9,
			_puppet[5].bulletInfo.bulletImage->getWidth(), _puppet[5].bulletInfo.bulletImage->getHeight() - 9);
	}
	else {
		puppet.bulletInfo.rc = RectMakeCenter(puppet.bulletInfo.x, puppet.bulletInfo.y, puppet.bulletInfo.bulletImage->getFrameWidth(),
			puppet.bulletInfo.bulletImage->getFrameHeight());
	}
}

void puppet::setY(tagpuppet& puppet, float y)
{
	puppet.bulletInfo.y = y;
	puppet.bulletInfo.rc = RectMakeCenter(puppet.bulletInfo.x, puppet.bulletInfo.y, puppet.bulletInfo.bulletImage->getFrameWidth(),
		puppet.bulletInfo.bulletImage->getFrameHeight());
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
viperDropMissile::viperDropMissile()
{
	_bulExplosion = IMAGE->addFrameImage("탄폭발", "images/bullet/bulletdeath.bmp", 96, 24, 4, 1, true);
}

viperDropMissile::~viperDropMissile(){}

HRESULT viperDropMissile::init()
{
	return S_OK;
}

void viperDropMissile::release()
{
}

void viperDropMissile::update()
{
	move();
}

void viperDropMissile::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->bulletDeath) {
			if (_isDebug) Rectangle(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->rc.right, _viBullet->rc.bottom);
			_viBullet->bulletImage->render(getMemDC(), _viBullet->x, _viBullet->y);
		}
		else {
			_bulExplosion->frameRender(getMemDC(), _viBullet->x, _viBullet->y, _viBullet->bulletDeathFrameX, 0);
			_viBullet->bulletDeathFrameX++;
			if (_viBullet->bulletDeathFrameX > _bulExplosion->getMaxFrameX())
				_viBullet->afterExpolsion = true;
		}
	}
}

void viperDropMissile::fire(float x, float y)
{
	tagBullet viperBull;
	viperBull.bulletImage = IMAGE->addImage("바이퍼낙하미사일", "images/bullet/vipermissile.bmp", 33, 30, true);
	viperBull.x = x-50;
	viperBull.y = y;
	viperBull.rc = RectMake(viperBull.x, viperBull.y, viperBull.bulletImage->getWidth(), viperBull.bulletImage->getHeight()-5);
	viperBull.speed = 10.0f;
	viperBull.angle = PI * (3.0 / 2.0) + PI * (1.0 / 6.0);
	viperBull.fire = true;
	viperBull.count = 0;
	viperBull.bulletDeath = false;
	viperBull.bulletDeathFrameX = 0;
	viperBull.afterExpolsion = false;
	_vBullet.push_back(viperBull);
}

void viperDropMissile::move()
{
	//총알이동
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		//죽지않은총알만 이동
		if (_viBullet->bulletDeath) continue;
		_viBullet->x = _viBullet->x + cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y = _viBullet->y - sinf(_viBullet->angle) * _viBullet->speed;
		_viBullet->rc = RectMake(_viBullet->x, _viBullet->y, _viBullet->bulletImage->getWidth(), _viBullet->bulletImage->getHeight());
	}
	//총알 삭제
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); )
	{
		if (_viBullet->y> WINSIZEY ||_viBullet->x > WINSIZEX + 100 || _viBullet->afterExpolsion) {
			_viBullet = _vBullet.erase(_viBullet);
		}
		else {
			++_viBullet;
		}
	}
}

viperDigonalBullet::viperDigonalBullet()
{
	_bulExplosion = IMAGE->addFrameImage("탄폭발", "images/bullet/bulletdeath.bmp", 96, 24, 4, 1, true);
}

viperDigonalBullet::~viperDigonalBullet()
{
}

HRESULT viperDigonalBullet::init()
{
	return S_OK;
}

void viperDigonalBullet::release()
{

}

void viperDigonalBullet::update()
{
	move();
}

void viperDigonalBullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->bulletDeath) {
			if (_isDebug) Rectangle(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->rc.right, _viBullet->rc.bottom);
			_viBullet->bulletImage->render(getMemDC(), _viBullet->x, _viBullet->y);
		}
		else {
			_bulExplosion->frameRender(getMemDC(), _viBullet->x, _viBullet->y, _viBullet->bulletDeathFrameX, 0);
			_viBullet->bulletDeathFrameX++;
			if (_viBullet->bulletDeathFrameX > _bulExplosion->getMaxFrameX())
				_viBullet->afterExpolsion = true;
		}
	}
}

void viperDigonalBullet::fire(float x, float y)
{
	tagBullet viperBull;
	viperBull.bulletImage = IMAGE->addImage("바이퍼대각선미사일", "images/bullet/diagonalbullet.bmp", 16, 16, true);
	viperBull.x = x;
	viperBull.y = y;
	viperBull.rc = RectMake(viperBull.x, viperBull.y, viperBull.bulletImage->getWidth()-5, viperBull.bulletImage->getHeight() - 5);
	viperBull.speed = 15.0f;
	viperBull.angle =  PI * (1.0 / 4.0);
	viperBull.fire = true;
	viperBull.count = 0;
	viperBull.bulletDeath = false;
	viperBull.bulletDeathFrameX = 0;
	viperBull.afterExpolsion = false;
	_vBullet.push_back(viperBull);
}

void viperDigonalBullet::move()
{
	//총알이동
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		//죽지않은총알만 이동
		if (_viBullet->bulletDeath) continue;
		_viBullet->x = _viBullet->x + cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y = _viBullet->y - sinf(_viBullet->angle) * _viBullet->speed;
		_viBullet->rc = RectMake(_viBullet->x, _viBullet->y, _viBullet->bulletImage->getWidth(), _viBullet->bulletImage->getHeight());
	}
	//총알 삭제
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); )
	{
		if (_viBullet->y + _viBullet->bulletImage->getHeight() < 0 || _viBullet->x > WINSIZEX + 100 || _viBullet->afterExpolsion) {
			_viBullet = _vBullet.erase(_viBullet);
		}
		else {
			++_viBullet;
		}
	}
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
viperLaser::viperLaser()
{
	_bulExplosion = IMAGE->addFrameImage("탄폭발", "images/bullet/bulletdeath.bmp", 96, 24, 4, 1, true);
}

viperLaser::~viperLaser(){}

HRESULT viperLaser::init()
{
	return S_OK;
}

void viperLaser::release()
{
}

void viperLaser::update()
{
	move();
}

void viperLaser::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->bulletDeath) {
			//_viBullet->bulletImage->render(getMemDC(), _viBullet->x, _viBullet->y);
			_viBullet->bulletImage->alphaRender(getMemDC(), _viBullet->x, _viBullet->y, 255 - 42 * (5 - _viBullet->hp));
			if (_isDebug) Rectangle(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->rc.right, _viBullet->rc.bottom);
		}
		else {
			_bulExplosion->frameRender(getMemDC(), _viBullet->x, _viBullet->y, _viBullet->bulletDeathFrameX, 0);
			_viBullet->bulletDeathFrameX++;
			if (_viBullet->bulletDeathFrameX > _bulExplosion->getMaxFrameX())
				_viBullet->afterExpolsion = true;
		}
	}
}

void viperLaser::fire(float x, float y)
{
	tagBullet viperBull;
	viperBull.bulletImage = IMAGE->addImage("바이퍼레이저", "images/bullet/viperlaser.bmp", 168, 3, true);
	viperBull.x = x;
	viperBull.y = y;
	viperBull.hp = 5;
	viperBull.rc = RectMake(viperBull.x, viperBull.y, viperBull.bulletImage->getWidth() - 5, viperBull.bulletImage->getHeight() - 5);
	viperBull.speed = 20.0;
	viperBull.fire = true;
	viperBull.count = 0;
	viperBull.bulletDeath = false;
	viperBull.bulletDeathFrameX = 0;
	viperBull.afterExpolsion = false;
	_vBullet.push_back(viperBull);
}

void viperLaser::move()
{

	//총알이동
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		//알파값 넣을래?
		
		//죽엇는지부터 체크
		if (_viBullet->hp <= 0) {
			_viBullet->bulletDeath = true;
		}
		//죽지않은총알만 이동
		if (_viBullet->bulletDeath) continue;
		_viBullet->x += _viBullet->speed;
		_viBullet->rc = RectMake(_viBullet->x, _viBullet->y, _viBullet->bulletImage->getWidth(), _viBullet->bulletImage->getHeight());
	}
	//총알 삭제
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); )
	{
		if (_viBullet->x > WINSIZEX + 100 || _viBullet->afterExpolsion) {
			_viBullet = _vBullet.erase(_viBullet);
		}
		else {
			++_viBullet;
		}
	}
}