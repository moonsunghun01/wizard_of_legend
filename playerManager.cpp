#include "stdafx.h"
#include "playerManager.h"

HRESULT playerManager::init(collisionRc* __collisionRc)
{
	// ������ ��ġ
	m_player->getPlayerImage()->setX(3540);
	m_player->getPlayerImage()->setY(5150);

	_playerShadow = IMAGEMANAGER->addImage("playerShadow", "images/playerShadow.bmp", 30 * 2, 29 * 2, true, RGB(255, 0, 255));

	// ��ų �ʱ�ȭ
	_playerSkill = new playerSkill;
	_playerSkill->init();

	// �ڷ���Ʈ ���� 
	_playerTeleport = new playerTeleport;
	_playerTeleport->init();

	// ������â
	_playerInventory = new playerInventory;
	_playerInventory->init();

	// ����â
	_playerStatus = new playerStatus;
	_playerStatus->init();

	_collisionRc = new collisionRc;
	_collisionRc = __collisionRc;

	// �׾��� ���
	_deathBackImage = IMAGEMANAGER->addImage("deathBackImage", "images/blackImage.bmp", WINSIZEX * 6, WINSIZEY * 8, true, RGB(255, 0, 255));
	_deathBackImageAlpha = 0;

	_gameOverImage = IMAGEMANAGER->addImage("GameOverText", "images/GameOverText2.bmp", 105 * 3, 18 * 3, true, RGB(255, 0, 255));
	_gameOverImage->setX(WINSIZEX / 2 - 150);
	_gameOverImage->setY(WINSIZEY / 2 - 200);
	_gameOverImageAlpha = 0;

	_victoryImage = IMAGEMANAGER->addImage("victory", "images/victory.bmp", 105 * 3, 18 * 3, true, RGB(255, 0, 255));
	_victoryImage->setX(WINSIZEX / 2 - 150);
	_victoryImage->setY(WINSIZEY / 2 - 200);
	_victoryImageAlpha = 0;

	_leftArcana = IMAGEMANAGER->addImage("leftArcana", "images/ArcanaLargeFront.bmp", 32 * 2, 50 * 2, true, RGB(255, 0, 255));
	_leftArcana->setX(WINSIZEX / 2 - 275);
	_leftArcana->setY(WINSIZEY / 2 + 100);
	_spaceArcana = IMAGEMANAGER->addImage("spaceArcana", "images/ArcanaLargeFront.bmp", 32 * 2, 50 * 2, true, RGB(255, 0, 255));
	_spaceArcana->setX(WINSIZEX / 2 - 175);
	_spaceArcana->setY(WINSIZEY / 2 + 100);
	_rightArcana = IMAGEMANAGER->addImage("rightArcana", "images/ArcanaLargeFront.bmp", 32 * 2, 50 * 2, true, RGB(255, 0, 255));
	_rightArcana->setX(WINSIZEX / 2 - 75);
	_rightArcana->setY(WINSIZEY / 2 + 100);
	_qArcana = IMAGEMANAGER->addImage("qArcana", "images/ArcanaLargeFront.bmp", 32 * 2, 50 * 2, true, RGB(255, 0, 255));
	_qArcana->setX(WINSIZEX / 2 + 25);
	_qArcana->setY(WINSIZEY / 2 + 100);
	_eArcana = IMAGEMANAGER->addImage("eArcana", "images/ArcanaLargeFront.bmp", 32 * 2, 50 * 2, true, RGB(255, 0, 255));
	_eArcana->setX(WINSIZEX / 2 + 125);
	_eArcana->setY(WINSIZEY / 2 + 100);
	_rArcana = IMAGEMANAGER->addImage("rArcana", "images/ArcanaLargeFront.bmp", 32 * 2, 50 * 2, true, RGB(255, 0, 255));
	_rArcana->setX(WINSIZEX / 2 + 225);
	_rArcana->setY(WINSIZEY / 2 + 100);

	_resetButton = IMAGEMANAGER->addImage("Space", "images/Space.bmp", 16 * 2, 16 * 2, true, RGB(255, 0, 255));
	_resetButton->setX(WINSIZEX / 2 - 5);
	_resetButton->setY(WINSIZEY / 2 + 250);

	_isPlayerVictoryAnimation = false;
	_isFinish = false;
	_isMove = false;
	_deathFrameX = 0;
	return S_OK;
}

void playerManager::release()
{
	SAFE_DELETE(_playerSkill);
	SAFE_DELETE(_playerTeleport);
	SAFE_DELETE(_playerInventory);
}

void playerManager::update()
{
	if (!_isFinish)
	{
		m_player->update();
		// �÷��̾� ��ų ����߿��� �ٸ� �ൿ �Ұ�
		if (!_playerSkill->getIsPlayerSkillActive()) keyManager();

		// �÷��̾� �⺻ �ִϸ��̼�
		animation();
		// ���� Dash �Ұ�
		if (_isDash) playerDash();
		// ��ų ������Ʈ
		_playerSkill->update();

		// ������ ������Ʈ
		_playerTeleport->update();
		// �׸��� ����
		_playerShadow->setX(m_player->getPlayerImage()->getX() + m_camera->getCameraX() + 35);
		_playerShadow->setY(m_player->getPlayerImage()->getY() + m_camera->getCameraY() + 100);

		// �κ��丮 ������Ʈ
		if (_isShowPlayerInventory) _playerInventory->update();

		// �浹ó�� 
		_collisionRc->update();
		_playerMoveRc = RectMake(m_player->getPlayerImage()->getX() + m_camera->getCameraX() + 40
			, m_player->getPlayerImage()->getY() + 110 + m_camera->getCameraY(), 50, 25);

		//if (_isMove) checkRectCollision();
		checkRectCollision();

		// ���� ����
		enemyHit();

		//���Ϳ��� ���� ���
		if (m_player->getIsHit()) playerHitCheck();
	}
	checkEndGame();
	if ((m_player->getIsPlayerDeath() || _isPlayerVictoryAnimation) && KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//SCENEMANAGER->changeScene("mainScene");
		_isReset = true;
	}
}

