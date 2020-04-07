#include "stdafx.h"
#include "Boss.h"

#pragma warning(disable:4996)
Boss::Boss()
{
}

Boss::~Boss()
{

}

HRESULT Boss::init(collisionRc* collisionRc)
{
	_collisionRc = collisionRc;
	_bossImage = IMAGEMANAGER->addFrameImage("iceBoss", "images/Boss/Boss.bmp", 1650, 2000, 11, 10, true, RGB(255, 0, 255));
	_currentFrameX = 2;
	_currentFrameY = 2;
	_bossImage->setX(420);
	_bossImage->setY(250);
	_bossHp = 1000;
	_bossCurrentHp = _bossHp;
	_bossAtk = 10;
	_bossSpeed = 10;
	_enemyMoveState = ENEMY_MOVE_IDLE;


	_isBossLive = true;
	return S_OK;
}

HRESULT Boss::init()
{

	return S_OK;
}

void Boss::release()
{
}

void Boss::update()
{
	if (_bossCurrentHp <= 0)
	{
		_isBossLive = false;
	}
	bossPatternMove();
	animation();

	if (_isBeHit) beHit();
}

void Boss::render()
{
	_bossImage->frameRender(getMemDC(), _bossImage->getX() + m_camera->getCameraX(), _bossImage->getY() + m_camera->getCameraY(), _currentFrameX, _currentFrameY);
}

bool Boss::bossWallCollision()
{
	RECT _tempRc;
	if (IntersectRect(&_tempRc, &_collisionRc->getCollisionRc(0), &_bossRc))
	{
		_isBossMove = false;
		_isWallCollision = true;
		_isHurricaneStart = true;
		_patternNum = 0;
		_bossImage->setX(_bossImage->getX() - 100);
	}
	//위
	if (IntersectRect(&_tempRc, &_collisionRc->getCollisionRc(1), &_bossRc))
	{
		_isBossMove = false;
		_isBossMove = false;
		_isWallCollision = true;
		_isHurricaneStart = true;
		_patternNum = 0;
		_bossImage->setY(_bossImage->getY() + 100);
	}
	//오
	if (IntersectRect(&_tempRc, &_collisionRc->getCollisionRc(2), &_bossRc))
	{
		_isBossMove = false;
		_isWallCollision = true;
		_isHurricaneStart = true;
		_patternNum = 0;
		_bossImage->setX(_bossImage->getX() + 100);
	}
	//아
	if (IntersectRect(&_tempRc, &_collisionRc->getCollisionRc(3), &_bossRc))
	{
		_isBossMove = false;
		_isWallCollision = true;
		_isHurricaneStart = true;
		_patternNum = 0;
		_bossImage->setY(_bossImage->getY() - 100);
	}

	return _isWallCollision;

}


void Boss::animation()
{
	if (!_isWallCollision&& _isBossMove && !_iceBossHurricaneAnimation && !_iceBossDarkBall && !_iceBossBreakTime && !_isIceBossReady && !_iceBossIdle)
	{
		//왼쪽
		if (_bossMoveAngle > -3.2 && _bossMoveAngle < -1.7)
		{
			_currentFrameY = 0;
			_currentFrameX = 0;
		}
		//아래쪽
		if (_bossMoveAngle > -1.7 && _bossMoveAngle < -1.3)
		{
			_currentFrameY = 0;
			_currentFrameX = 2;
		}
		//왼쪽
		if (_bossMoveAngle > 1.9 && _bossMoveAngle < 3.2)
		{
			_currentFrameY = 0;
			_currentFrameX = 0;
		}
		//위쪽
		if (_bossMoveAngle > 1.3 && _bossMoveAngle < 1.7)
		{
			_currentFrameY = 0;
			_currentFrameX = 3;
		}
		//오른쪽
		if (_bossMoveAngle<1.2 && _bossMoveAngle>-1.2)
		{
			_currentFrameY = 0;
			_currentFrameX = 1;
		}
	}

	if (_iceBossBreakTime && !_iceBossDarkBall && !_iceBossHurricaneAnimation && !_isIceBossReady)
	{
		_currentFrameY = 4;
		_currentFrameX = 8;
	}

	if (_iceBossHurricaneAnimation && !_iceBossDarkBall && !_iceBossIdle && !_iceBossBreakTime && !_isIceBossReady)
	{
		_bossHurricaneCount++;
		_currentFrameY = 2;

		if (_bossHurricaneCount % 3 == 0)
		{
			_currentFrameX++;
			if (_currentFrameX > 9)
			{
				_currentFrameX = 3;
				_bossHurricaneCount = 0;
			}
		}
	}

	if (_iceBossIdle && !_iceBossDarkBall && !_iceBossHurricaneAnimation && !_iceBossBreakTime && !_isIceBossReady)
	{
		_bossIdleCount++;
		_currentFrameY = 6;
		if (_bossIdleCount % 15 == 0)
		{
			_currentFrameX++;
			if (_currentFrameX > 2)
			{
				_currentFrameX = 0;

			}
		}
	}

	if (_isIceBossReady && !_iceBossDarkBall && !_iceBossHurricaneAnimation && !_iceBossBreakTime && !_iceBossIdle)
	{
		_bossReadyCount++;
		_currentFrameY = 6;

		if (_bossReadyCount % 15 == 0)
		{
			_currentFrameX++;
			if (_currentFrameX > 2)
			{
				_currentFrameX = 0;
				_isBattleStart = true;
			}
		}
	}

	if (_iceBossDarkBall && !_isIceBossReady && !_iceBossIdle && !_iceBossHurricaneAnimation && !_iceBossBreakTime && _isBattleStart)
	{
		_bossDarkBallCount++;
		if (_bossDarkBallCount % 15 == 0)
		{
			_currentFrameX++;
			if (_currentFrameX > 9)
			{
				_currentFrameX = 8;
				_bossDarkBallCount = 0;
			}
		}
	}

}

void Boss::bossMovePatternSetting(int patternNum)
{
	_patternNum = patternNum;
	if (_patternNum == 1)
	{
		if (!_isAttach)
		{
			_pointX = m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2;
			_pointY = m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2;
			_bossMoveAngle = getAngle(_bossImage->getX() + _bossImage->getFrameWidth() / 2, _bossImage->getY() + _bossImage->getFrameHeight() / 2
				, m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2, m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2);
			_isAttach = true;
		}
	}
}

void Boss::bossPatternMove()
{
	if (_patternNum == 1)
	{
		if (!bossWallCollision())
		{
			_bossImage->setX(_bossImage->getX() + cosf(_bossMoveAngle) * 15);
			_bossImage->setY(_bossImage->getY() - sinf(_bossMoveAngle) * 15);
		}
	}
	_bossCollisionRc = RectMake(_bossImage->getX(), _bossImage->getY(), _bossImage->getFrameWidth(), _bossImage->getFrameHeight());
	_bossRc = RectMake(_bossImage->getX() + m_camera->getCameraX(), _bossImage->getY() + m_camera->getCameraY(), _bossImage->getFrameWidth(), _bossImage->getFrameHeight());
}

void Boss::beHit()
{
	_hitTimeCount++;
	if (_hitTimeCount > 5)
	{
		_bossCurrentHp -= m_player->getAtk()*m_player->getSkillDamage();
		_isBeHit = false;
		_hitTimeCount = 0;
	}
}


