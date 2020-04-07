#include "stdafx.h"
#include "playerTeleport.h"

HRESULT playerTeleport::init()
{

	_teleportPad = IMAGEMANAGER->addImage("teleportPad", "images/teleportPad.bmp", 96 * 3, 96 * 3, true, RGB(255, 0, 255));
	//_teleportEffect = IMAGEMANAGER->addFrameImage("teleportEffect", "images/teleportEffect.bmp", 384 *2, 512,4,1, true, RGB(255, 0, 255));
	_teleportEffect = IMAGEMANAGER->addFrameImage("teleportEffect", "images/teleportEffect2.bmp", 768 *2.5 , 512, 8,1, true, RGB(255, 0, 255));
	_isTeleport = false;
	_isChangePosition = false;
	_teleportEffectIndex = 0;

	//_teleportPad->setX(3540 + m_camera->getCameraX());
	//_teleportPad->setY(5155 + m_camera->getCameraY());
	return S_OK;
}

void playerTeleport::release()
{
}

void playerTeleport::update()
{
	_teleportPad->setX(3460 + m_camera->getCameraX());
	_teleportPad->setY(5155 + m_camera->getCameraY());
	_teleportPadRc = RectMake(_teleportPad->getX(), _teleportPad->getY(), _teleportPad->getWidth(), _teleportPad->getHeight());
	if (_isTeleport)
		teleportActive();
}

void playerTeleport::render()
{
	_teleportPad->render(getMemDC(), _teleportPad->getX(), _teleportPad->getY());
	//Rectangle(getMemDC(), _teleportPadRc.left, _teleportPadRc.top, _teleportPadRc.right, _teleportPadRc.bottom);

	if(_isTeleport && !_isChangePosition)_teleportEffect->frameRender(getMemDC(), _teleportPad->getX() +25 , _teleportPad->getY() - 300);
	if (_isTeleport && _isChangePosition)
	{
		//SCENEMANAGER->changeScene("bossMap");
		/*_teleportEffect->frameRender(getMemDC(),
			m_player->getPlayerImage()->getX() + m_camera->getCameraX()-55,
			m_player->getPlayerImage()->getY() + m_camera->getCameraY() -300);*/
	}
}

void playerTeleport::teleportActive()
{ 
	_teleportEffect->setFrameY(0);
	_teleportEffectCount++;
	if (!_isChangePosition)
	{
		if (_teleportEffectCount % 5 == 0)
		{
			_teleportEffect->setFrameX(_teleportEffectIndex);
			_teleportEffectIndex++;

			if (_teleportEffectIndex > _teleportEffect->getMaxFrameX())
			{
				_teleportEffectIndex = 0;
				_teleportEffectCount = 0;
				_teleportEffect->setFrameX(0);

				m_player->getPlayerImage()->setX(4970);
				m_player->getPlayerImage()->setY(660);

				m_camera->setCameraX(-4521);
				m_camera->setCameraY(-350);
				_isChangePosition = true;
			}
		}
	}
	else
	{
		if (_teleportEffectCount % 5 == 0)
		{
			_teleportEffect->setFrameX(_teleportEffectIndex);
			_teleportEffectIndex++;

			if (_teleportEffectIndex > _teleportEffect->getMaxFrameX())
			{
				_teleportEffectIndex = 0;
				_teleportEffectCount = 0;
				_teleportEffect->setFrameX(0);
				_isChangePosition = false;
				_isTeleport = false;
			}
		}
	}


	
	
}
