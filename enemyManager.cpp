#include "stdafx.h"
#include "enemyManager.h"

#pragma warning(disable:4996)

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	return S_OK;
}

HRESULT enemyManager::init(collisionRc* collisionRc)
{
	_collisionRc = collisionRc;
	//boss
	_iceBoss = new Boss;
	_iceBoss->init(_collisionRc);


	_bossFrameX = 10;
	_bossFrameY = 7;

	_bossSkill = new bossSkill;
	_bossSkill->init(_iceBoss, _collisionRc);

	return S_OK;
}

void enemyManager::release()
{

}

void enemyManager::update()
{

	_viMinion = _vMinion.begin();
	for (int i = 0; i < _vMinion.size(); i++)
	{
		_vMinion.at(i)->update();
		monsterMoveCollision(i);
		monsterCollision(i);
		monsterDeadCheck(i);
	}

	for (int i = 0; i < _vCoin.size(); i++)
	{
		_vCoin[i]->update();
	}
	coinDestroy();


	//boss
	if (_isBossScene && getDistance(_iceBoss->getBossImage()->getX() + _iceBoss->getBossImage()->getFrameWidth() / 2, _iceBoss->getBossImage()->getY() + _iceBoss->getBossImage()->getFrameHeight() / 2
		, m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2, m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2) < 200)
		_isStart = true;
	if (_isBossScene && _isStart)
	{
		if (_iceBoss->getIsBossLive())
		{

			if (!_iceBoss->getIsBattleStart())
				_iceBoss->setIsIceBossReady(true);

			if (_iceBoss->getIsBattleStart())
			{
				_bossSceneDeltaTime += TIMEMANAGER->getElapsedTime();
				_iceBoss->setIsIceBossReady(false);
				if (!_isBossSkill)
				{

					if (_patternCount <= 4)
					{
						_patternCount++;
						_skillNum = RND->getFromIntTo(1, 3);
						//_skillNum = 3;
						_isBossSkill = true;
						_skillStartTime = TIMEMANAGER->getWorldTime();
					}
				}

				if (_isBossSkill && _skillNum == 1)
				{
					_iceBoss->setIceBossMove(false);
					if (_skillStartTime + 1 < TIMEMANAGER->getWorldTime() && _bossSceneDeltaTime < 3)
					{
						_iceBoss->setCurrentFrameY(4);
						_iceBoss->setCurrentFrameX(8);
						_iceBoss->setIceBossBreakTime(false);
						_iceBoss->setIceBossDarkBall(true);
						_skillStartTime = TIMEMANAGER->getWorldTime();
						_bossSkill->skillSetting(1, _iceBoss->getBossImage()->getX() + _iceBoss->getBossImage()->getFrameWidth() / 2, _iceBoss->getBossImage()->getY() + _iceBoss->getBossImage()->getFrameHeight() / 2);
					}

					if (_bossSceneDeltaTime > 3 && _bossSceneDeltaTime <= 5)
					{
						_iceBoss->setIceBossDarkBall(false);
						_iceBoss->setIceBossBreakTime(true);
					}
					if (_bossSceneDeltaTime > 5)
					{
						_bossSceneDeltaTime = 0;
						_isBossSkill = false;
					}
				}
				else if (_isBossSkill && _skillNum == 2)
				{

					if (_iceBoss->getBossWallCollision() && _iceBoss->getIsHurricaneStart())
					{

						_bossSkill->skillSetting(3, _iceBoss->getBossImage()->getX() - 120, _iceBoss->getBossImage()->getY() - 170);

						_iceBoss->setIceBossHurricaneAnimation(true);
						_iceBoss->setIsHurricaneStart(false);
						_iceBoss->setIceBossBreakTime(false);
					}
					else if (!_iceBoss->getBossWallCollision())
					{
						_iceBoss->setIceBossBreakTime(false);
						_bossSkill->setIsDead(false);
						_iceBoss->setIsIceBossMove(true);
						_iceBoss->bossMovePatternSetting(1);
					}
					if (_bossSkill->getIsDead() && _skillStartTime + 1 < TIMEMANAGER->getWorldTime())
					{
						_bossSceneDeltaTime = 0;
						_iceBoss->setIceBossBreakTime(false);
						_iceBoss->setBossWallCollision(false);
						_iceBoss->setIsHurricaneStart(false);
						_isBossSkill = false;
						_iceBoss->setIsAttach(false);
						_iceBoss->setIceBossHurricaneAnimation(false);
					}
				}

				else if (_isBossSkill && _skillNum == 3)
				{

					if (_iceBoss->getIceBossDarkExplosion())
					{
						_iceBoss->setIsIceBossDarkExplosion(true);
						_bossSkill->setIsOn(true);
						_skillStartTime = TIMEMANAGER->getWorldTime();
						_bossSkill->setIsMarionetteOn(true);
						_bossSkill->skillSetting(2, RND->getFromIntTo(100, 500), RND->getFromIntTo(200, 350));
						_bossSkill->skillSetting(2, RND->getFromIntTo(600, 800), RND->getFromIntTo(200, 350));
						_bossSkill->skillSetting(2, RND->getFromIntTo(100, 300), RND->getFromIntTo(450, 750));
						_bossSkill->skillSetting(2, RND->getFromIntTo(600, 800), RND->getFromIntTo(450, 750));

						_iceBoss->setIceBossDarkExplosion(false);
					}
					if (_skillStartTime + 2 < TIMEMANAGER->getWorldTime())
					{
						_iceBoss->setIsIceBossDarkExplosion(false);
						_iceBoss->setIceBossDarkExplosion(true);
						_bossSkill->setIsOn(false);
						_bossSkill->setIsMarionetteOn(false);
						_bossSceneDeltaTime = 0;
						_isBossSkill = false;
					}
				}

				if (_patternCount > 4)
				{
					if (!_isBossSkill)
					{
						_iceBoss->setIceBossBreakTime(false);
						_iceBoss->setIceBossIdle(true);
						if (_bossSceneDeltaTime > 2)
						{
							_patternCount = 0;
							_bossSceneDeltaTime = 0;
							_iceBoss->setIceBossIdle(false);
						}
					}
				}
			}
			_iceBoss->update();
		}
	}
	_bossSkill->update();
}