void playerManager::render()
{
	// ������ �̵� ������ �׸�
	//_isClearCheck = true;
	if (_isClearCheck) _playerTeleport->render();

	// ��ų �׸�
	_playerSkill->render();

	// ���� ��� 
	if (m_player->getIsPlayerDeath() || _isPlayerVictoryAnimation)
	{
		_deathBackImageAlpha += 10;
		if (_deathBackImageAlpha > 255) _deathBackImageAlpha = 255;
		_deathBackImage->alphaRender(getMemDC(), _deathBackImageAlpha);

		if (_deathBackImageAlpha >= 255)
		{
			if (m_player->getIsPlayerDeath())
			{
				_gameOverImageAlpha += 5;
				if (_gameOverImageAlpha > 255) _gameOverImageAlpha = 255;
				_gameOverImage->alphaRender(getMemDC(), _gameOverImageAlpha);
			}
			if (_isPlayerVictoryAnimation)
			{
				_victoryImageAlpha += 5;
				if (_victoryImageAlpha > 255) _victoryImageAlpha = 255;
				_victoryImage->alphaRender(getMemDC(), _victoryImageAlpha);
			}
			if (_gameOverImageAlpha >= 255 || _victoryImageAlpha >= 255)
			{
				_leftArcana->render(getMemDC(), _leftArcana->getX(), _leftArcana->getY());
				_spaceArcana->render(getMemDC(), _spaceArcana->getX(), _spaceArcana->getY());
				_rightArcana->render(getMemDC(), _rightArcana->getX(), _rightArcana->getY());
				_qArcana->render(getMemDC(), _qArcana->getX(), _qArcana->getY());
				_eArcana->render(getMemDC(), _eArcana->getX(), _eArcana->getY());
				_rArcana->render(getMemDC(), _rArcana->getX(), _rArcana->getY());

				if (m_player->getPlayerLButtonSkill().itemKind == item_Skill) m_player->getPlayerLButtonSkill().image->render(getMemDC(), _leftArcana->getX() + 10, _leftArcana->getY() + 30);
				if (m_player->getPlayerDashSkill().itemKind == item_dashSkill) m_player->getPlayerDashSkill().image->render(getMemDC(), _spaceArcana->getX() + 10, _spaceArcana->getY() + 30);
				if (m_player->getPlayerRButtonSkill().itemKind == item_Skill) m_player->getPlayerRButtonSkill().image->render(getMemDC(), _rightArcana->getX() + 10, _rightArcana->getY() + 30);
				if (m_player->getPlayerQButtonSkill().itemKind == item_Skill)m_player->getPlayerQButtonSkill().image->render(getMemDC(), _qArcana->getX() + 12, _qArcana->getY() + 30);
				if (m_player->getPlayerEButtonSkill().itemKind == item_Skill) m_player->getPlayerEButtonSkill().image->render(getMemDC(), _eArcana->getX() + 10, _eArcana->getY() + 30);
				if (m_player->getPlayerRRButtonSkill().itemKind == item_Skill) m_player->getPlayerRRButtonSkill().image->render(getMemDC(), _rArcana->getX() + 10, _rArcana->getY() + 30);
				_resetButton->render(getMemDC(), _resetButton->getX(), _resetButton->getY());
				char _str[128];
				wsprintf(_str, "��������");
				SetBkMode(getMemDC(), TRANSPARENT);
				SetTextColor(getMemDC(), RGB(255, 255, 255));
				TextOut(getMemDC(), _resetButton->getX() - 15, _resetButton->getY() + 45, _str, strlen(_str));
			}
		}
	}
	// �ɸ��� �׸�
	if (!_playerTeleport->getIsTeleport())
	{
		_playerShadow->alphaRender(getMemDC(), _playerShadow->getX(), _playerShadow->getY(), 100);
		m_player->getPlayerImage()->frameRender(getMemDC(), m_player->getPlayerImage()->getX() + m_camera->getCameraX(), m_player->getPlayerImage()->getY() + m_camera->getCameraY());
	}
	// �κ��丮 �׸�
	if (_isShowPlayerInventory) _playerInventory->render();
	if (_isShowPlayerStatus) _playerStatus->render();
	if (_isDragItem) dragItem();


	// ����׸��. �ɸ��� ���� ǥ��
	if (_isDebug)
	{
		Rectangle(getMemDC(), m_player->getPlayerRc().left, m_player->getPlayerRc().top, m_player->getPlayerRc().right, m_player->getPlayerRc().bottom);
		Rectangle(getMemDC(), m_player->getMonstetRc().left, m_player->getMonstetRc().top, m_player->getMonstetRc().right, m_player->getMonstetRc().bottom);
		_collisionRc->render();
		Rectangle(getMemDC(), _playerMoveRc.left, _playerMoveRc.top, _playerMoveRc.right, _playerMoveRc.bottom);
		for (int i = 0; i < _playerSkill->getPlayerSkill().size(); i++)
		{
			Rectangle(getMemDC(), _playerSkill->getPlayerSkill().at(i).skillRc.left + m_camera->getCameraX(),
				_playerSkill->getPlayerSkill().at(i).skillRc.top + m_camera->getCameraY()
				, _playerSkill->getPlayerSkill().at(i).skillRc.right + m_camera->getCameraX()
				, _playerSkill->getPlayerSkill().at(i).skillRc.bottom + m_camera->getCameraY());
		}
	}
}

