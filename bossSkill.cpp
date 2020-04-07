#include "stdafx.h"
#include "bossSkill.h"

#pragma warning(disable:4996)


HRESULT bossSkill::init(Boss * boss, collisionRc* collisionRc)
{
	_boss = boss;
	_collisionRc = collisionRc;
	IMAGEMANAGER->addFrameImage("darkBall", "images/Boss/darkBall.bmp", _boss->getBossImage()->getX(), _boss->getBossImage()->getY(), 192 * 2, 48 * 2, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("hurricane", "images/Boss/hurricane.bmp", _boss->getBossImage()->getX(), _boss->getBossImage()->getY(), 320 * 6, 192 * 6, 5, 3, true, RGB(0, 0, 0));

	_darkDollImage = IMAGEMANAGER->addImage("어둠인형", "images/Boss/어둠인형블랙2.bmp", 450 * 3, 360 * 3, true, RGB(0, 0, 0)); //스킬 어둠인형
	_darkBombImage = IMAGEMANAGER->addImage("어둠폭발", "images/Boss/어둠폭발블랙.bmp", 1350 * 2, 130 * 2, true, RGB(0, 0, 0)); // 스킬 어둠폭발

	int _skillMarionette[] = { 0,5,6,7,8 };//스킬 다크마리오네트
	_marionetteEffect[1] = new animation;
	_marionetteEffect[1]->init(_darkDollImage->getWidth(), _darkDollImage->getHeight(), 450, 360);
	_marionetteEffect[1]->setPlayFrame(_skillMarionette, 5, false);
	_marionetteEffect[1]->setFPS(1);

	int _skillDarkExplosion[] = { 0,1,2,3,4,5,6,7,8 }; // 스킬 어둠폭발
	_marionetteEffect[2] = new animation;
	_marionetteEffect[2]->init(_darkBombImage->getWidth(), _darkBombImage->getHeight(), 300, 260);
	_marionetteEffect[2]->setPlayFrame(_skillDarkExplosion, 9, true);
	_marionetteEffect[2]->setFPS(1);



	return S_OK;
}

void bossSkill::release()
{
}

void bossSkill::update()
{

	bossSkillAnimation();
	skillMove();
	skillLiveCheck();
	skillDeadCheck();

	for (int i = 0; i < _vBossSkill.size(); i++)
	{
		if (_vBossSkill[i].isLive)
		{
			_vBossSkill[i].bossSkillActiveTime += TIMEMANAGER->getElapsedTime();
		}
	}
}

void bossSkill::render()
{

	for (int i = 0; i < _vBossSkill.size(); i++)
	{
		if (_vBossSkill[i].isLive)
		{
			_vBossSkill[i].bossSkillImage->alphaFrameRender(getMemDC(), _vBossSkill[i].bossSkillRc.left + m_camera->getCameraX(), _vBossSkill[i].bossSkillRc.top + m_camera->getCameraY(),
				_vBossSkill[i].currentFrameX, _vBossSkill[i].currentFrameY, _vBossSkill[i].alpha);
			if (_vBossSkill[i].skillEnum == DARKEXPLOSION)
			{
				if (_marionetteEffect[1]->getIsMarionetteEnd())
				{
					_vBossSkill[i].bossSkillImage->aniAlphaRender(getMemDC(), _vBossSkill[i].bossSkillRc.left + m_camera->getCameraX(), _vBossSkill[i].bossSkillRc.top + m_camera->getCameraY(), _marionetteEffect[2], 255);
				}

			}
		}
	}
	if (_isMarionetteOn)
	{
		_darkDollImage->aniAlphaRender(getMemDC(), _boss->getBossImage()->getX() + _boss->getBossImage()->getFrameWidth() / 2 - _darkDollImage->getWidth() / 3 / 2 + m_camera->getCameraX(), _boss->getBossImage()->getY() + _boss->getBossImage()->getFrameHeight() / 2 - _darkDollImage->getHeight() / 3 / 2 + m_camera->getCameraY() - 70, _marionetteEffect[1], 170);

	}

}

void bossSkill::bossSkillAnimation()
{

	for (int i = 0; i < _vBossSkill.size(); i++)
	{
		if (_vBossSkill[i].isLive)
		{
			if (_vBossSkill[i].skillEnum == DARKBALL)
			{
				_vBossSkill[i].skillCount++;
				_vBossSkill[i].currentFrameY = 0;
				if (_vBossSkill[i].skillCount % 3 == 0)
				{
					_vBossSkill[i].currentFrameX++;
					_vBossSkill[i].bossSkillImage->setFrameX(_vBossSkill[i].currentFrameX);
					if (_vBossSkill[i].currentFrameX > 3)
					{
						_vBossSkill[i].currentFrameX = 0;
					}
				}
			}
			if (_vBossSkill[i].skillEnum == HURRICANE)
			{
				_vBossSkill[i].skillCount++;
				_vBossSkill[i].currentFrameY = 1;
				if (_vBossSkill[i].skillCount % 3 == 0)
				{
					_vBossSkill[i].currentFrameX++;
					_vBossSkill[i].bossSkillImage->setFrameX(_vBossSkill[i].currentFrameX);
					if (_vBossSkill[i].currentFrameX > 2)
					{
						_vBossSkill[i].currentFrameX = 0;
					}
				}
			}

			if (_vBossSkill[i].skillEnum == DARKEXPLOSION)
			{
				if (_isMarionetteOn && _isOn)
				{
					_marionetteEffect[1]->start();
					_isOn = false;
				}
				if (_marionetteEffect[1]->getIsMarionetteEnd())
				{
					_marionetteEffect[2]->resume();
				}
				_marionetteEffect[1]->frameUpdate(0.05); //다크마리오네트
				_marionetteEffect[2]->frameUpdate(0.05); //다크마리오네트



			}
		}

	}
}


void bossSkill::skillSetting(int activeSkillNum, float x, float y)
{
	_isDead = false;
	_isSkillActive = true;
	_bossSkill.isLive = true;
	_activeSkillNum = activeSkillNum;
	if (_isSkillActive)
	{
		if (_activeSkillNum == 1)
		{
			_bossSkill.isCollisionErase = true;
			_bossSkill.alpha = 255;
			_bossSkill.skillEnum = DARKBALL;
			_bossSkill.count = 0;
			_bossSkill.bossSkillImage = IMAGEMANAGER->findImage("darkBall");
			_bossSkill.bossSkillRc = RectMake(x, y, _bossSkill.bossSkillImage->getFrameWidth(), _bossSkill.bossSkillImage->getFrameHeight());
			_bossSkill.skillLifeTime = 5.0f;

			_bossSkill.bossSkillAngle = getAngle(_boss->getBossImage()->getX() + _boss->getBossImage()->getFrameWidth() / 2
				, _boss->getBossImage()->getY() + _boss->getBossImage()->getFrameHeight() / 2,
				m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2,
				m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2);
			_bossSkill.bossSkillCollisionRc = RectMake(_bossSkill.bossSkillRc.left + m_camera->getCameraX(), _bossSkill.bossSkillRc.top + m_camera->getCameraY(), _bossSkill.bossSkillImage->getFrameWidth(), _bossSkill.bossSkillImage->getFrameHeight());


			_vBossSkill.push_back(_bossSkill);
		}
		else if (_activeSkillNum == 2)
		{
			_bossSkill.isCollisionErase = false;
			_bossSkill.alpha = 255;
			_bossSkill.skillEnum = DARKEXPLOSION;
			_bossSkill.count = 0;
			_bossSkill.bossSkillImage = IMAGEMANAGER->findImage("어둠폭발");
			_bossSkill.bossSkillRc = RectMake(x, y, _bossSkill.bossSkillImage->getWidth() / 9, _bossSkill.bossSkillImage->getHeight());
			_bossSkill.skillLifeTime = 2.0f;

			_bossSkill.bossSkillCollisionRc = RectMake(_bossSkill.bossSkillRc.left + 30 + m_camera->getCameraX(), _bossSkill.bossSkillRc.top + 30 + m_camera->getCameraY(), _bossSkill.bossSkillImage->getWidth() / 9 - 30, _bossSkill.bossSkillImage->getHeight() - 30);

			_vBossSkill.push_back(_bossSkill);//위에 적을것들을 담아주는 명령어
		}
		else if (_activeSkillNum == 3)
		{
			_bossSkill.isCollisionErase = false;
			_bossSkill.hitCount = 0;
			_bossSkill.alpha = 100;
			_bossSkill.skillEnum = HURRICANE;
			_bossSkill.bossSkillImage = IMAGEMANAGER->findImage("hurricane");
			_bossSkill.bossSkillRc = RectMake(x, y, _bossSkill.bossSkillImage->getFrameWidth(), _bossSkill.bossSkillImage->getFrameHeight());
			_bossSkill.skillLifeTime = 2.0f;
			_vBossSkill.push_back(_bossSkill);
		}
	}


}

void bossSkill::skillMove()
{
	for (int i = 0; i < _vBossSkill.size(); i++)
	{
		if (_vBossSkill[i].isLive)
		{
			if (_vBossSkill[i].skillEnum == DARKBALL)
			{
				_vBossSkill[i].bossSkillAngle = skillWallCollision(_vBossSkill[i]);
				_vBossSkill[i].bossSkillRc.left += cosf(_vBossSkill[i].bossSkillAngle) * 10;
				_vBossSkill[i].bossSkillRc.right += cosf(_vBossSkill[i].bossSkillAngle) * 10;
				_vBossSkill[i].bossSkillRc.top += -sinf(_vBossSkill[i].bossSkillAngle) * 10;
				_vBossSkill[i].bossSkillRc.bottom += -sinf(_vBossSkill[i].bossSkillAngle) * 10;
				_vBossSkill[i].skillCount++;
				_vBossSkill[i].bossSkillCollisionRc = RectMake(_vBossSkill[i].bossSkillRc.left + m_camera->getCameraX(), _vBossSkill[i].bossSkillRc.top + m_camera->getCameraY(), _vBossSkill[i].bossSkillImage->getFrameWidth(), _vBossSkill[i].bossSkillImage->getFrameHeight());
			}
			if (_vBossSkill[i].skillEnum == HURRICANE)
			{
				_vBossSkill[i].bossSkillRc.left = _boss->getBossImage()->getX() - 120;
				_vBossSkill[i].bossSkillRc.top = _boss->getBossImage()->getY() - 170;
				_vBossSkill[i].bossSkillCollisionRc = RectMake(_vBossSkill[i].bossSkillRc.left + m_camera->getCameraX(), _vBossSkill[i].bossSkillRc.top + m_camera->getCameraY(), _vBossSkill[i].bossSkillImage->getFrameWidth(), _vBossSkill[i].bossSkillImage->getFrameHeight());
			}

			if (_vBossSkill[i].skillEnum == DARKEXPLOSION)
			{
				_vBossSkill[i].bossSkillCollisionRc = RectMake(_vBossSkill[i].bossSkillRc.left + 100 + m_camera->getCameraX(), _vBossSkill[i].bossSkillRc.top + m_camera->getCameraY() + 70, _vBossSkill[i].bossSkillImage->getWidth() / 9 - 210, _vBossSkill[i].bossSkillImage->getHeight() - 100);

			}
		}

	}



}

void bossSkill::skillLiveCheck()
{
	for (int i = 0; i < _vBossSkill.size(); i++)
	{
		RECT rc;
		if (_vBossSkill[i].skillLifeTime < _vBossSkill[i].bossSkillActiveTime)
		{
			_vBossSkill[i].isLive = false;
		}
		if (IntersectRect(&rc, &m_player->getPlayerRc(), &_vBossSkill[i].bossSkillCollisionRc))
		{
			m_player->setIsHit(true);
			if (_vBossSkill[i].isCollisionErase)
				_vBossSkill[i].isLive = false;
			if (_vBossSkill[i].skillEnum == DARKBALL)
			{
				m_player->setCurrentHp(m_player->getCurrentHp() - 45);
			}
			else if (_vBossSkill[i].skillEnum == HURRICANE)
			{
				if (_vBossSkill[i].hitCount < 3)
				{
					_vBossSkill[i].hitCount++;
					m_player->setCurrentHp(m_player->getCurrentHp() - 15);
				}
			}
			else if (_vBossSkill[i].skillEnum == DARKEXPLOSION)
			{
				if (_vBossSkill[i].hitCount < 5)
				{
					_vBossSkill[i].hitCount++;
					m_player->setCurrentHp(m_player->getCurrentHp() - 10);
				}
			}
			m_player->setMonsetRc(RectMake(_vBossSkill[i].bossSkillRc.left + m_camera->getCameraX() + 40, _vBossSkill[i].bossSkillRc.top + m_camera->getCameraY(), 40, 100));
		}
	}
}

float bossSkill::skillWallCollision(tagBossSkill bossSkill)
{

	RECT _tempRc;
	//왼
	if (IntersectRect(&_tempRc, &_collisionRc->getCollisionRc(0), &bossSkill.bossSkillCollisionRc))
	{
		bossSkill.bossSkillAngle = 3.14 - bossSkill.bossSkillAngle;
	}
	//위
	if (IntersectRect(&_tempRc, &_collisionRc->getCollisionRc(1), &bossSkill.bossSkillCollisionRc))
	{
		bossSkill.bossSkillAngle = 3.14 * 2 - bossSkill.bossSkillAngle;
	}
	//오
	if (IntersectRect(&_tempRc, &_collisionRc->getCollisionRc(2), &bossSkill.bossSkillCollisionRc))
	{
		bossSkill.bossSkillAngle = 3.14 - bossSkill.bossSkillAngle;
	}
	//아
	if (IntersectRect(&_tempRc, &_collisionRc->getCollisionRc(3), &bossSkill.bossSkillCollisionRc))
	{
		bossSkill.bossSkillAngle = 3.14 * 2 - bossSkill.bossSkillAngle;
	}
	return bossSkill.bossSkillAngle;
}

void bossSkill::skillDeadCheck()
{
	for (int i = 0; i < _vBossSkill.size(); i++)
	{
		if (!_vBossSkill[i].isLive)
		{
			_vBossSkill[i].bossSkillActiveTime = 0;
			_vBossSkill.erase(_vBossSkill.begin() + i);
			_isDead = true;
		}
	}
}
