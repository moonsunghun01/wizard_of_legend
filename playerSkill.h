#pragma once
#include "gameNode.h"

// �ɸ��� ��ų ����
struct tagSkill
{
	image* skillImage;		// ��ų �̹��� 
	RECT skillRc;			// ��ų ����
	float skillDamage;		// ��ų ������

	float skillCoolTime;	// ��ų ��Ÿ��

	int skillIndex;			// ��ų �����ӿ� �̹��� �ε���
	int skillCount;			// ��ų �����ӿ� ī��Ʈ

	int moveCount;			// �뽬�� ī��Ʈ

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

	// ��Ŭ�� ����
	image* _castingCircle;
	int _castingCircleFrameX;

	// ���߿� ����
	bool _isExplosion;
	image* _explosion;
	int _explosionCount;
	int _explosionFrameX;
	
	// ����� ����
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

