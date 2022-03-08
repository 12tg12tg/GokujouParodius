#include "framework.h"
#include "player.h"
#include "enemyManager.h"
#include "bell.h"
#include "powerUp.h"
player::player()
{
	_life = 3;
	_allPower = 0;
	_gameOver = false;
}

player::~player()
{
}

HRESULT player::init()
{
	playerGradeInit();
	_imageP1 = IMAGE->addFrameImage("������", "images/player/viper.bmp", 330, 48, 5, 1, true);
	_imageP2 = IMAGE->addFrameImage("�����ۺҲ�", "images/player/viperfire.bmp", 48, 21, 2, 1, true);
	_imagenewstart = IMAGE->addImage("������", "images/player/player1start.bmp", 192, 87, true);
	_viverdeathimg = IMAGE->addFrameImage("�����ۻ��", "images/player/viperdeath.bmp", 480, 45, 5, 1, true);
	_verlaserImg = IMAGE->addFrameImage("�����ۼ��η�����", "images/player/viperverticallaser.bmp", 102, 579, 2, 1, true);
	_imageP1->setFrameX(2);
	_newStart = true;
	_deathCount = 0;
	_deathFrameX = 0;
	_isDeath = false;
	_isAfterExplosion = false;
	_x = -_imageP1->getFrameWidth();
	_y = WINSIZEY / 2 - _imageP1->getFrameHeight();
	_rcP = RectMake(_x + 10, _y + 13, _imageP1->getFrameWidth() - 20, _imageP1->getFrameHeight() - 23);
	_speed = 3.5f;
	_startcount = 0;
	_framecount = 0;
	_shootcount = 0;
	_isUp = false;
	_isDown = false;
	_state = PLAYERSTATE::INVINCIBLE;
	//������
	_shootdelay = 15;
	_viperBullet = new viperBullet;
	_viperMissile = new viperDropMissile;
	_viperDigonalBullet = new viperDigonalBullet;
	_viperLaser = new viperLaser;

	//bell����
	_isBellOn = false;
	//	red
	_isVerticalLaser = false;
	_verLaserOn = false;
	_laserTimer = 0;
	_laserCount = 2;
	_laserFrameCount = 0;
	//	geen
	_isGreenEffect = false;
	_greenCount = 0;
	_maxPlusSize = 40;
	_plusSize = 1;
	//	while
	initWhiteEffect();
	//	blue
	initBlueEffect();




	//�׽�Ʈ����
	//setVerticalLaser();
	return S_OK;
}

void player::release()
{
	SAFE_DELETE(_viperBullet);
	SAFE_DELETE(_viperMissile);
	SAFE_DELETE(_viperDigonalBullet);
	SAFE_DELETE(_viperLaser);
}

void player::update()
{
	start();
	giveFrame();
	move();
	shootLaser();
	shoot();
	gettingBigger();
	megaphoneTimer();
	blueExplosionTimer();
	afterDeath();
	inputforgrade();
	_viperBullet->update();
	_viperMissile->update();
	_viperDigonalBullet->update();
	_viperLaser->update();
}

void player::render()
{
	//������ �򸮵��� ���
	showBlueExplosion();
	//ĳ���Ͱ���
	printPlayer();
	_viperBullet->render();
	_viperMissile->render();
	_viperDigonalBullet->render();
	_viperLaser->render();
	//������
	showLaser();
	//��
	showBigger();
	//�ް���
	showmegaphone();
	//���
	showafterdeath();
	//ġƮ
	cheetMode();
	//if (_isDeath) {
	//	TextOut(getMemDC(), _x, _y, "���", lstrlen("���"));
	//}
}

