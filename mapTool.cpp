#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}

mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{

	IMAGEMANAGER->addFrameImage("tilemap", "images/맵툴/불맵타일.bmp", 768, 320, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("objectmap", "images/맵툴/오브젝트.bmp", 768, 320, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("select", "images/맵툴/선택.bmp", 400, WINSIZEY, true, RGB(255, 0, 255));
	_backImage = IMAGEMANAGER->addImage("UI", "images/맵툴/back.bmp", 213, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button", "images/맵툴/button.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("buttonleft", "images/맵툴/buttonleft.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("buttonright", "images/맵툴/buttonright.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("camera", WINSIZEX, WINSIZEY);
	maptoolSetup();
	_currentTile.x = 2;
	_currentTile.y = 0;
	_viewTile = 0;
	_viewTerNum = 0;
	_viewObjNum = 0;
	_isFirstMenu = true;
	number = 0;
	_mapToolRc = RectMakeCenter(WINSIZEX / 2 / 2, WINSIZEY / 2, WINSIZEX / 2 + 230, WINSIZEY);
	_mapRc = RectMakeCenter(825, WINSIZEY / 2, 400, WINSIZEY);
	_startRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 32, 32);
	_isClick = false;
	return S_OK;
}

void mapTool::release()
{
	//SAFE_DELETE(_mapCamera);	
}

void mapTool::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {  //스페이스 클릭시 처음 화면으로 복귀
		SCENEMANAGER->changeScene("firstSceen");
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) {
		for (int i = 0; i < TILEX*TILEY; i++) {
			_tiles[i].rc.left += 5;
		}
		for (int i = 0; i < TILEX*TILEY; i++) {
			_tiles[i].rc.right += 5;
		}
		_startRc.left += 5;
		_startRc.right += 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
		for (int i = 0; i < TILEX*TILEY; i++) {
			_tiles[i].rc.left -= 5;
		}
		for (int i = 0; i < TILEX*TILEY; i++) {
			_tiles[i].rc.right -= 5;
		}
		_startRc.left -= 5;
		_startRc.right -= 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		for (int i = 0; i < TILEX*TILEY; i++) {
			_tiles[i].rc.top += 5;
		}
		for (int i = 0; i < TILEX*TILEY; i++) {
			_tiles[i].rc.bottom += 5;
		}
		_startRc.top += 5;
		_startRc.bottom += 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		_moveNum += 1;
		for (int i = 0; i < TILEX*TILEY; i++) {
			_tiles[i].rc.top -= 5;
		}
		for (int i = 0; i < TILEX*TILEY; i++) {
			_tiles[i].rc.bottom -= 5;
		}
		_startRc.top -= 5;
		_startRc.bottom -= 5;
	}

	if (PtInRect(&_mapToolRc, m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
		_isClick = true;
	}
	else {
		_isClick = false;
	}

	if (_moveNum > 76) {
		_moveNum = 76;
	}

	uisetting();
	setRectMap();
	setMap();
	//drag();
}

void mapTool::render()
{
	frameX = frameY = 0;
	/////////////////////////////////////////////

	for (int i = 0; i < TILEX * TILEY; i++)              //초기 타일 공백으로 셋팅(속성값은 NULL로)  //그리는 갯수?
	{
		if (_tiles[i].terrain == TR_NULL)
		{
			Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);

			if (i == 1317) {
				FillRect(getMemDC(), &_tiles[i].rc, CreateSolidBrush(RGB(255, 0, 255)));
			}
		}
		else IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);  //타일 관련 이미지 렌더링

		if (_tiles[i].obj == OBJ_NONE)continue;

		IMAGEMANAGER->frameRender("objectmap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);    //오브젝트 관련 이미지 렌더링
	}


	FrameRect(getMemDC(), &_mapToolRc, CreateSolidBrush(RGB(0, 100, 244)));   //틀만 생성한 렉트 (충돌 처리 검사용도)

	//Rectangle(getMemDC(),_map.left,_map.top,_map.right,_map.bottom);

	Rectangle(getMemDC(), _mapRc.left, _mapRc.top, _mapRc.right, _mapRc.bottom);
	IMAGEMANAGER->render("select", getMemDC(), _mapRc.left, _mapRc.top);
	if (_isFirstMenu == true) {   //초기화면일 경우 UI 출력
		if (KEYMANAGER->isToggleKey(VK_TAB)) {
			Rectangle(getMemDC(), _loadButton.left, _loadButton.top, _loadButton.right, _loadButton.bottom);
			Rectangle(getMemDC(), _saveButton.left, _saveButton.top, _saveButton.right, _saveButton.bottom);
			Rectangle(getMemDC(), _initButton.left, _initButton.top, _initButton.right, _initButton.bottom);
			Rectangle(getMemDC(), _terrainButton.left, _terrainButton.top, _terrainButton.right, _terrainButton.bottom);
			Rectangle(getMemDC(), _objectButton.left, _objectButton.top, _objectButton.right, _objectButton.bottom);
			Rectangle(getMemDC(), _eraserButton.left, _eraserButton.top, _eraserButton.right, _eraserButton.bottom);
		}
		IMAGEMANAGER->render("UI", getMemDC(), _saveButton.left, _saveButton.top);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), 815, 110, "SAVE", 4);
		IMAGEMANAGER->render("UI", getMemDC(), _loadButton.left, _loadButton.top);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), 815, 180, "LOAD", 4);
		IMAGEMANAGER->render("UI", getMemDC(), _initButton.left, _initButton.top);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), 815, 250, "INIT", 4);
		IMAGEMANAGER->render("UI", getMemDC(), _terrainButton.left, _terrainButton.top);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), 805, 320, "TERRAIN", 7);
		IMAGEMANAGER->render("UI", getMemDC(), _objectButton.left, _objectButton.top);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), 805, 390, "OBJECT", 6);
		IMAGEMANAGER->render("UI", getMemDC(), _eraserButton.left, _eraserButton.top);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), 805, 460, "ERASER", 6);
	}
	else {  //초기화면에서 타일 선택 창일 경우 UI
		if (_viewTile == 1) { //지형 선택에 대한 종류 UI
			if (KEYMANAGER->isToggleKey(VK_TAB)) {
				Rectangle(getMemDC(), _wallButton.left, _wallButton.top, _wallButton.right, _wallButton.bottom);
				Rectangle(getMemDC(), _floorButton.left, _floorButton.top, _floorButton.right, _floorButton.bottom);
				Rectangle(getMemDC(), _dropButton.left, _dropButton.top, _dropButton.right, _dropButton.bottom);
			}
			IMAGEMANAGER->render("UI", getMemDC(), _wallButton.left, _wallButton.top);
			SetBkMode(getMemDC(), TRANSPARENT);
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			TextOut(getMemDC(), 815, 110, "WALL", 4);
			IMAGEMANAGER->render("UI", getMemDC(), _floorButton.left, _floorButton.top);
			SetBkMode(getMemDC(), TRANSPARENT);
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			TextOut(getMemDC(), 810, 250, "FLOOR", 5);
			IMAGEMANAGER->render("UI", getMemDC(), _dropButton.left, _dropButton.top);
			SetBkMode(getMemDC(), TRANSPARENT);
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			TextOut(getMemDC(), 815, 180, "DROP", 4);
		}
		if (_viewTile == 2) { //오브젝트 선택에 대한 종류 UI
			if (KEYMANAGER->isToggleKey(VK_TAB)) {
				Rectangle(getMemDC(), _bigBenchButton.left, _bigBenchButton.top, _bigBenchButton.right, _bigBenchButton.bottom);
				Rectangle(getMemDC(), _smallBenchButton.left, _smallBenchButton.top, _smallBenchButton.right, _smallBenchButton.bottom);
				Rectangle(getMemDC(), _statuesButton.left, _statuesButton.top, _statuesButton.right, _statuesButton.bottom);
				Rectangle(getMemDC(), _pillarButton.left, _pillarButton.top, _pillarButton.right, _pillarButton.bottom);
			}
			IMAGEMANAGER->render("UI", getMemDC(), _bigBenchButton.left, _bigBenchButton.top);
			SetBkMode(getMemDC(), TRANSPARENT);
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			TextOut(getMemDC(), 800, 110, "BENCH 1", 7);
			IMAGEMANAGER->render("UI", getMemDC(), _smallBenchButton.left, _smallBenchButton.top);
			SetBkMode(getMemDC(), TRANSPARENT);
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			TextOut(getMemDC(), 800, 180, "BENCH 2", 7);
			IMAGEMANAGER->render("UI", getMemDC(), _statuesButton.left, _statuesButton.top);
			SetBkMode(getMemDC(), TRANSPARENT);
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			TextOut(getMemDC(), 800, 250, "STATUES", 7);
			IMAGEMANAGER->render("UI", getMemDC(), _pillarButton.left, _pillarButton.top);
			SetBkMode(getMemDC(), TRANSPARENT);
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			TextOut(getMemDC(), 805, 320, "PILLAR", 6);
		}
	}
	if (_viewTile == 1) {
		if (_viewTerNum == 1) { //바닥 타일 출력 및 버튼 UI 출력
			if (KEYMANAGER->isToggleKey(VK_TAB)) {
				Rectangle(getMemDC(), _nextRc.left, _nextRc.top, _nextRc.right, _nextRc.bottom);
				if (number > 0) {
					Rectangle(getMemDC(), _previousRc.left, _previousRc.top, _previousRc.right, _previousRc.bottom);
				}
			}
			IMAGEMANAGER->render("button", getMemDC(), _nextRc.left, _nextRc.top);
			IMAGEMANAGER->render("buttonright", getMemDC(), _nextRc.left + 10, _nextRc.top + 10);
			if (number > 0) {
				IMAGEMANAGER->render("button", getMemDC(), _previousRc.left, _previousRc.top);
				IMAGEMANAGER->render("buttonleft", getMemDC(), _previousRc.left + 5, _previousRc.top + 10);
			}
			if (number == 0) {  //바닥 관련 처음 이미지 범위지정 출력
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 8; j++) {
						IMAGEMANAGER->frameRender("tilemap", getMemDC(), 650 + (j * 45), 300 + (i * 45), frameX, frameY);
						frameX++;
						if (frameX > 7) { //화면에 출력 대는 이미지 숫자 7개 지정
							frameX = 0;
							frameY++;
						}
					}
				}
			}
			else if (number == 1) {   //바닥 관련 두번째 이미지 범위지정 출력
				frameX = 7;  //x축의 프레임 범위 다르게 지정
				frameY = 0;
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 8; j++) {
						IMAGEMANAGER->frameRender("tilemap", getMemDC(), 650 + (j * 45), 300 + (i * 45), frameX, frameY);
						frameX++;
						if (frameX > 14) { //화면에 출력 대는 이미지 숫자 7개 지정
							frameX = 7;
							frameY++;
						}
					}
				}
			}
			else if (number == 2) {	//바닥 관련 세번째 이미지 범위지정 출력
				frameX = 14;		 //x축의 프레임 범위 다르게 지정
				frameY = 0;
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 8; j++) {
						IMAGEMANAGER->frameRender("tilemap", getMemDC(), 650 + (j * 45), 300 + (i * 45), frameX, frameY);
						frameX++;
						if (frameX > 21) { //화면에 출력 대는 이미지 숫자 7개 지정
							frameX = 14;
							frameY++;
						}
					}
				}
			}
			else if (number == 3) {    //바닥 관련 네번째 이미지 범위지정 출력
				frameX = 21;		    //x축의 프레임 범위 다르게 지정
				frameY = 0;
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						IMAGEMANAGER->frameRender("tilemap", getMemDC(), 650 + (j * 45), 300 + (i * 45), frameX, frameY);
						frameX++;
						if (frameX > 24) { //화면에 출력 대는 이미지 숫자 7개 지정
							frameX = 21;
							frameY++;
						}
					}
				}
			}
		}
		else if (_viewTerNum == 2) { //벽 타일 선택시
			if (KEYMANAGER->isToggleKey(VK_TAB)) { //버튼 UI 출력
				Rectangle(getMemDC(), _nextRc.left, _nextRc.top, _nextRc.right, _nextRc.bottom);
				if (number > 0) {
					Rectangle(getMemDC(), _previousRc.left, _previousRc.top, _previousRc.right, _previousRc.bottom);
				}
			}
			IMAGEMANAGER->render("button", getMemDC(), _nextRc.left, _nextRc.top);
			IMAGEMANAGER->render("buttonright", getMemDC(), _nextRc.left + 10, _nextRc.top + 10);
			if (number > 0) {
				IMAGEMANAGER->render("button", getMemDC(), _previousRc.left, _previousRc.top);
				IMAGEMANAGER->render("buttonleft", getMemDC(), _previousRc.left + 5, _previousRc.top + 10);
			}
			if (number == 0) {	//벽의 처음 조건 추가
				frameY = 6;		//프레임 Y 축이 다른 경우 변경
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 8; j++) {
						IMAGEMANAGER->frameRender("tilemap", getMemDC(), 650 + (j * 45), 300 + (i * 45), frameX, frameY);
						frameX++;
						if (frameX > 7) {	//화면에 출력 대는 이미지 숫자 7개 지정
							frameX = 0;
							frameY++;
						}
						if (frameY > 7 && frameX == 2) {
							i = 3;
							j = 8;
						}
					}
				}
			}
			else if (number == 1) { //벽의 처음 조건 추가
				frameY = 6;			//프레임 Y 축이 다른 경우 변경
				frameX = 7;			//프레임 X축이 다른 경우 변경
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 8; j++) {
						IMAGEMANAGER->frameRender("tilemap", getMemDC(), 650 + (j * 45), 300 + (i * 45), frameX, frameY);
						frameX++;
						if (frameX > 14) {	//화면에 출력 대는 이미지 숫자 7개 지정
							frameX = 7;
							frameY++;
						}
					}
				}
			}
			else if (number == 2) { //벽의 처음 조건 추가
				frameY = 6;		   //프레임 Y 축이 다른 경우 변경
				frameX = 14;	   //프레임 X축이 다른 경우 변경
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 8; j++) {
						IMAGEMANAGER->frameRender("tilemap", getMemDC(), 650 + (j * 45), 300 + (i * 45), frameX, frameY);
						frameX++;
						if (frameX > 21) { //화면에 출력 대는 이미지 숫자 7개 지정
							frameX = 14;
							frameY++;
						}
					}
				}
			}
			else if (number == 3) {  //벽의 처음 조건 추가
				frameY = 6;			//프레임 Y 축이 다른 경우 변경
				frameX = 21;		//프레임 X축이 다른 경우 변경
				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < 3; j++) {
						IMAGEMANAGER->frameRender("tilemap", getMemDC(), 650 + (j * 45), 300 + (i * 45), frameX, frameY);
						frameX++;
						if (frameX > 24) {	//화면에 출력 대는 이미지 숫자 7개 지정
							frameX = 21;
							frameY++;
						}
					}
				}
			}
		}
		else if (_viewTerNum == 3) { //낙사 타일 선택
			if (KEYMANAGER->isToggleKey(VK_TAB)) {	//버튼 UI
				Rectangle(getMemDC(), _nextRc.left, _nextRc.top, _nextRc.right, _nextRc.bottom);
				if (number > 0) {
					Rectangle(getMemDC(), _previousRc.left, _previousRc.top, _previousRc.right, _previousRc.bottom);
				}
			}
			IMAGEMANAGER->render("button", getMemDC(), _nextRc.left, _nextRc.top);
			IMAGEMANAGER->render("buttonright", getMemDC(), _nextRc.left + 10, _nextRc.top + 10);
			if (number > 0) {
				IMAGEMANAGER->render("button", getMemDC(), _previousRc.left, _previousRc.top);
				IMAGEMANAGER->render("buttonleft", getMemDC(), _previousRc.left + 5, _previousRc.top + 10);
			}
			if (number == 0) {
				frameY = 9;	//프레임 Y 축이 다른 경우 변경
				frameX = 0;	//프레임 X축이 다른 경우 변경
				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < 8; j++) {
						IMAGEMANAGER->frameRender("tilemap", getMemDC(), 650 + (j * 45), 300 + (i * 45), frameX, frameY);
						frameX++;
						if (frameX > 7) {	//화면에 출력 대는 이미지 숫자 7개 지정
							frameX = 0;
						}
					}
				}
			}
			else if (number == 1) {
				frameY = 9;	//프레임 Y 축이 다른 경우 변경
				frameX = 7;	//프레임 X축이 다른 경우 변경
				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < 4; j++) {
						IMAGEMANAGER->frameRender("tilemap", getMemDC(), 650 + (j * 45), 300 + (i * 45), frameX, frameY);
						frameX++;
						if (frameX > 11) {	//화면에 출력 대는 이미지 5개
							frameX = 7;
						}
					}
				}
			}
		}
	}
	else if (_viewTile == 2) {  //오브젝트 출력
		if (_viewObjNum == 1) {
			for (int i = 0; i < 2; i++) {   //크기가 2by2인 이미지 출력(Y축이 2 X축이 2)
				for (int j = 0; j < 2; j++)
				{
					IMAGEMANAGER->frameRender("objectmap", getMemDC(), 650 + (j * 32), 400 + (i * 32), frameX, frameY); //여기서 32를 곱하는 이유는 타일 크기 값이 32이기 때문
					frameX++;
					if (frameX > 1) {
						frameX = 0;
						frameY++;
					}
				}
			}
		}
		else if (_viewObjNum == 2) {
			frameX = 2;  //x축 선택 
			for (int i = 0; i < 2; i++) {  //크기가 2by4인 이미지 출력(Y축이 2 X축이 4)
				for (int j = 0; j < 4; j++) {
					IMAGEMANAGER->frameRender("objectmap", getMemDC(), 650 + (j * 32), 400 + (i * 32), frameX, frameY);
					frameX++;
					if (frameX > 5) { //x축을 선택하여 범위를 넘어갈 경우 y축 변경하여 범위 지정(단 y축의 최대 증가는 2번뿐임으로 Y축의 사이즈에 포함)
						frameX = 2;
						frameY++;
					}
				}
			}
		}
		else if (_viewObjNum == 3) {
			frameX = 0;
			frameY = 2;
			for (int i = 0; i < 5; i++) {  //크기가 5by3인 이미지 출력(Y축이 5 X축이 3)
				for (int j = 0; j < 3; j++) {
					IMAGEMANAGER->frameRender("objectmap", getMemDC(), 650 + (j * 32), 400 + (i * 32), frameX, frameY);
					frameX++;
					if (frameX > 2) {
						frameX = 0;
						frameY++;
					}
				}
			}
		}
		else if (_viewObjNum == 4) {
			frameX = 4;
			frameY = 2;
			for (int i = 0; i < 5; i++) { //크기가 2by 5인 이미지 출력(Y축이 5 X축이 2)
				for (int j = 0; j < 2; j++) {
					IMAGEMANAGER->frameRender("objectmap", getMemDC(), 650 + (j * 32), 400 + (i * 32), frameX, frameY);
					frameX++;
					if (frameX > 5) {
						frameX = 4;
						frameY++;
					}
				}
			}
		}
	}




	if (KEYMANAGER->isToggleKey(VK_TAB))  //샘플 타일의 렉트 확인 용도
	{
		for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
		{
			Rectangle(getMemDC(), _sampleTiles[i].rcTile.left, _sampleTiles[i].rcTile.top, _sampleTiles[i].rcTile.right, _sampleTiles[i].rcTile.bottom);
		}
	}

	Rectangle(getMemDC(), _dragRc.left, _dragRc.top, _dragRc.right, _dragRc.bottom);
}

