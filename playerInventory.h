#pragma once
#include "gameNode.h"
#include "item.h"
class playerInventory : public gameNode
{
private:
	image* _playerInventoryImage;
	RECT _playerInventoryRc;

	image* _playerItemSelectImage;
	RECT _playerItemSelectRc;

	item* _item;
	vector<item*> _vItem;

	char _str[256];

	bool _isShowItemInfo;
	int _itemIndex;

	bool _isShowSkillInfo;
	int _skillIndex;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void showItemInfo();
	void showSkillInfo();

	bool getIsShowItemInfo() { return _isShowItemInfo; }
	void setIsShowItemInfo(bool isShowItemInfo) { _isShowItemInfo = isShowItemInfo; }

	bool getIsShowSkillInfo() { return _isShowSkillInfo; }
	void setIsShowSkillInfo(bool isShowSkillInfo) { _isShowSkillInfo = isShowSkillInfo; }
};

