#pragma once
#include "gameNode.h"

class soundOption : public gameNode
{
private:
	image* _bgImage;
	RECT _mute;
	RECT cursor;
	RECT soundBar;

	int x, y;
	float soundNum;
	RECT _backRc;
public:


	HRESULT init();
	void release();
	void update();
	void render();

	void mute();
	void volume();
	float getSoundVolume() { return soundNum; }
	void cursorPostion();
};