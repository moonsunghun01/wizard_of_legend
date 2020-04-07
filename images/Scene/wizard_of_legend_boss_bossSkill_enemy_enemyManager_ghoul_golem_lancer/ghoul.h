#pragma once
#include "enemy.h" 
class ghoul : public enemy
{
private:
	//��ȯī�� �̹���
	image* _summonImage;
	//��ȯī�� framerender�� ���� ����
	int _summonFrameX;

	//���� �⺻ �̵� framerender�� ���� ����
	int _currentFrameX;
	int _currentFrameY;

	ghoul* _ghoul;
	RECT _ghoulRc;

	//framerender�� ����
	int _count;
	int _index;
	int _attackCount;

	//������ ����
	bool _isAtkRange;
	bool _isChasingRange;
	bool _isDead;
	bool _isLeft;
	bool _isSummon;
	float _distance;
	float _angle;

	float _deltaTime;

	bool _isHitHp;


	//�浹�� RECT
	RECT _collisionRc;
	RECT _ghoulMoveCollisionRc;

	image* _attackImage;
	float _ghoulAttackCoolTime;
	float _ghoulAttackImageCoolTime;
	RECT _ghoulAttackRc;

	int _attackFrameX;
	int _attackFrameY;

	int _hitFrameX;
	int _hitFrameY;
	
	bool _isAttack;

	bool _isSlashImage;

	vector<RECT> _vAttackRc;




public:
	ghoul();
	~ghoul();


	HRESULT init();
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update();
	void render();

	void move();
	void dead();
	void summon();
	RECT getGhoulMoveCollision() { return _ghoulMoveCollisionRc; }

	void attack();

	void attackAnimation();

	void beHit();

	void hitAnimation();
};

