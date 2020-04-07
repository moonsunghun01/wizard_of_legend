#include "stdafx.h"
#include "lancer.h"


lancer::lancer()
{
}


lancer::~lancer()
{
}

HRESULT lancer::init()
{
	_lancer = new lancer;
	_lancer->setEnemyImage(IMAGEMANAGER->findImage("랜서"));

	return S_OK;
}

HRESULT lancer::init(const char * imageName, POINT position)
{
	_lancer = new lancer();
	this->setEnemyImage(IMAGEMANAGER->findImage(imageName));
	_summonImage = IMAGEMANAGER->findImage("소환카드");
	_attackImage = IMAGEMANAGER->findImage("큰공격");



	this->setHp(125);
	this->setAtk(50);
	this->setAttribute(ATTR_EARTH);


	this->setEnemyType(ENEMY_MINION_LANCER);


	_lancerRc = RectMake(position.x + 30, position.y + 70, this->getEnemyImage()->getFrameWidth() - 30, this->getEnemyImage()->getFrameHeight() - 70);
	this->setEnemyRc(_lancerRc);

	this->setIsDead(false);
	this->setIsHit(false);

	_x = this->getEnemyRc().left + this->getEnemyImage()->getFrameWidth() / 2;
	_y = this->getEnemyRc().top + this->getEnemyImage()->getFrameHeight() / 2;


	_lancerMoveCollisionRc = RectMake(this->getEnemyRc().left + 30, this->getEnemyRc().top + this->getEnemyImage()->getFrameHeight() - 40, this->getEnemyImage()->getFrameWidth() - 90, 30);


	this->setMoveCollisionRc(_lancerMoveCollisionRc);

	_isSummon = false;

	_lancerAttackCoolTime = 148;
	_deltaTime = 0;

	return S_OK;
}

void lancer::release()
{
	SAFE_DELETE(_lancer);
}

void lancer::update()
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

	if (!_isAtkRange && !_isChasingRange)
	{
		if (_isLeft)
			_currentFrameX = 5;
		if (!_isLeft)
			_currentFrameX = 0;
	}
	beHit();
}

void lancer::render()
{
	for (int i = 0; i < _vAttackRc.size(); i++)
	{
		Rectangle(getMemDC(), _vAttackRc[i].left + m_camera->getCameraX(), _vAttackRc[i].top + m_camera->getCameraY(), _vAttackRc[i].right + m_camera->getCameraX(), _vAttackRc[i].bottom + m_camera->getCameraY());
	}

	if (!_isSummon)
		_summonImage->frameRender(getMemDC(), this->getEnemyRc().left + m_camera->getCameraX() + 10, this->getEnemyRc().top + m_camera->getCameraY(), _summonFrameX, 0);

	if (_isSummon)
		this->getEnemyImage()->frameRender(getMemDC(), this->getEnemyRc().left + m_camera->getCameraX() - 30, this->getEnemyRc().top + m_camera->getCameraY() - 80 /*- m_camera->getCameraY()*/, _currentFrameX, _currentFrameY);

	if (_isAttack)
	{
		if (!_isLeft)
		{
			_attackImage->frameRender(getMemDC(), this->getAttackRc().left - 70, this->getAttackRc().top - 20, _attackFrameX, _attackFrameY);
		}
		else
			_attackImage->frameRender(getMemDC(), this->getAttackRc().left - 50, this->getAttackRc().top - 30, _attackFrameX, _attackFrameY);
	}
}

void lancer::move()
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

			this->setEnemyX(cosf(this->getEnemyAngle()) * 5);
			this->setEnemyY(-sinf(this->getEnemyAngle()) * 5);
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
				_count = 0;
				this->getEnemyImage()->setFrameX(0);
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
				_count = 0;
				this->getEnemyImage()->setFrameX(this->getEnemyImage()->getFrameX() + 1);
				_currentFrameX++;
				if (_currentFrameX > 5)
				{
					_currentFrameX = 0;
				}
			}
		}
	}

	if (!_isAttack && !_isChasingRange)
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

	_lancerMoveCollisionRc = RectMake(this->getEnemyRc().left + 30 + m_camera->getCameraX(), this->getEnemyRc().bottom - 40 + m_camera->getCameraY(), this->getEnemyImage()->getFrameWidth() - 90, 30);//(_ghoulRc.right - _ghoulRc.left) / 2, (_ghoulRc.bottom - _ghoulRc.top) / 2);
	this->setMoveCollisionRc(_lancerMoveCollisionRc);
}