void playerManager::keyManager()
{
	// �����̵�
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown('A'))
	{
		if (!_isDashPause)
		{
			m_player->getPlayerImage()->setX(m_player->getPlayerImage()->getX() - m_player->getCurrentMoveSpeed());
			m_camera->setCameraX(-(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 - WINSIZEX / 2));
		}
		// �밢�� ������
		if (_isUp) _isLeftUp = true;
		else _isLeftUp = false;
		if (_isDown) _isLeftDown = true;
		else _isLeftDown = false;

		// �Ϲ� ������
		_isLeft = true;
		_isRight = false;
		_isUp = false;
		_isDown = false;
		_isMove = true;
		_isIdle = false;
	}
	// ���� ��ư �� ���� �ٶ󺸰� idle����
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp('A'))
	{
		_isIdle = true;
		_isMove = false;
		_isLeftUp = false;
		_isLeftDown = false;
	}

	// ������ �̵�
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) || KEYMANAGER->isStayKeyDown('D'))
	{
		if (!_isDashPause)
		{
			m_player->getPlayerImage()->setX(m_player->getPlayerImage()->getX() + m_player->getCurrentMoveSpeed());
			m_camera->setCameraX(-(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 - WINSIZEX / 2));
		}
		// �밢�� ����
		if (_isUp) _isRightUp = true;
		else _isRightUp = false;
		if (_isDown) _isRightDown = true;
		else _isRightDown = false;

		// �Ϲ� �̵�
		_isLeft = false;
		_isRight = true;
		_isUp = false;
		_isDown = false;
		_isMove = true;
		_isIdle = false;
	}
	// �����U idle ����
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp('D'))
	{
		_isIdle = true;
		_isMove = false;
		_isRightDown = false;
		_isRightUp = false;
	}

	// ���� �̵�
	if (KEYMANAGER->isStayKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown('W'))
	{
		if (!_isDashPause)
		{
			m_player->getPlayerImage()->setY(m_player->getPlayerImage()->getY() - m_player->getCurrentMoveSpeed());
			m_camera->setCameraY(-(m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 - WINSIZEY / 2));
		}
		_isLeft = false;
		_isRight = false;
		_isUp = true;
		_isDown = false;
		_isMove = true;
		_isIdle = false;
	}
	// ������ IDle
	if (KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp('W'))
	{
		_isIdle = true;
		_isMove = false;
	}
	// �Ʒ��� �̵�
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) || KEYMANAGER->isStayKeyDown('S'))
	{
		if (!_isDashPause)
		{
			m_player->getPlayerImage()->setY(m_player->getPlayerImage()->getY() + m_player->getCurrentMoveSpeed());
			m_camera->setCameraY(-(m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 - WINSIZEY / 2));
		}
		_isLeft = false;
		_isRight = false;
		_isUp = false;
		_isDown = true;
		_isMove = true;
		_isIdle = false;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN) || KEYMANAGER->isOnceKeyUp('S'))
	{
		_isIdle = true;
		_isMove = false;
	}

	// �뽬 ���� �뽬 �Ұ� 
	if (m_player->getPlayerDashSkill().itemKind != item_Empty && !m_player->getPlayerDashSkill().isActive &&KEYMANAGER->isOnceKeyDown(VK_SPACE) && !_isDash && !_isDashPause)
	{
		_dashCount = 0;
		_isIdle = false;
		_isMove = false;
		_isDash = true;
		// ��ų ��Ƽ�� 
		SKILLBOOK _tempSkill = m_player->getPlayerDashSkill();
		_tempSkill.isActive = true;
		if (_tempSkill.skillCoolTime == 0) _tempSkill.isActive = false;
		m_player->setPlayerDashSkill(_tempSkill);
	}


	// ���� ��ų 
	if (!m_player->getPlayerLButtonSkill().isActive &&
		m_player->getPlayerLButtonSkill().itemKind != item_Empty && 
		!_isShowPlayerInventory && !_isShowPlayerStatus && 
		KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && 
		!_isDash && !_isDashPause && !_playerSkill->getIsSkillActive() 
		&& !_playerSkill->getIsPlayerSkillActive())
	{
		if (m_player->getPlayerLButtonSkill().skillNumber == 3)
		{
			_playerSkill->setSkillAngle(getAngle(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 + m_camera->getCameraX(),
				m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 + m_camera->getCameraY()
				, m_ptMouse.x, m_ptMouse.y));
		}
		_isIdle = false;
		_playerSkill->setIsSkillActive(true);
		_playerSkill->setIsPlayerSkillActive(true);
		_playerSkill->skillSetting(m_player->getPlayerLButtonSkill().skillNumber, m_player->getPlayerLButtonSkill().skillMotionNum);            // 1����ų , 1�����
		// ��ų ��Ƽ�� 
		SKILLBOOK _tempSkill = m_player->getPlayerLButtonSkill();
		_tempSkill.isActive = true;
		if (_tempSkill.skillCoolTime == 0) _tempSkill.isActive = false;
		m_player->setPlayerLButtonSkill(_tempSkill);
		m_player->setSkillDamage(m_player->getPlayerLButtonSkill().skillDamege); 
	}

	// ������ ��ų
	if (!m_player->getPlayerRButtonSkill().isActive && m_player->getPlayerRButtonSkill().itemKind != item_Empty && KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && !_isDash && !_isDashPause && !_playerSkill->getIsSkillActive() && !_playerSkill->getIsPlayerSkillActive())
	{
		if (m_player->getPlayerRButtonSkill().skillNumber == 3)
		{
			_playerSkill->setSkillAngle(getAngle(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 + m_camera->getCameraX(),
				m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 + m_camera->getCameraY()
				, m_ptMouse.x, m_ptMouse.y));
		}
		_isIdle = false;
		_playerSkill->setIsSkillActive(true);
		_playerSkill->setIsPlayerSkillActive(true);
		_playerSkill->skillSetting(m_player->getPlayerRButtonSkill().skillNumber, m_player->getPlayerRButtonSkill().skillMotionNum);
		// ��ų ��Ƽ�� 
		SKILLBOOK _tempSkill = m_player->getPlayerRButtonSkill();
		_tempSkill.isActive = true;
		if (_tempSkill.skillCoolTime == 0) _tempSkill.isActive = false;
		m_player->setPlayerRButtonSkill(_tempSkill);

		m_player->setSkillDamage(m_player->getPlayerRButtonSkill().skillDamege);

		//�Ҹ�
		if (m_player->getPlayerRButtonSkill().skillNumber == 4)SOUNDMANAGER->play("õ��", 1);
		int _rndNum = RND->getInt(2);
		if (m_player->getPlayerRButtonSkill().skillNumber == 6)
		{
			if (_rndNum == 0)   SOUNDMANAGER->play("����", 1);
			if (_rndNum == 1)   SOUNDMANAGER->play("����", 1);
		}
	}
	// q ��ų
	if (!m_player->getPlayerQButtonSkill().isActive && m_player->getPlayerQButtonSkill().itemKind != item_Empty && KEYMANAGER->isOnceKeyDown('Q') && !_isDash && !_isDashPause && !_playerSkill->getIsSkillActive() && !_playerSkill->getIsPlayerSkillActive())
	{
		if (m_player->getPlayerQButtonSkill().skillNumber == 3)
		{
			_playerSkill->setSkillAngle(getAngle(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 + m_camera->getCameraX(),
				m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 + m_camera->getCameraY()
				, m_ptMouse.x, m_ptMouse.y));
		}
		_isIdle = false;
		_playerSkill->setIsSkillActive(true);
		_playerSkill->setIsPlayerSkillActive(true);

		_playerSkill->skillSetting(m_player->getPlayerQButtonSkill().skillNumber, m_player->getPlayerQButtonSkill().skillMotionNum);
		// ��ų ��Ƽ�� 
		SKILLBOOK _tempSkill = m_player->getPlayerQButtonSkill();
		_tempSkill.isActive = true;
		if (_tempSkill.skillCoolTime == 0) _tempSkill.isActive = false;
		m_player->setPlayerQButtonSkill(_tempSkill);

		m_player->setSkillDamage(m_player->getPlayerQButtonSkill().skillDamege);

		//�Ҹ�
		if (m_player->getPlayerQButtonSkill().skillNumber == 4)SOUNDMANAGER->play("õ��", 1);
		int _rndNum = RND->getInt(2);
		if (m_player->getPlayerQButtonSkill().skillNumber == 6)
		{
			if (_rndNum == 0)   SOUNDMANAGER->play("����", 1);
			if (_rndNum == 1)   SOUNDMANAGER->play("����", 1);
		}
	}
	// e ��ų
	if (!m_player->getPlayerEButtonSkill().isActive && m_player->getPlayerEButtonSkill().itemKind != item_Empty && KEYMANAGER->isOnceKeyDown('E') && !_isDash && !_isDashPause && !_playerSkill->getIsSkillActive() && !_playerSkill->getIsPlayerSkillActive())
	{

		if (m_player->getPlayerEButtonSkill().skillNumber == 3)
		{
			_playerSkill->setSkillAngle(getAngle(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 + m_camera->getCameraX(),
				m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 + m_camera->getCameraY()
				, m_ptMouse.x, m_ptMouse.y));
		}
		_isIdle = false;
		_playerSkill->setIsSkillActive(true);
		_playerSkill->setIsPlayerSkillActive(true);
		_playerSkill->skillSetting(m_player->getPlayerEButtonSkill().skillNumber, m_player->getPlayerEButtonSkill().skillMotionNum);

		// ��ų ��Ƽ�� 
		SKILLBOOK _tempSkill = m_player->getPlayerEButtonSkill();
		_tempSkill.isActive = true;
		if (_tempSkill.skillCoolTime == 0) _tempSkill.isActive = false;
		m_player->setPlayerEButtonSkill(_tempSkill);

		m_player->setSkillDamage(m_player->getPlayerEButtonSkill().skillDamege);

		//�Ҹ�
		if (m_player->getPlayerEButtonSkill().skillNumber == 4)SOUNDMANAGER->play("õ��", 1);
		int _rndNum = RND->getInt(2);
		if (m_player->getPlayerEButtonSkill().skillNumber == 6)
		{
			if (_rndNum == 0)   SOUNDMANAGER->play("����", 1);
			if (_rndNum == 1)   SOUNDMANAGER->play("����", 1);
		}

	}
	// r ��ų
	if (!m_player->getPlayerRRButtonSkill().isActive && m_player->getPlayerRRButtonSkill().itemKind != item_Empty && KEYMANAGER->isOnceKeyDown('R') && !_isDash && !_isDashPause && !_playerSkill->getIsSkillActive() && !_playerSkill->getIsPlayerSkillActive())
	{
		if (m_player->getPlayerRButtonSkill().skillNumber == 3)
		{
			_playerSkill->setSkillAngle(getAngle(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 + m_camera->getCameraX(),
				m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 + m_camera->getCameraY()
				, m_ptMouse.x, m_ptMouse.y));
		}
		_isIdle = false;
		_playerSkill->setIsSkillActive(true);
		_playerSkill->setIsPlayerSkillActive(true);
		_playerSkill->skillSetting(m_player->getPlayerRRButtonSkill().skillNumber, m_player->getPlayerRRButtonSkill().skillMotionNum);

		SKILLBOOK _tempSkill = m_player->getPlayerRRButtonSkill();
		_tempSkill.isActive = true;
		if (_tempSkill.skillCoolTime == 0) _tempSkill.isActive = false;
		m_player->setPlayerRRButtonSkill(_tempSkill);

		m_player->setSkillDamage(m_player->getPlayerRRButtonSkill().skillDamege);
		// �Ҹ�
		if (m_player->getPlayerRRButtonSkill().skillNumber == 4)SOUNDMANAGER->play("õ��", 1);
		int _rndNum = RND->getInt(2);
		if (m_player->getPlayerRRButtonSkill().skillNumber == 6)
		{
			if (_rndNum == 0)   SOUNDMANAGER->play("����", 1);
			if (_rndNum == 1)   SOUNDMANAGER->play("����", 1);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('1') && m_player->getPlayerEqiupPotion().itemKind == item_potion && !m_player->getPlayerEqiupPotion().isActive)
	{
		m_player->setCurrentHp(m_player->getCurrentHp() + m_player->getPlayerEqiupPotion().hp);
		TAGITEMINFO _tempItem = m_player->getPlayerEqiupPotion();
		_tempItem.isActive = true;
		if (_tempItem.itemCoolTime == 0) _tempItem.isActive = false;
		m_player->setPlayerEqiupPotion(_tempItem);
	}
	// �������� ���� ��� �ڷ���Ʈ ������
	if (KEYMANAGER->isOnceKeyDown('G') && _isClearCheck)
	{
		RECT rc;
		if (IntersectRect(&rc, &m_player->getPlayerRc(), &_playerTeleport->getTeleportPadRc()))
		{
			_playerTeleport->setIsTeleport(true);
		}
	}

	// �κ��丮
	//if (KEYMANAGER->isOnceKeyDown('I'))
	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		if (!_isShowPlayerInventory) _isShowPlayerInventory = true;
		else if (_isShowPlayerInventory) _isShowPlayerInventory = false;
	}


	// ������ �巡��
	if ((_isShowPlayerInventory || _isShowPlayerStatus) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{

		// �κ��丮 ������ 
		for (int i = 0; i < m_player->getVPlayerItem().size(); i++)
		{
			if (PtInRect(&m_player->getVPlayerItem().at(i).itemRc, m_ptMouse))
			{
				_isInventoryItem = true;
				_isInventorySkill = false;
				_isDragItem = true;
				_dragItemNum = i;
			}
		}
		// �κ��丮 ��ų ����
		for (int i = 0; i < m_player->getVPlayerSkill().size(); i++)
		{
			if (PtInRect(&m_player->getVPlayerSkill().at(i).skillRc, m_ptMouse))
			{
				_isInventoryItem = false;
				_isInventorySkill = true;
				_isDragItem = true;
				_dragSkillNum = i;
			}
		}

		// ���� ����
		if (PtInRect(&_playerStatus->getWeaponRc(), m_ptMouse) && !_isArmorOff && !_isPotionOff && !_isSkillChange && m_player->getPlayerEqiupWeapon().itemKind != item_Empty)
		{
			_isWeaponOff = true;
			_isInventoryItem = false;
			_isDragItem = true;
		}
		// ��
		else if (PtInRect(&_playerStatus->getArmorRc(), m_ptMouse) && !_isWeaponOff && !_isPotionOff && !_isSkillChange && m_player->getPlayerEqiupArmor().itemKind != item_Empty)
		{
			_isArmorOff = true;
			_isInventoryItem = false;
			_isDragItem = true;
		}
		// ����
		else if (PtInRect(&_playerStatus->getPotionRc(), m_ptMouse) && !_isWeaponOff && !_isArmorOff && !_isSkillChange && m_player->getPlayerEqiupPotion().itemKind != item_Empty)
		{
			_isPotionOff = true;
			_isInventoryItem = false;
			_isDragItem = true;
		}
		// ��ų ���� ��ư
		else if (PtInRect(&_playerStatus->getLButtonSkillRc(), m_ptMouse) && !_isWeaponOff && !_isArmorOff && !_isWeaponOff && m_player->getPlayerLButtonSkill().itemKind != item_Empty)
		{
			_isLButtonSkillOff = true;
			_isSkillChange = true;
			_isInventoryItem = false;
			_isDragItem = true;
		}
		// ��ų �뽬 ��ư
		else if (PtInRect(&_playerStatus->getDashSkillRc(), m_ptMouse) && !_isWeaponOff && !_isArmorOff && !_isWeaponOff&& m_player->getPlayerDashSkill().itemKind != item_Empty)
		{
			_isDashSkillOff = true;
			_isSkillChange = true;
			_isInventoryItem = false;
			_isDragItem = true;
		}
		// ��ų ������ ��ư
		else if (PtInRect(&_playerStatus->getRButtonSkillRc(), m_ptMouse) && !_isWeaponOff && !_isArmorOff && !_isWeaponOff && m_player->getPlayerRButtonSkill().itemKind != item_Empty)
		{
			_isRButtonSkillOff = true;
			_isSkillChange = true;
			_isInventoryItem = false;
			_isDragItem = true;
		}
		// ��ų Q ��ư
		else if (PtInRect(&_playerStatus->getQButtonSkillRc(), m_ptMouse) && !_isWeaponOff && !_isArmorOff && !_isWeaponOff && m_player->getPlayerQButtonSkill().itemKind != item_Empty)
		{
			_isQButtonSkillOff = true;
			_isSkillChange = true;
			_isInventoryItem = false;
			_isDragItem = true;
		}
		// ��ų E ��ư
		else if (PtInRect(&_playerStatus->getEButtonSkillRc(), m_ptMouse) && !_isWeaponOff && !_isArmorOff && !_isWeaponOff && m_player->getPlayerEButtonSkill().itemKind != item_Empty)
		{
			_isEButtonSkillOff = true;
			_isSkillChange = true;
			_isInventoryItem = false;
			_isDragItem = true;
		}
		// ��ų RR ��ư
		else if (PtInRect(&_playerStatus->getRRButtonSkillRc(), m_ptMouse) && !_isWeaponOff && !_isArmorOff && !_isWeaponOff && m_player->getPlayerRRButtonSkill().itemKind != item_Empty)
		{
			_isRRButtonSkillOff = true;
			_isSkillChange = true;
			_isInventoryItem = false;
			_isDragItem = true;
		}
	}

	// ��ư �� 
	if ((_isShowPlayerInventory) && KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_isDragItem = false;
		checkEquipItem();
	}
	if ((_isShowPlayerStatus) && KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_isDragItem = false;
		checkEquipItem();
	}
	// ���� â
	//if (KEYMANAGER->isOnceKeyDown('C'))
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		if (!_isShowPlayerStatus) _isShowPlayerStatus = true;
		else if (_isShowPlayerStatus) _isShowPlayerStatus = false;
	}
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		m_player->setCurrentHp(m_player->getCurrentHp() - 100);
	}
	// ����� ���
	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		if (_isDebug) _isDebug = false;
		else if (!_isDebug) _isDebug = true;
	}
}

