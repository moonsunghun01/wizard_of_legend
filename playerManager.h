#pragma once
#include "gameNode.h"
#include "playerSkill.h" 
#include "playerTeleport.h"
#include "playerInventory.h"
#include "playerStatus.h"
#include "collisionRc.h"
#include "enemyManager.h"

class playerManager : public gameNode
{
private:
	 
	// ����� ���. �ɸ��� rect ǥ��
	bool _isDebug;

	// �⺻ ���� ������ 
	bool _isRight;
	bool _isLeft;
	bool _isUp;
	bool _isDown;

	// �밢�� ���� ����
	bool _isRightUp;
	bool _isRightDown;
	bool _isLeftUp;
	bool _isLeftDown;

	// �̵������� �����ִ��� Ȯ��. ������ ��
	bool _isMove;
	bool _isIdle;

	// �뽬��. �뽬 �������� ������ ��
	bool _isDash;
	bool _isDashPause;

	// �⺻ ��� �����ӿ� ī��Ʈ �ε���
	int _count;
	int _index;
	 
	// �뽬 �̵��Ÿ� ����
	int _dashCount;

	// ��ų���� ��� 
	playerSkill* _playerSkill;
	
	// ��ų ��������� �Ǵ�. ��ų ����߿��� �ٸ���ų ��� �Ұ�
	bool _isSkillActive;

	char str[256];

	playerTeleport* _playerTeleport; 
	image* _playerShadow;					// �׸���
	// �÷��̾� �κ��丮
	playerInventory* _playerInventory;		
	bool _isShowPlayerInventory;

	// �巡�� ������
	bool _isDragItem;
	int _dragItemNum;
	int _dragSkillNum;

	// ������ on off üũ
	bool _isInventoryItem;
	bool _isWeaponOff;			// ���� off ��
	bool _isArmorOff;			// �� off ��
	bool _isPotionOff;			// ���� off �� 

	// �÷��̾� ���� â
	playerStatus * _playerStatus;
	bool _isShowPlayerStatus;

	// ��ų ����
	bool _isInventorySkill;
	bool _isSkillChange;

	bool _isLButtonSkillOff;			// ���ʹ�ư ��ų 
	bool _isDashSkillOff;				// ��� ���
	bool _isRButtonSkillOff;
	bool _isQButtonSkillOff;
	bool _isEButtonSkillOff;
	bool _isRRButtonSkillOff;

	// �浹ó��
	collisionRc* _collisionRc;
	RECT _playerMoveRc;

	// ���ʹ̿� ó��
	enemyManager* _enemyManager;

	// �¾��� ��� ���� ���
	float _hitAngle;
	int _hitTimeCount;

	// ������ ���� ���� ���� üũ
	bool _isClearCheck;

	// �÷��̾� �׾�����
	bool _isPlayerDeathAnimation;
	image* _deathBackImage;
	int _deathBackImageAlpha;
	int _deathFrameX;

	image* _gameOverImage;
	int _gameOverImageAlpha;

	// �̰��� ���
	bool _isPlayerVictoryAnimation;
	image* _victoryImage;
	int _victoryImageAlpha;

	image* _leftArcana;
	image* _spaceArcana;
	image* _rightArcana;
	image* _qArcana;
	image* _eArcana;
	image* _rArcana;

	image* _resetButton;

	bool _isFinish;
	bool _isReset;

public :
	HRESULT init(collisionRc* collisionRc); 
	void release();
	void update();
	void render();

	// Ű���� ��ü ����
	void keyManager();
	// �÷��̾� �⺻ �ִϸ��̼� ������
	void animation();
	// �÷��̾� �뽬 ���� 
	void playerDash();
	
	// ������ �巡��
	void dragItem();
	// ������ ���� üũ
	void checkEquipItem();

	// Rect �浹 
	void checkRectCollision();
	void checkDashCollision();

	void setEnemyManagerLink(enemyManager* _enemyManagerLink);

	playerTeleport* getPlayerTeleport() { return _playerTeleport; }

	// ���� ������
	void enemyHit();

	// ���Ϳ��� ���� ���
	void playerHitCheck();
	// ������ ���� üũ
	void setIsClearCheck(bool isClearCheck) { _isClearCheck = isClearCheck; }
	// �÷��̾� ���� üũ
	void checkEndGame();

	bool getIsReset() { return _isReset; }
	void setIsReset(bool isReset) { _isReset = isReset; }
	 
};

