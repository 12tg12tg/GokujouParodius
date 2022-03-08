#pragma once
#include "gameNode.h"
class player;
struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float fireX, fireY; //거리계산용 발사위치. 쓸일없어보임.
	float radius;
	float angle;
	float speed;
	bool fire;
	int count;
	int hp;
	bool bulletDeath;
	int bulletDeathFrameX;
	bool afterExpolsion;
};

class bullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	image* _bulExplosion;
	bool _isDebug = false;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);

};

class viperBullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
	
	image* _bulExplosion;
	bool _isDebug = false;
public:
	viperBullet();
	~viperBullet();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

	void fire(float x, float y);
	void move();
	vector<tagBullet>* getviperBullet() { return &_vBullet; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
////////////////////////////////////////////////////////////////////

class eagle1Bullet : public gameNode
{
public:
	struct tagEagle1Bullet {
		tagBullet bulletInfo;
		int frameX;
	};
private:
	vector<tagEagle1Bullet> _vEagleBullet;
	vector<tagEagle1Bullet>::iterator _viEagleBullet;

	bool _isDebug = false;
public:
	eagle1Bullet();
	~eagle1Bullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y);
	void move();
	vector<tagEagle1Bullet>* getVEagleBullet() { return &_vEagleBullet; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
////////////////////////////////////////////////////////////////////

class eagle2Bullet : public gameNode
{
public:
	struct tagEagle2Bullet {
		tagBullet bulletInfo;
		int frameX;
	};
private:
	vector<tagEagle2Bullet> _vEagleBullet;
	vector<tagEagle2Bullet>::iterator _viEagleBullet;

	bool _isDebug = false;
public:
	eagle2Bullet();
	~eagle2Bullet();

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y);
	void move();
	void giveFrameAndHitBox(vector<tagEagle2Bullet>::iterator bullet);
	vector<tagEagle2Bullet>* getVEagleBullet() { return &_vEagleBullet; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
////////////////////////////////////////////////////////////////////

class puppet : public gameNode
{
public:
	struct tagpuppet
	{
		tagBullet bulletInfo;
		bool hasMother;
		bool isExist;
		int motherMax;
		int remainMother;
		int hp;
		bool specialChange;
	};
private:
	tagpuppet _puppet[6];
	bool _isDebug = false;
public:
	puppet();
	~puppet();

	HRESULT init();
	void release();
	void update(player* py);
	void render();

	void indexInit(int index);
	void setX(tagpuppet& puppet, float x); //x좌표 바꾸면서 바로 RECT도 재조정
	float getX(tagpuppet& puppet) { return puppet.bulletInfo.x; }
	void setY(tagpuppet& puppet, float y); //x좌표 바꾸면서 바로 RECT도 재조정
	float getY(tagpuppet& puppet) { return puppet.bulletInfo.y; }
	void checkMother();
	void fall();
	void afterDeath();
	void deathCheck();
	void plyaerBulletCollision(player* py);
	tagpuppet* givePuppet(float x, float y);
	tagpuppet* getLPuppet() { return _puppet; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
////////////////////////////////////////////////////////////////////
class viperDropMissile : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	image* _bulExplosion;
	bool _isDebug = false;
public:
	viperDropMissile();
	~viperDropMissile();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

	void fire(float x, float y);
	void move();
	vector<tagBullet>* getviperDropMissile() { return &_vBullet; }

	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
////////////////////////////////////////////////////////////////////
class viperDigonalBullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	image* _bulExplosion;
	bool _isDebug = false;
public:
	viperDigonalBullet();
	~viperDigonalBullet();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

	void fire(float x, float y);
	void move();

	vector<tagBullet>* getviperDigonalBullet() { return &_vBullet; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};
////////////////////////////////////////////////////////////////////
class viperLaser : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	image* _bulExplosion;
	bool _isDebug = false;
public:
	viperLaser();
	~viperLaser();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

	void fire(float x, float y);
	void move();

	vector<tagBullet>* getviperLaser() { return &_vBullet; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};