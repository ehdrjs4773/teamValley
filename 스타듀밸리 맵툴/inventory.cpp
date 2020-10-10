#include "stdafx.h"
#include "inventory.h"

void inventory::init()
{

	IMAGEMANAGER->addFrameImage("씨앗", "Images/BMP/씨앗아이템.bmp", 360, 160, 9, 4);
	IMAGEMANAGER->addFrameImage("도구", "Images/BMP/도구.bmp", 360, 160, 9, 4);
	IMAGEMANAGER->addImage("주전자 바", "Images/BMP/주전자 바.bmp", 40, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점인벤토리", "Images/shop/inventory.bmp", 750, 200, true, RGB(255, 0, 255));


	for (int i = 0; i < INVENMAX; i++)
	{
		tagItem temp;
		temp.rc = RectMake(270 + 59 * (i % 12), 400 + 55 * (i / 12), 55, 45);
		temp.item_image = NULL;
		_vItem.push_back(temp);
	}

	_vItem[0] = ITEMMANAGER->findItem("파스닙 씨앗");
	_vItem[1] = ITEMMANAGER->findItem("완두콩 씨앗");
	_vItem[3] = ITEMMANAGER->findItem("호미");
	_vItem[4] = ITEMMANAGER->findItem("곡괭이");
	_vItem[5] = ITEMMANAGER->findItem("도끼");
	_vItem[6] = ITEMMANAGER->findItem("주전자");
	_vItem[6].waterAmount = 100;
	_vItem[7] = ITEMMANAGER->findItem("낚시대");
	_vItem[8] = ITEMMANAGER->findItem("칼");

	_MouseItem.item_image = NULL;

	_isInventoryMove = false;
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
	craftObject();

	if(_MouseItem.item_image) _MouseItem.rc = RectMake(_ptMouse.x, _ptMouse.y, _MouseItem.item_image->getFrameWidth(), _MouseItem.item_image->getFrameHeight());
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i].rc = RectMake(270 + 59 * (i % 12), 400 + 55 * (i / 12), 55, 45);
	}



	for (int i = 0; i < _vItem.size(); i++)
	{
		if(PtInRect(&_vItem[i].rc, _ptMouse))
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				if (_vItem[i].item_image != NULL) // 아이템이 있으면
				{
					if (_MouseItem.item_image != NULL) // 마우스에 아이템이 있으면
					{
						tagItem exchangeItem; // 교환용 아이템
						exchangeItem = _vItem[i];
						_vItem[i] = _MouseItem;
						_MouseItem = exchangeItem;
					}	

					else if (_MouseItem.item_image == NULL) // 마우스에 아이템이 없으면
					{
						tagItem pushItem;
						pushItem.item_image = NULL;
						_MouseItem = _vItem[i];
						_vItem[i] = pushItem;
					}

				} 

				else if (_vItem[i].item_image == NULL)
				{
					if (_MouseItem.item_image != NULL)
					{
						tagItem clearItem;
						clearItem.item_image = NULL;
						_vItem[i] = _MouseItem;
						_MouseItem = clearItem;
					}
				}


			}

		}
	}

	

}


void inventory::render(HDC hdc)
{
	inventory_img = IMAGEMANAGER->findImage("상점인벤토리");
	inventory_img->render(hdc, 250,375);

	for (int i = 0; i < _vItem.size(); i++)
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

	if (_MouseItem.item_image)_MouseItem.item_image->frameRender(hdc, _MouseItem.rc.left, _MouseItem.rc.top, _MouseItem.indexX, _MouseItem.indexY);

}

void inventory::quickSlot(HDC hdc)
{
	IMAGEMANAGER->render("플레이어 퀵슬롯", hdc, WINSIZEX / 2 - 282, 520);

	for (int i = 0; i < 12; i++)
	{
		if (_vItem[i].item_image != NULL)
		{
			_vItem[i].item_image->frameRender(hdc, _playerTool[i].left, _playerTool[i].top, _vItem[i].indexX, _vItem[i].indexY);
			if (_vItem[i].amount >= 0)
			{
				char str[64];
				wsprintf(str, "%d", _vItem[i].amount);
				
				textOut(hdc, _playerTool[i].left + 30, _playerTool[i].top + 30, str, RGB(0, 0, 0));			}
			
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

void inventory::craftObject()
{
}

