#pragma once

#define TILESIZE 32 //���� ȭ�� Ÿ�� ������
#define TILEX 100//����ȭ�� Ÿ�� X�� ����  
#define TILEY 100	//����ȭ�� Ÿ�� Y�� ����

#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//ȭ�� ������ �̹��� Ÿ�� ����
#define SAMPLETILEX 24
#define SAMPLETILEY 10

//�Ӽ� ���� ����(�̵� ���� ����)
#define ATTR_UNMOVABLE 0x00000001
#define ATTR_POSITION 0x00000002

enum TERRAIN   //����
{
	TR_NULL, TR_FLOOR, TR_WALL, TR_DROP
};
enum OBJECT //������Ʈ
{
	OBJ_NONE, OBJ_STATUEBLOCK, OBJ_STATUE, OBJ_BIGBENCH, OBJ_SMALLBENCH, OBJ_PILLARBLOCK, OBJ_PILLAR
};

enum POS //��ġ
{
};

//Ÿ�� ����ü
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


//�̹��� Ÿ�� ����ü
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

//���� Ÿ�� ����ü
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

struct tagOBJAttribute  //�� �� �浹�� �ı� ���� ����ü
{
	int strengh;		//������
};