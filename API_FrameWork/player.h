#pragma once
#include "gameNode.h"
#include "bulletClasses.h"
class enemyManager;
class bell;
class powerUp;
class player : public gameNode
{
public:
	enum class PLAYERSTATE
	{
		INVINCIBLE,
		NORMAL,
		CANTSHOT,
		BIG
	};
	enum class NOWBELL
	{
		NONE,
		RED,
		WHITE,
		BLUE
	};
private:
	enemyManager* _enemyManager;
	bell* _bell;
	powerUp* _powerUp;
	viperBullet* _viperBullet;
	viperDropMissile* _viperMissile;
	viperDigonalBullet* _viperDigonalBullet;
	viperLaser* _viperLaser;


	//����������
	image* _imageP1;
	image* _imageP2;
	image* _imagenewstart;
	image* _viverdeathimg;
	RECT _rcP;
	float _x;
	float _y;
	float _speed;
	int _startcount;
	int _framecount;
	int _shootcount;
	bool _isUp;
	bool _isDown;
	bool _isDeath;
	int _deathCount;
	int _deathFrameX;
	bool _isAfterExplosion;
	bool _newStart;
	PLAYERSTATE _state;

	//bell��ȭ
	bool _isBellOn; //����, ȭ��Ʈ.
	// red
	bool _isVerticalLaser;
	bool _verLaserOn;
	int _laserFrameCount;
	int _laserTimer;
	int _laserCount;
	RECT _verlaserRect;
	image* _verlaserImg;
	// green
	bool _isGreenEffect;
	int _greenCount;
	int _maxPlusSize;
	int _plusSize;
	RECT _bigPlayerRect;
	//	while
	image* _iMegaphon;
	image* _iMent1;
	image* _iMent2;
	image* _iMent3;
	image* _iMent4;
	image* _iMent5;
	image* _iMent6;
	image* _iMent7;
	image* _iMent8;
	image* _iMent9;
	int _megaphoneCount;
	int _shortCount;
	int _mentNum;
	RECT _megaphoneRect;
	RECT _mentRect;
	bool _isWhiteEffect;
	bool _mentOn;
	// blue
	bool _isblueReady;
	image* _iBlueExplosion;
	int _blueExCount;
	bool _isBlueEffect;
	int _ExplusSize;
	float _ExAccNum;
	int _ExMaxPlusSize;
	int _nowX;
	int _nowY;
	RECT _explosionRc;
	
	//����������
	int _life = 3;
	int _countYelloBell;
	bool _gameOver;
	//-------------
	int _allPower;			//���� �Ŀ���
	int _powerUpNum = 0;	//���� �Ŀ���
	int _shootdelay;
	int _dropdelay;
	//-------------
	int _needforSpeedUp = 1; //��ȭ
	bool _isMaxSpeed;
	//-------------
	int _needforMissile = 2; //��ȭ
	bool _isMissleOn;
	bool _isMaxMissile;
	//-------------
	int  _needforDouble = 3; // ����
	bool _isDoubleOn;
	bool _isMaxDouble;
	//-------------
	int  _needforLaser= 4;	// ����
	int _laserdelay;
	bool _isLaserOn;
	bool _isMaxLaser;
	//-------------

	//����׸��
	bool _isDebug = false;
public:
	player();
	~player();

	HRESULT init();
	void release();
	void update();
	void render();

	//getter&&setter2
	//�����
	int getLife() { return _life; }
	void setLife(int life) { _life = life; }
	int getYellBell() {	return _countYelloBell;	}
	void setYellBell(int yellbell) { _countYelloBell = yellbell; }
	//��ȭâ
	int getPowerUpNum() { return _powerUpNum; }
	void setPowerUpNum(int puNum) {
		_allPower = puNum;
		_powerUpNum = puNum; 
	}
	int getneedforSpeedUp() { return _needforSpeedUp; }
	bool getisMaxspeed() { return _isMaxSpeed; }
	int getneedforMissile() {return _needforMissile;}
	bool getisMaxmissile() { return _isMaxMissile; }
	int getneedforDouble() { return _needforDouble; }
	bool getisMaxDouble() { return _isMaxDouble; }
	int getneedforLaser() { return _needforLaser; }
	bool getisMaxLaser() { return _isMaxLaser; }
	//����ųâ
	bool getIsBlueReady() { return _isblueReady; }
	bool getIsRedReady() { return _isVerticalLaser; }
	int getRedRemainNum() {	return _laserCount;	}

	//getter&setter
	void setEnemyMenegerMemoryLink(enemyManager* em) { _enemyManager = em; }
	void setBellMemoryLink(bell* bl) { _bell = bl; }
	void setPowerUpMemoryLink(powerUp* pu) { _powerUp = pu;	}
	float getX() { return _x; }
	float getY() { return _y; }
	RECT getRc() { return _rcP; }
	void setIsDeath(bool isdeath) { _isDeath = isdeath; }
	PLAYERSTATE getpyState() { return _state; }
	viperBullet* getBullet1() { return _viperBullet; }
	viperDropMissile* getBullet2() { return _viperMissile; }
	viperDigonalBullet* getBullet3() { return _viperDigonalBullet; }
	viperLaser* getBullet4() { return _viperLaser; }

	//��Ȱ �Ǵ� ����
	void start();
	void printPlayer();
	//���
	void afterDeath();
	void showafterdeath();
	bool getGameOver() { return _gameOver; }
	//�⺻����
	void move();
	void giveFrame();
	void shoot();
	//void offInvincibility(); //���������� ���ʿ��ϳ�

	//�÷��̾� ��ȭ����
	void playerGradeInit();
	void inputforgrade();
	void speedUp();
	void addMissile();
	void addDouble();
	void addlaser();
	void resetSpeed();
	void resetMissile();
	void resetDouble();
	void resetlaser();





	//bell��ȭ
	// 	yello
	void plusyellooCount() { _countYelloBell++; }
	//	red
	void setVerticalLaser(){
		if (!_isBellOn) {
			_isVerticalLaser = true;
			_laserCount = 2;
			_isBellOn = true;
		}
	}
	void shootLaser();
	void showLaser();
	// green
	void setGreenEffect() {
		if (!_isBellOn) {
			_isGreenEffect = true;
			_greenCount = 0;
			_isBellOn = true;
		}
	}
	void gettingBigger();
	void showBigger();
	//	white
	void setMegaphone() {
		if (!_isBellOn) {
			_isWhiteEffect = true;
			_isBellOn = true;
		}
	}
	void initWhiteEffect();
	void megaphoneTimer();
	void showmegaphone();
	//	blue
	void setBlueExplosion() { 
		if (!_isBellOn) {
			_isblueReady = true;
			_isBellOn = true;
		}
	}//_isBlueEffect = true;	}
	void initBlueEffect();
	void blueExplosionTimer();
	void showBlueExplosion();


	//������� ȣ��� ����
	void setPlayerInvincible() { _state = PLAYERSTATE::INVINCIBLE; }


	//ġƮ��
	void cheetMode();
	//�����on/off
	void setDebug(bool isDebug)
	{
		_isDebug = isDebug;
		_viperBullet->setIsDebug(isDebug);
		_viperMissile->setIsDebug(isDebug);
		_viperDigonalBullet->setIsDebug(isDebug);
		_viperLaser->setIsDebug(isDebug);
	}
};

