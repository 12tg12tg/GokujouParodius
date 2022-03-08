#include "framework.h"
#include "panda.h"
#include "player.h"
#include "enemyManager.h"
#include "powerUp.h"
panda::panda()
{
}

panda::~panda()
{
}

HRESULT panda::init()
{
	_pandaImg = IMAGE->addFrameImage("�Ҵ��븻", "images/boss/panda.bmp",  2016, 2010, 7, 5, true);
	_pandaDieImg = IMAGE->addFrameImage("�Ҵ����", "images/boss/pandaDie.bmp", 618, 321, 2, 1, true);
	_pandaExplosionImg = IMAGE->addFrameImage("�Ҵ�����", "images/boss/pandaExplosion.bmp", 720,  366, 2, 1, true);
	
	_shoot = IMAGE->addFrameImage("��", "images/boss/shoot.bmp", 720, 48, 3, 1, true);
	_backHp = IMAGE->addImage("hp��", "images/boss/backHpBar.bmp", 495, 54, true);
	_frontHp = IMAGE->addImage("hp��", "images/boss/frontHpBar.bmp", 483, 46);
	
	_unit1 = IMAGE->addFrameImage("�Ź�", "images/boss/unit1.bmp", 174, 57, 2, 1, true);
	_unit2 = IMAGE->addImage("��", "images/boss/unit2.bmp", 45, 48, true);
	_unit3 = IMAGE->addFrameImage("����", "images/boss/unit3.bmp", 96, 45, 2, 1, true);
	_unit4 = IMAGE->addFrameImage("����", "images/boss/unit4.bmp", 144, 69, 3, 1, true);
	_unit5 = IMAGE->addFrameImage("���Ƹ�", "images/boss/unit5.bmp", 90, 42, 2, 1, true);
	_unit6 = IMAGE->addFrameImage("ġŲ", "images/boss/unit6.bmp", 96, 48, 2, 1, true);
	_bigUnit = IMAGE->addFrameImage("ū����", "images/boss/bigunit.bmp", 450, 96, 5, 1, true);

	_x = 650;
	_y = WINSIZEY;
	_speed = 5.0f;
	_framespeed = 6;
	_thingSize = 40;
	_state = PANDASTATE::TURN;
	setNorFrame();
	_norCount = 0;
	_isDie = false;
	_isInvincible = false;
	_isHit = false;
	_dontChangeHitFrame = false;
	_hitCount = 0;
	_invinCount = 0;

	_hp = MAXHP;
	_showShoot = false;
	_showShootCount = 0;
	
	_term = 15;
	_untilX = 150;
	_turnUntil = 150;
	_patternCount = 0;
	_patternNum = 0;
	_start = false;
	_isStartInvin = true;
	_gravityacc = 0.1f;

	//����
	_clawCount = 0;


	_dieFrameX = 0;
	_dieCount = 0;
	_exploFrameX = 0;
	_exploCount = 0;
	_exploNum = 0;

	_isclear = false;

	_claw = new oclaw;
	return S_OK;
}

void panda::release()
{
	_claw->release();
	SAFE_DELETE(_claw);
}

void panda::update()
{
	if (_start) {
		if (!_isDie) {
			doPattern();
			collision();
			hitAndInvinAndDeathCheck();
			setNorFrame();
			setHitBox();
			under80();
			under55();
			under25();
			startPurpleEffect();
			puppetupdate();
			_claw->update(_py, _bl, _pu);
		}
		else {
			afterDeath();
		}
		clawCollisionToPlayer();
		checkclawDie();
	}
}

void panda::render()
{
	if (_start) {
		if (_showShoot) {
			_showShootCount++;
			if (_showShootCount % 5 == 0) {
				int frameX;
				frameX = _shoot->getFrameX();
				frameX++;
				if(frameX > _shoot->getMaxFrameX())
					frameX = 0;
				_shoot->setFrameX(frameX);
			}
			_shoot->frameRender(getMemDC(), _duckRc.left - 50 - _shoot->getFrameWidth(),
				_duckRc.top + (_duckRc.bottom - _duckRc.top) / 2 - 50, _shoot->getFrameX(), 0);
		}
		_claw->render();
		if (!_isDie) {
			showPanda();
		}
		else {
			showExplosion();
		}
		showPuppet();
		showHpBar();
	}
}

void panda::setNorFrame()
{
	switch (_state)
	{
	case panda::PANDASTATE::STAY:
		_norFrameX = 0;
		_norFrameY = 0;
		break;
	case panda::PANDASTATE::BARK:
		_startFrameX = 0;
		_maxFrameX = 3;
		_norFrameY = 0;
		break;
	case panda::PANDASTATE::TURN:
		_startFrameX = 0;
		_maxFrameX = 6;
		_norFrameY = 1;
		break;
	case panda::PANDASTATE::GOLEFT:
		_startFrameX = 0;
		_maxFrameX = 3;
		_norFrameY = 2;
		break;
	case panda::PANDASTATE::GORIGHT:
		_startFrameX = 0;
		_maxFrameX = 3;
		_norFrameY = 3;
		break;
	case panda::PANDASTATE::LEFTHIT:
		_startFrameX = 0;
		_maxFrameX = 1;
		_norFrameY = 4;
		break;
	case panda::PANDASTATE::RIGHTHIT:
		_startFrameX = 2;
		_maxFrameX = 3;
		_norFrameY = 4;
		break;
	}
	_norCount++;
	//�������ε����� �����ε�����
	if (_norFrameX<_startFrameX && _norFrameX>_maxFrameX)
		_norFrameX = _startFrameX;
	//���������� �������� ������ ������ ����.
	if (_norCount % _framespeed == 0 && _state != panda::PANDASTATE::STAY && _state != panda::PANDASTATE::LEFTHIT &&
		_state != panda::PANDASTATE::RIGHTHIT)
	{
		_norCount == 0;
		_norFrameX++;
		//�ƽ������Ӻ���ũ�ٸ�, �����ε�����
		if(_norFrameX > _maxFrameX)
			_norFrameX = _startFrameX;
	}
	//�´¸�����̿������ ���� ���� ã�ư���
	else if ((_state == panda::PANDASTATE::LEFTHIT || _state == panda::PANDASTATE::RIGHTHIT) && _norCount % 10 == 0) {
		_norFrameX++;
		if (_norFrameX > _maxFrameX) {
			switch (_patternNum)
			{
			case 1:
				_state = PANDASTATE::GOLEFT;
				_norFrameX = 0;
				break;
			case 3:
				_state = PANDASTATE::GORIGHT;
				_norFrameX = 0;
				break;
			}
		}
	}
}

