#pragma once
#include "gameNode.h"
#include "playerManager.h" 
#include "playerTeleport.h"
#include "enemyManager.h"
#include "shop.h"
#include "UI.h"
#include "collisionRc.h"
#include "soundOption.h"
class fireScene : public gameNode
{
private:
	playerManager* _playerManager;
	playerTeleport* _playerTeleport;
	enemyManager* _enemyManager;
	
	shop* _shop;
	UI* _ui;
	collisionRc* _collisionRc;

	soundOption* _sound;

	RECT _spawnRc1;
	RECT _spawnRc2;
	RECT _spawnRc3;
	RECT _spawnRc4;

	//렉트체크용 변수
	bool _isSpawnRc1;
	bool _isSpawnRc2;
	bool _isSpawnRc3;
	bool _isSpawnRc4;

	// 시작
	image* _blackImage;
	bool _isStart;
	int _blackImageAlpha;
	int _blackImageCount;

	image* _teleportEffect;
	bool _isTeleportEnd;
	int _teleportEffectFrameX;
	int _teleportEffectCount;

	image* _bone; 
	int _boneFrameX;
	int _boneCount;

	float sound;
public:
	HRESULT init();
	void update();
	void release();
	void render();
};

