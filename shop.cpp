#include "stdafx.h"
#include "shop.h"

HRESULT shop::init()
{

	_randNumWeapon = RND->getFromIntTo(0, 2);	//아이템 무기 랜덤 한개 선택
	_randNumArmor = RND->getFromIntTo(3, 5);	//아이템 방어구 랜덤 한개 선택
	_randNumPotion = RND->getFromIntTo(6, 8);		//아이템 포션 랜덤 한개 선택
	_randNumSkill = RND->getFromIntTo(0, 2);	//스킬 랜덤 한개 선택
	_randItem = new item;
	_randItem->init();
	_npc = new npc;
	_npc->init();

	_buy = IMAGEMANAGER->addFrameImage("구매시이모션", "images/상점/UI/구매시이모션.bmp", 400, 100, 7, 1, true, RGB(255, 0, 255));
	_noMoney = IMAGEMANAGER->addFrameImage("돈없을시이모션", "images/상점/UI/돈없을시이모션.bmp", 400, 100, 7, 1, true, RGB(255, 0, 255));
	_explanationImage = IMAGEMANAGER->addImage("설명", "images/상점/UI/설명란.bmp", 400, 130, true, RGB(255, 0, 255));
	_matImage = IMAGEMANAGER->addImage("돗자리", "images/상점/UI/돗자리.bmp", 400, 130, true, RGB(255, 0, 255));
	_soldOutImage = IMAGEMANAGER->addImage("매진", "images/상점/UI/물건없음.bmp", 50, 40, true, RGB(255, 0, 255));

	_skillRc = _randItem->getSkillInfo().at(_randNumSkill).skillRc;
	_weaponRc = _randItem->getEquipInfo().at(_randNumWeapon).itemRc;
	_armorRc = _randItem->getEquipInfo().at(_randNumArmor).itemRc;
	_potionRc = _randItem->getEquipInfo().at(_randNumPotion).itemRc;
	_matRc = RectMakeCenter(0, 0, _matImage->getWidth(), _matImage->getHeight());
	_skillSoldOutRc = RectMakeCenter(0, 0, _soldOutImage->getWidth(), _soldOutImage->getHeight());
	_explanationRc = RectMakeCenter(0, 0, _explanationImage->getWidth(), _explanationImage->getHeight());
	_weaponSoldOutRc = RectMakeCenter(0, 0, _soldOutImage->getWidth(), _soldOutImage->getHeight());
	_armorSoldOutRc = RectMakeCenter(0, 0, _soldOutImage->getWidth(), _soldOutImage->getHeight());
	_potionSoldOutRc = RectMakeCenter(0, 0, _soldOutImage->getWidth(), _soldOutImage->getHeight());
	_buyRc = RectMakeCenter(0, 0, _buy->getWidth(), _buy->getHeight());
	_noMoneyRc = RectMakeCenter(0, 0, _noMoney->getWidth(), _noMoney->getHeight());

	_isMouseUp = false;
	_isWeaponSoldOut = false;
	_isArmorSoldOut = false;
	_isPotionSoldOut = false;
	_isSkillSoldOut = false;
	_isSkill = false;
	_isItem = false;
	_sell = 1;
	_weaponSellCount = 0;
	_armorSellCount = 0;
	_potionSellCount = 0;
	_skillSellCount = 0;
	_destoryCount = 0;

	_isNoMoneyDestroy = false;
	return S_OK;
}

void shop::release()
{

}

void shop::update()
{
	position();
	buy();
	motionAnimation();
}

