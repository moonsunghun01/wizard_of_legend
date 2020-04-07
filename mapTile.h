#pragma once

#define TILESIZE 32 //왼쪽 화면 타일 사이즈
#define TILEX 100//왼쪽화면 타일 X축 개수  
#define TILEY 100	//왼쪽화면 타일 Y축 개수

#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//화면 오른쪽 이미지 타일 갯수
#define SAMPLETILEX 24
#define SAMPLETILEY 10

//속성 관련 설정(이동 가능 여부)
#define ATTR_UNMOVABLE 0x00000001
#define ATTR_POSITION 0x00000002

enum TERRAIN   //지형
{
	TR_NULL, TR_FLOOR, TR_WALL, TR_DROP
};
enum OBJECT //오브젝트
{
	OBJ_NONE, OBJ_STATUEBLOCK, OBJ_STATUE, OBJ_BIGBENCH, OBJ_SMALLBENCH, OBJ_PILLARBLOCK, OBJ_PILLAR
};

enum POS //위치
{
};

//타일 구조체
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};


//이미지 타일 구조체
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;

	int objFrameX1;
	int objFrameY1;

	int objFrameX2;
	int objFrameY2;

	int objFrameX3;
	int objFrameY3;

	int objFrameX4;
	int objFrameY4;

	int objFrameX5;
	int objFrameY5;

	int objFrameX6;
	int objFrameY6;

	int objFrameX7;
	int objFrameY7;

	int objFrameX8;
	int objFrameY8;

	int objFrameX9;
	int objFrameY9;

	int objFrameX10;
	int objFrameY10;

	int objFrameX11;
	int objFrameY11;

	int objFrameX12;
	int objFrameY12;
};

//현재 타일 구조체
struct tagCurrentTile
{
	int x;
	int y;

	int x1;
	int y1;

	int x2;
	int y2;

	int x3;
	int y3;

	int x4;
	int y4;

	int x5;
	int y5;

	int x6;
	int y6;

	int x7;
	int y7;

	int x8;
	int y8;

	int x9;
	int y9;

	int x10;
	int y10;

	int x11;
	int y11;

	int x12;
	int y12;
};

struct tagOBJAttribute  //몇 번 충돌시 파괴 관련 구조체
{
	int strengh;		//내구도
};