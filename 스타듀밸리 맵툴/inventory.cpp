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


	_vItem[0].item_image = IMAGEMANAGER->addFrameImage("�۹�", "Images/BMP/�۹�.bmp", 256, 784, 16, 49);
	_vItem[0].item_info = "�Ľ��վ���";
	_vItem[0].buy_price = 0;
	_vItem[0].item_kind = SEED;
	_vItem[0].indexX = 0;
	_vItem[0].indexY = 42;








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
	IMAGEMANAGER->render("playerInventory", hdc, WINSIZEX / 2 - 282, 520);

	for (int i = 0; i < 12; i++)
	{
		if (_vItem[i].item_image != NULL)
		{
			_vItem[i].item_image->frameRender(hdc, _playerTool[i].left, _playerTool[i].top, _vItem[i].indexX, _vItem[i].indexY);
		}

		if (PtInRect(&_playerTool[i], _ptMouse))
		{
			RECT temp{ _playerTool[i].left,_playerTool[i].top,_playerTool[i].right,_playerTool[i].bottom };
			FrameRect(hdc, temp, RGB(255, 0, 0));
		}
	}




}

