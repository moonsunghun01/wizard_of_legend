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
	ITEM itemKind;	//����
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
	vector<TAGITEMINFO> getEquipInfo() { return _vItem; } //������ ���� ��������
	vector<SKILLBOOK> getSkillInfo() { return _vSkill; } //��ų ���� ��������
	void setEquipInfo(vector<TAGITEMINFO> vItem) { _vItem = vItem; } //������ ���� ����
	void setEquipInfo(vector<SKILLBOOK> vSkill) { _vSkill = vSkill; } //��ų ���� ����
	RECT getItemRC(int num) { return _vItem.at(num).itemRc; }//������ RC ��������
	void setItemRC(int num, RECT rc) { _vItem.at(num).itemRc = rc; } //������ RC ����
	RECT getSkillRC(int num) { return _vSkill.at(num).skillRc; }//��ų RC ��������
	void setSkillRC(int num, RECT rc) { _vSkill.at(num).skillRc = rc; } //��ų RC ����

};

