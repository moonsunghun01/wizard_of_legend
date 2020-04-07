#pragma once
#include "ghoul.h"
#include "golem.h"
#include "lancer.h"

#include "collisionRc.h" 
#include "gameNode.h" 
#include "coin.h"
#include "bossSkill.h"
#include "Boss.h"

class enemyManager : public gameNode
{

private:

	coin* _coin;

	vector<enemy*>  _vMinion;
	vector<enemy*>::iterator _viMinion;

	vector<coin*> _vCoin;

	enemy* _middleBoss;
	enemy* _boss;

	ENEMYTYPE _enemyType;

	//테스트용
	ghoul* _ghoul;
	golem* _golem;
	lancer* _lancer;

	collisionRc* _collisionRc;

	int _randCoin;
	int _randCoinAmount;

	//test
	bool _isCollision;
	bool _isLeftCollision;
	bool _isRightCollision;
	bool _isTopCollision;
	bool _isBottomCollision;


	//boss
	Boss* _iceBoss;
	
	float _bossSceneDeltaTime;
	int _bossSkillTerm;
	int _bossSkillTime;

	int _bossFrameX;
	int _bossFrameY;

	int _bossMoveCount;
	int _bossMoveAngle;

	bossSkill* _bossSkill;

	vector<bossSkill*> _vBossSkill;

	int _bossSkillCount;

	RECT _tempRc1;
	RECT _tempRc2;
	RECT _tempRc3;
	RECT _tempRc4;

	bool _isBossScene;

	int _skillNum;
	bool _isBossSkill;
	int _patternCount;

	bool _skillDarkBall;
	int _darkBallCount;
	int _skillStartTime;

	bool _isStart;


public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	HRESULT init(collisionRc* _collisionRc);
	void release();
	void update();
	void render();

public:
	//minion
	void createMonster(int x, int y, int ghoulAmount, int golemAmount, int lancerAmount);
	vector<enemy*> getVectorMinion() { return _vMinion; }

	void monsterDeadCheck(int arrNum);

	void monsterMoveCollision(int arrNum);
	void monsterCollision(int arrNum);

	void coinDestroy();
	bool dropCoin();

	void setIsBossScene(bool isBossScene) { _isBossScene = isBossScene; }
	bool getIsBossScene() { return _isBossScene; }


	vector<enemy*> getVMinion() { return _vMinion; }

	Boss* getBoss() { return _iceBoss; }



public:
	//boss
	void moveBoss();
};