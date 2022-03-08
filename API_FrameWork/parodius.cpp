#include "framework.h"
#include "parodius.h"

parodius::parodius()
{
    IMAGE->addFrameImage("종료카운트다운", "images/screen/countdownnumber.bmp", 900, 96, 10, 1, true);
}

parodius::~parodius(){}

HRESULT parodius::init()
{
    py = new player;
    pui = new playerui;
    em = new enemyManager;
    bl = new bell;
    pu = new powerUp;
    py->init();
    em->init();
    pui->setPlayerMemoryLink(py);       //ui에 플레이어정보 전달
    py->setEnemyMenegerMemoryLink(em);  //플레이어에게 매니저전달
    em->setPlayerMemoryLink(py);        //매니저에게 플레이어전달
    em->setBellMemoryLink(bl);          //매니저에게 벨전달
    em->setPowerUpMemoryLink(pu);       //매니저에게 파워업전달
    bl->setPlayerMemoryLink(py);        //벨에게 플레이어 전달
    py->setBellMemoryLink(bl);          //플레이어에게 벨 전달
    pu->setPlayerMemoryLink(py);        //파워업에게 플레이어 전달(충돌해서 먹기위함)
    py->setPowerUpMemoryLink(pu);       //플레이어에게 파워업 전달(bell스킬 상자 주기위함)
    bl->setEnemyManagerMemoryLink(em);  //벨에게 매니저전달

    r1 = new round1;
    r1->init(py, em, bl, pu);
    pui->init();

    _introbg = IMAGE->addFrameImage("인트로배경", "images/screen/인트로2.bmp", WINSIZEX*2, WINSIZEY-38, 2, 1);
    _introTitle = IMAGE->addImage("타이틀", "images/screen/제목.bmp", 621, 339, true);
    _pressSpace = IMAGE->addImage("프레스버튼", "images/screen/프레스더스페이스.bmp", 244, 49, true);
    _loading = IMAGE->addImage("로딩", "images/screen/로딩.bmp", WINSIZEX, WINSIZEY - 38);

    _startcount = 0;
    _start = false;
    _gameStop = false;
    _playerDie = false;
    _gameOver = false;
    _gameOverCount = 0;
    _countDown = 10;
    _countcount = 0;
    return S_OK;
}

void parodius::release()
{
    py->release();
    pui->release();
    em->release();
    r1->release();
    SAFE_DELETE(py);
    SAFE_DELETE(em);
    SAFE_DELETE(bl);
    SAFE_DELETE(r1);
    SAFE_DELETE(pu);
    SAFE_DELETE(pui);
}

void parodius::update()
{
    if (!_gameStop) {
        if (!_start) {
            checktitle();
        }
        else if(_isloading){
            loading();
        }
        else {
            _afterloading++;
            if (_afterloading > 120) {
                _gamestart = true;
            }
        }
        
        if(_gamestart) {
            //게임시작 이후 처리
            //1. 플레이어 목숨 소진시 게임멈춤.
            if (py->getGameOver()) {
                _playerDie = true;
            }
            if (!_playerDie) {
                r1->update();
                pui->update();
            }
            //2. 종료카운트다운실행
            else {
                checkCountDown();
            }
            //3. 게임종료판단시 다시처음부터시작
            if (_gameOver) {
                _gameOverCount++;
                 if (_gameOverCount % 300 == 0) {
                    _gotomain = true;
                }
            }
        }
    }


    //디버그
    if (InputManager->isOnceKeyDown(VK_F1)) {
        _isDebug = !_isDebug;
        r1->setDebug(_isDebug);
        em->setDebug(_isDebug);
        py->setDebug(_isDebug);
        bl->setdebug(_isDebug);
        pu->setdebug(_isDebug);
    }
    //일시중지
    if (InputManager->isOnceKeyDown('P')) {
        _gameStop = !_gameStop;
    }
}

void parodius::render()
{
    if (!_start) {
        showtitle();
    }
    else if (_isloading) {
        showloading();
    }
    else if(!_gamestart){
        _loading->render(getMemDC());
        r1->getscreenManager()->blackfadein();
    }
    if(_gamestart) {
        //게임시작 이후
        r1->render();
        pui->render();
        if (_playerDie) {
            showCountDown();
        }
        if (_gameOver) {
             r1->getscreenManager()->blackfadein();
        }
    }
}

void parodius::checkCountDown()
{
    _countcount++;
    if (_countDown != 0) {
        if (_countcount % 80 == 0 || InputManager->isOnceKeyDown(VK_SPACE)) {
            _countcount = 0;
            _countDown--;
        }
    }
    else if (_countDown == 0) {
        _countcount++;
        if (_countcount % 30 == 0) {
            _countcount++;
            _gameOver = true;
            r1->getscreenManager()->initBlackFadeIn();
        }
    }
}

void parodius::showCountDown()
{
    if (_countDown == 10) {
        IMAGE->frameRender("종료카운트다운", getMemDC(),
            WINSIZEX / 2 - IMAGE->findImage("종료카운트다운")->getFrameWidth(),
            WINSIZEY / 2 - IMAGE->findImage("종료카운트다운")->getFrameHeight() / 2,
            1, 0);
        IMAGE->frameRender("종료카운트다운", getMemDC(),
            WINSIZEX / 2 ,
            WINSIZEY / 2 - IMAGE->findImage("종료카운트다운")->getFrameHeight() / 2,
            0, 0);
    }
    else {
        IMAGE->frameRender("종료카운트다운", getMemDC(),
            WINSIZEX / 2 - IMAGE->findImage("종료카운트다운")->getFrameWidth()/2,
            WINSIZEY / 2 - IMAGE->findImage("종료카운트다운")->getFrameHeight()/2,
            _countDown, 0);
    }
}

void parodius::showtitle()
{
    _introbg->frameRender(getMemDC(), 0, 0);
    _introTitle->render(getMemDC(), 210, 120);
    _pressSpace->render(getMemDC(), 380, 500);
}

void parodius::checktitle()
{
    if (InputManager->isOnceKeyDown(VK_SPACE))
    {
        _start = true;
        _isloading = true;
        r1->getscreenManager()->initBlackFadeOut();
    }
    _startcount++;
    if (_startcount % 10 == 0) {
        if (_introbg->getFrameX() == 0) {
            _introbg->setFrameX(1);
        }
        else {
            _introbg->setFrameX(0);
        }
    }
}

void parodius::loading()
{
    _loadingCount++;
    if (InputManager->isOnceKeyDown(VK_SPACE))
    {
        _isloading = false;
    }
    if (_loadingCount > 500) {

        _isloading = false;
    }
}

void parodius::showloading()
{
    _loading->render(getMemDC());
    if (_loadingCount < 60) {
        r1->getscreenManager()->blackfadeOut();
    }
}
