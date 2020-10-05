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

	_vItem[0] = ITEMMANAGER->findItem("ÆÄ½º´Õ ¾¾¾Ñ");
	_vItem[1] = ITEMMANAGER->findItem("¿ÏµÎÄá ¾¾¾Ñ");
	_vItem[3] = ITEMMANAGER->findItem("È£¹Ì");
	_vItem[4] = ITEMMANAGER->findItem("°î±ªÀÌ");
	_vItem[5] = ITEMMANAGER->findItem("µµ³¢");
	_vItem[6] = ITEMMANAGER->findItem("ÁÖÀüÀÚ");
	_vItem[7] = ITEMMANAGER->findItem("³¬½Ã´ë");
	_vItem[8] = ITEMMANAGER->findItem("Ä®");

	currentSlotNumber = 0;

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
	setCurrentSlotNumber(_mouseWheel);
}


void inventory::render(HDC hdc)
{

	inventory_img = IMAGEMANAGER->findImage("ÀÎº¥Åä¸®_¾ÆÀÌÅÛ");
	inventory_img->render(hdc, 250,375);

	for (int i = 0; i < INVENMAX; i++)
	{
		if (_vItem[i].item_image != NULL)
		{
			_vItem[i].item_image->frameRender(hdc, _vItem[i].rc.left, _vItem[i].rc.top,_vItem[i].indexX,_vItem[i].indexY);
		}
	}
}

void inventory::quickSlot(HDC hdc)
{
	IMAGEMANAGER->render("ÇÃ·¹ÀÌ¾î Äü½½·Ô", hdc, WINSIZEX / 2 - 282, 520);

	for (int i = 0; i < 12; i++)
	{
		if (_vItem[i].item_image != NULL)
		{
			_vItem[i].item_image->frameRender(hdc, _playerTool[i].left, _playerTool[i].top, _vItem[i].indexX, _vItem[i].indexY);
		}

		if (PtInRect(&_playerTool[i], _ptMouse))
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				currentSlotNumber = i;
			}
			
			//RECT temp{ _playerTool[i].left,_playerTool[i].top,_playerTool[i].right,_playerTool[i].bottom };
			//FrameRect(hdc, temp, RGB(0, 0, 255));
		}
		else
		{
			RECT temp{ _playerTool[currentSlotNumber].left,_playerTool[currentSlotNumber].top,_playerTool[currentSlotNumber].right,_playerTool[currentSlotNumber].bottom };
			FrameRect(hdc, temp, RGB(255, 0, 0));
		}
	}
	if (INPUT->GetKeyDown('1'))
	{
		currentSlotNumber = 0;
	}
	if (INPUT->GetKeyDown('2'))
	{
		currentSlotNumber = 1;
	}
	if (INPUT->GetKeyDown('3'))
	{
		currentSlotNumber = 2;
	}
	if (INPUT->GetKeyDown('4'))
	{
		currentSlotNumber = 3;
	}
	if (INPUT->GetKeyDown('5'))
	{
		currentSlotNumber = 4;
	}
	if (INPUT->GetKeyDown('6'))
	{
		currentSlotNumber = 5;
	}
	if (INPUT->GetKeyDown('7'))
	{
		currentSlotNumber = 6;
	}
	if (INPUT->GetKeyDown('8'))
	{
		currentSlotNumber = 7;
	}
	if (INPUT->GetKeyDown('9'))
	{
		currentSlotNumber = 8;
	}
	if (INPUT->GetKeyDown('0'))
	{
		currentSlotNumber = 9;
	}
	if (INPUT->GetKeyDown(VK_OEM_MINUS))
	{
		currentSlotNumber = 10;
	}
	if (INPUT->GetKeyDown(VK_OEM_PLUS))
	{
		currentSlotNumber = 11;
	}
}

