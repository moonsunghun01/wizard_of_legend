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

	//초기 UI 버튼
	RECT _saveButton; //저장
	RECT _loadButton; //불러오기
	RECT _initButton; //초기화
	RECT _terrainButton; //지형버튼
	RECT _objectButton; //오브젝트버튼
	RECT _eraserButton; //지우기버튼

	//terrain RECT
	RECT _wallButton; //벽
	RECT _floorButton; //바닥
	RECT _dropButton;
	//object RECT
	RECT _bigBenchButton;
	RECT _smallBenchButton;
	RECT _statuesButton;
	RECT _pillarButton;
	//이전 다음	
	RECT _previousRc;
	RECT _nextRc;
	//충돌 관련
	RECT _mapToolRc;
	RECT _mapRc;

	RECT _startRc;
	RECT _dragRc;
	RECT _dragButtonRc;

	int _viewTile; //오른쪽에 보여 줄 타일
	int _viewTerNum; //벽과 바닥 선택
	int _viewObjNum; //벽과 바닥 선택	
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

	void maptoolSetup();  //초기 맵 설정
	void setMap();  //맵 변경 및 설정
	void setRectMap();  //타일별 렉트 설정
	void save();  //저장
	void load();  //불러오기

	void uisetting(); //setting값
	void hiderect(); //SECTRECT 화면 밖으로 이동

	void drag();

	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);
	DWORD* getAttribute() { return _attribute; }

	tagTile* getMap() { return _tiles; }

};