void playerManager::playerDash()
{
	checkDashCollision();
	// �밢�� ���� �� 
	if (_isLeftUp)
	{
		_dashCount++;
		if (_dashCount > 5)
		{
			_index = 0;
			_isDash = false;
			_isDashPause = true;
			_isLeftUp = false;
		}
		else
		{
			m_player->getPlayerImage()->setX(m_player->getPlayerImage()->getX() - m_player->getCurrentMoveSpeed() * 10);
			m_camera->setCameraX(-(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 - WINSIZEX / 2));

			m_player->getPlayerImage()->setY(m_player->getPlayerImage()->getY() - m_player->getCurrentMoveSpeed() * 10);
			m_camera->setCameraY(-(m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 - WINSIZEY / 2));
		}
	}
	// �밢�� ���� �Ʒ�
	else if (_isLeftDown)
	{
		_dashCount++;
		if (_dashCount > 5)
		{
			_index = 0;
			_isDash = false;
			_isDashPause = true;
			_isLeftDown = false;
		}
		else
		{
			m_player->getPlayerImage()->setX(m_player->getPlayerImage()->getX() - m_player->getCurrentMoveSpeed() * 10);
			m_camera->setCameraX(-(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 - WINSIZEX / 2));
			m_player->getPlayerImage()->setY(m_player->getPlayerImage()->getY() + m_player->getCurrentMoveSpeed() * 10);
			m_camera->setCameraY(-(m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 - WINSIZEY / 2));
		}
	}
	// ����  
	else if (_isLeft)
	{
		_dashCount++;
		if (_dashCount > 5)
		{
			_index = 0;
			_isDash = false;
			_isDashPause = true;
		}
		else
		{
			m_player->getPlayerImage()->setX(m_player->getPlayerImage()->getX() - m_player->getCurrentMoveSpeed() * 10);
			m_camera->setCameraX(-(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 - WINSIZEX / 2));
		}
	}
	// �밢�� ������ �� 
	if (_isRightUp)
	{
		_dashCount++;
		if (_dashCount > 5)
		{
			_index = 0;
			_isDash = false;
			_isDashPause = true;
			_isRightUp = false;
		}
		else
		{
			m_player->getPlayerImage()->setX(m_player->getPlayerImage()->getX() + m_player->getCurrentMoveSpeed() * 10);
			m_camera->setCameraX(-(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 - WINSIZEX / 2));
			m_player->getPlayerImage()->setY(m_player->getPlayerImage()->getY() - m_player->getCurrentMoveSpeed() * 10);
			m_camera->setCameraY(-(m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 - WINSIZEY / 2));
		}
	}
	// �밢�� ������ �Ʒ�
	else if (_isRightDown)
	{
		_dashCount++;
		if (_dashCount > 5)
		{
			_index = 0;
			_isDash = false;
			_isDashPause = true;
			_isRightDown = false;
		}
		else
		{
			m_player->getPlayerImage()->setX(m_player->getPlayerImage()->getX() + m_player->getCurrentMoveSpeed() * 10);
			m_camera->setCameraX(-(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 - WINSIZEX / 2));
			m_player->getPlayerImage()->setY(m_player->getPlayerImage()->getY() + m_player->getCurrentMoveSpeed() * 10);
			m_camera->setCameraY(-(m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 - WINSIZEY / 2));
		}
	}
	else if (_isRight)
	{
		_dashCount++;
		if (_dashCount > 5)
		{
			_index = 0;
			_isDash = false;
			_isDashPause = true;
		}
		else
		{
			m_player->getPlayerImage()->setX(m_player->getPlayerImage()->getX() + m_player->getCurrentMoveSpeed() * 10);
			m_camera->setCameraX(-(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 - WINSIZEX / 2));
		}
	}

	if (_isUp)
	{
		_dashCount++;

		if (_dashCount > 5)
		{
			_index = 0;
			_isDash = false;
			_isDashPause = true;
		}
		else
		{
			m_player->getPlayerImage()->setY(m_player->getPlayerImage()->getY() - m_player->getCurrentMoveSpeed() * 10);
			m_camera->setCameraY(-(m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 - WINSIZEY / 2));
		}
	}

	if (_isDown)
	{
		_dashCount++;
		if (_dashCount > 5)
		{
			_index = 0;
			_isDash = false;
			_isDashPause = true;
		}
		else
		{
			m_player->getPlayerImage()->setY(m_player->getPlayerImage()->getY() + m_player->getCurrentMoveSpeed() * 10);
			m_camera->setCameraY(-(m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 - WINSIZEY / 2));
		}
	}
}

