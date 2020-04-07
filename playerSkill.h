#pragma once
#include "gameNode.h"

// 케릭터 스킬 정보
struct tagSkill
{
	image* skillImage;		// 스킬 이미지 
	RECT skillRc;			// 스킬 상자
	float skillDamage;		// 스킬 데미지

	float skillCoolTime;	// 스킬 쿨타임

	int skillIndex;			// 스킬 프레임용 이미지 인덱스
	int skillCount;			// 스킬 프레임용 카운트

	int moveCount;			// 대쉬용 카운트

	int currentFrameX;
	int currentFrameY;
};
class playerSkill : gameNode
{
private:
		
	tagSkill _tagSkill;

	vector<tagSkill> _vSkill; 
	vector<tagSkill> _vBuffSkill; 

	int _playerAnimationCount;
	int _playerAnimationIndex;

	bool _isSkillActive;
	bool _isPlayerSkillActive;
	float _skillAngle;

	int _skillNum;
	int _motionNum;

	int _delayCount;

	// 서클용 변수
	image* _castingCircle;
	int _castingCircleFrameX;

	// 폭발용 변수
	bool _isExplosion;
	image* _explosion;
	int _explosionCount;
	int _explosionFrameX;
	
	// 피즈궁 변수
	RECT _sharkTargetRc; 
	POINT _sharkTargetPt; 
	bool _isStartShark;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void skillAnimation();
	void playerSkillAnimadtion();

	float getSkillAngle() { return _skillAngle; }
	void setSkillAngle(float skillAngle) { _skillAngle = skillAngle; }

	bool getIsSkillActive() { return _isSkillActive; }
	void setIsSkillActive(bool isSkillActive) { _isSkillActive = isSkillActive; }

	bool getIsPlayerSkillActive() { return _isPlayerSkillActive; }
	void setIsPlayerSkillActive(bool isPlayerSkillActive) { _isPlayerSkillActive = isPlayerSkillActive; }

	void skillSetting(int skillNum,int motionNum);
	void skillMove();

	void sharkSetting();

	vector<tagSkill> getPlayerSkill() { return _vSkill; }

	RECT getPlayerSkillRc(int arrNum) { return _vSkill.at(arrNum).skillRc; }  

	int getSkillNum() { return _skillNum; }
	void setSkillNum(int skillNum) { _skillNum = skillNum; }

	RECT getSharkTargetRc() { return _sharkTargetRc; }
	void setSharkTargetRc(RECT sharkTargetRc) { _sharkTargetRc = sharkTargetRc; }

	POINT getSharkTargetPt() { return _sharkTargetPt; }
	void setSharkTargetPt(POINT sharkTargetPt) { _sharkTargetPt = sharkTargetPt; }

	bool getIsStartShark() { return _isStartShark; }
	void setIsStartShark(bool isStartShark) { _isStartShark = isStartShark; }

};

