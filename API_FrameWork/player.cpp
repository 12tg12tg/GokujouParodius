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
	_imageP1 = IMAGE->addFrameImage("바이퍼", "images/player/viper.bmp", 330, 48, 5, 1, true);
	_imageP2 = IMAGE->addFrameImage("바이퍼불꽃", "images/player/viperfire.bmp", 48, 21, 2, 1, true);
	_imagenewstart = IMAGE->addImage("새시작", "images/player/player1start.bmp", 192, 87, true);
	_viverdeathimg = IMAGE->addFrameImage("바이퍼사망", "images/player/viperdeath.bmp", 480, 45, 5, 1, true);
	_verlaserImg = IMAGE->addFrameImage("바이퍼세로레이저", "images/player/viperverticallaser.bmp", 102, 579, 2, 1, true);
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
	//블릿관련
	_shootdelay = 15;
	_viperBullet = new viperBullet;
	_viperMissile = new viperDropMissile;
	_viperDigonalBullet = new viperDigonalBullet;
	_viperLaser = new viperLaser;

	//bell관련
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




	//테스트설정
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
	//폭발이 깔리도록 출력
	showBlueExplosion();
	//캐릭터관련
	printPlayer();
	_viperBullet->render();
	_viperMissile->render();
	_viperDigonalBullet->render();
	_viperLaser->render();
	//레이저
	showLaser();
	//빅
	showBigger();
	//메가폰
	showmegaphone();
	//사망
	showafterdeath();
	//치트
	cheetMode();
	//if (_isDeath) {
	//	TextOut(getMemDC(), _x, _y, "사망", lstrlen("사망"));
	//}
}

