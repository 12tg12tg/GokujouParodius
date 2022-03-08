#include "framework.h"
#include "enemyManager.h"
#include "player.h"
#include "bell.h"
#include "powerUp.h"
/*
    공통                : new, delete, update, render, checkMonsterDie
    유닛 추가시          :  startPurpleEffect함수 내부에 추가. checkPlayerdie,
    오브젝트 추가시      : release(총알때문), checkPlayerdie2(총알까지)
*/
enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
    _chickin = new eChickin;
    _chick = new eChick;
    _head1 = new eHead1;
    _head2 = new eHead2;
    _head3 = new eHead3;
    _head4 = new eHead4;
    _head5 = new eHead5;
    _penguin = new ePenguin;

    _eagle1 = new oEagle1;
    _eagle2 = new oEagle2;                                   //몹추가시 ★1
    _claw = new oclaw;

    return S_OK;
}

void enemyManager::release()
{
    SAFE_DELETE(_chickin);
    SAFE_DELETE(_chick);
    SAFE_DELETE(_head1);
    SAFE_DELETE(_head2);
    SAFE_DELETE(_head3);
    SAFE_DELETE(_head4);
    SAFE_DELETE(_head5);
    SAFE_DELETE(_penguin);

    _eagle1->release();
    SAFE_DELETE(_eagle1);                                   //몹추가시 ★2
    _eagle2->release();
    SAFE_DELETE(_eagle2);
    _claw->release();
    SAFE_DELETE(_claw);
}

void enemyManager::update()
{
    _chickin->update(_player, _bell, _powerUp);
    _chick->update(_player, _bell, _powerUp);
    _head1->update(_player, _bell, _powerUp);
    _head2->update(_player, _bell, _powerUp);
    _head3->update(_player, _bell, _powerUp);
    _head4->update(_player, _bell, _powerUp);
    _head5->update(_player, _bell, _powerUp);
    _penguin->update(_player, _bell, _powerUp);

    _eagle1->update(_player, _bell, _powerUp);              //몹추가시 ★3
    _eagle2->update(_player, _bell, _powerUp);
    _claw->update(_player, _bell, _powerUp);

    startPurpleEffect(); //보라효과일때만 실행될것.

    checkPlayerdie();
    checkPlayerdie2();
    checkMonsterDie();
}

void enemyManager::render()
{
    _chickin->render();
    _chick->render();
    _head1->render();
    _head2->render();
    _head3->render();
    _head4->render();                                     //몹추가시 ★4
    _head5->render();
    _penguin->render();

    _eagle1->render();
    _eagle2->render();
    _claw->render();
}

void enemyManager::checkPlayerdie()
{
    //유닛 추가시 아래에 계속 충돌함수 추가하기★
    //유닛과 충돌
    monsterCollisionToPlayer(*_chickin);
    monsterCollisionToPlayer(*_chick);
    monsterCollisionToPlayer(*_head1);                   //몹추가시 ★5 (유닛만)
    monsterCollisionToPlayer(*_head2);
    monsterCollisionToPlayer(*_head3);
    monsterCollisionToPlayer(*_head4);
    monsterCollisionToPlayer(*_head5);
    monsterCollisionToPlayer(*_penguin);

}

void enemyManager::checkPlayerdie2()                    //몹추가시 ★6 (오브젝트만)
{
    //오브젝트 추가시 아래에 계속 충돌for문 추가하기★ (몬스터충돌과, 몬스터총알충돌)
    ///////////////////////////////////////////////////////////////////////////
    //이글1 :오브젝트와 투사체
    auto vObjcet = _eagle1->getVObject();
    auto viObject = vObjcet.begin();
    for (viObject; viObject != vObjcet.end(); ++viObject)
    {
        if (viObject->objectInfo.isDeath) continue;
        //오브젝트 먼저
        monsterCollisionToPlayer(viObject->objectInfo.rc);
    }
    if (_eagle1->getEagle1Bullet() != nullptr) {
        auto vBullet = _eagle1->getEagle1Bullet()->getVEagleBullet();
        auto viBullet = vBullet->begin();
        for (viBullet = vBullet->begin(); viBullet!=vBullet->end(); ++viBullet)
        {
            //그 다음 몬스터의 총알
            monsterCollisionToPlayer(viBullet->bulletInfo.rc);
        }
    }
    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    //이글2 :오브젝트와 투사체
    auto vObjcet2 = _eagle2->getVObject();
    auto viObject2 = vObjcet2.begin();
    for (viObject2; viObject2 != vObjcet2.end(); ++viObject2)
    {
        if (viObject2->objectInfo.isDeath) continue;
        //오브젝트 먼저
        monsterCollisionToPlayer(viObject2->objectInfo.rc);
    }
    if (_eagle2->getEagle2Bullet() != nullptr) {
        auto vBullet = _eagle2->getEagle2Bullet()->getVEagleBullet();
        auto viBullet = vBullet->begin();
        for (viBullet = vBullet->begin(); viBullet != vBullet->end(); ++viBullet)
        {
            //그 다음 몬스터의 총알
            monsterCollisionToPlayer(viBullet->bulletInfo.rc);
        }
    }
    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    auto vObjcet3 = _claw->getVObject();
    auto viObject3 = vObjcet3.begin();
    for (viObject3; viObject3 != vObjcet3.end(); ++viObject3)
    {
        if (viObject3->isDeath) continue;
        //오브젝트 먼저
        for (size_t i = 0; i < 3; i++)
        {
            monsterCollisionToPlayer(viObject3->ClawRc[i]);
        }
        for (size_t i = 0; i < 2; i++)
        {
            monsterCollisionToPlayer(viObject3->wireRc[i]);
        }
    }
    if (_claw->getPuppet() != nullptr) {
        auto lpuppet = _claw->getPuppet()->getLPuppet();
        for (size_t i = 0; i < 6; i++)
        {
            if (!lpuppet[i].isExist || lpuppet[i].bulletInfo.bulletDeath) continue;
            //퍼펫나중...
            monsterCollisionToPlayer(lpuppet[i].bulletInfo.rc);
        }
    }
    




}

