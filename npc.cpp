#include "stdafx.h"
#include "npc.h"


HRESULT npc::init()
{
	_x = 5500 ; //npc x축 좌표
	_y = 5000 ; //npc y축 좌표
	_npcImage = IMAGEMANAGER->addImage("NPC", "images/상점/NPC/상점 NPC.bmp", 100, 150, true, RGB(255, 0, 255));
	_npcRc = RectMakeCenter(_x, _y, _npcImage->getWidth(), _npcImage->getHeight());
	return S_OK; 
}

void npc::render()
{
	if (KEYMANAGER->isToggleKey('T')) { // T클릭시 사각형 출현
		Rectangle(getMemDC(), _npcRc.left, _npcRc.top, _npcRc.right, _npcRc.bottom);
	}
	IMAGEMANAGER->render("NPC", getMemDC(), _npcRc.left + m_camera->getCameraX(), _npcRc.top + m_camera->getCameraY()); //NPC 출력
}