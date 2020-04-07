#pragma once
#include "gameNode.h"
#include "mapToolScene.h"
#include "testMapToolSelect.h"
#include "mainScene.h"

class mapToolSelectScene : public gameNode
{
private:
	image* backGround;
	image* _button;
	RECT _mapToolRc;
	RECT _testRc;
	RECT _backRc;

public:
	mapToolSelectScene();
	~mapToolSelectScene();
	HRESULT init();
	void release();
	void update();
	void render();
};

