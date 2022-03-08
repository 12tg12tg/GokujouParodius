#pragma once
#include "gameNode.h"
#include "parodius.h"

class mainGame : public gameNode
{
private:
	parodius* pd;

	bool showFPS;
public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);

	void setFPSprint() { if (InputManager->isOnceKeyDown(VK_F2)) showFPS = !showFPS; }
};  