void player::playerGradeInit()
{
	//��ȭ���� �ʱ�ȭ
	_powerUpNum = _allPower;
	_needforSpeedUp = 1; //��ȭ
	_isMaxSpeed = false;
	_needforMissile = 2; //��ȭ
	_isMaxMissile = false;
	_needforDouble = 3; // ����
	_isMaxDouble = false;
	_needforLaser = 4;	// ����
	_isMaxLaser = false;

	//��ȭ�ɷ�ġ �ʱ�ȭ
	_isMissleOn = false;
	_dropdelay = 40;
	_isDoubleOn = false;
	_shootdelay = 15;
	_isLaserOn = false;
	_laserdelay = 20;
	/*
		���°�ȭ�� �ɷ�ġ�� �÷��̾� ����� �ڵ����� init()���� �ʱ�ȭ�ȴ�.
	*/
}

void player::start()
{
	if (_newStart) {
		_startcount++;
		if (_x > 0 && (InputManager->isStayKeyDown(VK_UP) ||
			InputManager->isStayKeyDown(VK_DOWN) ||
			InputManager->isStayKeyDown(VK_RIGHT))){
		}
		else {
			_x += 2;
		}
		_rcP = RectMake(_x + 10, _y + 13, _imageP1->getFrameWidth() - 20, _imageP1->getFrameHeight() - 23);
		if (_startcount == 150) {
			_newStart = false;
			_state = PLAYERSTATE::NORMAL;
		}
	}
}

void player::printPlayer()
{
	if (!_isDeath) {
		if (_isDebug) Rectangle(getMemDC(), _rcP.left, _rcP.top, _rcP.right, _rcP.bottom);
		if (_startcount < 120) {
			_imagenewstart->render(getMemDC(), _x - _imagenewstart->getWidth() / 3 - 10, _y - _imagenewstart->getHeight() + 10);
			if (_startcount % 5 != 0) {
				_imageP1->frameRender(getMemDC(), _x, _y);
				_imageP2->frameRender(getMemDC(), _x - _imageP2->getFrameWidth(), _y + 15);
			}
		}
		else {
			_imageP1->frameRender(getMemDC(), _x, _y);
			_imageP2->frameRender(getMemDC(), _x - _imageP2->getFrameWidth(), _y + 15);
		}
	}
}

void player::afterDeath()
{
	if (_isDeath) {
		if (_deathCount == 10) {
			_bell->init(_x+100, _y-100);
			_bell->init(_x+50, _y+50);
			_bell->init(_x+100, _y+100);
		}
		_state = PLAYERSTATE::CANTSHOT;
		_enemyManager->emptyRcVector();
		_bell->emptyRcVector();
		_deathCount++;
		if (_deathCount % 8 == 0) {
			_deathFrameX++;
		}
		if (_deathFrameX > _viverdeathimg->getMaxFrameX()) {
			_isAfterExplosion = true;
		}
	}
	if (_isAfterExplosion) {
		if (_deathCount > 90) {
			//���¸��� �Ŀ����� ���� ȯ��.
			_allPower /= 2;
			_life--;
			if (_life < 0) {
				_gameOver = true;
			}
			else {
				release();
				init();
			}
		}
	}
}

void player::showafterdeath()
{
	if (_isDeath&&!_isAfterExplosion) {
		_viverdeathimg->frameRender(getMemDC(), _x, _y, _deathFrameX, 0);
	}
}

