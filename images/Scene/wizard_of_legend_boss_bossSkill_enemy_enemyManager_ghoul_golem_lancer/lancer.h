#pragma once
#include "enemy.h"
class lancer : public enemy
{
private:
	lancer* _lancer;
	
	//소환카드 이미지
	image* _summonImage;
	//소환카드 framerender를 위한 정보
	int _summonFrameX;

	//구울 기본 이동 framerender를 위한 정보
	int _currentFrameX;
	int _currentFrameY;
	int _x;
	int _y;

	RECT _lancerRc;

	//framerender용 변구
	int _count;
	int _index;
	int _attackCount;

	//감지용 변수
	bool _isAtkRange;
	bool _isChasingRange;
	bool _isDead;
	bool _isLeft;
	bool _isSummon;
	float _distance;
	float _angle;

	float _deltaTime;

	bool _isHitHp;


	//충돌용 RECT
	RECT _collisionRc;
	RECT _lancerMoveCollisionRc;

	//test
	image* _attackImage;
	float _lancerAttackCoolTime;
	float _lancerAttackImageCoolTime;
	RECT _lancerAttackRc;

	int _attackFrameX;
	int _attackFrameY;

	int _hitFrameX;
	int _hitFrameY;


	bool _isAttack;

	bool _isSlashImage;

	vector<RECT> _vAttackRc;
public:
	lancer();
	~lancer();

	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update();
	void render();

	void move();
	void dead();
	void summon();
	RECT getLancerMoveCollision() { return _lancerMoveCollisionRc; }

	void attack();

	void attackAnimation();

	void beHit();

	void hitAnimation();

};

