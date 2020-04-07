#pragma once
#include "gameNode.h"
class npc : public gameNode
{
private:
	int _x; //NPC x�� ��ǥ
	int _y; //NPC y�� ��ǥ
	image* _npcImage;
	RECT _npcRc;
public:
	HRESULT init();
	void render();
	int getX() { return _x; }
	int getY() { return _y; }

};

