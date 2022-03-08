#pragma once
#include "enemyObject.h"
#include "bulletClasses.h"
class player;
class bell;
class powerUp;
///////////////////////////////////////////
class oEagle1 : public enemyObject
{
private:
	enum class EAGLESTATE
	{
		NORMAL,
		BEATTACKED,
		DOATTACK
	};
private:
	struct tagEagle1
	{
		tagObject objectInfo;
		image* faceImg;
		int faceFrameX;
		image* topImg;
		int topFrameX;
		EAGLESTATE state;
		bool isUp;
		float updownspeed;
		int attackcount;
	};
private:
	vector<tagEagle1> _vObject;
	vector<tagEagle1>::iterator _viObject;
	eagle1Bullet* _ebul;
public:
	oEagle1();
	~oEagle1();

	HRESULT init(float x, float y);
	void release();
	void update(player* py, bell* bl, powerUp* pu);
	void render();

	void attack(tagEagle1& eagle);
	void move(tagEagle1& eagle);
	
	vector<tagEagle1>& getVObject() { return _vObject; }
	eagle1Bullet* getEagle1Bullet() { return _ebul; }

	void changeStateInvinOrNormal(vector<tagEagle1>::iterator iter);

};
///////////////////////////////////////////
class oEagle2 : public enemyObject
{
private:
	enum class EAGLESTATE
	{
		NORMAL,
		BEATTACKED,
		DOATTACK
	};
private:
	struct tagEagle2
	{
		tagObject objectInfo;
		image* faceImg;
		int faceFrameX;
		image* topImg;
		int topFrameX;
		int topframeCount;
		EAGLESTATE state;
		bool isUp;
		float updownspeed;
		int attackcount;
		int attackNum;
		int shootY;
	};
private:
	vector<tagEagle2> _vObject;
	vector<tagEagle2>::iterator _viObject;
	eagle2Bullet* _ebul;
public:
	oEagle2();
	~oEagle2();

	HRESULT init(float x, float y);
	void release();
	void update(player* py, bell* bl, powerUp* pu);
	void render();

	void attack(tagEagle2& eagle);
	void move(tagEagle2& eagle);

	vector<tagEagle2>& getVObject() { return _vObject; }
	eagle2Bullet* getEagle2Bullet() { return _ebul; }

	void changeStateInvinOrNormal(vector<tagEagle2>::iterator iter);

};
///////////////////////////////////////////
class oclaw : public enemyObject
{
private:
	enum class CLAWSTATE
	{
		NORMAL,
		WIDE,
		GRAP
	};
	enum class MOVESTATE
	{
		GOLEFT,
		GORIGHT,
		STAY
	};
private:
	struct tagClaw
	{
		CLAWSTATE clawstate;
		image* clawImg;
		image* wireImg;
		int clawFrameX;
		int wireLength;
		float x;
		float centerX;
		float y;
		float speed;
		int moveCount;
		int hp;
		int deathcount;
		bool isDeath;
		int deathFrame;
		bool afterExplosion;
		int goDownCount;

		int patternNum;
		RECT wireRc[2];						//���̾Ʈ
		RECT ClawRc[3];				//���Է�Ʈ����
		

		puppet::tagpuppet* myPuppet;
		bool hasdoll;
	};
private:
	vector<tagClaw> _vObject;					//claw ����ü ��� ��� ����
	vector<tagClaw>::iterator _viObject;

	puppet* _pp;

public:
	oclaw();
	~oclaw();

	HRESULT init(int patternNum);
	void specailInit();
	void release();
	void update(player* py, bell* bl, powerUp* pu);
	void render();

	void checkDie(tagClaw& claw);
	void goLeft(tagClaw& claw);
	void goRight(tagClaw& claw);
	void goDown(tagClaw& claw); //���̱����.
	void goUp(tagClaw& claw);

	void pattern1(tagClaw& claw); //�������̰� �տ��� ������
	void pattern2(tagClaw& claw); //�����ʿ��� ��������
	void pattern3(tagClaw& claw); //���ʿ��� ���������� ���鼭 �߾ӿ� ����߸��� ��.
	void pattern4(tagClaw& claw); //���������� �ʰ� �ָ��� ������
	void pattern5(tagClaw& claw); //1�� ������ ���������� ����
	void pattern6(tagClaw& claw); //���������
	void changeClawState(tagClaw& claw, int snum);	//���Ի��¿� �浹���ڸ� �ٲ���.
	void setRcs(tagClaw& claw, int snum);

	void grapRandomDoll(tagClaw& claw);
	puppet* getPuppet() {return _pp;}
	vector<tagClaw>& getVObject() { return _vObject; }
};