void playerManager::checkRectCollision()
{
	for (int i = 0; i < 57; i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_collisionRc->getCollisionRc(i), &_playerMoveRc))
		{
			if (_isLeft || _isLeftUp || _isLeftDown)
			{
				m_player->getPlayerImage()->setX(m_player->getPlayerImage()->getX() + m_player->getCurrentMoveSpeed());
				m_camera->setCameraX(-(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 - WINSIZEX / 2));
			}

			if (_isRight || _isRightUp || _isRightDown)
			{
				m_player->getPlayerImage()->setX(m_player->getPlayerImage()->getX() - m_player->getCurrentMoveSpeed());
				m_camera->setCameraX(-(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 - WINSIZEX / 2));
			}
			if (_isUp)
			{
				m_player->getPlayerImage()->setY(m_player->getPlayerImage()->getY() + m_player->getCurrentMoveSpeed());
				m_camera->setCameraY(-(m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 - WINSIZEY / 2));
			}
			if (_isDown)
			{
				m_player->getPlayerImage()->setY(m_player->getPlayerImage()->getY() - m_player->getCurrentMoveSpeed());
				m_camera->setCameraY(-(m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 - WINSIZEY / 2));
			}
			if (m_player->getIsHit())
			{
				m_player->getPlayerImage()->setX(m_player->getPlayerImage()->getX() - cos(_hitAngle) * 10);
				m_player->getPlayerImage()->setY(m_player->getPlayerImage()->getY() - -sin(_hitAngle) * 10);
				m_camera->setCameraX(-(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 - WINSIZEX / 2));
				m_camera->setCameraY(-(m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 - WINSIZEY / 2));
			}
			if (_isIdle)
			{
				m_player->getPlayerImage()->setY(m_player->getPlayerImage()->getY() - m_player->getCurrentMoveSpeed());
				m_camera->setCameraY(-(m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 - WINSIZEY / 2));
			}
		}
	}
}

void playerManager::checkDashCollision()
{
	for (int i = 0; i < 57; i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_collisionRc->getCollisionRc(i), &_playerMoveRc) && _collisionRc->getCollisionRcKind(i) == RC_WALL)
		{
			_dashCount = 6;
			if (_isLeft)
			{
				m_player->getPlayerImage()->setX(_collisionRc->getCollisionRc(i).right - m_camera->getCameraX() - 35);
			}
			if (_isRight)
			{
				m_player->getPlayerImage()->setX(_collisionRc->getCollisionRc(i).left - m_camera->getCameraX() - 90);
			}
			if (_isUp)
			{
				m_player->getPlayerImage()->setY(_collisionRc->getCollisionRc(i).bottom - m_camera->getCameraY() - 100);
			}
			if (_isDown)
			{
				m_player->getPlayerImage()->setY(_collisionRc->getCollisionRc(i).top - m_camera->getCameraY() - 135);
			}
		}
	}
}

void playerManager::setEnemyManagerLink(enemyManager* _enemyManagerLink)
{
	_enemyManager = _enemyManagerLink;
}

void playerManager::enemyHit()
{
	RECT rc;
	for (int i = 0; i < _enemyManager->getVMinion().size(); i++)
	{
		for (int j = 0; j < _playerSkill->getPlayerSkill().size(); j++)
		{
			if (IntersectRect(&rc, &_enemyManager->getVMinion().at(i)->getEnemyRc(), &_playerSkill->getPlayerSkill().at(j).skillRc))
			{
				_enemyManager->getVMinion().at(i)->setIsHit(true);
				// ����� ����
				if (_playerSkill->getSkillNum() == 6 && !_playerSkill->getIsStartShark())
				{
					_playerSkill->sharkSetting();
				}
			}
		}
	}

	for (int i = 0; i < _playerSkill->getPlayerSkill().size(); i++)
	{
		if (IntersectRect(&rc, &_enemyManager->getBoss()->getBossCollisionRc(), &_playerSkill->getPlayerSkill().at(i).skillRc))
		{
			_enemyManager->getBoss()->setIsBeHit(true);
		}
	}
}

void playerManager::playerHitCheck()
{
	_hitAngle = getAngle(m_player->getMonstetRc().left + (m_player->getMonstetRc().right - m_player->getMonstetRc().left) / 2
		, m_player->getMonstetRc().top + (m_player->getMonstetRc().bottom - m_player->getMonstetRc().top) / 2
		, m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2
		, m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2);

	if (m_player->getPlayerRc().left < m_player->getMonstetRc().left) _hitAngle = 3.14 - _hitAngle;

	m_player->getPlayerImage()->setX(m_player->getPlayerImage()->getX() + cos(_hitAngle) * 3);
	m_player->getPlayerImage()->setY(m_player->getPlayerImage()->getY() + -sin(_hitAngle) * 3);
	m_camera->setCameraX(-(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 - WINSIZEX / 2));
	m_camera->setCameraY(-(m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 - WINSIZEY / 2));

	_hitTimeCount++;
	if (_hitTimeCount > 10)
	{
		m_player->setIsHit(false);
		_hitTimeCount = 0;
	}
}

// ���� ���� üũ
void playerManager::checkEndGame()
{
	if (m_player->getCurrentHp() < 0)
	{
		_isPlayerDeathAnimation = true;
		_isFinish = true;
	}
	if (_enemyManager->getBoss()->getBossCurrentHp() < 0)
	{
		_isPlayerVictoryAnimation = true;
		_isFinish = true;
	}

	if (_isPlayerDeathAnimation)
	{
		_count++;
		m_player->getPlayerImage()->setFrameY(9);
		if (_count % 10 == 0)
		{
			_count = 0;
			if (_deathFrameX >= m_player->getPlayerImage()->getMaxFrameX())
			{
				_deathFrameX = 9;
				m_player->setIsPlayerDeath(true);
			}
			m_player->getPlayerImage()->setFrameX(_deathFrameX);
			_deathFrameX++;
		}
	}
	if (_isPlayerVictoryAnimation)
	{
		m_player->getPlayerImage()->setFrameY(0);
		m_player->getPlayerImage()->setFrameX(0);
	}
}