void panda::setHitBox()
{
	//state�� frame�� �������, �׿� ���缭 ��Ʈ�ڽ��� ON/OFF ����.
	switch (_state)
	{
	case panda::PANDASTATE::BARK:
		_duckRc = RectMake(_x + 129, _y + 48, 30, 48);
		_headRc = RectMake(_x + 99, _y + 96, 90, 84);
		_bodyRc = RectMake(_x + 84, _y + 144, 123, 117);
		_leftArmRc[0] = RectMake(_x + 33, _y + 108, 24, 27);
		_leftArmRc[1] = RectMake(_x + 44, _y + 126, 33, 27);
		_leftArmRc[2] = RectMake(_x + 63, _y + 132, 30, 39);
		_rightArmRc[0] = RectMake(_x + 240, _y + 108, 18, 24);
		_rightArmRc[1] = RectMake(_x + 216, _y + 120, 27, 36);
		_rightArmRc[2] = RectMake(_x + 192, _y + 132, 27, 51);
		_waistRC = RectMake(_x + 33, _y + 249, 225, 60);
		_legRc[0] = RectMake(_x + 93, _y + 310, 108, 32);
		_legRc[1] = RectMake(_x + 100, _y + 342, 90, 24);
		_legRc[2] = RectMake(_x + 123, _y + 366, 42, 24);
		_duckOff = false;
		_headOff = false;
		_leftArmOff = false;
		_rightArmOff = false;
		break;
	case panda::PANDASTATE::TURN:
		_duckRc = RectMake(_x + 129, _y + 48, 30, 48);
		_headRc = RectMake(_x + 99, _y + 96, 90, 84);
		_bodyRc = RectMake(_x + 84, _y + 144, 123, 117);
		_leftArmRc[0] = RectMake(_x + 33, _y + 108, 24, 27);
		_leftArmRc[1] = RectMake(_x + 44, _y + 126, 33, 27);
		_leftArmRc[2] = RectMake(_x + 63, _y + 132, 30, 39);
		_rightArmRc[0] = RectMake(_x + 240, _y + 108, 18, 24);
		_rightArmRc[1] = RectMake(_x + 216, _y + 120, 27, 36);
		_rightArmRc[2] = RectMake(_x + 192, _y + 132, 27, 51);
		_waistRC = RectMake(_x + 33, _y + 249, 225, 60);
		_legRc[0] = RectMake(_x + 93, _y + 310, 108, 32);
		_legRc[1] = RectMake(_x + 100, _y + 342, 90, 24);
		_legRc[2] = RectMake(_x + 123, _y + 366, 42, 24);
		if (_norFrameX == 0) {
			_duckOff = false;
			_headOff = false;
			_leftArmOff = false;
			_rightArmOff = false;
		}
		else {
			_duckOff = false;
			_headOff = false;
			_leftArmOff = true;
			_rightArmOff = true;
		}
		break;
	case panda::PANDASTATE::GOLEFT:
		_duckRc = RectMake(_x + 123, _y + 48, 30, 48);
		_headRc = RectMake(_x + 99, _y + 96, 90, 84);
		_bodyRc = RectMake(_x + 84, _y + 144, 123, 117);
		_leftArmRc[0] = RectMake(_x + 33, _y + 108, 24, 27);
		_leftArmRc[1] = RectMake(_x + 44, _y + 126, 33, 27);
		_leftArmRc[2] = RectMake(_x + 63, _y + 132, 30, 39);
		_rightArmRc[0] = RectMake(_x + 240, _y + 108, 18, 24);
		_rightArmRc[1] = RectMake(_x + 216, _y + 120, 27, 36);
		_rightArmRc[2] = RectMake(_x + 192, _y + 132, 27, 51);
		_waistRC = RectMake(_x + 33, _y + 249, 225, 60);
		//legRc �ٸ�
		if (_norFrameX == 0) {
			_legRc[0] = RectMake(_x + 84, _y+327, 72, 21);
			_legRc[1] = RectMake(_x+102, _y+348, 54, 18);
			_legRc[2] = RectMake(_x+120, _y+366, 36, 36);
		}
		else if (_norFrameX == 1) {
			_legRc[0] = RectMake(_x + 96, _y + 309, 102, 24);
			_legRc[1] = RectMake(_x + 111, _y + 333, 96, 24);
			_legRc[2] = RectMake(_x + 111, _y+357, 39, 39);
		}
		else if (_norFrameX == 2) {
			_legRc[0] = RectMake(_x + 54, _y + 318, 30, 54);
			_legRc[1] = RectMake(_x + 153, _y + 321, 60, 39);
			_legRc[2] = RectMake(_x + 174, _y + 360, 39, 36);
		}
		else if(_norFrameX == 3) {
			_legRc[0] = RectMake(_x + 54, _y + 315, 66, 36);
			_legRc[1] = RectMake(_x + 51, _y + 351, 33, 45);
			_legRc[2] = RectMake(_x + 165, _y + 315, 78, 39);
		}
		_duckOff = false;
		_headOff = false;
		_leftArmOff = false;
		_rightArmOff = false;
		break;
	case panda::PANDASTATE::GORIGHT:
		_duckRc = RectMake(_x + 135, _y + 48, 30, 48);
		_headRc = RectMake(_x + 99, _y + 96, 90, 84);
		_bodyRc = RectMake(_x + 84, _y + 144, 123, 117);
		_leftArmRc[0] = RectMake(_x + 33, _y + 108, 24, 27);
		_leftArmRc[1] = RectMake(_x + 44, _y + 126, 33, 27);
		_leftArmRc[2] = RectMake(_x + 63, _y + 132, 30, 39);
		_rightArmRc[0] = RectMake(_x + 240, _y + 108, 18, 24);
		_rightArmRc[1] = RectMake(_x + 216, _y + 120, 27, 36);
		_rightArmRc[2] = RectMake(_x + 192, _y + 132, 27, 51);
		_waistRC = RectMake(_x + 33, _y + 249, 225, 60);
		//legRc �ٸ�
		if (_norFrameX == 0) {
			_legRc[0] = RectMake(_x + 132, _y + 324, 72, 24);
			_legRc[1] = RectMake(_x + 135, _y + 348, 51, 18);
			_legRc[2] = RectMake(_x + 132, _y + 354, 30, 48);
		}
		else if (_norFrameX == 1) {
			_legRc[0] = RectMake(_x + 87, _y + 309, 108, 21);
			_legRc[1] = RectMake(_x + 78, _y + 330, 96, 27);
			_legRc[2] = RectMake(_x + 138, _y + 357, 39, 45);
		}
		else if (_norFrameX == 2) {
			_legRc[0] = RectMake(_x + 75, _y + 315, 54, 54);
			_legRc[1] = RectMake(_x + 75, _y + 369, 33, 33);
			_legRc[2] = RectMake(_x + 204, _y + 318, 30, 54);
		}
		else if (_norFrameX == 3) {
			_legRc[0] = RectMake(_x + 42, _y + 312, 93, 42);
			_legRc[1] = RectMake(_x + 159, _y + 315, 75, 36);
			_legRc[2] = RectMake(_x + 204, _y + 348, 36, 54);
		}
		_duckOff = false;
		_headOff = false;
		_leftArmOff = false;
		_rightArmOff = false;
		break;
	case panda::PANDASTATE::LEFTHIT:
		_duckRc = RectMake(_x + 115, _y + 48, 30, 48);
		_headRc = RectMake(_x + 64, _y + 96, 90, 84);
		_bodyRc = RectMake(_x + 54, _y + 144, 123, 117);
		_waistRC = RectMake(_x + 33, _y + 249, 225, 60);
		_legRc[0] = RectMake(_x + 93, _y + 310, 108, 24);
		_legRc[1] = RectMake(_x + 111, _y + 334, 105, 24);
		_legRc[2] = RectMake(_x + 123, _y + 358, 42, 24);
		_duckOff = false;
		_headOff = false;
		_leftArmOff = true;
		_rightArmOff = true;
		break;
	case panda::PANDASTATE::RIGHTHIT:
		_duckRc = RectMake(_x + 139, _y + 48, 30, 48);
		_headRc = RectMake(_x + 129, _y + 96, 90, 84);
		_bodyRc = RectMake(_x + 114, _y + 144, 123, 117);
		_waistRC = RectMake(_x + 33, _y + 249, 225, 60);
		_legRc[0] = RectMake(_x + 93, _y + 310, 108, 24);
		_legRc[1] = RectMake(_x + 75, _y + 334, 105, 24);
		_legRc[2] = RectMake(_x + 123, _y + 358, 42, 24);
		_duckOff = false;
		_headOff = false;
		_leftArmOff = true;
		_rightArmOff = true;
		break;
	}
}

