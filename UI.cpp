#include "stdafx.h"
#include "UI.h"

HRESULT UI::init()
{
	_playerHpWight = 207;
	_playerFace = IMAGEMANAGER->addImage("playerFace", "images/interface/playerFace.bmp", 279, 69, true, RGB(255, 0, 255));
	_playerHp = IMAGEMANAGER->addImage("hpBar", "images/interface/hpBar.bmp", _playerHpWight, 30, true, RGB(255, 0, 255));

	_statusButton = IMAGEMANAGER->addImage("statusButtom", "images/interface/statusButton.bmp", 168 * 2, 52 * 2,true,RGB(255,0,255));
	_1Button = IMAGEMANAGER->addImage("1", "images/interface/1.bmp", 45 , 45 ,true,RGB(255,0,255));
	_potionButton = IMAGEMANAGER->addImage("skillUI", "images/interface/skillUI.bmp", 45 , 45 ,true,RGB(255,0,255));
	
	
	_lButtonSkillCoolTime = IMAGEMANAGER->addImage("lButtonCoolDown", "images/interface/coolDown.bmp", 57, WINSIZEY - 65, 38, _lButtonSkillHeight,true,RGB(255,0,255));
	_lButtonSkillCoolTimeRc = RectMake(_lButtonSkillCoolTime->getX(),_lButtonSkillCoolTime->getY(), _lButtonSkillCoolTime->getWidth(), _lButtonSkillCoolTime->getHeight() );

	_dashSkillCoolTime = IMAGEMANAGER->addImage("dashCoolDown", "images/interface/coolDown.bmp", 115, WINSIZEY - 65, 38, _dashSkillHeight, true, RGB(255, 0, 255));
	_dashSkillCoolTimeRc = RectMake(_dashSkillCoolTime->getX(), _dashSkillCoolTime->getY(), _dashSkillCoolTime->getWidth(), _dashSkillCoolTime->getHeight());

	_rButtonSkillCoolTime = IMAGEMANAGER->addImage("rlButtonCoolDown", "images/interface/coolDown.bmp", 170, WINSIZEY - 65, 38, _rButtonSkillHeight, true, RGB(255, 0, 255));
	_rButtonSkillCoolTimeRc = RectMake(_rButtonSkillCoolTime->getX(), _rButtonSkillCoolTime->getY(), _rButtonSkillCoolTime->getWidth(), _rButtonSkillCoolTime->getHeight());

	_qButtonSkillCoolTime = IMAGEMANAGER->addImage("qButtonCoolDown", "images/interface/coolDown.bmp", 225, WINSIZEY - 65, 38, _qButtonSkillHeight, true, RGB(255, 0, 255));
	_qButtonSkillCoolTimeRc = RectMake(_qButtonSkillCoolTime->getX(), _qButtonSkillCoolTime->getY(), _qButtonSkillCoolTime->getWidth(), _qButtonSkillCoolTime->getHeight());

	_eButtonSkillCoolTime = IMAGEMANAGER->addImage("eButtonCoolDown", "images/interface/coolDown.bmp", 280, WINSIZEY - 65, 38, _eButtonSkillHeight, true, RGB(255, 0, 255));
	_eButtonSkillCoolTimeRc = RectMake(_eButtonSkillCoolTime->getX(), _eButtonSkillCoolTime->getY(), _eButtonSkillCoolTime->getWidth(), _eButtonSkillCoolTime->getHeight());
	
	_rrButtonSkillCoolTime = IMAGEMANAGER->addImage("rrButtonCoolDown", "images/interface/coolDown.bmp", 335, WINSIZEY - 65, 38, _rrButtonSkillHeight, true, RGB(255, 0, 255));
	_rrButtonSkillCoolTimeRc = RectMake(_rrButtonSkillCoolTime->getX(), _rrButtonSkillCoolTime->getY(), _rrButtonSkillCoolTime->getWidth(), _rrButtonSkillCoolTime->getHeight());

	_potionButtonCoolTime = IMAGEMANAGER->addImage("potionButtonCoolDown", "images/interface/coolDown.bmp", WINSIZEX-97, WINSIZEY - 72, 38, _rrButtonSkillHeight, true, RGB(255, 0, 255));
	_potionButtonCoolTimeRc = RectMake(_potionButtonCoolTime->getX(), _potionButtonCoolTime->getY(), _potionButtonCoolTime->getWidth(), _potionButtonCoolTime->getHeight());

	return S_OK;
}

