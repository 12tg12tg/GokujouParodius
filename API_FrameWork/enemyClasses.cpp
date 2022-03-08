#include "framework.h"
#include "enemyClasses.h"
#include "player.h"
#include "bell.h"
#include "powerUp.h"
/*
=================================================
	Find monster class ctrl+F4 ("name!")
=================================================
	monstername			imagename
1.	eChickin		/		치킨
2.	eChick			/		병아리
3.	eHead1			/		머리1
4.	eHead2			/		머리2
5.	eHead3			/		머리3
6.	eHead4			/		머리4
7.	eHead5			/		머리5
8.	ePenguin		/		펭귄
*/
//////////////////////////////////////////////////////////////
//////////////////////eChikin! 치킨!//////////////////////////
//////////////////////////////////////////////////////////////
eChickin::eChickin()
{
}

eChickin::~eChickin()
{
}

HRESULT eChickin::init(float x, float y)
{
	tagEnemy chickin;
	chickin.imageE = IMAGE->addFrameImage("치킨", "images/enemy/chicken.bmp", 96, 48, 2, 1, true);
	chickin.x = x;//WINSIZEX-100;
	chickin.y = y;// 200;
	chickin.speed = 6;
	chickin.rcE = RectMake(chickin.x, chickin.y, chickin.imageE->getFrameWidth(), chickin.imageE->getFrameHeight());
	chickin.hpE = 1;
	chickin.count = 0;
	chickin.isDeathE = false;
	chickin.afterExplosion = false;
	chickin.deathcount = 0;
	chickin.deathFrame = 0;
	chickin.framecount = 0;
	chickin.framex = 0;
	chickin.goUp = false;
	_vEnemy.push_back(chickin);

	return S_OK;
}

void eChickin::release()
{
}

void eChickin::update(player* py, bell* bl, powerUp* pu)
{
	//벡터내에서 모든 요소가 해야할 것.
	int index = 0;
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		//몬스터의 패턴을 카운트별로 설정.
		_viEnemy->count++;
		if (_viEnemy->count < 50) {
			_viEnemy->x -= _viEnemy->speed;
		}
		//30카운트동안 멈춰서 유저방향확인
		else if (_viEnemy->count < 80) {			
			if (_viEnemy->y > py->getY()){
				_viEnemy->goUp = true;
			}
			else {
				_viEnemy->goUp = false;
			}
		}
		//110카운트에 또확인
		else if(_viEnemy->count == 85){
			if (_viEnemy->y > py->getY()) {
				_viEnemy->goUp = true;
			}
			else {
				_viEnemy->goUp = false;
			}
		}
		//140카운트에 또 확인
		else if (_viEnemy->count == 115) {
			if (_viEnemy->y > py->getY()) {
				_viEnemy->goUp = true;
			}
			else {
				_viEnemy->goUp = false;
			}
		}
		//170카운트에 또 확인
		else if (_viEnemy->count == 145) {
			if (_viEnemy->y > py->getY()) {
				_viEnemy->goUp = true;
			}
			else {
				_viEnemy->goUp = false;
			}
		}
		//나머지구간은 이동할뿐
		else {
			if (_viEnemy->goUp) {
				_viEnemy->x -= _viEnemy->speed;
				_viEnemy->y -= _viEnemy->speed/2;
			}
			else {
				_viEnemy->x -= _viEnemy->speed;;
				_viEnemy->y += _viEnemy->speed / 2;
			}
		}
		_viEnemy->rcE = RectMake(_viEnemy->x, _viEnemy->y, _viEnemy->imageE->getFrameWidth(), _viEnemy->imageE->getFrameHeight());	
		//프레임설정
		index++;
		_viEnemy->framecount++;
		int currentFrame = _viEnemy->framex;
		if (_viEnemy->framecount % 10 == 0) {
			_viEnemy->framecount = 0;
			currentFrame++;
			if (currentFrame > _viEnemy->imageE->getMaxFrameX()) {
				currentFrame = 0;
			}
			_viEnemy->framex = currentFrame;
		}
		//피격당했는지
		auto vBullet = py->getBullet1()->getviperBullet();
		auto viBullet = vBullet->begin();
		for (viBullet; viBullet != vBullet->end(); )
		{
			RECT temp;
			if (!viBullet->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet->rc), &(_viEnemy->rcE))) {
				viBullet->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet;
			}
		}
		auto vBullet2 = py->getBullet2()->getviperDropMissile();
		auto viBullet2 = vBullet2->begin();
		for (viBullet2; viBullet2 != vBullet2->end(); )
		{
			RECT temp;
			if (!viBullet2->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet2->rc), &(_viEnemy->rcE))) {
				viBullet2->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet2;
			}
		}
		auto vBullet3 = py->getBullet3()->getviperDigonalBullet();
		auto viBullet3 = vBullet3->begin();
		for (viBullet3; viBullet3 != vBullet3->end(); )
		{
			RECT temp;
			if (!viBullet3->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet3->rc), &(_viEnemy->rcE))) {
				viBullet3->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet3;
			}
		}
		auto vBullet4 = py->getBullet4()->getviperLaser();
		auto viBullet4 = vBullet4->begin();
		for (viBullet4; viBullet4 != vBullet4->end(); )
		{
			RECT temp;
			if (viBullet4->hp > 0 && !viBullet4->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet4->rc), &(_viEnemy->rcE))) {
				viBullet4->hp--;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet4;
			}
		}
	}
	//벡터내에서 선택적 요소가 해야할 것.
	//몬스터 폭발이미지랜더링 이후 사라지는 구문.
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); )
	{
		if (_viEnemy->afterExplosion) 
		{
			if (RND->getInt(2) == 0)
				pu->init(_viEnemy->x, _viEnemy->y, 0);
			else if(RND->getInt(3)==0)
				bl->init(_viEnemy->x, _viEnemy->y);
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else {
			++_viEnemy;
		}
	}
	//범위밖이라 사라지는 구문.
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); )
	{
		if (_viEnemy->x + _viEnemy->imageE->getFrameWidth() < 0 ||
			_viEnemy->y > WINSIZEY ||
			_viEnemy->x > WINSIZEX+100 ||
			_viEnemy->y + _viEnemy->imageE->getFrameHeight() < 0)
		{
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else {
			++_viEnemy;
		}
	}
}

