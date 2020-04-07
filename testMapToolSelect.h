#pragma once
#include "mainScene.h"
#include "gameNode.h"

class testMapToolSelect : public gameNode
{
private:
	image* backGround;
	image* _button;
	RECT _testFirstRc;
	RECT _testSecondRc;
	RECT _backRc;

public:
	testMapToolSelect();
	~testMapToolSelect();
	HRESULT init();
	void release();
	void update();
	void render();
};

