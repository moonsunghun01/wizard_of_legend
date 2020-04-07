#include "stdafx.h"
#include "ghoul.h"

#pragma warning(disable:4996)


ghoul::ghoul()
{
}


ghoul::~ghoul()
{
}

HRESULT ghoul::init()
{

	_ghoul = new ghoul;
	_ghoul->setEnemyImage(IMAGEMANAGER->findImage("구울"));
	_summonImage = IMAGEMANAGER->findImage("소환카드");
	_attackImage = IMAGEMANAGER->findImage("작은공격");

	_ghoul->setHp(100);
	_ghoul->setAtk(13);
	_ghoul->setAttribute(ATTR_EARTH);

	_ghoul->getEnemyImage()->setX(0);
	_ghoul->getEnemyImage()->setY(0);
	_ghoul->setIsDead(false);
	_ghoul->setIsHit(false);

	_isSummon = false;


	return S_OK;
}

HRESULT ghoul::init(const char* imageName, POINT position)
{

	_ghoul = new ghoul();
	this->setEnemyImage(IMAGEMANAGER->findImage(imageName));
	_summonImage = IMAGEMANAGER->findImage("소환카드");
	_attackImage = IMAGEMANAGER->findImage("작은공격");





	this->setHp(150);
	this->setAtk(13);
	this->setAttribute(ATTR_EARTH);

	this->setEnemyType(ENEMY_MINION_GHOUL);


	_ghoulRc = RectMake(position.x + 50, position.y + 60, this->getEnemyImage()->getFrameWidth() - 110, this->getEnemyImage()->getFrameHeight() - 70);
	this->setEnemyRc(_ghoulRc);

	this->setIsDead(false);
	this->setIsHit(false);

	_ghoulMoveCollisionRc = RectMake(this->getEnemyRc().left + 70, this->getEnemyRc().top + this->getEnemyImage()->getFrameHeight() - 50, this->getEnemyImage()->getFrameWidth() - 130, 30);


	this->setMoveCollisionRc(_ghoulMoveCollisionRc);

	_isSummon = false;


	_ghoulAttackCoolTime = 95;
	_deltaTime = 0;

	return S_OK;
}

void ghoul::release()
{
	SAFE_DELETE(_ghoul);
}

void ghoul::update()
{
	summon();
	if (_isSummon && !this->getIsDead())
		move();
	dead();
	if (this->getHp() < 0)
	{
		this->setIsDead(true);
	}
	else
		this->setIsDead(false);

	attack();
	attackAnimation();
	beHit();
}

void ghoul::render()
{
	if (!_isSummon)
		_summonImage->frameRender(getMemDC(), this->getEnemyRc().left + m_camera->getCameraX() - 15, this->getEnemyRc().top + m_camera->getCameraY() - 20, _summonFrameX, 0);

	if (_isSummon)
		this->getEnemyImage()->frameRender(getMemDC(), this->getEnemyRc().left + m_camera->getCameraX() - 50, this->getEnemyRc().top - 50 + m_camera->getCameraY() /*- m_camera->getCameraY()*/, _currentFrameX, _currentFrameY);

	if (_isAttack)
	{
	if (!_isLeft)
		{
			_attackImage->frameRender(getMemDC(), this->getAttackRc().left - 30, this->getAttackRc().top, _attackFrameX, _attackFrameY);
		}
		else
			_attackImage->frameRender(getMemDC(), this->getAttackRc().left - 10, this->getAttackRc().top, _attackFrameX, _attackFrameY);

	}

}