void eChickin::render()
{
	for (_viEnemy=_vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		//죽지 않았다면 계속 출력
		if (!_viEnemy->isDeathE) {
			if(_isDebug) Rectangle(getMemDC(), _viEnemy->rcE.left, _viEnemy->rcE.top, _viEnemy->rcE.right, _viEnemy->rcE.bottom);
			_viEnemy->imageE->frameRender(getMemDC(), _viEnemy->x, _viEnemy->y, _viEnemy->framex, 0);
		}
		//죽었다면 사망장면 출력
		else {
			_viEnemy->deathcount++;
			if (_viEnemy->deathcount % 3 == 0) {
				_viEnemy->deathcount = 0;
				_viEnemy->deathFrame++;
			}
			if (showExplosion(_viEnemy->x, _viEnemy->y, _viEnemy->deathFrame, 0, 1)) {
				_viEnemy->afterExplosion = true;
			}
		}
	}	
}
//////////////////////////////////////////////////////////////
//////////////////////eChick! 병아리!/////////////////////////
//////////////////////////////////////////////////////////////
eChick::eChick()
{
}

eChick::~eChick()
{
}

HRESULT eChick::init(float x, float y)
{
	tagEnemy chick;
	chick.imageE = IMAGE->addFrameImage("병아리", "images/enemy/chick.bmp", 90, 42, 2, 1, true);
	chick.x = x;
	chick.y = y;
	chick.speed = 4;
	chick.rcE = RectMake(chick.x, chick.y, chick.imageE->getFrameWidth(), chick.imageE->getFrameHeight());
	chick.hpE = 1;
	chick.count = 0;
	chick.isDeathE = false;
	chick.afterExplosion = false;
	chick.deathcount = 0;
	chick.deathFrame = 0;
	chick.framecount = 0;
	chick.framex = 0;
	chick.goUp = false;
	_vEnemy.push_back(chick);

	return S_OK;
}

void eChick::release()
{
}

void eChick::update(player* py, bell* bl, powerUp* pu)
{
	//벡터내에서 모든 요소가 해야할 것.
	int index = 0;
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		//몬스터의 패턴을 카운트별로 설정.
		_viEnemy->count++;
		if (_viEnemy->count < 60) {
			_viEnemy->x -= _viEnemy->speed;
		}
		//30카운트동안 멈춰서 유저방향확인
		else if (_viEnemy->count < 90) {
			if (_viEnemy->y > py->getY()) {
				_viEnemy->goUp = true;
			}
			else {
				_viEnemy->goUp = false;
			}
		}
		//120카운트에 또확인
		else if (_viEnemy->count == 150) {
			if (_viEnemy->y > py->getY()) {
				_viEnemy->goUp = true;
			}
			else {
				_viEnemy->goUp = false;
			}
		}
		//150카운트에 또 확인
		else if (_viEnemy->count == 190) {
			if (_viEnemy->y > py->getY()) {
				_viEnemy->goUp = true;
			}
			else {
				_viEnemy->goUp = false;
			}
		}
		//2200카운트에 또 확인
		else if (_viEnemy->count == 220) {
			if (_viEnemy->y > py->getY()) {
				_viEnemy->goUp = true;
			}
			else {
				_viEnemy->goUp = false;
			}
		}
		//나머지구간은 이동할뿐
		else {
			if (_viEnemy->goUp) {
				_viEnemy->x -= _viEnemy->speed;
				_viEnemy->y -= _viEnemy->speed/2;
			}
			else {
				_viEnemy->x -= _viEnemy->speed;
				_viEnemy->y += _viEnemy->speed/2;
			}
		}
		_viEnemy->rcE = RectMake(_viEnemy->x, _viEnemy->y, _viEnemy->imageE->getFrameWidth(), _viEnemy->imageE->getFrameHeight());
		//프레임설정
		index++;
		_viEnemy->framecount++;
		int currentFrame = _viEnemy->framex;
		if (_viEnemy->framecount % 10 == 0) {
			_viEnemy->framecount = 0;
			currentFrame++;
			if (currentFrame > _viEnemy->imageE->getMaxFrameX()) {
				currentFrame = 0;
			}
			_viEnemy->framex = currentFrame;
		}
		//피격당했는지
		auto vBullet = py->getBullet1()->getviperBullet();
		auto viBullet = vBullet->begin();
		for (viBullet; viBullet != vBullet->end(); )
		{
			RECT temp;
			if (!viBullet->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet->rc), &(_viEnemy->rcE))) {
				viBullet->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet;
			}
		}
		auto vBullet2 = py->getBullet2()->getviperDropMissile();
		auto viBullet2 = vBullet2->begin();
		for (viBullet2; viBullet2 != vBullet2->end(); )
		{
			RECT temp;
			if (!viBullet2->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet2->rc), &(_viEnemy->rcE))) {
				viBullet2->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet2;
			}
		}
		auto vBullet3 = py->getBullet3()->getviperDigonalBullet();
		auto viBullet3 = vBullet3->begin();
		for (viBullet3; viBullet3 != vBullet3->end(); )
		{
			RECT temp;
			if (!viBullet3->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet3->rc), &(_viEnemy->rcE))) {
				viBullet3->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet3;
			}
		}
		auto vBullet4 = py->getBullet4()->getviperLaser();
		auto viBullet4 = vBullet4->begin();
		for (viBullet4; viBullet4 != vBullet4->end(); )
		{
			RECT temp;
			if (viBullet4->hp > 0 && !viBullet4->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet4->rc), &(_viEnemy->rcE))) {
				viBullet4->hp--;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet4;
			}
		}
	}
	//벡터내에서 선택적 요소가 해야할 것.
	//몬스터 폭발이미지랜더링 이후 사라지는 구문.
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); )
	{
		if (_viEnemy->afterExplosion)
		{
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else {
			++_viEnemy;
		}
	}
	//범위밖이라 사라지는 구문.
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); )
	{
		if (_viEnemy->x + _viEnemy->imageE->getFrameWidth() < 0 ||
			_viEnemy->y > WINSIZEY ||
			_viEnemy->x > WINSIZEX + 100 ||
			_viEnemy->y + _viEnemy->imageE->getFrameHeight() < 0)
		{
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else {
			++_viEnemy;
		}
	}
}

