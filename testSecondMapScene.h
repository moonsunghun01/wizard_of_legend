#pragma once
#include "gameNode.h"
#include"madePlayerCollision.h"
class testSecondMapScene : public gameNode
{
private:
	madePlayerCollision* _player;
	float sound;
public:
	testSecondMapScene();
	~testSecondMapScene();
	HRESULT init();
	void release();
	void update();
	void render();
};