void enemyManager::render()
{

	for (int i = 0; i < _vCoin.size(); i++)
	{
		_vCoin[i]->render();
	}

	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
		(getMemDC(), (*_viMinion)->getMoveCollisionRc().left, (*_viMinion)->getMoveCollisionRc().top, (*_viMinion)->getMoveCollisionRc().right, (*_viMinion)->getMoveCollisionRc().bottom);
	}


	//boss
	_iceBoss->render();

	_bossSkill->render();

}

void enemyManager::createMonster(int x, int y, int ghoulAmount, int golemAmount, int lancerAmount)
{
	for (int i = 0; i < ghoulAmount; i++)
	{
		_ghoul = new ghoul;
		_ghoul->init("±¸¿ï", PointMake(x + 250 * cos(i), y + sin(i) * 100));
		_vMinion.push_back(_ghoul);
	}
	for (int i = 0; i < golemAmount; i++)
	{
		_golem = new golem;
		_golem->init("°ñ·½", PointMake(x + 250 * cos(i), y + sin(i) * 100));
		_vMinion.push_back(_golem);
	}
	for (int i = 0; i < lancerAmount; i++)
	{
		_lancer = new lancer;
		_lancer->init("·£¼­", PointMake(x + 250 * cos(i), y + sin(i) * 100));
		_vMinion.push_back(_lancer);
	}
}

void enemyManager::coinDestroy()
{
	for (int i = 0; i < _vCoin.size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_vCoin[i]->getCoinCollisionRc(), &m_player->getPlayerRc()))
		{
			m_player->setMoney(m_player->getMoney() + _vCoin[i]->getPrice());
			_vCoin.erase(_vCoin.begin() + i);

		}

	}
}

void enemyManager::monsterMoveCollision(int arrNum)
{
	_vMinion.at(arrNum)->setIsCollision(false);
	for (int i = 0; i < 57; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_vMinion.at(arrNum)->getMoveCollisionRc(), &_collisionRc->getCollisionRc(i)))
		{
			_vMinion.at(arrNum)->setIsCollision(true);
			if (_vMinion.at(arrNum)->getEnemyAngle() > 0.7 && _vMinion.at(arrNum)->getEnemyAngle() < 2.5)
				_vMinion.at(arrNum)->setAngle(0);
			else if (_vMinion.at(arrNum)->getEnemyAngle() < -0.7 && _vMinion.at(arrNum)->getEnemyAngle() > -2.5)
				_vMinion.at(arrNum)->setAngle(0);
			else if (_vMinion.at(arrNum)->getEnemyAngle() > -0.7 && _vMinion.at(arrNum)->getEnemyAngle() < 0.7)
				_vMinion.at(arrNum)->setAngle(-2);
			else if (_vMinion.at(arrNum)->getEnemyAngle() > 2.4 || _vMinion.at(arrNum)->getEnemyAngle() < -2.5)
				_vMinion.at(arrNum)->setAngle(-1);
		}
	}
}

void enemyManager::monsterDeadCheck(int arrNum)
{
	if (_vMinion.at(arrNum)->getIsErase())
	{
		if (dropCoin())
		{
			_randCoinAmount = RND->getFromIntTo(1, 4);
			for (int i = 0; i < _randCoinAmount; i++)
			{
				_coin = new coin;
				_coin->init("ÄÚÀÎ", PointMake(_vMinion.at(arrNum)->getEnemyRc().left + (_vMinion.at(arrNum)->getEnemyRc().right - _vMinion.at(arrNum)->getEnemyRc().left) / 2 + cos(i) * 50, _vMinion.at(arrNum)->getEnemyRc().top + (_vMinion.at(arrNum)->getEnemyRc().bottom - _vMinion.at(arrNum)->getEnemyRc().top) / 2 + sin(i) * 50));
				_vCoin.push_back(_coin);
			}
		}
		_vMinion.erase(_vMinion.begin() + arrNum);
	}
}

void enemyManager::monsterCollision(int arrNum)
{
	_vMinion.at(arrNum)->setMonsterCollision(false);

	for (int j = arrNum; j < _vMinion.size(); j++)
	{
		if (arrNum == j) continue;
		if (_vMinion[arrNum]->getEnemyType() != _vMinion[j]->getEnemyType()) continue;
		RECT rc;
		if (IntersectRect(&rc, &_vMinion.at(arrNum)->getMoveCollisionRc(), &_vMinion.at(j)->getMoveCollisionRc()))
		{
			_vMinion.at(arrNum)->setMonsterCollision(true);

		}
	}

}

bool enemyManager::dropCoin()
{
	_randCoin = RND->getFromIntTo(1, 12);
	if (_randCoin % 2 == 0)
	{
		return true;
	}
	return false;
}

//boss
void enemyManager::moveBoss()
{
	_bossMoveCount++;
}