void lancer::dead()
{
	if (this->getIsDead())
	{
		if (_isLeft)
		{
			_currentFrameY = 4;
			_count++;
			if (_count % 7 == 0)
			{
				_count = 0;
				this->getEnemyImage()->setFrameX(8);
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
			if (_count % 7 == 0)
			{
				_count = 0;
				this->getEnemyImage()->setFrameX(0);
				_currentFrameX++;
				if (_currentFrameX > 8)
				{
					this->setIsErase(true);
				}
			}
		}
	}
}

void lancer::summon()
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

void lancer::attack()
{
	if (_isAtkRange)
		_lancerAttackCoolTime += TIMEMANAGER->getElapsedTime() * 60;
	if (_lancerAttackCoolTime > 150)
	{
		_isAttack = true;
	}
	RECT rc;

	if (_lancerAttackCoolTime > 152 )
	{
		if (IntersectRect(&rc, &_lancerAttackRc, &m_player->getPlayerRc()))
		{
			m_player->setIsHit(true);
			m_player->setCurrentHp(m_player->getCurrentHp() - this->getAtk());
			m_player->setMonsetRc(RectMake(this->getEnemyRc().left + m_camera->getCameraX() + 40,
				this->getEnemyRc().top + m_camera->getCameraY(), 40, 100));

			_lancerAttackCoolTime = 0;
		}
		else
		{
			_isAttack = false;
			_lancerAttackCoolTime = 0;
		}
	}
}

void lancer::attackAnimation()
{
	if (_isAttack)
	{
		if (!_isLeft)
		{
			_lancerAttackRc = RectMake(this->getEnemyRc().right - 30 + m_camera->getCameraX(), this->getEnemyRc().top + 60 + m_camera->getCameraY(), 40, 140);
			_currentFrameY = 0;
			_count++;
			if (_count % 8 == 0)
			{
				_count = 0;
				this->getEnemyImage()->setFrameX(0);
				_currentFrameX++;
				if (_currentFrameX == 1)
				{
					_isSlashImage = true;
				}
				if (_currentFrameX > 2)
				{
					_isAttack = false;
				}
			}
			_attackCount++;
			_attackFrameY = 0;
			if (_isSlashImage)
			{
				if (_attackCount % 8 == 0)
				{
					_attackImage->setFrameX(0);
					_attackFrameX++;
					if (_attackFrameX > 2)
					{
						_attackCount = 0;
						_attackFrameX = 0;
						_isSlashImage = false;
					}
				}
			}
		}
		else if (_isLeft)
		{
			_lancerAttackRc = RectMake(this->getEnemyRc().left - 20 + m_camera->getCameraX(), this->getEnemyRc().top + 60 + m_camera->getCameraY(), 40, 140);
			_currentFrameY = 0;
			_count++;
			if (_count % 8 == 0)
			{
				this->getEnemyImage()->setFrameX(5);
				_currentFrameX--;
				if (_currentFrameX == 4)
				{
					_isSlashImage = true;
				}
				if (_currentFrameX < 3)
				{
					_currentFrameX = 5;
					_isAttack = false;
				}
			}
			_attackCount++;
			_attackFrameY = 1;
			if (_isSlashImage)
			{
				if (_attackCount % 8 == 0)
				{
					_attackImage->setFrameX(0);
					_attackFrameX--;
					if (_attackFrameX < 0)
					{
						_attackCount = 0;
						_attackFrameX = 2;
						_isSlashImage = false;

					}
				}
			}
		}
	}
	else
	{
		_attackCount = 0;

	}
	this->setAttackRc(_lancerAttackRc);
}

void lancer::beHit()
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
	if (_isHitHp)
	{
		if (_deltaTime > 19)
		{
			this->setHp(this->getHp() - (m_player->getCurrentAtk() * m_player->getSkillDamage()));
			_isHitHp = false;
		}
	}
}

void lancer::hitAnimation()
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
