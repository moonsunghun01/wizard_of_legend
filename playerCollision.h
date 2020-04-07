#pragma once
#include "gameNode.h"
#include "testMapTool.h"


enum PLAYERDIRECTION
{
	PLAYERDIRECTION_LEFT,
	PLAYERDIRECTION_UP,
	PLAYERDIRECTION_RIGHT,
	PLAYERDIRECTION_DOWN
};

class playerCollision : public gameNode
{
private:
	image* _image;
	testMapTool* _map;
	PLAYERDIRECTION _direction;
	int _frameX, _frameY;
	float _speed;
	float _x, _y;
	int tileX, tileY, tileX1, tileY1, tileX2, tileY2, tileX3, tileY3, tileX4, tileY4;	//플레이어가 밟고 있는 타일 넘버 

	RECT _rc;
	RECT sampleRc;

	int _frameCount;
public:
	playerCollision();
	~playerCollision();

	HRESULT init();
	void release();
	void update();
	void render();


	void setPlayerPosition();
	void playerMove();

};

