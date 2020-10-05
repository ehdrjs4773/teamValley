#include "stdafx.h"
#include "inventory.h"

void inventory::init()
{
	IMAGEMANAGER->addFrameImage("����", "Images/BMP/���Ѿ�����.bmp", 360, 160, 9, 4);
	IMAGEMANAGER->addFrameImage("����", "Images/BMP/����.bmp", 360, 160, 9, 4);

	for (int i = 0; i < INVENMAX; i++)
	{
		tagItem temp;
		temp.rc = RectMake(270 + 59 * (i % 12), 400 + 55 * (i / 12), 55, 45);
		temp.item_image = NULL;
		_vItem.push_back(temp);
	}

	_vItem[0].item_image = IMAGEMANAGER->findImage("����");
	_vItem[0].item_info = "�Ľ��� ����";
	_vItem[0].buy_price = 0;
	_vItem[0].item_kind = ITEM_SEED;
	_vItem[0].seedKind = SEED_PARSNIP;
	_vItem[0].indexX = 0;
	_vItem[0].indexY = 0;

	_vItem[1].item_image = IMAGEMANAGER->findImage("����");
	_vItem[1].item_info = "�ϵ��� ����";
	_vItem[1].buy_price = 0;
	_vItem[1].item_kind = ITEM_SEED;
	_vItem[1].seedKind = SEED_GREENBEAN;
	_vItem[1].indexX = 1;
	_vItem[1].indexY = 0;

	_vItem[3].item_image = IMAGEMANAGER->findImage("����");
	_vItem[3].item_info = "ȣ��";
	_vItem[3].buy_price = 0;
	_vItem[3].item_kind = ITEM_TOOL;
	_vItem[3].toolKind= TOOL_HOE;
	_vItem[3].indexX = 0;
	_vItem[3].indexY = 0;

	_vItem[4].item_image = IMAGEMANAGER->findImage("����");
	_vItem[4].item_info = "���";
	_vItem[4].buy_price = 0;
	_vItem[4].item_kind = ITEM_TOOL;
	_vItem[4].toolKind = TOOL_PICKAX;
	_vItem[4].indexX = 1;
	_vItem[4].indexY = 0;

	_vItem[5].item_image = IMAGEMANAGER->findImage("����");
	_vItem[5].item_info = "����";
	_vItem[5].buy_price = 0;
	_vItem[5].item_kind = ITEM_TOOL;
	_vItem[5].toolKind = TOOL_AX;
	_vItem[5].indexX = 2;
	_vItem[5].indexY = 0;

	_vItem[6].item_image = IMAGEMANAGER->findImage("����");
	_vItem[6].item_info = "������";
	_vItem[6].buy_price = 0;
	_vItem[6].item_kind = ITEM_TOOL;
	_vItem[6].toolKind = TOOL_KETTLE;
	_vItem[6].indexX = 3;
	_vItem[6].indexY = 0;

	_vItem[7].item_image = IMAGEMANAGER->findImage("����");
	_vItem[7].item_info = "���ô�";
	_vItem[7].buy_price = 0;
	_vItem[7].item_kind = ITEM_TOOL;
	_vItem[7].toolKind = TOOL_FISHINGROD;
	_vItem[7].indexX = 4;
	_vItem[7].indexY = 0;

	_vItem[8].item_image = IMAGEMANAGER->findImage("����");
	_vItem[8].item_info = "Į";
	_vItem[8].buy_price = 0;
	_vItem[8].item_kind = ITEM_TOOL;
	_vItem[8].toolKind = TOOL_SWORD;
	_vItem[8].indexX = 5;
	_vItem[8].indexY = 0;

	_vItem[4].item_image = IMAGEMANAGER->findImage("����");
	_vItem[4].item_info = "����";
	_vItem[4].buy_price = 0;
	_vItem[4].item_kind = ITEM_TOOL;
	_vItem[4].toolKind = TOOL_AX;
	_vItem[4].seedKind = SEED_NONE;
	_vItem[4].indexX = 3;
	_vItem[4].indexY = 0;

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
	std::cout << currentSlotNumber << std::endl;

	setCurrentSlotNumber(_mouseWheel);

	for (int i = 0; i < 12; i++)
	{
		if (PtInRect(&_playerTool[i], _ptMouse))
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				//if (_playerTool[i] == //����)
				//{
				//	
				//}

				//else if (_playerTool[i] == //���)
				//{

				//}

				//else if (_playerTool[i] == //��)
				//{
				 
				//}

				//else if (_playerTool[i] == //������)
				//{

				//}

				//else if (_playerTool[i] == //��)
				//{

				//}
			}
		}
	}
}


void inventory::render(HDC hdc)
{

	inventory_img = IMAGEMANAGER->findImage("�κ��丮_������");
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
	IMAGEMANAGER->render("�÷��̾� ������", hdc, WINSIZEX / 2 - 282, 520);

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
			
			RECT temp{ _playerTool[i].left,_playerTool[i].top,_playerTool[i].right,_playerTool[i].bottom };
			FrameRect(hdc, temp, RGB(255, 0, 0));
		}
	}
}

