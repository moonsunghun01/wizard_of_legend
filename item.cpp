#include "stdafx.h"
#include "item.h"

HRESULT item::init()
{

	////////////////////////////////////////////////////////////////////////  장비

	TAGITEMINFO _weapon1;
	_weapon1.itemKind = item_Weapon;
	_weapon1.image = IMAGEMANAGER->addImage("양날도끼", "images/상점/무기/무기1.bmp", 37, 37, true, RGB(255, 0, 255));
	_weapon1.name = "양날도끼";
	_weapon1.description = "무게는 무겁지만 한방이 있는 도끼";
	_weapon1.att = 15;
	_weapon1.def = 0;
	_weapon1.hp = 0;
	_weapon1.speed = 0;
	_weapon1.price = 1000;
	_weapon1.count = 1;
	_weapon1.itemRc = RectMakeCenter(0, 0, _weapon1.image->getWidth(), _weapon1.image->getHeight());
	_vItem.push_back(_weapon1);

	TAGITEMINFO _weapon2;
	_weapon2.itemKind = item_Weapon;
	_weapon2.image = IMAGEMANAGER->addImage("장검", "images/상점/무기/무기3.bmp", 37, 37, true, RGB(255, 0, 255));
	_weapon2.name = "장검";
	_weapon2.description = "평범한 대장간산 장검";
	_weapon2.att = 50;
	_weapon2.def = 0;
	_weapon2.hp = 0;
	_weapon2.speed = 0;
	_weapon2.price = 1500;
	_weapon2.count = 1;
	_weapon2.itemRc = RectMakeCenter(0, 0, _weapon2.image->getWidth(), _weapon2.image->getHeight());
	_vItem.push_back(_weapon2);


	TAGITEMINFO _weapon3;
	_weapon3.itemKind = item_Weapon;
	_weapon3.image = IMAGEMANAGER->addImage("귀도", "images/상점/무기/무기2.bmp", 37, 37, true, RGB(255, 0, 255));
	_weapon3.name = "귀도";
	_weapon3.description = "공격력이 매우 올라가는 귀도";
	_weapon3.att = 150;
	_weapon3.def = 0;
	_weapon3.hp = 0;
	_weapon3.speed = 0;
	_weapon3.price = 2000;
	_weapon3.count = 1;
	_weapon3.itemRc = RectMakeCenter(0, 0, _weapon3.image->getWidth(), _weapon3.image->getHeight());
	_vItem.push_back(_weapon3);


	TAGITEMINFO _armor1;
	_armor1.itemKind = item_Armor;
	_armor1.image = IMAGEMANAGER->addImage("로브", "images/상점/방어구/방어구1.bmp", 37, 37, true, RGB(255, 0, 255));
	_armor1.name = "로브";
	_armor1.description = "천으로 만든 로브이다.";
	_armor1.att = 0;
	_armor1.def = 10;
	_armor1.hp = 0;
	_armor1.speed = 0;
	_armor1.price = 1500;
	_armor1.count = 1;
	_armor1.itemRc = RectMakeCenter(0, 0, _armor1.image->getWidth(), _armor1.image->getHeight());
	_vItem.push_back(_armor1);


	TAGITEMINFO _armor2;
	_armor2.itemKind = item_Armor;
	_armor2.image = IMAGEMANAGER->addImage("갑옷", "images/상점/방어구/방어구2.bmp", 37, 37, true, RGB(255, 0, 255));
	_armor2.name = "갑옷";
	_armor2.description = "방어력은 좋지만 무거워서 속도가 감소 된다.";
	_armor2.att = 0;
	_armor2.def = 50;
	_armor2.hp = 0;
	_armor2.speed = -2;
	_armor2.price = 1800;
	_armor2.count = 1;
	_armor2.itemRc = RectMakeCenter(0, 0, _armor2.image->getWidth(), _armor2.image->getHeight());
	_vItem.push_back(_armor2);


	TAGITEMINFO _armor3;
	_armor3.itemKind = item_Armor;
	_armor3.image = IMAGEMANAGER->addImage("신발", "images/상점/방어구/방어구3.bmp", 37, 37, true, RGB(255, 0, 255));
	_armor3.name = "신발";
	_armor3.description = "방어력은 거의 없지만 속도가 증가한다.";
	_armor3.att = 0;
	_armor3.def = 5;
	_armor3.hp = 0;
	_armor3.speed = 5;
	_armor3.price = 1300;
	_armor3.count = 1;
	_armor3.itemRc = RectMakeCenter(0, 0, _armor3.image->getWidth(), _armor3.image->getHeight());
	_vItem.push_back(_armor3);

	//////////////////////////////////////////////////////////////////////////////////////////////// 포션

	TAGITEMINFO _potion1;
	_potion1.itemKind = item_potion;
	_potion1.image = IMAGEMANAGER->addImage("물약소", "images/상점/포션/물약소.bmp", 37, 37, true, RGB(255, 0, 255));
	_potion1.name = "물약 소";
	_potion1.description = "체력을 10 회복해주는 물약이다.";
	_potion1.att = 0;
	_potion1.def = 0;
	_potion1.hp = 10;
	_potion1.speed = 0;
	_potion1.price = 100;
	_potion1.count = 10;
	_potion1.itemCoolTime = 3;
	_potion1.isActive = false;
	_potion1.itemRc = RectMakeCenter(0, 0, _potion1.image->getWidth(), _potion1.image->getHeight());
	_vItem.push_back(_potion1);


	TAGITEMINFO _potion2;
	_potion2.itemKind = item_potion;
	_potion2.image = IMAGEMANAGER->addImage("물약중", "images/상점/포션/물약중.bmp", 37, 37, true, RGB(255, 0, 255));
	_potion2.name = "물약 중";
	_potion2.description = "체력을 20 회복해주는 물약이다.";
	_potion2.att = 0;
	_potion2.def = 0;
	_potion2.hp = 20;
	_potion2.speed = 0;
	_potion2.price = 300;
	_potion2.count = 10;
	_potion2.itemCoolTime = 4;
	_potion2.isActive = false;
	_potion2.itemRc = RectMakeCenter(0, 0, _potion2.image->getWidth(), _potion2.image->getHeight());
	_vItem.push_back(_potion2);


	TAGITEMINFO _potion3;
	_potion3.itemKind = item_potion;
	_potion3.image = IMAGEMANAGER->addImage("물약대", "images/상점/포션/물약대.bmp", 37, 37, true, RGB(255, 0, 255));
	_potion3.name = "물약 대";
	_potion3.description = "체력을 30 회복해주는 물약이다.";
	_potion3.att = 0;
	_potion3.def = 0;
	_potion3.hp = 30;
	_potion3.speed = 0;
	_potion3.price = 500;
	_potion3.count = 10;
	_potion3.itemCoolTime = 5;
	_potion3.isActive = false;
	_potion3.itemRc = RectMakeCenter(0, 0, _potion3.image->getWidth(), _potion3.image->getHeight());
	_vItem.push_back(_potion3);


	SKILLBOOK _meteorSkill;
	_meteorSkill.itemKind = item_Skill;
	_meteorSkill.image = IMAGEMANAGER->addImage("meteorIcon", "images/skillIcon/meteorIcon.bmp", 40, 38, true, RGB(255, 0, 255));
	_meteorSkill.name = "meteor";
	_meteorSkill.description = "사용자 위치에 강력한 메테오를 소환한다.";
	_meteorSkill.price = 11;
	_meteorSkill.skillNumber = 5;
	_meteorSkill.skillMotionNum = 2;
	_meteorSkill.count = 1;
	_meteorSkill.skillCoolTime = 10;
	_meteorSkill.isActive = false;
	_meteorSkill.skillRc = RectMakeCenter(0, 0, _meteorSkill.image->getWidth(), _meteorSkill.image->getHeight());
	_meteorSkill.skillDamege =10;
	_vSkill.push_back(_meteorSkill); 

	SKILLBOOK _sharkSkill;
	_sharkSkill.itemKind = item_Skill;
	_sharkSkill.image = IMAGEMANAGER->addImage("sharkIcon", "images/skillIcon/sharkIcon.bmp", 38, 38, true, RGB(255, 0, 255));
	_sharkSkill.name = "shark";
	_sharkSkill.description = "밥 먹자";
	_sharkSkill.price = 12;
	_sharkSkill.skillNumber = 6;
	_sharkSkill.skillMotionNum = 1;
	_sharkSkill.count = 1;
	_sharkSkill.skillCoolTime = 3;
	_sharkSkill.isActive = false;
	_sharkSkill.skillDamege = 1;
	_vSkill.push_back(_sharkSkill);

	SKILLBOOK _darkHole;
	_darkHole.itemKind = item_Skill;
	_darkHole.image = IMAGEMANAGER->addImage("blackHoleIcon", "images/skillIcon/blackHoleIcon.bmp", 38, 38, true, RGB(255, 0, 255));
	_darkHole.name = "blackHole";
	_darkHole.description = "어둠 어둠 열매 ";
	_darkHole.price = 12;
	_darkHole.skillNumber = 7;
	_darkHole.skillMotionNum = 1;
	_darkHole.count = 1;
	_darkHole.skillCoolTime = 3;
	_darkHole.isActive = false;
	_darkHole.skillDamege = 1;
	_vSkill.push_back(_darkHole);

	SKILLBOOK _waterCommonSkill;
	_waterCommonSkill.itemKind = item_Skill;
	_waterCommonSkill.image = IMAGEMANAGER->addImage("물근접icon", "images/skillIcon/물근접icon.bmp", 40, 38, true, RGB(255, 0, 255));
	_waterCommonSkill.name = "물근접";
	_waterCommonSkill.description = "가까이에 있는 적을 공격한다";
	_waterCommonSkill.price = 11;
	_waterCommonSkill.skillNumber = 1;
	_waterCommonSkill.skillMotionNum = 1;
	_waterCommonSkill.count = 1;
	_waterCommonSkill.skillCoolTime = 0;
	_waterCommonSkill.isActive = false;
	_waterCommonSkill.skillDamege = 1;
	_waterCommonSkill.skillRc = RectMakeCenter(0, 0, _waterCommonSkill.image->getWidth(), _waterCommonSkill.image->getHeight());

	m_player->setPlayerLButtonSkill(_waterCommonSkill);

	SKILLBOOK _dashCommonSkill;
	_dashCommonSkill.itemKind = item_dashSkill;
	_dashCommonSkill.image = IMAGEMANAGER->addImage("dashIcon", "images/skillIcon/dashIcon.bmp", 40, 38, true, RGB(255, 0, 255));
	_dashCommonSkill.name = "Dash";
	_dashCommonSkill.description = "일반 Dash 스킬";
	_dashCommonSkill.price = 11;
	_dashCommonSkill.skillNumber = 0;
	_dashCommonSkill.skillMotionNum = 1;
	_dashCommonSkill.count = 1;
	_dashCommonSkill.skillCoolTime = 0;  
	_dashCommonSkill.isActive = false; 

	m_player->setPlayerDashSkill(_dashCommonSkill);

	SKILLBOOK _windCutterSkill;
	_windCutterSkill.itemKind = item_Skill;
	_windCutterSkill.image = IMAGEMANAGER->addImage("windCutterIcon", "images/skillIcon/windCutterIcon.bmp", 40, 38, true, RGB(255, 0, 255));
	_windCutterSkill.name = "windCutter";
	_windCutterSkill.description = "사용 후 케릭에게 돌아오는 windCutter";
	_windCutterSkill.price = 11;
	_windCutterSkill.skillNumber = 2;
	_windCutterSkill.skillMotionNum = 1;
	_windCutterSkill.count = 1;
	_windCutterSkill.skillCoolTime = 2;
	_windCutterSkill.isActive = false;
	_windCutterSkill.skillDamege = 1;
	_windCutterSkill.skillRc = RectMakeCenter(0, 0, _windCutterSkill.image->getWidth(), _windCutterSkill.image->getHeight());

	m_player->setPlayerRButtonSkill(_windCutterSkill);

	SKILLBOOK _iceCrystalSkill;
	_iceCrystalSkill.itemKind = item_Skill;
	_iceCrystalSkill.image = IMAGEMANAGER->addImage("iceCrystalIcon", "images/skillIcon/iceCrystalIcon.bmp", 40, 38, true, RGB(255, 0, 255));
	_iceCrystalSkill.name = "iceCrystalIcon";
	_iceCrystalSkill.description = "일직선으로 나가는 iceCrystal";
	_iceCrystalSkill.price = 11;
	_iceCrystalSkill.skillNumber = 3;
	_iceCrystalSkill.skillMotionNum = 1;
	_iceCrystalSkill.count = 1;
	_iceCrystalSkill.skillCoolTime = 3;
	_iceCrystalSkill.isActive = false;
	_iceCrystalSkill.skillDamege = 1;
	_iceCrystalSkill.skillRc = RectMakeCenter(0, 0, _iceCrystalSkill.image->getWidth(), _iceCrystalSkill.image->getHeight());

	m_player->setPlayerQButtonSkill(_iceCrystalSkill);

	SKILLBOOK _lightningShowerSkill;
	_lightningShowerSkill.itemKind = item_Skill;
	_lightningShowerSkill.image = IMAGEMANAGER->addImage("lightningShower", "images/skillIcon/lightningShower.bmp", 40, 38, true, RGB(255, 0, 255));
	_lightningShowerSkill.name = "lightningShower";
	_lightningShowerSkill.description = "사용자 주위에 번개를 떨어트린다.";
	_lightningShowerSkill.price = 11;
	_lightningShowerSkill.skillNumber = 4;
	_lightningShowerSkill.skillMotionNum = 2;
	_lightningShowerSkill.count = 1;
	_lightningShowerSkill.skillCoolTime = 5;
	_lightningShowerSkill.isActive = false;
	_lightningShowerSkill.skillRc = RectMakeCenter(0, 0, _lightningShowerSkill.image->getWidth(), _lightningShowerSkill.image->getHeight());
	_lightningShowerSkill.skillDamege = 3;

	m_player->setPlayerEButtonSkill(_lightningShowerSkill);

	

	return S_OK;
}

