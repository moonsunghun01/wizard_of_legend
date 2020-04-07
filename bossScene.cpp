#include "stdafx.h"
#include "bossScene.h"

HRESULT bossScene::init()
{

	IMAGEMANAGER->addImage("bossMap", "images/bossMap.bmp", 530 * 2, 490 * 2, true, RGB(255, 0, 255));

	_collisionRc = new collisionRc;
	_collisionRc->init();
	_collisionRc->setIsBossMap(true);
	


	_playerManager = new playerManager;
	_playerManager->init(_collisionRc);

	_enemyManager = new enemyManager;
	_enemyManager->init(_collisionRc);
	
	m_camera->setCameraX(-16);
	m_camera->setCameraY(-146);

	m_player->getPlayerImage()->setX(469);
	m_player->getPlayerImage()->setY(794);
	m_player->getPlayerImage()->setFrameX(1);
	m_camera->setCameraX(-16);
	m_camera->setCameraY(-483);

	_ui = new UI;
	_ui->init();
	_bossUI = new bossUI;
	_bossUI->init(_enemyManager->getBoss());
	_sound = new soundOption;
	_sound->init();
	_sound->update();
	_enemyManager->setIsBossScene(true);

	_index = 0;
	_playerManager->setEnemyManagerLink(_enemyManager);

	sound = SOUNDMANAGER->getVolume();

	SOUNDMANAGER->stop("dungeonBGM");
	SOUNDMANAGER->play("bossBGM", sound);
	return S_OK;
}

void bossScene::release()
{
	SAFE_DELETE(_playerManager);
	SAFE_DELETE(_enemyManager);
	SAFE_DELETE(_ui);
	SAFE_DELETE(_collisionRc);
	SAFE_DELETE(_bossUI);
}

void bossScene::update()
{
	_playerManager->update();
	_enemyManager->update();
	_ui->update();
	_bossUI->update();
	if (_playerManager->getIsReset())SCENEMANAGER->changeScene("mainScene");
}

void bossScene::render()
{
	IMAGEMANAGER->render("bossMap", getMemDC(), m_camera->getCameraX(), m_camera->getCameraY());
	_ui->render();
	_enemyManager->render();
	_bossUI->render();
	_playerManager->render();
}
