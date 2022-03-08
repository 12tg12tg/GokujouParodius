#pragma once
#include "gameNode.h"
#include "round1.h"
class parodius : public gameNode
{
private:
	player* py;
	playerui* pui;
	enemyManager* em;
	bell* bl;
	powerUp* pu;
private:
	round1* r1;
private:
	image* _introbg;
	image* _introTitle;
	image* _pressSpace;
	image* _loading;

	bool _gamestart;
	int _afterloading;
	bool _start;
	int _startcount;
	//--------------
	bool _isloading;
	int _loadingCount;
	//---------------
	bool _playerDie;
	int _countDown;
	int _countcount;
	bool _gameOver;
	int _gameOverCount;
	//---------------
	bool _gameStop;
	bool _gotomain;
	bool _isDebug;
public:
	parodius();
	~parodius();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

	void checkCountDown();
	void showCountDown();

	void showtitle();
	void checktitle();

	void loading();
	void showloading();

	bool getGotoMain() { return _gotomain; }
};

