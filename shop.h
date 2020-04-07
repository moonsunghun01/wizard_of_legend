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

	image* _matImage; //돗자리 이미지	
	image* _explanationImage;  //설명백 이미지
	image* _soldOutImage; //물건이 다팔릴 경우 이미지
	image* _noMoney; // 금액 부족 이미지
	image* _buy; //구매시 이모션 이미지

	RECT _weaponRc; //무기아이템 충돌 관련 확인 렉트
	RECT _armorRc; //방어구아이템 충돌 관련 확인 렉트
	RECT _potionRc; //표션아이템 충돌 관련 확인 렉트
	RECT _skillRc; //스킬북아이템 충돌 관련 확인 렉트
	RECT _explanationRc; //설명란 관련 확인 렉트
	RECT _matRc; //돗자리 관련 확인 렉트
	RECT _weaponSoldOutRc; //무기 품절시 관련 확인 렉트
	RECT _armorSoldOutRc;  //방어구 품절시 관련 확인 렉트
	RECT _potionSoldOutRc; //포션 품절시 관련 확인 렉트
	RECT _skillSoldOutRc; //스킬 품절시 관련 확인 렉트
	RECT _buyRc; //구매 이모션 관련 렉트
	RECT _noMoneyRc; //금액 부족 이모션 관련 렉트

	bool _isMouseUp; //마우스가 위에 있는지
	bool _isWeaponSoldOut; //무기가 다팔렸는지
	bool _isArmorSoldOut; //방어구가 다팔렸는지
	bool _isPotionSoldOut; //포션이 다팔렸는지
	bool _isSkillSoldOut;  //스킬북이 다팔렸는지
	bool _isItem; //아이템 관련 확인(벡터 삭제 용도)
	bool _isSkill; //스킬북인지 확인(벡터 삭제 용도)
	bool _isBuyDestroy; //구매이미지 소멸 관련 확인
	bool _isNoMoneyDestroy; //금액 부족 이미지 소멸 관련 확인
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

