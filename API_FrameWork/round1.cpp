#include "framework.h"
#include "round1.h"

round1::round1()
{
}

round1::~round1()
{
}

HRESULT round1::init(player* py, enemyManager* em, bell* bl, powerUp* pu)
{	
	_bg1 = IMAGE->addImage("배경1", "images/round1/newbackground1.bmp", 1347, WINSIZEY-21);

	_bgSlow = IMAGE->addImage("느린별", "images/round1/backgroundstar1.bmp", 1518, WINSIZEY-21, true);
	_bgFast = IMAGE->addImage("빠른별", "images/round1/faststar.bmp", 1518, WINSIZEY-21, true);

	_longbgimg = IMAGE->addImage("롱배경", "images/round1/newlongbackground2.bmp", 6294, WINSIZEY-21);

	_offsetX = 0;
	_slowOffsetX = 0;
	_fastOffsetX = 0;

	_player = py;
	_em = em;
	_bl = bl;
	_pu = pu;

	_pd = new panda;
	_pd->init();
	_pd->setPlayerMemoryLink(_player);
	_pd->setEnemyManagerMemoryLink(_em);
	_pd->setBellMemoryLink(_bl);
	_pd->setPowerUpMemoryLink(_pu);
	_bl->setPandaMemoryLink(_pd);
	_pu->setPandaMemoryLink(_pd);

	_sm = new screenManager;
	_sm->init();

	_camera = 0;
	_endcount = 0;

	//for test
	//test = new oclaw;
	//
	
	_test = false;
	return S_OK;
}

void round1::release()
{
	_sm->release();
	SAFE_DELETE(_sm);
	SAFE_DELETE(_pd);
	//for test
	//SAFE_DELETE(test);
	//
}