void shop::render()
{
	if (KEYMANAGER->isToggleKey('T')) { // T클릭시 사각형 출현
		Rectangle(getMemDC(), _matRc.left, _matRc.top, _matRc.right, _matRc.bottom);
	}
	IMAGEMANAGER->render("돗자리", getMemDC(), _matRc.left, _matRc.top); //돗자리 출력(NPC 위치에 따라 출력)

	_npc->render();

	if (_armorSell < 3) {
		if (KEYMANAGER->isToggleKey('T')) { // T클릭시 사각형 출현
			Rectangle(getMemDC(), _randItem->getEquipInfo().at(_randNumArmor).itemRc.left, _randItem->getEquipInfo().at(_randNumArmor).itemRc.top, _randItem->getEquipInfo().at(_randNumArmor).itemRc.right, _randItem->getEquipInfo().at(_randNumArmor).itemRc.bottom);				//랜덤 아이템 방어구 사각형 지정
		}
	}
	if (_weaponSell < 3) {
		if (KEYMANAGER->isToggleKey('T')) { // T클릭시 사각형 출현
			Rectangle(getMemDC(), _randItem->getEquipInfo().at(_randNumWeapon).itemRc.left, _randItem->getEquipInfo().at(_randNumWeapon).itemRc.top, _randItem->getEquipInfo().at(_randNumWeapon).itemRc.right, _randItem->getEquipInfo().at(_randNumWeapon).itemRc.bottom);				//랜덤 아이템 무기 사각형 지정
		}
	}
	if (_potionSell < 3) {
		if (KEYMANAGER->isToggleKey('T')) { // T클릭시 사각형 출현
			Rectangle(getMemDC(), _randItem->getEquipInfo().at(_randNumPotion).itemRc.left, _randItem->getEquipInfo().at(_randNumPotion).itemRc.top, _randItem->getEquipInfo().at(_randNumPotion).itemRc.right, _randItem->getEquipInfo().at(_randNumPotion).itemRc.bottom);				//랜덤 아이템 포션 사각형 지정
		}
	}
	if (_randItem->getSkillInfo().size() > 0) {
		if (KEYMANAGER->isToggleKey('T')) { // T클릭시 사각형 출현
			Rectangle(getMemDC(), _randItem->getSkillInfo().at(_randNumSkill).skillRc.left, _randItem->getSkillInfo().at(_randNumSkill).skillRc.top, _randItem->getSkillInfo().at(_randNumSkill).skillRc.right, _randItem->getSkillInfo().at(_randNumSkill).skillRc.bottom);	//랜덤 스킬 한가지 사각형 위치 지정
		}
	}
	// 아이템 출현	(NPC 위치에 따라 출력)
	if (_isWeaponSoldOut == true) {
		IMAGEMANAGER->render("매진", getMemDC(), _weaponSoldOutRc.left , _weaponSoldOutRc.top);
	}
	else {
		_randItem->getEquipInfo().at(_randNumWeapon).image->render(getMemDC(), _randItem->getEquipInfo().at(_randNumWeapon).itemRc.left, _randItem->getEquipInfo().at(_randNumWeapon).itemRc.top);																				//랜덤 아이템 무기 이미지 지정

	}
	if (_isArmorSoldOut == true) {
		IMAGEMANAGER->render("매진", getMemDC(), _armorSoldOutRc.left, _armorSoldOutRc.top);
	}
	else {
		_randItem->getEquipInfo().at(_randNumArmor).image->render(getMemDC(), _randItem->getEquipInfo().at(_randNumArmor).itemRc.left, _randItem->getEquipInfo().at(_randNumArmor).itemRc.top);																				//랜덤 아이템 방어구 이미지 지정

	}
	if (_isPotionSoldOut == true) {
		IMAGEMANAGER->render("매진", getMemDC(), _potionSoldOutRc.left, _potionSoldOutRc.top);
	}
	else {
		_randItem->getEquipInfo().at(_randNumPotion).image->render(getMemDC(), _randItem->getEquipInfo().at(_randNumPotion).itemRc.left, _randItem->getEquipInfo().at(_randNumPotion).itemRc.top);																				//랜덤 아이템 포션 이미지 지정

	}
	if (_isSkillSoldOut == true) {
		IMAGEMANAGER->render("매진", getMemDC(), _skillSoldOutRc.left, _skillSoldOutRc.top);
	}
	else {
		_randItem->getSkillInfo().at(_randNumSkill).image->render(getMemDC(), _randItem->getSkillInfo().at(_randNumSkill).skillRc.left, _randItem->getSkillInfo().at(_randNumSkill).skillRc.top);																		//랜덤 스킬 한가지 이미지

	}

	if (_isShowItemInfo) 
	{  // 물건 위로 아이템 올릴 경우 설명창 출현
		if (KEYMANAGER->isToggleKey('T')) {// T클릭시 사각형 출현
			Rectangle(getMemDC(), _explanationRc.left, _explanationRc.top, _explanationRc.right, _explanationRc.bottom);
		}
		_explanationImage->alphaRender(getMemDC(), _explanationRc.left , _explanationRc.top , 500); //물건 설명란 출력(NPC 위치에 따라 출력)
		//텍스트 출력
		wsprintf(_str, "%s", _description.c_str());
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), _descriptionPositionX, _descriptionPositionY, _str, strlen(_str));  		
	} 
	if (_isNoMoneyDestroy == true) 
	{ 
		_noMoney->frameRender(getMemDC(), _noMoneyRc.left, _noMoneyRc.top, _noMoney->getFrameX(), _noMoney->getFrameY());
	}
	if (_isBuyDestroy == true) { 
		_buy->frameRender(getMemDC(), _buyRc.left, _buyRc.top, _buy->getFrameX(), _buy->getFrameY());
	}

}

