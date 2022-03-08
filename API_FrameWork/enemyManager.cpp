#include "framework.h"
#include "enemyManager.h"
#include "player.h"
#include "bell.h"
#include "powerUp.h"
/*
    ����                : new, delete, update, render, checkMonsterDie
    ���� �߰���          :  startPurpleEffect�Լ� ���ο� �߰�. checkPlayerdie,
    ������Ʈ �߰���      : release(�Ѿ˶���), checkPlayerdie2(�Ѿ˱���)
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
    _eagle2 = new oEagle2;                                   //���߰��� ��1
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
    SAFE_DELETE(_eagle1);                                   //���߰��� ��2
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

    _eagle1->update(_player, _bell, _powerUp);              //���߰��� ��3
    _eagle2->update(_player, _bell, _powerUp);
    _claw->update(_player, _bell, _powerUp);

    startPurpleEffect(); //����ȿ���϶��� ����ɰ�.

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
    _head4->render();                                     //���߰��� ��4
    _head5->render();
    _penguin->render();

    _eagle1->render();
    _eagle2->render();
    _claw->render();
}

void enemyManager::checkPlayerdie()
{
    //���� �߰��� �Ʒ��� ��� �浹�Լ� �߰��ϱ��
    //���ְ� �浹
    monsterCollisionToPlayer(*_chickin);
    monsterCollisionToPlayer(*_chick);
    monsterCollisionToPlayer(*_head1);                   //���߰��� ��5 (���ָ�)
    monsterCollisionToPlayer(*_head2);
    monsterCollisionToPlayer(*_head3);
    monsterCollisionToPlayer(*_head4);
    monsterCollisionToPlayer(*_head5);
    monsterCollisionToPlayer(*_penguin);

}

void enemyManager::checkPlayerdie2()                    //���߰��� ��6 (������Ʈ��)
{
    //������Ʈ �߰��� �Ʒ��� ��� �浹for�� �߰��ϱ�� (�����浹��, �����Ѿ��浹)
    ///////////////////////////////////////////////////////////////////////////
    //�̱�1 :������Ʈ�� ����ü
    auto vObjcet = _eagle1->getVObject();
    auto viObject = vObjcet.begin();
    for (viObject; viObject != vObjcet.end(); ++viObject)
    {
        if (viObject->objectInfo.isDeath) continue;
        //������Ʈ ����
        monsterCollisionToPlayer(viObject->objectInfo.rc);
    }
    if (_eagle1->getEagle1Bullet() != nullptr) {
        auto vBullet = _eagle1->getEagle1Bullet()->getVEagleBullet();
        auto viBullet = vBullet->begin();
        for (viBullet = vBullet->begin(); viBullet!=vBullet->end(); ++viBullet)
        {
            //�� ���� ������ �Ѿ�
            monsterCollisionToPlayer(viBullet->bulletInfo.rc);
        }
    }
    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    //�̱�2 :������Ʈ�� ����ü
    auto vObjcet2 = _eagle2->getVObject();
    auto viObject2 = vObjcet2.begin();
    for (viObject2; viObject2 != vObjcet2.end(); ++viObject2)
    {
        if (viObject2->objectInfo.isDeath) continue;
        //������Ʈ ����
        monsterCollisionToPlayer(viObject2->objectInfo.rc);
    }
    if (_eagle2->getEagle2Bullet() != nullptr) {
        auto vBullet = _eagle2->getEagle2Bullet()->getVEagleBullet();
        auto viBullet = vBullet->begin();
        for (viBullet = vBullet->begin(); viBullet != vBullet->end(); ++viBullet)
        {
            //�� ���� ������ �Ѿ�
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
        //������Ʈ ����
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
            //���곪��...
            monsterCollisionToPlayer(lpuppet[i].bulletInfo.rc);
        }
    }
    




}

void enemyManager::checkMonsterDie()                   //���߰��� ��7
{
    //1.���� �߰��� �Ʒ��� ��� �浹�Լ� �߰��ϱ�� (��������)
    pyBoxCollision(_chickin);
    pyBoxCollision(_chick);
    pyBoxCollision(_head1);
    pyBoxCollision(_head2);
    pyBoxCollision(_head3);
    pyBoxCollision(_head4);
    pyBoxCollision(_head5);
    pyBoxCollision(_penguin);

    //2.������Ʈ �߰��� �Ʒ��� ��� �浹�� �� �߰��� (�ڽ�����)
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
                //�̱���� �ʹ� ���� ���� �ʰ� ���� ���� �ϳ��� ���ڸ� �ڽ��浹 üũ
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
                //��ģ���� ���굵 Ȯ���ؾ���.
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
        if (pyBoxCollision(viEnemy->rcE)) //�浹�ϸ�
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

void enemyManager::startPurpleEffect()                   //���߰��� ��8 (���ָ�)
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
