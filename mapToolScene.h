#pragma once
#include"gameNode.h"
#include "mapTool.h"
#include "soundOption.h"
class mapToolScene : public gameNode
{
private:
	mapTool* _mapTool;
	soundOption* _sound;
	float sound;
public:
	mapToolScene();
	~mapToolScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);


};
