#pragma once
#include "gameNode.h"
#include"mapTile.h"


enum CTRL
{
	CTRL_DRAW,
	CTRL_ERASER,
	CTRL_INIT,
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_TERRAINDRAW,
	CTRL_OBJDRAW,
	CTRL_NUM1,
	CTRL_NUM2,
	CTRL_NUM3,
	CTRL_END
};


class mapTool : public gameNode
{
private:

	image* _backImage;
	image* _button;
	image* _buttonleft;
	image* _buttonright;

	int number;

	HANDLE _file1;
	HANDLE _file2;

	//�ʱ� UI ��ư
	RECT _saveButton; //����
	RECT _loadButton; //�ҷ�����
	RECT _initButton; //�ʱ�ȭ
	RECT _terrainButton; //������ư
	RECT _objectButton; //������Ʈ��ư
	RECT _eraserButton; //������ư

	//terrain RECT
	RECT _wallButton; //��
	RECT _floorButton; //�ٴ�
	RECT _dropButton;
	//object RECT
	RECT _bigBenchButton;
	RECT _smallBenchButton;
	RECT _statuesButton;
	RECT _pillarButton;
	//���� ����	
	RECT _previousRc;
	RECT _nextRc;
	//�浹 ����
	RECT _mapToolRc;
	RECT _mapRc;

	RECT _startRc;
	RECT _dragRc;
	RECT _dragButtonRc;

	int _viewTile; //�����ʿ� ���� �� Ÿ��
	int _viewTerNum; //���� �ٴ� ����
	int _viewObjNum; //���� �ٴ� ����	
	tagCurrentTile _currentTile;
	tagTile _tiles[TILEX* TILEY];
	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];
	tagOBJAttribute _OBJattribute[TILEX* TILEY];
	int _ctrlSelect;
	int frameX, frameY;
	bool _isSecondMenu;
	bool _isFirstMenu;
	bool _isClick;
	DWORD _attribute[TILEX* TILEY];
	DWORD write;
	DWORD read;
	int _pos[2];

	int _moveNum;

	bool _isDrag;

	int x;
	int y;
	int x1;
	int y1;
public:
	mapTool();
	~mapTool();
	HRESULT init();
	void release();
	void update();
	void render();

	void maptoolSetup();  //�ʱ� �� ����
	void setMap();  //�� ���� �� ����
	void setRectMap();  //Ÿ�Ϻ� ��Ʈ ����
	void save();  //����
	void load();  //�ҷ�����

	void uisetting(); //setting��
	void hiderect(); //SECTRECT ȭ�� ������ �̵�

	void drag();

	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);
	DWORD* getAttribute() { return _attribute; }

	tagTile* getMap() { return _tiles; }

};

