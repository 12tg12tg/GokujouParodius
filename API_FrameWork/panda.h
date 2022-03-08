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
		float y;		//�߽��� x, y
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
	//�ܺ� �ν��Ͻ�
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
	bool _isInvincible;	//bellȿ���κ��� �������ع����ϱ����� ��������
	int _invinCount;		//������ Ǯ������ count ����
	bool _isHit;		//�¾��� �� ���� �̹��� �������� ������ ���� ����
	bool _dontChangeHitFrame;	//hit��Ÿ��(hit�� ���к��ϰ� true���Ǹ�, ����������� ��ħ.)
	int _hitCount;				//hit�� �ٽ� Ȱ��ȭ��Ű������ count

	bool _isStartInvin;
	bool _isLeft;

	int _norFrameX;
	int _norFrameY;
	int _startFrameX;
	int _maxFrameX;
	int _norCount;		//������� ������ī��Ʈ

	int _patternCount;

	int _dieFrameX;
	int _dieCount;		//������� ������ī��Ʈ
	int _exploFrameX;
	int _exploCount;	//���� ������ ī��Ʈ
	int _exploNum;		//����Ƚ��

	//���Ϻθ���
	int _clawCount;


	float _x;
	float _y;


	int _hp;
	int _patternNum;

	int _isclear;

	//���ϳ��̵�����												���̵�����������
	int _term;			//state�ٲ�� ����						����ª����
	float _speed;		//�Ǵ� �̵��Ÿ�							��������.
	int _framespeed;	//������ �ٲ�� %���꿡 ���̴� ����		�����پ��.
	int _turnUntil;		//ȸ���ϴ� �ð�							�����þ.
	float _untilX;		//������ �ٰ����� ��ǥ���� x��ǥ
	float _gravityacc;		//�߷°��ӵ�									�����پ���
	int _thingSize;		//���������� �浹�ڽ�ũ��					�Ѵܰ�Ŀ��. (40 -> 80)

	//�浹�ڽ� ON/OFF
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

	//���ú�
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
	
	//�Ǵ��� ���� �� �̹��� ����.
	void setNorFrame();
	void setHitBox();
	void showPanda();
	void showExplosion();
	void afterDeath();
	void showHpBar();

	//�̵�����
	void goUp();
	void goLeft();
	void goRight();
	void goDown();

	//���̵�����
	void clawCollisionToPlayer();
	void checkclawDie();
	void under80();
	void under55();
	void under25();

	//�������
	void initPuppet();
	void throwPuppet();
	void puppetupdate();
	void showPuppet();
	image* chooseImage(int snum);

	//bool���� ����
	void setStart(bool start) {	_start = start;	}
	bool getStart() {	return _start;	}
	bool getIsClear() { return _isclear; }
	
	//�Ǵ��� ���ϰ���
	void doPattern();
	void collision();
	void bullet1collision();
	void bullet2collision();
	void bullet3collision();
	void bullet4collision();
	void hitAndInvinAndDeathCheck();

	//������ȿ��
	void setPurpleItem() { _isPurbleBellEffect = true; }
	void startPurpleEffect();

	//����׿� ��Ŀ
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