void mapTool::maptoolSetup()
{
	//왼쪽 맵 셋팅
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_tiles[i*TILEX + j].rc,   //각 타일의 크기별로 RECT 지정
				j*TILESIZE,
				i*TILESIZE,
				j*TILESIZE + TILESIZE,
				i*TILESIZE + TILESIZE);
		}
	}

	//처음 깔려있는 타일
	for (int i = 0; i < TILEX*TILEY; i++)  //초기 타일 전부 0으로 설정
	{
		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;

		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;

		_tiles[i].terrain = TR_NULL;
		_tiles[i].obj = OBJ_NONE;


	}

}

void mapTool::setMap()
{
	//오른쪽 샘플

	if (_viewTile == 1) {
		if (_viewTerNum == 1 || _viewTerNum == 2 || _viewTerNum == 3) {
			for (int i = 0; i < SAMPLETILEX* SAMPLETILEY; i++)
			{
				if (PtInRect(&_sampleTiles[i].rcTile, m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
				{
					_currentTile.x = _sampleTiles[i].terrainFrameX;  //지형 선택 후 해당 이미지의 좌표를 다른 좌표에 주소 저장
					_currentTile.y = _sampleTiles[i].terrainFrameY;  //지형 선택 후 해당 이미지의 좌표를 다른 좌표에 주소 저장
					break;
				}
			}
		}
	}
	else if (_viewTile == 2) {
		if (_viewObjNum == 1) {
			for (int i = 0; i < SAMPLETILEX* SAMPLETILEY; i++)
			{
				if (PtInRect(&_sampleTiles[i].rcTile, m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)) //세팅이 많은 이유 오브젝트의 크기가 한개의 타일 크기가 아니므로 인접 좌표 또한 변경해주어야함 
				{
					_currentTile.x = _sampleTiles[i].objFrameX;  //현재 X축 값을 OBJECT X축 값으로 변경
					_currentTile.y = _sampleTiles[i].objFrameY;	 //현재 Y축 값을 OBJECT Y축 값으로 변경

					_currentTile.x1 = _sampleTiles[i + 1].objFrameX1;
					_currentTile.y1 = _sampleTiles[i + 1].objFrameY1;

					_currentTile.x2 = _sampleTiles[i + TILEX].objFrameX2;
					_currentTile.y2 = _sampleTiles[i + TILEX].objFrameY2;

					_currentTile.x3 = _sampleTiles[i + TILEX + 1].objFrameX3;
					_currentTile.y3 = _sampleTiles[i + TILEX + 1].objFrameY3;

					break;
				}
			}
		}
		if (_viewObjNum == 2) {
			for (int i = 0; i < SAMPLETILEX* SAMPLETILEY; i++)
			{
				if (PtInRect(&_sampleTiles[i].rcTile, m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))  //세팅이 많은 이유 오브젝트의 크기가 한개의 타일 크기가 아니므로 인접 좌표 또한 변경해주어야함 
				{

					_currentTile.x = _sampleTiles[i].objFrameX;  //현재 X축 값을 OBJECT X축 값으로 변경
					_currentTile.y = _sampleTiles[i].objFrameY;	 //현재 Y축 값을 OBJECT Y축 값으로 변경

					_currentTile.x1 = _sampleTiles[i + 1].objFrameX1;
					_currentTile.y1 = _sampleTiles[i + 1].objFrameY1;

					_currentTile.x2 = _sampleTiles[i + 2].objFrameX2;
					_currentTile.y2 = _sampleTiles[i + 2].objFrameY2;

					_currentTile.x3 = _sampleTiles[i + 3].objFrameX3;
					_currentTile.y3 = _sampleTiles[i + 3].objFrameY3;

					_currentTile.x4 = _sampleTiles[i + TILEX].objFrameX4;
					_currentTile.y4 = _sampleTiles[i + TILEX].objFrameY4;

					_currentTile.x5 = _sampleTiles[i + 1 + TILEX].objFrameX5;
					_currentTile.y5 = _sampleTiles[i + 1 + TILEX].objFrameY5;

					_currentTile.x6 = _sampleTiles[i + 2 + TILEX].objFrameX6;
					_currentTile.y6 = _sampleTiles[i + 2 + TILEX].objFrameY6;

					_currentTile.x7 = _sampleTiles[i + 3 + TILEX].objFrameX7;
					_currentTile.y7 = _sampleTiles[i + 3 + TILEX].objFrameY7;
					break;
				}
			}
		}
		if (_viewObjNum == 3) {
			for (int i = 0; i < SAMPLETILEX* SAMPLETILEY; i++)
			{
				if (PtInRect(&_sampleTiles[i].rcTile, m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))  //세팅이 많은 이유 오브젝트의 크기가 한개의 타일 크기가 아니므로 인접 좌표 또한 변경해주어야함 
				{
					_currentTile.x = _sampleTiles[i].objFrameX;  //현재 X축 값을 OBJECT X축 값으로 변경
					_currentTile.y = _sampleTiles[i].objFrameY;	 //현재 Y축 값을 OBJECT Y축 값으로 변경

					_currentTile.x1 = _sampleTiles[i + 1].objFrameX1;
					_currentTile.y1 = _sampleTiles[i + 1].objFrameY1;

					_currentTile.x2 = _sampleTiles[i + 2].objFrameX2;
					_currentTile.y2 = _sampleTiles[i + 2].objFrameY2;

					_currentTile.x3 = _sampleTiles[i + TILEX].objFrameX3;
					_currentTile.y3 = _sampleTiles[i + TILEX].objFrameY3;

					_currentTile.x4 = _sampleTiles[i + 1 + TILEX].objFrameX4;
					_currentTile.y4 = _sampleTiles[i + 1 + TILEX].objFrameY4;

					_currentTile.x5 = _sampleTiles[i + 2 + TILEX].objFrameX5;
					_currentTile.y5 = _sampleTiles[i + 2 + TILEX].objFrameY5;

					_currentTile.x6 = _sampleTiles[i + (2 * TILEX)].objFrameX6;
					_currentTile.y6 = _sampleTiles[i + (2 * TILEX)].objFrameY6;

					_currentTile.x7 = _sampleTiles[i + 1 + (2 * TILEX)].objFrameX7;
					_currentTile.y7 = _sampleTiles[i + 1 + (2 * TILEX)].objFrameY7;

					_currentTile.x8 = _sampleTiles[i + 2 + (2 * TILEX)].objFrameX8;
					_currentTile.y8 = _sampleTiles[i + 2 + (2 * TILEX)].objFrameY8;

					_currentTile.x9 = _sampleTiles[i + (3 * TILEX)].objFrameX9;
					_currentTile.y9 = _sampleTiles[i + (3 * TILEX)].objFrameY9;

					_currentTile.x10 = _sampleTiles[i + 1 + (3 * TILEX)].objFrameX10;
					_currentTile.y10 = _sampleTiles[i + 1 + (3 * TILEX)].objFrameY10;

					_currentTile.x11 = _sampleTiles[i + 2 + (3 * TILEX)].objFrameX11;
					_currentTile.y11 = _sampleTiles[i + 2 + (3 * TILEX)].objFrameY11;
					break;
				}
			}
		}
		else if (_viewObjNum == 4) {
			for (int i = 0; i < SAMPLETILEX* SAMPLETILEY; i++)
			{
				if (PtInRect(&_sampleTiles[i].rcTile, m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)) //세팅이 많은 이유 오브젝트의 크기가 한개의 타일 크기가 아니므로 인접 좌표 또한 변경해주어야함 
				{
					_currentTile.x = _sampleTiles[i].objFrameX;  //현재 X축 값을 OBJECT X축 값으로 변경
					_currentTile.y = _sampleTiles[i].objFrameY;	 //현재 Y축 값을 OBJECT Y축 값으로 변경

					_currentTile.x1 = _sampleTiles[i + 1].objFrameX1;
					_currentTile.y1 = _sampleTiles[i + 1].objFrameY1;

					_currentTile.x2 = _sampleTiles[i + TILEX].objFrameX2;
					_currentTile.y2 = _sampleTiles[i + TILEX].objFrameY2;

					_currentTile.x3 = _sampleTiles[i + 1 + TILEX].objFrameX3;
					_currentTile.y3 = _sampleTiles[i + 1 + TILEX].objFrameY3;

					_currentTile.x4 = _sampleTiles[i + (2 * TILEX)].objFrameX4;
					_currentTile.y4 = _sampleTiles[i + (2 * TILEX)].objFrameY4;

					_currentTile.x5 = _sampleTiles[i + 1 + (2 * TILEX)].objFrameX5;
					_currentTile.y5 = _sampleTiles[i + 1 + (2 * TILEX)].objFrameY5;

					_currentTile.x6 = _sampleTiles[i + (3 * TILEX)].objFrameX6;
					_currentTile.y6 = _sampleTiles[i + (3 * TILEX)].objFrameY6;

					_currentTile.x7 = _sampleTiles[i + 1 + (3 * TILEX)].objFrameX7;
					_currentTile.y7 = _sampleTiles[i + 1 + (3 * TILEX)].objFrameY7;

					_currentTile.x8 = _sampleTiles[i + (4 * TILEX)].objFrameX8;
					_currentTile.y8 = _sampleTiles[i + (4 * TILEX)].objFrameY8;

					_currentTile.x9 = _sampleTiles[i + 1 + (4 * TILEX)].objFrameX9;
					_currentTile.y9 = _sampleTiles[i + 1 + (4 * TILEX)].objFrameY9;

					break;
				}
			}
		}
	}
	if (_isClick == true) {
		//왼쪽 타일
		for (int i = 0; i < TILEX * TILEY; i++) {
			if (PtInRect(&_tiles[i].rc, m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				if (_ctrlSelect == CTRL_TERRAINDRAW)
				{
					_tiles[i].terrainFrameX = _currentTile.x;
					_tiles[i].terrainFrameY = _currentTile.y;
					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				else if (_ctrlSelect == CTRL_OBJDRAW)
				{
					if (_viewObjNum == 1) {
						if (_tiles[i].obj == OBJ_NONE && _tiles[i + 1].obj == OBJ_NONE && _tiles[i + TILEX].obj == OBJ_NONE && _tiles[i + 1 + TILEX].obj == OBJ_NONE) {
							//마우스를 클릭 지점과 해당 이미지 크기주변의 속성이 NONE일경우
							_tiles[i].objFrameX = _currentTile.x; //지정된 타일에 현재 타일 X값으로 변경
							_tiles[i].objFrameY = _currentTile.y; //지정된 타일에 현재 타일 Y값으로 변경.

							_tiles[i + 1].objFrameX = _currentTile.x1;
							_tiles[i + 1].objFrameY = _currentTile.y1;

							_tiles[i + TILEX].objFrameX = _currentTile.x2;
							_tiles[i + TILEX].objFrameY = _currentTile.y2;

							_tiles[i + 1 + TILEX].objFrameX = _currentTile.x3;
							_tiles[i + 1 + TILEX].objFrameY = _currentTile.y3;

							_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);  // 상태 불러 오기	
							_tiles[i + 1].obj = objSelect(_currentTile.x1, _currentTile.y1);
							_tiles[i + TILEX].obj = objSelect(_currentTile.x2, _currentTile.y2);
							_tiles[i + TILEX + 1].obj = objSelect(_currentTile.x3, _currentTile.y3);
							//	_rectTile[i].interRect = RectMake(i, i, 64, 64);
						}
					}

					if (_viewObjNum == 2) {
						if (_tiles[i].obj == OBJ_NONE && _tiles[i + 1].obj == OBJ_NONE && _tiles[i + 2].obj == OBJ_NONE && _tiles[i + 3].obj == OBJ_NONE && _tiles[i + TILEX].obj == OBJ_NONE && _tiles[i + 1 + TILEX].obj == OBJ_NONE && _tiles[i + 2 + TILEX].obj == OBJ_NONE && _tiles[i + 3 + TILEX].obj == OBJ_NONE) {
							//마우스를 클릭 지점과 해당 이미지 크기주변의 속성이 NONE일경우
							_tiles[i].objFrameX = _currentTile.x;
							_tiles[i].objFrameY = _currentTile.y;

							_tiles[i + 1].objFrameX = _currentTile.x1;
							_tiles[i + 1].objFrameY = _currentTile.y1;

							_tiles[i + 2].objFrameX = _currentTile.x2;
							_tiles[i + 2].objFrameY = _currentTile.y2;

							_tiles[i + 3].objFrameX = _currentTile.x3;
							_tiles[i + 3].objFrameY = _currentTile.y3;

							_tiles[i + TILEX].objFrameX = _currentTile.x4;
							_tiles[i + TILEX].objFrameY = _currentTile.y4;

							_tiles[i + 1 + TILEX].objFrameX = _currentTile.x5;
							_tiles[i + 1 + TILEX].objFrameY = _currentTile.y5;

							_tiles[i + 2 + TILEX].objFrameX = _currentTile.x6;
							_tiles[i + 2 + TILEX].objFrameY = _currentTile.y6;

							_tiles[i + 3 + TILEX].objFrameX = _currentTile.x7;
							_tiles[i + 3 + TILEX].objFrameY = _currentTile.y7;

							_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
							_tiles[i + 1].obj = objSelect(_currentTile.x1, _currentTile.y1);
							_tiles[i + 2].obj = objSelect(_currentTile.x2, _currentTile.y2);
							_tiles[i + 3].obj = objSelect(_currentTile.x3, _currentTile.y3);
							_tiles[i + TILEX].obj = objSelect(_currentTile.x4, _currentTile.y4);
							_tiles[i + 1 + TILEX].obj = objSelect(_currentTile.x5, _currentTile.y5);
							_tiles[i + 2 + TILEX].obj = objSelect(_currentTile.x6, _currentTile.y6);
							_tiles[i + 3 + TILEX].obj = objSelect(_currentTile.x7, _currentTile.y7);
							//_rectTile[i].interRect = RectMake(i, i,128, 64);
						}
					}
					if (_viewObjNum == 3) {
						if (_tiles[i].obj == OBJ_NONE && _tiles[i + 1].obj == OBJ_NONE && _tiles[i + 2].obj == OBJ_NONE && _tiles[i + TILEX].obj == OBJ_NONE && _tiles[i + 1 + TILEX].obj == OBJ_NONE && _tiles[i + 2 + TILEX].obj == OBJ_NONE && _tiles[i + (2 * TILEX)].obj == OBJ_NONE && _tiles[i + 1 + (2 * TILEX)].obj == OBJ_NONE && _tiles[i + 2 + (2 * TILEX)].obj == OBJ_NONE && _tiles[i + (3 * TILEX)].obj == OBJ_NONE && _tiles[i + 1 + (3 * TILEX)].obj == OBJ_NONE && _tiles[i + 2 + (3 * TILEX)].obj == OBJ_NONE) {
							//마우스를 클릭 지점과 해당 이미지 크기주변의 속성이 NONE일경우
							_tiles[i].objFrameX = _currentTile.x;
							_tiles[i].objFrameY = _currentTile.y;

							_tiles[i + 1].objFrameX = _currentTile.x1;
							_tiles[i + 1].objFrameY = _currentTile.y1;

							_tiles[i + 2].objFrameX = _currentTile.x2;
							_tiles[i + 2].objFrameY = _currentTile.y2;

							_tiles[i + TILEX].objFrameX = _currentTile.x3;
							_tiles[i + TILEX].objFrameY = _currentTile.y3;

							_tiles[i + 1 + TILEX].objFrameX = _currentTile.x4;
							_tiles[i + 1 + TILEX].objFrameY = _currentTile.y4;

							_tiles[i + 2 + TILEX].objFrameX = _currentTile.x5;
							_tiles[i + 2 + TILEX].objFrameY = _currentTile.y5;

							_tiles[i + (2 * TILEX)].objFrameX = _currentTile.x6;
							_tiles[i + (2 * TILEX)].objFrameY = _currentTile.y6;

							_tiles[i + 1 + (2 * TILEX)].objFrameX = _currentTile.x7;
							_tiles[i + 1 + (2 * TILEX)].objFrameY = _currentTile.y7;

							_tiles[i + 2 + (2 * TILEX)].objFrameX = _currentTile.x8;
							_tiles[i + 2 + (2 * TILEX)].objFrameY = _currentTile.y8;

							_tiles[i + (3 * TILEX)].objFrameX = _currentTile.x9;
							_tiles[i + (3 * TILEX)].objFrameY = _currentTile.y9;

							_tiles[i + 1 + (3 * TILEX)].objFrameX = _currentTile.x10;
							_tiles[i + 1 + (3 * TILEX)].objFrameY = _currentTile.y10;

							_tiles[i + 2 + (3 * TILEX)].objFrameX = _currentTile.x11;
							_tiles[i + 2 + (3 * TILEX)].objFrameY = _currentTile.y11;

							_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
							_tiles[i + 1].obj = objSelect(_currentTile.x1, _currentTile.y1);
							_tiles[i + 2].obj = objSelect(_currentTile.x2, _currentTile.y2);
							_tiles[i + TILEX].obj = objSelect(_currentTile.x3, _currentTile.y3);
							_tiles[i + 1 + TILEX].obj = objSelect(_currentTile.x4, _currentTile.y4);
							_tiles[i + 2 + TILEX].obj = objSelect(_currentTile.x5, _currentTile.y5);
							_tiles[i + (2 * TILEX)].obj = objSelect(_currentTile.x6, _currentTile.y6);
							_tiles[i + 1 + (2 * TILEX)].obj = objSelect(_currentTile.x7, _currentTile.y7);
							_tiles[i + 2 + (2 * TILEX)].obj = objSelect(_currentTile.x8, _currentTile.y8);
							_tiles[i + (3 * TILEX)].obj = objSelect(_currentTile.x9, _currentTile.y9);
							_tiles[i + 1 + (3 * TILEX)].obj = objSelect(_currentTile.x10, _currentTile.y10);
							_tiles[i + 2 + (3 * TILEX)].obj = objSelect(_currentTile.x11, _currentTile.y11);
						}
						//_rectTile[i].interRect = RectMake(i, i,96, 128);
					}
					if (_viewObjNum == 4) {
						if (_tiles[i].obj == OBJ_NONE && _tiles[i + 1].obj == OBJ_NONE && _tiles[i + TILEX].obj == OBJ_NONE && _tiles[i + 1 + TILEX].obj == OBJ_NONE && _tiles[i + (2 * TILEX)].obj == OBJ_NONE && _tiles[i + 1 + (2 * TILEX)].obj == OBJ_NONE && _tiles[i + (3 * TILEX)].obj == OBJ_NONE && _tiles[i + 1 + (3 * TILEX)].obj == OBJ_NONE && _tiles[i + (4 * TILEX)].obj == OBJ_NONE && _tiles[i + 1 + (4 * TILEX)].obj == OBJ_NONE) {
							//마우스를 클릭 지점과 해당 이미지 크기주변의 속성이 NONE일경우
							_tiles[i].objFrameX = _currentTile.x;
							_tiles[i].objFrameY = _currentTile.y;

							_tiles[i + 1].objFrameX = _currentTile.x1;
							_tiles[i + 1].objFrameY = _currentTile.y1;

							_tiles[i + TILEX].objFrameX = _currentTile.x2;
							_tiles[i + TILEX].objFrameY = _currentTile.y2;

							_tiles[i + 1 + TILEX].objFrameX = _currentTile.x3;
							_tiles[i + 1 + TILEX].objFrameY = _currentTile.y3;

							_tiles[i + (2 * TILEX)].objFrameX = _currentTile.x4;
							_tiles[i + (2 * TILEX)].objFrameY = _currentTile.y4;

							_tiles[i + 1 + (2 * TILEX)].objFrameX = _currentTile.x5;
							_tiles[i + 1 + (2 * TILEX)].objFrameY = _currentTile.y5;

							_tiles[i + (3 * TILEX)].objFrameX = _currentTile.x6;
							_tiles[i + (3 * TILEX)].objFrameY = _currentTile.y6;

							_tiles[i + 1 + (3 * TILEX)].objFrameX = _currentTile.x7;
							_tiles[i + 1 + (3 * TILEX)].objFrameY = _currentTile.y7;
							_tiles[i + (4 * TILEX)].objFrameX = _currentTile.x8;
							_tiles[i + (4 * TILEX)].objFrameY = _currentTile.y8;

							_tiles[i + 1 + (4 * TILEX)].objFrameX = _currentTile.x9;
							_tiles[i + 1 + (4 * TILEX)].objFrameY = _currentTile.y9;

							_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
							_tiles[i + 1].obj = objSelect(_currentTile.x1, _currentTile.y1);
							_tiles[i + TILEX].obj = objSelect(_currentTile.x2, _currentTile.y2);
							_tiles[i + 1 + TILEX].obj = objSelect(_currentTile.x3, _currentTile.y3);
							_tiles[i + (2 * TILEX)].obj = objSelect(_currentTile.x4, _currentTile.y4);
							_tiles[i + 1 + (2 * TILEX)].obj = objSelect(_currentTile.x5, _currentTile.y5);
							_tiles[i + (3 * TILEX)].obj = objSelect(_currentTile.x6, _currentTile.y6);
							_tiles[i + 1 + (3 * TILEX)].obj = objSelect(_currentTile.x7, _currentTile.y7);
							_tiles[i + (4 * TILEX)].obj = objSelect(_currentTile.x8, _currentTile.y8);
							_tiles[i + 1 + (4 * TILEX)].obj = objSelect(_currentTile.x9, _currentTile.y9);

							//_rectTile[i].interRect = RectMake(i, i,96, 160);
						}
					}



				}

				else if (_ctrlSelect == CTRL_ERASER) //맵툴 지우개 기능(커서의 위치의 값을 0와 무 속성으로 바꿈)
				{
					_tiles[i].objFrameX = 0;
					_tiles[i].objFrameY = 0;
					_tiles[i].obj = OBJ_NONE;
					_tiles[i].terrainFrameX = 0;
					_tiles[i].terrainFrameY = 0;
					_tiles[i].terrain = TR_NULL;
				}
				InvalidateRect(m_hWnd, NULL, false);
				break;
			}
		}
	}
}

void mapTool::setRectMap()  //이미지 위치에 렉트 생성
{
	if (_viewTile == 1) {
		if (_viewTerNum == 1) {
			if (number == 0) {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 8; j++) {
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameX = j;
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameY = i;
						SetRect(&_sampleTiles[i* SAMPLETILEX + j].rcTile, (665 + (j * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
							(315 + (i * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))),
							(665 + (j * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))));
					}
				}
			}
			if (number == 1) {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 8; j++) {
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameX = j + 7;
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameY = i;
						SetRect(&_sampleTiles[i* SAMPLETILEX + j].rcTile, (665 + (j * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))),
							(665 + (j * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))));
					}
				}
			}
			if (number == 2) {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 8; j++) {
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameX = j + 14;
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameY = i;
						SetRect(&_sampleTiles[i* SAMPLETILEX + j].rcTile, (665 + (j * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))),
							(665 + (j * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))));
					}
				}
			}
			if (number == 3) {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameX = j + 21;
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameY = i;
						SetRect(&_sampleTiles[i* SAMPLETILEX + j].rcTile, (665 + (j * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))),
							(665 + (j * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))));
					}
				}
			}
		}
		else if (_viewTerNum == 2) {
			if (number == 0) {
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 8; j++) {
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameX = j;
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameY = i + 6;
						SetRect(&_sampleTiles[i* SAMPLETILEX + j].rcTile, (665 + (j * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))),
							(665 + (j * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))));
					}
				}
			}
			if (number == 1) {
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 8; j++) {
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameX = j + 7;
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameY = i + 6;
						SetRect(&_sampleTiles[i* SAMPLETILEX + j].rcTile, (665 + (j * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))),
							(665 + (j * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))));
					}
				}
			}
			if (number == 2) {
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 8; j++) {
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameX = j + 14;
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameY = i + 6;
						SetRect(&_sampleTiles[i* SAMPLETILEX + j].rcTile, (665 + (j * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))),
							(665 + (j * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))));
					}
				}
			}
			if (number == 3) {
				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < 3; j++) {
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameX = j + 21;
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameY = i + 6;
						SetRect(&_sampleTiles[i* SAMPLETILEX + j].rcTile, (665 + (j * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))),
							(665 + (j * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))));

					}
				}
			}
		}
		else if (_viewTerNum == 3) {
			if (number == 0) {
				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < 8; j++) {
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameX = j;
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameY = i + 9;
						SetRect(&_sampleTiles[i* SAMPLETILEX + j].rcTile, (665 + (j * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))),
							(665 + (j * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))));
					}
				}
			}
			if (number == 1) {
				for (int i = 0; i < 1; i++) {
					for (int j = 0; j < 4; j++) {
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameX = j + 7;
						_sampleTiles[i* SAMPLETILEX + j].terrainFrameY = i + 9;
						SetRect(&_sampleTiles[i* SAMPLETILEX + j].rcTile, (665 + (j * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))),
							(665 + (j * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))));
					}
				}
			}
		}
	}
	else if (_viewTile == 2) { //렉트 크기 지정
		if (_viewObjNum == 1) {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					_sampleTiles[i* SAMPLETILEX + j].objFrameX = 0;
					_sampleTiles[i* SAMPLETILEX + j].objFrameY = 0;

					_sampleTiles[(i* SAMPLETILEX + j) + 1].objFrameX1 = 1;
					_sampleTiles[(i* SAMPLETILEX + j) + 1].objFrameY1 = 0;

					_sampleTiles[(i* SAMPLETILEX + j) + TILEX].objFrameX2 = 0;
					_sampleTiles[(i* SAMPLETILEX + j) + TILEX].objFrameY2 = 1;

					_sampleTiles[(i* SAMPLETILEX + j) + TILEX + 1].objFrameX3 = 1;
					_sampleTiles[(i* SAMPLETILEX + j) + TILEX + 1].objFrameY3 = 1;
					SetRect(&_sampleTiles[i* SAMPLETILEX + j].rcTile, (665 - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),
						(415 - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))),
						(665 + 32 + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),
						(415 + 32 + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))));
				}
			}
		}
		else if (_viewObjNum == 2) {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 4; j++) {
					_sampleTiles[i* SAMPLETILEX + j].objFrameX = 2;  //OBJECTMAP 파일의 벤치 2 렉트 값 확인 및 설정
					_sampleTiles[i* SAMPLETILEX + j].objFrameY = 0;		 //OBJECTMAP 파일의 벤치 2 렉트 값 확인 및 설정
					_sampleTiles[(i* SAMPLETILEX + j) + 1].objFrameX1 = 3;
					_sampleTiles[(i* SAMPLETILEX + j) + 1].objFrameY1 = 0;
					_sampleTiles[(i* SAMPLETILEX + j) + 2].objFrameX2 = 4;
					_sampleTiles[(i* SAMPLETILEX + j) + 2].objFrameY2 = 0;
					_sampleTiles[(i* SAMPLETILEX + j) + 3].objFrameX3 = 5;
					_sampleTiles[(i* SAMPLETILEX + j) + 3].objFrameY3 = 0;
					_sampleTiles[(i* SAMPLETILEX + j) + TILEX].objFrameX4 = 2;
					_sampleTiles[(i* SAMPLETILEX + j) + TILEX].objFrameY4 = 1;
					_sampleTiles[(i* SAMPLETILEX + j) + 1 + TILEX].objFrameX5 = 3;
					_sampleTiles[(i* SAMPLETILEX + j) + 1 + TILEX].objFrameY5 = 1;
					_sampleTiles[(i* SAMPLETILEX + j) + 2 + TILEX].objFrameX6 = 4;
					_sampleTiles[(i* SAMPLETILEX + j) + 2 + TILEX].objFrameY6 = 1;
					_sampleTiles[(i* SAMPLETILEX + j) + 3 + TILEX].objFrameX7 = 5;
					_sampleTiles[(i* SAMPLETILEX + j) + 3 + TILEX].objFrameY7 = 1;

					SetRect(&_sampleTiles[i* SAMPLETILEX + j].rcTile, (665 - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),
						(415 - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))),
						(665 + 96 + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),
						(415 + 32 + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))));

				}
			}
		}
		else if (_viewObjNum == 3) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 3; j++) {
					_sampleTiles[i* SAMPLETILEX + j].objFrameX = 0;
					_sampleTiles[i* SAMPLETILEX + j].objFrameY = 2;
					_sampleTiles[(i* SAMPLETILEX + j) + 1].objFrameX1 = 1;
					_sampleTiles[(i* SAMPLETILEX + j) + 1].objFrameY1 = 2;
					_sampleTiles[(i* SAMPLETILEX + j) + 2].objFrameX2 = 2;
					_sampleTiles[(i* SAMPLETILEX + j) + 2].objFrameY2 = 2;
					_sampleTiles[(i* SAMPLETILEX + j) + TILEX].objFrameX3 = 0;
					_sampleTiles[(i* SAMPLETILEX + j) + TILEX].objFrameY3 = 3;
					_sampleTiles[(i* SAMPLETILEX + j) + 1 + TILEX].objFrameX4 = 1;
					_sampleTiles[(i* SAMPLETILEX + j) + 1 + TILEX].objFrameY4 = 3;
					_sampleTiles[(i* SAMPLETILEX + j) + 2 + TILEX].objFrameX5 = 2;
					_sampleTiles[(i* SAMPLETILEX + j) + 2 + TILEX].objFrameY5 = 3;
					_sampleTiles[(i* SAMPLETILEX + j) + (2 * TILEX)].objFrameX6 = 0;
					_sampleTiles[(i* SAMPLETILEX + j) + (2 * TILEX)].objFrameY6 = 4;
					_sampleTiles[(i* SAMPLETILEX + j) + 1 + (2 * TILEX)].objFrameX7 = 1;
					_sampleTiles[(i* SAMPLETILEX + j) + 1 + (2 * TILEX)].objFrameY7 = 4;
					_sampleTiles[(i* SAMPLETILEX + j) + 2 + (2 * TILEX)].objFrameX8 = 2;
					_sampleTiles[(i* SAMPLETILEX + j) + 2 + (2 * TILEX)].objFrameY8 = 4;
					_sampleTiles[(i* SAMPLETILEX + j) + (3 * TILEX)].objFrameX9 = 0;
					_sampleTiles[(i* SAMPLETILEX + j) + (3 * TILEX)].objFrameY9 = 5;
					_sampleTiles[(i* SAMPLETILEX + j) + 1 + (3 * TILEX)].objFrameX10 = 1;
					_sampleTiles[(i* SAMPLETILEX + j) + 1 + (3 * TILEX)].objFrameY10 = 5;
					_sampleTiles[(i* SAMPLETILEX + j) + 2 + (3 * TILEX)].objFrameX11 = 2;
					_sampleTiles[(i* SAMPLETILEX + j) + 2 + (3 * TILEX)].objFrameY11 = 5;


					SetRect(&_sampleTiles[i* SAMPLETILEX + j].rcTile, (665 - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),
						(415 - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))),
						(665 + 64 + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),
						(415 + 128 + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))));

				}
			}
		}
		else if (_viewObjNum == 4) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 2; j++) {
					_sampleTiles[i* SAMPLETILEX + j].objFrameX = 4;
					_sampleTiles[i* SAMPLETILEX + j].objFrameY = 2;
					_sampleTiles[(i* SAMPLETILEX + j) + 1].objFrameX1 = 5;
					_sampleTiles[(i* SAMPLETILEX + j) + 1].objFrameY1 = 2;
					_sampleTiles[(i* SAMPLETILEX + j) + TILEX].objFrameX2 = 4;
					_sampleTiles[(i* SAMPLETILEX + j) + TILEX].objFrameY2 = 3;
					_sampleTiles[(i* SAMPLETILEX + j) + 1 + TILEX].objFrameX3 = 5;
					_sampleTiles[(i* SAMPLETILEX + j) + 1 + TILEX].objFrameY3 = 3;
					_sampleTiles[(i* SAMPLETILEX + j) + (2 * TILEX)].objFrameX4 = 4;
					_sampleTiles[(i* SAMPLETILEX + j) + (2 * TILEX)].objFrameY4 = 4;
					_sampleTiles[(i* SAMPLETILEX + j) + 1 + (2 * TILEX)].objFrameX5 = 5;
					_sampleTiles[(i* SAMPLETILEX + j) + 1 + (2 * TILEX)].objFrameY5 = 4;
					_sampleTiles[(i* SAMPLETILEX + j) + (3 * TILEX)].objFrameX6 = 4;
					_sampleTiles[(i* SAMPLETILEX + j) + (3 * TILEX)].objFrameY6 = 5;
					_sampleTiles[(i* SAMPLETILEX + j) + 1 + (3 * TILEX)].objFrameX7 = 5;
					_sampleTiles[(i* SAMPLETILEX + j) + 1 + (3 * TILEX)].objFrameY7 = 5;
					_sampleTiles[(i* SAMPLETILEX + j) + (4 * TILEX)].objFrameX8 = 4;
					_sampleTiles[(i* SAMPLETILEX + j) + (4 * TILEX)].objFrameY8 = 6;
					_sampleTiles[(i* SAMPLETILEX + j) + 1 + (4 * TILEX)].objFrameX9 = 5;
					_sampleTiles[(i* SAMPLETILEX + j) + 1 + (4 * TILEX)].objFrameY9 = 6;

					SetRect(&_sampleTiles[i* SAMPLETILEX + j].rcTile, (665 - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),
						(415 - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))),
						(665 + 32 + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),
						(415 + 128 + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))));

				}
			}
		}

	}
}

