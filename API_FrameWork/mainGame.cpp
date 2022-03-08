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
	gameNode::init(true);	//필요한동적할당

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

void mainGame::render(/*HDC hdc*/)	//그림그리는곳
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//========================================================
						/*렌더링 공간*/
	
	pd->render();
	//Rectangle(getMemDC(), 100, 100, 500, 500);
	//========================================================
	if (showFPS)TIME->render(getMemDC());
	//백퍼버의 내용을 HDC에 그린다. (건드리지 말것)
	//this->getMapBuffer()->render(getMemDC(), 0, 0, 400, 0, WINSIZEX, WINSIZEY);
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

