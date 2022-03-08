#include "framework.h"
#include "parodius.h"

parodius::parodius()
{
    IMAGE->addFrameImage("����ī��Ʈ�ٿ�", "images/screen/countdownnumber.bmp", 900, 96, 10, 1, true);
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
    pui->setPlayerMemoryLink(py);       //ui�� �÷��̾����� ����
    py->setEnemyMenegerMemoryLink(em);  //�÷��̾�� �Ŵ�������
    em->setPlayerMemoryLink(py);        //�Ŵ������� �÷��̾�����
    em->setBellMemoryLink(bl);          //�Ŵ������� ������
    em->setPowerUpMemoryLink(pu);       //�Ŵ������� �Ŀ�������
    bl->setPlayerMemoryLink(py);        //������ �÷��̾� ����
    py->setBellMemoryLink(bl);          //�÷��̾�� �� ����
    pu->setPlayerMemoryLink(py);        //�Ŀ������� �÷��̾� ����(�浹�ؼ� �Ա�����)
    py->setPowerUpMemoryLink(pu);       //�÷��̾�� �Ŀ��� ����(bell��ų ���� �ֱ�����)
    bl->setEnemyManagerMemoryLink(em);  //������ �Ŵ�������

    r1 = new round1;
    r1->init(py, em, bl, pu);
    pui->init();

    _introbg = IMAGE->addFrameImage("��Ʈ�ι��", "images/screen/��Ʈ��2.bmp", WINSIZEX*2, WINSIZEY-38, 2, 1);
    _introTitle = IMAGE->addImage("Ÿ��Ʋ", "images/screen/����.bmp", 621, 339, true);
    _pressSpace = IMAGE->addImage("��������ư", "images/screen/�������������̽�.bmp", 244, 49, true);
    _loading = IMAGE->addImage("�ε�", "images/screen/�ε�.bmp", WINSIZEX, WINSIZEY - 38);

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
            //���ӽ��� ���� ó��
            //1. �÷��̾� ��� ������ ���Ӹ���.
            if (py->getGameOver()) {
                _playerDie = true;
            }
            if (!_playerDie) {
                r1->update();
                pui->update();
            }
            //2. ����ī��Ʈ�ٿ����
            else {
                checkCountDown();
            }
            //3. ���������Ǵܽ� �ٽ�ó�����ͽ���
            if (_gameOver) {
                _gameOverCount++;
                 if (_gameOverCount % 300 == 0) {
                    _gotomain = true;
                }
            }
        }
    }


    //�����
    if (InputManager->isOnceKeyDown(VK_F1)) {
        _isDebug = !_isDebug;
        r1->setDebug(_isDebug);
        em->setDebug(_isDebug);
        py->setDebug(_isDebug);
        bl->setdebug(_isDebug);
        pu->setdebug(_isDebug);
    }
    //�Ͻ�����
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
        //���ӽ��� ����
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
        IMAGE->frameRender("����ī��Ʈ�ٿ�", getMemDC(),
            WINSIZEX / 2 - IMAGE->findImage("����ī��Ʈ�ٿ�")->getFrameWidth(),
            WINSIZEY / 2 - IMAGE->findImage("����ī��Ʈ�ٿ�")->getFrameHeight() / 2,
            1, 0);
        IMAGE->frameRender("����ī��Ʈ�ٿ�", getMemDC(),
            WINSIZEX / 2 ,
            WINSIZEY / 2 - IMAGE->findImage("����ī��Ʈ�ٿ�")->getFrameHeight() / 2,
            0, 0);
    }
    else {
        IMAGE->frameRender("����ī��Ʈ�ٿ�", getMemDC(),
            WINSIZEX / 2 - IMAGE->findImage("����ī��Ʈ�ٿ�")->getFrameWidth()/2,
            WINSIZEY / 2 - IMAGE->findImage("����ī��Ʈ�ٿ�")->getFrameHeight()/2,
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
