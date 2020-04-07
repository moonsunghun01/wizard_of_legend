#pragma once
#include "gameNode.h"
class npc : public gameNode
{
private:
	int _x; //NPC xÃà ÁÂÇ¥
	int _y; //NPC yÃà ÁÂÇ¥
	image* _npcImage;
	RECT _npcRc;
public:
	HRESULT init();
	void render();
	int getX() { return _x; }
	int getY() { return _y; }

};

