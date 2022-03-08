#include "framework.h"
#include "objectClasses.h"
#include "player.h"
#include "bell.h"
#include "powerUp.h"
/*
=================================================
	Find monster class ctrl+F4 ("name!")
=================================================
	monstername			imagename
1.	oEagle1			/		독수리1
2.	oEagle2			/		독수리2
3.	oclaw			/		뽑기머신
4.			/		
5.			/		
6.			/		
7.			/		
*/
//////////////////////////////////////////////////////////////
//////////////////////oEagle1! 독수리1!//////////////////////////
//////////////////////////////////////////////////////////////
oEagle1::oEagle1()
{
	_ebul = new eagle1Bullet;
}

oEagle1::~oEagle1()
{
}

HRESULT oEagle1::init(float x, float y)
{
	tagEagle1 eagle1;
	eagle1.objectInfo.image = IMAGE->addFrameImage("독수리1", "images/enemy/eagle1_body.bmp", 564, 135, 4, 1, true);
	eagle1.objectInfo.x = x;
	eagle1.objectInfo.y = y;
	eagle1.objectInfo.speed = 4;
	eagle1.objectInfo.rc = RectMake(eagle1.objectInfo.x+24, eagle1.objectInfo.y+3, 
		eagle1.objectInfo.image->getFrameWidth()-48, eagle1.objectInfo.image->getFrameHeight()-6);
	eagle1.objectInfo.hp = 10;
	eagle1.objectInfo.movecount = 0;
	eagle1.objectInfo.isDeath = false;
	eagle1.objectInfo.isHit = false;
	eagle1.objectInfo.isinvincible = false;
	eagle1.objectInfo.isinvincibleCount = 0;
	eagle1.objectInfo.afterExplosion = false;
	eagle1.objectInfo.deathcount = 0;
	eagle1.objectInfo.deathFrame = 0;
	eagle1.objectInfo.framecount = 0;
	eagle1.objectInfo.frameX = 0;
	
	eagle1.faceImg = IMAGE->addFrameImage("독수리얼굴", "images/enemy/eagle_face.bmp", 117, 39, 3, 1, true);
	eagle1.faceFrameX = 0;
	eagle1.topImg = IMAGE->addFrameImage("독수리모자", "images / enemy / eagle_top.bmp", 60, 39, 2, 1, true);
	eagle1.topFrameX = 0;
	eagle1.state = EAGLESTATE::NORMAL;
	eagle1.isUp = false;
	eagle1.updownspeed = 3;
	eagle1.attackcount = 0;
	_vObject.push_back(eagle1);

	return S_OK;
}

void oEagle1::release()
{
	SAFE_DELETE(_ebul);
}