void player::move()
{
	if (!_isDeath) {
		//if (InputManager->isStayKeyDown(VK_LEFT))
		//{
		//	if (InputManager->isStayKeyDown(VK_DOWN)) {
		//		_x -= _speed;
		//		_y += _speed;
		//		_isUp = false;
		//		_isDown = true;
		//	}
		//	else if (InputManager->isStayKeyDown(VK_UP)) {
		//		_x -= _speed;
		//		_y -= _speed;
		//		_isUp = true;
		//		_isDown = false;
		//	}
		//	else if (InputManager->isStayKeyDown(VK_RIGHT)) {
		//		_isUp = false;
		//		_isDown = false;
		//	}
		//	else {
		//		_x -= _speed;
		//		_isUp = false;
		//		_isDown = false;
		//	}
		//}
		//else if (InputManager->isStayKeyDown(VK_RIGHT))
		//{
		//	if (InputManager->isStayKeyDown(VK_DOWN)) {
		//		_x += _speed;
		//		_y += _speed;
		//		_isUp = false;
		//		_isDown = true;
		//	}
		//	else if (InputManager->isStayKeyDown(VK_UP)) {
		//		_x += _speed;
		//		_y -= _speed;
		//		_isUp = true;
		//		_isDown = false;
		//	}
		//	else {
		//		_x += _speed;
		//	}
		//}
		//else if (InputManager->isStayKeyDown(VK_UP)) {
		//	if (InputManager->isStayKeyDown(VK_DOWN)) {
		//		_isUp = false;
		//		_isDown = false;
		//	}
		//	else {
		//		_y -= _speed;
		//		_isUp = true;
		//		_isDown = false;
		//	}
		//}
		//else if (InputManager->isStayKeyDown(VK_DOWN)) {
		//	_y += _speed;
		//	_isUp = false;
		//	_isDown = true;
		//}
		//if (InputManager->isOnceKeyUp(VK_UP)) {
		//	_isUp = false;
		//	_isDown = false;
		//}
		//else if (InputManager->isOnceKeyUp(VK_DOWN)) {
		//	_isUp = false;
		//	_isDown = false;
		//}
		if (InputManager->isStayKeyDown(VK_UP))
		{
			_y -= _speed;
			_isUp = true;
			_isDown = false;
		}
		if (InputManager->isStayKeyDown(VK_DOWN))
		{
			_y += _speed;
			_isUp = false;
			_isDown = true;
		}
		if (InputManager->isStayKeyDown(VK_LEFT))
		{
			_x -= _speed;
		}
		if (InputManager->isStayKeyDown(VK_RIGHT))
		{
			_x += _speed;
		}
		if (InputManager->isOnceKeyUp(VK_UP))
		{
			_isUp = false;
			_isDown = false;
		}
		if (InputManager->isOnceKeyUp(VK_DOWN))
		{
			_isUp = false;
			_isDown = false;
		}
		if (_x < 0 && !_newStart) {
			_x = 0;
		}
		if (_x + _imageP1->getFrameWidth() > WINSIZEX) {
			_x = WINSIZEX - _imageP1->getFrameWidth();
		}
		if (_y < 0) {
			_y = 0;
		}
		if (_y + _imageP1->getFrameHeight() > WINSIZEY - 20) {
			_y = WINSIZEY - 20 - _imageP1->getFrameHeight();
		}
		_rcP = RectMake(_x + 10, _y + 13, _imageP1->getFrameWidth() - 20, _imageP1->getFrameHeight() - 23);
	}
}

void player::giveFrame()
{
	_framecount++;
	int currntFrame = _imageP1->getFrameX();
	if (_framecount % 6 == 0) {
		_framecount = 0;
		if (_isUp) {
			currntFrame--;
			if (currntFrame < 0) {
				currntFrame = 0;				
			}
		}
		else if (_isDown) {
			currntFrame++;
			if (currntFrame > _imageP1->getMaxFrameX()) {
				currntFrame = _imageP1->getMaxFrameX();
			}
		}
		else {
			if (currntFrame > 2) {
				currntFrame--;
			}
			else if (currntFrame < 2) {
				currntFrame++;
			}
		}
	}
	_imageP1->setFrameX(currntFrame);

	currntFrame = _imageP2->getFrameX();
	if (_framecount % 6 == 0) {
		currntFrame++;
		if (currntFrame > _imageP2->getMaxFrameX()) {
			currntFrame = 0;
		}
	}
	_imageP2->setFrameX(currntFrame);
}

