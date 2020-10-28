#include "stdafx.h"
#include "towerScene.h"
#include "stdafx.h"
#include "shopScene.h"

HRESULT towerScene::init()
{
	CAMERAMANAGER->init(1600, 1600, 480, 240);
	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());

	_skillShop = new shop;
	_skillShop->init(SKILL_NPC);

	_isSkillClicked = false;

	_pos.x = 270;
	_pos.y = 310;

	_rc_player = RectMake(_pos.x, _pos.y, 16, 32);

	_skillNpc = new npc;
	_skillNpc->init(SKILL_NPC);
	_skillNpc->setPos(360, 143);

	//_itemNpc->setPos(310, 240);

	_npcPtr = _skillNpc;
	//_npcPtr[1] = _skillNpc;

	if (!SOUNDMANAGER->isPlaySound("농장"))
	{
		SOUNDMANAGER->stop("농장");
	}

	this->update();
	return S_OK;
}

void towerScene::release()
{
	//_shop->release();
}

void towerScene::update()
{
	if (!SOUNDMANAGER->isPlaySound("town"))
	{
		SOUNDMANAGER->play("town", 0.05f);
	}

	_skillNpc->update();
	cout << "x : " << PLAYER->getCenterX() << "\t" << "y : " << PLAYER->getCenterY() << endl;
	//상점 나가기 포탈
	if (PLAYER->getCenterY() >= 270)
	{
		if (!SWITCHMANAGER->getFade())
		{
			SOUNDMANAGER->play("doorOpen", 0.2f);
			SWITCHMANAGER->changeScene("인게임화면");
			SWITCHMANAGER->startFade(384.0f, 192.0f);
		}
	}

	if (_isSkillClicked)
	{
		_skillShop->update();
		_isSkillClicked = !_skillShop->shopClose();
		PLAYER->getInventory()->isShopOpen(_isSkillClicked);
	}
	else
	{
		PLAYER->update();

		if (!PLAYER->getIsShowInventory())
		{
			playerMove();
		}

		_skillNpc->update();

		_rc_player = RectMake(_pos.x, _pos.y, 16, 32);

		temp.x = CAMERAMANAGER->getX() + (float)_ptMouse.x / (float)WINSIZEX * 480;
		temp.y = CAMERAMANAGER->getY() + (float)_ptMouse.y / (float)WINSIZEY * (float)230;

		if (PtInRect(&_skillNpc->getRC(), temp))
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				_isSkillClicked = true;
			}
		}
		CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());
	}
}

void towerScene::render()
{
	IMAGEMANAGER->render("마법사성내부", CAMERAMANAGER->getMemDC());

	bool isFront = true;

	if (_npcPtr->getPos().x <= PLAYER->getCenterX() + 8 && _npcPtr->getPos().x + 16 >= PLAYER->getCenterX() - 8)
	{
		if (_npcPtr->getPos().y <= PLAYER->getCenterY() - 16)
		{
			isFront = true;
		}
		else
		{
			isFront = false;
		}
	}

	if (isFront == false) PLAYER->render();

	_npcPtr->render();

	if (isFront == true) PLAYER->render();

	CAMERAMANAGER->render(getMemDC());

	 if (_isSkillClicked)
	{
		_skillShop->render();
	}
	else
	{
		PLAYER->playerStatusRender(getMemDC());
	}
}

void towerScene::playerMove()
{
	if (INPUT->GetKey('W'))
	{
		if (GetPixel(IMAGEMANAGER->findImage("마법사성내부충돌")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY()) != RGB(255, 0, 0))
		{
			RECT temp;
			bool iscoli = false;
			for (int i = 0; i < 2; i++)
			{
				if (IntersectRect(&temp, &_npcPtr->getRC(), &RectMake(PLAYER->getCenterX() - 8, PLAYER->getCenterY(), 16, 1)))
				{
					iscoli = true;
				}
			}
			if (!iscoli)
			{
				if (!SOUNDMANAGER->isPlaySound("movewood"))
				{
					SOUNDMANAGER->play("movewood", 0.2f);
				}
				PLAYER->setDirection(UP);
				PLAYER->setState(RUN);
				PLAYER->setCenterY(PLAYER->getCenterY() - PLAYER->getSpeed());
			}
		}
	}
	if (INPUT->GetKey('S'))
	{
		if (GetPixel(IMAGEMANAGER->findImage("마법사성내부충돌")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY() + 16) != RGB(255, 0, 0))
		{
			RECT temp;
			bool iscoli = false;
			for (int i = 0; i < 2; i++)
			{
				if (IntersectRect(&temp, &_npcPtr->getRC(), &RectMake(PLAYER->getCenterX() - 8, PLAYER->getCenterY() + 16, 16, 1)))
				{
					iscoli = true;
				}
			}
			if (!iscoli)
			{
				if (!SOUNDMANAGER->isPlaySound("movewood"))
				{
					SOUNDMANAGER->play("movewood", 0.2f);
				}
				PLAYER->setDirection(DOWN);
				PLAYER->setState(RUN);
				PLAYER->setCenterY(PLAYER->getCenterY() + PLAYER->getSpeed());
			}
		}

	}
	if (INPUT->GetKey('A'))
	{
		if (GetPixel(IMAGEMANAGER->findImage("마법사성내부충돌")->getMemDC(), PLAYER->getCenterX() - 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
		{
			RECT temp;
			bool iscoli = false;
			for (int i = 0; i < 2; i++)
			{
				if (IntersectRect(&temp, &_npcPtr->getRC(), &RectMake(PLAYER->getCenterX() - 8, PLAYER->getCenterY(), 1, 16)))
				{
					iscoli = true;
				}
			}
			if (!iscoli)
			{
				if (!SOUNDMANAGER->isPlaySound("movewood"))
				{
					SOUNDMANAGER->play("movewood", 0.2f);
				}
				PLAYER->setDirection(LEFT);
				PLAYER->setState(RUN);
				PLAYER->setCenterX(PLAYER->getCenterX() - PLAYER->getSpeed());
			}
		}
	}
	if (INPUT->GetKey('D'))
	{
		if (GetPixel(IMAGEMANAGER->findImage("마법사성내부충돌")->getMemDC(), PLAYER->getCenterX() + 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
		{
			RECT temp;
			bool iscoli = false;

			if (IntersectRect(&temp, &_npcPtr->getRC(), &RectMake(PLAYER->getCenterX() + 8, PLAYER->getCenterY(), 1, 16)))	iscoli = true;
			if (!iscoli)
			{
				if (!SOUNDMANAGER->isPlaySound("movewood"))
				{
					SOUNDMANAGER->play("movewood", 0.2f);
				}
				PLAYER->setDirection(RIGHT);
				PLAYER->setState(RUN);
				PLAYER->setCenterX(PLAYER->getCenterX() + PLAYER->getSpeed());
			}
		}
	}
	if (!(INPUT->GetKey('W')) && !(INPUT->GetKey('S')) && !(INPUT->GetKey('A')) && !(INPUT->GetKey('D')))
	{
		if (SOUNDMANAGER->isPlaySound("movewood"))
		{
			SOUNDMANAGER->stop("movewood");
		}
		PLAYER->setState(STAND);
	}
}
