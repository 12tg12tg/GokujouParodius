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
	//�»�� �����������
	int _yellframeCount;
	int _yellframe;
	//���ϴ� ��ȭâ
	int speedUpFrame;
	int missileFrame;
	int doubleFrame;
	int laserFrame;
	//���ϴ� ����ųâ
	int bellframe;

public:
	playerui();
	~playerui();

	HRESULT init();
	void release();
	void update();
	void render();

	//����������Ӽ���(+��������)
	void yellbellsetting();
	//���ǵ尭ȭ ������ ����
	void speedUpsetting();
	//�̻��� ������ ����
	void missileUpsetting();
	//���� ������ ����
	void doubleUpsetting();
	//������ ������ ����
	void laserUpsetting();
	//���ϴ� ����ų ����
	void bellskillsetting();
	//���������۰������
	void showPowerUpNum();

	void setPlayerMemoryLink(player* py) { _py = py; }
};

