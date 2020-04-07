#include "stdafx.h"
#include "testMapTool.h"


testMapTool::testMapTool()
{
}


testMapTool::~testMapTool()
{
}

HRESULT testMapTool::init()
{
	//맵로드
	load();
	IMAGEMANAGER->addFrameImage("tilemap", "images/맵툴/불맵타일.bmp", 768, 320, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("objectmap", "images/맵툴/오브젝트.bmp", 768, 320, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	return S_OK;

}

void testMapTool::release()
{
}

void testMapTool::update()
{
}

void testMapTool::tileRender()
{
	for (int i = 0; i < TILEX * TILEY; i++) {             //초기 타일 렌더
		if (_tiles[i].terrain == TR_NULL)
		{
			//Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
		}
		else IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);  //타일 관련 이미지 렌더링
	}
}

void testMapTool::objRender()
{
	for (int i = 0; i < TILEX * TILEY; i++)              //초기 오브젝트 랜더
	{
		if (_tiles[i].obj == OBJ_NONE)continue;
		//Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
		IMAGEMANAGER->frameRender("objectmap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);    //오브젝트 관련 이미지 렌더링
	}
}


void testMapTool::load()
{
	_file1 = CreateFile("map.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(_file1, _tiles, sizeof(tagTile)*(TILEY*TILEX), &_read, NULL);

	memset(_attribute, 0, sizeof(DWORD)*TILEX*TILEY);
	for (int i = 0; i < TILEX*TILEY; i++)
	{
		if (_tiles[i].terrain == TR_NULL) {
			_attribute[i] |= ATTR_UNMOVABLE;
		}

		if (_tiles[i].terrain == TR_WALL)  //벽
		{
			_attribute[i] |= ATTR_UNMOVABLE;
		}
		if (_tiles[i].terrain == TR_DROP) {   //낙사 지점(속성 추가)
			_attribute[i] |= ATTR_UNMOVABLE;
		}
		if (_tiles[i].obj == OBJ_BIGBENCH) {  //큰벤치
			_attribute[i] |= ATTR_UNMOVABLE;
		}
		if (_tiles[i].obj == OBJ_SMALLBENCH) {  //작은 벤치
			_attribute[i] |= ATTR_UNMOVABLE;
		}
		if (_tiles[i].obj == OBJ_PILLARBLOCK) { //기둥 하단 부분 
			_attribute[i] |= ATTR_UNMOVABLE;
		}
		if (_tiles[i].obj == OBJ_STATUEBLOCK) { //조각상 하단부분
			_attribute[i] |= ATTR_UNMOVABLE;
		}
	}
}