void round1::update()
{
	if(!_cameraStop)
		_camera++;

	if (_test) {
		//if (_camera == 900) {
		//	_em->getEagle1()->init(WINSIZEX + 1, 150);
		//	_em->getEagle1()->init(WINSIZEX + 1, 450);
		//}
		//if (_camera == 1320) {
		//	_em->getEagle2()->init(WINSIZEX+1, 150);
		//	_em->getEagle2()->init(WINSIZEX+1, 450);
		//}
		////첫뽑기기계 그냥 오->왼 지나감
		//if (_camera == 1710) {
		//	_em->getClaw()->init(2);
		//}
		//if (_camera == 2000) {
		//	_em->getClaw()->init(3);
		//}
		//if (_camera == 2300) {
		//	_em->getClaw()->init(4);
		//}
		//if (_camera == 3000) {
		//	_em->getClaw()->init(5);
		//}
		//if (_camera == 3880) {
		//	_em->getClaw()->init(1);
		//}
		//if (_camera == 4600) {
		//	_em->getClaw()->init(6);
		//}
		//if (_camera >= 300 && _camera%200==0) {
		//	_em->getEagle1()->init(WINSIZEX + 10, 1);
		//	_em->getEagle2()->init(WINSIZEX + 1, 50);
		//	_em->getEagle1()->init(WINSIZEX + 10, 100);
		//	_em->getEagle2()->init(WINSIZEX + 10, 150);
		//	_em->getEagle1()->init(WINSIZEX + 1, 200);
		//	_em->getEagle2()->init(WINSIZEX + 10, 250);
		//	_em->getEagle1()->init(WINSIZEX + 10, 300);
		//	_em->getEagle2()->init(WINSIZEX + 1, 350);
		//	_em->getEagle1()->init(WINSIZEX + 10, 400);
		//	_em->getEagle2()->init(WINSIZEX + 10, 450);
		//	_em->getEagle1()->init(WINSIZEX + 1, 500);
		//	_em->getEagle2()->init(WINSIZEX + 10, 550);
		//	_em->getEagle1()->init(WINSIZEX + 10, 600);
		//	_em->getEagle2()->init(WINSIZEX + 1, 650);
		//	_em->getEagle1()->init(WINSIZEX + 10, 700);
		//	_em->getEagle2()->init(WINSIZEX + 10, 750);
		//	_em->getEagle1()->init(WINSIZEX + 1, 800);
		//	_em->getEagle2()->init(WINSIZEX + 10, 850);
		//}
		////닭병아리
		//if (_camera == 140) {
		//	_em->getChick()->init(WINSIZEX + 10, 150);
		//	_em->getChiKin()->init(WINSIZEX + 1, 200);
		//	_em->getChick()->init(WINSIZEX + 10, 250);
		//}
		////머리5개
		//if (_camera == 400) {
		//	_em->getHead1()->init(WINSIZEX + 1, 600);
		//}
		//if (_camera == 420) {
		//	_em->getHead2()->init(WINSIZEX + 1, 600);
		//}
		//if (_camera == 440) {
		//	_em->getHead3()->init(WINSIZEX + 1, 600);
		//}
		//if (_camera == 460) {
		//	_em->getHead4()->init(WINSIZEX + 1, 600);
		//}
		//if (_camera == 480) {
		//	_em->getHead5()->init(WINSIZEX + 1, 600);
		//}

		////펭귄3마리↘
		//if (_camera == 880) {
		//	_em->getPenguin()->init(200, -50, 1);
		//}
		//if (_camera == 900) {
		//	_em->getPenguin()->init(400, -50, 1);
		//}
		//if (_camera == 920) {
		//	_em->getPenguin()->init(600, -50, 1);
		//}

		////펭귄3마리↙
		//if (_camera == 1100) {
		//	_em->getPenguin()->init(500, -50, 2);
		//}
		//if (_camera == 1120) {
		//	_em->getPenguin()->init(700, -50, 2);
		//}
		//if (_camera == 1140) {
		//	_em->getPenguin()->init(900, -50, 2);
		//}

		////펭귄3마리 팅기는
		//if (_camera == 1300) {
		//	_em->getPenguin()->init(200, -50, 3);
		//}
		//if (_camera == 1320) {
		//	_em->getPenguin()->init(400, -50, 3);
		//}
		//if (_camera == 1340) {
		//	_em->getPenguin()->init(600, -50, 3);
		//}

	}
	else
	{
		//카메라 수치별로 몹등장패턴 정하기
		//100일때 닭, 병아리 출현
		if (_camera == 140) {
			_em->getChick()->init(WINSIZEX + 10, 150);
			_em->getChiKin()->init(WINSIZEX + 1, 200);
			_em->getChick()->init(WINSIZEX + 10, 250);
		}
		//200일때 닭, 병아리 출현
		if (_camera == 200) {
			_em->getChick()->init(WINSIZEX + 10, 450);
			_em->getChiKin()->init(WINSIZEX + 1, 500);
			_em->getChick()->init(WINSIZEX + 10, 550);
		}
		//독수리출현
		if (_camera == 300) {
			_em->getEagle1()->init(WINSIZEX + 1, 300);
		}
		//일때 머리5개 출현
		if (_camera == 400) {
			_em->getHead1()->init(WINSIZEX + 1, 600);
		}
		if (_camera == 420) {
			_em->getHead2()->init(WINSIZEX + 1, 600);
		}
		if (_camera == 440) {
			_em->getHead3()->init(WINSIZEX + 1, 600);
		}
		if (_camera == 460) {
			_em->getHead4()->init(WINSIZEX + 1, 600);
		}
		if (_camera == 480) {
			_em->getHead5()->init(WINSIZEX + 1, 600);
		}
		//일때 머리5개 출현
		if (_camera == 500) {
			_em->getHead1()->init(WINSIZEX + 1, 100);
		}
		if (_camera == 520) {
			_em->getHead2()->init(WINSIZEX + 1, 100);
		}
		if (_camera == 540) {
			_em->getHead3()->init(WINSIZEX + 1, 100);
		}
		if (_camera == 560) {
			_em->getHead4()->init(WINSIZEX + 1, 100);
		}
		if (_camera == 580) {
			_em->getHead5()->init(WINSIZEX + 1, 100);
		}
		//파랑독수리출현
		if (_camera == 700) {
			_em->getEagle2()->init(WINSIZEX + 1, 300);
		}
		//병아리셋
		if (_camera == 800)
		{
			_em->getChick()->init(WINSIZEX + 10, 100);
			_em->getChick()->init(WINSIZEX + 10, 150);
			_em->getChick()->init(WINSIZEX + 10, 200);
		}
		//머리5
		if (_camera == 880) {
			_em->getHead1()->init(WINSIZEX + 1, 100);
		}
		if (_camera == 900) {
			_em->getHead2()->init(WINSIZEX + 1, 100);
		}
		if (_camera == 920) {
			_em->getHead3()->init(WINSIZEX + 1, 100);
		}
		if (_camera == 940) {
			_em->getHead4()->init(WINSIZEX + 1, 100);
		}
		if (_camera == 960) {
			_em->getHead5()->init(WINSIZEX + 1, 100);
		}
		//닭셋
		if (_camera == 1000)
		{
			_em->getChiKin()->init(WINSIZEX + 10, 300);
			_em->getChiKin()->init(WINSIZEX + 10, 350);
			_em->getChiKin()->init(WINSIZEX + 10, 400);
		}
		//닭셋
		if (_camera == 1100)
		{
			_em->getChiKin()->init(WINSIZEX + 10, 300);
			_em->getChiKin()->init(WINSIZEX + 10, 350);
			_em->getChiKin()->init(WINSIZEX + 10, 400);
		}
		//머리5
		if (_camera == 1150) {
			_em->getHead1()->init(WINSIZEX + 1, 400);
		}
		if (_camera == 1170) {
			_em->getHead2()->init(WINSIZEX + 1, 400);
		}
		if (_camera == 1190) {
			_em->getHead3()->init(WINSIZEX + 1, 400);
		}
		if (_camera == 1210) {
			_em->getHead4()->init(WINSIZEX + 1, 400);
		}
		if (_camera == 1230) {
			_em->getHead5()->init(WINSIZEX + 1, 400);
		}
		//파랑독수리출현
		if (_camera == 1300) {
			_em->getEagle2()->init(WINSIZEX + 1, 150);
			_em->getEagle2()->init(WINSIZEX + 1, 500);
		}
		//펭귄3마리↘
		if (_camera == 1500) {
			_em->getPenguin()->init(200, -50, 1);
		}
		if (_camera == 1520) {
			_em->getPenguin()->init(400, -50, 1);
		}
		if (_camera == 1540) {
			_em->getPenguin()->init(600, -50, 1);
		}
		//펭귄3마리↙
		if (_camera == 1650) {
			_em->getPenguin()->init(500, -50, 2);
		}
		if (_camera == 1670) {
			_em->getPenguin()->init(700, -50, 2);
		}
		if (_camera == 1690) {
			_em->getPenguin()->init(900, -50, 2);
		}
		//첫뽑기기계 그냥 오->왼 지나감
		if (_camera == 1710) {
			_em->getClaw()->init(2);
		}
		//그리고 병아리셋
		if (_camera == 1750)
		{
			_em->getChick()->init(WINSIZEX + 10, 300);
			_em->getChick()->init(WINSIZEX + 10, 350);
			_em->getChick()->init(WINSIZEX + 10, 400);
		}
		//두번째뽑기기계 멀리서 가져감.
		if (_camera == 1850) {
			_em->getClaw()->init(4);
		}
		//그리고 머리5
		if (_camera == 1900) {
			_em->getHead1()->init(WINSIZEX + 1, 600);
		}
		if (_camera == 1920) {
			_em->getHead2()->init(WINSIZEX + 1, 600);
		}
		if (_camera == 1940) {
			_em->getHead3()->init(WINSIZEX + 1, 600);
		}
		if (_camera == 1960) {
			_em->getHead4()->init(WINSIZEX + 1, 600);
		}
		if (_camera == 1980) {
			_em->getHead5()->init(WINSIZEX + 1, 600);
		}
		//세번째뽑기기계 떨구고감
		if (_camera == 2200) {
			_em->getClaw()->init(3);
		}
		//펭귄3마리 ↙
		if (_camera == 2200) {
			_em->getPenguin()->init(500, -50, 2);
		}
		if (_camera == 2240) {
			_em->getPenguin()->init(700, -50, 2);
		}
		if (_camera == 2260) {
			_em->getPenguin()->init(900, -50, 2);
		}
		//네번째뽑기기계 앞에서 가져감.
		if (_camera == 2500) {
			_em->getClaw()->init(1);
		}
		//닭셋
		if (_camera == 2580)
		{
			_em->getChiKin()->init(WINSIZEX + 10, 500);
			_em->getChiKin()->init(WINSIZEX + 10, 550);
			_em->getChiKin()->init(WINSIZEX + 10, 600);
		}
		//닭셋
		if (_camera == 2700)
		{
			_em->getChiKin()->init(WINSIZEX + 10, 100);
			_em->getChiKin()->init(WINSIZEX + 10, 150);
			_em->getChiKin()->init(WINSIZEX + 10, 200);
		}
		//다섯번째뽑기기계 오른쪽으로퇴장.
		if (_camera == 2900) {
			_em->getClaw()->init(5);
		}
		//파랑독수리출현
		if (_camera == 3100) {
			_em->getEagle2()->init(WINSIZEX + 1, 400);
		}
		//기계
		if (_camera == 3200) {
			_em->getClaw()->init(3);
		}
		//뽑기기계 싸가지없게 가운데 투척.
		if (_camera == 3400) {
			_em->getClaw()->init(5);
		}
		//펭귄3마리 ↙
		if (_camera == 3500) {
			_em->getPenguin()->init(500, -50, 3);
		}
		if (_camera == 3600) {
			_em->getPenguin()->init(700, -50, 3);
		}
		if (_camera == 3700) {
			_em->getPenguin()->init(900, -50, 3);
		}
		//기계 세대
		if (_camera == 3750) {
			_em->getClaw()->init(5);
		}
		if (_camera == 3880) {
			_em->getClaw()->init(3);
		}
		if (_camera == 4150) {
			_em->getClaw()->init(4);
		}
		//머리5
		if (_camera == 4000) {
			_em->getHead1()->init(WINSIZEX + 1, 200);
		}
		if (_camera == 4020) {
			_em->getHead2()->init(WINSIZEX + 1, 200);
		}
		if (_camera == 4040) {
			_em->getHead3()->init(WINSIZEX + 1, 200);
		}
		if (_camera == 4060) {
			_em->getHead4()->init(WINSIZEX + 1, 200);
		}
		if (_camera == 4080) {
			_em->getHead5()->init(WINSIZEX + 1, 200);
		}
		//학원간판
		if (_camera == 4400) {
			_em->getClaw()->init(6);
		}
		//닭셋
		if (_camera == 4500)
		{
			_em->getChiKin()->init(WINSIZEX + 10, 500);
			_em->getChiKin()->init(WINSIZEX + 10, 550);
			_em->getChiKin()->init(WINSIZEX + 10, 600);
		}
		//뽑아가는 기계2대
		if (_camera == 4580) {
			_em->getClaw()->init(1);
		}
		if (_camera == 4600) {
			_em->getClaw()->init(4);
		}
		//파랑독수리출현
		if (_camera == 4600) {
			_em->getEagle2()->init(WINSIZEX + 1, 500);
		}
		//마지막 닭, 병아리 출현
		if (_camera == 4700) {
			_em->getChick()->init(WINSIZEX + 10, 150);
			_em->getChiKin()->init(WINSIZEX + 1, 200);
			_em->getChick()->init(WINSIZEX + 10, 250);
		}
		//독수리출현
		if (_camera == 5100) {
			_em->getEagle1()->init(WINSIZEX + 1, 300);
		}
		//마지막 닭, 병아리 출현
		if (_camera == 5100) {
			_em->getChick()->init(WINSIZEX + 10, 600);
			_em->getChiKin()->init(WINSIZEX + 1, 650);
			_em->getChick()->init(WINSIZEX + 10, 700);
		}
		//펭귄3마리 ↙
		if (_camera == 5300) {
			_em->getPenguin()->init(500, -50, 2);
		}
		if (_camera == 5350) {
			_em->getPenguin()->init(700, -50, 2);
		}
		if (_camera == 5400) {
			_em->getPenguin()->init(900, -50, 2);
		}
		//파랑독수리출현
		if (_camera == 5400) {
			_em->getEagle2()->init(WINSIZEX + 1, 200);
		}
		//펭귄3마리 ↘
		if (_camera == 5450) {
			_em->getPenguin()->init(200, -50, 1);
		}
		if (_camera == 5500) {
			_em->getPenguin()->init(400, -50, 1);
		}
		if (_camera == 5600) {
			_em->getPenguin()->init(600, -50, 1);
		}
		//마지막 닭, 병아리 출현
		if (_camera == 5800) {
			_em->getChick()->init(WINSIZEX + 10, 600);
			_em->getChiKin()->init(WINSIZEX + 1, 650);
			_em->getChick()->init(WINSIZEX + 10, 700);
		}
		//펭귄3마리 팅기는
		if (_camera == 6000) {
			_em->getPenguin()->init(200, -50, 3);
		}
		if (_camera == 6020) {
			_em->getPenguin()->init(400, -50, 3);
		}
		if (_camera == 6040) {
			_em->getPenguin()->init(600, -50, 3);
		}
		//독수리출현
		if (_camera == 6100) {
			_em->getEagle1()->init(WINSIZEX + 1, 100);
		}
		//파랑독수리출현
		if (_camera == 6100) {
			_em->getEagle2()->init(WINSIZEX + 1, 500);
		}
	}



	//보스
	if (_camera == MAXCAMERA) {
		_pd->setStart(true);
	}
	//클리어하자마자 카운팅
	if (_pd->getIsClear()) {
		_endcount++;
	}
	if (_endcount == 10) {
		_sm->initBlackFadeIn();
	}

	_em->update();
	_player->update();
	_bl->update();
	_pu->update();
	_pd->update();

	//라운드 종료전에는 일단 최대카메라까지 당김
	if (_endcount==0 && _offsetX < MAXCAMERA) {
		if (!_cameraStop)
			_offsetX++;
		_slowOffsetX += 2;
		_fastOffsetX += 3;
	}
	//종료후 다시 오프셋 당기기
	if (_endcount > 200) {
		_offsetX++;
		_slowOffsetX += 2;
		_fastOffsetX += 3;
	}
	cheetMode();
}