void ghoul::move()
{
	_distance = getDistance(this->getEnemyRc().left + (this->getEnemyRc().right - this->getEnemyRc().left) / 2 + m_camera->getCameraX(), this->getEnemyRc().top + (this->getEnemyRc().bottom - this->getEnemyRc().top) / 2 + m_camera->getCameraY(),

		m_player->getPlayerRc().left + (m_player->getPlayerRc().right - m_player->getPlayerRc().left) / 2, m_player->getPlayerRc().top + (m_player->getPlayerRc().bottom - m_player->getPlayerRc().top) / 2);

	if (!_isAtkRange&& _distance <= (m_player->getPlayerImage()->getFrameWidth() / 2) * 10)
	{
		_isChasingRange = true;
	}
	else
		_isChasingRange = false;

	if (_isChasingRange && !_isAttack)
	{
		if (!this->getIsCollision())
			this->setAngle(getAngle(this->getEnemyRc().left + (this->getEnemyRc().right - this->getEnemyRc().left) / 2 + m_camera->getCameraX(), this->getEnemyRc().top + (this->getEnemyRc().bottom - this->getEnemyRc().top) / 2 + m_camera->getCameraY(), m_player->getPlayerRc().left + (m_player->getPlayerRc().right - m_player->getPlayerRc().left) / 2,
				m_player->getPlayerRc().bottom - (m_player->getPlayerRc().bottom - m_player->getPlayerRc().top) / 2));

		if (!this->getMonsterCollision() && !this->getIsHit())
		{

			this->setEnemyX(cosf(this->getEnemyAngle()) * 4);
			this->setEnemyY(-sinf(this->getEnemyAngle()) * 4);
		}
	}
	_angle = getAngle(this->getEnemyRc().left + (this->getEnemyRc().right - this->getEnemyRc().left) / 2 + m_camera->getCameraX(), this->getEnemyRc().top + (this->getEnemyRc().bottom - this->getEnemyRc().top) / 2 + m_camera->getCameraY(),
		m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2, m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2);

	if (_angle > -3.2 && _angle < -1.7)
	{
		if (_distance < (this->getEnemyRc().right - this->getEnemyRc().left) / 2 + (m_player->getPlayerRc().right - m_player->getPlayerRc().left) / 2)
			_isAtkRange = true;
		else
		{
			_isAtkRange = false;
			_isAttack = false;
		}
	}
	if (_angle > -1.7 && _angle < -1.3)
	{
		if (_distance < (this->getEnemyRc().bottom - this->getEnemyRc().top) / 3 + (m_player->getPlayerRc().bottom - m_player->getPlayerRc().top) / 2)
			_isAtkRange = true;
		else
		{
			_isAtkRange = false;
			_isAttack = false;
		}
	}
	if (_angle > 1.9 && _angle < 3.2)
	{
		if (_distance < (this->getEnemyRc().right - this->getEnemyRc().left) / 2 + (m_player->getPlayerRc().right - m_player->getPlayerRc().left) / 2)
			_isAtkRange = true;
		else
		{
			_isAtkRange = false;
			_isAttack = false;
		}
	}
	if (_angle > 1.3 && _angle < 1.7)
	{
		if (_distance < (this->getEnemyRc().bottom - this->getEnemyRc().top) / 3 + (m_player->getPlayerRc().bottom - m_player->getPlayerRc().top) / 2)
			_isAtkRange = true;
		else
		{
			_isAtkRange = false;
			_isAttack = false;
		}
	}
	if (_angle<1.2 && _angle>-1.2)
	{
		if (_distance < (this->getEnemyRc().right - this->getEnemyRc().left) / 2 + (m_player->getPlayerRc().right - m_player->getPlayerRc().left) / 2)
			_isAtkRange = true;
		else
		{
			_isAtkRange = false;
			_isAttack = false;
		}
	}

	if (this->getEnemyRc().left + (this->getEnemyRc().right - this->getEnemyRc().left) / 2 > m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2)
	{
		_isLeft = true;
		if (_isChasingRange)
		{
			_currentFrameY = 2;
			_count++;
			if (_count % 10 == 0)
			{
				this->getEnemyImage()->setFrameX(_currentFrameX);
				_currentFrameX++;
				if (_currentFrameX > 5)
				{
					_currentFrameX = 0;
				}
			}
		}
	}
	if (this->getEnemyRc().left + (this->getEnemyRc().right - this->getEnemyRc().left) / 2 < m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2)
	{
		_isLeft = false;
		if (_isChasingRange)
		{
			_currentFrameY = 1;
			_count++;
			if (_count % 10 == 0)
			{
				this->getEnemyImage()->setFrameX(_currentFrameX);
				_currentFrameX--;
				if (_currentFrameX < 0)
				{
					_currentFrameX = 5;
				}
			}
		}
	}
	_ghoulMoveCollisionRc = RectMake(this->getEnemyRc().left + 70 + m_camera->getCameraX(), this->getEnemyRc().bottom - 50 + m_camera->getCameraY(), this->getEnemyImage()->getFrameWidth() - 130, 30);//(_ghoulRc.right - _ghoulRc.left) / 2, (_ghoulRc.bottom - _ghoulRc.top) / 2);

	this->setMoveCollisionRc(_ghoulMoveCollisionRc);
}

void ghoul::dead()
{
	if (this->getIsDead())
	{
		if (_isLeft)
		{
			_currentFrameY = 4;
			_count++;
			if (_count % 12 == 0)
			{
				this->getEnemyImage()->setFrameX(_currentFrameX);
				_currentFrameX--;
				if (_currentFrameX < 0)
				{
					this->setIsErase(true);
				}
			}
		}
		if (!_isLeft)
		{
			_currentFrameY = 3;
			_count++;
			if (_count % 12 == 0)
			{
				this->getEnemyImage()->setFrameX(_currentFrameX);
				_currentFrameX++;
				if (_currentFrameX > 8)
				{
					this->setIsErase(true);
				}
			}
		}
	}

}

