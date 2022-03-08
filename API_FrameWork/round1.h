#pragma once
#include"gameNode.h"
#include"player.h"
#include"playerui.h"
#include"enemyManager.h"
#include "bell.h"
#include "powerUp.h"
#include "screenManager.h"
#include "panda.h"

#define MAXCAMERA 6632

class round1 : gameNode
{
private:
	player* _player;
	enemyManager* _em;
	bell* _bl;
	powerUp* _pu;
	panda* _pd;

	image* _bg1;
	image* _bgFast;
	image* _bgSlow;
	image* _longbgimg;

	screenManager* _sm;

	int _offsetX;
	int _slowOffsetX;
	int _fastOffsetX;

	bool _cameraStop;
	int _camera;
	int _endcount;

	bool _test;
public:
	round1();
	~round1();

	HRESULT init(player* py, enemyManager* em, bell* bl, powerUp* pu);
	void release();
	void update();
	void render(/*HDC hdc*/);

	screenManager* getscreenManager() { return _sm; }

	void cheetMode();
	void setDebug(bool isdebug) { _pd->setDebug(isdebug); }
};