void player::shoot()
{
	//���������϶��� �����������϶� �߻����
	if (_state != PLAYERSTATE::CANTSHOT &&
		_state != PLAYERSTATE::BIG) {
		if (InputManager->isOnceKeyDown(VK_SPACE)) {
			if (_isLaserOn) {
				_viperLaser->fire(_x + _imageP1->getFrameWidth(), _y + _imageP1->getFrameHeight() / 2);
			}
			else {
				_viperBullet->fire(_x + _imageP1->getFrameWidth(), _y + _imageP1->getFrameHeight() / 2);
			}
			if (_isDoubleOn) {
				_viperDigonalBullet->fire(_x + _imageP1->getFrameWidth(), _y + _imageP1->getFrameHeight() / 2);
			}
		}
		if (InputManager->isStayKeyDown(VK_SPACE)) {
			_shootcount++;
			if (_isLaserOn) {
				if (_shootcount % _laserdelay == 0) {
					_viperLaser->fire(_x + _imageP1->getFrameWidth(), _y + _imageP1->getFrameHeight() / 2);
				}
			}
			else {
				if ((_shootcount % _shootdelay == 0)) {
					_viperBullet->fire(_x + _imageP1->getFrameWidth(), _y + _imageP1->getFrameHeight() / 2);
				}
			}
			if (_isMissleOn) {
				if ((_shootcount % _dropdelay == 0)) {
					_viperMissile->fire(_x + _imageP1->getFrameWidth(), _y + _imageP1->getFrameHeight() / 2);
				}
			}
			if (_isDoubleOn) {
				if ((_shootcount % _shootdelay == 0)) {
					_viperDigonalBullet->fire(_x + _imageP1->getFrameWidth(), _y + _imageP1->getFrameHeight() / 2);
				}
			}
		}
	}

}

void player::shootLaser()
{
	//���η�������ȭ �����̸�, ���� �������� �ߵ������� ������
	if (_isVerticalLaser && !_verLaserOn) {
		//A �Է� �� �ٷ� ��
 		if (InputManager->isStayKeyDown('A')) {
			_verLaserOn = true;
			_laserCount--;
			//��������ǥ ���⼭ ����(�ѹ��� ����)
			_verlaserImg->setX(_x + 300);
			_verlaserImg->setY(_y- _verlaserImg->getFrameHeight()/2);
			//����
			_verlaserRect = RectMake(_verlaserImg->getX()+10, _verlaserImg->getY(),
				_verlaserImg->getFrameWidth()-20, _verlaserImg->getFrameHeight());
			_enemyManager->insertRcVector("�����ۼ��η�����", &_verlaserRect);
			_bell->insertAttackRect("�����ۼ��η�����", &_verlaserRect);
			if (_laserCount == 0) {
				_isVerticalLaser = false;
				_isBellOn = false;
				_laserCount = 2;
			}
		}
	}
	//���������϶� ī��Ʈ ����
	if (_verLaserOn) {
		_laserTimer++;
		//400ī��Ʈ�� ��������,
		if (_laserTimer % 350 == 0) {
			_laserTimer = 0;
			_verLaserOn = false;
			//�������ڽ���������
			_enemyManager->deleteRcVector("�����ۼ��η�����");
			_bell->deleteAttackRect("�����ۼ��η�����");
		}
	}
	//�����Ӱ���
	if (_verLaserOn) {
		_laserFrameCount++;
		if (_laserFrameCount % 5 == 0) {
			int currentFrame = _verlaserImg->getFrameX();
			currentFrame++;
			if (currentFrame > _verlaserImg->getMaxFrameX()) {
				currentFrame = 0;
			}
			_verlaserImg->setFrameX(currentFrame);
		}
	}
}

void player::showLaser()
{
	if (_verLaserOn) {
		if (_isDebug) Rectangle(getMemDC(), _verlaserRect.left, _verlaserRect.top, _verlaserRect.right, _verlaserRect.bottom);
		_verlaserImg->frameRender(getMemDC());
	}
}