void ghoul::summon()
{
	if (!_isSummon)
	{
		_count++;
		_summonImage->setFrameY(0);
		if (_count % 10 == 0)
		{
			_summonFrameX++;
			_summonImage->setFrameX(_summonFrameX);
			if (_summonFrameX > 9)
			{
				_isSummon = true;
				_summonFrameX = 0;
			}
		}
	}

}

void ghoul::attack()
{
	if (_isAtkRange)
		_ghoulAttackCoolTime += TIMEMANAGER->getElapsedTime() * 60;
	if (_ghoulAttackCoolTime > 100)
	{
		_isAttack = true;
	}
	RECT rc;
	if (_ghoulAttackCoolTime > 102)
	{
		if (IntersectRect(&rc, &_ghoulAttackRc, &m_player->getPlayerRc()))
		{
			m_player->setIsHit(true);
			m_player->setCurrentHp(m_player->getCurrentHp() - this->getAtk());
			m_player->setMonsetRc(RectMake(this->getEnemyRc().left + m_camera->getCameraX() + 40, this->getEnemyRc().top + m_camera->getCameraY(), 40, 100));
			_ghoulAttackCoolTime = 0;
		}
		else
		{
			_ghoulAttackCoolTime = 0;
			_isAttack = false;
		}
	}
}

void ghoul::attackAnimation()
{
	if (_isAttack)
	{
		if (!_isLeft)
		{
			_ghoulAttackRc = RectMake(this->getEnemyRc().right - 20+ m_camera->getCameraX(), this->getEnemyRc().top + 20 + m_camera->getCameraY(), 70, 110);
			_currentFrameY = 0;
			_count++;
			if (_count % 8 == 0)
			{
				this->getEnemyImage()->setFrameX(_currentFrameX);
				_currentFrameX++;
				if (_currentFrameX == 1)
				{
					_isSlashImage = true;
				}
				if (_currentFrameX > 2)
				{
					_isAttack = false;
					_currentFrameX = 0;
				}
			}
			_attackCount++;
			_attackFrameY = 0;
			if (_isSlashImage)
			{
				if (_attackCount % 8 == 0)
				{
					_attackImage->setFrameX(_attackFrameX);
					_attackFrameX++;
					if (_attackFrameX > 2)
					{
						_isSlashImage = false;
						_attackFrameX = 0;
					}
				}
			}
		}
		else if (_isLeft)
		{
			_ghoulAttackRc = RectMake(this->getEnemyRc().left - 20+ m_camera->getCameraX(), this->getEnemyRc().top + 30 + m_camera->getCameraY(), 70, 110);
			_currentFrameY = 0;
			_count++;
			if (_count % 8 == 0)
			{
				this->getEnemyImage()->setFrameX(_currentFrameX);
				_currentFrameX--;
				if (_currentFrameX == 4)
				{
					_isSlashImage = true;
				}
				if (_currentFrameX < 3)
				{
					_isAttack = false;
					_currentFrameX = 5;

				}
			}
			_attackCount++;
			_attackFrameY = 1;
			if (_isSlashImage)
			{
				if (_attackCount % 8 == 0)
				{
					_attackImage->setFrameX(_attackFrameX);
					_attackFrameX--;
					if (_attackFrameX < 0)
					{
						_isSlashImage = false;
						_attackFrameX = 2;

					}
				}
			}
		}


	}
	else
	{
		if (!_isChasingRange)
		{
			if (!_isLeft)
			{
				_currentFrameX = 0;
				_currentFrameY = 0;
			}
			if (_isLeft)
			{
				_currentFrameX = 5;
				_currentFrameY = 0;
			}
		}

		_attackCount = 0;
		for (int i = 0; i < _vAttackRc.size(); i++)
		{
			_vAttackRc.erase(_vAttackRc.begin() + i);
		}
	}

	this->setAttackRc(_ghoulAttackRc);
}

void ghoul::beHit()
{
	if (this->getIsHit() && !this->getIsDead())
	{
		hitAnimation();
		this->setEnemyX(cosf(this->getEnemyAngle())*-2.5);
		this->setEnemyY(-sinf(this->getEnemyAngle())*-2.5);
		_isHitHp = true;
		_deltaTime += TIMEMANAGER->getElapsedTime() * 60;
		if (_deltaTime > 20)
		{
			this->setIsHit(false);
			_deltaTime = 0;
		}
	}
	if (_isHitHp && !this->getIsDead())
	{
		if (_deltaTime > 19)
		{
			this->setHp(this->getHp() - (m_player->getCurrentAtk() * m_player->getSkillDamage()));
			_isHitHp = false;
		}
	}
}

void ghoul::hitAnimation()
{

	if (!_isLeft)
	{
		_currentFrameY = 3;
		_currentFrameX = 0;
	}
	if (_isLeft)
	{
		_currentFrameY = 4;
		_currentFrameX = 8;
	}
}
