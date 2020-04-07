#include "stdafx.h"
#include "testSecondMapScene.h"

testSecondMapScene::testSecondMapScene()
{
}

testSecondMapScene::~testSecondMapScene()
{
}

HRESULT testSecondMapScene::init()
{
	_player = new madePlayerCollision;
	_player->init();
	_player->setPlayerPosition();

	sound = SOUNDMANAGER->getVolume();

	SOUNDMANAGER->stop("intro");
	SOUNDMANAGER->play("maptoolBGM", sound);
	return S_OK;
}

void testSecondMapScene::release()
{
	SAFE_DELETE(_player);
}

void testSecondMapScene::update()
{

	_player->update();
	if (KEYMANAGER->isOnceKeyDown(VK_CONTROL)) {
		SOUNDMANAGER->stop("maptoolBGM");
		SCENEMANAGER->changeScene("mainScene");
	}
}

void testSecondMapScene::render()
{
	_player->render();
}