void player::showBigger()
{
	if (_isGreenEffect) {
		_state = PLAYERSTATE::BIG;
		if(_isDebug)Rectangle(getMemDC(), _bigPlayerRect.left, _bigPlayerRect.top, _bigPlayerRect.right, _bigPlayerRect.bottom);
		_greenCount++;
		//�������
		if (_greenCount > 500) {
			_plusSize--;
			_imageP1->frameRender(getMemDC(), _x - _plusSize, _y - _plusSize, _plusSize * 2);
			_imageP2->frameRender(getMemDC(), _x - _plusSize - _imageP2->getFrameWidth() - _plusSize * 2,
				_y - _plusSize + 15, _plusSize * 2);
		}
		//��������� �ƴ϶�� ��� Ŀ���ٰ� �������ؿ��� ���߱�.
		else {
			if (_plusSize < _maxPlusSize)
			{
				_imageP1->frameRender(getMemDC(), _x - _plusSize, _y - _plusSize, _plusSize * 2);
				_imageP2->frameRender(getMemDC(), _x - _plusSize - _imageP2->getFrameWidth()- _plusSize * 2,
					_y - _plusSize +15, _plusSize * 2);
				_plusSize++;
			}
			else {
				_imageP1->frameRender(getMemDC(), _x - _maxPlusSize, _y - _maxPlusSize, _maxPlusSize * 2);
				_imageP2->frameRender(getMemDC(), _x - _maxPlusSize - _imageP2->getFrameWidth() - _maxPlusSize * 2,
					_y - _maxPlusSize + 15, _maxPlusSize * 2);
			}
		}

	}
}

void player::gettingBigger()
{
	if (_isGreenEffect) {
		_bigPlayerRect = RectMake(_x - _maxPlusSize, _y - _maxPlusSize,
			_imageP1->getFrameWidth() + _maxPlusSize * 2,
			_imageP1->getFrameHeight() + _maxPlusSize * 2);
		_enemyManager->insertRcVector("��������÷��̾�", &_bigPlayerRect);
		_bell->insertAttackRect("��������÷��̾�", &_bigPlayerRect);
		_powerUp->insertAdditionalRc("��������÷��̾�", &_bigPlayerRect);
	}
	//��������
	if (_plusSize == 0) {
		_isGreenEffect = false;
		_enemyManager->deleteRcVector("��������÷��̾�");
		_bell->deleteAttackRect("��������÷��̾�");
		_powerUp->deleteAdditionalRc("��������÷��̾�");
		_greenCount = 0;
		_plusSize = 1;
		_isBellOn = false;
		_state = PLAYERSTATE::NORMAL;
	}
}

void player::initWhiteEffect()
{
	_iMegaphon = IMAGE->addImage("�ް���", "images/item/megaphone.bmp", 42, 42, true);
	_iMent1 = IMAGE->addImage("��Ʈ1", "images/item/ment1.bmp", 500, 42, true);
	_iMent2 = IMAGE->addImage("��Ʈ2", "images/item/ment2.bmp", 860, 42, true);
	_iMent3 = IMAGE->addImage("��Ʈ3", "images/item/ment3.bmp", 350, 42, true);
	_iMent4 = IMAGE->addImage("��Ʈ4", "images/item/ment4.bmp", 390, 42, true);
	_iMent5 = IMAGE->addImage("��Ʈ5", "images/item/ment5.bmp", 700, 42, true);
	_iMent6 = IMAGE->addImage("��Ʈ6", "images/item/ment6.bmp", 280, 42, true);
	_iMent7 = IMAGE->addImage("��Ʈ7", "images/item/ment7.bmp", 200, 42, true);
	_iMent8 = IMAGE->addImage("��Ʈ8", "images/item/ment8.bmp", 800, 42, true);
	_iMent9 = IMAGE->addImage("��Ʈ9", "images/item/ment9.bmp", 150, 42, true);
	_megaphoneCount=0;
	_shortCount=0;
	_isWhiteEffect = false;
	_mentOn = false;
	_mentNum = 0;
}

