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

	_isWood = NULL;
	_isRock = NULL;
	_isIron = NULL;
	_isCopper = NULL;

	_isTemp3 = false;
	_isTemp4 = false;


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
			craftInven_item_info(hdc);
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
	for (int j = 0; j < _inven->getvInven().size(); j++) //����
	{
		if (_inven->getvInven()[j].item_kind == ITEM_DEBRIS && _inven->getvInven()[j].indexX == 6 && _inven->getvInven()[j].indexY == 2)
		{
			_isWood = j;
			break;
		}
	}

	for (int k = 0; k < _inven->getvInven().size(); k++) //��
	{
		if (_inven->getvInven()[k].item_kind == ITEM_DEBRIS && _inven->getvInven()[k].indexX == 5 && _inven->getvInven()[k].indexY == 2)
		{
			_isRock = k;
			break;
		}
	}

	for (int l = 0; l < _inven->getvInven().size(); l++) //ö
	{
		if (_inven->getvInven()[l].item_kind == ITEM_ORE && _inven->getvInven()[l].indexX == 8 && _inven->getvInven()[l].indexY == 3)
		{
			_isIron = l;
			break;
		}
	}

	for (int m = 0; m < _inven->getvInven().size(); m++) //����
	{
		if (_inven->getvInven()[m].item_kind == ITEM_ORE && _inven->getvInven()[m].indexX == 6 && _inven->getvInven()[m].indexY == 3)
		{
			_isCopper = m;
			break;
		}
	}

	for (int i = 0; i < _vCraftItem.size(); i++)
	{
		if (PtInRect(&_vCraftItem[i].rc, _ptMouse))
		{
			if (_vCraftItem[i].item_image != NULL)
			{
				char temp_info[3][256];
				RECT temp1 = RectMake(_ptMouse.x + 35, _ptMouse.y + 45, 200, 50);
				RECT temp2 = RectMake(temp1.left, temp1.bottom, 200, 100);
				RECT temp3 = RectMake(temp2.left + 40, temp2.top, 160, 40);
				RECT temp4 = RectMake(temp2.left + 40, temp3.bottom, 160, 40);

				IMAGEMANAGER->findImage("����������")->render(hdc, _ptMouse.x + 25, _ptMouse.y + 25);

				SetTextColor(hdc, RGB(0, 0, 0));

				memset(temp_info, 0, sizeof(temp_info));


				if (PtInRect(&_vCraftItem[0].rc, _ptMouse) || PtInRect(&_vCraftItem[6].rc, _ptMouse)) //������ ��Ʈ�� ������
				{
					IMAGEMANAGER->frameRender("����", hdc, temp2.left-5 , temp2.top-5 , 6, 2);

					sprintf(temp_info[0], "������", sizeof("������"));
					sprintf(temp_info[1], ": ���� 10��", sizeof(": ���� 10��"));

					if (_isWood != NULL)
					{
						if (_inven->getvInven()[_isWood].amount < 10)
						{
							SetTextColor(hdc, RGB(255, 0, 0));
							DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						}
						else if (_inven->getvInven()[_isWood].amount >= 10)
						{
							SetTextColor(hdc, RGB(0, 0, 0));
							DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						}
					}
					else
					{ 
					SetTextColor(hdc, RGB(255, 0, 0));
					DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
					}
				}
				else if (PtInRect(&_vCraftItem[1].rc, _ptMouse) || PtInRect(&_vCraftItem[7].rc, _ptMouse)) //������ ��Ʈ�� ������ 
				{
					IMAGEMANAGER->frameRender("����", hdc, temp2.left - 5, temp2.top - 5, 6, 2);

					sprintf(temp_info[0], "������", sizeof("������"));
					sprintf(temp_info[1], ": ���� 15��", sizeof(": ���� 15��"));

					if (_isWood != NULL)
					{
						if (_inven->getvInven()[_isWood].amount < 15)
						{
							SetTextColor(hdc, RGB(255, 0, 0));
							DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						}
						else if (_inven->getvInven()[_isWood].amount >= 15)
						{
							SetTextColor(hdc, RGB(0, 0, 0));
							DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						}
					}
					else
					{
						SetTextColor(hdc, RGB(255, 0, 0));
						DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
					}
				}
				else if (PtInRect(&_vCraftItem[2].rc, _ptMouse) || PtInRect(&_vCraftItem[8].rc, _ptMouse)) //����� ��Ʈ�� ������ 
				{
					sprintf(temp_info[0], "�����", sizeof("�����"));
					sprintf(temp_info[1], ": ���� 20��", sizeof(": ���� 20��"));
					sprintf(temp_info[2], ": ö ���� 10��", sizeof(": ö ���� 10��"));

					IMAGEMANAGER->frameRender("����", hdc, temp2.left - 5, temp2.top - 5, 6, 2);
					IMAGEMANAGER->frameRender("����", hdc, temp2.left - 5, temp2.top - 5, 8, 3);
				
					if (_isWood != NULL || _isIron !=NULL)
					{
						if (_inven->getvInven()[_isWood].amount < 20)
						{
							SetTextColor(hdc, RGB(255, 0, 0));
							DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						}
						else if (_inven->getvInven()[_isWood].amount >= 20)
						{
							SetTextColor(hdc, RGB(0, 0, 0));
							DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						}

						if (_inven->getvInven()[_isIron].amount < 10)
						{
							SetTextColor(hdc, RGB(255, 0, 0));
							DrawText(hdc, temp_info[2], strlen(temp_info[2]), &temp4, NULL);
						}
						else if (_inven->getvInven()[_isIron].amount >= 10)
						{
							SetTextColor(hdc, RGB(0, 0, 0));
							DrawText(hdc, temp_info[2], strlen(temp_info[2]), &temp4, NULL);
						}
					}
					else
					{
						SetTextColor(hdc, RGB(255, 0, 0));
						DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						DrawText(hdc, temp_info[2], strlen(temp_info[2]), &temp4, NULL);
					}
				}
				else if (PtInRect(&_vCraftItem[3].rc, _ptMouse) || PtInRect(&_vCraftItem[9].rc, _ptMouse)) //����ƺ� ��Ʈ�� ������ 
				{
					sprintf(temp_info[0], "����ƺ�", sizeof("����ƺ�"));
					sprintf(temp_info[1], ": ���� 15��", sizeof(": ���� 15��"));
					sprintf(temp_info[2], ": �� 5��", sizeof(": �� 5��"));

					IMAGEMANAGER->frameRender("����", hdc, temp2.left +5, temp2.top - 5, 6, 2);
					IMAGEMANAGER->frameRender("����", hdc, temp2.left + 5, temp2.top + 35, 5, 2);

					if (_isWood != NULL || _isRock != NULL)
					{
						if (_inven->getvInven()[_isWood].amount < 15)
						{
							SetTextColor(hdc, RGB(255, 0, 0));
							DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						}
						else if (_inven->getvInven()[_isWood].amount >= 15)
						{
							SetTextColor(hdc, RGB(0, 0, 0));
							DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						}

						if (_inven->getvInven()[_isRock].amount < 5)
						{
							SetTextColor(hdc, RGB(255, 0, 0));
							DrawText(hdc, temp_info[2], strlen(temp_info[1]), &temp4, NULL);
						}
						else if (_inven->getvInven()[_isRock].amount >= 5)
						{
							SetTextColor(hdc, RGB(0, 0, 0));
							DrawText(hdc, temp_info[2], strlen(temp_info[1]), &temp4, NULL);
						}
					}
					else
					{
						SetTextColor(hdc, RGB(255, 0, 0));
						DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						DrawText(hdc, temp_info[2], strlen(temp_info[2]), &temp4, NULL);
					}
				}
				else if (PtInRect(&_vCraftItem[4].rc, _ptMouse) || PtInRect(&_vCraftItem[10].rc, _ptMouse)) //�뱤�� ��Ʈ�� ������ 
				{
					sprintf(temp_info[0], "�뱤��", sizeof("�뱤��"));
					sprintf(temp_info[1], ": �������� 15��", sizeof(": �������� 15��"));
					sprintf(temp_info[2], ": �� 20��", sizeof(": �� 20��"));

					IMAGEMANAGER->frameRender("����", hdc, temp2.left + 5, temp2.top + 35, 6, 3);
					IMAGEMANAGER->frameRender("����", hdc, temp2.left + 5, temp2.top - 5, 5, 2);

					if (_isCopper != NULL || _isRock != NULL)
					{
						if (_inven->getvInven()[_isCopper].amount < 15)
						{
							SetTextColor(hdc, RGB(255, 0, 0));
							DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						}
						else if (_inven->getvInven()[_isCopper].amount >= 15)
						{
							SetTextColor(hdc, RGB(0, 0, 0));
							DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						}

						if (_inven->getvInven()[_isRock].amount < 20)
						{
							SetTextColor(hdc, RGB(255, 0, 0));
							DrawText(hdc, temp_info[2], strlen(temp_info[1]), &temp4, NULL);
						}
						else if (_inven->getvInven()[_isRock].amount >= 20)
						{
							SetTextColor(hdc, RGB(0, 0, 0));
							DrawText(hdc, temp_info[2], strlen(temp_info[1]), &temp4, NULL);
						}
					}
					else
					{
						SetTextColor(hdc, RGB(255, 0, 0));
						DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						DrawText(hdc, temp_info[2], strlen(temp_info[2]), &temp4, NULL);
					}
				}
				else if (PtInRect(&_vCraftItem[5].rc, _ptMouse) || PtInRect(&_vCraftItem[11].rc, _ptMouse)) //������ ��Ʈ�� ������ 
				{
					sprintf(temp_info[0], "������", sizeof("������"));
					sprintf(temp_info[1], ": ���� 15��", sizeof(": ���� 15��"));
					sprintf(temp_info[2], ": �� 20��", sizeof(": �� 20��"));

					IMAGEMANAGER->frameRender("����", hdc, temp2.left + 5, temp2.top - 5, 6, 2);
					IMAGEMANAGER->frameRender("����", hdc, temp2.left + 5, temp2.top + 35, 5, 2);

					if (_isWood != NULL || _isRock != NULL)
					{
						if (_inven->getvInven()[_isWood].amount < 15)
						{
							SetTextColor(hdc, RGB(255, 0, 0));
							DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						}
						else if (_inven->getvInven()[_isWood].amount >= 15)
						{
							SetTextColor(hdc, RGB(0, 0, 0));
							DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						}

						if (_inven->getvInven()[_isRock].amount < 20)
						{
							SetTextColor(hdc, RGB(255, 0, 0));
							DrawText(hdc, temp_info[2], strlen(temp_info[1]), &temp4, NULL);
						}
						else if (_inven->getvInven()[_isRock].amount >= 20)
						{
							SetTextColor(hdc, RGB(0, 0, 0));
							DrawText(hdc, temp_info[2], strlen(temp_info[1]), &temp4, NULL);
						}
					}
					else
					{
						SetTextColor(hdc, RGB(255, 0, 0));
						DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						DrawText(hdc, temp_info[2], strlen(temp_info[2]), &temp4, NULL);
					}
				}
				DrawText(hdc, temp_info[0], strlen(temp_info[0]), &temp1, NULL);
			}
		}
	}
}
