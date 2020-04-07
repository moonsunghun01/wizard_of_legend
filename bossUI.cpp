#include "stdafx.h"
#include "bossUI.h"


bossUI::bossUI()
{
}


bossUI::~bossUI()
{
}

HRESULT bossUI::init()
{ 
	return S_OK;
}

HRESULT bossUI::init(Boss* boss)
{
	_boss = boss; 
	_bossHpBarWidth = 225;
	_bossHpBar = IMAGEMANAGER->addImage("bossHpBar", "images/Boss/bossHpBar.bmp", _bossHpBarWidth, 30, true, RGB(255, 0, 255));
	_bossHpBar->setX(WINSIZEX - 362);
	_bossHpBar->setY(65);

	_bossHpBarBackground = IMAGEMANAGER->addImage("bossHpBackgroundBar", "images/Boss/bosshpBarBack_300x41.bmp", 240, 50, true, RGB(255, 0, 255));
	_bossHpBarBackground->setX(WINSIZEX - 370);
	_bossHpBarBackground->setY(55);

	_bossHpBarLeft = IMAGEMANAGER->addImage("bossHpBarLeft", "images/Boss/bosshpBarLeftDecorate.bmp", 34, 54, true, RGB(255, 0, 255));
	_bossFace = IMAGEMANAGER->addImage("bossFace", "images/Boss/BossIcon.bmp", 120 * 0.75, 126 * 0.75, true, RGB(255, 0, 255));

	return S_OK;
}

void bossUI::release()
{
}

void bossUI::update()
{ 
	_bossHpBarWidth = 225 * _boss->getBossCurrentHp() / 1000;
}

void bossUI::render()
{
	_bossHpBarBackground->render(getMemDC(), _bossHpBarBackground->getX(), _bossHpBarBackground->getY());
	_bossHpBar->render(getMemDC(), _bossHpBar->getX() + (225 - _bossHpBarWidth), _bossHpBar->getY(), 0, 0, _bossHpBarWidth, _bossHpBar->getHeight());
	 
	_bossHpBarLeft->render(getMemDC(), _bossHpBarBackground->getX() - _bossHpBarLeft->getWidth(), _bossHpBarBackground->getY() - 5);
	_bossFace->render(getMemDC(), _bossHpBarBackground->getX() + _bossHpBarBackground->getWidth(), _bossHpBarBackground->getY() - 20);
}
