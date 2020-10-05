#include "stdafx.h"
#include "inventory.h"

void inventory::init()
{
<<<<<<< HEAD
	IMAGEMANAGER->addFrameImage("¾¾¾Ñ", "Images/BMP/¾¾¾Ñ¾ÆÀÌÅÛ.bmp", 360, 160, 9, 4);
	IMAGEMANAGER->addFrameImage("µµ±¸", "Images/BMP/µµ±¸.bmp", 360, 160, 9, 4);
	IMAGEMANAGER->addFrameImage("ÁÖÀüÀÚ ¹Ù", "Images/BMP/ÁÖÀüÀÚ ¹Ù.bmp", 40, 10, 9, 4);

=======
	IMAGEMANAGER->addImage("»óÁ¡ÀÎº¥Åä¸®", "Images/shop/inventory.bmp", 750, 200, true, RGB(255, 0, 255));
>>>>>>> 997524e2cd608d2345e17b2a8aa9a355f8d3f79b

	for (int i = 0; i < INVENMAX; i++)
	{
		tagItem temp;
		temp.rc = RectMake(270 + 59 * (i % 12), 400 + 55 * (i / 12), 55, 45);
		temp.item_image = NULL;
		_vItem.push_back(temp);
	}

<<<<<<< HEAD
	_vItem[0].item_image = IMAGEMANAGER->findImage("¾¾¾Ñ");
	_vItem[0].item_info = "ÆÄ½º´Õ ¾¾¾Ñ";
	_vItem[0].buy_price = 0;
	_vItem[0].item_kind = ITEM_SEED;
	_vItem[0].seedKind = SEED_PARSNIP;
	_vItem[0].indexX = 0;
	_vItem[0].indexY = 0;

	_vItem[1].item_image = IMAGEMANAGER->findImage("¾¾¾Ñ");
	_vItem[1].item_info = "¿ÏµÎÄá ¾¾¾Ñ";
	_vItem[1].buy_price = 0;
	_vItem[1].item_kind = ITEM_SEED;
	_vItem[1].seedKind = SEED_GREENBEAN;
	_vItem[1].indexX = 1;
	_vItem[1].indexY = 0;

	_vItem[3].item_image = IMAGEMANAGER->findImage("µµ±¸");
	_vItem[3].item_info = "È£¹Ì";
	_vItem[3].buy_price = 0;
	_vItem[3].item_kind = ITEM_TOOL;
	_vItem[3].toolKind= TOOL_HOE;
	_vItem[3].indexX = 0;
	_vItem[3].indexY = 0;

	_vItem[4].item_image = IMAGEMANAGER->findImage("µµ±¸");
	_vItem[4].item_info = "°î±ªÀÌ";
	_vItem[4].buy_price = 0;
	_vItem[4].item_kind = ITEM_TOOL;
	_vItem[4].toolKind = TOOL_PICKAX;
	_vItem[4].indexX = 1;
	_vItem[4].indexY = 0;

	_vItem[5].item_image = IMAGEMANAGER->findImage("µµ±¸");
	_vItem[5].item_info = "µµ³¢";
	_vItem[5].buy_price = 0;
	_vItem[5].item_kind = ITEM_TOOL;
	_vItem[5].toolKind = TOOL_AX;
	_vItem[5].indexX = 2;
	_vItem[5].indexY = 0;

	_vItem[6].item_image = IMAGEMANAGER->findImage("µµ±¸");
	_vItem[6].item_info = "ÁÖÀüÀÚ";
	_vItem[6].buy_price = 0;
	_vItem[6].item_kind = ITEM_TOOL;
	_vItem[6].toolKind = TOOL_KETTLE;
	_vItem[6].indexX = 3;
	_vItem[6].indexY = 0;

	_vItem[7].item_image = IMAGEMANAGER->findImage("µµ±¸");
	_vItem[7].item_info = "³¬½Ã´ë";
	_vItem[7].buy_price = 0;
	_vItem[7].item_kind = ITEM_TOOL;
	_vItem[7].toolKind = TOOL_FISHINGROD;
	_vItem[7].indexX = 4;
	_vItem[7].indexY = 0;

	_vItem[8].item_image = IMAGEMANAGER->findImage("µµ±¸");
	_vItem[8].item_info = "Ä®";
	_vItem[8].buy_price = 0;
	_vItem[8].item_kind = ITEM_TOOL;
	_vItem[8].toolKind = TOOL_SWORD;
	_vItem[8].indexX = 5;
	_vItem[8].indexY = 0;
=======
	_vItem[0] = ITEMMANAGER->findItem("ÆÄ½º´Õ ¾¾¾Ñ");
	_vItem[1] = ITEMMANAGER->findItem("¿ÏµÎÄá ¾¾¾Ñ");
	_vItem[3] = ITEMMANAGER->findItem("È£¹Ì");
	_vItem[4] = ITEMMANAGER->findItem("°î±ªÀÌ");
	_vItem[5] = ITEMMANAGER->findItem("µµ³¢");
	_vItem[6] = ITEMMANAGER->findItem("ÁÖÀüÀÚ");
	_vItem[7] = ITEMMANAGER->findItem("³¬½Ã´ë");
	_vItem[8] = ITEMMANAGER->findItem("Ä®");
>>>>>>> 997524e2cd608d2345e17b2a8aa9a355f8d3f79b

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
}


void inventory::render(HDC hdc)
{
	inventory_img = IMAGEMANAGER->findImage("»óÁ¡ÀÎº¥Åä¸®");
	inventory_img->render(hdc, 250,375);

	for (int i = 0; i < INVENMAX; i++)
	{
		if (_vItem[i].item_image != NULL)
		{
			if (_vItem[i].isFrame)
			{
				_vItem[i].item_image->frameRender(hdc, _vItem[i].rc.left+10, _vItem[i].rc.top+2,_vItem[i].indexX,_vItem[i].indexY);
			}
			else
			{
				_vItem[i].item_image->render(hdc, _vItem[i].rc.left, _vItem[i].rc.top);
			}
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

	RECT temp{ _playerTool[currentSlotNumber].left,_playerTool[currentSlotNumber].top,_playerTool[currentSlotNumber].right,_playerTool[currentSlotNumber].bottom };
	FrameRect(hdc, temp, RGB(255, 0, 0));


}

