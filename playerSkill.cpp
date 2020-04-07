#include "stdafx.h"
#include "playerSkill.h"

HRESULT playerSkill::init()
{
	// 스킬 이미지 초기화
	IMAGEMANAGER->addFrameImage("waterSkill", "images/playerSkill/물근접.bmp", 116, 448, 1, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("windSkill", "images/playerSkill/windSkill.bmp", 380, 80, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("iceSkill", "images/playerSkill/iceCrystal.bmp", 840, 199, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("thunderSkill", "images/playerSkill/thunderSkill.bmp", 2048, 512, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("thunderChain", "images/playerSkill/thunderChain.bmp", 540, 900, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("iceRain", "images/playerSkill/Blizzard.bmp", 128 , 128, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("meteor", "images/playerSkill/meteor.bmp", 352 *5 , 178 *5, 4, 1, true, RGB(255, 0, 255)); 
	_castingCircle = IMAGEMANAGER->addFrameImage("castingCircle", "images/playerSkill/CastingCircle.bmp", 3328 , 128, 26, 1, true, RGB(0, 0, 0));
	_explosion =  IMAGEMANAGER->addFrameImage("explosion", "images/playerSkill/explosion.bmp",847 * 6 , 61 * 6, 11, 1, true, RGB(255, 0, 255)); 

	IMAGEMANAGER->addFrameImage("sharkPool", "images/playerSkill/sharkPool.bmp",608 * 3, 68 * 3, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shark", "images/playerSkill/shark.bmp",720 * 3, 80 * 3 , 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WaterBombExplosion", "images/playerSkill/WaterBombExplosion2.bmp",1120 * 2.3, 160 * 2.3 , 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("IceBall", "images/playerSkill/IceBall.bmp",64 * 2,16 * 2, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("blackHole", "images/playerSkill/blackHole.bmp",1320,110, 12, 1, true, RGB(255, 0, 255));
	
	_delayCount = 0;
	return S_OK;
}
void playerSkill::release()
{
}

void playerSkill::update()
{
	// 스킬 애니매이션
	skillAnimation();
	// 플레이어 애니매이션
	playerSkillAnimadtion();
	// 스킬 이동 시 
	skillMove(); 
}

void playerSkill::render()
{
	if (_isSkillActive)
	{
		// 근접 물
		if (_skillNum == 1)
		{
			 _vSkill.at(0).skillImage->frameRender(getMemDC(), _vSkill.at(0).skillImage->getX() + m_camera->getCameraX(), _vSkill.at(0).skillImage->getY() + m_camera->getCameraY());
		}
		// 바람개비
		if (_skillNum == 2)
		{
			//_tagSkill.skillImage->frameRender(getMemDC(), _tagSkill.skillImage->getX() + m_camera->getCameraX(), _tagSkill.skillImage->getY() + m_camera->getCameraY());
			_vSkill.at(0).skillImage->frameRender(getMemDC(), _vSkill.at(0).skillImage->getX() + m_camera->getCameraX(), _vSkill.at(0).skillImage->getY() + m_camera->getCameraY());
			
		}
		// 얼음기둥
		if (_skillNum == 3)
		{  
			if (_delayCount > 5 )
			{
				_vSkill.at(0).skillImage->frameRender(getMemDC(), 
					cosf(_skillAngle)  + _vSkill.at(0).skillImage->getX() + m_camera->getCameraX(),
					(-sinf(_skillAngle)  + _vSkill.at(0).skillImage->getY() - 40 ) + m_camera->getCameraY() , (_delayCount - 6) / 3, 0); 
				 
				_vSkill.at(0).skillRc = RectMake(_vSkill.at(0).skillImage->getX()  ,
					_vSkill.at(0).skillImage->getY() ,
					_vSkill.at(0).skillImage->getFrameWidth(), _vSkill.at(0).skillImage->getFrameHeight()); 
			}
			if (_delayCount > 10 )
			{
				_vSkill.at(1).skillImage->frameRender(getMemDC(),
					cosf(_skillAngle) * 120  + _vSkill.at(0).skillImage->getX() + m_camera->getCameraX(),
					(-sinf(_skillAngle)* (120 ) + _vSkill.at(0).skillImage->getY() - 40) + m_camera->getCameraY(), (_delayCount - 11) / 3, 0);
			 
				_vSkill.at(1).skillRc = RectMake(_vSkill.at(1).skillImage->getX() + cosf(_skillAngle) * 120,
					_vSkill.at(1).skillImage->getY() + (-sinf(_skillAngle)* (120)),
					_vSkill.at(1).skillImage->getFrameWidth(), _vSkill.at(1).skillImage->getFrameHeight());
			}
			
			if (_delayCount > 15 )
			{
				_vSkill.at(2).skillImage->frameRender(getMemDC(),
					cosf(_skillAngle) * (120 *2) + _vSkill.at(0).skillImage->getX() + m_camera->getCameraX(),
					(-sinf(_skillAngle)* (120 * 2) + _vSkill.at(0).skillImage->getY() - 40) + m_camera->getCameraY(), (_delayCount - 16) / 3,0);
				
				_vSkill.at(2).skillRc = RectMake(_vSkill.at(2).skillImage->getX() + cosf(_skillAngle) * (120 * 2),
					_vSkill.at(2).skillImage->getY() + (-sinf(_skillAngle)* (120 * 2)),
					_vSkill.at(2).skillImage->getFrameWidth(), _vSkill.at(2).skillImage->getFrameHeight());
			} 
			_delayCount++;
			if (_delayCount > 50)
			{
				_isSkillActive = false;
				_vSkill.clear();
				_delayCount = 0;
			}
		}
		// 번개
		if (_skillNum == 4)
		{
			_vSkill.at(0).skillImage->frameRender(getMemDC(), _vSkill.at(0).skillImage->getX() + m_camera->getCameraX()
				, _vSkill.at(0).skillImage->getY() +m_camera->getCameraY());

			for (int i = 1; i < _vSkill.size(); i++)
			{
				_vSkill.at(i).skillImage->frameRender(getMemDC(),
					_vSkill.at(0).skillImage->getX() 
					+ RND->getFromIntTo(0,400)+ m_camera->getCameraX(),
					_vSkill.at(0).skillImage->getY() 
					- _vSkill.at(0).skillImage->getFrameHeight() / 2 
					+ RND->getFromIntTo(-200, 300) 
					+ m_camera->getCameraY());
			}
		}
		// 메테오
		if (_skillNum == 5)
		{  
			_castingCircle->frameRender(getMemDC(),_castingCircle->getX() + m_camera->getCameraX(),
				_castingCircle->getY() + m_camera->getCameraY(), _castingCircleFrameX,0); 
			_vSkill.at(0).skillImage->frameRender(getMemDC(), _vSkill.at(0).skillImage->getX() + m_camera->getCameraX()
				, _vSkill.at(0).skillImage->getY() + m_camera->getCameraY()); 
		}
		// 피즈
		if (_skillNum == 6)
		{ 
			if(!_isStartShark) _vSkill.at(0).skillImage->frameRender(getMemDC(), _vSkill.at(0).skillImage->getX() + m_camera->getCameraX(), _vSkill.at(0).skillImage->getY() + m_camera->getCameraY());

			else
			{
				_vSkill.at(1).skillImage->frameRender(getMemDC(), _vSkill.at(1).skillImage->getX() + m_camera->getCameraX()
					, _vSkill.at(1).skillImage->getY() + m_camera->getCameraY());
				if (_vSkill.at(1).skillIndex == 8)
				{
					_vSkill.at(3).skillImage->frameRender(getMemDC(), _vSkill.at(3).skillImage->getX() + m_camera->getCameraX()
						, _vSkill.at(3).skillImage->getY() + m_camera->getCameraY());

					_vSkill.at(2).skillImage->frameRender(getMemDC(), _vSkill.at(2).skillImage->getX() + m_camera->getCameraX()
						, _vSkill.at(2).skillImage->getY() + m_camera->getCameraY());

					_vSkill.at(2).skillRc = (RectMake(_vSkill.at(2).skillImage->getX()
						, _vSkill.at(2).skillImage->getY(),
						_vSkill.at(2).skillImage->getFrameWidth(), _vSkill.at(2).skillImage->getFrameHeight()));
				}
			}
		}

		// 블랙홀
		if (_skillNum == 7)
		{
			_vSkill.at(0).skillImage->frameRender(getMemDC(), _vSkill.at(0).skillImage->getX() + m_camera->getCameraX()
				, _vSkill.at(0).skillImage->getY() + m_camera->getCameraY());
		}
	} 
	if (_isExplosion)
	{
		_explosion->frameRender(getMemDC(), _explosion->getX() + m_camera->getCameraX(),
			_explosion->getY() + m_camera->getCameraY(), _explosionFrameX, 0);
	}
	//Rectangle(getMemDC(), _tagSkill.skillRc.left, _tagSkill.skillRc.top, _tagSkill.skillRc.right, _tagSkill.skillRc.bottom);
	/*for (int i = 0; i < _vSkill.size(); i++)
	{
		Rectangle(getMemDC(), _vSkill.at(i).skillRc.left, _vSkill.at(i).skillRc.top,
			_vSkill.at(i).skillRc.right, _vSkill.at(i).skillRc.bottom);
	}*/
}

// 스킬 프레임 애니매이션
void playerSkill::skillAnimation()
{ 
	if (_isSkillActive)
	{
		if (_skillNum == 1)
		{
			_tagSkill.skillCount++;
			_tagSkill.skillImage->setFrameX(0);
			if (_tagSkill.skillCount % 3 == 0)
			{
				_tagSkill.skillIndex++;
				_tagSkill.skillImage->setFrameY(_tagSkill.skillIndex);
				if (_tagSkill.skillIndex > _tagSkill.skillImage->getMaxFrameY())
				{
					_tagSkill.skillIndex = 0;
					_tagSkill.skillCount = 0;
					_isSkillActive = false;
					_vSkill.clear();
				}
			}
		}
		if (_skillNum == 2)
		{
			_tagSkill.skillCount++;
			_tagSkill.skillImage->setFrameY(0);
			_tagSkill.skillImage->setFrameX(_tagSkill.skillIndex);
			_tagSkill.skillIndex++;
			if (_tagSkill.skillIndex > _tagSkill.skillImage->getMaxFrameX())
			{
				_tagSkill.skillIndex = 0;
			}
		}
		if (_skillNum == 4)
		{

			_vSkill.at(0).skillCount++;
			if (_vSkill.at(0).skillCount % 2 == 0) m_camera->setCameraX(m_camera->getCameraX() + 10);
			if (_vSkill.at(0).skillCount % 2 == 1) m_camera->setCameraX(m_camera->getCameraX() - 10);

			_vSkill.at(0).skillImage->setFrameY(0);
			if (_vSkill.at(0).skillCount % 3 == 0)
			{
				_vSkill.at(0).skillImage->setFrameX(_vSkill.at(0).skillIndex);
				_vSkill.at(0).skillIndex++;
			}
			if (_vSkill.at(0).skillIndex > _vSkill.at(0).skillImage->getMaxFrameX())
			{
				_vSkill.at(0).skillIndex = 0;
			}
			if (_vSkill.at(0).skillCount > 50)
			{
				_vSkill.at(0).skillIndex = 0;
				_vSkill.at(0).skillCount = 0;
				_isSkillActive = false;
				_vSkill.clear();
			}

			for (int i = 1; i < _vSkill.size(); i++)
			{
				_vSkill.at(i).skillCount++;
				_vSkill.at(i).skillImage->setFrameY(0);
				if (_vSkill.at(i).skillCount % 3 == 0)
				{
					_vSkill.at(i).skillImage->setFrameX(_vSkill.at(0).skillIndex);
					_vSkill.at(i).skillIndex++;
					if (_vSkill.at(i).skillIndex > _vSkill.at(0).skillImage->getMaxFrameX())
					{
						_vSkill.at(i).skillIndex = 0;
					}
				}
			}
		}
		if (_skillNum == 5)
		{
			_vSkill.at(0).skillCount++;
			_vSkill.at(0).skillImage->setFrameY(0);
			if (_vSkill.at(0).skillCount % 3 == 0)
			{
				_vSkill.at(0).skillIndex++;
				_vSkill.at(0).skillImage->setFrameX(_vSkill.at(0).skillIndex);
				if (_vSkill.at(0).skillIndex > _vSkill.at(0).skillImage->getMaxFrameX())
				{
					_vSkill.at(0).skillIndex = 0; 
				}
			}
			if (_vSkill.at(0).skillCount % 5 == 0)
			{
				_castingCircleFrameX++;
				_castingCircle->setFrameX(_castingCircleFrameX);
				if (_castingCircleFrameX > _castingCircle->getMaxFrameX()) _castingCircleFrameX = 23;
			}
		}
		if (_skillNum == 6)
		{
			if (!_isStartShark)
			{
				_vSkill.at(0).skillCount++;
				_vSkill.at(0).skillImage->setFrameY(0);
				_vSkill.at(0).skillImage->setFrameX(_vSkill.at(0).skillIndex);
				_vSkill.at(0).skillIndex++;
				if (_vSkill.at(0).skillIndex > _vSkill.at(0).skillImage->getMaxFrameX())
				{
					_vSkill.at(0).skillIndex = 0;
				}
			}
			else
			{
				_vSkill.at(1).skillCount++;
				_vSkill.at(1).skillImage->setFrameY(0);
				if (_vSkill.at(1).skillCount % 8 == 0)
				{
					_vSkill.at(1).skillImage->setFrameX(_vSkill.at(1).skillIndex);
					_vSkill.at(1).skillIndex++;
					if (_vSkill.at(1).skillIndex > _vSkill.at(1).skillImage->getMaxFrameX())
					{
						_vSkill.at(1).skillIndex = 8;
					}
				}
				if (_vSkill.at(1).skillIndex == 8)
				{
					_vSkill.at(3).skillCount++;
					_vSkill.at(3).skillImage->setFrameY(0);
					if (_vSkill.at(3).skillCount % 5 == 0)
					{
						_vSkill.at(3).skillImage->setFrameX(_vSkill.at(3).skillIndex);
						_vSkill.at(3).skillIndex++;
						if (_vSkill.at(3).skillIndex > _vSkill.at(3).skillImage->getMaxFrameX())
						{
							_vSkill.at(3).skillIndex = 0;
						}
					}
					_vSkill.at(2).skillCount++;
					_vSkill.at(2).skillImage->setFrameY(0);
					if (_vSkill.at(2).skillCount % 5 == 0)
					{
						_vSkill.at(2).skillImage->setFrameX(_vSkill.at(2).skillIndex);
						_vSkill.at(2).skillIndex++;
						if (_vSkill.at(2).skillIndex > _vSkill.at(2).skillImage->getMaxFrameX())
						{
							_isSkillActive = false;
							_isStartShark = false;
							_vSkill.clear();
						}
					}
				} 
			}
		}
		if (_skillNum == 7)
		{
			_vSkill.at(0).skillCount++;
			_vSkill.at(0).skillImage->setFrameY(0);
			if (_vSkill.at(0).skillCount % 5 == 0)
			{
				_vSkill.at(0).skillImage->setFrameX(_vSkill.at(0).skillIndex);
				_vSkill.at(0).skillIndex++;
				if (_vSkill.at(0).skillIndex > _vSkill.at(0).skillImage->getMaxFrameX())
				{
					//_vSkill.at(0).skillIndex = 0;
					_isSkillActive = false;
					_isStartShark = false;
					_vSkill.clear();
				}
			}
		}
	}
	if (_isExplosion)
	{
		_explosionCount++;

		if (_explosionCount % 2 == 0) m_camera->setCameraX(m_camera->getCameraX() + 10);
		if (_explosionCount % 2 == 1) m_camera->setCameraX(m_camera->getCameraX() - 10);
		if (_explosionCount % 5 == 0)
		{
			_explosionFrameX++;
			if (_explosionFrameX > _explosion->getMaxFrameX())
			{
				_explosionCount = 0;
				_explosionFrameX = 0;
				_explosion->setX(0);
				_explosion->setY(0);
				_isExplosion = false;
				_vSkill.clear();
			}
		}
	}
}

void playerSkill::playerSkillAnimadtion()
{
	if (_isPlayerSkillActive)
	{
		if (_motionNum == 1)
		{
			// 아래 모션
			if (_skillAngle < -0.7 && _skillAngle > -2.5)
			{
				_playerAnimationCount++;
				m_player->getPlayerImage()->setFrameY(6);
				if (_playerAnimationCount % 2 == 0)
				{
					_playerAnimationIndex++;
					m_player->getPlayerImage()->setFrameX(_playerAnimationIndex);
					if (_playerAnimationIndex > 7)
					{
						_playerAnimationCount = 0;
						_playerAnimationIndex = 0;
						m_player->getPlayerImage()->setFrameY(0);
						m_player->getPlayerImage()->setFrameX(0);
						_isPlayerSkillActive = false;
					}
				}
			}
			// 위 모션
			if (_skillAngle > 0.7 && _skillAngle < 2.5)
			{
				_playerAnimationCount++;
				m_player->getPlayerImage()->setFrameY(14);
				if (_playerAnimationCount % 2 == 0)
				{
					_playerAnimationIndex++;
					m_player->getPlayerImage()->setFrameX(_playerAnimationIndex);
					if (_playerAnimationIndex > 9)
					{
						_playerAnimationCount = 0;
						_playerAnimationIndex = 0;
						m_player->getPlayerImage()->setFrameY(0);
						m_player->getPlayerImage()->setFrameX(1);
						_isPlayerSkillActive = false;
					}
				}
			}
			// 왼쪽 모션
			if (_skillAngle > -0.7 && _skillAngle < 0.7)
			{
				_playerAnimationCount++;
				m_player->getPlayerImage()->setFrameY(12);
				if (_playerAnimationCount % 2 == 0)
				{
					_playerAnimationIndex++;
					m_player->getPlayerImage()->setFrameX(_playerAnimationIndex);
					if (_playerAnimationIndex > 7)
					{
						_playerAnimationCount = 0;
						_playerAnimationIndex = 0;
						m_player->getPlayerImage()->setFrameY(0);
						m_player->getPlayerImage()->setFrameX(2);
						_isPlayerSkillActive = false;
					}
				}
			}
			// 오른쪽 모션
			if (_skillAngle > 2.4 || _skillAngle < -2.5)
			{
				_playerAnimationCount++;
				m_player->getPlayerImage()->setFrameY(13);
				if (_playerAnimationCount % 2 == 0)
				{
					_playerAnimationIndex++;
					m_player->getPlayerImage()->setFrameX(7 - _playerAnimationIndex);
					if (_playerAnimationIndex > 7)
					{
						_playerAnimationCount = 0;
						_playerAnimationIndex = 0;
						m_player->getPlayerImage()->setFrameY(0);
						m_player->getPlayerImage()->setFrameX(3);
						_isPlayerSkillActive = false;
					}
				}
			}
		}

		if (_motionNum == 2)
		{
			_playerAnimationCount++;
			m_player->getPlayerImage()->setFrameY(10);
			if (_playerAnimationCount % 2 == 0)
			{
				_playerAnimationIndex++;
				m_player->getPlayerImage()->setFrameX(_playerAnimationIndex);
				if (_playerAnimationIndex > m_player->getPlayerImage()->getMaxFrameX() -2 )
				{
					_playerAnimationIndex = 1;
				}
			}
			if (_playerAnimationCount > 50)
			{
				_playerAnimationCount = 0;
				_playerAnimationIndex = 0;
				m_player->getPlayerImage()->setFrameY(0);
				m_player->getPlayerImage()->setFrameX(0);
				_isPlayerSkillActive = false;
			}
		}
	}
}

// 스킬 숫자 , 모션 숫자 
void playerSkill::skillSetting(int skillNum,int motionNum)
{
	_skillNum = skillNum;
	_motionNum = motionNum;

	// 물스킬 사용
	if (_skillNum == 1)
	{
		_tagSkill.skillImage = IMAGEMANAGER->findImage("waterSkill");
		//스킬 각도
		_skillAngle = getAngle(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 + m_camera->getCameraX(),
			m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 + m_camera->getCameraY()
			, m_ptMouse.x, m_ptMouse.y);

		_tagSkill.skillImage->setX((cosf(_skillAngle) * 120 + m_player->getPlayerImage()->getX() + 20 ) );
		_tagSkill.skillImage->setY((-sinf(_skillAngle) * 150 + m_player->getPlayerImage()->getY() + 40 ) );
		 
		_tagSkill.skillRc = RectMake(_tagSkill.skillImage->getX() , _tagSkill.skillImage->getY() ,
			_tagSkill.skillImage->getFrameWidth(), _tagSkill.skillImage->getFrameHeight()); 
		_vSkill.push_back(_tagSkill);
	}

	// 바람스킬 사용
	if (_skillNum == 2)
	{ 
		_tagSkill.skillImage = IMAGEMANAGER->findImage("windSkill");
		_skillAngle = getAngle(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 + m_camera->getCameraX(),
			m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 + m_camera->getCameraY()
			, m_ptMouse.x, m_ptMouse.y);

		_tagSkill.skillImage->setX((cosf(_skillAngle) * 60 + m_player->getPlayerImage()->getX()+50 ));
		_tagSkill.skillImage->setY((-sinf(_skillAngle) * 60 + m_player->getPlayerImage()->getY()+50 ));

		_tagSkill.skillRc = RectMake(_tagSkill.skillImage->getX(), _tagSkill.skillImage->getY(),
			_tagSkill.skillImage->getFrameWidth(), _tagSkill.skillImage->getFrameHeight());
		_vSkill.push_back(_tagSkill);
	}
	// 얼음스킬 사용
	if (_skillNum == 3)
	{  
		for (int i = 0; i < 3; i++)
		{
			_tagSkill.skillIndex = 0;
			_tagSkill.skillCount = 0;
			_tagSkill.skillImage = IMAGEMANAGER->findImage("iceSkill"); 
			_tagSkill.skillImage->setX((cosf(_skillAngle) * 120 + m_player->getPlayerImage()->getX()));
			_tagSkill.skillImage->setY((-sinf(_skillAngle) * 120 + m_player->getPlayerImage()->getY())); 

			_vSkill.push_back(_tagSkill);
		}
	}
	// 번개 스킬
	if (_skillNum == 4)
	{  
		_tagSkill.skillImage = IMAGEMANAGER->findImage("thunderSkill");
		_tagSkill.skillImage->setX( m_player->getPlayerImage()->getX() - m_player->getPlayerImage()->getFrameWidth() * 1.45);
		_tagSkill.skillImage->setY( m_player->getPlayerImage()->getY() - m_player->getPlayerImage()->getFrameHeight() / 2 * 1.85);

		_tagSkill.skillRc = RectMake(_tagSkill.skillImage->getX(), _tagSkill.skillImage->getY(),
			_tagSkill.skillImage->getFrameWidth(), _tagSkill.skillImage->getFrameHeight());

		_vSkill.push_back(_tagSkill);  
		for (int i = 0; i < 5; i++)
		{ 
			_tagSkill.skillImage = IMAGEMANAGER->findImage("thunderChain");
			_tagSkill.skillImage->setX(0);
			_tagSkill.skillImage->setY(0);

			_tagSkill.skillRc = RectMake(_tagSkill.skillImage->getX() + m_camera->getCameraX(),
				_tagSkill.skillImage->getY() + m_camera->getCameraY(),
				_tagSkill.skillImage->getFrameWidth(), _tagSkill.skillImage->getFrameHeight());

			_vSkill.push_back(_tagSkill);
		}
	}  

	// 메테오
	if (_skillNum == 5)
	{
		_tagSkill.skillIndex = 0;
		_tagSkill.skillCount = 0;
		_tagSkill.skillImage = IMAGEMANAGER->findImage("meteor");
		_tagSkill.skillImage->setX(m_player->getPlayerImage()->getX() - m_player->getPlayerImage()->getFrameWidth()- 30 );
		_tagSkill.skillImage->setY(m_player->getPlayerImage()->getY() - 1450);

		_vSkill.push_back(_tagSkill);

		_castingCircle->setX(m_player->getPlayerImage()->getX());
		_castingCircle->setY(m_player->getPlayerImage()->getY()+60);
	}

	// 피즈
	if (_skillNum == 6)
	{
		_skillAngle = getAngle(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 + m_camera->getCameraX(),
			m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 + m_camera->getCameraY()
			, m_ptMouse.x, m_ptMouse.y);

		// 아이스볼
		_tagSkill.skillImage = IMAGEMANAGER->findImage("IceBall");
		_tagSkill.skillImage->setX((cosf(_skillAngle) * 60 + m_player->getPlayerImage()->getX() + 50));
		_tagSkill.skillImage->setY((-sinf(_skillAngle) * 60 + m_player->getPlayerImage()->getY() + 50));

		_vSkill.push_back(_tagSkill); 
	}
	// 블랙홀
	if (_skillNum == 7)
	{
		_tagSkill.skillImage = IMAGEMANAGER->findImage("blackHole");
		//스킬 각도
		_skillAngle = getAngle(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2 + m_camera->getCameraX(),
			m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2 + m_camera->getCameraY()
			, m_ptMouse.x, m_ptMouse.y);

		_tagSkill.skillImage->setX(m_ptMouse.x - _tagSkill.skillImage->getFrameWidth()/2 - m_camera->getCameraX() );
		_tagSkill.skillImage->setY(m_ptMouse.y - _tagSkill.skillImage->getFrameHeight()/2 - m_camera->getCameraY());

		_tagSkill.skillRc = RectMake(_tagSkill.skillImage->getX(), _tagSkill.skillImage->getY(),
			_tagSkill.skillImage->getFrameWidth(), _tagSkill.skillImage->getFrameHeight());

		_vSkill.push_back(_tagSkill);
	}
}

void playerSkill::skillMove()
{
	if (_isSkillActive)
	{
		if (_skillNum == 2)
		{
			_tagSkill.moveCount++;
			if (_tagSkill.moveCount < 20)
			{
				_tagSkill.skillImage->setX(_tagSkill.skillImage->getX() + cosf(_skillAngle) * 15);
				_tagSkill.skillImage->setY(_tagSkill.skillImage->getY() + -sinf(_skillAngle) * 15);
				_vSkill.at(0).skillRc = RectMake(_vSkill.at(0).skillImage->getX(), _vSkill.at(0).skillImage->getY(),
					_vSkill.at(0).skillImage->getFrameWidth(), _vSkill.at(0).skillImage->getFrameHeight());
			}
			else if (_tagSkill.moveCount > 20)
			{
				_skillAngle = getAngle(m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2,
					m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2,
					_tagSkill.skillImage->getX() + _tagSkill.skillImage->getFrameWidth()/2,
					_tagSkill.skillImage->getY() + _tagSkill.skillImage->getFrameHeight()/2);

				_tagSkill.skillImage->setX(_tagSkill.skillImage->getX() - cosf(_skillAngle) * 15);
				_tagSkill.skillImage->setY(_tagSkill.skillImage->getY() - -sinf(_skillAngle) * 15);

				RECT rc;
				RECT _tempSkillRc;
				_tempSkillRc = RectMake(_vSkill.at(0).skillImage->getX() + m_camera->getCameraX(), _vSkill.at(0).skillImage->getY() + m_camera->getCameraY(),
					_vSkill.at(0).skillImage->getFrameWidth(), _vSkill.at(0).skillImage->getFrameHeight());
				//if (IntersectRect(&rc,&m_player->getPlayerRc(),&_vSkill.at(0).skillRc))

				_vSkill.at(0).skillRc = RectMake(_vSkill.at(0).skillImage->getX(), _vSkill.at(0).skillImage->getY(),
					_vSkill.at(0).skillImage->getFrameWidth(), _vSkill.at(0).skillImage->getFrameHeight());
				if (IntersectRect(&rc,&m_player->getPlayerRc(),&_tempSkillRc))
				{
					_tagSkill.moveCount = 0;
					_tagSkill.skillCount = 0;
					_isSkillActive = false;
					_vSkill.clear();
				}
			} 
		} 
		// 메테오
		if (_skillNum == 5)
		{
			_tagSkill.moveCount++;
			_vSkill.at(0).skillImage->setY(_tagSkill.skillImage->getY() + 3);
			/*_vSkill.at(0).skillRc = RectMake(_vSkill.at(0).skillImage->getX(), _vSkill.at(0).skillImage->getY(),
				_vSkill.at(0).skillImage->getFrameWidth(), _vSkill.at(0).skillImage->getFrameHeight());*/
			
			// 폭발 생성
			if (_vSkill.at(0).skillImage->getY() + _vSkill.at(0).skillImage->getFrameHeight() > _castingCircle->getY() + _castingCircle->getFrameHeight() / 2 -20)
			{
				_isExplosion = true;
				_explosion->setX(_vSkill.at(0).skillImage->getX());
				_explosion->setY(_vSkill.at(0).skillImage->getY() + _vSkill.at(0).skillImage->getFrameHeight() / 2 + 100);

				_vSkill.at(0).skillRc = RectMake(_explosion->getX(), _explosion->getY(),
					_explosion->getFrameWidth(), _explosion->getFrameHeight());
			}
			// 메테오 삭제
			if (_vSkill.at(0).skillImage->getY() + _vSkill.at(0).skillImage->getFrameHeight() > _castingCircle->getY() + _castingCircle->getFrameHeight()/2)
			{
				_tagSkill.moveCount = 0;
				_castingCircleFrameX = 0;
				_isSkillActive = false;
			} 
		}
		// 얼음 날리기
		if (_skillNum == 6)
		{
			if (!_isStartShark)
			{
				_vSkill.at(0).moveCount++;
				_vSkill.at(0).skillImage->setX(_vSkill.at(0).skillImage->getX() + cosf(_skillAngle) * 5);
				_vSkill.at(0).skillImage->setY(_vSkill.at(0).skillImage->getY() + -sinf(_skillAngle) * 5);
				_vSkill.at(0).skillRc = RectMake(_vSkill.at(0).skillImage->getX(), _vSkill.at(0).skillImage->getY(),
					_vSkill.at(0).skillImage->getFrameWidth(), _vSkill.at(0).skillImage->getFrameHeight());
				if (_vSkill.at(0).moveCount > 50 )
				{ 
					_sharkTargetPt = PointMake(_vSkill.at(0).skillImage->getX(), _vSkill.at(0).skillImage->getY());
					sharkSetting();
				}
			} 
		}

	}
}

void playerSkill::sharkSetting()
{ 
	_vSkill.at(0).skillRc = RectMake(0,0,0,0);
	_isStartShark = true;
	// 웅덩이
	_tagSkill.skillIndex = 0;
	_tagSkill.skillCount = 0;
	_tagSkill.skillImage = IMAGEMANAGER->findImage("sharkPool");
	_tagSkill.skillImage->setX(_vSkill.at(0).skillImage->getX() + _vSkill.at(0).skillImage->getFrameWidth() / 2 - _tagSkill.skillImage->getFrameWidth() / 2);
	_tagSkill.skillImage->setY(_vSkill.at(0).skillImage->getY() + _vSkill.at(0).skillImage->getFrameHeight() / 2 - _tagSkill.skillImage->getFrameHeight() / 2);


	_vSkill.push_back(_tagSkill);

	// 상어
	_tagSkill.skillIndex = 0;
	_tagSkill.skillCount = 0;
	_tagSkill.skillImage = IMAGEMANAGER->findImage("shark");
	_tagSkill.skillImage->setX(_vSkill.at(0).skillImage->getX() + _vSkill.at(0).skillImage->getFrameWidth() / 2 - _tagSkill.skillImage->getFrameWidth() / 2);
	_tagSkill.skillImage->setY(_vSkill.at(0).skillImage->getY() + _vSkill.at(0).skillImage->getFrameHeight() / 2 - _tagSkill.skillImage->getFrameHeight() / 2 - 20);

	_vSkill.push_back(_tagSkill);

	// 배경
	_tagSkill.skillIndex = 0;
	_tagSkill.skillCount = 0;
	_tagSkill.skillImage = IMAGEMANAGER->findImage("WaterBombExplosion");
	_tagSkill.skillImage->setX(_vSkill.at(0).skillImage->getX() + _vSkill.at(0).skillImage->getFrameWidth() / 2 - _tagSkill.skillImage->getFrameWidth() / 2);
	_tagSkill.skillImage->setY(_vSkill.at(0).skillImage->getY() + _vSkill.at(0).skillImage->getFrameHeight() / 2 - _tagSkill.skillImage->getFrameHeight() / 2 - 75);

	_vSkill.push_back(_tagSkill);
}