void eChick::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		//죽지 않았다면 계속 출력
		if (!_viEnemy->isDeathE) {
			if(_isDebug)Rectangle(getMemDC(), _viEnemy->rcE.left, _viEnemy->rcE.top, _viEnemy->rcE.right, _viEnemy->rcE.bottom);
			_viEnemy->imageE->frameRender(getMemDC(), _viEnemy->x, _viEnemy->y, _viEnemy->framex, 0);
		}
		//죽었다면 사망장면 출력
		else {
			_viEnemy->deathcount++;
			if (_viEnemy->deathcount % 3 == 0) {
				_viEnemy->deathcount = 0;
				_viEnemy->deathFrame++;
			}
			if (showExplosion(_viEnemy->x, _viEnemy->y, _viEnemy->deathFrame, 0, 1)) {
				_viEnemy->afterExplosion = true;
			}
		}
	}
}
//////////////////////////////////////////////////////////////
//////////////////////eHead1! 머리1!//////////////////////////
//////////////////////////////////////////////////////////////

eHead1::eHead1()
{
}

eHead1::~eHead1()
{
}

HRESULT eHead1::init(float x, float y)
{
	tagEnemy head1;
	head1.imageE = IMAGE->addFrameImage("머리1", "images/enemy/head1.bmp", 270, 48, 6, 1, true);
	head1.x = x;
	head1.y = y;
	head1.speed = 6;
	head1.rcE = RectMake(head1.x, head1.y, head1.imageE->getFrameWidth(), head1.imageE->getFrameHeight());
	head1.hpE = 1;
	head1.count = 0;
	head1.isDeathE = false;
	head1.afterExplosion = false;
	head1.deathcount = 0;
	head1.deathFrame = 0;
	head1.framecount = 0;
	head1.framex = 0;
	head1.goUp = false;
	_vEnemy.push_back(head1);
	return S_OK;
}

void eHead1::release()
{
}

void eHead1::update(player* py, bell* bl, powerUp* pu)
{
	//벡터내에서 모든 요소가 해야할 것.
	int index = 0;
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		//몬스터의 패턴을 카운트별로 설정.
		_viEnemy->count++;
		if (_viEnemy->count < 150) {
			_viEnemy->x -= _viEnemy->speed;
		}
		else if(_viEnemy->count < 160){
			_viEnemy->targetY = py->getY();
		}
		else {
			_viEnemy->x += _viEnemy->speed-2;
			if (_viEnemy->y > _viEnemy->targetY) {
				_viEnemy->y -=2;
			}
			else if(_viEnemy->y < _viEnemy->targetY){
				_viEnemy->y+=2;
			}
			else {
			}
		}
		_viEnemy->rcE = RectMake(_viEnemy->x, _viEnemy->y, _viEnemy->imageE->getFrameWidth(), _viEnemy->imageE->getFrameHeight());
		//프레임설정
		index++;
		_viEnemy->framecount++;
		int currentFrame = _viEnemy->framex;
		if (_viEnemy->framecount % 10 == 0) {
			_viEnemy->framecount = 0;
			currentFrame++;
			if (currentFrame > _viEnemy->imageE->getMaxFrameX()) {
				currentFrame = 0;
			}
			_viEnemy->framex = currentFrame;
		}
		//피격당했는지
		auto vBullet = py->getBullet1()->getviperBullet();
		auto viBullet = vBullet->begin();
		for (viBullet; viBullet != vBullet->end(); )
		{
			RECT temp;
			if (!viBullet->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet->rc), &(_viEnemy->rcE))) {
				viBullet->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet;
			}
		}
		auto vBullet2 = py->getBullet2()->getviperDropMissile();
		auto viBullet2 = vBullet2->begin();
		for (viBullet2; viBullet2 != vBullet2->end(); )
		{
			RECT temp;
			if (!viBullet2->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet2->rc), &(_viEnemy->rcE))) {
				viBullet2->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet2;
			}
		}
		auto vBullet3 = py->getBullet3()->getviperDigonalBullet();
		auto viBullet3 = vBullet3->begin();
		for (viBullet3; viBullet3 != vBullet3->end(); )
		{
			RECT temp;
			if (!viBullet3->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet3->rc), &(_viEnemy->rcE))) {
				viBullet3->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet3;
			}
		}
		auto vBullet4 = py->getBullet4()->getviperLaser();
		auto viBullet4 = vBullet4->begin();
		for (viBullet4; viBullet4 != vBullet4->end(); )
		{
			RECT temp;
			if (viBullet4->hp > 0 && !viBullet4->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet4->rc), &(_viEnemy->rcE))) {
				viBullet4->hp--;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet4;
			}
		}
	}
	//벡터내에서 선택적 요소가 해야할 것.
	//몬스터 폭발이미지랜더링 이후 사라지는 구문.
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); )
	{
		if (_viEnemy->afterExplosion)
		{
			if (RND->getInt(12) < 2) {
				pu->init(_viEnemy->x, _viEnemy->y, 0);
			}
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else {
			++_viEnemy;
		}
	}
	//범위밖이라 사라지는 구문.
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); )
	{
		if (_viEnemy->x + _viEnemy->imageE->getFrameWidth() < 0 ||
			_viEnemy->y > WINSIZEY ||
			_viEnemy->x > WINSIZEX + 100 ||
			_viEnemy->y + _viEnemy->imageE->getFrameHeight() < 0)
		{
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else {
			++_viEnemy;
		}
	}
}

