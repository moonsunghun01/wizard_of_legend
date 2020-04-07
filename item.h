#pragma once

enum ITEM
{
	item_Empty,
	item_Armor,
	item_Weapon,
	item_potion,
	item_Skill,
	item_dashSkill,
	item_SoldOut
};

struct TAGITEMINFO
{
	ITEM itemKind;	//종류
	image* image;
	const char* name;
	string description;
	int hp;
	int speed;
	int att;
	int def;
	int price;
	int count;
	RECT itemRc;

	float itemCoolTime;
	bool isActive;
};

struct SKILLBOOK
{
	ITEM itemKind;
	image* image;
	const char* name;
	string description;
	int count;
	int price;
	int skillNumber;
	int skillMotionNum;
	RECT skillRc;

	float skillCoolTime;
	bool isActive;
	int skillDamege;
};

class item
{
private:
	vector <TAGITEMINFO> _vItem;
	vector <SKILLBOOK> _vSkill;

	vector <TAGITEMINFO>::iterator _viItem;
	vector <SKILLBOOK>::iterator _viSkill;
public:
	HRESULT init();
	vector<TAGITEMINFO> getEquipInfo() { return _vItem; } //아이템 벡터 가져오기
	vector<SKILLBOOK> getSkillInfo() { return _vSkill; } //스킬 벡터 가져오기
	void setEquipInfo(vector<TAGITEMINFO> vItem) { _vItem = vItem; } //아이템 벡터 세팅
	void setEquipInfo(vector<SKILLBOOK> vSkill) { _vSkill = vSkill; } //스킬 벡터 세팅
	RECT getItemRC(int num) { return _vItem.at(num).itemRc; }//아이템 RC 가져오기
	void setItemRC(int num, RECT rc) { _vItem.at(num).itemRc = rc; } //아이템 RC 변경
	RECT getSkillRC(int num) { return _vSkill.at(num).skillRc; }//스킬 RC 가져오기
	void setSkillRC(int num, RECT rc) { _vSkill.at(num).skillRc = rc; } //스킬 RC 변경

};

