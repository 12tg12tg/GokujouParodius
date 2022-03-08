#pragma once
#include "gameNode.h"
class player;
class panda;
class powerUp : public gameNode
{
private:
	enum class POWERUPCOLOR
	{
		RED,
		BLUE
	};
	struct tagPowerUp
	{
		image* img;
		int frameX;
		int frameY;
		int frameCount;
		POWERUPCOLOR color;
		RECT rc;
		float x;
		float y;
	};
private:
	vector<tagPowerUp> _vPowerUp;
	vector<tagPowerUp>::iterator _viPowerUp;
	map<const char*, RECT*> _checkBox;
	map<const char*, RECT*>::iterator _icheckBox;

	player* _py;
	panda* _pd;
	bool _isDebug = false;
public:
	powerUp();
	~powerUp();

	HRESULT init(float x, float y, int colorNum = 0, bool makeFour=false);
	void release();
	void update();
	void render(/*HDC hdc*/);

	void giveFrmae(tagPowerUp& powerup);
	void move(tagPowerUp& powerup);

	//충돌상자
	void insertAdditionalRc(const char* name, RECT* box) { _checkBox.insert(map<const char*, RECT*>::value_type(name, box)); }
	void deleteAdditionalRc(const char* name) { _checkBox.erase(name); }
	void checkBoxCollision();

	//디버그나 링커
	void setPlayerMemoryLink(player* py) { _py = py; }
	void setPandaMemoryLink(panda* pd) { _pd = pd; }
	void setdebug(bool isDebug) { _isDebug = isDebug; }
};

