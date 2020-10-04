#include "stdafx.h"
#include "inventory.h"

HRESULT inventory::init()
{
	IMAGEMANAGER->addImage("인벤토리_아이템","Images/shop/inventory.bmp", 750, 200,true,RGB(255,0,255));

	for (int i = 0; i < INVENMAX; i++)
	{
		tagItem temp;
		temp.rc = RectMake(270 + 59 * (i % 12), 400 + 55 * (i / 12), 55, 45);
		temp.item_image = NULL;
		_vItem.push_back(temp);
	}

	return S_OK;
}

void inventory::release()
{
}

void inventory::update()
{

}


void inventory::render()
{
	inventory_img = IMAGEMANAGER->findImage("인벤토리_아이템");
	inventory_img->render(getMemDC(), 250,375);
	for (int i = 0; i < INVENMAX; i++)
	{
		if (_vItem[i].item_image != NULL)
		{
			_vItem[i].item_image->render(getMemDC(), _vItem[i].rc.left, _vItem[i].rc.top);
		}
	}
}