void enemyManager::checkMonsterDie()                   //몹추가시 ★7
{
    //1.유닛 추가시 아래에 계속 충돌함수 추가하기★ (유닛전달)
    pyBoxCollision(_chickin);
    pyBoxCollision(_chick);
    pyBoxCollision(_head1);
    pyBoxCollision(_head2);
    pyBoxCollision(_head3);
    pyBoxCollision(_head4);
    pyBoxCollision(_head5);
    pyBoxCollision(_penguin);

    //2.오브젝트 추가시 아래에 계속 충돌함 수 추가★ (박스전달)
    auto vObjcet = &_eagle1->getVObject();
    auto viObject = vObjcet->begin();
    for (viObject; viObject != vObjcet->end(); ++viObject)
    {
        RECT rc = viObject->objectInfo.rc;
        if (pyBoxCollision(rc))
        {
            _eagle1->changeStateInvinOrNormal(viObject);
            
        }
    }
    //----------------------------------------------------
    auto vObjcet2 = &_eagle2->getVObject();
    auto viObject2 = vObjcet2->begin();
    for (viObject2; viObject2 != vObjcet2->end(); ++viObject2)
    {
        RECT rc = viObject2->objectInfo.rc;
        if (pyBoxCollision(rc))
        { 
            _eagle2->changeStateInvinOrNormal(viObject2);
        }
    }
    //----------------------------------------------------
                //뽑기기계는 너무 빨리 죽지 않게 제일 넓은 하나의 상자만 박스충돌 체크
    auto vObject3 = &_claw->getVObject();
    auto viObject3 = vObject3->begin();
    for (viObject3; viObject3 != vObject3->end(); ++viObject3)
    {
        RECT rc = viObject3->ClawRc[1];
        if (pyBoxCollision(rc))
        {
            viObject3->hp--;
        }
        rc = rc = viObject3->wireRc[1];
        if (pyBoxCollision(rc))
        {
            viObject3->hp--;
        }    
    }
                //이친구의 퍼펫도 확인해야함.
    auto lpuppet = _claw->getPuppet()->getLPuppet();
    for (size_t i = 0; i < 6; i++)
    {
        if (!lpuppet[i].isExist) continue;
        if (pyBoxCollision(lpuppet[i].bulletInfo.rc))
        {
            lpuppet[i].hp--;
        }
    }
    //----------------------------------------------------




}

void enemyManager::monsterCollisionToPlayer(enemyUnit unit)
{
    RECT temp;
    vector<tagEnemy> vEnemy = unit.getVEnemy();
    vector<tagEnemy>::iterator viEnemy = vEnemy.begin();

    for (viEnemy; viEnemy != vEnemy.end(); ++viEnemy)
    {
        if (viEnemy->isDeathE) continue;
        if (_player->getpyState() != player::PLAYERSTATE::INVINCIBLE&&
            _player->getpyState() != player::PLAYERSTATE::BIG &&
            IntersectRect(&temp, &_player->getRc(), &viEnemy->rcE))
        {
            _player->setIsDeath(true);
        }
    }
}

void enemyManager::monsterCollisionToPlayer(RECT objectRc)
{
    RECT temp;
    if (_player->getpyState() != player::PLAYERSTATE::INVINCIBLE&&
        _player->getpyState() != player::PLAYERSTATE::BIG &&
        IntersectRect(&temp, &objectRc, &_player->getRc()))
    {
        _player->setIsDeath(true);
    }
}



void enemyManager::pyBoxCollision(enemyUnit* unit)
{
    vector<tagEnemy>* vEnemy = &unit->getVEnemy();
    vector<tagEnemy>::iterator viEnemy = vEnemy->begin();
    for (viEnemy; viEnemy != vEnemy->end(); ++viEnemy)
    {
        if (pyBoxCollision(viEnemy->rcE)) //충돌하면
        {
            viEnemy->isDeathE = true;
        }
    }
}

bool enemyManager::pyBoxCollision(RECT objectRc)
{
    RECT temp;
    iAdditionalAttack = additionalAttack.begin();
    for (iAdditionalAttack; iAdditionalAttack!=additionalAttack.end(); ++iAdditionalAttack)
    {
        if(IntersectRect(&temp, iAdditionalAttack->second, &objectRc))
            return true;     
    }
    return false;
}

void enemyManager::startPurpleEffect()                   //몹추가시 ★8 (유닛만)
{
    if (_isPurbleBellEffect)
    {
        purpleEffect(_chickin);
        purpleEffect(_chick);
        purpleEffect(_head1);
        purpleEffect(_head2);
        purpleEffect(_head3);
        purpleEffect(_head4);
        purpleEffect(_head5);
        purpleEffect(_penguin);


        _isPurbleBellEffect = false;
    }
}

void enemyManager::purpleEffect(enemyUnit* unit)
{
    vector<tagEnemy>* vEnemy = &unit->getVEnemy();
    vector<tagEnemy>::iterator viEnemy = vEnemy->begin();
    for (viEnemy; viEnemy != vEnemy->end(); ++viEnemy)
    {
        _powerUp->init(viEnemy->x, viEnemy->y, 0);
        viEnemy->isDeathE = true;
    }
}
