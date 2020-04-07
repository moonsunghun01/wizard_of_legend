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
	 
	// 디버그 모드. 케릭터 rect 표시
	bool _isDebug;

	// 기본 방향 설정용 
	bool _isRight;
	bool _isLeft;
	bool _isUp;
	bool _isDown;

	// 대각선 방향 설정
	bool _isRightUp;
	bool _isRightDown;
	bool _isLeftUp;
	bool _isLeftDown;

	// 이동중인지 멈춰있는지 확인. 프레임 용
	bool _isMove;
	bool _isIdle;

	// 대쉬중. 대쉬 멈췄을때 프레임 용
	bool _isDash;
	bool _isDashPause;

	// 기본 모션 프레임용 카운트 인덱스
	int _count;
	int _index;
	 
	// 대쉬 이동거리 조절
	int _dashCount;

	// 스킬정보 상속 
	playerSkill* _playerSkill;
	
	// 스킬 사용중인지 판단. 스킬 사용중에는 다른스킬 사용 불가
	bool _isSkillActive;

	char str[256];

	playerTeleport* _playerTeleport; 
	image* _playerShadow;					// 그림자
	// 플레이어 인벤토리
	playerInventory* _playerInventory;		
	bool _isShowPlayerInventory;

	// 드래그 아이템
	bool _isDragItem;
	int _dragItemNum;
	int _dragSkillNum;

	// 아이템 on off 체크
	bool _isInventoryItem;
	bool _isWeaponOff;			// 무기 off 중
	bool _isArmorOff;			// 방어구 off 중
	bool _isPotionOff;			// 물약 off 중 

	// 플레이어 상태 창
	playerStatus * _playerStatus;
	bool _isShowPlayerStatus;

	// 스킬 변경
	bool _isInventorySkill;
	bool _isSkillChange;

	bool _isLButtonSkillOff;			// 왼쪽버튼 스킬 
	bool _isDashSkillOff;				// 대시 기술
	bool _isRButtonSkillOff;
	bool _isQButtonSkillOff;
	bool _isEButtonSkillOff;
	bool _isRRButtonSkillOff;

	// 충돌처리
	collisionRc* _collisionRc;
	RECT _playerMoveRc;

	// 에너미와 처리
	enemyManager* _enemyManager;

	// 맞았을 경우 각도 계산
	float _hitAngle;
	int _hitTimeCount;

	// 보스몹 진입 가능 여부 체크
	bool _isClearCheck;

	// 플레이어 죽었을떄
	bool _isPlayerDeathAnimation;
	image* _deathBackImage;
	int _deathBackImageAlpha;
	int _deathFrameX;

	image* _gameOverImage;
	int _gameOverImageAlpha;

	// 이겼을 경우
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

	// 키보드 전체 관리
	void keyManager();
	// 플레이어 기본 애니매이션 프레임
	void animation();
	// 플레이어 대쉬 설정 
	void playerDash();
	
	// 아이템 드래그
	void dragItem();
	// 아이템 장착 체크
	void checkEquipItem();

	// Rect 충돌 
	void checkRectCollision();
	void checkDashCollision();

	void setEnemyManagerLink(enemyManager* _enemyManagerLink);

	playerTeleport* getPlayerTeleport() { return _playerTeleport; }

	// 몬스터 때릴시
	void enemyHit();

	// 몬스터에게 맞을 경우
	void playerHitCheck();
	// 보스방 진입 체크
	void setIsClearCheck(bool isClearCheck) { _isClearCheck = isClearCheck; }
	// 플레이어 죽음 체크
	void checkEndGame();

	bool getIsReset() { return _isReset; }
	void setIsReset(bool isReset) { _isReset = isReset; }
	 
};

