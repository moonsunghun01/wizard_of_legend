#include "stdafx.h"
#include "playerCollision.h"


playerCollision::playerCollision()
{
}


playerCollision::~playerCollision()
{
}

HRESULT playerCollision::init()
{
	_map = new testMapTool; //동적 할당
	_map->init();

	_image = IMAGEMANAGER->findImage("player");

	_speed = m_player->getMoveSpeed();

	return S_OK;
}

void playerCollision::release()
{
	SAFE_DELETE(_map);
}

void playerCollision::update()
{
	if (KEYMANAGER->isStayKeyDown('A') && _rc.left > 0)
	{
		_direction = PLAYERDIRECTION_LEFT;
		playerMove();
	}
	if (KEYMANAGER->isStayKeyDown('D') && _rc.right < WINSIZEX) {
		_direction = PLAYERDIRECTION_RIGHT;
		playerMove();
	}
	if (KEYMANAGER->isStayKeyDown('W') && _rc.top > 0) {
		_direction = PLAYERDIRECTION_UP;
		playerMove();
	}
	if (KEYMANAGER->isStayKeyDown('S') && _rc.bottom < WINSIZEY) {
		_direction = PLAYERDIRECTION_DOWN;
		playerMove();
	}
}

void playerCollision::render()
{
	if (_map->getMap()->obj != OBJ_NONE) {
		_map->tileRender();
		_map->objRender();
		if (KEYMANAGER->isToggleKey(VK_TAB)) {
			Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
		}
		//_image->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, _frameY, 96, 96);
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, _frameY, 96, 96);
	}
	else {
		_map->tileRender();
		if (KEYMANAGER->isToggleKey(VK_TAB)) {
			Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
		}
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, _frameY, 96, 96);
		_map->objRender();
	}
}

void playerCollision::setPlayerPosition() //위치 지정
{
	sampleRc = RectMakeCenter(WINSIZEX / 2 + 80, WINSIZEY / 2, 96, 96);
	_rc = sampleRc;
	_x = _rc.left + (_rc.right - _rc.left) / 2;
	_y = _rc.top + (_rc.bottom - _rc.top) / 2;
}

