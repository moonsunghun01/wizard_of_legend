#pragma once
#include "enemy.h"
#include "collisionRc.h" 


class Boss : public enemy
{
private:

	ENEMYMOVESTATE _enemyMoveState;
	collisionRc* _collisionRc;

	image* _bossImage; //보스 이미지
	RECT _bossRc;


	int _bossHp;
	int _bossCurrentHp;
	int _bossSpeed;
	int _bossAtk;
	float _bossAngle;

	POINT _center;

	int _currentFrameX;
	int _currentFrameY;

	float _changeX;
	float _changeY;

	int _count;

	float _bossDeltaTime;

	bool _isStart;
	bool _isBossLive;
	float _bossMoveAngle;

	int _pointX;
	int _pointY;

	bool _isAttach;
	int _patternNum;

	//hpBar
	image* _bossHpBarImage;
	image* _bossHpBarBackgroundImage;
	RECT _bossHpRc;
	float _bossHpWidth;
	image* _bossHpBarLeft;
	image* _bossHpBarRight;

	bool _isWallCollision;

	bool _isBeHit;

	int _hitTimeCount;

	bool _isHurricaneStart;


	bool _iceBossHurricaneAnimation;
	bool _iceBossMove;
	bool _iceBossDarkBall;
	bool _iceBossIdle;
	int _bossIdleCount;
	int _bossHurricaneCount;
	int _bossDarkBallCount;
	int _bossReadyCount;

	bool _iceBossBreakTime;

	int _darkBallTime;

	bool _iceBossDarkExplosion;

	bool _isBattleStart;
	bool _isIceBossReady;

	bool _isBossMove;

	RECT _bossCollisionRc;

	bool _isIceBossDarkExplosion;

public:
	Boss();
	~Boss();
	HRESULT init(collisionRc* _collisionRc);
	HRESULT init();
	void release();
	void update();
	void render();

	image* getBossImage() { return _bossImage; }
	void setBossImage(image* bossIamge) { _bossImage = bossIamge; }

	RECT getBossRc() { return _bossRc; }
	void setBossRc(RECT bossRc) { _bossRc = bossRc; }

	int getBossSpeed() { return _bossSpeed; }
	void setBossSpeed(int bossSpeed) { _bossSpeed = bossSpeed; }

	int getBossCurrentHp() { return _bossCurrentHp; }
	void setBossCurrentHp(int bossCurrentHp) { _bossCurrentHp = bossCurrentHp; }

	bool bossWallCollision();

	bool getIsBossLive() { return _isBossLive; }



	void animation();

	float getBossDeltaTime() { return _bossDeltaTime; }

	void bossMovePatternSetting(int patternNum);

	void bossPatternMove();

	void setBossState(ENEMYMOVESTATE enemyMoveState) { _enemyMoveState = enemyMoveState; }

	void setIsAttach(bool isAttach) { _isAttach = isAttach; }

	void beHit();


	bool getIsBeHit() { return _isBeHit; }
	void setIsBeHit(bool isBeHit) { _isBeHit = isBeHit; }

	bool getIsHurricaneStart() { return _isHurricaneStart; }
	void setIsHurricaneStart(bool isHurricaneStart) { _isHurricaneStart = isHurricaneStart; }

	bool getBossWallCollision() { return _isWallCollision; }

	void setBossWallCollision(bool isWallCollision) { _isWallCollision = isWallCollision; }

	bool getIceBossHurricaneAnimation() { return _iceBossHurricaneAnimation; }
	void setIceBossHurricaneAnimation(bool iceBossHurricaneAnimation) { _iceBossHurricaneAnimation = iceBossHurricaneAnimation; }


	bool getIceBossMove() { return _iceBossMove; }
	void setIceBossMove(bool iceBossMove) { _iceBossMove = iceBossMove; }

	bool getIceBossDarkBall() { return _iceBossDarkBall; }
	void setIceBossDarkBall(bool iceBossDarkBall) { _iceBossDarkBall = iceBossDarkBall; }

	bool getIceBossIdle() { return _iceBossIdle; }
	void setIceBossIdle(bool iceBossIdle) { _iceBossIdle = iceBossIdle; }

	void setCurrentFrameX(int currentFrameX) { _currentFrameX = currentFrameX; }
	void setCurrentFrameY(int currentFrameY) { _currentFrameY = currentFrameY; }

	void setIceBossBreakTime(int iceBossBreakTime) { _iceBossBreakTime = iceBossBreakTime; }
	bool getIceBossBreakTime() { return _iceBossBreakTime; }


	void setIceBossDarkExplosion(bool iceBossDarkExplosion) { _iceBossDarkExplosion = iceBossDarkExplosion; }
	bool getIceBossDarkExplosion() { return _iceBossDarkExplosion; }

	bool getIsBattleStart() {
		return _isBattleStart;
	}

	void setIsBattleStart(bool isBattleStart) { _isBattleStart = isBattleStart; }

	void setIsIceBossReady(bool isIceBossReady) { _isIceBossReady = isIceBossReady; }
	bool getIsIceBossReady() { return _isIceBossReady; }

	void setIsIceBossMove(bool isBossMove) { _isBossMove = isBossMove; }
	bool getIsIceBossMove() { return _isBossMove; }

	void setIsIceBossDarkExplosion(bool isIceBossDarkExplosion) { _isIceBossDarkExplosion = isIceBossDarkExplosion; }
	bool getIsIceBossDarkExplosion() { return _isIceBossDarkExplosion; }

	RECT getBossCollisionRc() { return _bossCollisionRc; }
};