void panda::showPanda()
{
	_pandaImg->frameRender(getMemDC(), _x, _y, _norFrameX, _norFrameY);
	if (_isDebug)
	{
		//�����浹�ڽ�
		if (!_duckOff) {
			Rectangle(getMemDC(), _duckRc.left, _duckRc.top, _duckRc.right, _duckRc.bottom);
		}
		//�Ӹ��浹�ڽ�
		if (!_headOff) {
			Rectangle(getMemDC(), _headRc.left, _headRc.top, _headRc.right, _headRc.bottom);
		}
		//���浹�ڽ�
		Rectangle(getMemDC(), _bodyRc.left, _bodyRc.top, _bodyRc.right, _bodyRc.bottom);
		//�㸮�浹�ڽ�
		Rectangle(getMemDC(), _waistRC.left, _waistRC.top, _waistRC.right, _waistRC.bottom);
		//���浹�ڽ�
		if (!_leftArmOff) {
			for (size_t i = 0; i < 3; i++)
			{
				Rectangle(getMemDC(), _leftArmRc[i].left, _leftArmRc[i].top, _leftArmRc[i].right, _leftArmRc[i].bottom);
			}			
		}
		if (!_rightArmOff) {
			for (size_t i = 0; i < 3; i++)
			{
				Rectangle(getMemDC(), _rightArmRc[i].left, _rightArmRc[i].top, _rightArmRc[i].right, _rightArmRc[i].bottom);
			}
		}
		//�ٸ��浹�ڽ�
		for (size_t i = 0; i < 3; i++)
		{
			Rectangle(getMemDC(), _legRc[i].left, _legRc[i].top, _legRc[i].right, _legRc[i].bottom);
		}
	}
}

