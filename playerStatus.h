#pragma once
#include "gameNode.h"
#include "item.h"
class playerStatus : public gameNode
{
private:
	image* _playerStatusImage;
	RECT _playerStatusRc;

	item* _item;
	vector<TAGITEMINFO> _vItem;

	RECT _weaponRc;
	RECT _armorRc;
	RECT _potionRc;

	RECT _lButtonSkillRc;
	RECT _dashSkillRc;
	RECT _rButtonSkillRc;
	RECT _qButtonSkillRc;
	RECT _eButtonSkillRc;
	RECT _rrButtonSkillRc;

	char _str[128];

public :
	HRESULT init();
	void release();
	void update();
	void render();

	RECT getWeaponRc() { return _weaponRc; }
	void setWeaponRc(RECT weaponRc) { _weaponRc = weaponRc; }

	RECT getArmorRc() { return _armorRc; }
	void setArmorRc(RECT armorRc) { _armorRc = armorRc; }
	
	RECT getPotionRc() { return _potionRc; }
	void setPotionRc(RECT potionRc) { _potionRc = potionRc; }

	RECT getLButtonSkillRc() { return _lButtonSkillRc; }
	RECT getDashSkillRc() { return _dashSkillRc; }
	RECT getRButtonSkillRc() { return _rButtonSkillRc; }
	RECT getQButtonSkillRc() { return _qButtonSkillRc; }
	RECT getEButtonSkillRc() { return _eButtonSkillRc; }
	RECT getRRButtonSkillRc() { return _rrButtonSkillRc; }
};