void round1::render()
{

	_bg1->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _offsetX, 0);
	_longbgimg->render(getMemDC(), 1347 - _offsetX, 0);
	if(_offsetX < MAXCAMERA) _bgSlow->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _slowOffsetX, 0);

	if (_endcount < 200) {
		_player->render();
		_em->render();
		_bl->render();
		_pu->render();
		_pd->render();
	}
	if (_endcount > 100) {
		_sm->blackfadein();
		_player->render();
	}
	if (_endcount >= 250) {
		_bgSlow->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _slowOffsetX, 0);
		_player->render();
		_bgFast->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _fastOffsetX, 0);
	}

	if(_offsetX < MAXCAMERA) _bgFast->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _fastOffsetX, 0);

	//페이드인, 폭죽출력
	if (_camera < 250) {
		if (_camera > 100) {
			_sm->showFireWork1();
		}
		if (_camera > 120) {
			_sm->showFireWork2();
		}
		if (_camera > 150) {
			_sm->showFireWork3();
		}
		if (_camera > 170) {
			_sm->showFireWork4();
		}
		if (_camera > 180) {
			_sm->showFireWork5();
		}
		_sm->blackfadeOut();
	}

	//TCHAR str[128];
	//wsprintf(str, "offsetX : %d", _offsetX);
	//TextOut(getMemDC(), 600, 0, str, lstrlen(str));
}

void round1::cheetMode()
{
	if (InputManager->isOnceKeyDown(VK_F8)) {
		_bl->init(600, 130);
		_bl->init(600, 230);
		_bl->init(600, 330);
		_bl->init(600, 430);
		_bl->init(600, 530);		
		_bl->init(600, 630);		
	}
	if (InputManager->isOnceKeyDown(VK_F11)) {
		_cameraStop = !_cameraStop;
	}
}
