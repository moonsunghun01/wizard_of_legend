#include "stdafx.h"
#include "playerInventory.h"

HRESULT playerInventory::init()
{
	_playerInventoryImage = IMAGEMANAGER->addImage("inventory", "images/inventory2.bmp", 432, 630, true, RGB(255, 0, 255));
	_playerItemSelectImage = IMAGEMANAGER->addImage("selectItem", "images/selectItem.bmp", 37, 37, true, RGB(255, 0, 255));

	
	return S_OK;
}

void playerInventory::release()
{
}

void playerInventory::update()
{
	for (int i = 0; i < m_player->getVPlayerItem().size(); i++)
	{ 
		m_player->getVPlayerItem().at(i).image->setX(m_player->getPlayerImage()->getX() + m_camera->getCameraX() + 150 + (i * 75) - (i / 5 * 375));
		m_player->getVPlayerItem().at(i).image->setY(m_player->getPlayerImage()->getY() + m_camera->getCameraY() + 55 + (i / 5 * 75)); 
	}
	showItemInfo();

	for (int i = 0; i < m_player->getVPlayerSkill().size(); i++)
	{
		m_player->getVPlayerSkill().at(i).image->setX(m_player->getPlayerImage()->getX() + m_camera->getCameraX() + 150 + (i * 75) - (i / 5 * 375));
		m_player->getVPlayerSkill().at(i).image->setY(m_player->getPlayerImage()->getY() + m_camera->getCameraY() -140 + (i / 5 * 75));
	}
	showSkillInfo();
}

void playerInventory::render()
{
	_playerInventoryImage->alphaRender(getMemDC(),m_player->getPlayerImage()->getX()  + m_camera->getCameraX() + 100
		, m_player->getPlayerImage()->getY() + m_camera->getCameraY() - 200,245) ;
	for (int i = 0; i < m_player->getVPlayerItem().size(); i++)
	{
		m_player->getVPlayerItem().at(i).image->render(getMemDC(), m_player->getVPlayerItem().at(i).image->getX()
			, m_player->getVPlayerItem().at(i).image->getY()); 
	}

	if (_isShowItemInfo)
	{
		_playerItemSelectImage->render(getMemDC(), m_player->getVPlayerItem().at(_itemIndex).image->getX()
			, m_player->getVPlayerItem().at(_itemIndex).image->getY() );

		wsprintf(_str, "%s", m_player->getVPlayerItem().at(_itemIndex).name);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), m_player->getPlayerImage()->getX() + m_camera->getCameraX() + 150
			, m_player->getPlayerImage()->getY() + m_camera->getCameraY() + 250
			, _str, strlen(_str));

		wsprintf(_str, "%s", m_player->getVPlayerItem().at(_itemIndex).description.c_str());
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), m_player->getPlayerImage()->getX() + m_camera->getCameraX() + 150
			, m_player->getPlayerImage()->getY() + m_camera->getCameraY() + 300
			, _str, strlen(_str));  //Á¡¼ö		
	}

	for (int i = 0; i < m_player->getVPlayerSkill().size(); i++)
	{
		m_player->getVPlayerSkill().at(i).image->render(getMemDC(), m_player->getVPlayerSkill().at(i).image->getX()
			, m_player->getVPlayerSkill().at(i).image->getY());
	}

	if (_isShowSkillInfo)
	{
		_playerItemSelectImage->render(getMemDC(), m_player->getVPlayerSkill().at(_skillIndex).image->getX()
			, m_player->getVPlayerSkill().at(_skillIndex).image->getY());

		wsprintf(_str, "%s", m_player->getVPlayerSkill().at(_skillIndex).name);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), m_player->getPlayerImage()->getX() + m_camera->getCameraX() + 150
			, m_player->getPlayerImage()->getY() + m_camera->getCameraY() + 250
			, _str, strlen(_str));

		wsprintf(_str, "%s", m_player->getVPlayerSkill().at(_skillIndex).description.c_str());
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), m_player->getPlayerImage()->getX() + m_camera->getCameraX() + 150
			, m_player->getPlayerImage()->getY() + m_camera->getCameraY() + 300
			, _str, strlen(_str));  	
	}
}

void playerInventory::showItemInfo()
{
	for (int i = 0; i < m_player->getVPlayerItem().size(); i++)
	{
		if (PtInRect(&m_player->getVPlayerItem().at(i).itemRc, m_ptMouse))
		{ 
			_isShowItemInfo = true;
			_isShowSkillInfo = false;
			_itemIndex = i;
		}
	}
	if (m_player->getVPlayerItem().empty()) _isShowItemInfo = false;
}

void playerInventory::showSkillInfo()
{
	for (int i = 0; i < m_player->getVPlayerSkill().size(); i++)
	{
		if (PtInRect(&m_player->getVPlayerSkill().at(i).skillRc, m_ptMouse))
		{
			_isShowItemInfo = false;
			_isShowSkillInfo = true;
			_skillIndex = i;
		}
	}
	if (m_player->getVPlayerSkill().empty()) _isShowSkillInfo = false; 
}
