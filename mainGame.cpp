#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}

HRESULT mainGame::init()
{
	IMAGEMANAGER->addFrameImage("구울", "images/monster/ghoul.bmp", 1800, 1000, 9, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("골렘", "images/monster/Golem.bmp", 1440, 1400, 6, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("슬라임", "images/monster/slime.bmp", 1190, 320, 17, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("소환사", "images/monster/SummonerSource.bmp", 750, 1050, 5, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("소환카드", "images/monster/appearEnemy_1080x187_9x1.bmp", 1080, 187, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("랜서", "images/monster/lancer.bmp", 1462, 1200, 9, 5, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("작은공격", "images/monster/smallSlash.bmp", 246, 328, 3, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("큰공격", "images/monster/largeSlash.bmp", 492, 328, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("코인", "images/monster/coin.bmp", 32 * 4, 8 * 4, 4, 1, true, RGB(255, 0, 255));

	gameNode::init(true);

	SCENEMANAGER->addScene("fireMap", new fireScene);							// 메인 던전
	SCENEMANAGER->addScene("bossMap", new bossScene);							// 보스

	SCENEMANAGER->addScene("mainScene", new mainScene);							// 메인
	SCENEMANAGER->addScene("maptoolSelectScene", new mapToolSelectScene);		// 맵툴 상세 scene
	SCENEMANAGER->addScene("maptoolScene", new mapToolScene);					// 맵툴
	SCENEMANAGER->addScene("mapToolTestMap", new testMapScene);					// 테스트
	SCENEMANAGER->addScene("mapToolSecondTestMap", new testSecondMapScene);
	SCENEMANAGER->addScene("sound", new soundOption);							//사운드 옵션

	SCENEMANAGER->addScene("mapToolTestSelect", new testMapToolSelect);


	SCENEMANAGER->changeScene("fireMap");
	//SCENEMANAGER->changeScene("mainScene");

	//SCENEMANAGER->changeScene("bossMap");


	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
}

void mainGame::update()
{
	gameNode::update();
	SCENEMANAGER->update();
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changeScene("FireMap");
	if (KEYMANAGER->isOnceKeyDown(VK_F2)) SCENEMANAGER->changeScene("bossMap");
	ANIMATIONMANAGER->update();

}

void mainGame::render(/*HDC hdc*/)
{
	//흰색 비트맵
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//====================================================
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	//=====================================================
	//백버퍼의 내용을 HDC에 그린다.(지우지마!!)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}









