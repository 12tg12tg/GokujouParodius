#pragma once
#include "gameNode.h"
class screenManager : public gameNode
{
private:
	class imageTag
	{
	public:
		image*	img;
		int		alpha;
		int		frameX;
		int		count;

		void init() {
			alpha = 255;
			frameX = 0;
			count = 0;
		}
	};
private:
	imageTag*		_bg1;
	imageTag*		_bg2;
	imageTag*		_bgSlow;
	imageTag*		_bgFast;
	imageTag*		_fireWork1;
	imageTag*		_fireWork2;
	imageTag*		_fireWork3;
	imageTag*		_fireWork4;
	imageTag*		_fireWork5;
			
	imageTag*		_fadeOut1;
	imageTag*		_fadeOut2;

public:
	screenManager();
	~screenManager();

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

	void blackfadeOut();
	void blackfadein();
	void showFireWork1();
	void showFireWork2();
	void showFireWork3();
	void showFireWork4();
	void showFireWork5();

	void initBlackFadeOut() { _fadeOut2->alpha = 255; }
	void initBlackFadeIn() { _fadeOut2->alpha = 0; }
};

