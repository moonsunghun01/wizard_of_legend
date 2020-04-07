#pragma once
#include "gameNode.h"
#include "playerManager.h"  
#include "enemyManager.h"
#include "UI.h" 
#include "bossUI.h"
#include "soundOption.h"
#include "collisionRc.h"

class bossScene : public gameNode
{
private:
	playerManager* _playerManager;
	enemyManager* _enemyManager;
	UI* _ui;
	bossUI* _bossUI;

	image* _teleportPad;
	RECT _teleportPadRc;
	soundOption* _sound;
	image* _castingCircle;
	image* _meteor;
	int _count;
	int _index;
	int _index2;

	collisionRc* _collisionRc;
	float sound;
public:
	HRESULT init();
	void update();
	void release();
	void render();
};

