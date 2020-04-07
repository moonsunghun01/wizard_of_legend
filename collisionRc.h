#pragma once 
#include "gameNode.h"

enum RC_KIND
{
	RC_WALL,
	RC_OBSTACLE
};
struct tagCollisionRc
{
	RECT rc;
	int index;
	RC_KIND rcKind = RC_WALL;
};


class collisionRc : public gameNode
{
private:

	tagCollisionRc _tagCollisionRc[57];
	vector<tagCollisionRc> _vCollsionRc;

	bool _isBossMap;
	//렉트 확인용 렌더 변수
	int num;
public:
	collisionRc();
	~collisionRc();

	HRESULT init();
	void release();
	void update();
	void render();

	RECT getCollisionRc(int i) { return _tagCollisionRc[i].rc; }
	RC_KIND getCollisionRcKind(int i) { return _tagCollisionRc[i].rcKind; }

	void setIsBossMap(bool isBossMap) { _isBossMap = isBossMap; }




};

