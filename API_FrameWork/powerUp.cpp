#include "framework.h"
#include "powerUp.h"
#include "player.h"
#include "panda.h"

powerUp::powerUp(){}

powerUp::~powerUp(){}

HRESULT powerUp::init(float x, float y, int colorNum, bool makeFour)
{
	if (!makeFour) {
		tagPowerUp powerUp;
		powerUp.img = IMAGE->addFrameImage("파워업", "images/item/powerup.bmp", 192, 96, 4, 2, true);
		powerUp.color = (POWERUPCOLOR)colorNum;
		powerUp.frameX = 0;
		powerUp.frameY = colorNum;
		powerUp.frameCount = 0;
		powerUp.x = x;
		powerUp.y = y;
		powerUp.rc = RectMake(powerUp.x, powerUp.y,
			powerUp.img->getFrameWidth(), powerUp.img->getFrameWidth());
		_vPowerUp.push_back(powerUp);
	}
	else {
		tagPowerUp powerUp;
		int startx = x+10;
		int starty = y;
		for (size_t i = 0; i < 2; i++)
		{
			for (size_t j = 0; j < 2; j++)
			{
				powerUp.img = IMAGE->addFrameImage("파워업", "images/item/powerup.bmp", 192, 96, 4, 2, true);
				powerUp.color = (POWERUPCOLOR)colorNum;
				powerUp.frameX = 0;
				powerUp.frameY = colorNum;
				powerUp.frameCount = 0;
				powerUp.x = startx + 100 * j;
				powerUp.y = starty + 100 * i;
				powerUp.rc = RectMake(powerUp.x, powerUp.y,
					powerUp.img->getFrameWidth(), powerUp.img->getFrameWidth());
				_vPowerUp.push_back(powerUp);
			}
		}
	}
	return S_OK;
}

void powerUp::release(){}

void powerUp::update()
{
	for (_viPowerUp = _vPowerUp.begin(); _viPowerUp != _vPowerUp.end(); )
	{
		//프레임주기 및 이동
		giveFrmae(*_viPowerUp);
		move(*_viPowerUp);
		//플레이어RC와 충돌시 사라짐
		RECT temp;
		if (IntersectRect(&temp, &_viPowerUp->rc, &_py->getRc())) {
			_py->setPowerUpNum(_py->getPowerUpNum()+ (int)_viPowerUp->color + 1);
			_viPowerUp = _vPowerUp.erase(_viPowerUp);
		}
		else
			++_viPowerUp;
	}
	for (_viPowerUp = _vPowerUp.begin(); _viPowerUp != _vPowerUp.end(); )
	{
		//범위벗어나면 삭제
		RECT temp;
		if (_viPowerUp->x+_viPowerUp->img->getFrameWidth()<0) {
			_viPowerUp = _vPowerUp.erase(_viPowerUp);
		}
		else
			++_viPowerUp;
	}
	checkBoxCollision();
}

void powerUp::render()
{
	for (_viPowerUp = _vPowerUp.begin(); _viPowerUp != _vPowerUp.end(); ++_viPowerUp)
	{
		if (_isDebug) Rectangle(getMemDC(), _viPowerUp->rc.left, _viPowerUp->rc.top, _viPowerUp->rc.right, _viPowerUp->rc.bottom);
		_viPowerUp->img->frameRender(getMemDC(),
			_viPowerUp->x, _viPowerUp->y, _viPowerUp->frameX, _viPowerUp->frameY);
	}
}

void powerUp::giveFrmae(tagPowerUp& powerup)
{
	powerup.frameCount++;
	if (powerup.frameCount % 8 == 0) {
		int currentFrame = powerup.frameX;
		currentFrame++;
		if (currentFrame > powerup.img->getMaxFrameX()) {
			currentFrame = 0;
		}
		powerup.frameX = currentFrame;
		powerup.img->setFrameX(powerup.frameX);
	}
}

void powerUp::move(tagPowerUp& powerup)
{
	if (!_pd->getStart()) {
		powerup.x -= 2;
		powerup.rc = RectMake(powerup.x, powerup.y,
			powerup.img->getFrameWidth(), powerup.img->getFrameWidth());
	}
}

void powerUp::checkBoxCollision()
{
	//커졋을때쳐먹는거
	RECT temp;
	_icheckBox = _checkBox.begin();
	for (_icheckBox; _icheckBox != _checkBox.end(); ++_icheckBox)
	{
		for (_viPowerUp = _vPowerUp.begin(); _viPowerUp != _vPowerUp.end();)
		{
			if (IntersectRect(&temp, &_viPowerUp->rc, _icheckBox->second))
			{
				_py->setPowerUpNum(_py->getPowerUpNum() + (int)_viPowerUp->color);
				_viPowerUp = _vPowerUp.erase(_viPowerUp);
			}
			else
				++_viPowerUp;
		}
	}
}