void panda::showExplosion()
{
	if (_isDie && _exploNum != 3) {
		_pandaExplosionImg->frameRender(getMemDC(), _x, _y, _exploFrameX, 0);
	}
	else if(_exploNum == 3) {
		_pandaDieImg->frameRender(getMemDC(), _x, _y, _dieFrameX, 0);
	}
}

void panda::afterDeath()
{
	if (_isDie && _exploNum != 3) {
		_exploCount++;
		if (_exploCount % 10 == 0) {
			_exploCount = 0;
			_exploFrameX++;
			if (_exploFrameX > 2) {
				_exploFrameX = 0;
				_exploNum++;
			}
		}
	}
	if (_exploNum == 3) {
		_dieCount++;
		if (_dieCount % 8 == 0) {
			_dieFrameX++;
			if (_dieFrameX > _pandaDieImg->getMaxFrameX()) {
				_dieFrameX = 0;
			}
		}
		if (_dieCount > 50) {
			_isclear = true;
			goDown();
		}
	}
}

void panda::showHpBar()
{
	_backHp->render(getMemDC(), WINSIZEX - _backHp->getWidth() - 50, 30);
	_frontHp->alphaRender(getMemDC(), WINSIZEX - _backHp->getWidth() - 50 + 6, 30 + 4,
		0, 0,
		_hp / MAXHP * _frontHp->getWidth(), _frontHp->getHeight(), 100);
}

void panda::goUp()
{
	_y -= _speed;
}

void panda::goLeft()
{
	_x -= _speed;
}

void panda::goRight()
{
	_x += _speed;
}

void panda::goDown()
{
	_y += 3;
}

void panda::clawCollisionToPlayer()
{
	auto vObjcet3 = _claw->getVObject();
	auto viObject3 = vObjcet3.begin();
	for (viObject3; viObject3 != vObjcet3.end(); ++viObject3)
	{
		if (viObject3->isDeath) continue;
		//������Ʈ ����
		for (size_t i = 0; i < 3; i++)
		{
			_em->monsterCollisionToPlayer(viObject3->ClawRc[i]);
		}
		for (size_t i = 0; i < 2; i++)
		{
			_em->monsterCollisionToPlayer(viObject3->wireRc[i]);
		}
	}
	if (_claw->getPuppet() != nullptr) {
		auto lpuppet = _claw->getPuppet()->getLPuppet();
		for (size_t i = 0; i < 6; i++)
		{
			if (!lpuppet[i].isExist || lpuppet[i].bulletInfo.bulletDeath) continue;
			//���곪��...
			_em->monsterCollisionToPlayer(lpuppet[i].bulletInfo.rc);
		}
	}
}

void panda::checkclawDie()
{
	auto vObject3 = &_claw->getVObject();
	auto viObject3 = vObject3->begin();
	for (viObject3; viObject3 != vObject3->end(); ++viObject3)
	{
		RECT rc = viObject3->ClawRc[1];
		if (_em->pyBoxCollision(rc))
		{
			viObject3->hp--;
		}
		rc = rc = viObject3->wireRc[1];
		if (_em->pyBoxCollision(rc))
		{
			viObject3->hp--;
		}
	}
	//��ģ���� ���굵 Ȯ���ؾ���.
	auto lpuppet = _claw->getPuppet()->getLPuppet();
	for (size_t i = 0; i < 6; i++)
	{
		if (!lpuppet[i].isExist)continue;
		if (_em->pyBoxCollision(lpuppet[i].bulletInfo.rc))
		{
			lpuppet[i].hp--;
		}
	}
}

void panda::initPuppet()
{
	tagthrowedThing thing;
	thing.x = _legRc[2].left + (_legRc[2].right - _legRc[2].left) / 2;
	thing.y = _legRc[2].bottom;
	thing.size = _thingSize;
	thing.rc = RectMakeCenter(thing.x, thing.y, thing.size, thing.size);
	thing.angle = (RND->getFromInTo(30, 160) / 180.0) * PI; //30~160�� ���� ����.
	thing.isdeath = false;
	thing.afterExplosion = false;
	thing.speed = _speed*2;
	thing.gravity = 0;
	thing.imgFrame = 0;
	thing.deathFrame = 0;
	thing.deathCount = 0;
	thing.imgCount = 0;
	if (_thingSize == 40) {
		thing.hp = 1;
		thing.deathimg = IMAGE->addFrameImage("���ͻ��1", "images/enemy/deadExplosion.bmp", 336, 48, 7, 1, true);
		thing.img = chooseImage(RND->getInt(6));
	}
	else { //Ŭ ��,
		thing.hp = 2;
		thing.deathimg = IMAGE->addFrameImage("������Ʈ���1", "images/enemy/deadExplosion.bmp", 896, 128, 7, 1, true);
		thing.img = _bigUnit;
		thing.imgFrame = RND->getInt(5);
	}
	_vThing.push_back(thing);
}

void panda::throwPuppet()
{
	//���� ī��Ʈ���� ������ ���Ϳ� �����ÿ�.
	if (_patternCount % 6 == 0) {
		//��������� �ڵ����� ������ �־���. ��½ÿ��� ��������� �����ӹٲ��� �ȹٲ��� �����ϸ��.
		initPuppet();
	}
}

