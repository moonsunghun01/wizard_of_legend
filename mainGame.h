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

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�


	
};

