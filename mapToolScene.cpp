#include "stdafx.h"
#include "mapToolScene.h"


mapToolScene::mapToolScene()
{
}


mapToolScene::~mapToolScene()
{
}

HRESULT mapToolScene::init()
{
	_mapTool = new mapTool;
	_mapTool->init();
	
	_sound = new soundOption;
	_sound->init();
	_sound->update();
	
	sound = SOUNDMANAGER->getVolume();
	
	SOUNDMANAGER->stop("intro");
	SOUNDMANAGER->play("maptoolBGM",sound);
	return S_OK;
}

void mapToolScene::release()
{	
}

void mapToolScene::update()
{
	_mapTool->update();
	if (KEYMANAGER->isOnceKeyDown(VK_CONTROL)) {
		SOUNDMANAGER->stop("maptoolBGM");
		SCENEMANAGER->changeScene("mainScene");
	}
}

void mapToolScene::render()
{
	//mapÅø ·»´õ
	_mapTool->render();
}