void panda::puppetupdate()
{
	//��ü�� ���鼭 �۾��� �����Ͻÿ�.
	for (_viThing = _vThing.begin(); _viThing != _vThing.end(); ++_viThing)
	{
		//�׾����� �Ǵ��Ͻÿ�.
		if (_viThing->hp <= 0) {
			_viThing->isdeath = true;
		}
		//��ǥ�� �̵���Ű�ÿ�.
		_viThing->x = _viThing->x + cosf(_viThing->angle) * _viThing->speed;
		_viThing->y = _viThing->y - sinf(_viThing->angle) * _viThing->speed;
		_viThing->y += _viThing->gravity;
		_viThing->gravity += _gravityacc;
		_viThing->rc = RectMakeCenter(_viThing->x, _viThing->y, _viThing->size, _viThing->size);
		//�������� ������Ű�ÿ�. �������ָ�.
		if (!_viThing->isdeath) {
			_viThing->imgCount++;
			if (_viThing->imgCount % 8 == 0 && (_viThing->rc.right - _viThing->rc.left) == 40) {
				_viThing->imgFrame++;
				if (_viThing->imgFrame > _viThing->img->getMaxFrameX()) {
					_viThing->imgFrame = 0;
				}
			}
		}
		//����������� ������Ű�ÿ�.
		else {
			_viThing->deathCount++;
			if (_viThing->deathCount % 5 == 0) {
				_viThing->deathFrame++;
				if (_viThing->deathFrame > _viThing->deathimg->getMaxFrameX()) {
					_viThing->afterExplosion = true;
				}
			}
		}
	}
	//�������̸� �����Ͻÿ�.
	for (_viThing = _vThing.begin(); _viThing != _vThing.end(); )
	{
		if (_viThing->x + _viThing->img->getFrameWidth() / 2 < 0 ||
			_viThing->x - _viThing->img->getFrameWidth() / 2 > WINSIZEX ||
			_viThing->y - _viThing->img->getFrameHeight() / 2 > WINSIZEY)
		{
			_viThing = _vThing.erase(_viThing);
		}
		else {
			++_viThing;
		}
	}
	//���߳����ٸ� �����Ͻÿ�.
	for (_viThing = _vThing.begin(); _viThing != _vThing.end(); )
	{
		if(_viThing->afterExplosion)
			_viThing = _vThing.erase(_viThing);
		else
			++_viThing;
	}
	//�浹�����Ͻÿ�. isdeath�� true��
	for (_viThing = _vThing.begin(); _viThing != _vThing.end(); ++_viThing)
	{
		//�̹��׾����� ��� �浹 ��ŵ
		if (_viThing->isdeath)continue;
		RECT temp;
		//1. �Ѿ˰� �浹
		auto vBullet = _py->getBullet1()->getviperBullet();
		auto viBullet = vBullet->begin();
		for (viBullet; viBullet != vBullet->end(); ++viBullet)
		{
			//�̹� �΋H�� �Ѿ��̸� ��ŵ
			if (viBullet->bulletDeath) continue;
			if (IntersectRect(&temp, &_viThing->rc, &viBullet->rc))
			{
				viBullet->bulletDeath = true;
				_viThing->hp--;
			}
		}
		auto vBullet2 = _py->getBullet2()->getviperDropMissile();
		auto viBullet2 = vBullet2->begin();
		for (viBullet2; viBullet2 != vBullet2->end(); ++viBullet2)
		{
			//�̹� �΋H�� �Ѿ��̸� ��ŵ
			if (viBullet2->bulletDeath) continue;
			if (IntersectRect(&temp, &_viThing->rc, &viBullet2->rc))
			{
				viBullet2->bulletDeath = true;
				_viThing->hp--;
			}
		}
		auto vBullet3 = _py->getBullet3()->getviperDigonalBullet();
		auto viBullet3 = vBullet3->begin();
		for (viBullet3; viBullet3 != vBullet3->end(); ++viBullet3)
		{
			//�̹� �΋H�� �Ѿ��̸� ��ŵ
			if (viBullet3->bulletDeath) continue;
			if (IntersectRect(&temp, &_viThing->rc, &viBullet3->rc))
			{
				viBullet3->bulletDeath = true;
				_viThing->hp--;
			}
		}
		auto vBullet4 = _py->getBullet4()->getviperLaser();
		auto viBullet4 = vBullet4->begin();
		for (viBullet4; viBullet4 != vBullet4->end(); ++viBullet4)
		{
			//�̹� �΋H�� �Ѿ��̸� ��ŵ
			if (viBullet4->hp <= 0 && viBullet4->bulletDeath) continue;
			if (IntersectRect(&temp, &_viThing->rc, &viBullet4->rc))
			{
				viBullet4->hp--;
				_viThing->hp--;
			}
		}

		//2. �ڽ��� �浹
		auto box = _em->getBellBox();
		auto ibox = box.begin();
		for (ibox; ibox != box.end(); ++ibox)
		{
			if (IntersectRect(&temp, ibox->second, &_viThing->rc))
			{
				_viThing->hp--;
			}
		}
		//3. �÷��̾�� �浹
		if (_py->getpyState() != player::PLAYERSTATE::INVINCIBLE &&
			_py->getpyState() != player::PLAYERSTATE::BIG &&
			IntersectRect(&temp, &_viThing->rc, &_py->getRc()))
		{
			_py->setIsDeath(true);
		}
	}

}

void panda::showPuppet()
{
	for (_viThing = _vThing.begin(); _viThing != _vThing.end(); ++_viThing)
	{
		if (!_viThing->isdeath) {
			_viThing->img->frameRender(getMemDC(), _viThing->rc.left - 10, _viThing->rc.top - 10,
				_viThing->imgFrame, 0);
			if (_isDebug) Rectangle(getMemDC(), _viThing->rc.left, _viThing->rc.top, _viThing->rc.right, _viThing->rc.bottom);
		}
		else {
			_viThing->deathimg->frameRender(getMemDC(), _viThing->rc.left - 10, _viThing->rc.top - 10,
				_viThing->deathFrame, 0);
		}
	}
}

image* panda::chooseImage(int snum)
{
	if (_thingSize == 40) {
		switch (snum)
		{
		case 0:
			return _unit1;
		case 1:
			return _unit2;
		case 2:
			return _unit3;
		case 3:
			return _unit4;
		case 4:
			return _unit5;
		case 5:
			return _unit6;
		}
	}
}

