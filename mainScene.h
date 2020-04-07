#pragma once
#include "gameNode.h"
#include "mapToolSelectScene.h"
#include "fireScene.h"
#include "testMapScene.h"
#include "soundOption.h"

class mainScene : public gameNode
{
private:
	soundOption* _sound;
	image* _backGround;
	image* _button;
	RECT _titleRc;
	RECT _startRc;
	RECT _mapToolRc;
	RECT _testMapRc;
	RECT _soundOptionRc;
	RECT _exitRc;
	bool _isClick;
	HFONT hfont, oldFont;
	float sound;
public:
	mainScene();
	~mainScene();
	HRESULT init();
	void release();
	void update();
	void render();
};

