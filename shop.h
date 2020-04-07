#pragma once
#include "gameNode.h"
#include "item.h"
#include "npc.h"
class shop : public gameNode
{
private:
	npc* _npc;
	item* _randItem;

	int _skillSell;
	int _weaponSell;
	int _armorSell;
	int _potionSell;
	int _xWeapon;
	int _xArmor;
	int _xPotion;
	int _xSkill;
	int _sell;
	int _yWeapon;
	int _yArmor;
	int _yPotion;
	int _ySkill;

	int _randNumWeapon;
	int _randNumArmor;
	int _randNumPotion;
	int _randNumSkill;
	int _weaponSellCount;
	int _armorSellCount;
	int _potionSellCount;
	int _skillSellCount;
	int _descriptionPositionX;
	int _descriptionPositionY;
	int _destoryCount;
	int _currentFrameX;
	int _currentFrameY;
	int _count;

	image* _matImage; //���ڸ� �̹���	
	image* _explanationImage;  //����� �̹���
	image* _soldOutImage; //������ ���ȸ� ��� �̹���
	image* _noMoney; // �ݾ� ���� �̹���
	image* _buy; //���Ž� �̸�� �̹���

	RECT _weaponRc; //��������� �浹 ���� Ȯ�� ��Ʈ
	RECT _armorRc; //�������� �浹 ���� Ȯ�� ��Ʈ
	RECT _potionRc; //ǥ�Ǿ����� �浹 ���� Ȯ�� ��Ʈ
	RECT _skillRc; //��ų�Ͼ����� �浹 ���� Ȯ�� ��Ʈ
	RECT _explanationRc; //����� ���� Ȯ�� ��Ʈ
	RECT _matRc; //���ڸ� ���� Ȯ�� ��Ʈ
	RECT _weaponSoldOutRc; //���� ǰ���� ���� Ȯ�� ��Ʈ
	RECT _armorSoldOutRc;  //�� ǰ���� ���� Ȯ�� ��Ʈ
	RECT _potionSoldOutRc; //���� ǰ���� ���� Ȯ�� ��Ʈ
	RECT _skillSoldOutRc; //��ų ǰ���� ���� Ȯ�� ��Ʈ
	RECT _buyRc; //���� �̸�� ���� ��Ʈ
	RECT _noMoneyRc; //�ݾ� ���� �̸�� ���� ��Ʈ

	bool _isMouseUp; //���콺�� ���� �ִ���
	bool _isWeaponSoldOut; //���Ⱑ ���ȷȴ���
	bool _isArmorSoldOut; //���� ���ȷȴ���
	bool _isPotionSoldOut; //������ ���ȷȴ���
	bool _isSkillSoldOut;  //��ų���� ���ȷȴ���
	bool _isItem; //������ ���� Ȯ��(���� ���� �뵵)
	bool _isSkill; //��ų������ Ȯ��(���� ���� �뵵)
	bool _isBuyDestroy; //�����̹��� �Ҹ� ���� Ȯ��
	bool _isNoMoneyDestroy; //�ݾ� ���� �̹��� �Ҹ� ���� Ȯ��
	char _str[128];
	string _description;

	bool _isShowItemInfo;

public:
	HRESULT init();
	void release();
	void update();
	void render();
	void buy();
	void removing(int i);
	void position();
	void countTime();
	void motionAnimation();
	void motion();
};

