#pragma once
#include "gameNode.h"
class UI : public gameNode
{
private:
	image* _statusButton;
	image* _potionButton;
	image* _1Button;

	image* _skillUI;

	image* _playerFace;
	image* _playerHp;
	RECT _playerHpRc;
	float _playerHpWight;

	image* _lButtonSkillCoolTime;
	RECT _lButtonSkillCoolTimeRc;

	image* _dashSkillCoolTime;
	RECT _dashSkillCoolTimeRc;

	image* _rButtonSkillCoolTime;
	RECT _rButtonSkillCoolTimeRc;

	image* _qButtonSkillCoolTime;
	RECT _qButtonSkillCoolTimeRc;

	image* _eButtonSkillCoolTime;
	RECT _eButtonSkillCoolTimeRc;
	 
	image* _rrButtonSkillCoolTime;
	RECT _rrButtonSkillCoolTimeRc;

	image* _potionButtonCoolTime;
	RECT _potionButtonCoolTimeRc;

	float _lButtonSkillCoolTimeCount;
	float _dashSkillCoolTimeCount;
	float _rButtonSkillCoolTimeCount;
	float _qButtonSkillCoolTimeCount;
	float _eButtonSkillCoolTimeCount;
	float _rrButtonSkillCoolTimeCount;
	float _potionButtonCoolTimeCount;
	
	float _lButtonSkillHeight = 38;
	float _dashSkillHeight = 38;
	float _rButtonSkillHeight = 38;
	float _qButtonSkillHeight = 38;
	float _eButtonSkillHeight = 38;
	float _rrButtonSkillHeight = 38;
	float _potionButtonHeight = 38;

	char _str[128];
public:
	HRESULT init();
	void release();
	void update();
	void render();
};

