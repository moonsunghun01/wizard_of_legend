#pragma once
#include"gameNode.h"

#include"playerManager.h"
#include "mainScene.h"
#include "fireScene.h"
#include "bossScene.h"
#include "soundOption.h"
#include "maptoolScene.h" 
#include "testMapScene.h"  
#include "testSecondMapScene.h"
#include "testMapToolSelect.h"

class mainGame :  public gameNode
{
private:
	playerManager* _playerManager;
public:
	mainGame();
	~mainGame();

	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳


	
};

