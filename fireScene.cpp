#include "stdafx.h"
#include "fireScene.h"

HRESULT fireScene::init()
{
	m_player->init();
	//IMAGEMANAGER->addImage("FireMap", "images/FireMap.bmp", WINSIZEX*9 , WINSIZEY*10 , true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("FireMap", "images/FireMap.bmp", WINSIZEX*6 , WINSIZEY*8 , true, RGB(255, 0, 255)); 
	_blackImage = IMAGEMANAGER->addImage("blackImage", "images/blackImage.bmp", WINSIZEX* 6, WINSIZEY*8 , true, RGB(255, 0, 255));
	_teleportEffect = IMAGEMANAGER->addFrameImage("teleportEffect", "images/teleportEffect2.bmp", 768 * 2.5, 512, 8, 1, true, RGB(255, 0, 255));


	_collisionRc = new collisionRc;
	_collisionRc->init();

	_ui = new UI;
	_ui->init();
	
	_shop = new shop;
	_shop->init();  

	_playerManager = new playerManager;
	_playerManager->init(_collisionRc);

	_enemyManager = new enemyManager;
	_enemyManager->init(_collisionRc); 
	 
	_sound = new soundOption;
	_sound->init();
	_sound->update();

	_playerManager->setEnemyManagerLink(_enemyManager); 
	
	_isStart = true;
	_blackImageAlpha = 255;
	_teleportEffectCount = 0;
	_teleportEffectFrameX = 0;
	_isTeleportEnd = false;

	_isSpawnRc1 = false;
	_isSpawnRc2 = false;
	_isSpawnRc3 = false;

	sound = SOUNDMANAGER->getVolume();
	SOUNDMANAGER->stop("intro");
	SOUNDMANAGER->play("dungeonBGM", sound);

	 
	return S_OK;
}

void fireScene::release()
{
	SAFE_DELETE(_playerManager);  
	SAFE_DELETE(_enemyManager);
	SAFE_DELETE(_shop); 
	SAFE_DELETE(_ui);
	
}

void fireScene::update()
{
	 
	RECT temp;
	_spawnRc1 = RectMake(m_camera->getCameraX() + 2620, m_camera->getCameraY() + 2835, 310, 30);
	_spawnRc2 = RectMake(m_camera->getCameraX() + 4900, m_camera->getCameraY() + 990, 310, 30);
	_spawnRc3 = RectMake(m_camera->getCameraX() + 1730, m_camera->getCameraY() + 4560, 30, 160);
	_spawnRc4 = RectMake(m_camera->getCameraX() + 3460, m_camera->getCameraY() + 5720, 300, 30);

	if (IntersectRect(&temp, &m_player->getPlayerRc(), &_spawnRc1) && !_isSpawnRc1)
	{
		_enemyManager->createMonster(2180, 2250, 1, 0, 1);
		_enemyManager->createMonster(2800, 2180, 2, 0, 1);
		_enemyManager->createMonster(2850, 2360, 2, 0, 1);
		_isSpawnRc1 = true;
	}

	if (IntersectRect(&temp, &m_player->getPlayerRc(), &_spawnRc2) && !_isSpawnRc2)
	{
		_enemyManager->createMonster(4495, 335, 2, 0, 2);
		_enemyManager->createMonster(4495, 550, 1, 2, 1);
		_enemyManager->createMonster(5150, 380, 1, 1, 1);
		_enemyManager->createMonster(5100, 650, 2, 0, 0);
		_isSpawnRc2 = true;
	}

	if (IntersectRect(&temp, &m_player->getPlayerRc(), &_spawnRc3) && !_isSpawnRc3)
	{
		_enemyManager->createMonster(315, 4450, 2, 1, 1);
		_enemyManager->createMonster(315, 4550, 2, 1, 1);
		_enemyManager->createMonster(750, 4350, 1, 1, 3);
		_enemyManager->createMonster(1130, 4570, 2, 0, 3);
		_isSpawnRc3 = true;
	}

	if (IntersectRect(&temp, &m_player->getPlayerRc(), &_spawnRc4) && !_isSpawnRc4)
	{
		_enemyManager->createMonster(3300, 5780, 0, 0, 1);
		_isSpawnRc4 = true;
	}

	if (_isSpawnRc1 && _isSpawnRc2 && _isSpawnRc3 && _enemyManager->getVMinion().size() == 0)
		_playerManager->setIsClearCheck(true);
	_playerManager->update();
	_enemyManager->update(); 
	_ui->update(); 
	_shop->update();
	_playerManager->setEnemyManagerLink(_enemyManager);
	// 보스 맵 이동
	if (_playerManager->getPlayerTeleport()->getIsChangePosition()) SCENEMANAGER->changeScene("bossMap");
	else if(_playerManager->getIsReset())SCENEMANAGER->changeScene("mainScene");
	// 시작 시 화면 조정
	if (_isStart)
	{
		_blackImageAlpha -= 10; 
		if (_teleportEffectCount % 3 == 0)
		{
			_teleportEffect->setFrameX(_teleportEffectFrameX);
			_teleportEffectFrameX++;
			if (_teleportEffectFrameX > _teleportEffect->getMaxFrameX()) _isTeleportEnd = true;
		}
		_teleportEffectCount++;
		
		
		if (_blackImageAlpha < 3)
		{
			_isStart = false;
		} 
	}
	//// 사망 시 
	//if (m_player->getIsPlayerDeath())
	//{
	//	_blackImageAlpha += 10;
	//	if (_blackImageAlpha > 255)
	//	{
	//		_blackImageAlpha = 255;
	//	}
	//}
}

void fireScene::render()
{ 
	IMAGEMANAGER->render("FireMap", getMemDC(),m_camera->getCameraX() , m_camera->getCameraY());
	_shop->render(); 
	_enemyManager->render(); 
	_ui->render();
	_playerManager->render();
	 
	if (_isStart)
	{
		_blackImage->alphaRender(getMemDC(), _blackImageAlpha); 
		if(!_isTeleportEnd)
		_teleportEffect->frameRender(getMemDC(),
			m_player->getPlayerImage()->getX() + m_camera->getCameraX() - 55,
			m_player->getPlayerImage()->getY() + m_camera->getCameraY() - 300); 
	}
}