void panda::under80()
{
	if (_hp / MAXHP * 100 <= 90 &&
		_hp / MAXHP * 100 > 65) {
		//������ �����ִ� �ð��� �پ��. ������ �� ������ �پ��.
		_clawCount++;
		_untilX = 50;
		_term = 10;
		_framespeed = 5;
		if (_clawCount % 250 == 0) {
			_claw->init(2);
		}
	}
}

void panda::under55()
{
	if (_hp / MAXHP * 100 <= 65 &&
		_hp / MAXHP * 100 > 35) {
		//�������̼�, ���������
		_clawCount++;
		_speed = 6.5f;
		_untilX = 10;
		_framespeed = 4;
		if (_clawCount % 300 == 0) {
			_claw->init(3);
		}
	}
}

void panda::under25()
{
	if (_hp / MAXHP * 100 <= 35) {
		//ȸ���� �� ����, ������ ũ��
		_turnUntil = 180;
		_thingSize = 70;
		_clawCount++;
		if (_clawCount % 700 == 0) {
			_claw->init(1);
		}
		else if (_clawCount % 250 == 0) { 
			_claw->init(2);
		}
		if (_clawCount % 300 == 0) {
			_claw->init(3);
		}
	}
}

void panda::doPattern()
{
	_patternCount++;
	if (_state == PANDASTATE::LEFTHIT || _state == PANDASTATE::RIGHTHIT){
	}
	else {
		switch (_patternNum)
		{
		case 0:
			if (_y > 320) {
				//�ö������ ����
				goUp();
			}
			if (_patternCount == 200) {
				//�� �ö�� �� ��������.
				_state = PANDASTATE::STAY;
				_showShoot = true;
			}
			if (_patternCount == 300) {
				_isStartInvin = false;
				_norFrameX = 0;
				_patternNum = 1;
				_patternCount = 0;
			}
			break;
		case 1:
			if (_patternCount > _term && _patternCount < _term + 60) {
				_state = PANDASTATE::BARK;
				_showShoot = false;
			}
			else if (_patternCount > _term + 60) {
				_state = PANDASTATE::GOLEFT;
				_isLeft = true;
				goLeft();
				if (_x < _untilX) {
					_state = PANDASTATE::STAY;
					_norFrameX = 0;
					_patternNum = 2;
					_patternCount = 0;
				}
			}
			break;
		case 2:
			if (_patternCount > _term && _patternCount < _turnUntil) {
				_state = PANDASTATE::TURN;
				throwPuppet();
			}
			else if (_patternCount == _turnUntil) {
				_state = PANDASTATE::STAY;
				_norFrameX = 0;
				_patternNum = 3;
				_patternCount = 0;
			}
			break;
		case 3:
			if (_patternCount > _term && _patternCount < _term + 60) {
				_state = PANDASTATE::BARK;
			}
			else if (_patternCount > _term + 60) {
				_state = PANDASTATE::GORIGHT;
				_isLeft = false;
				goRight();
				if (_x > 600) {
					_state = PANDASTATE::STAY;
					_norFrameX = 0;
					_patternNum = 4;
					_patternCount = 0;
				}
			}
			break;
		case 4:
			if (_patternCount > 15 && _patternCount < _turnUntil) {
				_state = PANDASTATE::TURN;
				throwPuppet();
			}
			else if (_patternCount == _turnUntil) {
				_state = PANDASTATE::STAY;
				_norFrameX = 0;
				_patternNum = 1;
				_patternCount = 0;
			}
			break;
		}
	}
}

void panda::collision()
{
	//1. bullet to panda
	bullet1collision();
	bullet2collision();
	bullet3collision();
	bullet4collision();
	//2. box to panda
	auto box = _em->getBellBox();
	auto ibox = box.begin();
	for (ibox; ibox != box.end(); ++ibox)
	{
		RECT temp;
		//�ǰ� ���� ���̴� ���� ���� : �������°� �ƴҶ��� ������
		if (!_isInvincible && IntersectRect(&temp, ibox->second, &_bodyRc))
		{
			if (!_dontChangeHitFrame) {
				_isHit = true;
			}
			_isInvincible = true;
			_hp--;
		}
	}
	//3. panda to player
	RECT temp;
	//����
	if (_py->getpyState()!=player::PLAYERSTATE::INVINCIBLE && 
		_py->getpyState() != player::PLAYERSTATE::BIG &&
		!_duckOff && IntersectRect(&temp, &_py->getRc(), &_duckRc)) {
		_py->setIsDeath(true);
	}
	//�Ӹ�
	if (_py->getpyState() != player::PLAYERSTATE::INVINCIBLE && 
		_py->getpyState() != player::PLAYERSTATE::BIG &&
		!_headOff && IntersectRect(&temp, &_py->getRc(), &_headRc)) {
		_py->setIsDeath(true);
	}
	//��
	if (_py->getpyState() != player::PLAYERSTATE::INVINCIBLE && 
		_py->getpyState() != player::PLAYERSTATE::BIG &&
		IntersectRect(&temp, &_py->getRc(), &_bodyRc)) {
		_py->setIsDeath(true);
	}
	//����
	if (!_leftArmOff) {
		for (size_t i = 0; i < 3; i++)
		{
			if (_py->getpyState() != player::PLAYERSTATE::INVINCIBLE && 
				_py->getpyState() != player::PLAYERSTATE::BIG &&
				IntersectRect(&temp, &_py->getRc(), &_leftArmRc[i])) {
				_py->setIsDeath(true);
			}
		}
	}
	//������
	if (!_rightArmOff) {
		for (size_t i = 0; i < 3; i++)
		{
			if (_py->getpyState() != player::PLAYERSTATE::INVINCIBLE && 
				_py->getpyState() != player::PLAYERSTATE::BIG &&
				IntersectRect(&temp, &_py->getRc(), &_rightArmRc[i])) {
				_py->setIsDeath(true);
			}
		}
	}
	//�㸮
	if (_py->getpyState() != player::PLAYERSTATE::INVINCIBLE && 
		_py->getpyState() != player::PLAYERSTATE::BIG &&
		IntersectRect(&temp, &_py->getRc(), &_waistRC)) {
		_py->setIsDeath(true);
	}
	//�ٸ�
	for (size_t i = 0; i < 3; i++)
	{
		if (_py->getpyState() != player::PLAYERSTATE::INVINCIBLE && 
			_py->getpyState() != player::PLAYERSTATE::BIG &&
			IntersectRect(&temp, &_py->getRc(), &_legRc[i])) {
			_py->setIsDeath(true);
		}
	}
}