void eHead1::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		//죽지 않았다면 계속 출력
		if (!_viEnemy->isDeathE) {
			if(_isDebug) Rectangle(getMemDC(), _viEnemy->rcE.left, _viEnemy->rcE.top, _viEnemy->rcE.right, _viEnemy->rcE.bottom);
			_viEnemy->imageE->frameRender(getMemDC(), _viEnemy->x, _viEnemy->y, _viEnemy->framex, 0);
		}
		//죽었다면 사망장면 출력
		else {
			_viEnemy->deathcount++;
			if (_viEnemy->deathcount % 10 == 0) {
				_viEnemy->deathcount = 0;
				_viEnemy->deathFrame++;
			}
			if (showExplosion(_viEnemy->x, _viEnemy->y, _viEnemy->deathFrame, 0, 2)) {
				_viEnemy->afterExplosion = true;
			}
		}
	}
}
//////////////////////////////////////////////////////////////
//////////////////////eHead2! 머리2!//////////////////////////
//////////////////////////////////////////////////////////////
eHead2::eHead2()
{
}

eHead2::~eHead2()
{
}

HRESULT eHead2::init(float x, float y)
{
	tagEnemy head2;
	head2.imageE = IMAGE->addFrameImage("머리2", "images/enemy/head2.bmp", 252, 48, 6, 1, true);
	head2.x = x;
	head2.y = y;
	head2.speed = 6;
	head2.rcE = RectMake(head2.x, head2.y, head2.imageE->getFrameWidth(), head2.imageE->getFrameHeight());
	head2.hpE = 1;
	head2.count = 0;
	head2.isDeathE = false;
	head2.afterExplosion = false;
	head2.deathcount = 0;
	head2.deathFrame = 0;
	head2.framecount = 0;
	head2.framex = 0;
	head2.goUp = false;
	_vEnemy.push_back(head2);
	return S_OK;
}

void eHead2::release()
{
}

void eHead2::update(player* py, bell* bl, powerUp* pu)
{
	//벡터내에서 모든 요소가 해야할 것.
	int index = 0;
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		//몬스터의 패턴을 카운트별로 설정.
		_viEnemy->count++;
		if (_viEnemy->count < 150) {
			_viEnemy->x -= _viEnemy->speed;
		}
		else if (_viEnemy->count < 160) {
			_viEnemy->targetY = py->getY();
		}
		else {
			_viEnemy->x += _viEnemy->speed - 2;
			if (_viEnemy->y > _viEnemy->targetY) {
				_viEnemy->y -= 2;
			}
			else if (_viEnemy->y < _viEnemy->targetY) {
				_viEnemy->y += 2;
			}
			else {
			}
		}
		_viEnemy->rcE = RectMake(_viEnemy->x, _viEnemy->y, _viEnemy->imageE->getFrameWidth(), _viEnemy->imageE->getFrameHeight());
		//프레임설정
		index++;
		_viEnemy->framecount++;
		int currentFrame = _viEnemy->framex;
		if (_viEnemy->framecount % 10 == 0) {
			_viEnemy->framecount = 0;
			currentFrame++;
			if (currentFrame > _viEnemy->imageE->getMaxFrameX()) {
				currentFrame = 0;
			}
			_viEnemy->framex = currentFrame;
		}
		//피격당했는지
		auto vBullet = py->getBullet1()->getviperBullet();
		auto viBullet = vBullet->begin();
		for (viBullet; viBullet != vBullet->end(); )
		{
			RECT temp;
			if (!viBullet->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet->rc), &(_viEnemy->rcE))) {
				viBullet->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet;
			}
		}
		auto vBullet2 = py->getBullet2()->getviperDropMissile();
		auto viBullet2 = vBullet2->begin();
		for (viBullet2; viBullet2 != vBullet2->end(); )
		{
			RECT temp;
			if (!viBullet2->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet2->rc), &(_viEnemy->rcE))) {
				viBullet2->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet2;
			}
		}
		auto vBullet3 = py->getBullet3()->getviperDigonalBullet();
		auto viBullet3 = vBullet3->begin();
		for (viBullet3; viBullet3 != vBullet3->end(); )
		{
			RECT temp;
			if (!viBullet3->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet3->rc), &(_viEnemy->rcE))) {
				viBullet3->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet3;
			}
		}
		auto vBullet4 = py->getBullet4()->getviperLaser();
		auto viBullet4 = vBullet4->begin();
		for (viBullet4; viBullet4 != vBullet4->end(); )
		{
			RECT temp;
			if (viBullet4->hp > 0 && !viBullet4->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet4->rc), &(_viEnemy->rcE))) {
				viBullet4->hp--;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet4;
			}
		}
	}
	//벡터내에서 선택적 요소가 해야할 것.
	//몬스터 폭발이미지랜더링 이후 사라지는 구문.
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); )
	{
		if (_viEnemy->afterExplosion)
		{
			if (RND->getInt(12) < 2) {
				pu->init(_viEnemy->x, _viEnemy->y, 0);
			}
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else {
			++_viEnemy;
		}
	}
	//범위밖이라 사라지는 구문.
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); )
	{
		if (_viEnemy->x + _viEnemy->imageE->getFrameWidth() < 0 ||
			_viEnemy->y > WINSIZEY ||
			_viEnemy->x > WINSIZEX + 100 ||
			_viEnemy->y + _viEnemy->imageE->getFrameHeight() < 0)
		{
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else {
			++_viEnemy;
		}
	}
}

void eHead2::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		//죽지 않았다면 계속 출력
		if (!_viEnemy->isDeathE) {
			if (_isDebug) Rectangle(getMemDC(), _viEnemy->rcE.left, _viEnemy->rcE.top, _viEnemy->rcE.right, _viEnemy->rcE.bottom);
			_viEnemy->imageE->frameRender(getMemDC(), _viEnemy->x, _viEnemy->y, _viEnemy->framex, 0);
		}
		//죽었다면 사망장면 출력
		else {
			_viEnemy->deathcount++;
			if (_viEnemy->deathcount % 10 == 0) {
				_viEnemy->deathcount = 0;
				_viEnemy->deathFrame++;
			}
			if (showExplosion(_viEnemy->x, _viEnemy->y, _viEnemy->deathFrame, 0, 2)) {
				_viEnemy->afterExplosion = true;
			}
		}
	}
}
//////////////////////////////////////////////////////////////
//////////////////////eHead3! 머리3!//////////////////////////
//////////////////////////////////////////////////////////////
eHead3::eHead3()
{
}