// ������ �巡�� �̹���
void playerManager::dragItem()
{
	if (_isInventoryItem)
	{
		m_player->getVPlayerItem().at(_dragItemNum).image->alphaRender(getMemDC(),
			m_ptMouse.x - m_player->getVPlayerItem().at(_dragItemNum).image->getWidth() / 2,
			m_ptMouse.y - m_player->getVPlayerItem().at(_dragItemNum).image->getHeight() / 2, 125);
	}
	else if (!_isInventoryItem)
	{
		if (_isWeaponOff) m_player->getPlayerEqiupWeapon().image->alphaRender(getMemDC(), m_ptMouse.x - m_player->getPlayerEqiupWeapon().image->getWidth() / 2, m_ptMouse.y - m_player->getPlayerEqiupWeapon().image->getHeight() / 2, 125);
		if (_isArmorOff) m_player->getPlayerEqiupArmor().image->alphaRender(getMemDC(), m_ptMouse.x - m_player->getPlayerEqiupArmor().image->getWidth() / 2, m_ptMouse.y - m_player->getPlayerEqiupArmor().image->getHeight() / 2, 125);
		if (_isPotionOff) m_player->getPlayerEqiupPotion().image->alphaRender(getMemDC(), m_ptMouse.x - m_player->getPlayerEqiupPotion().image->getWidth() / 2, m_ptMouse.y - m_player->getPlayerEqiupPotion().image->getHeight() / 2, 125);
	}

	if (_isInventorySkill)
	{
		m_player->getVPlayerSkill().at(_dragSkillNum).image->alphaRender(getMemDC(),
			m_ptMouse.x - m_player->getVPlayerSkill().at(_dragSkillNum).image->getWidth() / 2,
			m_ptMouse.y - m_player->getVPlayerSkill().at(_dragSkillNum).image->getHeight() / 2, 125);
	}
	if (_isSkillChange)
	{
		if (_isLButtonSkillOff)m_player->getPlayerLButtonSkill().image->alphaRender(getMemDC(), m_ptMouse.x - m_player->getPlayerLButtonSkill().image->getWidth() / 2, m_ptMouse.y - m_player->getPlayerLButtonSkill().image->getHeight() / 2, 125);
		if (_isDashSkillOff)m_player->getPlayerDashSkill().image->alphaRender(getMemDC(), m_ptMouse.x - m_player->getPlayerDashSkill().image->getWidth() / 2, m_ptMouse.y - m_player->getPlayerDashSkill().image->getHeight() / 2, 125);
		if (_isRButtonSkillOff)m_player->getPlayerRButtonSkill().image->alphaRender(getMemDC(), m_ptMouse.x - m_player->getPlayerRButtonSkill().image->getWidth() / 2, m_ptMouse.y - m_player->getPlayerRButtonSkill().image->getHeight() / 2, 125);
		if (_isQButtonSkillOff)m_player->getPlayerQButtonSkill().image->alphaRender(getMemDC(), m_ptMouse.x - m_player->getPlayerQButtonSkill().image->getWidth() / 2, m_ptMouse.y - m_player->getPlayerQButtonSkill().image->getHeight() / 2, 125);
		if (_isEButtonSkillOff)m_player->getPlayerEButtonSkill().image->alphaRender(getMemDC(), m_ptMouse.x - m_player->getPlayerEButtonSkill().image->getWidth() / 2, m_ptMouse.y - m_player->getPlayerEButtonSkill().image->getHeight() / 2, 125);
		if (_isRRButtonSkillOff)m_player->getPlayerRRButtonSkill().image->alphaRender(getMemDC(), m_ptMouse.x - m_player->getPlayerRRButtonSkill().image->getWidth() / 2, m_ptMouse.y - m_player->getPlayerRRButtonSkill().image->getHeight() / 2, 125);
	}

	_playerInventory->setIsShowItemInfo(false);
	_playerInventory->setIsShowSkillInfo(false);
}

