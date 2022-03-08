#pragma once
#include "gameNode.h"
#include "objectClasses.h"
#define MAXHP 500.0
class player;
class enemyManager;
class bell;
class PowerUp;
class panda : public gameNode
{
private:
	struct tagthrowedThing
	{
		RECT rc;
		int hp;
		image* img;
		image* deathimg;
		int imgFrame;
		int imgCount;
		int deathFrame;
		int deathCount;
		float x;
		float y;		//중심의 x, y
		int size;
		float angle;
		bool isdeath;
		bool afterExplosion;
		float speed;
		float gravity;
	};
	enum class PANDASTATE
	{
		STAY,
		BARK,
		TURN,
		GOLEFT,
		GORIGHT,
		LEFTHIT,
		RIGHTHIT
	};
private:
	//외부 인스턴스
	player* _py;
	enemyManager* _em;
	bell* _bl;
	powerUp* _pu;
private:
	image* _unit1;
	image* _unit2;
	image* _unit3;
	image* _unit4;
	image* _unit5;
	image* _unit6;
	image* _bigUnit;

	vector<tagthrowedThing> _vThing;
	vector<tagthrowedThing>::iterator _viThing;

	oclaw* _claw;
private:
	image* _frontHp;
	image* _backHp;
	image* _shoot;
	bool _showShoot;
	int _showShootCount;

	image* _pandaImg;
	image* _pandaDieImg;
	image* _pandaExplosionImg;	
	PANDASTATE _state;

	bool _isDie;
	bool _isInvincible;	//bell효과로부터 지속피해방지하기위한 무적변수
	int _invinCount;		//무적을 풀기위한 count 변수
	bool _isHit;		//맞았을 때 맞은 이미지 프레임을 돌리기 위한 변수
	bool _dontChangeHitFrame;	//hit쿨타임(hit이 무분별하게 true가되면, 프레임출력이 겹침.)
	int _hitCount;				//hit을 다시 활성화시키기위한 count

	bool _isStartInvin;
	bool _isLeft;

	int _norFrameX;
	int _norFrameY;
	int _startFrameX;
	int _maxFrameX;
	int _norCount;		//보통상태 프레임카운트

	int _patternCount;

	int _dieFrameX;
	int _dieCount;		//사망상태 프레임카운트
	int _exploFrameX;
	int _exploCount;	//폭발 프레임 카운트
	int _exploNum;		//폭발횟수

	//패턴부르기
	int _clawCount;


	float _x;
	float _y;


	int _hp;
	int _patternNum;

	int _isclear;

	//패턴난이도관련												난이도가오를수록
	int _term;			//state바뀌는 간격						점점짧아짐
	float _speed;		//판다 이동거리							점점증가.
	int _framespeed;	//프레임 바뀌는 %연산에 쓰이는 숫자		점점줄어듬.
	int _turnUntil;		//회전하는 시간							점점늘어남.
	float _untilX;		//보스가 다가오는 목표지점 x좌표
	float _gravityacc;		//중력가속도									점점줄어들기
	int _thingSize;		//던지는퍼펫 충돌박스크기					한단계커짐. (40 -> 80)

	//충돌박스 ON/OFF
	RECT _duckRc;
	RECT _headRc;
	RECT _bodyRc;
	RECT _leftArmRc[3];
	RECT _rightArmRc[3];
	RECT _waistRC;
	RECT _legRc[3];
	bool _duckOff;
	bool _headOff;
	bool _leftArmOff;
	bool _rightArmOff;

	//퍼플벨
	bool _isPurbleBellEffect;

	bool _start;
	bool _isDebug = false;
public:
	panda();
	~panda();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);
	
	//판다의 상태 및 이미지 관련.
	void setNorFrame();
	void setHitBox();
	void showPanda();
	void showExplosion();
	void afterDeath();
	void showHpBar();

	//이동관련
	void goUp();
	void goLeft();
	void goRight();
	void goDown();

	//난이도관련
	void clawCollisionToPlayer();
	void checkclawDie();
	void under80();
	void under55();
	void under25();

	//퍼펫관련
	void initPuppet();
	void throwPuppet();
	void puppetupdate();
	void showPuppet();
	image* chooseImage(int snum);

	//bool변수 관련
	void setStart(bool start) {	_start = start;	}
	bool getStart() {	return _start;	}
	bool getIsClear() { return _isclear; }
	
	//판다의 패턴관련
	void doPattern();
	void collision();
	void bullet1collision();
	void bullet2collision();
	void bullet3collision();
	void bullet4collision();
	void hitAndInvinAndDeathCheck();

	//보라종효과
	void setPurpleItem() { _isPurbleBellEffect = true; }
	void startPurpleEffect();

	//디버그와 링커
	void setDebug(bool isdebug) {
		_isDebug = isdebug; 
		_claw->setdebug(_isDebug);
		_claw->getPuppet()->setIsDebug(_isDebug);
	}
	void setPlayerMemoryLink(player* py) { _py = py; }
	void setEnemyManagerMemoryLink(enemyManager* em) { _em = em; }
	void setBellMemoryLink(bell* bl) { _bl = bl; }
	void setPowerUpMemoryLink(powerUp* pu) { _pu = pu; }
};

