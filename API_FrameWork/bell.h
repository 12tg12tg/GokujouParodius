#pragma once
#include "gameNode.h"
class player;
class enemyManager;
class panda;
class bell : public gameNode
{
private:
	enum class BELLCOLOR
	{
		YELLO = 0,
		BLUE,
		GREEN,
		WHITE,
		PURPLE,
		RED
	};
	struct tagBell
	{
		image* bellImg;
		int frameX;
		int frameY;
		BELLCOLOR color;
		RECT rc;
		float x;
		float y;
		bool isHit;
		bool isinvincible;
		bool isJump;
		int count;
		int frameCount;
		float gravity;
		float jumpPower;
	};
private:
	vector<tagBell> _vBell;
	vector<tagBell>::iterator _viBell;
	map<const char*, RECT*> _checkBox;
	map<const char*, RECT*>::iterator _icheckBox; //레이저, 빅플레이어, 

	player* _py;
	enemyManager* _em;
	panda* _pd;
	bool _isDebug = false;
public:
	bell();
	~bell();

	HRESULT init(float x, float y);
	void release();
	void update();
	void render(/*HDC hdc*/);

	void giveframe(tagBell& bell);
	void collision(tagBell& bell);
	int giveRandomColor();
	void afterHit(tagBell& bell);
	void move(tagBell& bell);
	void ifOutOfRengeRemove();

	//체크박스(레이저, 빅플레이어,..) 관련함수
	void insertAttackRect(const char* name, RECT* box) {
		_checkBox.insert(map<const char*, RECT*>::value_type(name, box)); 
	}
	void deleteAttackRect(const char* name) {
		_checkBox.erase(name);
	}
	void emptyRcVector() { _checkBox.clear(); }
	void checkBoxCollision();

	//디버그나 링커
	void setPlayerMemoryLink(player* py) { _py = py; }
	void setEnemyManagerMemoryLink(enemyManager* em) { _em = em; }
	void setPandaMemoryLink(panda* pd) { _pd = pd; }
	void setdebug(bool isDebug) { _isDebug = isDebug; }
};