eHead3::~eHead3()
{
}

HRESULT eHead3::init(float x, float y)
{
	tagEnemy head3;
	head3.imageE = IMAGE->addFrameImage("머리3", "images/enemy/head3.bmp", 270, 48, 6, 1, true);
	head3.x = x;
	head3.y = y;
	head3.speed = 6;
	head3.rcE = RectMake(head3.x, head3.y, head3.imageE->getFrameWidth(), head3.imageE->getFrameHeight());
	head3.hpE = 1;
	head3.count = 0;
	head3.isDeathE = false;
	head3.afterExplosion = false;
	head3.deathcount = 0;
	head3.deathFrame = 0;
	head3.framecount = 0;
	head3.framex = 0;
	head3.goUp = false;
	_vEnemy.push_back(head3);
	return S_OK;
}

void eHead3::release()
{
}

void eHead3::update(player* py, bell* bl, powerUp* pu)
{
	//벡터내에서 모든 요소가 해야할 것.
	int index = 0;
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		//몬스터의 패턴을 카운트별로 설정.
		_viEnemy->count++;
		if (_viEnemy->count < 150) {
			_viEnemy->x -= _viEnemy->speed;
		}
		else if (_viEnemy->count < 160) {
			_viEnemy->targetY = py->getY();
		}
		else {
			_viEnemy->x += _viEnemy->speed - 2;
			if (_viEnemy->y > _viEnemy->targetY) {
				_viEnemy->y -= 2;
			}
			else if (_viEnemy->y < _viEnemy->targetY) {
				_viEnemy->y += 2;
			}
			else {
			}
		}
		_viEnemy->rcE = RectMake(_viEnemy->x, _viEnemy->y, _viEnemy->imageE->getFrameWidth(), _viEnemy->imageE->getFrameHeight());
		//프레임설정
		index++;
		_viEnemy->framecount++;
		int currentFrame = _viEnemy->framex;
		if (_viEnemy->framecount % 10 == 0) {
			_viEnemy->framecount = 0;
			currentFrame++;
			if (currentFrame > _viEnemy->imageE->getMaxFrameX()) {
				currentFrame = 0;
			}
			_viEnemy->framex = currentFrame;
		}
		//피격당했는지
		auto vBullet = py->getBullet1()->getviperBullet();
		auto viBullet = vBullet->begin();
		for (viBullet; viBullet != vBullet->end(); )
		{
			RECT temp;
			if (!viBullet->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet->rc), &(_viEnemy->rcE))) {
				viBullet->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet;
			}
		}
		auto vBullet2 = py->getBullet2()->getviperDropMissile();
		auto viBullet2 = vBullet2->begin();
		for (viBullet2; viBullet2 != vBullet2->end(); )
		{
			RECT temp;
			if (!viBullet2->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet2->rc), &(_viEnemy->rcE))) {
				viBullet2->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet2;
			}
		}
		auto vBullet3 = py->getBullet3()->getviperDigonalBullet();
		auto viBullet3 = vBullet3->begin();
		for (viBullet3; viBullet3 != vBullet3->end(); )
		{
			RECT temp;
			if (!viBullet3->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet3->rc), &(_viEnemy->rcE))) {
				viBullet3->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet3;
			}
		}
		auto vBullet4 = py->getBullet4()->getviperLaser();
		auto viBullet4 = vBullet4->begin();
		for (viBullet4; viBullet4 != vBullet4->end(); )
		{
			RECT temp;
			if (viBullet4->hp > 0 && !viBullet4->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet4->rc), &(_viEnemy->rcE))) {
				viBullet4->hp--;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet4;
			}
		}
	}
	//벡터내에서 선택적 요소가 해야할 것.
	//몬스터 폭발이미지랜더링 이후 사라지는 구문.
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); )
	{
		if (_viEnemy->afterExplosion)
		{
			if (RND->getInt(12) < 2) {
				pu->init(_viEnemy->x, _viEnemy->y, 0);
			}
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else {
			++_viEnemy;
		}
	}
	//범위밖이라 사라지는 구문.
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); )
	{
		if (_viEnemy->x + _viEnemy->imageE->getFrameWidth() < 0 ||
			_viEnemy->y > WINSIZEY ||
			_viEnemy->x > WINSIZEX + 100 ||
			_viEnemy->y + _viEnemy->imageE->getFrameHeight() < 0)
		{
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else {
			++_viEnemy;
		}
	}
}

void eHead3::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		//죽지 않았다면 계속 출력
		if (!_viEnemy->isDeathE) {
			if (_isDebug) Rectangle(getMemDC(), _viEnemy->rcE.left, _viEnemy->rcE.top, _viEnemy->rcE.right, _viEnemy->rcE.bottom);
			_viEnemy->imageE->frameRender(getMemDC(), _viEnemy->x, _viEnemy->y, _viEnemy->framex, 0);
		}
		//죽었다면 사망장면 출력
		else {
			_viEnemy->deathcount++;
			if (_viEnemy->deathcount % 10 == 0) {
				_viEnemy->deathcount = 0;
				_viEnemy->deathFrame++;
			}
			if (showExplosion(_viEnemy->x, _viEnemy->y, _viEnemy->deathFrame, 0, 2)) {
				_viEnemy->afterExplosion = true;
			}
		}
	}
}
//////////////////////////////////////////////////////////////
//////////////////////eHead4! 머리4!//////////////////////////
//////////////////////////////////////////////////////////////
eHead4::eHead4()
{
}

eHead4::~eHead4()
{
}

