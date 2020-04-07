#pragma once
#include "gameNode.h"

class coin : public gameNode
{
private:
	image* _coinImage;

	coin* _coin;

	int _price;

	RECT _coinRc;
	RECT _collisionRc;

	int _currentFrameX;
	int _currentFrameY;
	int _count;

	int _x;
	int _y;

public:
	coin();
	~coin();

	HRESULT init();

	HRESULT init(const char* imageName, POINT position);
	void release();
	void update();
	void render();
	void animation();
	void move();


	RECT getCoinRc() { return _coinRc; }
	int getPrice() { return _price; }

	RECT getCoinCollisionRc() { return _collisionRc; }
};

