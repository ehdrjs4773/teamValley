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
	_itemNpc->update();

	//_itemNpc->setPos(310, 240);
	
	_skillNpc = new npc;
	_skillNpc->init(SKILL_NPC);
	_skillNpc->setPos(450, 240);
	_skillNpc->update();

	return S_OK;
}

void shopScene::release()
{
	//_shop->release();
}

void shopScene::update()
{
	if (INPUT->GetKeyDown(VK_TAB))
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

	_itemNpc->render();

	_skillNpc->render();
	
	PLAYER->render();

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
				PLAYER->setDirection(UP);
				PLAYER->setState(RUN);
				PLAYER->setCenterY(PLAYER->getCenterY() - PLAYER->getSpeed());
			}
		}
		if (INPUT->GetKey('S'))
		{
			if (GetPixel(IMAGEMANAGER->findImage("상점실내뒷배경")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY() + 16) != RGB(255, 0, 0))
			{
				PLAYER->setDirection(DOWN);
				PLAYER->setState(RUN);
				PLAYER->setCenterY(PLAYER->getCenterY() + PLAYER->getSpeed());
			}
		}
		if (INPUT->GetKey('A'))
		{
			if (GetPixel(IMAGEMANAGER->findImage("상점실내뒷배경")->getMemDC(), PLAYER->getCenterX() - 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
			{
				PLAYER->setDirection(LEFT);
				PLAYER->setState(RUN);
				PLAYER->setCenterX(PLAYER->getCenterX() - PLAYER->getSpeed());
			}
		}
		if (INPUT->GetKey('D'))
		{
			if (GetPixel(IMAGEMANAGER->findImage("상점실내뒷배경")->getMemDC(), PLAYER->getCenterX() + 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
			{
				PLAYER->setDirection(RIGHT);
				PLAYER->setState(RUN);
				PLAYER->setCenterX(PLAYER->getCenterX() + PLAYER->getSpeed());
			}
		}
		if (!(INPUT->GetKey('W')) && !(INPUT->GetKey('S')) && !(INPUT->GetKey('A')) && !(INPUT->GetKey('D')))
		{
			PLAYER->setState(STAND);
		}

}