void mapTool::save() //저장
{
	if (_ctrlSelect == CTRL_SAVE) {
		//윈도우 핸들 추가 초기 창에 저장 위치 설정
		_file1 = CreateFile("map.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(_file1, _tiles, sizeof(tagTile)*(TILEY*TILEX), &write, NULL);
		CloseHandle(_file1);

		/*
		_file2 = CreateFile("map2.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(_file2, _tiles, sizeof(tagTile)*(TILEY*TILEX), &write, NULL);
		CloseHandle(_file2);
		*/
	}
}

void mapTool::load() //불러오기
{
	if (_ctrlSelect == CTRL_LOAD) {
		//윈도우 핸들 추가 및 초기 창에서 위치 지정 밑 불러올 것 확인
		_file1 = CreateFile("map.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(_file1, _tiles, sizeof(tagTile)*(TILEY*TILEX), &read, NULL);
		CloseHandle(_file1);

		/*
		_file2 = CreateFile("map.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(_file2, _tiles, sizeof(tagTile)*(TILEX*TILEY), &read, NULL);
		CloseHandle(_file2);
		*/
	}
}

void mapTool::uisetting() //화면 UI 세팅
{
	if (_isFirstMenu == true) {
		//첫화면 UI
		_loadButton = RectMakeCenter(830, 190, _backImage->getWidth(), _backImage->getHeight());
		_saveButton = RectMakeCenter(830, 120, _backImage->getWidth(), _backImage->getHeight());
		_initButton = RectMakeCenter(830, 260, _backImage->getWidth(), _backImage->getHeight());
		_terrainButton = RectMakeCenter(830, 330, _backImage->getWidth(), _backImage->getHeight());
		_objectButton = RectMakeCenter(830, 400, _backImage->getWidth(), _backImage->getHeight());
		_eraserButton = RectMakeCenter(830, 470, _backImage->getWidth(), _backImage->getHeight());


		_viewTile = 0;
		_viewTerNum = 0;
		number = 0;
		hiderect();
		//두번째 화면 UI
		_floorButton = RectMakeCenter(-830, -50, _backImage->getWidth(), _backImage->getHeight());
		_wallButton = RectMakeCenter(-830, -120, _backImage->getWidth(), _backImage->getHeight());
		_dropButton = RectMakeCenter(-830, -190, _backImage->getWidth(), _backImage->getHeight());
	}
	else
	{
		//첫화면 UI
		_loadButton = RectMakeCenter(-100, -100, _backImage->getWidth(), _backImage->getHeight());
		_saveButton = RectMakeCenter(-830, -120, _backImage->getWidth(), _backImage->getHeight());
		_initButton = RectMakeCenter(-830, -190, _backImage->getWidth(), _backImage->getHeight());
		_terrainButton = RectMakeCenter(-830, -260, _backImage->getWidth(), _backImage->getHeight());
		_objectButton = RectMakeCenter(-830, -330, _backImage->getWidth(), _backImage->getHeight());
		_eraserButton = RectMakeCenter(-830, -400, _backImage->getWidth(), _backImage->getHeight());

		//두번째 화면 UI
		if (_viewTile == 1) {
			_floorButton = RectMakeCenter(830, 260, _backImage->getWidth(), _backImage->getHeight());
			_wallButton = RectMakeCenter(830, 120, _backImage->getWidth(), _backImage->getHeight());
			_dropButton = RectMakeCenter(830, 190, _backImage->getWidth(), _backImage->getHeight());

			_nextRc = RectMakeCenter(WINSIZEX - 48, WINSIZEY - 105, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
			if (number > 0) {
				_previousRc = RectMakeCenter(673, WINSIZEY - 105, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
			}
		}
		else if (_viewTile == 2) {
			_bigBenchButton = RectMakeCenter(830, 120, _backImage->getWidth(), _backImage->getHeight());
			_smallBenchButton = RectMakeCenter(830, 190, _backImage->getWidth(), _backImage->getHeight());
			_statuesButton = RectMakeCenter(830, 260, _backImage->getWidth(), _backImage->getHeight());
			_pillarButton = RectMakeCenter(830, 330, _backImage->getWidth(), _backImage->getHeight());

			_nextRc = RectMakeCenter(WINSIZEX - 48, WINSIZEY - 105, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
			if (number > 0) {
				_previousRc = RectMakeCenter(673, WINSIZEY - 105, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
			}
		}
	}

	if (PtInRect(&_saveButton, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		_ctrlSelect = CTRL_SAVE;
		save();
	}
	if (PtInRect(&_eraserButton, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		_ctrlSelect = CTRL_ERASER;
	}
	if (PtInRect(&_loadButton, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		_ctrlSelect = CTRL_LOAD;
		load();
	}
	if (PtInRect(&_initButton, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		_ctrlSelect = CTRL_INIT;
		init();
	}

	if (PtInRect(&_terrainButton, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		_ctrlSelect = CTRL_TERRAINDRAW;
		_viewTile = 1;
		_isFirstMenu = false;
		_isSecondMenu = true;
	}
	else if (KEYMANAGER->isOnceKeyDown('Q')) {
		_isFirstMenu = true;
		_isSecondMenu = false;
	}

	if (PtInRect(&_objectButton, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		_ctrlSelect = CTRL_OBJDRAW;
		_viewTile = 2;
		_isFirstMenu = false;
		_isSecondMenu = true;
	}
	else if (KEYMANAGER->isOnceKeyDown('Q')) {

		_isFirstMenu = true;
		_isSecondMenu = false;
	}

	if (PtInRect(&_floorButton, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		hiderect();
		number = 0;
		_viewTerNum = 1;
	}
	if (PtInRect(&_wallButton, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		hiderect();
		number = 0;
		_viewTerNum = 2;
	}
	if (PtInRect(&_dropButton, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		hiderect();
		number = 0;
		_viewTerNum = 3;
	}

	if (PtInRect(&_bigBenchButton, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		hiderect();
		number = 0;
		_viewObjNum = 1;
	}
	if (PtInRect(&_smallBenchButton, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		hiderect();
		number = 0;
		_viewObjNum = 2;
	}
	if (PtInRect(&_statuesButton, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		hiderect();
		number = 0;
		_viewObjNum = 3;
	}
	if (PtInRect(&_pillarButton, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		hiderect();
		number = 0;
		_viewObjNum = 4;
	}

	if (PtInRect(&_nextRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		hiderect();
		number += 1;
	}

	else if (PtInRect(&_previousRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		hiderect();
		number -= 1;
	}
}

void mapTool::hiderect() //RECT 위치 변경(해당 위치가 아닌 음수로 이동)  -> 사각형 지우는 방법 (1. 해당 조건이 아닐 경우 그리지 않는다 2. 렉트의 위치를 이동한다. 3. 렉트를 메모리 상에서 전부 삭제 한다.(getMemDc()함수 응용))
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			SetRect(&_sampleTiles[i* SAMPLETILEX + j].rcTile, -100, -100, -100, -100);
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 7; j++) {
			SetRect(&_sampleTiles[i* SAMPLETILEX + j].rcTile, -100, -100, -100, -100);
		}
	}
}

/*void mapTool::drag()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		x = m_ptMouse.x;
		y = m_ptMouse.y;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
		if (x != m_ptMouse.x) {
			x1 = m_ptMouse.x;
		}
		if (y != m_ptMouse.y) {
			y1 = m_ptMouse.y;
		}
	}
	if (x < x1 && y < y1) {
		SetRect(&_dragRc, x, y, x1, y1);
	}
	if (x < x1 && y1 < y) {
		SetRect(&_dragRc, x, y1, x1, y);
	}
	if (x1 < x && y1 < y) {
		SetRect(&_dragRc, x1, y1, x, y);
	}
	if (x1 < x && y < y1) {
		SetRect(&_dragRc, x1, y, x, y1);
	}

}
*/
TERRAIN mapTool::terrainSelect(int frameX, int frameY)  //Terrain 값 세팅
{
	if (_ctrlSelect == CTRL_TERRAINDRAW) {
		if (_viewTerNum == 1) {
			for (int i = 0; i < 11; i++) {
				for (int j = 0; j < 25; j++) {
					if (j == frameX && i == frameY)
					{
						return TR_FLOOR;
					}//바닥		
				}
			}
		}
		else if (_viewTerNum == 2) {
			for (int i = 0; i < 11; i++) {
				for (int j = 0; j < 25; j++) {
					if (frameX == j && frameY == i)
					{
						return TR_WALL;
					}//벽		
				}
			}
		}
		else if (_viewTerNum == 3) {
			for (int i = 0; i < 11; i++) {
				for (int j = 0; j < 25; j++) {
					if (frameX == j && frameY == i)
					{
						return TR_DROP;
					}//낙사	
				}
			}
		}
	}
	return TERRAIN();
}

OBJECT mapTool::objSelect(int frameX, int frameY) //OBJECT 값 세팅
{
	if (_ctrlSelect == CTRL_OBJDRAW) {
		if (_viewObjNum == 1) {
			for (int j = 0; j < 2; j++) {
				for (int i = 0; i < 2; i++)
				{
					if (frameX == i && frameY == j) {
						return OBJ_SMALLBENCH;  //벤치 1 설정
					}
				}
			}
		}
		else if (_viewObjNum == 2) {
			for (int j = 0; j < 2; j++) {
				for (int i = 2; i < 6; i++) {
					if (frameX == i && frameY == j)
					{
						return OBJ_BIGBENCH; //벤치 2 설정
					}
				}
			}
		}
		else if (_viewObjNum == 3) {
			for (int j = 2; j < 4; j++) {
				for (int i = 0; i < 3; i++) {
					if (frameX == i && frameY == j) {
						return OBJ_STATUE;  //조각상 상단 부분 설정
					}
				}
			}
			for (int j = 4; j < 6; j++) {
				for (int i = 0; i < 3; i++) {
					if (frameX == i && frameY == j) {
						return OBJ_STATUEBLOCK;  //조각상 하단 부분 설정(충돌 처리 때문에 나눔)
					}
				}
			}
		}
		else if (_viewObjNum == 4) {
			for (int j = 2; j < 5; j++) {
				for (int i = 4; i < 6; i++) {
					if (frameX == i && frameY == j) {
						return OBJ_PILLAR;  //기둥 상단부분 설정
					}
				}
			}
			for (int j = 5; j < 7; j++) {
				for (int i = 4; i < 6; i++) {
					if (frameX == i && frameY == j) {
						return OBJ_PILLARBLOCK;  //기둥 하단 부분 설정(충돌 처리 때문에 나눔)
					}
				}
			}
		}
	}
	return OBJECT();
}