void player::megaphoneTimer() //update
{
	if (_isWhiteEffect) {
		//Ÿ�̸Ӱ��������Ű�� ���������·ιٲٰ� �����̽��ٴ����� ������Ʈ����
		_megaphoneCount++;
		_megaphoneRect = RectMake(_x + _imageP1->getFrameWidth()+3,
			_y + _imageP1->getFrameHeight() / 2 - _iMegaphon->getHeight() / 2,
			_iMegaphon->getWidth(), _iMegaphon->getHeight());
		_enemyManager->insertRcVector("�ް���", &_megaphoneRect);
		_bell->insertAttackRect("�ް���", &_megaphoneRect);
		_state = PLAYERSTATE::CANTSHOT;
		if (!_mentOn && InputManager->isOnceKeyDown(VK_SPACE)) {
			_mentOn = true;
			int temp = _mentNum;
			while(_mentNum == temp) {
				_mentNum = RND->getInt(9) + 1;
			}			
		}
		//����Ʈ ��ȣ�� ������ٸ�, �簢�������, map���� ������
		if (_mentOn)
		{
			_shortCount++;
			switch (_mentNum)
			{
			case 1:
				_mentRect = RectMake(_megaphoneRect.right + 3, _y + _imageP1->getFrameHeight() / 2 - _iMent1->getHeight() / 2,
					_iMent1->getWidth(), _iMent1->getHeight());
				break;
			case 2:
				_mentRect = RectMake(_megaphoneRect.right + 3, _y + _imageP1->getFrameHeight() / 2 - _iMent2->getHeight() / 2,
					_iMent2->getWidth(), _iMent2->getHeight());
				break;
			case 3:
				_mentRect = RectMake(_megaphoneRect.right + 3, _y + _imageP1->getFrameHeight() / 2 - _iMent3->getHeight() / 2,
					_iMent3->getWidth(), _iMent3->getHeight());
				break;
			case 4:
				_mentRect = RectMake(_megaphoneRect.right + 3, _y + _imageP1->getFrameHeight() / 2 - _iMent4->getHeight() / 2,
					_iMent4->getWidth(), _iMent4->getHeight());
				break;
			case 5:
				_mentRect = RectMake(_megaphoneRect.right + 3, _y + _imageP1->getFrameHeight() / 2 - _iMent5->getHeight() / 2,
					_iMent5->getWidth(), _iMent5->getHeight());
				break;
			case 6:
				_mentRect = RectMake(_megaphoneRect.right + 3, _y + _imageP1->getFrameHeight() / 2 - _iMent6->getHeight() / 2,
					_iMent6->getWidth(), _iMent6->getHeight());
				break;
			case 7:
				_mentRect = RectMake(_megaphoneRect.right + 3, _y + _imageP1->getFrameHeight() / 2 - _iMent7->getHeight() / 2,
					_iMent7->getWidth(), _iMent7->getHeight());
				break;
			case 8:
				_mentRect = RectMake(_megaphoneRect.right + 3, _y + _imageP1->getFrameHeight() / 2 - _iMent8->getHeight() / 2,
					_iMent8->getWidth(), _iMent8->getHeight());
				break;
			case 9:
				_mentRect = RectMake(_megaphoneRect.right + 3, _y + _imageP1->getFrameHeight() / 2 - _iMent9->getHeight() / 2,
					_iMent9->getWidth(), _iMent9->getHeight());
				break;
			}
			if (_isDeath) {
				_megaphoneRect.top += _deathCount * 8;
				_megaphoneRect.bottom += _deathCount * 8;
				_mentRect.top += _deathCount * 8;
				_mentRect.bottom += _deathCount * 8;
			}
			_enemyManager->insertRcVector("��Ʈ", &_mentRect);
			_bell->insertAttackRect("��Ʈ", &_mentRect);
		}
		//���λ̱�
		if (_shortCount > 200) {
			_mentOn = false;
			_shortCount = 0;
			_enemyManager->deleteRcVector("��Ʈ");
			_bell->deleteAttackRect("��Ʈ");
		}
		//��������
		if (_megaphoneCount > 880) {
			_state = PLAYERSTATE::NORMAL;
			_isWhiteEffect = false;
			_mentOn = false;
			_shortCount = 0;
			_megaphoneCount = 0;
			_mentNum = 0;
			_isBellOn = false;
			_enemyManager->deleteRcVector("�ް���");
			_enemyManager->deleteRcVector("��Ʈ");
			_bell->deleteAttackRect("�ް���");
			_bell->deleteAttackRect("��Ʈ");
		}
	}
}

