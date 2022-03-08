#pragma once
#include "gameNode.h"
struct tagEnemy
{
	image* imageE;
	RECT rcE;
	float x;
	float y;
	float speed;
	int hpE;
	int count;
	bool isDeathE;
	bool afterExplosion;
	int deathcount;
	int deathFrame;
	int framecount;
	int framex;
	bool goUp;
	int targetX;
	int targetY;
	int patternNum;
	float angle;
};

class enemyUnit : public gameNode
{
protected:
	vector<tagEnemy> _vEnemy;
	vector<tagEnemy>::iterator _viEnemy;
	bool _isDebug = false;
private:
	image* death1;
	image* death2;

public:
	enemyUnit();
	~enemyUnit();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);


	bool showExplosion(float x, float y, int frameX, int frameY, int deathNum); //폭발끝나면 true 반환
	vector<tagEnemy>& getVEnemy() { return _vEnemy; }

	void setdebug(bool isDebug) { _isDebug = isDebug; }
};

