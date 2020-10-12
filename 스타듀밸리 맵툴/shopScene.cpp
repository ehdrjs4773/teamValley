#include "stdafx.h"
#include "shopScene.h"
POINT temp;

HRESULT shopScene::init()
{
	_shop = new shop;
	_shop->init();

	_isClicked = false;

	IMAGEMANAGER->addImage("상점실내", "Images/shop/shop.bmp",600, 360,true,RGB(255,0,255));

	_pos.x = 280;
	_pos.y = 310;

	_rc_player = RectMake(_pos.x, _pos.y, 16, 32);

	CAMERAMANAGER->init(1600, 1600, 480, 230);

	_itemNpc = new npc;
	_itemNpc->init(ITEM_NPC);
	_itemNpc->setPos(240, 180);

	_skillNpc = new npc;
	_skillNpc->init(SKILL_NPC);
	_skillNpc->setPos(140, 180);

	return S_OK;
}

void shopScene::release()
{
	//_shop->release();
}

void shopScene::update()
{

	PLAYER->update();

	_shop->update();

	_itemNpc->update();

	_skillNpc->update();

	_rc_player = RectMake(_pos.x, _pos.y, 16, 32);

	temp.x = CAMERAMANAGER->getX() + (float)_ptMouse.x / (float)WINSIZEX * 480;
	temp.y = CAMERAMANAGER->getY() + (float)_ptMouse.y / (float)WINSIZEY * (float)230;
	if (PtInRect(&_itemNpc->getRC(), temp))
	{
		cout << "충돌" << endl;
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			_isClicked = true;
		}
	}

	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		cout << "클릭" << endl;
	}

	CAMERAMANAGER->cameraMove(_pos.x, _pos.y);

	if (INPUT->GetKey('A'))
	{
		_pos.x -= 1;
	}
	if (INPUT->GetKey('S'))
	{
		_pos.y += 1;
	}
	if (INPUT->GetKey('D'))
	{
		_pos.x += 1;
	}
	if (INPUT->GetKey('W'))
	{
		_pos.y -= 1;
	}

}

void shopScene::render()
{

	IMAGEMANAGER->render("상점실내", CAMERAMANAGER->getMemDC());

	Rectangle(CAMERAMANAGER->getMemDC(), _rc_player);

	_itemNpc->render();

	_skillNpc->render();

	CAMERAMANAGER->render(getMemDC());

	if (_isClicked)
	{
		_shop->render();
	}
}
