#include "stdafx.h"
#include "mapToolSelectScene.h"


mapToolSelectScene::mapToolSelectScene()
{
}


mapToolSelectScene::~mapToolSelectScene()
{
}

HRESULT mapToolSelectScene::init()
{
	IMAGEMANAGER->addImage("background", "images/Scene/title.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("buttonUI", "images/Scene/back.bmp", 213, 64, true, RGB(255, 0, 255));

	_mapToolRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, IMAGEMANAGER->findImage("buttonUI")->getWidth(), IMAGEMANAGER->findImage("buttonUI")->getHeight());
	_testRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 100, IMAGEMANAGER->findImage("buttonUI")->getWidth(), IMAGEMANAGER->findImage("buttonUI")->getHeight());
	_backRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 200, IMAGEMANAGER->findImage("buttonUI")->getWidth(), IMAGEMANAGER->findImage("buttonUI")->getHeight());
	return S_OK;
}

void mapToolSelectScene::release()
{

}

void mapToolSelectScene::update()
{

	if (PtInRect(&_mapToolRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		SCENEMANAGER->changeScene("maptoolScene");
		SOUNDMANAGER->stop("intro");
	}
	if (PtInRect(&_testRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		SCENEMANAGER->changeScene("mapToolTestSelect");

	}
	if (PtInRect(&_backRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		SCENEMANAGER->changeScene("mainScene");
		SOUNDMANAGER->stop("intro");
	}
}

void mapToolSelectScene::render()
{
	IMAGEMANAGER->findImage("background")->render(getMemDC());
	if (KEYMANAGER->isToggleKey(VK_TAB)) {
		Rectangle(getMemDC(), _mapToolRc.left, _mapToolRc.top, _mapToolRc.right, _mapToolRc.bottom);
		Rectangle(getMemDC(), _testRc.left, _testRc.top, _testRc.right, _testRc.bottom);
		Rectangle(getMemDC(), _backRc.left, _backRc.top, _backRc.right, _backRc.bottom);
	}
	IMAGEMANAGER->findImage("buttonUI")->render(getMemDC(), _mapToolRc.left, _mapToolRc.top);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), WINSIZEX / 2 - 30, WINSIZEY / 2 - 10, "MAPTOOL", 7);
	IMAGEMANAGER->findImage("buttonUI")->render(getMemDC(), _testRc.left, _testRc.top);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), WINSIZEX / 2 - 50, WINSIZEY / 2 + 90, "MAPTOOL TEST", 12);
	IMAGEMANAGER->findImage("buttonUI")->render(getMemDC(), _backRc.left, _backRc.top);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), WINSIZEX / 2 - 20, WINSIZEY / 2 + 190, "BACK", 4);
}