void panda::bullet1collision()
{
	auto vBullet = _py->getBullet1()->getviperBullet();
	auto viBullet = vBullet->begin();
	for (viBullet; viBullet != vBullet->end(); ++viBullet)
	{
		RECT temp;
		//������ ����
		if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_duckRc))
		{
			viBullet->bulletDeath = true;
			if (!_dontChangeHitFrame) {
				_isHit = true;
			}
			if (!_isStartInvin) {
				_hp -= 2;
			}
		}
		//�Ӹ�
		if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_headRc))
		{
			viBullet->bulletDeath = true;
			if (!_dontChangeHitFrame) {
				_isHit = true;
			}
			if (!_isStartInvin) {
				_hp -= 2;
			}
		}
		//��
		if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_bodyRc))
		{
			viBullet->bulletDeath = true;
			if (!_dontChangeHitFrame) {
				_isHit = true;
			}
			if (!_isStartInvin) {
				_hp -= 2;
			}
		}
		//����
		for (size_t i = 0; i < 3; i++)
		{
			if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_leftArmRc[i]))
			{
				viBullet->bulletDeath = true;
				if (!_dontChangeHitFrame) {
					_isHit = true;
				}
				if (!_isStartInvin) {
					_hp -= 2;
				}
			}
		}
		//������
		for (size_t i = 0; i < 3; i++)
		{
			if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_rightArmRc[i]))
			{
				viBullet->bulletDeath = true;
				if (!_dontChangeHitFrame) {
					_isHit = true;
				}
				if (!_isStartInvin) {
					_hp -= 2;
				}
			}
		}
		//�㸮
		if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_waistRC))
		{
			viBullet->bulletDeath = true;
			if (!_dontChangeHitFrame) {
				_isHit = true;
			}
			if (!_isStartInvin) {
				_hp -= 2;
			}
		}
		//�ٸ�
		for (size_t i = 0; i < 3; i++)
		{
			if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_legRc[i]))
			{
				viBullet->bulletDeath = true;
				if (!_dontChangeHitFrame) {
					_isHit = true;
				}
				if (!_isStartInvin) {
					_hp -= 2;
				}
			}
		}
	}
}

void panda::bullet2collision()
{
	auto vBullet = _py->getBullet2()->getviperDropMissile();
	auto viBullet = vBullet->begin();
	for (viBullet; viBullet != vBullet->end(); ++viBullet)
	{
		RECT temp;
		//������ ����
		if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_duckRc))
		{
			viBullet->bulletDeath = true;
			if (!_dontChangeHitFrame) {
				_isHit = true;
			}
			if (!_isStartInvin) {
				_hp -= 2;
			}
		}
		//�Ӹ�
		if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_headRc))
		{
			viBullet->bulletDeath = true;
			if (!_dontChangeHitFrame) {
				_isHit = true;
			}
			if (!_isStartInvin) {
				_hp -= 2;
			}
		}
		//��
		if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_bodyRc))
		{
			viBullet->bulletDeath = true;
			if (!_dontChangeHitFrame) {
				_isHit = true;
			}
			if (!_isStartInvin) {
				_hp -= 2;
			}
		}
		//����
		for (size_t i = 0; i < 3; i++)
		{
			if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_leftArmRc[i]))
			{
				viBullet->bulletDeath = true;
				if (!_dontChangeHitFrame) {
					_isHit = true;
				}
				if (!_isStartInvin) {
					_hp -= 2;
				}
			}
		}
		//������
		for (size_t i = 0; i < 3; i++)
		{
			if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_rightArmRc[i]))
			{
				viBullet->bulletDeath = true;
				if (!_dontChangeHitFrame) {
					_isHit = true;
				}
				if (!_isStartInvin) {
					_hp -= 2;
				}
			}
		}
		//�㸮
		if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_waistRC))
		{
			viBullet->bulletDeath = true;
			if (!_dontChangeHitFrame) {
				_isHit = true;
			}
			if (!_isStartInvin) {
				_hp -= 2;
			}
		}
		//�ٸ�
		for (size_t i = 0; i < 3; i++)
		{
			if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_legRc[i]))
			{
				viBullet->bulletDeath = true;
				if (!_dontChangeHitFrame) {
					_isHit = true;
				}
				if (!_isStartInvin) {
					_hp -= 2;
				}
			}
		}
	}
}

