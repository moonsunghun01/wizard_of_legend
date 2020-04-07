#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	_hp = 500; 
	_atk = 15;
	_def = 15;
	_moveSpeed = 5; 
	_money = 15500;
	_playerImage = IMAGEMANAGER->addFrameImage("player", "images/player.bmp", 1700 * 0.75, 4800 * 0.75, 10, 24, true, RGB(255, 0, 255));
	_playerImage->setFrameX(0);
	_playerImage->setFrameY(0);
	_playerRc  = RectMake(_playerImage->getX(), _playerImage->getY(), _playerImage->getFrameWidth(), _playerImage->getFrameHeight());

	_playerEqiupWeapon.itemKind = item_Empty;
	_playerEqiupArmor.itemKind = item_Empty;
	_playerEqiupPotion.itemKind = item_Empty;

	_currentHp = _hp;
	_currentAtk = _atk;
	_currentDef = _def;
	_currentMoveSpeed = _moveSpeed;
	_isHit = false;
	_isPlayerDeath = false; 
	m_camera->setCameraX(-3091);
	m_camera->setCameraY(-4846);
	_vPlayerItem.clear();
	_vPlayerSkill.clear(); 
	_playerEqiupWeapon = {};
	_playerEqiupArmor = {};
	_playerEqiupPotion = {};

	_playerLButtonSkill = {};
	_playerDashSkill = {};
	_playerRButtonSkill = {};
	_playerQButtonSkill = {};
	_playerEButtonSkill = {};
	_playerRRButtonSkill = {};
	return S_OK;
}

void player::update()
{
	 _playerRc = RectMake(_playerImage->getX() + m_camera->getCameraX() + 45, _playerImage->getY() + m_camera->getCameraY() + 25,
		40, 100); 
	for (int i = 0; i < _vPlayerItem.size(); i++)
	{
		_vPlayerItem.at(i).itemRc = RectMake(_vPlayerItem.at(i).image->getX(), _vPlayerItem.at(i).image->getY(),
			_vPlayerItem.at(i).image->getWidth(), _vPlayerItem.at(i).image->getHeight());
	}
	for (int i = 0; i < _vPlayerSkill.size(); i++)
	{
		_vPlayerSkill.at(i).skillRc = RectMake(_vPlayerSkill.at(i).image->getX(), _vPlayerSkill.at(i).image->getY(),
			_vPlayerSkill.at(i).image->getWidth(), _vPlayerSkill.at(i).image->getHeight());
	}

	if (_currentHp > _hp) _currentHp = _hp;
}

void player::addPlayerItem(TAGITEMINFO buyItem)
{
	_vPlayerItem.push_back(buyItem);
}

void player::addPlayerSkill(SKILLBOOK buySkill)
{
	_vPlayerSkill.push_back(buySkill);
}
