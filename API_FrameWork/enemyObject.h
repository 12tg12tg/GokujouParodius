#pragma once
#include "gameNode.h"
class enemyObject : public gameNode
{
protected:
	struct tagObject
	{
		image* image;
		int frameX;
		int framecount;
		RECT rc;

		float x;
		float y;
		float speed;
		int hp;
		int movecount;
		bool isDeath;
		bool isHit;
		bool isinvincible;
		int isinvincibleCount;
		bool afterExplosion;
		int deathcount;
		int deathFrame;

		int targetX;
		int targetY;
	};

	bool _isDebug = false;
private:
	image* death1;
	image* death2;

public:
	enemyObject();
	~enemyObject();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

	bool showExplosion(float x, float y, int frameX, int frameY, int deathNum); //폭발끝나면 true 반환
	void setdebug(bool isDebug) { _isDebug = isDebug; }
};