void panda::bullet3collision()
{
	auto vBullet = _py->getBullet3()->getviperDigonalBullet();
	auto viBullet = vBullet->begin();
	for (viBullet; viBullet != vBullet->end(); ++viBullet)
	{
		RECT temp;
		//������ ����
		if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_duckRc))
		{
			viBullet->bulletDeath = true;
			if (!_dontChangeHitFrame) {
				_isHit = true;
			}
			if (!_isStartInvin) {
				_hp -= 2;
			}
		}
		//�Ӹ�
		if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_headRc))
		{
			viBullet->bulletDeath = true;
			if (!_dontChangeHitFrame) {
				_isHit = true;
			}
			if (!_isStartInvin) {
				_hp -= 2;
			}
		}
		//��
		if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_bodyRc))
		{
			viBullet->bulletDeath = true;
			if (!_dontChangeHitFrame) {
				_isHit = true;
			}
			if (!_isStartInvin) {
				_hp -= 2;
			}
		}
		//����
		for (size_t i = 0; i < 3; i++)
		{
			if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_leftArmRc[i]))
			{
				viBullet->bulletDeath = true;
				if (!_dontChangeHitFrame) {
					_isHit = true;
				}
				if (!_isStartInvin) {
					_hp -= 2;
				}
			}
		}
		//������
		for (size_t i = 0; i < 3; i++)
		{
			if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_rightArmRc[i]))
			{
				viBullet->bulletDeath = true;
				if (!_dontChangeHitFrame) {
					_isHit = true;
				}
				if (!_isStartInvin) {
					_hp -= 2;
				}
			}
		}
		//�㸮
		if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_waistRC))
		{
			viBullet->bulletDeath = true;
			if (!_dontChangeHitFrame) {
				_isHit = true;
			}
			if (!_isStartInvin) {
				_hp -= 2;
			}
		}
		//�ٸ�
		for (size_t i = 0; i < 3; i++)
		{
			if (!viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_legRc[i]))
			{
				viBullet->bulletDeath = true;
				if (!_dontChangeHitFrame) {
					_isHit = true;
				}
				if (!_isStartInvin) {
					_hp -= 2;
				}
			}
		}
	}
}

void panda::bullet4collision()
{
	auto vBullet = _py->getBullet4()->getviperLaser();
	auto viBullet = vBullet->begin();
	for (viBullet; viBullet != vBullet->end(); ++viBullet)
	{
		RECT temp;
		//������ ����
		if (viBullet->hp > 0 && !viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_duckRc))
		{
			viBullet->hp--;
			if (!_dontChangeHitFrame) {
				_isHit = true;
			}
			if (!_isStartInvin) {
				_hp -= 2;
			}
		}
		//�Ӹ�
		if (viBullet->hp > 0 && !viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_headRc))
		{
			viBullet->hp--;
			if (!_dontChangeHitFrame) {
				_isHit = true;
			}
			if (!_isStartInvin) {
				_hp -= 2;
			}
		}
		//��
		if (viBullet->hp > 0 && !viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_bodyRc))
		{
			viBullet->hp--;
			if (!_dontChangeHitFrame) {
				_isHit = true;
			}
			if (!_isStartInvin) {
				_hp -= 2;
			}
		}
		//����
		for (size_t i = 0; i < 3; i++)
		{
			if (viBullet->hp > 0 && !viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_leftArmRc[i]))
			{
				viBullet->hp--;
				if (!_dontChangeHitFrame) {
					_isHit = true;
				}
				if (!_isStartInvin) {
					_hp -= 2;
				}
			}
		}
		//������
		for (size_t i = 0; i < 3; i++)
		{
			if (viBullet->hp > 0 && !viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_rightArmRc[i]))
			{
				viBullet->hp--;
				if (!_dontChangeHitFrame) {
					_isHit = true;
				}
				if (!_isStartInvin) {
					_hp -= 2;
				}
			}
		}
		//�㸮
		if (viBullet->hp > 0 && !viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_waistRC))
		{
			viBullet->hp--;
			if (!_dontChangeHitFrame) {
				_isHit = true;
			}
			if (!_isStartInvin) {
				_hp -= 2;
			}
		}
		//�ٸ�
		for (size_t i = 0; i < 3; i++)
		{
			if (viBullet->hp > 0 && !viBullet->bulletDeath && IntersectRect(&temp, &viBullet->rc, &_legRc[i]))
			{
				viBullet->hp--;
				if (!_dontChangeHitFrame) {
					_isHit = true;
				}
				if (!_isStartInvin) {
					_hp -= 2;
				}
			}
		}
	}
}

void panda::hitAndInvinAndDeathCheck()
{
	/*isHit�� �����Ӽ������� ������ ��*/
	//5ī��Ʈ �� ��������
	if (_isInvincible) {
		_invinCount++;
		if (_invinCount % 8 == 0)
		{
			_invinCount = 0;
			_isInvincible = false;
		}
	}

	if (_isHit) {
		_isHit = false;
		//ȸ�����̰ų� ¢���� �´�������������� �ʰڴ�.
		_dontChangeHitFrame = true;
		if (_state != PANDASTATE::BARK && _state != PANDASTATE::TURN && _state != PANDASTATE::STAY)
		{
			if (_isLeft) {
				_state = PANDASTATE::LEFTHIT;
				_norFrameX = 0;
				_norFrameY = 4;
				_norCount = 0;
			}
			else {
				_state = PANDASTATE::RIGHTHIT;
				_norFrameX = 2;
				_norFrameY = 5;
				_norCount = 0;
			}
		}		
	}
	if (_dontChangeHitFrame) {
		_hitCount++;
		if (_hitCount % 40 == 0) {
			_dontChangeHitFrame = false;
		}
	}

	if (_hp <= 0) {
		_isDie = true;
		_py->setPlayerInvincible();
		_dieCount = 0;
		_dieFrameX = 0;
		_exploCount = 0;
	}
}

void panda::startPurpleEffect()
{
	if (_isPurbleBellEffect)
	{
		_viThing = _vThing.begin();
		for (_viThing; _viThing != _vThing.end(); ++_viThing)
		{
			_pu->init(_viThing->x, _viThing->y, 0);
			_viThing->isdeath = true;
		}


		_isPurbleBellEffect = false;
	}
}