void UI::release()
{
}

void UI::update()
{
	//HP ¼³Á¤
	_playerHpWight = 207 * m_player->getCurrentHp() / 500;

	if (m_player->getPlayerLButtonSkill().isActive)
	{
		_lButtonSkillCoolTimeCount += TIMEMANAGER->getElapsedTime();
		_lButtonSkillHeight -= (40 / m_player->getPlayerLButtonSkill().skillCoolTime) * TIMEMANAGER->getElapsedTime();
		if (_lButtonSkillCoolTimeCount > m_player->getPlayerLButtonSkill().skillCoolTime)
		{
			SKILLBOOK _tempSkill = m_player->getPlayerLButtonSkill();
			_tempSkill.isActive = false;
			m_player->setPlayerLButtonSkill(_tempSkill);
			_lButtonSkillHeight = 38;
			_lButtonSkillCoolTimeCount = 0;
		}
	}

	if (m_player->getPlayerDashSkill().isActive)
	{
		_dashSkillCoolTimeCount += TIMEMANAGER->getElapsedTime();
		_dashSkillHeight -= (40 / m_player->getPlayerDashSkill().skillCoolTime) * TIMEMANAGER->getElapsedTime();
		if (_dashSkillCoolTimeCount > m_player->getPlayerDashSkill().skillCoolTime)
		{
			SKILLBOOK _tempSkill = m_player->getPlayerDashSkill();
			_tempSkill.isActive = false;
			m_player->setPlayerDashSkill(_tempSkill);
			_dashSkillHeight = 38;
			_dashSkillCoolTimeCount = 0;
		}
	}

	if (m_player->getPlayerRButtonSkill().isActive)
	{
		_rButtonSkillCoolTimeCount += TIMEMANAGER->getElapsedTime();
		_rButtonSkillHeight -= (40 / m_player->getPlayerRButtonSkill().skillCoolTime) * TIMEMANAGER->getElapsedTime();
		if (_rButtonSkillCoolTimeCount > m_player->getPlayerRButtonSkill().skillCoolTime)
		{
			SKILLBOOK _tempSkill = m_player->getPlayerRButtonSkill();
			_tempSkill.isActive = false;
			m_player->setPlayerRButtonSkill(_tempSkill);
			_rButtonSkillHeight = 38;
			_rButtonSkillCoolTimeCount = 0;
		}
	}

	if (m_player->getPlayerQButtonSkill().isActive)
	{
		_qButtonSkillCoolTimeCount += TIMEMANAGER->getElapsedTime();
		_qButtonSkillHeight -= (40 / m_player->getPlayerQButtonSkill().skillCoolTime) * TIMEMANAGER->getElapsedTime();
		if (_qButtonSkillCoolTimeCount > m_player->getPlayerQButtonSkill().skillCoolTime)
		{
			SKILLBOOK _tempSkill = m_player->getPlayerQButtonSkill();
			_tempSkill.isActive = false;
			m_player->setPlayerQButtonSkill(_tempSkill);
			_qButtonSkillHeight = 38;
			_qButtonSkillCoolTimeCount = 0;
		}
	}

	if (m_player->getPlayerEButtonSkill().isActive)
	{
		_eButtonSkillCoolTimeCount += TIMEMANAGER->getElapsedTime();
		
		_eButtonSkillHeight -= (40 / m_player->getPlayerEButtonSkill().skillCoolTime) * TIMEMANAGER->getElapsedTime();

		if (_eButtonSkillCoolTimeCount > m_player->getPlayerEButtonSkill().skillCoolTime)
		{
			SKILLBOOK _tempSkill = m_player->getPlayerEButtonSkill();
			_tempSkill.isActive = false;
			m_player->setPlayerEButtonSkill(_tempSkill);
			_eButtonSkillHeight = 38;
			_eButtonSkillCoolTimeCount = 0;
		} 
	}

	if (m_player->getPlayerRRButtonSkill().isActive)
	{
		_rrButtonSkillCoolTimeCount += TIMEMANAGER->getElapsedTime();

		_rrButtonSkillHeight -= (40 / m_player->getPlayerRRButtonSkill().skillCoolTime) * TIMEMANAGER->getElapsedTime();

		if (_rrButtonSkillCoolTimeCount > m_player->getPlayerRRButtonSkill().skillCoolTime)
		{
			SKILLBOOK _tempSkill = m_player->getPlayerRRButtonSkill();
			_tempSkill.isActive = false;
			m_player->setPlayerRRButtonSkill(_tempSkill);
			_rrButtonSkillHeight = 38;
			_rrButtonSkillCoolTimeCount = 0;
		}
	}

	if (m_player->getPlayerEqiupPotion().isActive)
	{
		_potionButtonCoolTimeCount += TIMEMANAGER->getElapsedTime();

		_potionButtonHeight -= (40 / m_player->getPlayerEqiupPotion().itemCoolTime) * TIMEMANAGER->getElapsedTime();

		if (_potionButtonCoolTimeCount > m_player->getPlayerEqiupPotion().itemCoolTime)
		{
			TAGITEMINFO _tempItem = m_player->getPlayerEqiupPotion();
			_tempItem.isActive = false;
			m_player->setPlayerEqiupPotion(_tempItem);
			_potionButtonHeight = 38;
			_potionButtonCoolTimeCount= 0;
		}
	}
}

