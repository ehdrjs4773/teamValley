#include "stdafx.h"
#include "inventoryCraft.h"
#include "inventory.h"

void inventoryCraft::init()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			_CraftItem.item_image = IMAGEMANAGER->findImage("����������");
			_CraftItem.indexX = j;
			_CraftItem.indexY = i;
			_vCraftItem.push_back(_CraftItem);
		}
	}
}

void inventoryCraft::update()
{

	for (int i = 0; i < _vCraftItem.size(); i++)
	{
		if (_vCraftItem[i].item_image == NULL)
		{
			_vCraftItem[i].item_image = IMAGEMANAGER->findImage("���������۾���");
		}
		_vCraftItem[i].rc = RectMake(250 + i % 6 * 50, 130 + i / 6 * 40, 40, 40);
	
	}

	for (int i = 0; i < _inven->getvInven().size(); i++)
	{
		if (_inven->getvInven()[i].item_image != NULL)
		{
			if (_inven->getvInven()[i].item_kind == ITEM_DEBRIS && _inven->getvInven()[i].indexX == 6 && _inven->getvInven()[i].indexY == 2)
			{
				if (_inven->getvInven()[i].amount >= 10)
				{

					_vCraftItem[0].item_image = IMAGEMANAGER->findImage("����������");
					_vCraftItem[6].item_image = IMAGEMANAGER->findImage("����������");
					if (PtInRect(&_vCraftItem[0].rc, _ptMouse) || PtInRect(&_vCraftItem[6].rc, _ptMouse))
					{
						if (INPUT->GetKeyDown(VK_LBUTTON))
						{
							tagItem box;
							box.item_image = IMAGEMANAGER->findImage("������");
							box.item_info = "����";
							box.indexX = 0;
							box.indexY = 0;
							box.item_kind = ITEM_BOX;

							_inven->setMouseItem(box);
							_inven->setInvenItemAmount(i, _inven->getvInven()[i].amount - 10);
						}
					}

				}
				else if (_inven->getvInven()[i].amount < 10)
				{
					if (_vCraftItem[0].item_image != IMAGEMANAGER->findImage("���������۾���") &&
						_vCraftItem[6].item_image != IMAGEMANAGER->findImage("���������۾���"))
					{
						_vCraftItem[0].item_image = IMAGEMANAGER->findImage("���������۾���");
						_vCraftItem[6].item_image = IMAGEMANAGER->findImage("���������۾���");
					}
				}
			}
			else
			{

			}
		}
		
	}
}
void inventoryCraft::release()
{
}

void inventoryCraft::render(HDC hdc)
{
	// IMAGEMANAGER->frameRender("����������", hdc, 225, 30);
	for (int i = 0; i < _vCraftItem.size(); i++)
	{
		if (_vCraftItem[i].item_image != NULL)
		{
			
			_vCraftItem[i].item_image->frameRender(hdc, _vCraftItem[i].rc.left, _vCraftItem[i].rc.top, _vCraftItem[i].indexX, _vCraftItem[i].indexY);

		}
		//Rectangle(hdc, _vCraftItem[i].rc); 
	}

	//if (INPUT->GetToggleKey(VK_F1))
	//{
	//	for (int i = 0; i < _vCraftItem.size(); i++)
	//	{
	//		Rectangle(hdc, _vCraftItem[i].rc);
	//	}
	//}
	
}

void inventoryCraft::craftInven_item_info(HDC hdc)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (PtInRect(&_vCraftItem[i].rc, _ptMouse)|| PtInRect(&_vCraftItem[j].rc, _ptMouse))
			{
				if (_vCraftItem[i].item_image != NULL && _vCraftItem[j].item_image != NULL)
				{
					char temp_info[2][256];
					RECT temp1 = RectMake(_ptMouse.x + 35, _ptMouse.y + 45, 200, 50);
					RECT temp2 = RectMake(temp1.left, temp1.bottom, 200, 100);
					IMAGEMANAGER->findImage("����������")->render(hdc, _ptMouse.x + 25, _ptMouse.y + 25);

					SetTextColor(hdc, RGB(0, 0, 0));

					memset(temp_info, 0, sizeof(temp_info));


					if (PtInRect(&_vCraftItem[0].rc, _ptMouse) || PtInRect(&_vCraftItem[6].rc, _ptMouse))
					{
						sprintf(temp_info[0], "������", sizeof("������"));
					}
					else if (PtInRect(&_vCraftItem[1].rc, _ptMouse) || PtInRect(&_vCraftItem[7].rc, _ptMouse))
					{
						sprintf(temp_info[0], "������", sizeof("������"));
					}
					else if (PtInRect(&_vCraftItem[2].rc, _ptMouse) || PtInRect(&_vCraftItem[8].rc, _ptMouse))
					{
						sprintf(temp_info[0], "�����", sizeof("�����"));
					}
					else if (PtInRect(&_vCraftItem[3].rc, _ptMouse) || PtInRect(&_vCraftItem[9].rc, _ptMouse))
					{
						sprintf(temp_info[0], "����ƺ�", sizeof("����ƺ�"));
					}
					else if (PtInRect(&_vCraftItem[4].rc, _ptMouse) || PtInRect(&_vCraftItem[10].rc, _ptMouse))
					{
						sprintf(temp_info[0], "�뱤��", sizeof("�뱤��"));
					}
					else if (PtInRect(&_vCraftItem[5].rc, _ptMouse) || PtInRect(&_vCraftItem[11].rc, _ptMouse))
					{
						sprintf(temp_info[0], "������", sizeof("������"));
					}

					sprintf(temp_info[1], _vCraftItem[i].item_info, sizeof(_vCraftItem[i].item_info));

					DrawText(hdc, temp_info[0], strlen(temp_info[0]), &temp1, NULL);
					DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp2, NULL);
				}
			}
		}
	}
}
