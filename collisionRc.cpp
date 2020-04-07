#include "stdafx.h"
#include "collisionRc.h"



collisionRc::collisionRc()
{
}


collisionRc::~collisionRc()
{

}

HRESULT collisionRc::init()
{
	_isBossMap = false;
	return S_OK;
}

void collisionRc::release()
{
}

void collisionRc::update()
{
	if (_isBossMap)
	{
		_tagCollisionRc[0].rc = RectMake(1000 + m_camera->getCameraX(), 200 + m_camera->getCameraY(), 200, 1000);
		_tagCollisionRc[1].rc = RectMake(m_camera->getCameraX(), m_camera->getCameraY(), 1100, 230);
		_tagCollisionRc[2].rc = RectMake(-50 + m_camera->getCameraX(), 200 + m_camera->getCameraY(), 100, 1000);
		_tagCollisionRc[3].rc = RectMake(m_camera->getCameraX(), 930 + m_camera->getCameraY(), 1050, 200);
	}
	else
	{
		_tagCollisionRc[0].rc = RectMake(m_camera->getCameraX() + 3110, m_camera->getCameraY() + 4840, 150, 410);
		_tagCollisionRc[1].rc = RectMake(m_camera->getCameraX() + 3250, m_camera->getCameraY() + 4840, 215, 240);
		_tagCollisionRc[2].rc = RectMake(m_camera->getCameraX() + 3110, m_camera->getCameraY() + 5335, 150, 335);
		_tagCollisionRc[3].rc = RectMake(m_camera->getCameraX() + 3250, m_camera->getCameraY() + 5400, 215, 270);

		_tagCollisionRc[4].rc = RectMake(m_camera->getCameraX() + 3710, m_camera->getCameraY() + 4840, 400, 230);
		_tagCollisionRc[5].rc = RectMake(m_camera->getCameraX() + 3970, m_camera->getCameraY() + 5010, 140, 200);
		_tagCollisionRc[6].rc = RectMake(m_camera->getCameraX() + 3970, m_camera->getCameraY() + 5280, 140, 400);
		_tagCollisionRc[7].rc = RectMake(m_camera->getCameraX() + 3750, m_camera->getCameraY() + 5430, 230, 250);




		_tagCollisionRc[8].rc = RectMake(m_camera->getCameraX() + 3020, m_camera->getCameraY() + 4500, 450, 250);
		_tagCollisionRc[9].rc = RectMake(m_camera->getCameraX() + 2850, m_camera->getCameraY() + 4500, 200, 350);
		_tagCollisionRc[10].rc = RectMake(m_camera->getCameraX() + 2330, m_camera->getCameraY() + 4500, 580, 720);

		_tagCollisionRc[11].rc = RectMake(m_camera->getCameraX() + 2330, m_camera->getCameraY() + 2675, 280, 1900);
		_tagCollisionRc[12].rc = RectMake(m_camera->getCameraX() + 2000, m_camera->getCameraY() + 2080, 335, 2520);
		_tagCollisionRc[13].rc = RectMake(m_camera->getCameraX() + 2000, m_camera->getCameraY() + 1850, 610, 450);
		_tagCollisionRc[14].rc = RectMake(m_camera->getCameraX() + 2000, m_camera->getCameraY() + 1250, 900, 840);


		_tagCollisionRc[15].rc = RectMake(m_camera->getCameraX() + 2800, m_camera->getCameraY() + 1000, 2100, 460);

		_tagCollisionRc[16].rc = RectMake(m_camera->getCameraX() + 4250, m_camera->getCameraY() + 920, 210, 130);


		_tagCollisionRc[17].rc = RectMake(m_camera->getCameraX() + 4100, m_camera->getCameraY() + 130, 220, 900);

		_tagCollisionRc[18].rc = RectMake(m_camera->getCameraX() + 4200, m_camera->getCameraY() + 80, 260, 250);

		_tagCollisionRc[19].rc = RectMake(m_camera->getCameraX() + 4400, m_camera->getCameraY(), 1250, 230);

		_tagCollisionRc[20].rc = RectMake(m_camera->getCameraX() + 5600, m_camera->getCameraY() + 100, 200, 230);

		_tagCollisionRc[21].rc = RectMake(m_camera->getCameraX() + 5740, m_camera->getCameraY() + 120, 200, 900);

		_tagCollisionRc[22].rc = RectMake(m_camera->getCameraX() + 5600, m_camera->getCameraY() + 935, 200, 200);
		_tagCollisionRc[23].rc = RectMake(m_camera->getCameraX() + 5170, m_camera->getCameraY() + 1000, 600, 700);

		_tagCollisionRc[24].rc = RectMake(m_camera->getCameraX() + 4325, m_camera->getCameraY() + 1640, 900, 900);


		_tagCollisionRc[25].rc = RectMake(m_camera->getCameraX() + 3470, m_camera->getCameraY() + 2445, 900, 280);

		_tagCollisionRc[26].rc = RectMake(m_camera->getCameraX() + 3185, m_camera->getCameraY() + 2650, 900, 280);

		_tagCollisionRc[27].rc = RectMake(m_camera->getCameraX() + 2900, m_camera->getCameraY() + 2900, 900, 420);

		_tagCollisionRc[28].rc = RectMake(m_camera->getCameraX() + 3180, m_camera->getCameraY() + 3300, 900, 1050);

		_tagCollisionRc[29].rc = RectMake(m_camera->getCameraX() + 2900, m_camera->getCameraY() + 3610, 300, 740);

		_tagCollisionRc[30].rc = RectMake(m_camera->getCameraX() + 3755, m_camera->getCameraY() + 4000, 450, 750);

		_tagCollisionRc[31].rc = RectMake(m_camera->getCameraX() + 4180, m_camera->getCameraY() + 4650, 300, 200);
		_tagCollisionRc[32].rc = RectMake(m_camera->getCameraX() + 3180, m_camera->getCameraY() + 1660, 900, 660);

		_tagCollisionRc[33].rc = RectMake(m_camera->getCameraX() + 4320, m_camera->getCameraY() + 4820, 580, 360);
		_tagCollisionRc[34].rc = RectMake(m_camera->getCameraX() + 4850, m_camera->getCameraY() + 4610, 1200, 360);
		_tagCollisionRc[35].rc = RectMake(m_camera->getCameraX() + 6040, m_camera->getCameraY() + 4800, 50, 750);

		_tagCollisionRc[36].rc = RectMake(m_camera->getCameraX() + 4320, m_camera->getCameraY() + 5340, 1850, 500);

		_tagCollisionRc[37].rc = RectMake(m_camera->getCameraX() + 4180, m_camera->getCameraY() + 5650, 1850, 200);
		_tagCollisionRc[38].rc = RectMake(m_camera->getCameraX() + 3750, m_camera->getCameraY() + 5745, 450, 400);
		_tagCollisionRc[39].rc = RectMake(m_camera->getCameraX() + 3130, m_camera->getCameraY() + 6070, 650, 200);
		_tagCollisionRc[40].rc = RectMake(m_camera->getCameraX() + 2865, m_camera->getCameraY() + 5745, 320, 400);

		_tagCollisionRc[41].rc = RectMake(m_camera->getCameraX() + 3000, m_camera->getCameraY() + 5745, 465, 170);
		_tagCollisionRc[42].rc = RectMake(m_camera->getCameraX() + 2865, m_camera->getCameraY() + 5655, 180, 100);

		_tagCollisionRc[43].rc = RectMake(m_camera->getCameraX() + 1985, m_camera->getCameraY() + 5365, 912, 300);
		_tagCollisionRc[44].rc = RectMake(m_camera->getCameraX() + 1760, m_camera->getCameraY() + 4780, 283, 800);

		_tagCollisionRc[45].rc = RectMake(m_camera->getCameraX(), m_camera->getCameraY() + 4940, 1770, 200);
		_tagCollisionRc[46].rc = RectMake(m_camera->getCameraX(), m_camera->getCameraY() + 4140, 1780, 230);

		_tagCollisionRc[47].rc = RectMake(m_camera->getCameraX(), m_camera->getCameraY() + 4140, 1780, 230);
		_tagCollisionRc[48].rc = RectMake(m_camera->getCameraX(), m_camera->getCameraY() + 4340, 48, 640);

		_tagCollisionRc[49].rc = RectMake(m_camera->getCameraX() + 1763, m_camera->getCameraY() + 4100, 300, 500);


		_tagCollisionRc[50].rc = RectMake(m_camera->getCameraX() + 340, m_camera->getCameraY() + 4625, 130, 100);
		_tagCollisionRc[50].rcKind = RC_OBSTACLE;

		_tagCollisionRc[51].rc = RectMake(m_camera->getCameraX() + 1345, m_camera->getCameraY() + 4625, 130, 100);
		_tagCollisionRc[51].rcKind = RC_OBSTACLE;

		_tagCollisionRc[52].rc = RectMake(m_camera->getCameraX() + 2600, m_camera->getCameraY() + 3640, 150, 80);
		_tagCollisionRc[52].rcKind = RC_OBSTACLE;

		_tagCollisionRc[53].rc = RectMake(m_camera->getCameraX() + 3050, m_camera->getCameraY() + 3530, 130, 85);
		_tagCollisionRc[53].rcKind = RC_OBSTACLE;

		_tagCollisionRc[54].rc = RectMake(m_camera->getCameraX() + 2600, m_camera->getCameraY() + 3450, 330, 220);
		_tagCollisionRc[54].rcKind = RC_OBSTACLE;

		_tagCollisionRc[55].rc = RectMake(m_camera->getCameraX() + 2835, m_camera->getCameraY() + 2440, 130, 95);
		_tagCollisionRc[55].rcKind = RC_OBSTACLE;

		_tagCollisionRc[56].rc = RectMake(m_camera->getCameraX() + 4080, m_camera->getCameraY() + 1700, 260, 220);
		_tagCollisionRc[56].rcKind = RC_OBSTACLE;

	}


}

void collisionRc::render()
{
	if (_isBossMap)
	{
		num = 4;
	}
	else
		num = 57;
	for (int i = 0; i < num; i++)
	{
		char str[256];
		wsprintf(str, "%d", i);
		Rectangle(getMemDC(), _tagCollisionRc[i].rc.left, _tagCollisionRc[i].rc.top, _tagCollisionRc[i].rc.right, _tagCollisionRc[i].rc.bottom);
		TextOut(getMemDC(), _tagCollisionRc[i].rc.left + 20, _tagCollisionRc[i].rc.top + 10, str, strlen(str));
	}

}

