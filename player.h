#pragma once
#include "item.h"
class player
{
private:
	// �÷��̾� �⺻����
	int _hp;				// hp
	int _atk;				// �⺻ ���ݷ�
	int _skillDamage;			// ��ų ���ݷ�
	int _def;				// ����
	int _moveSpeed;			// �̵��ӵ�
	int _money;				// �ݾ�
	int _currentHp;				//���� hp ( ���� �� �� )
	int _currentAtk;			//���� Atk
	int _currentDef;			//���� def
	int _currentMoveSpeed;		//���� Speed 
	bool _isHit;				// �ǰ� üũ
	bool _isPlayerDeath;		//���� üũ

	image* _playerImage;	// �ɸ��� �̹���
	RECT _playerRc;			// �浹 ó���� ���� 

	RECT _monsterRc;		// �ǰݿ� ���� ����
	// �κ��丮
	vector<TAGITEMINFO> _vPlayerItem;
	// ��ų
	vector<SKILLBOOK> _vPlayerSkill;

	TAGITEMINFO _playerEqiupWeapon;
	TAGITEMINFO _playerEqiupArmor;
	TAGITEMINFO _playerEqiupPotion;

	SKILLBOOK _playerLButtonSkill;
	SKILLBOOK _playerDashSkill;
	SKILLBOOK _playerRButtonSkill;
	SKILLBOOK _playerQButtonSkill;
	SKILLBOOK _playerEButtonSkill;
	SKILLBOOK _playerRRButtonSkill;

public :
	HRESULT init();
	void update();

	int getHp() { return _hp; }
	void setHp(int hp) { _hp = hp; } 

	int getAtk() { return _atk; }
	void setAtk(int atk) { _atk = atk; }

	int getSkillDamage() { return _skillDamage; }
	void setSkillDamage(int skillDamage) { _skillDamage = skillDamage; }

	int getDef() { return _def; }
	void setDef(int def) { _def = def; }

	int getMoveSpeed() { return _moveSpeed; }
	void setMoveSpeed(int moveSpeed) { _moveSpeed = moveSpeed; } 

	int getMoney() { return _money; }
	void setMoney(int money) { _money = money; }
	// ����
	int getCurrentHp() { return _currentHp; }
	void setCurrentHp(int currentHp) { _currentHp = currentHp; }

	int getCurrentAtk() { return _currentAtk; }
	void setCurrentAtk(int currentAtk) { _currentAtk = currentAtk; }

	int getCurrentDef() { return _currentDef; }
	void setCurrentDef(int currentDef) { _currentDef = currentDef; }

	int getCurrentMoveSpeed() { return _currentMoveSpeed; }
	void setCurrentMoveSpeed(int currentMoveSpeed) { _currentMoveSpeed = currentMoveSpeed; }

	bool getIsHit() { return _isHit; }
	void setIsHit(bool isHit) { _isHit = isHit; }

	bool getIsPlayerDeath() { return _isPlayerDeath; }
	void setIsPlayerDeath(bool isPlayerDeath) { _isPlayerDeath = isPlayerDeath; }

	RECT getMonstetRc() { return _monsterRc; }
	void setMonsetRc(RECT monsterRc) { _monsterRc = monsterRc; }

	image* getPlayerImage() { return _playerImage; }
	void setPlayerImage(image* playerImage) { _playerImage = playerImage; }

	RECT getPlayerRc() { return _playerRc; }
	void setPlayerRc(RECT playerRc) { _playerRc = playerRc; } 

	vector<TAGITEMINFO> getVPlayerItem() { return _vPlayerItem; }
	void setVPlayerItem(vector<TAGITEMINFO> vPlayerItem) { _vPlayerItem = vPlayerItem; }

	vector<SKILLBOOK> getVPlayerSkill() { return _vPlayerSkill; }
	void setVPlayerSkill(vector<SKILLBOOK> vPlayerSkill) { _vPlayerSkill = vPlayerSkill; }

	TAGITEMINFO getPlayerEqiupWeapon() { return _playerEqiupWeapon; }
	void setPlayerEqiupWeapon(TAGITEMINFO playerEqiupWeapon) { _playerEqiupWeapon = playerEqiupWeapon; }

	TAGITEMINFO getPlayerEqiupArmor() { return _playerEqiupArmor; }
	void setPlayerEqiupArmor(TAGITEMINFO playerEqiupArmor) { _playerEqiupArmor = playerEqiupArmor; }

	TAGITEMINFO getPlayerEqiupPotion() { return _playerEqiupPotion; }
	void setPlayerEqiupPotion(TAGITEMINFO playerEqiuppotion) { _playerEqiupPotion = playerEqiuppotion; }

	SKILLBOOK getPlayerLButtonSkill() { return _playerLButtonSkill; }
	void setPlayerLButtonSkill(SKILLBOOK playerLButtonSkill) { _playerLButtonSkill = playerLButtonSkill; }

	SKILLBOOK getPlayerDashSkill() { return _playerDashSkill; }
	void setPlayerDashSkill(SKILLBOOK playerDashSkill) { _playerDashSkill = playerDashSkill; }

	SKILLBOOK getPlayerRButtonSkill() { return _playerRButtonSkill; }
	void setPlayerRButtonSkill(SKILLBOOK playerRButtonSkill) { _playerRButtonSkill = playerRButtonSkill; }

	SKILLBOOK getPlayerQButtonSkill() { return _playerQButtonSkill; }
	void setPlayerQButtonSkill(SKILLBOOK playerQButtonSkill) { _playerQButtonSkill = playerQButtonSkill; }

	SKILLBOOK getPlayerEButtonSkill() { return _playerEButtonSkill; }
	void setPlayerEButtonSkill(SKILLBOOK playerEButtonSkill) { _playerEButtonSkill = playerEButtonSkill; }

	SKILLBOOK getPlayerRRButtonSkill() { return _playerRRButtonSkill; }
	void setPlayerRRButtonSkill(SKILLBOOK playerRRButtonSkill) { _playerRRButtonSkill = playerRRButtonSkill; }

	void addPlayerItem(TAGITEMINFO buyItem);
	void addPlayerSkill(SKILLBOOK buySkill);
};

