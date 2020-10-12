#include "stdafx.h"
#include "shopScene.h"
POINT temp;

HRESULT shopScene::init()
{
	_shop = new shop;
	_shop->init();

	_isClicked = false;

	IMAGEMANAGER->addImage("상점실내", "Images/shop/shop.bmp", 800, 480, true, RGB(255, 0, 255));

	_pos.x = 360;
	_pos.y = 430;

	_rc_player = RectMake(_pos.x, _pos.y, 16, 32);

	CAMERAMANAGER->init(800, 480, 400, 240);

	_itemNpc = new npc;
	_itemNpc->init(ITEM_NPC);
	_itemNpc->setPos(360, 300);

	_skillNpc = new npc;
	_skillNpc->init(SKILL_NPC);
	_skillNpc->setPos(260, 300);

	return S_OK;
}

void shopScene::release()
{
	//if (_shop != nullptr)
	//{
	//	//_shop->release();
	//	SAFE_DELETE(_shop);
	//}
	//if (_itemNpc != nullptr)
	//{
	//	SAFE_DELETE(_itemNpc);
	//}
	//if (_skillNpc != nullptr)
	//{
	//	SAFE_DELETE(_skillNpc);
	//}
}

void shopScene::update()
{
	_shop->update();

	_itemNpc->update();

	_skillNpc->update();

	_rc_player = RectMake(_pos.x, _pos.y, 16, 32);

	temp.x = CAMERAMANAGER->getX() + (float)_ptMouse.x / (float)WINSIZEX * 400;
	temp.y = CAMERAMANAGER->getY() + (float)_ptMouse.y / (float)WINSIZEY * (float)240;
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

	//Rectangle(CAMERAMANAGER->getMemDC(), RectMake(temp.x, temp.y, 16, 32));
	CAMERAMANAGER->render(getMemDC());

	if (_isClicked)
	{
		_shop->render();
	}
}