HRESULT eHead4::init(float x, float y)
{
	tagEnemy head4;
	head4.imageE = IMAGE->addFrameImage("머리4", "images/enemy/head4.bmp", 252, 48, 6, 1, true);
	head4.x = x;
	head4.y = y;
	head4.speed = 6;
	head4.rcE = RectMake(head4.x, head4.y, head4.imageE->getFrameWidth(), head4.imageE->getFrameHeight());
	head4.hpE = 1;
	head4.count = 0;
	head4.isDeathE = false;
	head4.afterExplosion = false;
	head4.deathcount = 0;
	head4.deathFrame = 0;
	head4.framecount = 0;
	head4.framex = 0;
	head4.goUp = false;
	_vEnemy.push_back(head4);
	return S_OK;
}

void eHead4::release()
{
}

void eHead4::update(player* py, bell* bl, powerUp* pu)
{
	//벡터내에서 모든 요소가 해야할 것.
	int index = 0;
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		//몬스터의 패턴을 카운트별로 설정.
		_viEnemy->count++;
		if (_viEnemy->count < 150) {
			_viEnemy->x -= _viEnemy->speed;
		}
		else if (_viEnemy->count < 160) {
			_viEnemy->targetY = py->getY();
		}
		else {
			_viEnemy->x += _viEnemy->speed - 2;
			if (_viEnemy->y > _viEnemy->targetY) {
				_viEnemy->y -= 2;
			}
			else if (_viEnemy->y < _viEnemy->targetY) {
				_viEnemy->y += 2;
			}
			else {
			}
		}
		_viEnemy->rcE = RectMake(_viEnemy->x, _viEnemy->y, _viEnemy->imageE->getFrameWidth(), _viEnemy->imageE->getFrameHeight());
		//프레임설정
		index++;
		_viEnemy->framecount++;
		int currentFrame = _viEnemy->framex;
		if (_viEnemy->framecount % 10 == 0) {
			_viEnemy->framecount = 0;
			currentFrame++;
			if (currentFrame > _viEnemy->imageE->getMaxFrameX()) {
				currentFrame = 0;
			}
			_viEnemy->framex = currentFrame;
		}
		//피격당했는지
		auto vBullet = py->getBullet1()->getviperBullet();
		auto viBullet = vBullet->begin();
		for (viBullet; viBullet != vBullet->end(); )
		{
			RECT temp;
			if (!viBullet->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet->rc), &(_viEnemy->rcE))) {
				viBullet->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet;
			}
		}
		auto vBullet2 = py->getBullet2()->getviperDropMissile();
		auto viBullet2 = vBullet2->begin();
		for (viBullet2; viBullet2 != vBullet2->end(); )
		{
			RECT temp;
			if (!viBullet2->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet2->rc), &(_viEnemy->rcE))) {
				viBullet2->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet2;
			}
		}
		auto vBullet3 = py->getBullet3()->getviperDigonalBullet();
		auto viBullet3 = vBullet3->begin();
		for (viBullet3; viBullet3 != vBullet3->end(); )
		{
			RECT temp;
			if (!viBullet3->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet3->rc), &(_viEnemy->rcE))) {
				viBullet3->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet3;
			}
		}
		auto vBullet4 = py->getBullet4()->getviperLaser();
		auto viBullet4 = vBullet4->begin();
		for (viBullet4; viBullet4 != vBullet4->end(); )
		{
			RECT temp;
			if (viBullet4->hp > 0 && !viBullet4->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet4->rc), &(_viEnemy->rcE))) {
				viBullet4->hp--;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet4;
			}
		}

	}
	//벡터내에서 선택적 요소가 해야할 것.
	//몬스터 폭발이미지랜더링 이후 사라지는 구문.
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); )
	{
		if (_viEnemy->afterExplosion)
		{
			if (RND->getInt(12) < 2) {
				pu->init(_viEnemy->x, _viEnemy->y, 0);
			}
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else {
			++_viEnemy;
		}
	}
	//범위밖이라 사라지는 구문.
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); )
	{
		if (_viEnemy->x + _viEnemy->imageE->getFrameWidth() < 0 ||
			_viEnemy->y > WINSIZEY ||
			_viEnemy->x > WINSIZEX + 100 ||
			_viEnemy->y + _viEnemy->imageE->getFrameHeight() < 0)
		{
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else {
			++_viEnemy;
		}
	}
}

void eHead4::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		//죽지 않았다면 계속 출력
		if (!_viEnemy->isDeathE) {
			if (_isDebug) Rectangle(getMemDC(), _viEnemy->rcE.left, _viEnemy->rcE.top, _viEnemy->rcE.right, _viEnemy->rcE.bottom);
			_viEnemy->imageE->frameRender(getMemDC(), _viEnemy->x, _viEnemy->y, _viEnemy->framex, 0);
		}
		//죽었다면 사망장면 출력
		else {
			_viEnemy->deathcount++;
			if (_viEnemy->deathcount % 10 == 0) {
				_viEnemy->deathcount = 0;
				_viEnemy->deathFrame++;
			}
			if (showExplosion(_viEnemy->x, _viEnemy->y, _viEnemy->deathFrame, 0, 2)) {
				_viEnemy->afterExplosion = true;
			}
		}
	}
}
//////////////////////////////////////////////////////////////
//////////////////////eHead5! 머리5!//////////////////////////
//////////////////////////////////////////////////////////////

eHead5::eHead5()
{
}

eHead5::~eHead5()
{
}

HRESULT eHead5::init(float x, float y)
{
	tagEnemy head5;
	head5.imageE = IMAGE->addFrameImage("머리5", "images/enemy/head5.bmp", 270, 48, 6, 1, true);
	head5.x = x;
	head5.y = y;
	head5.speed = 6;
	head5.rcE = RectMake(head5.x, head5.y, head5.imageE->getFrameWidth(), head5.imageE->getFrameHeight());
	head5.hpE = 1;
	head5.count = 0;
	head5.isDeathE = false;
	head5.afterExplosion = false;
	head5.deathcount = 0;
	head5.deathFrame = 0;
	head5.framecount = 0;
	head5.framex = 0;
	head5.goUp = false;
	_vEnemy.push_back(head5);
	return S_OK;
}

