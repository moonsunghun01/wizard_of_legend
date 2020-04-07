#pragma once
#include "gameNode.h"
#include "mapTool.h"


class madeTestMapTool : public gameNode
{
private:
	mapTool* _map;
	DWORD _attribute[TILEX* TILEY];
	tagTile _tiles[TILEX* TILEY];
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];
	tagOBJAttribute _OBJattribute[TILEX* TILEY];
	HANDLE _file2;
	DWORD _read;
	RECT _rc;
	int _pos[2];
public:
	madeTestMapTool();
	~madeTestMapTool();

	HRESULT init();
	void release();
	void update();
	void tileRender();
	void objRender();
	void load();
	DWORD* getAttribute() { return _attribute; }
	tagTile* getMap() { return _tiles; }
	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }
};

