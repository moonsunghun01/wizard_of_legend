#pragma once
#include"gameNode.h"
#include "camera.h"

#include "collisionRc.h"


enum ATTRIBUTE
{
	ATTR_NONE,
	ATTR_FIRE,
	ATTR_WATER,
	ATTR_LIGHTNING,
	ATTR_EARTH,
	ATTR_DARK
};

enum ENEMYTYPE
{
	ENEMY_NONE,
	ENEMY_MINION_GHOUL,
	ENEMY_MINION_GOLEM,
	ENEMY_MINION_LANCER,
	ENEMY_MIDDLEBOSS,
	ENEMY_BOSS,
};

enum ENEMYMOVESTATE
{
	ENEMY_MOVE_IDLE,
	ENEMY_MOVE_UP,
	ENEMY_MOVE_DOWN,
	ENEMY_MOVE_LEFT,
	ENEMY_MOVE_RIGHT,
	ENEMY_MOVE_ATTACK,
	ENEMY_MOVE_HITTED,
	ENEMY_MOVE_COOLTIME,
	ENEMY_MOVE_DASH,
};


class enemy : public gameNode
{
private:
	int _hp;
	int _atk;
	int _moveSpeed;
	int _atkFrequency;
	float _angle;
	bool _isHit;
	bool _isDead;
	image* _enemyImage;
	RECT _enemyRc;
	ATTRIBUTE _attribute;

	ENEMYTYPE _enemyType;

	//RECT _collisionRc;

	//이동 체크
	RECT _moveCollisionRc;

	//
	collisionRc* _collisionRc;
	bool _isCollision;
	bool _isErase;

	RECT _attackRc;

	float _attackCoolTime;

	bool _isLeftCollision;
	bool _isRightCollision;
	bool _isTopCollision;
	bool _isBottomCollision;

	bool _monsterCollision;



public:
	enemy();
	~enemy();
	HRESULT init();

	HRESULT init(int x, int y) { _enemyImage->setX(x); _enemyImage->setY(y); return S_OK; }

	void update();

	void setAngle(float angle) { _angle = angle; }
	float getEnemyAngle() { return _angle; }

	int getHp() { return _hp; }
	void setHp(int hp) { _hp = hp; }


	bool getIsHit() { return _isHit; }
	void setIsHit(bool isHit) { _isHit = isHit; }

	bool getIsDead() { return _isDead; }
	void setIsDead(bool isDead) { _isDead = isDead; }

	void setAtk(int atk) { _atk = atk; }
	int getAtk() { return _atk; }

	void setAtkFrequency(int atkFrequency) { _atkFrequency = atkFrequency; }

	image* getEnemyImage() { return _enemyImage; }
	void setEnemyImage(image* enemyImage) { _enemyImage = enemyImage; }

	RECT getEnemyRc() { return _enemyRc; }
	void setEnemyRc(RECT enemyRc) { _enemyRc = enemyRc; }


	ENEMYTYPE getEnemyType() { return _enemyType; }
	void setEnemyType(ENEMYTYPE enemyType) { _enemyType = enemyType; }

	ATTRIBUTE getAttribute() { return _attribute; }
	void setAttribute(ATTRIBUTE attribute) { _attribute = attribute; }


	void setMoveCollisionRc(RECT moveCollisionRc) { _moveCollisionRc = moveCollisionRc; }
	RECT getMoveCollisionRc() { return _moveCollisionRc; }


	void setIsCollision(bool isCollision) { _isCollision = isCollision; }
	bool getIsCollision() { return _isCollision; }

	void setIsErase(bool isErase) { _isErase = isErase; }
	bool getIsErase() { return _isErase; }

	RECT getAttackRc() { return _attackRc; }
	void setAttackRc(RECT attackRc) { _attackRc = attackRc; }

	float getAttackCoolTime() { return _attackCoolTime; }
	void setAttackCoolTime(float attackCoolTime) { _attackCoolTime = attackCoolTime; }



	bool getIsLeftCollision() { return _isLeftCollision; }
	bool getIsRightCollision() { return _isRightCollision; }
	bool getIsTopCollision() { return _isTopCollision; }
	bool getIsBottomCollision() { return _isBottomCollision; }

	void setIsLeftCollision(bool isLeftCollision) { _isLeftCollision = isLeftCollision; }
	void setIsRightCollision(bool isRightCollision) { _isRightCollision = isRightCollision; }
	void setIsTopCollision(bool isTopCollision) { _isTopCollision = isTopCollision; }
	void setIsBottomCollision(bool isBottomCollision) { _isBottomCollision = isBottomCollision; }


	void setEnemyX(int x) { _enemyRc.left += x;  _enemyRc.right += x; }

	void setEnemyY(int y) { _enemyRc.top += y;  _enemyRc.bottom += y; }

	void setMonsterCollision(bool monsterCollision) { _monsterCollision = monsterCollision; }
	bool getMonsterCollision() { return _monsterCollision; } 
};

