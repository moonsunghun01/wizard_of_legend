#pragma once
#include "gameNode.h"
class playerTeleport : public gameNode
{
private:
	// �ڷ���Ʈ �е�
	image* _teleportPad;
	RECT _teleportPadRc;

	// �ڷ���Ʈ ����Ʈ
	image* _teleportEffect;
	RECT _teleportEffectRc;

	int _teleportEffectIndex;
	int _teleportEffectCount;

	bool _isTeleport;
	bool _isChangePosition;
public:

	HRESULT init();
	void release();
	void update();
	void render();

	image* getTeleportPad() { return _teleportPad; }
	void setTeleportPad(image* teleportPad) { _teleportPad = teleportPad;}

	RECT getTeleportPadRc() { return _teleportPadRc; }
	void setTeleportPadRc(RECT teleportPadRc) { _teleportPadRc = teleportPadRc; }

	bool getIsTeleport() { return _isTeleport; }
	void setIsTeleport(bool isTeleport) { _isTeleport = isTeleport; }

	bool getIsChangePosition() { return _isChangePosition; }
	void setIsChangePosition(bool isChangePosition) { _isChangePosition = isChangePosition; }

	void teleportActive();
};

