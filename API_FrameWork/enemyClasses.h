#pragma once
#include "enemyUnit.h"
class player;
class bell;
class powerUp;
//////////////////////////////////////////////////////////////
class eChickin : public enemyUnit
{
private:


public:
	eChickin();
	~eChickin();

	HRESULT init(float x, float y);
	void release();
	void update(player* py, bell* bl, powerUp* pu);
	void render(/*HDC hdc*/);
};
//////////////////////////////////////////////////////////////
class eChick : public enemyUnit
{
private:


public:
	eChick();
	~eChick();

	HRESULT init(float x, float y);
	void release();
	void update(player* py, bell* bl, powerUp* pu);
	void render(/*HDC hdc*/);
};
//////////////////////////////////////////////////////////////
class eHead1 : public enemyUnit
{
private:


public:
	eHead1();
	~eHead1();

	HRESULT init(float x, float y);
	void release();
	void update(player* py, bell* bl, powerUp* pu);
	void render(/*HDC hdc*/);
};
//////////////////////////////////////////////////////////////
class eHead2 : public enemyUnit
{
private:


public:
	eHead2();
	~eHead2();

	HRESULT init(float x, float y);
	void release();
	void update(player* py, bell* bl, powerUp* pu);
	void render(/*HDC hdc*/);
};
//////////////////////////////////////////////////////////////
class eHead3 : public enemyUnit
{
private:


public:
	eHead3();
	~eHead3();

	HRESULT init(float x, float y);
	void release();
	void update(player* py, bell* bl, powerUp* pu);
	void render(/*HDC hdc*/);
};
//////////////////////////////////////////////////////////////
class eHead4 : public enemyUnit
{
private:


public:
	eHead4();
	~eHead4();

	HRESULT init(float x, float y);
	void release();
	void update(player* py, bell* bl, powerUp* pu);
	void render(/*HDC hdc*/);
};
//////////////////////////////////////////////////////////////
class eHead5 : public enemyUnit
{
private:


public:
	eHead5();
	~eHead5();

	HRESULT init(float x, float y);
	void release();
	void update(player* py, bell* bl, powerUp* pu);
	void render(/*HDC hdc*/);
};
//////////////////////////////////////////////////////////////
class ePenguin : public enemyUnit
{
private:


public:
	ePenguin();
	~ePenguin();

	HRESULT init(float x, float y, int patternNum);
	void release();
	void update(player* py, bell* bl, powerUp* pu);
	void render(/*HDC hdc*/);

	void pattern1(vector<tagEnemy>::iterator iter);	//대각선오른쪽아래	↘
	void pattern2(vector<tagEnemy>::iterator iter);	//대각선왼쪽아래		↙
	void pattern3(vector<tagEnemy>::iterator iter);	//계속화면팅기며맴돌기 
};