void player::showmegaphone() //render
{
	if (_isWhiteEffect) {
		if (_isDebug) Rectangle(getMemDC(), _megaphoneRect.left, _megaphoneRect.top, _megaphoneRect.right, _megaphoneRect.bottom);
		_iMegaphon->render(getMemDC(), _megaphoneRect.left,	_megaphoneRect.top);
	}
	if (_mentOn) {
		if (_isDebug) Rectangle(getMemDC(), _mentRect.left, _mentRect.top, _mentRect.right, _mentRect.bottom);
		switch (_mentNum)
		{
		case 1:
			_iMent1->render(getMemDC(), _mentRect.left, _mentRect.top);
			break;
		case 2:
			_iMent2->render(getMemDC(), _mentRect.left, _mentRect.top);
			break;
		case 3:
			_iMent3->render(getMemDC(), _mentRect.left, _mentRect.top);
			break;
		case 4:
			_iMent4->render(getMemDC(), _mentRect.left, _mentRect.top);
			break;
		case 5:
			_iMent5->render(getMemDC(), _mentRect.left, _mentRect.top);
			break;
		case 6:
			_iMent6->render(getMemDC(), _mentRect.left, _mentRect.top);
			break;
		case 7:
			_iMent7->render(getMemDC(), _mentRect.left, _mentRect.top);
			break;
		case 8:
			_iMent8->render(getMemDC(), _mentRect.left, _mentRect.top);
			break;
		case 9:
			_iMent9->render(getMemDC(), _mentRect.left, _mentRect.top);
			break;
		}
	}
}

void player::inputforgrade()
{
	if (InputManager->isOnceKeyDown(0x31))  //1�� ���ǵ�
	{
		if (!_isMaxSpeed && _powerUpNum >= _needforSpeedUp) {
			_powerUpNum -= _needforSpeedUp;
			speedUp();
		}
	}
	if (InputManager->isOnceKeyDown(0x32))  //2�� ���Ϲ̻���
	{
		if (!_isMaxMissile && _powerUpNum >= _needforMissile) {
			_powerUpNum -= _needforMissile;
			addMissile();
		}
	}
	if (InputManager->isOnceKeyDown(0x33))  //3�� �밢���̻���
	{
		if (!_isMaxDouble && _powerUpNum >= _needforDouble) {
			_powerUpNum -= _needforDouble;
			addDouble();
		}
	}
	if(InputManager->isOnceKeyDown(0x34)) //4�� ������
	{
		if (!_isMaxLaser && _powerUpNum >= _needforLaser) {
			_powerUpNum -= _needforLaser;
			addlaser();
		}
	}
}


void player::speedUp()
{
	if (_needforSpeedUp == 1) {
		_needforSpeedUp = 2;
		_speed = 5;
	}
	else if (_needforSpeedUp == 2) {
		_needforSpeedUp = 3;
		_speed = 7;
	}
	else if (_needforSpeedUp == 3) {
		_speed = 9;
		_isMaxSpeed = true;
	}
}


void player::addMissile()
{
	//��Ÿ�� ���Ϲ̻����߰�
	if (!_isMissleOn) {
		_isMissleOn = true;
		_needforMissile = 3;
	}
	else if (_dropdelay==40) {
		_dropdelay = 20;
		_isMaxMissile = true;
	}
}

void player::addDouble()
{
	if (!_isDoubleOn) {
		_isDoubleOn = true;
		resetlaser();
	}
	else if(_shootdelay==15){
		_shootdelay = 8;
		_isMaxDouble = true;
	}
}

