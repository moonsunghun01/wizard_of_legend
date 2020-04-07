#include "stdafx.h"
#include "playerStatus.h"

HRESULT playerStatus::init()
{
	_playerStatusImage = IMAGEMANAGER->addImage("status", "images/상태창.bmp", 432, 630, true, RGB(255, 0, 255));

	_weaponRc = RectMake(122,425,40,40);
	_armorRc = RectMake(250, 425,40,40);
	_potionRc = RectMake(370, 425,40,40);

	_lButtonSkillRc = RectMake(104, 182,40,40);
	_dashSkillRc	 = RectMake(160, 182,40,40);
	_rButtonSkillRc = RectMake(216, 182,40,40);
	_qButtonSkillRc = RectMake(276, 182,40,40);
	_eButtonSkillRc = RectMake(330, 182,40,40);
	_rrButtonSkillRc = RectMake(390, 182,40,40);
	return S_OK;
}

void playerStatus::release()
{
}

void playerStatus::update()
{
}

void playerStatus::render()
{
	_playerStatusImage->render(getMemDC(), m_player->getPlayerImage()->getX() + m_camera->getCameraX() - 400
		, m_player->getPlayerImage()->getY() + m_camera->getCameraY() - 200);
	// 스킬 정렬
	if (m_player->getPlayerLButtonSkill().itemKind == item_Skill)
	{
		m_player->getPlayerLButtonSkill().image->render(getMemDC(), _lButtonSkillRc.left, _lButtonSkillRc.top);
	}

	if (m_player->getPlayerDashSkill().itemKind == item_dashSkill)
	{
		m_player->getPlayerDashSkill().image->render(getMemDC(), _dashSkillRc.left, _dashSkillRc.top);
	}

	if (m_player->getPlayerRButtonSkill().itemKind == item_Skill)
	{
		m_player->getPlayerRButtonSkill().image->render(getMemDC(), _rButtonSkillRc.left, _rButtonSkillRc.top);
	}

	if (m_player->getPlayerQButtonSkill().itemKind == item_Skill)
	{
		m_player->getPlayerQButtonSkill().image->render(getMemDC(), _qButtonSkillRc.left, _qButtonSkillRc.top);
	}

	if (m_player->getPlayerEButtonSkill().itemKind == item_Skill)
	{
		m_player->getPlayerEButtonSkill().image->render(getMemDC(), _eButtonSkillRc.left, _eButtonSkillRc.top);
	}

	if (m_player->getPlayerRRButtonSkill().itemKind == item_Skill)
	{
		m_player->getPlayerRRButtonSkill().image->render(getMemDC(), _rrButtonSkillRc.left, _rrButtonSkillRc.top);
	}

	// 아이템 정렬
	if (m_player->getPlayerEqiupWeapon().itemKind == item_Weapon)
	{
		m_player->getPlayerEqiupWeapon().image->render(getMemDC(),_weaponRc.left, _weaponRc.top);
	}
	if (m_player->getPlayerEqiupArmor().itemKind == item_Armor)
	{
		m_player->getPlayerEqiupArmor().image->render(getMemDC(), _armorRc.left, _armorRc.top);
	}
	if (m_player->getPlayerEqiupPotion().itemKind == item_potion)
	{
		m_player->getPlayerEqiupPotion().image->render(getMemDC(), _potionRc.left, _potionRc.top);
	}

	
	wsprintf(_str, "Hp                   : %d", m_player->getHp());
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), m_player->getPlayerImage()->getX() + m_camera->getCameraX() -330
		, m_player->getPlayerImage()->getY() + m_camera->getCameraY() + 250
		, _str, strlen(_str));
	wsprintf(_str, "Atk                   : %d", m_player->getCurrentAtk());
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), m_player->getPlayerImage()->getX() + m_camera->getCameraX() - 330
		, m_player->getPlayerImage()->getY() + m_camera->getCameraY() + 270
		, _str, strlen(_str));
	wsprintf(_str, "Def                  : %d", m_player->getCurrentDef());
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), m_player->getPlayerImage()->getX() + m_camera->getCameraX() - 330
		, m_player->getPlayerImage()->getY() + m_camera->getCameraY() + 290
		, _str, strlen(_str));
	wsprintf(_str, "MoveSpeed     : %d", m_player->getCurrentMoveSpeed());
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), m_player->getPlayerImage()->getX() + m_camera->getCameraX() - 330
		, m_player->getPlayerImage()->getY() + m_camera->getCameraY() + 310
		, _str, strlen(_str));

	wsprintf(_str, "보유 골드     : %d", m_player->getMoney());
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), m_player->getPlayerImage()->getX() + m_camera->getCameraX() - 330
		, m_player->getPlayerImage()->getY() + m_camera->getCameraY() + 350
		, _str, strlen(_str));
/*
	wsprintf(_str, "Hp : %d", m_player->getVPlayerItem().at(_itemIndex).description.c_str());
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), m_player->getPlayerImage()->getX() + m_camera->getCameraX() + 150
		, m_player->getPlayerImage()->getY() + m_camera->getCameraY() + 300
		, _str, strlen(_str));*/
/*
	Rectangle(getMemDC(), _weaponRc.left, _weaponRc.top, _weaponRc.right, _weaponRc.bottom);
	Rectangle(getMemDC(), _armorRc.left, _armorRc.top, _armorRc.right, _armorRc.bottom);
	Rectangle(getMemDC(), _potionRc.left, _potionRc.top, _potionRc.right, _potionRc.bottom);
	Rectangle(getMemDC(), _lButtonSkillRc.left, _lButtonSkillRc.top, _lButtonSkillRc.right, _lButtonSkillRc.bottom);
	Rectangle(getMemDC(), _dashSkillRc.left, _dashSkillRc.top, _dashSkillRc.right, _dashSkillRc.bottom);
	Rectangle(getMemDC(), _rButtonSkillRc.left, _rButtonSkillRc.top, _rButtonSkillRc.right, _rButtonSkillRc.bottom);
	Rectangle(getMemDC(), _qButtonSkillRc.left, _qButtonSkillRc.top, _qButtonSkillRc.right, _qButtonSkillRc.bottom);
	Rectangle(getMemDC(), _eButtonSkillRc.left, _eButtonSkillRc.top, _eButtonSkillRc.right, _eButtonSkillRc.bottom);
	*/
}
