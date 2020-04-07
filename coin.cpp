#include "stdafx.h"
#include "coin.h"


coin::coin()
{
}


coin::~coin()
{
}

HRESULT coin::init()
{
	return S_OK;
}

HRESULT coin::init(const char* imageName, POINT position)
{
	_coin = new coin;
	_coinImage = IMAGEMANAGER->findImage("ÄÚÀÎ");

	_coinRc = RectMake(position.x, position.y , _coinImage->getFrameWidth(), _coinImage->getFrameHeight());
	_price = 10;

	_x = _coinRc.left;
	_y = _coinRc.top;




	return S_OK;
}

void coin::release()
{

}

void coin::update()
{

	move();
	animation();
}

void coin::render()
{
	_coinImage->frameRender(getMemDC(), _coinRc.left + m_camera->getCameraX(), _coinRc.top + m_camera->getCameraY(), _currentFrameX, _currentFrameY);
 }

void coin::animation()
{
	_currentFrameY = 0;
	_count++;
	if (_count % 5 == 0)
	{
		_coinImage->setFrameX(0);
		_currentFrameX++;
		if (_currentFrameX > 2)
		{
			_currentFrameX = 0;
		}
	}
}

void coin::move()
{ 
	_coinRc.left += cosf(getAngle(_coinRc.left + (_coinRc.right - _coinRc.left) / 2, _coinRc.top + (_coinRc.bottom - _coinRc.top) / 2,
		m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2, m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2)) * 4;
	_coinRc.right += cosf(getAngle(_coinRc.left + (_coinRc.right - _coinRc.left) / 2, _coinRc.top + (_coinRc.bottom - _coinRc.top) / 2,
		m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2, m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2)) * 4;
	_coinRc.top += -sinf(getAngle(_coinRc.left + (_coinRc.right - _coinRc.left) / 2, _coinRc.top + (_coinRc.bottom - _coinRc.top) / 2,
		m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2, m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2)) * 4;
	_coinRc.bottom += -sinf(getAngle(_coinRc.left + (_coinRc.right - _coinRc.left) / 2, _coinRc.top + (_coinRc.bottom - _coinRc.top) / 2,
		m_player->getPlayerImage()->getX() + m_player->getPlayerImage()->getFrameWidth() / 2, m_player->getPlayerImage()->getY() + m_player->getPlayerImage()->getFrameHeight() / 2)) * 4;

 	_collisionRc = RectMake(_coinRc.left + m_camera->getCameraX(), _coinRc.top + m_camera->getCameraY(), _coinImage->getFrameWidth(), _coinImage->getFrameHeight());
}
