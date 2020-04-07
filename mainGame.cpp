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
	IMAGEMANAGER->addFrameImage("����", "images/monster/ghoul.bmp", 1800, 1000, 9, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��", "images/monster/Golem.bmp", 1440, 1400, 6, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "images/monster/slime.bmp", 1190, 320, 17, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ȯ��", "images/monster/SummonerSource.bmp", 750, 1050, 5, 7, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ȯī��", "images/monster/appearEnemy_1080x187_9x1.bmp", 1080, 187, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "images/monster/lancer.bmp", 1462, 1200, 9, 5, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("��������", "images/monster/smallSlash.bmp", 246, 328, 3, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ū����", "images/monster/largeSlash.bmp", 492, 328, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "images/monster/coin.bmp", 32 * 4, 8 * 4, 4, 1, true, RGB(255, 0, 255));

	gameNode::init(true);

	SCENEMANAGER->addScene("fireMap", new fireScene);							// ���� ����
	SCENEMANAGER->addScene("bossMap", new bossScene);							// ����

	SCENEMANAGER->addScene("mainScene", new mainScene);							// ����
	SCENEMANAGER->addScene("maptoolSelectScene", new mapToolSelectScene);		// ���� �� scene
	SCENEMANAGER->addScene("maptoolScene", new mapToolScene);					// ����
	SCENEMANAGER->addScene("mapToolTestMap", new testMapScene);					// �׽�Ʈ
	SCENEMANAGER->addScene("mapToolSecondTestMap", new testSecondMapScene);
	SCENEMANAGER->addScene("sound", new soundOption);							//���� �ɼ�

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
	//��� ��Ʈ��
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//====================================================
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	//=====================================================
	//������� ������ HDC�� �׸���.(��������!!)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}









