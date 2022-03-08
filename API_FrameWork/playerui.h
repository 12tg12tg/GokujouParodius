#pragma once
#include "gameNode.h"
class player;
class playerui : public gameNode
{
private:
	player* _py;
private:
	image* _number;
	image* _smallpower;
	image* _life;
	image* _bellskill;
	image* _gradeUp;
	image* _bellgauage;
	//좌상단 노랑벨게이지
	int _yellframeCount;
	int _yellframe;
	//좌하단 강화창
	int speedUpFrame;
	int missileFrame;
	int doubleFrame;
	int laserFrame;
	//우하단 벨스킬창
	int bellframe;

public:
	playerui();
	~playerui();

	HRESULT init();
	void release();
	void update();
	void render();

	//노랑별프레임세팅(+목숨업기능)
	void yellbellsetting();
	//스피드강화 프레임 세팅
	void speedUpsetting();
	//미사일 프레임 세팅
	void missileUpsetting();
	//더블 프레임 세팅
	void doubleUpsetting();
	//레이저 프레임 세팅
	void laserUpsetting();
	//우하단 벨스킬 세팅
	void bellskillsetting();
	//보유아이템개수출력
	void showPowerUpNum();

	void setPlayerMemoryLink(player* py) { _py = py; }
};

