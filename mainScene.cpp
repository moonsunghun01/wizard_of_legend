#include "stdafx.h"
#include "mainScene.h"


mainScene::mainScene()
{
}


mainScene::~mainScene()
{
}

HRESULT mainScene::init()
{
	_sound = new soundOption;
	_sound->init();
	_sound->update();

	IMAGEMANAGER->addImage("background", "images/Scene/title.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("buttonUI", "images/Scene/back.bmp", 213, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("제목", "images/Scene/제목.bmp", 800, 150, true, RGB(255, 0, 255));

	_titleRc = RectMakeCenter(WINSIZEX / 2, 150, IMAGEMANAGER->findImage("제목")->getWidth(), IMAGEMANAGER->findImage("제목")->getHeight());
	_startRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, IMAGEMANAGER->findImage("buttonUI")->getWidth(), IMAGEMANAGER->findImage("buttonUI")->getHeight());
	_mapToolRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 100, IMAGEMANAGER->findImage("buttonUI")->getWidth(), IMAGEMANAGER->findImage("buttonUI")->getHeight());
	_soundOptionRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 200, IMAGEMANAGER->findImage("buttonUI")->getWidth(), IMAGEMANAGER->findImage("buttonUI")->getHeight());
	_exitRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 300, IMAGEMANAGER->findImage("buttonUI")->getWidth(), IMAGEMANAGER->findImage("buttonUI")->getHeight());
	//사운드 추가 (mainGame에 선언시 문제 발생)
	SOUNDMANAGER->addSound("intro", "sound/intro.mp3", false, true);
	SOUNDMANAGER->addSound("dungeonBGM", "sound/던전 확정.mp3", false, true);
	SOUNDMANAGER->addSound("maptoolBGM", "sound/마을 확정.mp3", false, true);
	SOUNDMANAGER->addSound("bossBGM", "sound/보스 확정.mp3", false, true);
	SOUNDMANAGER->addSound("피즈", "sound/피즈.mp3", false, false);
	SOUNDMANAGER->addSound("상어다", "sound/상어다.mp3", false, false);
	SOUNDMANAGER->addSound("천둥", "sound/천둥.mp3", false, false);

	sound = SOUNDMANAGER->getVolume();

	SOUNDMANAGER->play("intro", sound);  //노래 재생
	SOUNDMANAGER->stop("dungeonBGM");
	SOUNDMANAGER->stop("bossBGM");
	return S_OK;
}

void mainScene::release()
{

}

void mainScene::update()
{
	if (PtInRect(&_startRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		SCENEMANAGER->changeScene("fireMap");
	}
	if (PtInRect(&_mapToolRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		SCENEMANAGER->changeScene("maptoolSelectScene");
	}
	if (PtInRect(&_soundOptionRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		SCENEMANAGER->changeScene("sound");
	}
	if (PtInRect(&_exitRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		SOUNDMANAGER->stop("intro");
		exit(0);
	}
}

void mainScene::render()
{
	char _strStart[] = "START";
	char _strExit[] = "EXIT";
	char _strMapTool[] = "MAPTOOL";
	IMAGEMANAGER->findImage("background")->render(getMemDC());
	IMAGEMANAGER->findImage("제목")->render(getMemDC(), _titleRc.left, _titleRc.top);
	if (KEYMANAGER->isToggleKey(VK_TAB)) {
		Rectangle(getMemDC(), _mapToolRc.left, _mapToolRc.top, _mapToolRc.right, _mapToolRc.bottom);
		Rectangle(getMemDC(), _startRc.left, _startRc.top, _startRc.right, _startRc.bottom);
		Rectangle(getMemDC(), _exitRc.left, _exitRc.top, _exitRc.right, _exitRc.bottom);
		Rectangle(getMemDC(), _soundOptionRc.left, _soundOptionRc.top, _soundOptionRc.right, _soundOptionRc.bottom);
		Rectangle(getMemDC(), _titleRc.left, _titleRc.top, _titleRc.right, _titleRc.bottom);
	}
	IMAGEMANAGER->findImage("buttonUI")->render(getMemDC(), _startRc.left, _startRc.top);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), WINSIZEX / 2 - 25, WINSIZEY / 2 - 10, "START", 5);

	IMAGEMANAGER->findImage("buttonUI")->render(getMemDC(), _mapToolRc.left, _mapToolRc.top);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), WINSIZEX / 2 - 30, WINSIZEY / 2 + 90, "MAPTOOL", 7);

	IMAGEMANAGER->findImage("buttonUI")->render(getMemDC(), _soundOptionRc.left, _soundOptionRc.top);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), WINSIZEX / 2 - 27, WINSIZEY / 2 + 190, "OPTION", 6);

	IMAGEMANAGER->findImage("buttonUI")->render(getMemDC(), _exitRc.left, _exitRc.top);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), WINSIZEX / 2 - 15, WINSIZEY / 2 + 290, "EXIT", 4);
}