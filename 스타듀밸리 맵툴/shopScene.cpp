#include "stdafx.h"
#include "shopScene.h"
POINT temp;

HRESULT shopScene::init()
{
	CAMERAMANAGER->init(1600, 1600, 480, 230);
	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());

	_shop = new shop;
	_shop->init();

	_isClicked = false;

	_pos.x = 270;
	_pos.y = 310;

	_rc_player = RectMake(_pos.x, _pos.y, 16, 32);

	_itemNpc = new npc;
	_itemNpc->init(ITEM_NPC);
	_itemNpc->setPos(270, 220);

	//_itemNpc->setPos(310, 240);
	
	_skillNpc = new npc;
	_skillNpc->init(SKILL_NPC);
	_skillNpc->setPos(450, 240);

	_npcPtr[0] = _itemNpc;
	_npcPtr[1] = _skillNpc;

	return S_OK;
}

void shopScene::release()
{
	//_shop->release();
}

void shopScene::update()
{

	_itemNpc->update();
	_skillNpc->update();

	//상점 나가기 포탈
	if (PLAYER->getCenterY() >= 338)
	{
		if (!SWITCHMANAGER->getFade())
		{
			SWITCHMANAGER->changeScene("인게임화면");
			SWITCHMANAGER->startFade(800.0f, 340.0f);
		}
	}


	if (_isClicked)
	{
		_shop->update();
		_isClicked = !_shop->shopClose();
	}
	else
	{
		PLAYER->update();
		
		playerMove();

		_itemNpc->update();

		_skillNpc->update();

		_rc_player = RectMake(_pos.x, _pos.y, 16, 32);

		temp.x = CAMERAMANAGER->getX() + (float)_ptMouse.x / (float)WINSIZEX * 480;
		temp.y = CAMERAMANAGER->getY() + (float)_ptMouse.y / (float)WINSIZEY * (float)230;

		if (PtInRect(&_itemNpc->getRC(), temp))
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				_isClicked = true;
			}
		}

		CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());
	}
}

void shopScene::render()
{
	IMAGEMANAGER->render("상점실내", CAMERAMANAGER->getMemDC());
	bool isFront = true;
	
	for (int i = 0; i < 2; i++)
	{
		if (_npcPtr[i]->getPos().x <= PLAYER->getCenterX() + 8 && _npcPtr[i]->getPos().x + 16 >= PLAYER->getCenterX() - 8)
		{
			if (_npcPtr[i]->getPos().y <= PLAYER->getCenterY() - 16)
			{
				isFront = true;
			}
			else
			{
				isFront = false;
			}
		}
	}

	if (isFront == false) PLAYER->render();
	
	for (int i = 0; i < 2; i++)
	{
		_npcPtr[i]->render();
	}
	
	if (isFront == true) PLAYER->render();

	if (PLAYER->getCenterY() + 32 >= 238 && PLAYER->getCenterY() <= 270)
	{
		IMAGEMANAGER->render("상점테이블", CAMERAMANAGER->getMemDC(), 230, 235);
	}

	CAMERAMANAGER->render(getMemDC());

	if (_isClicked)
	{
		_shop->render();
	}
}

void shopScene::playerMove()
{
		if (INPUT->GetKey('W'))
		{
			if (GetPixel(IMAGEMANAGER->findImage("상점실내뒷배경")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY()) != RGB(255, 0, 0))
			{
				RECT temp;
				bool iscoli = false;
				for (int i = 0; i < 2; i++)
				{
					if (IntersectRect(&temp, &_npcPtr[i]->getRC(), &RectMake(PLAYER->getCenterX()-8, PLAYER->getCenterY(), 16, 1)))
					{
						iscoli = true;
					}
				}
				if (!iscoli)
				{
					PLAYER->setDirection(UP);
					PLAYER->setState(RUN);
					PLAYER->setCenterY(PLAYER->getCenterY() - PLAYER->getSpeed());
				}
			}
		}
		if (INPUT->GetKey('S'))
		{
			if (GetPixel(IMAGEMANAGER->findImage("상점실내뒷배경")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY() + 16) != RGB(255, 0, 0))
			{
				RECT temp;
				bool iscoli = false;
				for (int i = 0; i < 2; i++)
				{
					if (IntersectRect(&temp, &_npcPtr[i]->getRC(), &RectMake(PLAYER->getCenterX() - 8, PLAYER->getCenterY() + 16, 16, 1)))
					{
						iscoli = true;
					}
				}
				if (!iscoli)
				{
					PLAYER->setDirection(DOWN);
					PLAYER->setState(RUN);
					PLAYER->setCenterY(PLAYER->getCenterY() + PLAYER->getSpeed());
				}
			}
			
		}
		if (INPUT->GetKey('A'))
		{
			if (GetPixel(IMAGEMANAGER->findImage("상점실내뒷배경")->getMemDC(), PLAYER->getCenterX() - 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
			{
				RECT temp;
				bool iscoli = false;
				for (int i = 0; i < 2; i++)
				{
					if (IntersectRect(&temp, &_npcPtr[i]->getRC(), &RectMake(PLAYER->getCenterX() - 8, PLAYER->getCenterY(), 1, 16)))
					{
						iscoli = true;
					}
				}
				if (!iscoli)
				{
					PLAYER->setDirection(LEFT);
					PLAYER->setState(RUN);
					PLAYER->setCenterX(PLAYER->getCenterX() - PLAYER->getSpeed());
				}
			}
		}
		if (INPUT->GetKey('D'))
		{
			if (GetPixel(IMAGEMANAGER->findImage("상점실내뒷배경")->getMemDC(), PLAYER->getCenterX() + 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
			{
				RECT temp;
				bool iscoli = false;
				for (int i = 0; i < 2; i++)
				{
					if (IntersectRect(&temp, &_npcPtr[i]->getRC(), &RectMake(PLAYER->getCenterX() + 8, PLAYER->getCenterY(), 1, 16)))
					{
						iscoli = true;
					}
				}
				if (!iscoli)
				{
					PLAYER->setDirection(RIGHT);
					PLAYER->setState(RUN);
					PLAYER->setCenterX(PLAYER->getCenterX() + PLAYER->getSpeed());
				}
			}
		}
		if (!(INPUT->GetKey('W')) && !(INPUT->GetKey('S')) && !(INPUT->GetKey('A')) && !(INPUT->GetKey('D')))
		{
			PLAYER->setState(STAND);
		}
}
