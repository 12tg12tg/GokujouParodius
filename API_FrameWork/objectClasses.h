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
		RECT wireRc[2];						//와이어렉트
		RECT ClawRc[3];				//집게렉트집합
		

		puppet::tagpuppet* myPuppet;
		bool hasdoll;
	};
private:
	vector<tagClaw> _vObject;					//claw 구조체 모두 담는 벡터
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
	void goDown(tagClaw& claw); //줄이길어짐.
	void goUp(tagClaw& claw);

	void pattern1(tagClaw& claw); //위헙적이게 앞에서 가져감
	void pattern2(tagClaw& claw); //오른쪽에서 왼쪽으로
	void pattern3(tagClaw& claw); //왼쪽에서 오른쪽으로 오면서 중앙에 떨어뜨리고 감.
	void pattern4(tagClaw& claw); //위협적이지 않게 멀리서 가져감
	void pattern5(tagClaw& claw); //1과 같은데 오른쪽으로 퇴장
	void pattern6(tagClaw& claw); //스페셜패턴
	void changeClawState(tagClaw& claw, int snum);	//집게상태와 충돌상자를 바꿔줌.
	void setRcs(tagClaw& claw, int snum);

	void grapRandomDoll(tagClaw& claw);
	puppet* getPuppet() {return _pp;}
	vector<tagClaw>& getVObject() { return _vObject; }
};
