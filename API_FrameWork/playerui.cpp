#include "framework.h"
#include "playerui.h"
#include "player.h"
playerui::playerui(){}

playerui::~playerui(){}

HRESULT playerui::init()
{
	_number = IMAGE->addFrameImage("����", "images/player/number.bmp", 240, 24, 10, 1, true);
	_smallpower = IMAGE->addFrameImage("�����Ŀ�", "images/player/itemforui.bmp", 128, 32, 4, 1, true);
	_life = IMAGE->addImage("���","images/player/life.bmp", 24, 21, true);
	_bellskill = IMAGE->addFrameImage("����ų", "images/player/�����ʾƷ�.bmp", 192, 48, 4, 1, true);
	_gradeUp = IMAGE->addFrameImage("��ȭâ", "images/player/��ȭâ.bmp", 792, 144, 3, 4, true);
	_bellgauage = IMAGE->addFrameImage("��������", "images/player/��������.bmp", 288, 210, 8, 1, true);
	return S_OK;
}

void playerui::release()
{
}

void playerui::update()
{
	yellbellsetting();
	speedUpsetting();
	missileUpsetting();
	doubleUpsetting();
	laserUpsetting();
	bellskillsetting();
}

void playerui::render()
{
	//���
	int life = _py->getLife();
	if (life < 0) {
		life = 0;
	}
	for (size_t i = 0; i < life; i++)
	{
		_life->render(getMemDC(), 50 + 30*i, 10);
	}
	//����ų(�Ķ�, �������� ǥ��)
	_bellskill->frameRender(getMemDC(), WINSIZEX - 70, WINSIZEY - 90, bellframe, 0);
	//��ȭâ(���� �Ŀ����� �°� ��ȭ���� ���
	_gradeUp->frameRender(getMemDC(), 5, WINSIZEY - 76, speedUpFrame, 0);
	_gradeUp->frameRender(getMemDC(), 5, WINSIZEY - 76, missileFrame, 1);
	_gradeUp->frameRender(getMemDC(), 5, WINSIZEY - 76, doubleFrame, 2);
	_gradeUp->frameRender(getMemDC(), 5, WINSIZEY - 76, laserFrame, 3);
	//�����Ŀ�ǥ��
	_smallpower->frameRender(getMemDC(), 280, WINSIZEY - 76);
	showPowerUpNum();
	//�����������
	_bellgauage->frameRender(getMemDC(), 0, 0, _yellframe, 0);
}

void playerui::yellbellsetting()
{
	if (_py->getYellBell() >= 7) {
		_yellframeCount++;
		//���ڱ���
		if (_yellframeCount % 8 == 0) {
			if (_yellframe == 7) {
				_yellframe = 0;
			}
			else {
				_yellframe = 7;
			}
		}
		//1�����
		if (_yellframeCount > 100) {
			_yellframeCount = 0;
			_yellframe = 0;
			_py->setLife(_py->getLife() + 1);
			_py->setYellBell(_py->getYellBell() - 7);
		}
	}
	else {
		_yellframe = _py->getYellBell();
	}
}

void playerui::speedUpsetting()
{
	if (_py->getisMaxspeed()) {
		speedUpFrame = 2;
	}
	else if (_py->getPowerUpNum() >= _py->getneedforSpeedUp()) {
		speedUpFrame = 1;
	}
	else {
		speedUpFrame = 0;
	}
}

void playerui::missileUpsetting()
{
	if (_py->getisMaxmissile()) {
		missileFrame = 2;
	}
	else if (_py->getPowerUpNum() >= _py->getneedforMissile()) {
		missileFrame = 1;
	}
	else {
		missileFrame = 0;
	}
}

void playerui::doubleUpsetting()
{
	if (_py->getisMaxDouble()) {
		doubleFrame = 2;
	}
	else if (_py->getPowerUpNum() >= _py->getneedforDouble()) {
		doubleFrame = 1;
	}
	else {
		doubleFrame = 0;
	}
}

void playerui::laserUpsetting()
{
	if (_py->getisMaxLaser()) {
		laserFrame = 2;
	}
	else if (_py->getPowerUpNum() >= _py->getneedforLaser()) {
		laserFrame = 1;
	}
	else {
		laserFrame = 0;
	}
}

void playerui::bellskillsetting()
{
	if (_py->getIsBlueReady()) {
		bellframe = 3;
	}
	else if (_py->getIsRedReady()) {
		if (_py->getRedRemainNum() == 2)
			bellframe = 2;
		else if (_py->getRedRemainNum() == 1)
			bellframe = 1;
	}
	else {
		bellframe = 0;
	}
}

void playerui::showPowerUpNum()
{
	int num = _py->getPowerUpNum();
	float startX = 320;
	float startY = WINSIZEY - 73;
	//���ڸ� �� �� ��,
	if (num / 10 == 0) {
		_number->frameRender(getMemDC(), startX, startY, num, 0);
	}
	//���ڸ� �� �� ��,
	else if (num / 100 == 0)
	{
		_number->frameRender(getMemDC(), startX, startY, num/10, 0);
		_number->frameRender(getMemDC(), startX+25, startY, num%10, 0);
	}
	else {
		_number->frameRender(getMemDC(), startX, startY, num / 100, 0);
		_number->frameRender(getMemDC(), startX + 25, startY, (num % 100) /10, 0);
		_number->frameRender(getMemDC(), startX + 50, startY, (num % 100)%10, 0);
	}
}
