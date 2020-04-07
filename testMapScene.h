#pragma once
#include "gameNode.h"
#include "playerCollision.h"
#include "soundOption.h"

class testMapScene : public gameNode
{
private:
	
	playerCollision* _player;
	float sound;
	//float start;
public:
	testMapScene();
	~testMapScene();
	HRESULT init();
	void release();
	void update();
	void render();

};