// ������ ����
void playerManager::checkEquipItem()
{
	RECT tempRc;
	vector<TAGITEMINFO> _vTempItem = m_player->getVPlayerItem();
	// ����������
	if (_isInventoryItem)
	{
		// ��������
		if (PtInRect(&_playerStatus->getWeaponRc(), m_ptMouse) && m_player->getVPlayerItem().at(_dragItemNum).itemKind == item_Weapon)
		{
			if (m_player->getPlayerEqiupWeapon().itemKind != item_Empty)
			{
				_vTempItem.push_back(m_player->getPlayerEqiupWeapon());
			}
			m_player->setPlayerEqiupWeapon(_vTempItem.at(_dragItemNum));
			_vTempItem.erase(_vTempItem.begin() + _dragItemNum);
			m_player->setVPlayerItem(_vTempItem);
		}

		// �� ����
		if (PtInRect(&_playerStatus->getArmorRc(), m_ptMouse) && m_player->getVPlayerItem().at(_dragItemNum).itemKind == item_Armor)
		{
			if (m_player->getPlayerEqiupArmor().itemKind != item_Empty)
			{
				_vTempItem.push_back(m_player->getPlayerEqiupArmor());
			}
			m_player->setPlayerEqiupArmor(_vTempItem.at(_dragItemNum));

			_vTempItem.erase(_vTempItem.begin() + _dragItemNum);
			m_player->setVPlayerItem(_vTempItem);
		}

		// ���� ����
		if (PtInRect(&_playerStatus->getPotionRc(), m_ptMouse) && m_player->getVPlayerItem().at(_dragItemNum).itemKind == item_potion)
		{
			if (m_player->getPlayerEqiupPotion().itemKind != item_Empty)
			{
				_vTempItem.push_back(m_player->getPlayerEqiupPotion());
			}
			m_player->setPlayerEqiupPotion(_vTempItem.at(_dragItemNum));

			_vTempItem.erase(_vTempItem.begin() + _dragItemNum);
			m_player->setVPlayerItem(_vTempItem);
		}
	}
	// ������ ����
	else
	{
		vector<TAGITEMINFO> _vTempItem = m_player->getVPlayerItem();
		TAGITEMINFO _tempItem;
		// ����
		if (_isWeaponOff)
		{
			_vTempItem.push_back(m_player->getPlayerEqiupWeapon());
			m_player->setVPlayerItem(_vTempItem);
			_tempItem.itemKind = item_Empty;
			_tempItem.hp = _tempItem.att = _tempItem.def = _tempItem.speed = 0;
			m_player->setPlayerEqiupWeapon(_tempItem);
			_isWeaponOff = false;
		}
		//��
		if (_isArmorOff)
		{
			_vTempItem.push_back(m_player->getPlayerEqiupArmor());
			m_player->setVPlayerItem(_vTempItem);
			_tempItem.itemKind = item_Empty;
			_tempItem.hp = _tempItem.att = _tempItem.def = _tempItem.speed = 0;
			m_player->setPlayerEqiupArmor(_tempItem);
			_isArmorOff = false;
		}
		// ����
		if (_isPotionOff)
		{
			_vTempItem.push_back(m_player->getPlayerEqiupPotion());
			m_player->setVPlayerItem(_vTempItem);
			_tempItem.itemKind = item_Empty;
			_tempItem.hp = _tempItem.att = _tempItem.def = _tempItem.speed = 0;
			m_player->setPlayerEqiupPotion(_tempItem);
			_isPotionOff = false;
		}

	}
	 
	m_player->setCurrentAtk(m_player->getAtk() + m_player->getPlayerEqiupWeapon().att + m_player->getPlayerEqiupArmor().att);
	m_player->setCurrentDef(m_player->getDef() + m_player->getPlayerEqiupWeapon().def + m_player->getPlayerEqiupArmor().def);
	m_player->setCurrentMoveSpeed(m_player->getMoveSpeed() + m_player->getPlayerEqiupWeapon().speed + m_player->getPlayerEqiupArmor().speed);

	// ��ų ����
	if (_isInventorySkill)
	{
		vector<SKILLBOOK> _vTempSkill = m_player->getVPlayerSkill();
		SKILLBOOK _tempSkill;
		// ��ų����
		if (PtInRect(&_playerStatus->getLButtonSkillRc(), m_ptMouse) && m_player->getVPlayerSkill().at(_dragSkillNum).itemKind == item_Skill)
		{
			if (m_player->getPlayerLButtonSkill().itemKind != item_Empty)
			{
				_vTempSkill.push_back(m_player->getPlayerLButtonSkill());
			}
			m_player->setPlayerLButtonSkill(_vTempSkill.at(_dragSkillNum));
			_vTempSkill.erase(_vTempSkill.begin() + _dragSkillNum);
			m_player->setVPlayerSkill(_vTempSkill);
			_isInventorySkill = false;
		}
		if (PtInRect(&_playerStatus->getDashSkillRc(), m_ptMouse) && m_player->getVPlayerSkill().at(_dragSkillNum).itemKind == item_dashSkill)
		{
			if (m_player->getPlayerDashSkill().itemKind != item_Empty)
			{
				_vTempSkill.push_back(m_player->getPlayerDashSkill());
			}
			m_player->setPlayerDashSkill(_vTempSkill.at(_dragSkillNum));
			_vTempSkill.erase(_vTempSkill.begin() + _dragSkillNum);
			m_player->setVPlayerSkill(_vTempSkill);
			_isInventorySkill = false;
		}
		if (PtInRect(&_playerStatus->getRButtonSkillRc(), m_ptMouse) && m_player->getVPlayerSkill().at(_dragSkillNum).itemKind == item_Skill)
		{
			if (m_player->getPlayerRButtonSkill().itemKind != item_Empty)
			{
				_vTempSkill.push_back(m_player->getPlayerRButtonSkill());
			}
			m_player->setPlayerRButtonSkill(_vTempSkill.at(_dragSkillNum));
			_vTempSkill.erase(_vTempSkill.begin() + _dragSkillNum);
			m_player->setVPlayerSkill(_vTempSkill);
			_isInventorySkill = false;
		}
		if (PtInRect(&_playerStatus->getQButtonSkillRc(), m_ptMouse) && m_player->getVPlayerSkill().at(_dragSkillNum).itemKind == item_Skill)
		{
			if (m_player->getPlayerQButtonSkill().itemKind != item_Empty)
			{
				_vTempSkill.push_back(m_player->getPlayerQButtonSkill());
			}
			m_player->setPlayerQButtonSkill(_vTempSkill.at(_dragSkillNum));
			_vTempSkill.erase(_vTempSkill.begin() + _dragSkillNum);
			m_player->setVPlayerSkill(_vTempSkill);
			_isInventorySkill = false;
		}
		if (PtInRect(&_playerStatus->getEButtonSkillRc(), m_ptMouse) && m_player->getVPlayerSkill().at(_dragSkillNum).itemKind == item_Skill)
		{
			if (m_player->getPlayerEButtonSkill().itemKind != item_Empty)
			{
				_vTempSkill.push_back(m_player->getPlayerEButtonSkill());
			}
			m_player->setPlayerEButtonSkill(_vTempSkill.at(_dragSkillNum));
			_vTempSkill.erase(_vTempSkill.begin() + _dragSkillNum);
			m_player->setVPlayerSkill(_vTempSkill);
			_isInventorySkill = false;
		}

		if (PtInRect(&_playerStatus->getRRButtonSkillRc(), m_ptMouse) && m_player->getVPlayerSkill().at(_dragSkillNum).itemKind == item_Skill)
		{
			if (m_player->getPlayerRRButtonSkill().itemKind != item_Empty)
			{
				_vTempSkill.push_back(m_player->getPlayerRRButtonSkill());
			}
			m_player->setPlayerRRButtonSkill(_vTempSkill.at(_dragSkillNum));
			_vTempSkill.erase(_vTempSkill.begin() + _dragSkillNum);
			m_player->setVPlayerSkill(_vTempSkill);
			_isInventorySkill = false;
		}

	}
	// ��ų �ٲٱ�
	if (_isSkillChange)
	{
		if (_isLButtonSkillOff)
		{
			if (PtInRect(&_playerStatus->getRButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerLButtonSkill();
				m_player->setPlayerLButtonSkill(m_player->getPlayerRButtonSkill());
				m_player->setPlayerRButtonSkill(_tempSkill);
			}
			else if (PtInRect(&_playerStatus->getQButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerLButtonSkill();
				m_player->setPlayerLButtonSkill(m_player->getPlayerQButtonSkill());
				m_player->setPlayerQButtonSkill(_tempSkill);
			}
			else if (PtInRect(&_playerStatus->getEButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerLButtonSkill();
				m_player->setPlayerLButtonSkill(m_player->getPlayerEButtonSkill());
				m_player->setPlayerEButtonSkill(_tempSkill);
			}
			else if (PtInRect(&_playerStatus->getRRButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerLButtonSkill();
				m_player->setPlayerLButtonSkill(m_player->getPlayerRRButtonSkill());
				m_player->setPlayerRRButtonSkill(_tempSkill);
			}
			// ��ų ����
			else
			{
				vector<SKILLBOOK> _vTempSkill = m_player->getVPlayerSkill();
				_vTempSkill.push_back(m_player->getPlayerLButtonSkill());
				m_player->setVPlayerSkill(_vTempSkill);
				SKILLBOOK _tempSkill;
				_tempSkill.itemKind = item_Empty;
				m_player->setPlayerLButtonSkill(_tempSkill);
			}
			_isLButtonSkillOff = false;
		}
		// Dash ü����
		if (_isDashSkillOff)
		{
			vector<SKILLBOOK> _vTempSkill = m_player->getVPlayerSkill();
			_vTempSkill.push_back(m_player->getPlayerDashSkill());
			m_player->setVPlayerSkill(_vTempSkill);
			SKILLBOOK _tempSkill;
			_tempSkill.itemKind = item_Empty;
			m_player->setPlayerDashSkill(_tempSkill);

			_isDashSkillOff = false;
		}
		//R��ưü����
		if (_isRButtonSkillOff)
		{
			if (PtInRect(&_playerStatus->getLButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerRButtonSkill();
				m_player->setPlayerRButtonSkill(m_player->getPlayerLButtonSkill());
				m_player->setPlayerLButtonSkill(_tempSkill);
			}
			else if (PtInRect(&_playerStatus->getQButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerRButtonSkill();
				m_player->setPlayerRButtonSkill(m_player->getPlayerQButtonSkill());
				m_player->setPlayerQButtonSkill(_tempSkill);
			}
			else if (PtInRect(&_playerStatus->getEButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerRButtonSkill();
				m_player->setPlayerRButtonSkill(m_player->getPlayerEButtonSkill());
				m_player->setPlayerEButtonSkill(_tempSkill);
			}
			else if (PtInRect(&_playerStatus->getRRButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerRButtonSkill();
				m_player->setPlayerRButtonSkill(m_player->getPlayerRRButtonSkill());
				m_player->setPlayerRRButtonSkill(_tempSkill);
			}
			// ��ų ����
			else
			{
				vector<SKILLBOOK> _vTempSkill = m_player->getVPlayerSkill();
				_vTempSkill.push_back(m_player->getPlayerRButtonSkill());
				m_player->setVPlayerSkill(_vTempSkill);
				SKILLBOOK _tempSkill;
				_tempSkill.itemKind = item_Empty;
				m_player->setPlayerRButtonSkill(_tempSkill);
			}
			_isRButtonSkillOff = false;
		}

		// Q��ư ü����
		if (_isQButtonSkillOff)
		{
			if (PtInRect(&_playerStatus->getLButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerQButtonSkill();
				m_player->setPlayerQButtonSkill(m_player->getPlayerLButtonSkill());
				m_player->setPlayerLButtonSkill(_tempSkill);
			}
			else if (PtInRect(&_playerStatus->getRButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerQButtonSkill();
				m_player->setPlayerQButtonSkill(m_player->getPlayerRButtonSkill());
				m_player->setPlayerRButtonSkill(_tempSkill);
			}
			else if (PtInRect(&_playerStatus->getEButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerQButtonSkill();
				m_player->setPlayerQButtonSkill(m_player->getPlayerEButtonSkill());
				m_player->setPlayerEButtonSkill(_tempSkill);
			}
			else if (PtInRect(&_playerStatus->getRRButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerQButtonSkill();
				m_player->setPlayerQButtonSkill(m_player->getPlayerRRButtonSkill());
				m_player->setPlayerRRButtonSkill(_tempSkill);
			}
			// ��ų ����
			else
			{
				vector<SKILLBOOK> _vTempSkill = m_player->getVPlayerSkill();
				_vTempSkill.push_back(m_player->getPlayerQButtonSkill());
				m_player->setVPlayerSkill(_vTempSkill);
				SKILLBOOK _tempSkill;
				_tempSkill.itemKind = item_Empty;
				m_player->setPlayerQButtonSkill(_tempSkill);
			}
			_isQButtonSkillOff = false;
		}
		// E��ư ü����
		if (_isEButtonSkillOff)
		{
			if (PtInRect(&_playerStatus->getLButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerEButtonSkill();
				m_player->setPlayerEButtonSkill(m_player->getPlayerLButtonSkill());
				m_player->setPlayerLButtonSkill(_tempSkill);
			}
			else if (PtInRect(&_playerStatus->getRButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerEButtonSkill();
				m_player->setPlayerEButtonSkill(m_player->getPlayerRButtonSkill());
				m_player->setPlayerRButtonSkill(_tempSkill);
			}
			else if (PtInRect(&_playerStatus->getQButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerEButtonSkill();
				m_player->setPlayerEButtonSkill(m_player->getPlayerQButtonSkill());
				m_player->setPlayerQButtonSkill(_tempSkill);
			}
			else if (PtInRect(&_playerStatus->getRRButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerEButtonSkill();
				m_player->setPlayerEButtonSkill(m_player->getPlayerRRButtonSkill());
				m_player->setPlayerRRButtonSkill(_tempSkill);
			}
			// ��ų ����
			else
			{
				vector<SKILLBOOK> _vTempSkill = m_player->getVPlayerSkill();
				_vTempSkill.push_back(m_player->getPlayerEButtonSkill());
				m_player->setVPlayerSkill(_vTempSkill);
				SKILLBOOK _tempSkill;
				_tempSkill.itemKind = item_Empty;
				m_player->setPlayerEButtonSkill(_tempSkill);
			}
			_isEButtonSkillOff = false;
		}
		// E��ư ü����
		if (_isRRButtonSkillOff)
		{
			if (PtInRect(&_playerStatus->getLButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerRRButtonSkill();
				m_player->setPlayerRRButtonSkill(m_player->getPlayerLButtonSkill());
				m_player->setPlayerLButtonSkill(_tempSkill);
			}
			else if (PtInRect(&_playerStatus->getRButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerRRButtonSkill();
				m_player->setPlayerRRButtonSkill(m_player->getPlayerRButtonSkill());
				m_player->setPlayerRButtonSkill(_tempSkill);
			}
			else if (PtInRect(&_playerStatus->getQButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerRRButtonSkill();
				m_player->setPlayerRRButtonSkill(m_player->getPlayerQButtonSkill());
				m_player->setPlayerQButtonSkill(_tempSkill);
			}
			else if (PtInRect(&_playerStatus->getEButtonSkillRc(), m_ptMouse))
			{
				SKILLBOOK _tempSkill;
				_tempSkill = m_player->getPlayerRRButtonSkill();
				m_player->setPlayerRRButtonSkill(m_player->getPlayerEButtonSkill());
				m_player->setPlayerEButtonSkill(_tempSkill);
			}
			// ��ų ����
			else
			{
				vector<SKILLBOOK> _vTempSkill = m_player->getVPlayerSkill();
				_vTempSkill.push_back(m_player->getPlayerRRButtonSkill());
				m_player->setVPlayerSkill(_vTempSkill);
				SKILLBOOK _tempSkill;
				_tempSkill.itemKind = item_Empty;
				m_player->setPlayerRRButtonSkill(_tempSkill);
			}
			_isRRButtonSkillOff = false;
		}
	}
}


void playerManager::animation()
{
	// �̵����϶�
	if (_isMove)
	{
		if (_isDown)
		{
			_count++;
			m_player->getPlayerImage()->setFrameY(1);
			if (_count % 10 == 0)
			{
				_count = 0;
				_index++;
				if (_index >= m_player->getPlayerImage()->getMaxFrameX())
				{
					_index = 0;
				}
				m_player->getPlayerImage()->setFrameX(_index);
			}
		}
		if (_isUp)
		{
			_count++;
			m_player->getPlayerImage()->setFrameY(2);
			if (_count % 10 == 0)
			{
				_count = 0;
				_index++;
				if (_index >= m_player->getPlayerImage()->getMaxFrameX())
				{
					_index = 0;
				}
				m_player->getPlayerImage()->setFrameX(_index);
			}
		}
		if (_isLeft)
		{
			_count++;
			m_player->getPlayerImage()->setFrameY(4);
			if (_count % 10 == 0)
			{
				_count = 0;
				_index++;
				if (_index >= m_player->getPlayerImage()->getMaxFrameX())
				{
					_index = 0;
				}
				m_player->getPlayerImage()->setFrameX(_index);
			}
		}
		if (_isRight)
		{
			_count++;
			m_player->getPlayerImage()->setFrameY(3);
			if (_count % 10 == 0)
			{
				_count = 0;
				_index++;
				if (_index >= m_player->getPlayerImage()->getMaxFrameX())
				{
					_index = 0;
				}
				m_player->getPlayerImage()->setFrameX(_index);
			}
		}
	}
	// �뽬
	if (_isDash)
	{
		if (_isLeft)
		{
			m_player->getPlayerImage()->setFrameX(7);
			m_player->getPlayerImage()->setFrameY(8);
		}
		if (_isRight)
		{
			m_player->getPlayerImage()->setFrameX(0);
			m_player->getPlayerImage()->setFrameY(7);
		}
		if (_isUp)
		{
			m_player->getPlayerImage()->setFrameX(0);
			m_player->getPlayerImage()->setFrameY(18);
		}
		if (_isDown)
		{
			m_player->getPlayerImage()->setFrameX(6);
			m_player->getPlayerImage()->setFrameY(18);
		}
	}
	// ��� �� ���⋚
	if (_isDashPause)
	{
		_isMove = false;
		if (_isLeft)
		{
			_count++;
			m_player->getPlayerImage()->setFrameY(8);
			if (_count % 3 == 0)
			{
				_index++;
				m_player->getPlayerImage()->setFrameX(7 - _index);
				if (_index > 7)
				{
					m_player->getPlayerImage()->setFrameX(3);
					m_player->getPlayerImage()->setFrameY(0);
					_index = 0;
					_isDashPause = false;
				}
			}
		}
		if (_isRight)
		{
			_count++;
			m_player->getPlayerImage()->setFrameY(7);
			if (_count % 3 == 0)
			{
				_count = 0;
				_index++;
				m_player->getPlayerImage()->setFrameX(_index);
				if (_index > 7)
				{
					m_player->getPlayerImage()->setFrameX(2);
					m_player->getPlayerImage()->setFrameY(0);
					_index = 0;
					_isDashPause = false;
				}
			}
		}
		if (_isUp)
		{
			_count++;
			m_player->getPlayerImage()->setFrameY(18);
			if (_count % 5 == 0)
			{
				_count = 0;
				_index++;
				m_player->getPlayerImage()->setFrameX(_index);
				if (_index > 2)
				{
					m_player->getPlayerImage()->setFrameX(1);
					m_player->getPlayerImage()->setFrameY(0);
					_index = 0;
					_isDashPause = false;
				}
			}
		}
		if (_isDown)
		{
			_count++;
			m_player->getPlayerImage()->setFrameY(18);
			if (_count % 5 == 0)
			{
				_count = 0;
				_index++;
				m_player->getPlayerImage()->setFrameX(6 - _index);
				if (_index > 3)
				{
					m_player->getPlayerImage()->setFrameX(0);
					m_player->getPlayerImage()->setFrameY(0);
					_index = 0;
					_isDashPause = false;
				}
			}
		}
	}
	// ������ �������
	else if (_isIdle)
	{
		m_player->getPlayerImage()->setFrameY(0);

		if (_isLeft)   m_player->getPlayerImage()->setFrameX(3);
		if (_isRight)m_player->getPlayerImage()->setFrameX(2);
		if (_isUp)   m_player->getPlayerImage()->setFrameX(1);
		if (_isDown)   m_player->getPlayerImage()->setFrameX(0);
	}

	if (m_player->getIsHit())
	{
		m_player->getPlayerImage()->setFrameY(0);
		// �Ʒ� ���
		if (_hitAngle < -0.7 && _hitAngle > -2.5) m_player->getPlayerImage()->setFrameX(4);
		// �� ���
		else if (_hitAngle > 0.7 && _hitAngle < 2.5) m_player->getPlayerImage()->setFrameX(5);
		// ���Ͱ� ���ʿ��� ����
		else if (_hitAngle > -0.7 && _hitAngle < 0.7) m_player->getPlayerImage()->setFrameX(6);
		// ������ ���
		else if (_hitAngle > 2.4 || _hitAngle < -2.5) m_player->getPlayerImage()->setFrameX(7);
	}

}
