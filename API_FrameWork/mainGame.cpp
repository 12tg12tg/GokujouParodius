#include "framework.h"
#include "mainGame.h"

mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

HRESULT mainGame::init()
{
	gameNode::init(true);	//�ʿ��ѵ����Ҵ�

	pd = new parodius;
	pd->init();

	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	SAFE_DELETE(pd);

}

void mainGame::update()
{
	gameNode::update();

	pd->update();
	if (pd->getGotoMain()) {
		release();
		init();
	}
	setFPSprint();
}

void mainGame::render(/*HDC hdc*/)	//�׸��׸��°�
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//========================================================
						/*������ ����*/
	
	pd->render();
	//Rectangle(getMemDC(), 100, 100, 500, 500);
	//========================================================
	if (showFPS)TIME->render(getMemDC());
	//���۹��� ������ HDC�� �׸���. (�ǵ帮�� ����)
	//this->getMapBuffer()->render(getMemDC(), 0, 0, 400, 0, WINSIZEX, WINSIZEY);
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