void oEagle1::update(player* py, bell* bl, powerUp* pu)
{
	//벡터내에서 모든 요소가 해야할 것.
	for (_viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject)
	{
		move(*_viObject);
		//몬스터의 패턴을 카운트별로 설정.
		_viObject->objectInfo.movecount++;
		if (_viObject->objectInfo.movecount < 50) {

			_viObject->objectInfo.x -= _viObject->objectInfo.speed;
		}
		else if (_viObject->objectInfo.movecount == 70) {
			attack(*_viObject);
		}
		else if (_viObject->objectInfo.movecount > 150) {
			_viObject->objectInfo.x -= _viObject->objectInfo.speed;
		}
		_viObject->objectInfo.rc = RectMake(_viObject->objectInfo.x + 24, _viObject->objectInfo.y + 6,
			_viObject->objectInfo.image->getFrameWidth() - 48, _viObject->objectInfo.image->getFrameHeight() - 12);
		//프레임설정
		_viObject->objectInfo.framecount++;
		int currentFrame = _viObject->objectInfo.frameX;
		if (_viObject->objectInfo.framecount % 10 == 0) {
			_viObject->objectInfo.framecount = 0;
			currentFrame++;
			if (currentFrame > _viObject->objectInfo.image->getMaxFrameX()) {
				currentFrame = 0;
			}
			_viObject->objectInfo.frameX = currentFrame;
		}
		if (_viObject->state == EAGLESTATE::NORMAL) {
			_viObject->faceFrameX = (int)EAGLESTATE::NORMAL;
		}
		else if (_viObject->state == EAGLESTATE::BEATTACKED) {
			_viObject->faceFrameX = (int)EAGLESTATE::BEATTACKED;
		}
		else if (_viObject->state == EAGLESTATE::DOATTACK) {
			_viObject->faceFrameX = (int)EAGLESTATE::DOATTACK;
		}
		//피격당했는지
		auto vBullet = py->getBullet1()->getviperBullet();
		auto viBullet = vBullet->begin();
		for (viBullet; viBullet != vBullet->end(); )
		{
			RECT temp;
			if (!viBullet->bulletDeath && !_viObject->objectInfo.isDeath && IntersectRect(&temp, &(viBullet->rc), &(_viObject->objectInfo.rc))) {
				viBullet->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				if (!_viObject->objectInfo.isinvincible) {
					_viObject->objectInfo.isHit = true;
					_viObject->objectInfo.hp--;
				}
				if (_viObject->objectInfo.hp <= 0) {
					_viObject->objectInfo.isDeath = true;
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
			if (!viBullet2->bulletDeath && !_viObject->objectInfo.isDeath && IntersectRect(&temp, &(viBullet2->rc), &(_viObject->objectInfo.rc))) {
				viBullet2->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				if (!_viObject->objectInfo.isinvincible) {
					_viObject->objectInfo.isHit = true;
					_viObject->objectInfo.hp--;
				}
				if (_viObject->objectInfo.hp <= 0) {
					_viObject->objectInfo.isDeath = true;
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
			if (!viBullet3->bulletDeath && !_viObject->objectInfo.isDeath && IntersectRect(&temp, &(viBullet3->rc), &(_viObject->objectInfo.rc))) {
				viBullet3->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				if (!_viObject->objectInfo.isinvincible) {
					_viObject->objectInfo.isHit = true;
					_viObject->objectInfo.hp--;
				}
				if (_viObject->objectInfo.hp <= 0) {
					_viObject->objectInfo.isDeath = true;
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
			if (viBullet4->hp >0 && !viBullet4->bulletDeath && !_viObject->objectInfo.isDeath && IntersectRect(&temp, &(viBullet4->rc), &(_viObject->objectInfo.rc))) {
				viBullet4->hp--;
				//viBullet = vBullet->erase(viBullet);
				if (!_viObject->objectInfo.isinvincible) {
					_viObject->objectInfo.isHit = true;
					_viObject->objectInfo.hp--;
				}
				if (_viObject->objectInfo.hp <= 0) {
					_viObject->objectInfo.isDeath = true;
				}
			}
			else {
				++viBullet4;
			}
		}
	}
	//벡터내에서 선택적 요소가 해야할 것.
	//몬스터 폭발이미지랜더링 이후 사라지는 구문.
	for (_viObject = _vObject.begin(); _viObject != _vObject.end(); )
	{
		if (_viObject->objectInfo.afterExplosion)
		{
			pu->init(_viObject->objectInfo.x, _viObject->objectInfo.y, 0, true);
			_viObject = _vObject.erase(_viObject);
		}
		else {
			++_viObject;
		}
	}
	//범위밖이라 사라지는 구문.
	for (_viObject = _vObject.begin(); _viObject != _vObject.end(); )
	{
		if (_viObject->objectInfo.x + _viObject->objectInfo.image->getFrameWidth() < 0 ||
			_viObject->objectInfo.y > WINSIZEY ||
			_viObject->objectInfo.x > WINSIZEX + 100 ||
			_viObject->objectInfo.y + _viObject->objectInfo.image->getFrameHeight() < 0)
		{
			_viObject = _vObject.erase(_viObject);
		}
		else {
			++_viObject;
		}
	}
	if(_ebul!=nullptr) _ebul->update();
	//checkCollisionToPlayer(py);
}

void oEagle1::render()
{
	if (_ebul != nullptr) _ebul->render();
	for (_viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject)
	{
		//죽지 않았다면 계속 출력
		if (!_viObject->objectInfo.isDeath) {
			if (_isDebug) Rectangle(getMemDC(), _viObject->objectInfo.rc.left, _viObject->objectInfo.rc.top, 
				_viObject->objectInfo.rc.right, _viObject->objectInfo.rc.bottom);
			_viObject->objectInfo.image->frameRender(getMemDC(), _viObject->objectInfo.x, _viObject->objectInfo.y, _viObject->objectInfo.frameX, 0);
		
			_viObject->faceImg->frameRender(getMemDC(),
				_viObject->objectInfo.x+15, _viObject->objectInfo.y+48, _viObject->faceFrameX, 0);
		
		}
		//죽었다면 사망장면 출력
		else {
			_viObject->objectInfo.deathcount++;
			if (_viObject->objectInfo.deathcount % 3 == 0) {
				_viObject->objectInfo.deathcount = 0;
				_viObject->objectInfo.deathFrame++;
			}
			if (showExplosion(_viObject->objectInfo.x, _viObject->objectInfo.y, _viObject->objectInfo.deathFrame, 0, 1)) {
				_viObject->objectInfo.afterExplosion = true;
			}
		}
	}
}

void oEagle1::attack(tagEagle1& eagle)
{
	eagle.state = EAGLESTATE::DOATTACK;
	_ebul->fire(eagle.objectInfo.x+eagle.objectInfo.image->getFrameWidth()/2,
		eagle.objectInfo.y+ eagle.objectInfo.image->getFrameHeight() / 2);
}

void oEagle1::move(tagEagle1& eagle)
{
	//위아래이동조건
	if (!eagle.objectInfo.isinvincible) {
		if (eagle.isUp) {
			eagle.objectInfo.y -= eagle.updownspeed;
			eagle.updownspeed-=0.1;
			if (eagle.updownspeed <= 0) {
				eagle.isUp = false;
				eagle.updownspeed = 3;
			}
		}
		else {
			eagle.objectInfo.y += eagle.updownspeed;
			eagle.updownspeed-=0.1;
			if (eagle.updownspeed <= 0) {
				eagle.isUp = true;
				eagle.updownspeed = 3;
			}
		}
	}
	//피격받았을때 무적상태진입 (공격중이라면 다씹고 무빙할거임)
	if(eagle.objectInfo.isHit && eagle.state != EAGLESTATE::DOATTACK) {
		eagle.objectInfo.isHit = false;
		eagle.objectInfo.isinvincible = true;
	}
	//무적상태라면 이동안하고 표정 바꿈. 5카운트 후 원상태로 돌아옴.
	if (eagle.objectInfo.isinvincible && eagle.state != EAGLESTATE::DOATTACK) {
		eagle.objectInfo.isinvincibleCount++;
		eagle.state = EAGLESTATE::BEATTACKED;
		if (eagle.objectInfo.isinvincibleCount % 5 == 0) {
			eagle.objectInfo.isinvincibleCount = 0;
			eagle.objectInfo.isinvincible = false;
			eagle.state = EAGLESTATE::NORMAL;
		}
	}
	//공격중이라면 표정바꾸고 공격마치면 모든것을 원래상태로
	if (eagle.state == EAGLESTATE::DOATTACK)
	{
		eagle.attackcount++;
		if (eagle.attackcount % 80 == 0) {
			eagle.state = EAGLESTATE::NORMAL;
			eagle.objectInfo.isinvincibleCount = 0;
			eagle.objectInfo.isinvincible = false;
			eagle.objectInfo.isHit = false;
		}
	}
}

void oEagle1::changeStateInvinOrNormal(vector<tagEagle1>::iterator iter)
{
	if (!iter->objectInfo.isinvincible) {
		iter->objectInfo.hp--;
		iter->objectInfo.isHit = true;
	}	
	if (iter->objectInfo.hp <= 0) {
		iter->objectInfo.isDeath = true;
	}
}
//////////////////////////////////////////////////////////////
//////////////////////oEagle2! 독수리2!//////////////////////////
//////////////////////////////////////////////////////////////

oEagle2::oEagle2()
{
	_ebul = new eagle2Bullet;
}

oEagle2::~oEagle2(){}

HRESULT oEagle2::init(float x, float y)
{
	tagEagle2 eagle2;
	eagle2.objectInfo.image = IMAGE->addFrameImage("독수리2", "images/enemy/eagle2_body.bmp", 564, 135, 4, 1, true);
	eagle2.objectInfo.x = x;
	eagle2.objectInfo.y = y;
	eagle2.objectInfo.speed = 4;
	eagle2.objectInfo.rc = RectMake(eagle2.objectInfo.x + 24, eagle2.objectInfo.y + 3,
		eagle2.objectInfo.image->getFrameWidth() - 48, eagle2.objectInfo.image->getFrameHeight() - 6);
	eagle2.objectInfo.hp = 10;
	eagle2.objectInfo.movecount = 0;
	eagle2.objectInfo.isDeath = false;
	eagle2.objectInfo.isHit = false;
	eagle2.objectInfo.isinvincible = false;
	eagle2.objectInfo.isinvincibleCount = 0;
	eagle2.objectInfo.afterExplosion = false;
	eagle2.objectInfo.deathcount = 0;
	eagle2.objectInfo.deathFrame = 0;
	eagle2.objectInfo.framecount = 0;
	eagle2.objectInfo.frameX = 0;

	eagle2.faceImg = IMAGE->addFrameImage("독수리얼굴", "images/enemy/eagle_face.bmp", 117, 39, 3, 1, true);
	eagle2.faceFrameX = 0;
	eagle2.topImg = IMAGE->addFrameImage("독수리모자", "images/enemy/eagle_top.bmp", 60, 39, 2, 1, true);
	eagle2.topFrameX = 0;
	eagle2.topframeCount = 0;
	eagle2.state = EAGLESTATE::NORMAL;
	eagle2.isUp = false;
	eagle2.updownspeed = 3;
	eagle2.attackcount = 0;
	eagle2.attackNum = 0;
	eagle2.shootY = -1;
	_vObject.push_back(eagle2);

	return S_OK;
}

void oEagle2::release()
{
	SAFE_DELETE(_ebul);
}

void oEagle2::update(player* py, bell* bl, powerUp* pu)
{
	//벡터내에서 모든 요소가 해야할 것.
	for (_viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject)
	{
		move(*_viObject);
		//몬스터의 패턴을 카운트별로 설정.
		_viObject->objectInfo.movecount++;
		if (_viObject->objectInfo.movecount < 50) {
			_viObject->objectInfo.x -= _viObject->objectInfo.speed;
		}
		else if (_viObject->objectInfo.movecount == 70||
			_viObject->objectInfo.movecount == 80||
			_viObject->objectInfo.movecount == 90) 
		{
			attack(*_viObject);
		}
		else if (_viObject->objectInfo.movecount > 150) {
			_viObject->objectInfo.x -= _viObject->objectInfo.speed;
		}
		_viObject->objectInfo.rc = RectMake(_viObject->objectInfo.x + 24, _viObject->objectInfo.y + 6,
			_viObject->objectInfo.image->getFrameWidth() - 48, _viObject->objectInfo.image->getFrameHeight() - 12);
		//프레임설정(몸짓, 표지판, 표정 순서)
		_viObject->objectInfo.framecount++;
		int currentFrame = _viObject->objectInfo.frameX;
		if (_viObject->objectInfo.framecount % 10 == 0) {
			_viObject->objectInfo.framecount = 0;
			currentFrame++;
			if (currentFrame > _viObject->objectInfo.image->getMaxFrameX()) {
				currentFrame = 0;
			}
			_viObject->objectInfo.frameX = currentFrame;
		}
		//	맞앗을때 표지판
		if (_viObject->state == EAGLESTATE::BEATTACKED) {
			currentFrame = _viObject->topFrameX;
			_viObject->topframeCount++;
			if (_viObject->topframeCount % 4 == 0) {
				_viObject->topframeCount = 0;
				currentFrame++;
				if (currentFrame > _viObject->topImg->getMaxFrameX()) {
					currentFrame = 0;
				}
				_viObject->topFrameX = currentFrame;
			}
		}
		//	표정
		if (_viObject->state == EAGLESTATE::NORMAL) {
			_viObject->faceFrameX = (int)EAGLESTATE::NORMAL;
		}
		else if (_viObject->state == EAGLESTATE::BEATTACKED) {
			_viObject->faceFrameX = (int)EAGLESTATE::BEATTACKED;
		}
		else if (_viObject->state == EAGLESTATE::DOATTACK) {
			_viObject->faceFrameX = (int)EAGLESTATE::DOATTACK;
		}
		//피격당했는지
		auto vBullet = py->getBullet1()->getviperBullet();
		auto viBullet = vBullet->begin();
		for (viBullet; viBullet != vBullet->end(); )
		{
			RECT temp;
			if (!viBullet->bulletDeath && !_viObject->objectInfo.isDeath && IntersectRect(&temp, &(viBullet->rc), &(_viObject->objectInfo.rc))) {
				viBullet->bulletDeath = true;
				if (!_viObject->objectInfo.isinvincible) {
					_viObject->objectInfo.isHit = true;
					_viObject->objectInfo.hp--;
				}
				if (_viObject->objectInfo.hp <= 0) {
					_viObject->objectInfo.isDeath = true;
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
			if (!viBullet2->bulletDeath && !_viObject->objectInfo.isDeath && IntersectRect(&temp, &(viBullet2->rc), &(_viObject->objectInfo.rc))) {
				viBullet2->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				if (!_viObject->objectInfo.isinvincible) {
					_viObject->objectInfo.isHit = true;
					_viObject->objectInfo.hp--;
				}
				if (_viObject->objectInfo.hp <= 0) {
					_viObject->objectInfo.isDeath = true;
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
			if (!viBullet3->bulletDeath && !_viObject->objectInfo.isDeath && IntersectRect(&temp, &(viBullet3->rc), &(_viObject->objectInfo.rc))) {
				viBullet3->bulletDeath = true;
				//viBullet = vBullet->erase(viBullet);
				if (!_viObject->objectInfo.isinvincible) {
					_viObject->objectInfo.isHit = true;
					_viObject->objectInfo.hp--;
				}
				if (_viObject->objectInfo.hp <= 0) {
					_viObject->objectInfo.isDeath = true;
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
			if (viBullet4->hp > 0 && !viBullet4->bulletDeath && !_viObject->objectInfo.isDeath && IntersectRect(&temp, &(viBullet4->rc), &(_viObject->objectInfo.rc))) {
				viBullet4->hp--;
				//viBullet = vBullet->erase(viBullet);
				if (!_viObject->objectInfo.isinvincible) {
					_viObject->objectInfo.isHit = true;
					_viObject->objectInfo.hp--;
				}
				if (_viObject->objectInfo.hp <= 0) {
					_viObject->objectInfo.isDeath = true;
				}
			}
			else {
				++viBullet4;
			}
		}
	}
	//벡터내에서 선택적 요소가 해야할 것.
	//몬스터 폭발이미지랜더링 이후 사라지는 구문.
	for (_viObject = _vObject.begin(); _viObject != _vObject.end(); )
	{
		if (_viObject->objectInfo.afterExplosion)
		{
			//bl->init(_viObject->objectInfo.x, _viObject->objectInfo.y-20);
			bl->init(_viObject->objectInfo.x+100, _viObject->objectInfo.y+40);
			bl->init(_viObject->objectInfo.x+200, _viObject->objectInfo.y+100);
			bl->init(_viObject->objectInfo.x+100, _viObject->objectInfo.y+160);
			//bl->init(_viObject->objectInfo.x, _viObject->objectInfo.y+220);
			_viObject = _vObject.erase(_viObject);
		}
		else {
			++_viObject;
		}
	}
	//범위밖이라 사라지는 구문.
	for (_viObject = _vObject.begin(); _viObject != _vObject.end(); )
	{
		if (_viObject->objectInfo.x + _viObject->objectInfo.image->getFrameWidth() < 0 ||
			_viObject->objectInfo.y > WINSIZEY ||
			_viObject->objectInfo.x > WINSIZEX + 100 ||
			_viObject->objectInfo.y + _viObject->objectInfo.image->getFrameHeight() < 0)
		{
			_viObject = _vObject.erase(_viObject);
		}
		else {
			++_viObject;
		}
	}
	if (_ebul != nullptr) _ebul->update();
}

void oEagle2::render()
{
	if (_ebul != nullptr) _ebul->render();
	for (_viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject)
	{
		//죽지 않았다면 계속 출력
		if (!_viObject->objectInfo.isDeath) {
			if (_isDebug) Rectangle(getMemDC(), _viObject->objectInfo.rc.left, _viObject->objectInfo.rc.top,
				_viObject->objectInfo.rc.right, _viObject->objectInfo.rc.bottom);
			_viObject->objectInfo.image->frameRender(getMemDC(), _viObject->objectInfo.x, _viObject->objectInfo.y, _viObject->objectInfo.frameX, 0);

			_viObject->faceImg->frameRender(getMemDC(),
				_viObject->objectInfo.x + 15, _viObject->objectInfo.y + 48, _viObject->faceFrameX, 0);
			if (_viObject->state == EAGLESTATE::BEATTACKED) {

				_viObject->topImg->frameRender(getMemDC(),
					_viObject->objectInfo.x + 39, _viObject->objectInfo.y - 33, _viObject->topFrameX, 0);
			}
		}
		//죽었다면 사망장면 출력
		else {
			_viObject->objectInfo.deathcount++;
			if (_viObject->objectInfo.deathcount % 3 == 0) {
				_viObject->objectInfo.deathcount = 0;
				_viObject->objectInfo.deathFrame++;
			}
			if (showExplosion(_viObject->objectInfo.x, _viObject->objectInfo.y, _viObject->objectInfo.deathFrame, 0, 1)) {
				_viObject->objectInfo.afterExplosion = true;
			}
		}
	}
}

void oEagle2::attack(tagEagle2& eagle)
{
	eagle.state = EAGLESTATE::DOATTACK;
	if (eagle.shootY == -1) {
		eagle.shootY = eagle.objectInfo.y + eagle.objectInfo.image->getFrameHeight() / 2 - 50;
	}
	_ebul->fire(eagle.objectInfo.x + eagle.objectInfo.image->getFrameWidth() / 2 - 21,
		eagle.shootY);
}

void oEagle2::move(tagEagle2& eagle)
{
	//위아래이동조건
	if (!eagle.objectInfo.isinvincible) {
		if (eagle.isUp) {
			eagle.objectInfo.y -= eagle.updownspeed;
			eagle.updownspeed -= 0.1;
			if (eagle.updownspeed <= 0) {
				eagle.isUp = false;
				eagle.updownspeed = 3;
			}
		}
		else {
			eagle.objectInfo.y += eagle.updownspeed;
			eagle.updownspeed -= 0.1;
			if (eagle.updownspeed <= 0) {
				eagle.isUp = true;
				eagle.updownspeed = 3;
			}
		}
	}
	//피격받았을때 무적상태진입 (공격중이라면 다씹고 무빙할거임)
	if (eagle.objectInfo.isHit && eagle.state != EAGLESTATE::DOATTACK) {
		eagle.objectInfo.isHit = false;
		eagle.objectInfo.isinvincible = true;
	}
	//무적상태라면 이동안하고 표정 바꿈. 10카운트 후 원상태로 돌아옴.
	if (eagle.objectInfo.isinvincible && eagle.state != EAGLESTATE::DOATTACK) {
		eagle.objectInfo.isinvincibleCount++;
		eagle.state = EAGLESTATE::BEATTACKED;
		if (eagle.objectInfo.isinvincibleCount % 10 == 0) {
			eagle.objectInfo.isinvincibleCount = 0;
			eagle.objectInfo.isinvincible = false;
			eagle.state = EAGLESTATE::NORMAL;
		}
	}
	//공격중이라면 표정바꾸고 공격마치면 모든것을 원래상태로
	if (eagle.state == EAGLESTATE::DOATTACK)
	{
		eagle.attackcount++;
		if (eagle.attackcount % 80 == 0) {
			eagle.state = EAGLESTATE::NORMAL;
			eagle.objectInfo.isinvincibleCount = 0;
			eagle.objectInfo.isinvincible = false;
			eagle.objectInfo.isHit = false;
		}
	}
}

void oEagle2::changeStateInvinOrNormal(vector<tagEagle2>::iterator iter)
{
	if (!iter->objectInfo.isinvincible) {
		iter->objectInfo.hp--;
		iter->objectInfo.isHit = true;
	}
	if (iter->objectInfo.hp <= 0) {
		iter->objectInfo.isDeath = true;
	}
}
//////////////////////////////////////////////////////////////
//////////////////////oclaw! 뽑기집게!//////////////////////////
//////////////////////////////////////////////////////////////
oclaw::oclaw()
{
	_pp = new puppet;
	_pp->init();
}

oclaw::~oclaw(){}

HRESULT oclaw::init(int patternNum)
{
	if (patternNum != 6) {
		tagClaw newClaw;
		newClaw.clawImg = IMAGE->addFrameImage("집게", "images/enemy/claw.bmp", 504, 111, 3, 1, true);
		newClaw.wireImg = IMAGE->addImage("와이어", "images/enemy/clawwire.bmp", 18, 72);
		newClaw.y = 0;

		if (patternNum == 1) {
			newClaw.x = WINSIZEX + 1;
			newClaw.clawstate = CLAWSTATE::NORMAL;
		}
		else if (patternNum == 2) {
			newClaw.x = WINSIZEX + 1;
			newClaw.clawstate = CLAWSTATE::NORMAL;
		}
		else if (patternNum == 3) {
			newClaw.x = -50;
			newClaw.clawstate = CLAWSTATE::GRAP;
		}
		else if (patternNum == 4) {
			newClaw.x = WINSIZEX + 1;
			newClaw.clawstate = CLAWSTATE::NORMAL;
		}
		else if (patternNum == 5) {
			newClaw.x = WINSIZEX + 1;
			newClaw.clawstate = CLAWSTATE::NORMAL;
		}
		newClaw.centerX = newClaw.x + newClaw.wireImg->getWidth() / 2;
		newClaw.clawFrameX = (int)newClaw.clawstate;
		newClaw.wireLength = newClaw.wireImg->getHeight();
		setRcs(newClaw, (int)newClaw.clawstate);

		newClaw.myPuppet = nullptr;
		newClaw.hasdoll = false;

		newClaw.speed = 4.0f;
		newClaw.moveCount = 0;
		newClaw.hp = 20;
		newClaw.deathcount = 0;
		newClaw.deathFrame = 0;
		newClaw.isDeath = false;
		newClaw.afterExplosion = false;
		newClaw.goDownCount = 0;

		newClaw.patternNum = patternNum;

		_vObject.push_back(newClaw);
	}
	else {
		specailInit();
	}
	return S_OK;
}

void oclaw::specailInit()
{
	tagClaw newClaw;
	newClaw.clawImg = IMAGE->addFrameImage("집게", "images/enemy/claw.bmp", 504, 111, 3, 1, true);
	newClaw.wireImg = IMAGE->addImage("와이어", "images/enemy/clawwire.bmp", 18, 72);
	newClaw.y = 0;
	newClaw.x = -60;
	newClaw.clawstate = CLAWSTATE::NORMAL;
	newClaw.centerX = newClaw.x + newClaw.wireImg->getWidth() / 2;
	newClaw.clawFrameX = (int)newClaw.clawstate;
	newClaw.wireLength = newClaw.wireImg->getHeight();
	setRcs(newClaw, (int)newClaw.clawstate);
	newClaw.myPuppet = &_pp->getLPuppet()[5];
	newClaw.hasdoll = true;
	newClaw.speed = 2.0f;
	newClaw.moveCount = 0;
	newClaw.hp = 20;
	newClaw.deathcount = 0;
	newClaw.deathFrame = 0;
	newClaw.isDeath = false;
	newClaw.afterExplosion = false;
	newClaw.goDownCount = 0;
	newClaw.patternNum = 6;
	_vObject.push_back(newClaw);

	ZeroMemory(&newClaw, sizeof(newClaw));
	newClaw.clawImg = IMAGE->addFrameImage("집게", "images/enemy/claw.bmp", 504, 111, 3, 1, true);
	newClaw.wireImg = IMAGE->addImage("와이어", "images/enemy/clawwire.bmp", 18, 72);
	newClaw.y = 0;
	newClaw.x = -300;
	newClaw.clawstate = CLAWSTATE::NORMAL;
	newClaw.centerX = newClaw.x + newClaw.wireImg->getWidth() / 2;
	newClaw.clawFrameX = (int)newClaw.clawstate;
	newClaw.wireLength = newClaw.wireImg->getHeight();
	setRcs(newClaw, (int)newClaw.clawstate);
	newClaw.myPuppet = &_pp->getLPuppet()[5];
	newClaw.hasdoll = true;
	newClaw.speed = 2.0f;
	newClaw.moveCount = 0;
	newClaw.hp = 20;
	newClaw.deathcount = 0;
	newClaw.deathFrame = 0;
	newClaw.isDeath = false;
	newClaw.afterExplosion = false;
	newClaw.goDownCount = 0;
	newClaw.patternNum = 6;
	_vObject.push_back(newClaw);
}

void oclaw::release()
{
	_pp->release();
	SAFE_DELETE(_pp);
}

void oclaw::update(player* py, bell* bl, powerUp* pu)
{
	//벡터내에서 모든 요소가 해야할 것.
	for (_viObject = _vObject.begin(); _viObject != _vObject.end(); ++_viObject)
	{
		//죽엇는지 확인
		checkDie(*_viObject);
		//몬스터의 패턴을 카운트별로 설정.
		_viObject->moveCount++;
		if (_viObject->patternNum == 1) {
			pattern1(*_viObject);
		}
		else if (_viObject->patternNum == 2) {
			pattern2(*_viObject);
		}
		else if (_viObject->patternNum == 3) {
			pattern3(*_viObject);
		}
		else if(_viObject->patternNum == 4){
			pattern4(*_viObject);
		}
		else if(_viObject->patternNum == 5) {
			pattern5(*_viObject);
		}
		else {
			pattern6(*_viObject);
		}

		//피격당했는지
		auto vBullet = py->getBullet1()->getviperBullet();
		auto viBullet = vBullet->begin();
		for (viBullet; viBullet != vBullet->end(); ++viBullet)
		{
			RECT temp;
			for (size_t i = 0; i < 2; i++)
			{
				if (!viBullet->bulletDeath && !_viObject->isDeath && IntersectRect(&temp, &(viBullet->rc), &(_viObject->wireRc[i]))) {
					viBullet->bulletDeath = true;
					_viObject->hp--;
					if (_viObject->hp <= 0) {
						_viObject->isDeath = true;
    						if(_viObject->myPuppet!=nullptr) _viObject->myPuppet->remainMother--;
					}
				}
			}
			for (size_t i = 0; i < 3; i++)
			{
				if (!viBullet->bulletDeath && !_viObject->isDeath && IntersectRect(&temp, &(viBullet->rc), &(_viObject->ClawRc[i]))) {
					viBullet->bulletDeath = true;
					_viObject->hp--;
					if (_viObject->hp <= 0) {
						_viObject->isDeath = true;
						if (_viObject->myPuppet != nullptr) _viObject->myPuppet->remainMother--;
					}
				}
			}
		}
		auto vBullet2 = py->getBullet2()->getviperDropMissile();
		auto viBullet2 = vBullet2->begin();
		for (viBullet2; viBullet2 != vBullet2->end(); ++viBullet2)
		{
			RECT temp;
			for (size_t i = 0; i < 2; i++)
			{
				if (!viBullet2->bulletDeath && !_viObject->isDeath && IntersectRect(&temp, &(viBullet2->rc), &(_viObject->wireRc[i]))) {
					viBullet2->bulletDeath = true;
					_viObject->hp--;
					if (_viObject->hp <= 0) {
						_viObject->isDeath = true;
						if (_viObject->myPuppet != nullptr) _viObject->myPuppet->remainMother--;
					}
				}
			}
			for (size_t i = 0; i < 3; i++)
			{
				if (!viBullet2->bulletDeath && !_viObject->isDeath && IntersectRect(&temp, &(viBullet2->rc), &(_viObject->ClawRc[i]))) {
					viBullet2->bulletDeath = true;
					_viObject->hp--;
					if (_viObject->hp <= 0) {
						_viObject->isDeath = true;
						if (_viObject->myPuppet != nullptr) _viObject->myPuppet->remainMother--;
					}
				}
			}
		}
		auto vBullet3 = py->getBullet3()->getviperDigonalBullet();
		auto viBullet3 = vBullet3->begin();
		for (viBullet3; viBullet3 != vBullet3->end(); ++viBullet3)
		{
			RECT temp;
			for (size_t i = 0; i < 2; i++)
			{
				if (!viBullet3->bulletDeath && !_viObject->isDeath && IntersectRect(&temp, &(viBullet3->rc), &(_viObject->wireRc[i]))) {
					viBullet3->bulletDeath = true;
					_viObject->hp--;
					if (_viObject->hp <= 0) {
						_viObject->isDeath = true;
						if (_viObject->myPuppet != nullptr) _viObject->myPuppet->remainMother--;
					}
				}
			}
			for (size_t i = 0; i < 3; i++)
			{
				if (!viBullet3->bulletDeath && !_viObject->isDeath && IntersectRect(&temp, &(viBullet3->rc), &(_viObject->ClawRc[i]))) {
					viBullet3->bulletDeath = true;
					_viObject->hp--;
					if (_viObject->hp <= 0) {
						_viObject->isDeath = true;
						if (_viObject->myPuppet != nullptr) _viObject->myPuppet->remainMother--;
					}
				}
			}
		}
		auto vBullet4 = py->getBullet4()->getviperLaser();
		auto viBullet4 = vBullet4->begin();
		for (viBullet4; viBullet4 != vBullet4->end(); ++viBullet4)
		{
			RECT temp;
			for (size_t i = 0; i < 2; i++)
			{
				if (viBullet4->hp>0 && !viBullet4->bulletDeath && !_viObject->isDeath && IntersectRect(&temp, &(viBullet4->rc), &(_viObject->wireRc[i]))) {
					viBullet4->hp--;
					_viObject->hp--;
					if (_viObject->hp <= 0) {
						_viObject->isDeath = true;
						if (_viObject->myPuppet != nullptr) _viObject->myPuppet->remainMother--;
					}
				}
			}
			for (size_t i = 0; i < 3; i++)
			{
				if (viBullet4->hp > 0 && !viBullet4->bulletDeath && !_viObject->isDeath && IntersectRect(&temp, &(viBullet4->rc), &(_viObject->ClawRc[i]))) {
					viBullet4->hp--;
					_viObject->hp--;
					if (_viObject->hp <= 0) {
						_viObject->isDeath = true;
						if (_viObject->myPuppet != nullptr) _viObject->myPuppet->remainMother--;
					}
				}
			}
		}
	}
	//벡터내에서 선택적 요소가 해야할 것.
	//몬스터 폭발이미지랜더링 이후 사라지는 구문.
	for (_viObject = _vObject.begin(); _viObject != _vObject.end(); )
	{
		if (_viObject->afterExplosion)
		{
			//pu->init(_viObject->objectInfo.x, _viObject->objectInfo.y, 0, true);
			if (RND->getInt(1) == 0) {
				bl->init(_viObject->centerX - _viObject->clawImg->getFrameWidth() / 2,
					_viObject->y + _viObject->wireLength);
				bl->init(_viObject->x + 200, _viObject->y + 100);
			}
			_viObject = _vObject.erase(_viObject);
		}
		else {
			++_viObject;
		}
	}
	//범위밖이라 사라지는 구문.
	for (_viObject = _vObject.begin(); _viObject != _vObject.end(); )
	{
		if ((_viObject->centerX + _viObject->clawImg->getFrameWidth()/2 < -200 && _viObject->patternNum!=6) ||
			(_viObject->centerX - _viObject->clawImg->getFrameWidth()/2 > WINSIZEX + 200 && _viObject->patternNum != 6)||
			(_viObject->patternNum == 6 && _viObject->centerX - _viObject->clawImg->getFrameWidth() / 2 > WINSIZEX + 400))
		{
			_viObject = _vObject.erase(_viObject);
		}
		else {
			++_viObject;
		}
	}
	_pp->update(py);
}

void oclaw::render()
{
	for (_viObject = _vObject.begin(); _viObject!= _vObject.end(); ++_viObject){
		//죽지않았으면 출력
		if (!_viObject->isDeath) {
			if (_isDebug) {
				for (size_t i = 0; i < 2; i++)
				{
					Rectangle(getMemDC(), _viObject->wireRc[i].left, _viObject->wireRc[i].top, _viObject->wireRc[i].right, _viObject->wireRc[i].bottom);
				}
				for (size_t i = 0; i < 3; i++) {
					Rectangle(getMemDC(), _viObject->ClawRc[i].left, _viObject->ClawRc[i].top, _viObject->ClawRc[i].right, _viObject->ClawRc[i].bottom);
				}
			}
			_viObject->wireImg->loopRender(getMemDC(), &RectMake(_viObject->x, _viObject->y, _viObject->wireImg->getWidth(), _viObject->wireLength), 0, 0);
			_viObject->clawImg->frameRender(getMemDC(), _viObject->centerX - _viObject->clawImg->getFrameWidth() / 2,
				_viObject->y + _viObject->wireLength, _viObject->clawFrameX, 0);
		}
		//죽엇으면 사망장면출력
		else {
			_viObject->deathcount++;
			if (_viObject->deathcount % 3 == 0) {
				_viObject->deathcount = 0;
				_viObject->deathFrame++;
			}
			if (showExplosion(_viObject->centerX - _viObject->clawImg->getFrameWidth() / 2,
				_viObject->y + _viObject->wireLength, _viObject->deathFrame, 0, 1)) {
				_viObject->afterExplosion = true;
			}
		}
	}
	_pp->render();
}

void oclaw::checkDie(tagClaw& claw)
{
	if (claw.hp <= 0) {
		claw.isDeath = true;
		if (_viObject->myPuppet != nullptr) claw.myPuppet->remainMother--;
	}
}

void oclaw::goLeft(tagClaw& claw)
{
	claw.x -= claw.speed;
	claw.centerX = claw.x + claw.wireImg->getWidth() / 2;
	//가진 인형이 있다면 걔도 왼쪽으로
	if (claw.hasdoll&&!claw.isDeath) {
		_pp->setX(*(claw.myPuppet), _pp->getX(*(claw.myPuppet)) - claw.speed);
	}
	for (size_t i = 0; i < 2; i++)
	{
		OffsetRect(&claw.wireRc[i], -claw.speed, 0);
	}	
	for (size_t i = 0; i < 3; i++)
	{
		OffsetRect(&claw.ClawRc[i], -claw.speed, 0);
	}
}

void oclaw::goRight(tagClaw& claw)
{
	claw.x += claw.speed;
	claw.centerX = claw.x + claw.wireImg->getWidth() / 2;
	//가진 인형이 있다면 걔도 오른쪽으로 가는 구문.
	if (claw.patternNum == 6) {
		//다만 패턴6일때는 체인지변수확인하고 이미 바뀌었으면 건들지않음.
		if (claw.myPuppet->remainMother == 2) {
			if (!claw.myPuppet->specialChange) {
				//부모둘인데 아직 체인지되지 않은경우에는 움직여줌
				_pp->setX(*(claw.myPuppet), _pp->getX(*(claw.myPuppet)) + claw.speed);
				claw.myPuppet->specialChange = true;
			}
			else {
				//부모둘인데 이미 체인지된경우에는 움직이지 않음.
				claw.myPuppet->specialChange = false;
			}
		}
		else if (claw.myPuppet->remainMother == 1) {
			_pp->setX(*(claw.myPuppet), _pp->getX(*(claw.myPuppet)) + claw.speed);
		}
	}
	else {
		if (claw.hasdoll && !claw.isDeath) {
			_pp->setX(*(claw.myPuppet), _pp->getX(*(claw.myPuppet)) + claw.speed);
		}
	}
	for (size_t i = 0; i < 2; i++)
	{
		OffsetRect(&claw.wireRc[i], claw.speed, 0);
	}
	for (size_t i = 0; i < 3; i++)
	{
		OffsetRect(&claw.ClawRc[i], claw.speed, 0);
	}
}

void oclaw::goDown(tagClaw& claw)
{
	claw.goDownCount++;
	if (claw.goDownCount < 120) {
		claw.wireLength += claw.speed;
		setRcs(claw, 0);
		//내려갈 땐 인형을 가지고 있을리 없으므로, 그냥 자기 좌표만 수정.
	}
	else if (claw.goDownCount > 120 && claw.goDownCount < 140)
	{
		if (!claw.hasdoll)	grapRandomDoll(claw);
		changeClawState(claw, 1);
		setRcs(claw, 1);
	}
	else if (claw.goDownCount > 140 && claw.wireLength!=claw.wireImg->getHeight()) {
		goUp(claw);		
	}
}

void oclaw::goUp(tagClaw& claw)
{
	claw.wireLength -= claw.speed;
	changeClawState(claw, 2);
	setRcs(claw, 2);
	//인형을 가지고 있다면 인형도 위로끌어올리기.
	if (claw.hasdoll) {
		_pp->setY(*(claw.myPuppet), _pp->getY(*(claw.myPuppet)) - claw.speed);
	}
}

void oclaw::pattern1(tagClaw& claw)
{
	if (claw.moveCount < 200) {
		goLeft(*_viObject);
	}
	if (claw.moveCount > 250 && claw.moveCount < 270) {
		goRight(*_viObject);
	}
	if (claw.moveCount > 270 && claw.moveCount < 600) { //330정도 소요
		goDown(*_viObject);
	}
	if(claw.moveCount > 600) {
		goLeft(*_viObject);
	}
}

void oclaw::pattern2(tagClaw& claw)
{
	if (claw.moveCount < 500) {
		goLeft(*_viObject);
	}
}

void oclaw::pattern3(tagClaw& claw)
{
	if (claw.moveCount == 5) {
		grapRandomDoll(claw);
	}
	if (claw.moveCount < 150) {
		goRight(*_viObject);
	}
	if (claw.moveCount > 150 && claw.moveCount < 165)
	{
		changeClawState(claw, 1);
		claw.myPuppet->hasMother = false;
		claw.hasdoll = false;
		setRcs(claw, 1);
	}
	if (claw.moveCount > 165)
	{
		goRight(*_viObject);
	}
}

void oclaw::pattern4(tagClaw& claw)
{
	if (claw.moveCount < 100) {
		goLeft(*_viObject);
	}
	if (claw.moveCount > 140 && claw.moveCount < 470) { //330정도 소요
		goDown(*_viObject);
	}
	if (claw.moveCount > 470) {
		goLeft(*_viObject);
	}
}

void oclaw::pattern5(tagClaw& claw)
{
	if (claw.moveCount < 200) {
		goLeft(*_viObject);
	}
	if (claw.moveCount > 250 && claw.moveCount < 270) {
		goRight(*_viObject);
	}
	if (claw.moveCount > 270 && claw.moveCount < 600) { //330정도 소요
		goDown(*_viObject);
	}
	if (claw.moveCount > 600) {
		goRight(*_viObject);
	}
}

void oclaw::pattern6(tagClaw& claw)
{
	goRight(*_viObject);
}

void oclaw::changeClawState(tagClaw& claw, int snum)
{
	switch (snum)
	{
	case 0:
		claw.clawstate = CLAWSTATE::NORMAL;
		claw.clawFrameX = (int)claw.clawstate;
		break;
	case 1:
		claw.clawstate = CLAWSTATE::WIDE;
		claw.clawFrameX = (int)claw.clawstate;
		break;
	case 2:
		claw.clawstate = CLAWSTATE::GRAP;
		claw.clawFrameX = (int)claw.clawstate;
		break;
	}
}

void oclaw::setRcs(tagClaw& claw, int snum) //y좌표가 바뀌면 꼭 호출하기.
{
	switch (snum)
	{
	case 0:
		claw.wireRc[0] = RectMake(claw.x, claw.y, claw.wireImg->getWidth(), claw.wireLength);
		claw.wireRc[1] = RectMake(claw.centerX - 30, claw.y + claw.wireLength, 60, 24);
		claw.ClawRc[0] = RectMake(claw.centerX - 45, claw.y + claw.wireLength + 24, 90, 30);
		claw.ClawRc[1] = RectMake(claw.centerX - 45, claw.y + claw.wireLength + 24 + 30, 24, 54);
		claw.ClawRc[2] = RectMake(claw.centerX + 45 - 24, claw.y + claw.wireLength + 24 + 30, 24, 54);
		break;
	case 1:
		claw.wireRc[0] = RectMake(claw.x, claw.y, claw.wireImg->getWidth(), claw.wireLength);
		claw.wireRc[1] = RectMake(claw.centerX - 30, claw.y + claw.wireLength, 60, 24);
		claw.ClawRc[0] = RectMake(claw.centerX - 72, claw.y + claw.wireLength + 24, 144, 30);
		claw.ClawRc[1] = RectMake(claw.centerX - 81, claw.y + claw.wireLength + 24 + 30, 12, 45);
		claw.ClawRc[2] = RectMake(claw.centerX + 81 - 12, claw.y + claw.wireLength + 24 + 30, 12, 45);
		break;
	case 2:
		claw.wireRc[0] = RectMake(claw.x, claw.y, claw.wireImg->getWidth(), claw.wireLength);
		claw.wireRc[1] = RectMake(claw.centerX - 30, claw.y + claw.wireLength, 60, 24);
		claw.ClawRc[0] = RectMake(claw.centerX - 45, claw.y + claw.wireLength + 24, 90, 30);
		claw.ClawRc[1] = RectMake(claw.centerX - 45 - 24, claw.y + claw.wireLength + 24 + 30 - 15, 24, 60);
		claw.ClawRc[2] = RectMake(claw.centerX + 45, claw.y + claw.wireLength + 24 + 30 - 15, 24, 60);
		break;
	}
}

void oclaw::grapRandomDoll(tagClaw& claw)
{
	claw.myPuppet = _pp->givePuppet(claw.centerX, claw.ClawRc[0].bottom + 51);
	claw.hasdoll = true;
}
