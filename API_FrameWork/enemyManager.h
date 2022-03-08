#pragma once
#include "enemyClasses.h"
#include "objectClasses.h"
//#include "bulletClasses.h"

class player;
class bell;
class powerUp;
class enemyManager
{
private:
	player* _player;
	bell* _bell;
	powerUp* _powerUp;
	
	bool _isPurbleBellEffect;

	map<const char*, RECT*> additionalAttack;
	map<const char*, RECT*>::iterator iAdditionalAttack; // 추가 공격수단의 충돌체 박스

	eChickin*	_chickin;
	eChick*		_chick;
	eHead1*		_head1;
	eHead2*		_head2;
	eHead3*		_head3;
	eHead4*		_head4;								//몹추가시 ★1
	eHead5*		_head5;
	ePenguin*	_penguin;

	oEagle1*	_eagle1;
	oEagle2*	_eagle2;
	oclaw*		_claw;
public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();
	void setPlayerMemoryLink(player* py) { _player = py; }
	void setPowerUpMemoryLink(powerUp* pu) { _powerUp = pu; }
	void setBellMemoryLink(bell* bl) { _bell = bl; }

	eChickin* getChiKin() { return _chickin; } //round에서 init하기위해 호출될것.
	eChick* getChick() { return _chick; }
	eHead1* getHead1() { return _head1; }
	eHead2* getHead2() { return _head2; }
	eHead3* getHead3() { return _head3; }
	eHead4* getHead4() { return _head4; }
	eHead5* getHead5() { return _head5; }				//몹추가시 ★2
	ePenguin* getPenguin() { return _penguin; }			
	
	oEagle1* getEagle1() { return _eagle1; }
	oEagle2* getEagle2() { return _eagle2; }
	oclaw* getClaw() { return _claw; }

	//플레이어사망관련 충돌
	void checkPlayerdie();
	void checkPlayerdie2();
	void monsterCollisionToPlayer(enemyUnit unit);
	void monsterCollisionToPlayer(RECT objectRc);

	//몬스터사망관련(레이저박스, ...)
	void checkMonsterDie();


	//박스관련 함수
	void insertRcVector(const char* name, RECT* box){additionalAttack.insert(map<const char*, RECT*>::value_type(name, box));}
	void deleteRcVector(const char* name) { additionalAttack.erase(name);}
	void emptyRcVector() { additionalAttack.clear(); }
	void pyBoxCollision(enemyUnit* unit); 
	bool pyBoxCollision(RECT objectRc); //레이저같은 공격기능있는 박스랑 검사.
	map<const char*, RECT*> getBellBox() { return additionalAttack; }

	//퍼플벨 함수
	void setPurpleItem() {_isPurbleBellEffect = true;}
	void startPurpleEffect();
	void purpleEffect(enemyUnit* unit);

	//디버그
	void setDebug(bool isDebug)							//몹추가시 ★3
	{
		_chickin->setdebug(isDebug);
		_chick->setdebug(isDebug);
		_head1->setdebug(isDebug);
		_head2->setdebug(isDebug);
		_head3->setdebug(isDebug);
		_head4->setdebug(isDebug);
		_head5->setdebug(isDebug);
		_penguin->setdebug(isDebug);

		_eagle1->setdebug(isDebug);
		if (_eagle1->getEagle1Bullet() != nullptr) {
			_eagle1->getEagle1Bullet()->setIsDebug(isDebug);
		}
		_eagle2->setdebug(isDebug);
		if (_eagle2->getEagle2Bullet() != nullptr) {
			_eagle2->getEagle2Bullet()->setIsDebug(isDebug);
		}
		_claw->setdebug(isDebug);
		if (_claw->getPuppet() != nullptr) {
			_claw->getPuppet()->setIsDebug(isDebug);
		}
	}
};