void UI::render()
{
	_playerFace->render(getMemDC(),50,50);
	_playerHp->render(getMemDC(),115,60,0,0,_playerHpWight,30);

	_statusButton->render(getMemDC(),50,WINSIZEY-125);
	_1Button->render(getMemDC(),WINSIZEX - 100,WINSIZEY-125);
	_potionButton->render(getMemDC(),WINSIZEX - 100,WINSIZEY-75);
	 
	if (m_player->getPlayerEqiupPotion().itemKind != item_Empty) m_player->getPlayerEqiupPotion().image->render(getMemDC(), WINSIZEX - 97, WINSIZEY - 72);
	if (m_player->getPlayerEqiupPotion().isActive && m_player->getPlayerEqiupPotion().itemKind == item_potion)
	{
		_potionButtonCoolTime->alphaRender(getMemDC(), _potionButtonCoolTimeRc.left, _potionButtonCoolTimeRc.top,
			0, 0, 38, _potionButtonHeight, 100);
		sprintf_s(_str, "%.1f", m_player->getPlayerEqiupPotion().itemCoolTime - _potionButtonCoolTimeCount);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		TextOut(getMemDC(), WINSIZEX - 85, WINSIZEY - 55, _str, strlen(_str));
	}

	if(m_player->getPlayerLButtonSkill().itemKind != item_Empty) m_player->getPlayerLButtonSkill().image->render(getMemDC(), 55, WINSIZEY - 63);
	if (m_player->getPlayerLButtonSkill().isActive)
	{
		_lButtonSkillCoolTime->alphaRender(getMemDC(), _lButtonSkillCoolTimeRc.left, _lButtonSkillCoolTimeRc.top,
			0, 0, 38, _lButtonSkillHeight, 100);
		sprintf_s(_str, "%.1f", m_player->getPlayerLButtonSkill().skillCoolTime - _lButtonSkillCoolTimeCount);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		TextOut(getMemDC(), 65, WINSIZEY - 55, _str, strlen(_str));
	}

	if (m_player->getPlayerDashSkill().itemKind != item_Empty) m_player->getPlayerDashSkill().image->render(getMemDC(), 115, WINSIZEY - 65);
	if (m_player->getPlayerDashSkill().isActive)
	{
		_dashSkillCoolTime->alphaRender(getMemDC(), _dashSkillCoolTimeRc.left, _dashSkillCoolTimeRc.top,
			0, 0, 38, _dashSkillHeight, 100);
		sprintf_s(_str, "%.1f", m_player->getPlayerDashSkill().skillCoolTime - _dashSkillCoolTimeCount);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		TextOut(getMemDC(), 125, WINSIZEY - 55, _str, strlen(_str));
	}

	if (m_player->getPlayerRButtonSkill().itemKind != item_Empty) m_player->getPlayerRButtonSkill().image->render(getMemDC(), 170, WINSIZEY - 63);
	if (m_player->getPlayerRButtonSkill().isActive)
	{
		_rButtonSkillCoolTime->alphaRender(getMemDC(), _rButtonSkillCoolTimeRc.left, _rButtonSkillCoolTimeRc.top,
			0, 0, 38, _rButtonSkillHeight, 100);
		sprintf_s(_str, "%.1f", m_player->getPlayerRButtonSkill().skillCoolTime - _rButtonSkillCoolTimeCount);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		TextOut(getMemDC(), 180, WINSIZEY - 55, _str, strlen(_str));
	}

	if (m_player->getPlayerQButtonSkill().itemKind != item_Empty) m_player->getPlayerQButtonSkill().image->render(getMemDC(), 225, WINSIZEY - 65);
	if (m_player->getPlayerQButtonSkill().isActive)
	{
		_qButtonSkillCoolTime->alphaRender(getMemDC(), _qButtonSkillCoolTimeRc.left, _qButtonSkillCoolTimeRc.top,
			0, 0, 38, _qButtonSkillHeight, 100);
		sprintf_s(_str, "%.1f", m_player->getPlayerQButtonSkill().skillCoolTime - _qButtonSkillCoolTimeCount);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		TextOut(getMemDC(), 235, WINSIZEY - 55, _str, strlen(_str));
	}

	if (m_player->getPlayerEButtonSkill().itemKind != item_Empty) m_player->getPlayerEButtonSkill().image->render(getMemDC(), 280, WINSIZEY - 65);
	if (m_player->getPlayerEButtonSkill().isActive)
	{
		_eButtonSkillCoolTime->alphaRender(getMemDC(),_eButtonSkillCoolTimeRc.left, _eButtonSkillCoolTimeRc.top,
			0,0,38, _eButtonSkillHeight,100);

		sprintf_s(_str, "%.1f", m_player->getPlayerEButtonSkill().skillCoolTime - _eButtonSkillCoolTimeCount);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		TextOut(getMemDC(), 290, WINSIZEY - 55,_str, strlen(_str));
	}

	if (m_player->getPlayerRRButtonSkill().itemKind != item_Empty) m_player->getPlayerRRButtonSkill().image->render(getMemDC(), 335, WINSIZEY - 65);
	if (m_player->getPlayerRRButtonSkill().isActive)
	{
		_rrButtonSkillCoolTime->alphaRender(getMemDC(), _rrButtonSkillCoolTimeRc.left, _rrButtonSkillCoolTimeRc.top,
			0, 0, 38, _rrButtonSkillHeight, 100);

		sprintf_s(_str, "%.1f", m_player->getPlayerRRButtonSkill().skillCoolTime - _rrButtonSkillCoolTimeCount);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		TextOut(getMemDC(), 345, WINSIZEY - 55, _str, strlen(_str));
	}
}
