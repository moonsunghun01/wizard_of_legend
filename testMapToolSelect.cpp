#include "stdafx.h"
#include "testMapToolSelect.h"

testMapToolSelect::testMapToolSelect()
{
}

testMapToolSelect::~testMapToolSelect()
{
}

HRESULT testMapToolSelect::init()
{
	IMAGEMANAGER->addImage("background", "images/Scene/title.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("buttonUI", "images/Scene/back.bmp", 213, 64, true, RGB(255, 0, 255));
	_testFirstRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, IMAGEMANAGER->findImage("buttonUI")->getWidth(), IMAGEMANAGER->findImage("buttonUI")->getHeight());
	_testSecondRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 100, IMAGEMANAGER->findImage("buttonUI")->getWidth(), IMAGEMANAGER->findImage("buttonUI")->getHeight());
	_backRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 200, IMAGEMANAGER->findImage("buttonUI")->getWidth(), IMAGEMANAGER->findImage("buttonUI")->getHeight());

	return S_OK;
}

void testMapToolSelect::release()
{
}

void testMapToolSelect::update()
{
	if (PtInRect(&_testFirstRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		SCENEMANAGER->changeScene("mapToolTestMap");
		SOUNDMANAGER->stop("intro");
	}
	if (PtInRect(&_testSecondRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		SCENEMANAGER->changeScene("mapToolSecondTestMap");
		SOUNDMANAGER->stop("intro");
	}
	if (PtInRect(&_backRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		SCENEMANAGER->changeScene("mainScene");
		SOUNDMANAGER->stop("intro");
	}
}

void testMapToolSelect::render()
{
	IMAGEMANAGER->findImage("background")->render(getMemDC());
	if (KEYMANAGER->isToggleKey(VK_TAB)) {
		Rectangle(getMemDC(), _testFirstRc.left, _testFirstRc.top, _testFirstRc.right, _testFirstRc.bottom);
		Rectangle(getMemDC(), _testSecondRc.left, _testSecondRc.top, _testSecondRc.right, _testSecondRc.bottom);
		Rectangle(getMemDC(), _backRc.left, _backRc.top, _backRc.right, _backRc.bottom);
	}
	IMAGEMANAGER->findImage("buttonUI")->render(getMemDC(), _testFirstRc.left, _testFirstRc.top);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), WINSIZEX / 2 - 30, WINSIZEY / 2 - 10, "First", 5);
	IMAGEMANAGER->findImage("buttonUI")->render(getMemDC(), _testSecondRc.left, _testSecondRc.top);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), WINSIZEX / 2 - 50, WINSIZEY / 2 + 90, "Second", 6);
	IMAGEMANAGER->findImage("buttonUI")->render(getMemDC(), _backRc.left, _backRc.top);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), WINSIZEX / 2 - 20, WINSIZEY / 2 + 190, "BACK", 4);
}