void eHead5::release()
{
}

void eHead5::update(player* py, bell* bl, powerUp* pu)
{
	//벡터내에서 모든 요소가 해야할 것.
	int index = 0;
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		//몬스터의 패턴을 카운트별로 설정.
		_viEnemy->count++;
		if (_viEnemy->count < 150) {
			_viEnemy->x -= _viEnemy->speed;
		}
		else if (_viEnemy->count < 160) {
			_viEnemy->targetY = py->getY();
		}
		else {
			_viEnemy->x += _viEnemy->speed - 2;
			if (_viEnemy->y > _viEnemy->targetY) {
				_viEnemy->y -= 2;
			}
			else if (_viEnemy->y < _viEnemy->targetY) {
				_viEnemy->y += 2;
			}
			else {
			}
		}
		_viEnemy->rcE = RectMake(_viEnemy->x, _viEnemy->y, _viEnemy->imageE->getFrameWidth(), _viEnemy->imageE->getFrameHeight());
		//프레임설정
		index++;
		_viEnemy->framecount++;
		int currentFrame = _viEnemy->framex;
		if (_viEnemy->framecount % 10 == 0) {
			_viEnemy->framecount = 0;
			currentFrame++;
			if (currentFrame > _viEnemy->imageE->getMaxFrameX()) {
				currentFrame = 0;
			}
			_viEnemy->framex = currentFrame;
		}
		//피격당했는지
		auto vBullet = py->getBullet1()->getviperBullet();
		auto viBullet = vBullet->begin();
		for (viBullet; viBullet != vBullet->end(); )
		{
			RECT temp;
			if (!viBullet->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet->rc), &(_viEnemy->rcE))) {
				viBullet->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet;
			}
		}
		auto vBullet2 = py->getBullet2()->getviperDropMissile();
		auto viBullet2 = vBullet2->begin();
		for (viBullet2; viBullet2 != vBullet2->end(); )
		{
			RECT temp;
			if (!viBullet2->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet2->rc), &(_viEnemy->rcE))) {
				viBullet2->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet2;
			}
		}
		auto vBullet3 = py->getBullet3()->getviperDigonalBullet();
		auto viBullet3 = vBullet3->begin();
		for (viBullet3; viBullet3 != vBullet3->end(); )
		{
			RECT temp;
			if (!viBullet3->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet3->rc), &(_viEnemy->rcE))) {
				viBullet3->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet3;
			}
		}
		auto vBullet4 = py->getBullet4()->getviperLaser();
		auto viBullet4 = vBullet4->begin();
		for (viBullet4; viBullet4 != vBullet4->end(); )
		{
			RECT temp;
			if (viBullet4->hp > 0 && !viBullet4->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet4->rc), &(_viEnemy->rcE))) {
				viBullet4->hp--;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet4;
			}
		}
	}
	//벡터내에서 선택적 요소가 해야할 것.
	//몬스터 폭발이미지랜더링 이후 사라지는 구문.
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); )
	{
		if (_viEnemy->afterExplosion)
		{
			if (RND->getInt(12) < 2) {
				pu->init(_viEnemy->x, _viEnemy->y, 0);
			}
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else {
			++_viEnemy;
		}
	}
	//범위밖이라 사라지는 구문.
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); )
	{
		if (_viEnemy->x + _viEnemy->imageE->getFrameWidth() < 0 ||
			_viEnemy->y > WINSIZEY ||
			_viEnemy->x > WINSIZEX + 100 ||
			_viEnemy->y + _viEnemy->imageE->getFrameHeight() < 0)
		{
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else {
			++_viEnemy;
		}
	}
}

void eHead5::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		//죽지 않았다면 계속 출력
		if (!_viEnemy->isDeathE) {
			if (_isDebug) Rectangle(getMemDC(), _viEnemy->rcE.left, _viEnemy->rcE.top, _viEnemy->rcE.right, _viEnemy->rcE.bottom);
			_viEnemy->imageE->frameRender(getMemDC(), _viEnemy->x, _viEnemy->y, _viEnemy->framex, 0);
		}
		//죽었다면 사망장면 출력
		else {
			_viEnemy->deathcount++;
			if (_viEnemy->deathcount % 10 == 0) {
				_viEnemy->deathcount = 0;
				_viEnemy->deathFrame++;
			}
			if (showExplosion(_viEnemy->x, _viEnemy->y, _viEnemy->deathFrame, 0, 2)) {
				_viEnemy->afterExplosion = true;
			}
		}
	}
}
//////////////////////////////////////////////////////////////
//////////////////////ePenguin! 펭귄!//////////////////////////
//////////////////////////////////////////////////////////////
ePenguin::ePenguin()
{
}

ePenguin::~ePenguin()
{
}

HRESULT ePenguin::init(float x, float y, int patternNum)
{
	tagEnemy penguin;
	penguin.imageE = IMAGE->addFrameImage("펭귄", "images/enemy/penguin.bmp", 240, 69, 5, 1, true);
	penguin.x = x;
	penguin.y = y;
	penguin.speed = 4.0f;
	penguin.rcE = RectMake(penguin.x, penguin.y, penguin.imageE->getFrameWidth(), penguin.imageE->getFrameHeight());
	penguin.hpE = 1;
	penguin.count = 0;
	penguin.isDeathE = false;
	penguin.afterExplosion = false;
	penguin.deathcount = 0;
	penguin.deathFrame = 0;
	penguin.framecount = 0;
	penguin.framex = 0;
	penguin.goUp = false;
	penguin.patternNum = patternNum;
	if (patternNum == 1) {
		penguin.angle = PI2 - PI / 3;
	}
	else if (patternNum == 2) {
		penguin.angle = PI + PI / 3;
	}
	else {
		penguin.angle = PI + PI / 3;
	}
	_vEnemy.push_back(penguin);
	return S_OK;
}

