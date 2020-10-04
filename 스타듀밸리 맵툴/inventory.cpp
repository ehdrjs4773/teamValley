#include "stdafx.h"
#include "inventory.h"

void inventory::init()
{
	for (int i = 0; i < INVENMAX; i++)
	{
		tagItem temp;
		temp.rc = RectMake(270 + 59 * (i % 12), 400 + 55 * (i / 12), 55, 45);
		temp.item_image = NULL;
		_vItem.push_back(temp);
	}

	for (int i = 0; i < 12; i++)
	{
		_playerTool[i] = RectMake(333 + i * 45, 535, 40, 40);
	}


}

void inventory::release()
{
}

void inventory::update()
{
	cout << _ptMouse.x << "\t" << _ptMouse.y << endl;

	for (int i = 0; i < 12; i++)
	{
		if (PtInRect(&_playerTool[i], _ptMouse))
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				//if (_playerTool[i] == //µµ³¢)
				//{
				//	
				//}

				//else if (_playerTool[i] == //°î±ªÀÌ)
				//{

				//}

				//else if (_playerTool[i] == //»ð)
				//{

				//}

				//else if (_playerTool[i] == //ÁÖÀüÀÚ)
				//{

				//}

				//else if (_playerTool[i] == //³´)
				//{

				//}
			}
		}
	}
}


void inventory::render(HDC hdc)
{
	inventory_img = IMAGEMANAGER->findImage("ÀÎº¥Åä¸®_¾ÆÀÌÅÛ");
	inventory_img->render(hdc, 250,375);
	for (int i = 0; i < INVENMAX; i++)
	{
		if (_vItem[i].item_image != NULL)
		{
			_vItem[i].item_image->render(hdc, _vItem[i].rc.left, _vItem[i].rc.top);
		}
	}

	IMAGEMANAGER->render("playerInventory", hdc, WINSIZEX / 2 - 282, 520);

	for (int i = 0; i < 12; i++)
	{
		Rectangle(hdc, _playerTool[i]);
		if (PtInRect(&_playerTool[i], _ptMouse))
		{
			RECT temp{ _playerTool[i].left,_playerTool[i].top,_playerTool[i].right,_playerTool[i].bottom };
			FrameRect(hdc, temp, RGB(255, 0, 0));
		}
	}
}
