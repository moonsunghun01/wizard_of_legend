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
	//�ʷε�
	load();
	IMAGEMANAGER->addFrameImage("tilemap", "images/����/�Ҹ�Ÿ��.bmp", 768, 320, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("objectmap", "images/����/������Ʈ.bmp", 768, 320, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
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
	for (int i = 0; i < TILEX * TILEY; i++) {             //�ʱ� Ÿ�� ����
		if (_tiles[i].terrain == TR_NULL)
		{
			//Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
		}
		else IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);  //Ÿ�� ���� �̹��� ������
	}
}

void testMapTool::objRender()
{
	for (int i = 0; i < TILEX * TILEY; i++)              //�ʱ� ������Ʈ ����
	{
		if (_tiles[i].obj == OBJ_NONE)continue;
		//Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
		IMAGEMANAGER->frameRender("objectmap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);    //������Ʈ ���� �̹��� ������
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

		if (_tiles[i].terrain == TR_WALL)  //��
		{
			_attribute[i] |= ATTR_UNMOVABLE;
		}
		if (_tiles[i].terrain == TR_DROP) {   //���� ����(�Ӽ� �߰�)
			_attribute[i] |= ATTR_UNMOVABLE;
		}
		if (_tiles[i].obj == OBJ_BIGBENCH) {  //ū��ġ
			_attribute[i] |= ATTR_UNMOVABLE;
		}
		if (_tiles[i].obj == OBJ_SMALLBENCH) {  //���� ��ġ
			_attribute[i] |= ATTR_UNMOVABLE;
		}
		if (_tiles[i].obj == OBJ_PILLARBLOCK) { //��� �ϴ� �κ� 
			_attribute[i] |= ATTR_UNMOVABLE;
		}
		if (_tiles[i].obj == OBJ_STATUEBLOCK) { //������ �ϴܺκ�
			_attribute[i] |= ATTR_UNMOVABLE;
		}
	}
}
