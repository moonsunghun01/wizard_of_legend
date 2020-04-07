#pragma once
#include "gameNode.h"
#include "madeTestMapTool.h"

enum SECONDPLAYERDIRECTION
{
	SECONDPLAYERDIRECTION_LEFT,
	SECONDPLAYERDIRECTION_UP,
	SECONDPLAYERDIRECTION_RIGHT,
	SECONDPLAYERDIRECTION_DOWN
};

class madePlayerCollision : public gameNode
{
private:
	image* _image;
	madeTestMapTool* _map;
	SECONDPLAYERDIRECTION _direction;

	int _frameX, _frameY;
	float _speed;
	float _x, _y;
	int tileX, tileY, tileX1, tileY1, tileX2, tileY2, tileX3, tileY3, tileX4, tileY4;	//�÷��̾ ��� �ִ� Ÿ�� �ѹ� 

	RECT _rc;
	RECT sampleRc;

	int _frameCount;
public:
	madePlayerCollision();
	~madePlayerCollision();

	HRESULT init();
	void release();
	void update();
	void render();


	void setPlayerPosition();
	void playerMove();

};