void player::playerGradeInit()
{
	//강화조건 초기화
	_powerUpNum = _allPower;
	_needforSpeedUp = 1; //변화
	_isMaxSpeed = false;
	_needforMissile = 2; //변화
	_isMaxMissile = false;
	_needforDouble = 3; // 고정
	_isMaxDouble = false;
	_needforLaser = 4;	// 고정
	_isMaxLaser = false;

	//강화능력치 초기화
	_isMissleOn = false;
	_dropdelay = 40;
	_isDoubleOn = false;
	_shootdelay = 15;
	_isLaserOn = false;
	_laserdelay = 20;
	/*
		여태강화된 능력치는 플레이어 사망시 자동으로 init()에서 초기화된다.
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
			//여태먹은 파워업의 절반 환불.
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
	//무적상태일때와 샷금지상태일때 발사금지
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
	//세로레이저강화 상태이며, 현재 레이저가 발동중이지 않으면
	if (_isVerticalLaser && !_verLaserOn) {
		//A 입력 시 바로 온
 		if (InputManager->isStayKeyDown('A')) {
			_verLaserOn = true;
			_laserCount--;
			//레이저좌표 여기서 설정(한번만 설정)
			_verlaserImg->setX(_x + 300);
			_verlaserImg->setY(_y- _verlaserImg->getFrameHeight()/2);
			//전달
			_verlaserRect = RectMake(_verlaserImg->getX()+10, _verlaserImg->getY(),
				_verlaserImg->getFrameWidth()-20, _verlaserImg->getFrameHeight());
			_enemyManager->insertRcVector("바이퍼세로레이저", &_verlaserRect);
			_bell->insertAttackRect("바이퍼세로레이저", &_verlaserRect);
			if (_laserCount == 0) {
				_isVerticalLaser = false;
				_isBellOn = false;
				_laserCount = 2;
			}
		}
	}
	//레이저온일때 카운트 증가
	if (_verLaserOn) {
		_laserTimer++;
		//400카운트가 지낫으면,
		if (_laserTimer % 350 == 0) {
			_laserTimer = 0;
			_verLaserOn = false;
			//레이저박스에서삭제
			_enemyManager->deleteRcVector("바이퍼세로레이저");
			_bell->deleteAttackRect("바이퍼세로레이저");
		}
	}
	//프레임관리
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
		//축소조건
		if (_greenCount > 500) {
			_plusSize--;
			_imageP1->frameRender(getMemDC(), _x - _plusSize, _y - _plusSize, _plusSize * 2);
			_imageP2->frameRender(getMemDC(), _x - _plusSize - _imageP2->getFrameWidth() - _plusSize * 2,
				_y - _plusSize + 15, _plusSize * 2);
		}
		//종료시점이 아니라면 계속 커지다가 일정수준에서 멈추기.
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
		_enemyManager->insertRcVector("빅사이즈플레이어", &_bigPlayerRect);
		_bell->insertAttackRect("빅사이즈플레이어", &_bigPlayerRect);
		_powerUp->insertAdditionalRc("빅사이즈플레이어", &_bigPlayerRect);
	}
	//종료조건
	if (_plusSize == 0) {
		_isGreenEffect = false;
		_enemyManager->deleteRcVector("빅사이즈플레이어");
		_bell->deleteAttackRect("빅사이즈플레이어");
		_powerUp->deleteAdditionalRc("빅사이즈플레이어");
		_greenCount = 0;
		_plusSize = 1;
		_isBellOn = false;
		_state = PLAYERSTATE::NORMAL;
	}
}

void player::initWhiteEffect()
{
	_iMegaphon = IMAGE->addImage("메가폰", "images/item/megaphone.bmp", 42, 42, true);
	_iMent1 = IMAGE->addImage("멘트1", "images/item/ment1.bmp", 500, 42, true);
	_iMent2 = IMAGE->addImage("멘트2", "images/item/ment2.bmp", 860, 42, true);
	_iMent3 = IMAGE->addImage("멘트3", "images/item/ment3.bmp", 350, 42, true);
	_iMent4 = IMAGE->addImage("멘트4", "images/item/ment4.bmp", 390, 42, true);
	_iMent5 = IMAGE->addImage("멘트5", "images/item/ment5.bmp", 700, 42, true);
	_iMent6 = IMAGE->addImage("멘트6", "images/item/ment6.bmp", 280, 42, true);
	_iMent7 = IMAGE->addImage("멘트7", "images/item/ment7.bmp", 200, 42, true);
	_iMent8 = IMAGE->addImage("멘트8", "images/item/ment8.bmp", 800, 42, true);
	_iMent9 = IMAGE->addImage("멘트9", "images/item/ment9.bmp", 150, 42, true);
	_megaphoneCount=0;
	_shortCount=0;
	_isWhiteEffect = false;
	_mentOn = false;
	_mentNum = 0;
}

void player::megaphoneTimer() //update
{
	if (_isWhiteEffect) {
		//타이머계속증가시키고 샷금지상태로바꾸고 스페이스바눌리면 랜덤멘트생성
		_megaphoneCount++;
		_megaphoneRect = RectMake(_x + _imageP1->getFrameWidth()+3,
			_y + _imageP1->getFrameHeight() / 2 - _iMegaphon->getHeight() / 2,
			_iMegaphon->getWidth(), _iMegaphon->getHeight());
		_enemyManager->insertRcVector("메가폰", &_megaphoneRect);
		_bell->insertAttackRect("메가폰", &_megaphoneRect);
		_state = PLAYERSTATE::CANTSHOT;
		if (!_mentOn && InputManager->isOnceKeyDown(VK_SPACE)) {
			_mentOn = true;
			int temp = _mentNum;
			while(_mentNum == temp) {
				_mentNum = RND->getInt(9) + 1;
			}			
		}
		//새멘트 번호가 결정됬다면, 사각형만들고, map으로 보내기
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
			_enemyManager->insertRcVector("멘트", &_mentRect);
			_bell->insertAttackRect("멘트", &_mentRect);
		}
		//새로뽑기
		if (_shortCount > 200) {
			_mentOn = false;
			_shortCount = 0;
			_enemyManager->deleteRcVector("멘트");
			_bell->deleteAttackRect("멘트");
		}
		//종료조건
		if (_megaphoneCount > 880) {
			_state = PLAYERSTATE::NORMAL;
			_isWhiteEffect = false;
			_mentOn = false;
			_shortCount = 0;
			_megaphoneCount = 0;
			_mentNum = 0;
			_isBellOn = false;
			_enemyManager->deleteRcVector("메가폰");
			_enemyManager->deleteRcVector("멘트");
			_bell->deleteAttackRect("메가폰");
			_bell->deleteAttackRect("멘트");
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
	if (InputManager->isOnceKeyDown(0x31))  //1번 스피드
	{
		if (!_isMaxSpeed && _powerUpNum >= _needforSpeedUp) {
			_powerUpNum -= _needforSpeedUp;
			speedUp();
		}
	}
	if (InputManager->isOnceKeyDown(0x32))  //2번 낙하미사일
	{
		if (!_isMaxMissile && _powerUpNum >= _needforMissile) {
			_powerUpNum -= _needforMissile;
			addMissile();
		}
	}
	if (InputManager->isOnceKeyDown(0x33))  //3번 대각선미사일
	{
		if (!_isMaxDouble && _powerUpNum >= _needforDouble) {
			_powerUpNum -= _needforDouble;
			addDouble();
		}
	}
	if(InputManager->isOnceKeyDown(0x34)) //4번 레이저
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
	//평타에 낙하미사일추가
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
	//init에서 자동으로 스피드 따운시키니 상관없어보임.
}

void player::resetMissile()
{
}

void player::resetDouble()
{
	_isDoubleOn = false;
	_shootdelay = 15;
	_needforDouble = 3; // 고정
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
	_iBlueExplosion = IMAGE->addFrameImage("파랑폭발", "images/item/blueexplosion.bmp", 240, 120, 2, 1, true);
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
		//타이머계속증가시키고 일정크기까지확대
		//딱한번만(폭발효과얻엇을때) 지금위치저장.
		if (_blueExCount == 0) {
			_nowX = _x;
			_nowY = _y;
		}
		//카운트계속증가
		_blueExCount++;
		//사각형재설정
		_explosionRc = RectMake(_nowX - _ExplusSize, _nowY - _ExplusSize,
			_iBlueExplosion->getFrameWidth() + _ExplusSize * 2,
			_iBlueExplosion->getFrameHeight() + _ExplusSize * 2);
		//적에게 사각형정보전달
		_enemyManager->insertRcVector("파랑폭발", &_explosionRc);
		//종료조건
		if (_blueExCount > 150) {
			_isBlueEffect = false;
			_enemyManager->deleteRcVector("파랑폭발");
			initBlueEffect();
		}
	}
	
}

void player::showBlueExplosion()
{
	if (_isBlueEffect) {
		//최대치까지 계속증가
		if (_ExplusSize < _ExMaxPlusSize)
		{
			_iBlueExplosion->setFrameX(0);
			_iBlueExplosion->frameRender(getMemDC(), _nowX - _ExplusSize, _nowY - _ExplusSize, _ExplusSize * 2);
			_ExplusSize += _ExAccNum;
			_ExAccNum+=0.4;
		}
		//최대치도달시 최대치로만 출력인데, 프레임 왓다갓다
		else {
			//3카운트마다 한번씩
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