void shop::buy() //구매 부분 (미완 범위 설정)
{
	RECT temp;
	if (_isWeaponSoldOut == false) {
		if (IntersectRect(&temp, &m_player->getPlayerRc(), &_randItem->getEquipInfo().at(_randNumWeapon).itemRc) && KEYMANAGER->isOnceKeyDown('F')) {
			if (m_player->getMoney() - _randItem->getEquipInfo().at(_randNumWeapon).price < 0)
			{
				_isNoMoneyDestroy = true; //돈없을시 bool값
				_isBuyDestroy = false; //돈없을시 bool값
			}
			else
			{
				//구매 
				m_player->setMoney(m_player->getMoney() - _randItem->getEquipInfo().at(_randNumWeapon).price);
				_isItem = true;
				_randNumPotion -= 1;
				_randNumArmor -= 1;
				if (_randNumArmor < 0) {
					_randNumArmor = 0;
				}
				if (_randNumPotion < 0) {
					_randNumPotion = 0;
				}
				removing(_randNumWeapon); //삭제		
				_weaponSell += 1;
				if (_weaponSellCount < 2) {
					_weaponSellCount += 1;

					_randNumWeapon = _randNumWeapon - 1;
					_isNoMoneyDestroy = false;
					_isBuyDestroy = true;
					for (int i = 0; i < 100; i++) {
						_randNumWeapon = RND->getFromIntTo(0, 2 - _weaponSell);
						if ((_randItem->getEquipInfo().at(_randNumWeapon).itemKind == item_Weapon)) {
							break;
						}
					}
				}
				else {
					//			_isBuyDestroy = false; //돈없을시 bool값
					//			_isNoMoneyDestroy = true; //돈없을시 bool값
					_isWeaponSoldOut = true;
					_isItem = false;
				}
			}
		}
		else {
			_isItem = false; 
		}
	}
	if (_isArmorSoldOut == false) {
		if (IntersectRect(&temp, &m_player->getPlayerRc(), &_randItem->getEquipInfo().at(_randNumArmor).itemRc) && KEYMANAGER->isOnceKeyDown('F')) {
			if (m_player->getMoney() - _randItem->getEquipInfo().at(_randNumWeapon).price < 0)
			{
				_isNoMoneyDestroy = true; //돈없을시 bool값
				_isBuyDestroy = false; //돈없을시 bool값
			}
			else
			{
				//구매 
				m_player->setMoney(m_player->getMoney() - _randItem->getEquipInfo().at(_randNumArmor).price);
				_isItem = true;
				_randNumPotion -= 1;
				if (_randNumPotion < 0) {
					_randNumPotion = 0;
				}
				removing(_randNumArmor); //삭제			
				_armorSell += 1;
				if (_armorSellCount < 2) {
					_armorSellCount += 1;
					_randNumArmor = _randNumArmor - 1;
					_isNoMoneyDestroy = false;
					_isBuyDestroy = true;
					motionAnimation();
					for (int i = 0; i < 100; i++) {
						_randNumArmor = RND->getFromIntTo(0, 5 - _armorSell - _weaponSell);
						if ((_randItem->getEquipInfo().at(_randNumArmor).itemKind == item_Armor)) {
							break;
						}
					} 
				}
				else {
					//			_isBuyDestroy = false; //돈없을시 bool값
					//			_isNoMoneyDestroy = true; //돈없을시 bool값
					_isArmorSoldOut = true;
					_isItem = false;
				}
			}
		}
		else {
			_isItem = false;
		}
	}
	if (_isPotionSoldOut == false) {
		if (IntersectRect(&temp, &m_player->getPlayerRc(), &_randItem->getEquipInfo().at(_randNumPotion).itemRc) && KEYMANAGER->isOnceKeyDown('F')) {
			if (m_player->getMoney() - _randItem->getEquipInfo().at(_randNumPotion).price < 0)
			{
				_isNoMoneyDestroy = true; //돈없을시 bool값
				_isBuyDestroy = false; //돈없을시 bool값
			}
			else
			{
				//구매 
				m_player->setMoney(m_player->getMoney() - _randItem->getEquipInfo().at(_randNumPotion).price);

				_isItem = true;
				removing(_randNumPotion); //삭제	
				_potionSell += 1;
				if (_potionSellCount < 2) {
					_potionSellCount += 1;
					_randNumPotion = _randNumPotion - 1;
					_isBuyDestroy = true;
					_isNoMoneyDestroy = false;
					motionAnimation();
					for (int i = 0; i < 100; i++) {
						_randNumPotion = RND->getFromIntTo(0, 8 - _potionSell - _weaponSell - _armorSell);
						if ((_randItem->getEquipInfo().at(_randNumPotion).itemKind == item_potion)) {
							break;
						}
					}
				}
				else {
					//			_isBuyDestroy = false; //돈없을시 bool값
					//			_isNoMoneyDestroy = true; //돈없을시 bool값
					_isPotionSoldOut = true;
					_isItem = false;
				}
			}
		}
		else {
			_isItem = false;
		}
	}

	if (_isSkillSoldOut == false) {
		if (IntersectRect(&temp, &m_player->getPlayerRc(), &_randItem->getSkillInfo().at(_randNumSkill).skillRc) && KEYMANAGER->isOnceKeyDown('F')) {
			if (m_player->getMoney() - _randItem->getSkillInfo().at(_randNumSkill).price < 0)
			{
				_isNoMoneyDestroy = true; //돈없을시 bool값
			}
			else
			{
				//구매 
				m_player->setMoney(m_player->getMoney() - _randItem->getSkillInfo().at(_randNumSkill).price);

				_isSkill = true;
				removing(_randNumSkill); //삭제	
				_skillSell += 1;
				if (_skillSellCount < 2) {
					_skillSellCount += 1;
					_randNumSkill = _randNumSkill - 1;
					_isBuyDestroy = true;
					_isNoMoneyDestroy = false;
					motionAnimation();
					for (int i = 0; i < 100; i++) {
						_randNumSkill = RND->getFromIntTo(0, 2 - _skillSell);
						if ((_randItem->getSkillInfo().at(_randNumSkill).itemKind == item_Skill)) {
							break;
						}
					}
				}
				else {
					//			_isBuyDestroy = false;//돈없을시 bool값
					//			_isNoMoneyDestroy = true;//돈없을시 bool값
					_isSkillSoldOut = true;
					_isSkill = false;
				}
			}
		}
		else {
			_isSkill = false;
		}
	}
}

