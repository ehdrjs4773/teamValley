#include "stdafx.h"
#include "item.h"

HRESULT item::init()
{
	for (int i = 0; i < 7; i++)
	{
		tagItem temp;

		_vItem.push_back(temp);
	}

	_vItem[0].item_image = IMAGEMANAGER->addImage("rusty_sword", "Images/sword/rusty_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	_vItem[0].item_info = " Damage : 2-5";
	_vItem[0].sell_price = 50;
	_vItem[0].item_kind = WEAPON;

	_vItem[1].item_image = IMAGEMANAGER->addImage("galaxy_sword", "Images/sword/galaxy_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	_vItem[1].item_info = " Damage : 60-80\n Speed : 4";
	_vItem[1].sell_price = 1300;
	_vItem[1].buy_price = 50000;
	_vItem[1].item_kind = WEAPON;

	_vItem[2].item_image = IMAGEMANAGER->addImage("pencil", "Images/sword/pencil.bmp", 55, 45, true, RGB(255, 0, 255));
	_vItem[2].item_info = " Damage : 1-3 \n Speed : 3";
	_vItem[2].item_kind = WEAPON;

	_vItem[3].item_image = IMAGEMANAGER->addImage("rusty_sword", "Images/sword/rusty_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	_vItem[3].item_info = " Damage : 2-5";
	_vItem[3].sell_price = 50;
	_vItem[3].item_kind = WEAPON;

	_vItem[4].item_image = IMAGEMANAGER->addImage("rusty_sword", "Images/sword/rusty_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	_vItem[4].item_info = " Damage : 2-5";
	_vItem[4].sell_price = 50;
	_vItem[4].item_kind = WEAPON;

	_vItem[5].item_image = IMAGEMANAGER->addImage("rusty_sword", "Images/sword/rusty_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	_vItem[5].item_info = " Damage : 2-5";
	_vItem[5].sell_price = 50;
	_vItem[5].item_kind = WEAPON;

	_vItem[6].item_image = IMAGEMANAGER->addImage("rusty_sword", "Images/sword/rusty_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	_vItem[6].item_info = " Damage : 2-5";
	_vItem[6].sell_price = 50;
	_vItem[6].item_kind = WEAPON;

	return S_OK;
}

void item::release()
{
}

void item::update()
{
}

void item::render()
{
}
