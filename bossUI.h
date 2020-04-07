#pragma once
#include "Boss.h"
#include "gameNode.h"

class bossUI : public gameNode
{
private:
	Boss* _boss;
	image* _bossHpBar;
	image* _bossHpBarBackground;
	image* _bossHpBarLeft;
	image* _bossHpBarRight;
	image* _bossFace;
	RECT _bossHpBarRc;
	float _bossHpBarWidth;

public:
	bossUI();
	~bossUI();

	HRESULT init();
	HRESULT init(Boss* boss);
	void release();
	void update();
	void render();
};