void shop::removing(int i) //제거 (벡터제거 해당 벡터 출력 관련 확인(정확한 위치 벡터값 삭제 안됨), 스킬 삭제 관련 에러)
{
	if (_isItem == true) {
		vector<TAGITEMINFO> _tempItem = _randItem->getEquipInfo();
		m_player->addPlayerItem(_tempItem.at(i));
		_tempItem.erase(_tempItem.begin() + i);
		_randItem->setEquipInfo(_tempItem);
	}
	if (_isSkill == true) {
		vector<SKILLBOOK> _tempSkill = _randItem->getSkillInfo();
		m_player->addPlayerSkill(_tempSkill.at(i));
		_tempSkill.erase(_tempSkill.begin() + i);
		_randItem->setEquipInfo(_tempSkill);

	}
}

void shop::position() //위치 지정
{
	RECT temp;
	_xWeapon = _npc->getX() - 120 +m_camera->getCameraX();
	_xArmor = _npc->getX() - 50 + m_camera->getCameraX();
	_xPotion = _npc->getX() + 50 + m_camera->getCameraX();
	_xSkill = _npc->getX() + 120 + m_camera->getCameraX();

	_yWeapon = _npc->getY() + 100 + m_camera->getCameraY();
	_yArmor = _npc->getY() + 100 + m_camera->getCameraY();
	_yPotion = _npc->getY() + 100 + m_camera->getCameraY();
	_ySkill = _npc->getY() + 100 + m_camera->getCameraY();
	//물건 아이템 위치 지정

	_matRc = RectMakeCenter(_npc->getX() + m_camera->getCameraX(), _npc->getY() + 100 + m_camera->getCameraY(), _matImage->getWidth(), _matImage->getHeight());


	if (_skillSell < 3) {
		_randItem->getSkillRC(_randNumSkill);
		_skillRc = RectMakeCenter(_xSkill, _ySkill, _randItem->getSkillInfo().at(_randNumSkill).image->getWidth(), _randItem->getSkillInfo().at(_randNumSkill).image->getHeight());
		_randItem->setSkillRC(_randNumSkill, _skillRc);
	}
	if (_weaponSell < 3) {
		_randItem->getItemRC(_randNumWeapon);
		_weaponRc = RectMakeCenter(_xWeapon, _yWeapon, _randItem->getEquipInfo().at(_randNumWeapon).image->getWidth(), _randItem->getEquipInfo().at(_randNumWeapon).image->getHeight());
		_randItem->setItemRC(_randNumWeapon, _weaponRc);
	}
	if (_armorSell < 3) {
		_randItem->getItemRC(_randNumArmor);
		_armorRc = RectMakeCenter(_xArmor, _yArmor, _randItem->getEquipInfo().at(_randNumArmor).image->getWidth(), _randItem->getEquipInfo().at(_randNumArmor).image->getHeight());
		_randItem->setItemRC(_randNumArmor, _armorRc);
	}
	if (_potionSell < 3) {
		_randItem->getItemRC(_randNumPotion);
		_potionRc = RectMakeCenter(_xPotion, _yPotion, _randItem->getEquipInfo().at(_randNumPotion).image->getWidth(), _randItem->getEquipInfo().at(_randNumPotion).image->getHeight());
		_randItem->setItemRC(_randNumPotion, _potionRc);
	}

	if (IntersectRect(&temp, &_weaponRc, &m_player->getPlayerRc()) && _isWeaponSoldOut == false) {
		_explanationRc = RectMakeCenter(_xWeapon , _yWeapon - 120 , _explanationImage->getWidth(), _explanationImage->getHeight());
		_description = _randItem->getEquipInfo().at(_randNumWeapon).description;
		_descriptionPositionX = _xWeapon - 190;
		_descriptionPositionY = _yWeapon - 130;
		_isShowItemInfo = true;
	}
	else if (IntersectRect(&temp, &_armorRc, &m_player->getPlayerRc()) && _isArmorSoldOut == false)
	{ 
			_explanationRc = RectMakeCenter(_xArmor, _yArmor - 120, _explanationImage->getWidth(), _explanationImage->getHeight());
			_description = _randItem->getEquipInfo().at(_randNumArmor).description;
			_descriptionPositionX = _xArmor - 190;
			_descriptionPositionY = _yArmor - 130; 
			_isShowItemInfo = true;
	} 
	else if (IntersectRect(&temp, &_potionRc, &m_player->getPlayerRc()) && _isPotionSoldOut == false)
	{
		_explanationRc = RectMakeCenter(_xPotion, _yPotion - 120, _explanationImage->getWidth(), _explanationImage->getHeight());
		_description = _randItem->getEquipInfo().at(_randNumPotion).description;
		_descriptionPositionX = _xPotion - 190;
		_descriptionPositionY = _yPotion - 130;
		_isShowItemInfo = true;
	} 
	else if (IntersectRect(&temp, &_skillRc, &m_player->getPlayerRc()) && _isSkillSoldOut == false) {
			_explanationRc = RectMakeCenter(_xSkill, _ySkill - 120, _explanationImage->getWidth(), _explanationImage->getHeight());
			_description = _randItem->getSkillInfo().at(_randNumSkill).description;
			_descriptionPositionX = _xSkill - 190;
			_descriptionPositionY = _ySkill - 130; 
			_isShowItemInfo = true;
	} 
	else
	{
		_isShowItemInfo = false;
	}
	_buyRc = RectMakeCenter(_npc->getX() + 180 + m_camera->getCameraX(), _npc->getY() - 90 + m_camera->getCameraY(), _buy->getWidth(), _buy->getHeight());
	_noMoneyRc = RectMakeCenter(_npc->getX() + 180 + m_camera->getCameraX(), _npc->getY() - 90 + m_camera->getCameraY(), _noMoney->getWidth(), _noMoney->getHeight());


	if (_isWeaponSoldOut) _weaponSoldOutRc = RectMakeCenter(_xWeapon, _yWeapon + 30, _soldOutImage->getWidth(), _soldOutImage->getHeight());
	if (_isArmorSoldOut)  _armorSoldOutRc = RectMakeCenter(_xArmor, _yArmor + 30, _soldOutImage->getWidth(), _soldOutImage->getHeight());
	if (_isPotionSoldOut)_potionSoldOutRc = RectMakeCenter(_xPotion, _yPotion + 30, _soldOutImage->getWidth(), _soldOutImage->getHeight());
	if (_isSkillSoldOut) _skillSoldOutRc = RectMakeCenter(_xSkill, _ySkill + 30, _soldOutImage->getWidth(), _soldOutImage->getHeight());

}

void shop::countTime()
{
	_destoryCount++;
	if (_destoryCount == 10) {
		_destoryCount = 0;
	}

}

void shop::motionAnimation()
{
	if (_isBuyDestroy == true) {
		_count++;
		if (_count % 3 == 0)
		{
			_buy->setFrameX(_buy->getFrameX() + 1);
			_currentFrameX++;

			if (_currentFrameX >= _buy->getMaxFrameX())
			{
				//_currentFrameX = 0; 
			}
		}
	}
	if (_isNoMoneyDestroy == true) {
		_count++;
		if (_count % 3 == 0)
		{
			_noMoney->setFrameX(_currentFrameX);
			_currentFrameX++;

			if (_currentFrameX >= _noMoney->getMaxFrameX())
			{

			}
		}
	}

} 
void shop::motion()
{

}