void player::addlaser()
{
	if (!_isLaserOn) {
		_isLaserOn = true;
		resetDouble();
	}
	else if(_laserdelay == 20 ){
		_laserdelay = 8;
		_isMaxLaser = true;
	}

}

void player::resetSpeed()
{
	//init���� �ڵ����� ���ǵ� �����Ű�� ��������.
}

void player::resetMissile()
{
}

void player::resetDouble()
{
	_isDoubleOn = false;
	_shootdelay = 15;
	_needforDouble = 3; // ����
	_isMaxDouble = false;
}

void player::resetlaser()
{
	_isLaserOn = false;
	_laserdelay = 20;
	_needforLaser = 4;
	_isMaxLaser = false;
}

void player::initBlueEffect()
{
	_iBlueExplosion = IMAGE->addFrameImage("�Ķ�����", "images/item/blueexplosion.bmp", 240, 120, 2, 1, true);
	_blueExCount = 0;
	_isblueReady = false;
	_isBlueEffect = false;
	_ExplusSize = -50;
	_ExAccNum = 0;
	_ExMaxPlusSize = 950;
	_nowX = 0;
	_nowY = 0;
}

void player::blueExplosionTimer()
{
	if (_isblueReady) {
		if (InputManager->isOnceKeyDown('A'))
		{
			_isBlueEffect = true;
			_isblueReady = false;
			_isBellOn = false;
		}
	}
	if (_isBlueEffect) {
		//Ÿ�̸Ӱ��������Ű�� ����ũ�����Ȯ��
		//���ѹ���(����ȿ���������) ������ġ����.
		if (_blueExCount == 0) {
			_nowX = _x;
			_nowY = _y;
		}
		//ī��Ʈ�������
		_blueExCount++;
		//�簢���缳��
		_explosionRc = RectMake(_nowX - _ExplusSize, _nowY - _ExplusSize,
			_iBlueExplosion->getFrameWidth() + _ExplusSize * 2,
			_iBlueExplosion->getFrameHeight() + _ExplusSize * 2);
		//������ �簢����������
		_enemyManager->insertRcVector("�Ķ�����", &_explosionRc);
		//��������
		if (_blueExCount > 150) {
			_isBlueEffect = false;
			_enemyManager->deleteRcVector("�Ķ�����");
			initBlueEffect();
		}
	}
	
}

void player::showBlueExplosion()
{
	if (_isBlueEffect) {
		//�ִ�ġ���� �������
		if (_ExplusSize < _ExMaxPlusSize)
		{
			_iBlueExplosion->setFrameX(0);
			_iBlueExplosion->frameRender(getMemDC(), _nowX - _ExplusSize, _nowY - _ExplusSize, _ExplusSize * 2);
			_ExplusSize += _ExAccNum;
			_ExAccNum+=0.4;
		}
		//�ִ�ġ���޽� �ִ�ġ�θ� ����ε�, ������ �Ӵٰ���
		else {
			//3ī��Ʈ���� �ѹ���
			if (_blueExCount % 5 == 0) {
				if (_iBlueExplosion->getFrameX() == 0) {
					_iBlueExplosion->setFrameX(1);
				}
				else {
					_iBlueExplosion->setFrameX(0);
				}
			}
			_iBlueExplosion->frameRender(getMemDC(), _nowX - _ExMaxPlusSize, _nowY - _ExMaxPlusSize, _ExMaxPlusSize * 2);
		}
		if (_isDebug) Rectangle(getMemDC(), _explosionRc.left, _explosionRc.top, _explosionRc.right, _explosionRc.bottom);
	}
}

void player::cheetMode()
{
	if (InputManager->isOnceKeyDown(VK_F9)) {
		_powerUpNum += 10;
	}
	if (InputManager->isOnceKeyDown(VK_F7)) {
		_life++;
	}
}




