#pragma once
#include "gameNode.h"
#include "Boss.h"
#include "collisionRc.h" 

enum SKILLENUM
{
	DARKBALL,
	HURRICANE,
	MARIONETTE,
	DARKEXPLOSION,
};

struct tagBossSkill
{
	image* bossSkillImage;
	RECT bossSkillRc;
	RECT bossSkillCollisionRc;

	SKILLENUM skillEnum;

	float skillCoolTime;	// 스킬 쿨타임

	int skillIndex = 0;			// 스킬 프레임용 이미지 인덱스
	int skillCount = 0;			// 스킬 프레임용 카운트 

	int currentFrameX = 0;
	int currentFrameY = 0;

	float skillLifeTime;

	float bossSkillAngle;

	bool isActive;
	bool isLive;
	bool isCollisionErase;

	float bossSkillActiveTime;
	int count;
	BYTE alpha;

	int hitCount;


};
class bossSkill : public gameNode
{
private:
	Boss* _boss;

	collisionRc* _collisionRc;

	tagBossSkill _bossSkill;
	vector<tagBossSkill> _vBossSkill;

	int _skillIndex;			// 스킬 프레임용 이미지 인덱스
	int _skillCount;			// 스킬 프레임용 카운트

	float _skillAngle;

	int _activeSkillNum;

	bool _bossSkillActive;

	float _bossSkillActiveTime;



	bool _isLive;
	bool _isDead;
	bool _isErase;

	bool _isSkillActive;

	bool _isMarionetteOn;

	bool _isOn;

	////
	int i;
	animation* _marionetteEffect[3];

	image* _darkDollImage; //스킬 어둠인형(마리오네트) 이미지
	image* _darkBombImage; //스킬 어둠폭탄 이미지
	RECT _darkBombRc;
	RECT _marionetteRc;


public:
	HRESULT init(Boss* boss, collisionRc* collisionRc);
	void release();
	void update();
	void render();

	void bossSkillAnimation();

	void skillDeadCheck();

	tagBossSkill getBossSKill() { return _bossSkill; }
	void setBossSkill(tagBossSkill bossSkill) { _bossSkill = bossSkill; }

	RECT getBossSKillRc() { return _bossSkill.bossSkillRc; }
	void setBossSkillRc(RECT bossSkillRc) { _bossSkill.bossSkillRc = bossSkillRc; }

	float getBossSKillAngle() { return _bossSkill.bossSkillAngle; }
	void setBossSkillAngle(float bossSkillAngle) { _bossSkill.bossSkillAngle = bossSkillAngle; }

	float getSkillAngle() { return _skillAngle; }
	void setSkillAngle(float skillAngle) { _skillAngle = skillAngle; }

	int getActiveSkillNum() { return _activeSkillNum; }
	void setActiveSkillNum(int activeSkillNum) { _activeSkillNum = activeSkillNum; }

	float getSkillLifeTime() { return _bossSkill.skillLifeTime; }

	float getBossSkillActiveTime() { return _bossSkillActiveTime; }
	void setBossSkillActiveTime(float bossSkillActiveTime) { _bossSkillActiveTime = bossSkillActiveTime; }

	bool getIsErase() { return _isErase; }

	void setIsActive(bool isActive) { _bossSkill.isActive = isActive; }

	void setDeltaTime(float bossSkillActiveTime) { _bossSkillActiveTime = bossSkillActiveTime; }
	void setIsDead(bool isDead) { _isDead = isDead; }
	bool getIsDead() { return _isDead; }

	void skillSetting(int activeSkillNum, float x, float y);

	void skillMove();
	void skillLiveCheck();

	float skillWallCollision(tagBossSkill bossSkill);

	vector<tagBossSkill> getVBossSkill() { return _vBossSkill; }


	bool getIsSkillActive() { return _isSkillActive; }
	void setIsSkillActive(bool isSkillActive) { _isSkillActive = isSkillActive; }


	bool getIsMarionetteOn() { return _isMarionetteOn; }

	void setIsMarionetteOn(bool isMarionette) { _isMarionetteOn = isMarionette; }


	void setIsOn(bool isOn) { _isOn = isOn; }
};