void ePenguin::release()
{
}

void ePenguin::update(player* py, bell* bl, powerUp* pu)
{
	//벡터내에서 모든 요소가 해야할 것.
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		_viEnemy->count++;
		//몬스터의 패턴을 카운트별로 설정.
		if (_viEnemy->patternNum == 1)
		{
			pattern1(_viEnemy);
		}
		else if (_viEnemy->patternNum == 2) {
			pattern2(_viEnemy);
		}
		else {
			pattern3(_viEnemy);
		}
		_viEnemy->rcE = RectMake(_viEnemy->x, _viEnemy->y, _viEnemy->imageE->getFrameWidth(), _viEnemy->imageE->getFrameHeight());
		//프레임설정
		_viEnemy->framecount++;
		int currentFrame = _viEnemy->framex;
		if (_viEnemy->framecount % 10 == 0) {
			_viEnemy->framecount = 0;
			currentFrame++;
			if (currentFrame > _viEnemy->imageE->getMaxFrameX()) {
				currentFrame = 0;
			}
			_viEnemy->framex = currentFrame;
		}
		//피격당했는지
		auto vBullet = py->getBullet1()->getviperBullet();
		auto viBullet = vBullet->begin();
		for (viBullet; viBullet != vBullet->end(); )
		{
			RECT temp;
			if (!viBullet->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet->rc), &(_viEnemy->rcE))) {
				viBullet->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet;
			}
		}
		auto vBullet2 = py->getBullet2()->getviperDropMissile();
		auto viBullet2 = vBullet2->begin();
		for (viBullet2; viBullet2 != vBullet2->end(); )
		{
			RECT temp;
			if (!viBullet2->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet2->rc), &(_viEnemy->rcE))) {
				viBullet2->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet2;
			}
		}
		auto vBullet3 = py->getBullet3()->getviperDigonalBullet();
		auto viBullet3 = vBullet3->begin();
		for (viBullet3; viBullet3 != vBullet3->end(); )
		{
			RECT temp;
			if (!viBullet3->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet3->rc), &(_viEnemy->rcE))) {
				viBullet3->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet3;
			}
		}
		auto vBullet4 = py->getBullet4()->getviperLaser();
		auto viBullet4 = vBullet4->begin();
		for (viBullet4; viBullet4 != vBullet4->end(); )
		{
			RECT temp;
			if (viBullet4->hp > 0 && !viBullet4->bulletDeath && !_viEnemy->isDeathE && IntersectRect(&temp, &(viBullet4->rc), &(_viEnemy->rcE))) {
				viBullet4->hp--;
				//viBullet = vBullet->erase(viBullet);
				_viEnemy->hpE--;
				if (_viEnemy->hpE <= 0) {
					_viEnemy->isDeathE = true;
				}
			}
			else {
				++viBullet4;
			}
		}
	}
	//벡터내에서 선택적 요소가 해야할 것.
	//몬스터 폭발이미지랜더링 이후 사라지는 구문.
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); )
	{
		if (_viEnemy->afterExplosion)
		{
			if (RND->getInt(10) < 2) {
				pu->init(_viEnemy->x, _viEnemy->y, 0);
			}
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else {
			++_viEnemy;
		}
	}
	//범위밖이라 사라지는 구문.
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); )
	{
		if (_viEnemy->count < 100) { //회전 안갇히게 카운트100이상부터적용.
			++_viEnemy; 
			continue; 
		}						
		if (_viEnemy->x + _viEnemy->imageE->getFrameWidth() < 0 ||
			_viEnemy->y > WINSIZEY ||
			_viEnemy->x > WINSIZEX + 100 ||
			_viEnemy->y + _viEnemy->imageE->getFrameHeight() < 0)
		{
			_viEnemy = _vEnemy.erase(_viEnemy);
		}
		else {
			++_viEnemy;
		}
	}
}

void ePenguin::render()
{
	for (_viEnemy = _vEnemy.begin(); _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		//죽지 않았다면 계속 출력
		if (!_viEnemy->isDeathE) {
			if (_isDebug) Rectangle(getMemDC(), _viEnemy->rcE.left, _viEnemy->rcE.top, _viEnemy->rcE.right, _viEnemy->rcE.bottom);
			_viEnemy->imageE->frameRender(getMemDC(), _viEnemy->x, _viEnemy->y, _viEnemy->framex, 0);
		}
		//죽었다면 사망장면 출력
		else {
			_viEnemy->deathcount++;
			if (_viEnemy->deathcount % 5 == 0) {
				_viEnemy->deathcount = 0;
				_viEnemy->deathFrame++;
			}
			if (showExplosion(_viEnemy->x, _viEnemy->y, _viEnemy->deathFrame, 0, 1)) {
				_viEnemy->afterExplosion = true;
			}
		}
	}
}

void ePenguin::pattern1(vector<tagEnemy>::iterator iter)
{
 	iter->x = iter->x + cosf(iter->angle) * iter->speed;
	iter->y = iter->y - sinf(iter->angle) * iter->speed;
}

void ePenguin::pattern2(vector<tagEnemy>::iterator iter)
{
	iter->x = iter->x + cosf(iter->angle) * iter->speed;
	iter->y = iter->y - sinf(iter->angle) * iter->speed;
}

void ePenguin::pattern3(vector<tagEnemy>::iterator iter)
{
	iter->x = iter->x + cosf(iter->angle) * iter->speed;
	iter->y = iter->y - sinf(iter->angle) * iter->speed;
	if (iter->count > 50) {
		if (iter->x < 0) {
			iter->angle = PI - iter->angle;
		}
		else if (iter->x + iter->imageE->getFrameWidth() > WINSIZEX) {
			iter->angle = PI - iter->angle;
		}
		if (iter->y < 0)
		{
			iter->angle = PI2 - iter->angle;
		}
		else if (iter->y + iter->imageE->getFrameHeight() > WINSIZEY - 80) {
			iter->angle = PI2 - iter->angle;
		}
	}
}