void playerCollision::playerMove()
{
	RECT rcCollision;
	int tileIndex[8];//검사용 타일
	rcCollision = _rc;//가상의 렉트
	float elpasedTime = TIMEMANAGER->getElapsedTime();
	switch (_direction) //일단 이동
	{
	case PLAYERDIRECTION_LEFT:
		_x -= _speed;
		rcCollision = RectMakeCenter(_x, _y, 96, 96);
		_frameY = 4;
		_frameCount++;
		if (_frameCount % 5 == 0)
		{
			_frameX++;
			if (_frameX > 9) _frameX = 0;
		}
		break;
	case PLAYERDIRECTION_RIGHT:
		_x += _speed;
		rcCollision = RectMakeCenter(_x, _y, 96, 96);
		_frameY = 3;
		_frameCount++;
		if (_frameCount % 5 == 0)
		{
			_frameX++;
			if (_frameX > 9) _frameX = 0;
		}
		break;
	case PLAYERDIRECTION_UP:
		_y -= _speed;
		rcCollision = RectMakeCenter(_x, _y, 96, 96);
		_frameY = 2;
		_frameCount++;
		if (_frameCount % 5 == 0)
		{
			_frameX++;
			if (_frameX > 9) _frameX = 0;
		}
		break;
	case PLAYERDIRECTION_DOWN:
		_y += _speed;
		rcCollision = RectMakeCenter(_x, _y, 96, 96);
		_frameY = 1;
		_frameCount++;
		if (_frameCount % 5 == 0)
		{
			_frameX++;
			if (_frameX > 9) _frameX = 0;
		}
		break;
	}
	/////////////////////////////////////////////////////////////////////////
	tileX = (rcCollision.left / TILESIZE);  //타일 넘버 지정
	tileY = (rcCollision.top / TILESIZE);   //타일 넘버
	tileX1 = tileX + 1;
	tileY1 = tileY + 1;
	tileX2 = tileX1 + 1;
	tileY2 = tileY1 + 1;
	tileX3 = tileX2 + 1;
	tileY3 = tileY3 + 1;

	/////////////////////////////////////////////////////////////////////////
	switch (_direction) //타일 검사 위치 변경
	{
	case PLAYERDIRECTION_LEFT:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + (tileY + 1)* TILEX;

		tileIndex[2] = tileX + tileY1 * TILEX;
		tileIndex[3] = tileX + (tileY1 + 1)* TILEX;

		tileIndex[4] = tileX + tileY2 * TILEX;
		tileIndex[5] = tileX + (tileY2 + 1)* TILEX;

		tileIndex[6] = tileX + tileY3 * TILEX;
		tileIndex[7] = tileX + (tileY3 + 1)* TILEX;

		break;
	case PLAYERDIRECTION_UP:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + 1 + tileY * TILEX;

		tileIndex[2] = tileX1 + tileY * TILEX;
		tileIndex[3] = tileX1 + (tileY + 1)* TILEX;

		tileIndex[4] = tileX2 + tileY * TILEX;
		tileIndex[5] = tileX2 + (tileY + 1)* TILEX;

		tileIndex[6] = tileX3 + tileY * TILEX;
		tileIndex[7] = tileX3 + (tileY + 1)* TILEX;


		break;
	case PLAYERDIRECTION_RIGHT:
		tileIndex[0] = (tileX + tileY * TILEX) + 3;
		tileIndex[1] = (tileX + (tileY + 1)*TILEX) + 3;

		tileIndex[2] = (tileX + tileY1 * TILEX) + 3;
		tileIndex[3] = (tileX + (tileY1 + 1)*TILEX) + 3;

		tileIndex[4] = (tileX + tileY2 * TILEX) + 3;
		tileIndex[5] = (tileX + (tileY2 + 1)*TILEX) + 3;

		tileIndex[6] = (tileX + tileY3 * TILEX) + 3;
		tileIndex[7] = (tileX + (tileY3 + 1)*TILEX) + 3;

		break;
	case PLAYERDIRECTION_DOWN:
		tileIndex[0] = (tileX + tileY * TILEX) + 3 * TILEX;
		tileIndex[1] = (tileX + 1 + tileY * TILEX) + 3 * TILEX;

		tileIndex[2] = (tileX1 + tileY * TILEX) + 3 * TILEX;
		tileIndex[3] = (tileX1 + 1 + tileY * TILEX) + 3 * TILEX;

		tileIndex[4] = (tileX2 + tileY * TILEX) + 3 * TILEX;
		tileIndex[5] = (tileX2 + 1 + tileY * TILEX) + 3 * TILEX;

		tileIndex[6] = (tileX3 + tileY * TILEX) + 3 * TILEX;
		tileIndex[7] = (tileX3 + 1 + tileY * TILEX) + 3 * TILEX;

		break;
	}

	RECT rc;
	for (int i = 0; i < 6; i++) {    //이미지의 넓이와 높이가 타일의 렉트와 안맞는 관계로 타일의 렉트의 크기에 맞춤
		if (((_map->getAttribute()[tileIndex[i]] & ATTR_UNMOVABLE) == ATTR_UNMOVABLE) &&
			IntersectRect(&rc, &_map->getMap()[tileIndex[i]].rc, &rcCollision))
		{
			switch (_direction)
			{
			case PLAYERDIRECTION_LEFT:
				_rc.left = _map->getMap()[tileIndex[i]].rc.right;
				_rc.right = _rc.left + 96;
				_x = _rc.left + (_rc.right - _rc.left) / 2;
				break;
			case PLAYERDIRECTION_RIGHT:
				_rc.right = _map->getMap()[tileIndex[i]].rc.left;
				_rc.left = _rc.right - 96;
				_x = _rc.left + (_rc.right - _rc.left) / 2;
				break;
			case PLAYERDIRECTION_UP:
				_rc.top = _map->getMap()[tileIndex[i]].rc.bottom;
				_rc.bottom = _rc.top + 96;
				_y = _rc.top + (_rc.bottom - _rc.top) / 2;
				break;
			case PLAYERDIRECTION_DOWN:
				_rc.bottom = _map->getMap()[tileIndex[i]].rc.top;
				_rc.top = _rc.bottom - 96;
				_y = _rc.top + (_rc.bottom - _rc.top) / 2;
				break;
			}
			return;
		}
	}
	rcCollision = RectMakeCenter(_x, _y, 96, 96);
	_rc = rcCollision;
}
