#include "stdafx.h"
#include "testMapScene.h"


testMapScene::testMapScene()
{
}


testMapScene::~testMapScene()
{
}

HRESULT testMapScene::init()
{
	//start = TIMEMANAGER->getWorldTime();
	_player = new playerCollision;
	_player->init();
	_player->setPlayerPosition();

	sound = SOUNDMANAGER->getVolume();
	
	SOUNDMANAGER->stop("intro");
	SOUNDMANAGER->play("maptoolBGM", sound);
	return S_OK;
}

void testMapScene::release()
{
	SAFE_DELETE(_player);
	
}

void testMapScene::update()
{
	
	_player->update();
	if (KEYMANAGER->isOnceKeyDown(VK_CONTROL)) {
		SOUNDMANAGER->stop("maptoolBGM");
		SCENEMANAGER->changeScene("mainScene");
	}
	
}

void testMapScene::render()
{
	_player->render();	
}