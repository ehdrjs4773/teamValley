#include "stdafx.h"
#include "inventoryCraft.h"
#include "inventory.h"

void inventoryCraft::init()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			_CraftItem.item_image = IMAGEMANAGER->findImage("아이템제작알파");
			_CraftItem.indexX = j;
			_CraftItem.indexY = i;
			_CraftItem.rc = RectMake(250 + j % 6 * 50, 130 + i / 6 * 40, 40, 40);
			_vCraftItem.push_back(_CraftItem);
		}
	}

	_isWood = NULL;
	_isRock = NULL;
	_isIron = NULL;
	_isCopper = NULL;
	_isGold = NULL;

	_isTemp3 = false;
	_isTemp4 = false;
}
void inventoryCraft::materialUpdate()
{
	for (int i = 0; i < _inven->getvInven().size(); i++)
	{
		if (_inven->getvInven()[i].item_kind == ITEM_DEBRIS)
		{
			if (_isWood == NULL)
			{
				if (_inven->getvInven()[i].indexX == 4 && _inven->getvInven()[i].indexY == 2)
				{
					_isWood = i;
				}
			}
			else
			{
				if (_inven->getvInven()[_isWood].amount <= 0)
				{
					_isWood = NULL;
				}
			}
			if (_isRock == NULL)
			{
				if (_inven->getvInven()[i].indexX == 3 && _inven->getvInven()[i].indexY == 2)
				{
					_isRock = i;
				}
			}
			else
			{
				if (_inven->getvInven()[_isRock].amount <= 0)
				{
					_isRock = NULL;
				}
			}
		}
		else if (_inven->getvInven()[i].item_kind == ITEM_ORE)
		{
			if (_isCopper == NULL)
			{
				if (_inven->getvInven()[i].indexX == 6 && _inven->getvInven()[i].indexY == 3)
				{
					_isCopper = i;
				}
			}
			else
			{
				if (_inven->getvInven()[_isCopper].amount <= 0)
				{
					_isCopper = NULL;
				}

			}
			if (_isIron == NULL)
			{
				if (_inven->getvInven()[i].indexX == 8 && _inven->getvInven()[i].indexY == 3)
				{
					_isIron = i;

				}
			}
			else
			{
				if (_inven->getvInven()[_isIron].amount <= 0)
				{
					_isIron = NULL;
				}
			}
			if (_isGold == NULL)
			{
				if (_inven->getvInven()[i].indexX == 12 && _inven->getvInven()[i].indexY == 3)
				{
					_isGold = i;

				}
			}
			else
			{
				if (_inven->getvInven()[_isGold].amount <= 0)
				{
					_isGold = NULL;
				}
			}
		}
	}
	cout << _isWood << "  " << _isRock << "  " << _isCopper << "  " << _isIron << "  " << _isGold << endl;
}

void inventoryCraft::update()
{
	if (initCount == 0)
	{
		for (int i = 0; i < _vCraftItem.size(); i++)
		{
			if (_vCraftItem[i].item_image == NULL)
			{
				_vCraftItem[i].item_image = IMAGEMANAGER->findImage("아이템제작알파");
			}
			else
			{

			}
			_vCraftItem[i].rc = RectMake(250 + i % 6 * 50, 130 + i / 6 * 40, 40, 40);

		}
		initCount = 1;
	}

	//상자 만들기 

	if (_isWood != NULL)
	{
		if (_inven->getvInven()[_isWood].amount >= 10)
		{
			_vCraftItem[0].item_image = IMAGEMANAGER->findImage("아이템제작");
			_vCraftItem[6].item_image = IMAGEMANAGER->findImage("아이템제작");
			if (PtInRect(&_vCraftItem[0].rc, _ptMouse) || PtInRect(&_vCraftItem[6].rc, _ptMouse))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					tagItem box;
					box.item_image = IMAGEMANAGER->findImage("아이템");
					box.item_info = "상자";
					box.indexX = 0;
					box.indexY = 0;
					box.item_kind = ITEM_BOX;
					box.isFrame = true;
					box.amount = 1;

					_inven->setMouseItem(box);
					_inven->setInvenItemAmount(_isWood, _inven->getvInven()[_isWood].amount - 10);
				}
			}
		}
		else if (_inven->getvInven()[_isWood].amount < 10)
		{
			if (_vCraftItem[0].item_image != IMAGEMANAGER->findImage("아이템제작알파") &&
				_vCraftItem[6].item_image != IMAGEMANAGER->findImage("아이템제작알파"))
			{
				_vCraftItem[0].item_image = IMAGEMANAGER->findImage("아이템제작알파");
				_vCraftItem[6].item_image = IMAGEMANAGER->findImage("아이템제작알파");
			}
		}
	}
	
	//허수아비 만들기 
	if (_isWood != NULL && _isRock != NULL)
	{
		if (_inven->getvInven()[_isWood].amount >= 15 && _inven->getvInven()[_isRock].amount >= 5)
		{
			_vCraftItem[3].item_image = IMAGEMANAGER->findImage("아이템제작");
			_vCraftItem[9].item_image = IMAGEMANAGER->findImage("아이템제작");

			if (PtInRect(&_vCraftItem[3].rc, _ptMouse) || PtInRect(&_vCraftItem[9].rc, _ptMouse))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					tagItem scarecrow;
					scarecrow.item_image = IMAGEMANAGER->findImage("아이템");
					scarecrow.item_info = "허수아비";
					scarecrow.indexX = 3;
					scarecrow.indexY = 0;
					scarecrow.item_kind = ITEM_SCARECROW;
					scarecrow.isFrame = true;
					scarecrow.amount = 1;

					_inven->setMouseItem(scarecrow);
					_inven->setInvenItemAmount(_isWood, _inven->getvInven()[_isWood].amount - 15);
					_inven->setInvenItemAmount(_isRock, _inven->getvInven()[_isRock].amount - 5);

				}
			}
		}
		else if (_inven->getvInven()[_isWood].amount < 15 || _inven->getvInven()[_isRock].amount < 5)
		{
			if (_vCraftItem[3].item_image != IMAGEMANAGER->findImage("아이템제작알파") &&
				_vCraftItem[9].item_image != IMAGEMANAGER->findImage("아이템제작알파"))
			{
				_vCraftItem[3].item_image = IMAGEMANAGER->findImage("아이템제작알파");
				_vCraftItem[9].item_image = IMAGEMANAGER->findImage("아이템제작알파");
			}
		}
	}
	
	//허수아비 1-9번 
	//for (int i = 1; i < 10; i++)
	//{
	//	if (_inven->getvInven()[_isWood].amount >= 2*i+8 && _inven->getvInven()[_isRock].amount >= i+3)
	//	{
	//		_vCraftItem[i + 2].item_image = IMAGEMANAGER->findImage("아이템제작");
	//		_vCraftItem[i + 7].item_image = IMAGEMANAGER->findImage("아이템제작");

	//		if (PtInRect(&_vCraftItem[i + 2].rc, _ptMouse) || PtInRect(&_vCraftItem[i + 7].rc, _ptMouse))
	//		{
	//			if (INPUT->GetKeyDown(VK_LBUTTON))
	//			{
	//				tagItem scarecrow;
	//				scarecrow.item_image = IMAGEMANAGER->findImage("아이템");
	//				scarecrow.item_info = "허수아비";
	//				scarecrow.indexX = i + 2;
	//				scarecrow.indexY = 0;
	//				scarecrow.item_kind = ITEM_SCARECROW;
	//				scarecrow.isFrame = true;
	//				scarecrow.amount = 1;

	//				_inven->setMouseItem(scarecrow);
	//				_inven->setInvenItemAmount(_isWood, _inven->getvInven()[_isWood].amount - 15);
	//				_inven->setInvenItemAmount(_isRock, _inven->getvInven()[_isRock].amount - 5);
	//			}
	//		}
	//	}
	//	else if (_inven->getvInven()[_isWood].amount < 2 * i + 8 || _inven->getvInven()[_isRock].amount < i + 3)
	//	{
	//		if (_vCraftItem[i + 2].item_image != IMAGEMANAGER->findImage("아이템제작알파") &&
	//			_vCraftItem[i + 7].item_image != IMAGEMANAGER->findImage("아이템제작알파"))
	//		{
	//			_vCraftItem[i + 2].item_image = IMAGEMANAGER->findImage("아이템제작알파");
	//			_vCraftItem[i + 7].item_image = IMAGEMANAGER->findImage("아이템제작알파");
	//		}
	//	}
	//}

	//용광로 만들기 
	if (_isCopper != NULL && _isRock != NULL)
	{
		if (_inven->getvInven()[_isCopper].amount >= 15 && _inven->getvInven()[_isRock].amount >= 20)
		{
			_vCraftItem[4].item_image = IMAGEMANAGER->findImage("아이템제작");
			_vCraftItem[10].item_image = IMAGEMANAGER->findImage("아이템제작");

			if (PtInRect(&_vCraftItem[4].rc, _ptMouse) || PtInRect(&_vCraftItem[10].rc, _ptMouse))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					tagItem blastfurnace;
					blastfurnace.item_image = IMAGEMANAGER->findImage("아이템");
					blastfurnace.item_info = "용광로";
					blastfurnace.indexX = 4;
					blastfurnace.indexY = 0;
					blastfurnace.item_kind = ITEM_BLASTFURNACE;
					blastfurnace.isFrame = true;
					blastfurnace.amount = 1;

					_inven->setMouseItem(blastfurnace);
					_inven->setInvenItemAmount(_isCopper, _inven->getvInven()[_isCopper].amount - 15);
					_inven->setInvenItemAmount(_isRock, _inven->getvInven()[_isRock].amount - 20);
				}
			}
		}
		else if (_inven->getvInven()[_isCopper].amount < 15 || _inven->getvInven()[_isRock].amount < 20)
		{
			if (_vCraftItem[4].item_image != IMAGEMANAGER->findImage("아이템제작알파") &&
				_vCraftItem[10].item_image != IMAGEMANAGER->findImage("아이템제작알파"))
			{
				_vCraftItem[4].item_image = IMAGEMANAGER->findImage("아이템제작알파");
				_vCraftItem[10].item_image = IMAGEMANAGER->findImage("아이템제작알파");
			}
		}
	}
}

void inventoryCraft::blastFurnace()
{
	//IMAGEMANAGER->findImage("제작중인 아이템");

	if (PLAYER->getCurrentSlotNumber() == _isCopper) //구리조각이 5개 이상일 때 
	{
		if (_inven->getvInven()[_isCopper].amount >= 5)
		{
			tagItem copperIngot;
			copperIngot.item_image = IMAGEMANAGER->findImage("광물아이템");
			copperIngot.item_info = "구리주괴";
			copperIngot.indexX = 6;
			copperIngot.indexY = 4;
			copperIngot.isFrame = true;
			copperIngot.amount = 1;

			_inven->setInvenItemAmount(_isCopper, _inven->getvInven()[_isCopper].amount - 5);

			for (int i = 0; i < _inven->getvInven().size(); i++)
			{
				if (_inven->getvInven()[i].item_image == IMAGEMANAGER->findImage("광물아이템") && _inven->getvInven()[i].item_info=="구리주괴")
				{
					_inven->setInvenItemAmount(i, _inven->getvInven()[i].amount +1);
					break;
				}
				else if (_inven->getvInven()[i].item_image == NULL)
				{
					_inven->setInvenItem(i, copperIngot);
					break;
				}
			}
		}
	}

	if (PLAYER->getCurrentSlotNumber() == _isIron) //철조각이 5개 이상일 때 
	{
		if (_inven->getvInven()[_isIron].amount >= 5)
		{
			tagItem ironIngot;
			ironIngot.item_image = IMAGEMANAGER->findImage("광물아이템");
			ironIngot.item_info = "철주괴";
			ironIngot.indexX = 8;
			ironIngot.indexY = 4;
			ironIngot.isFrame = true;
			ironIngot.amount = 1;

			_inven->setInvenItemAmount(_isIron, _inven->getvInven()[_isIron].amount - 5);

			for (int i = 0; i < _inven->getvInven().size(); i++)
			{
				if (_inven->getvInven()[i].item_image == NULL)
				{
					_inven->setInvenItem(i, ironIngot);
					break;
				}
				else if (_inven->getvInven()[i].item_image == IMAGEMANAGER->findImage("광물아이템") && _inven->getvInven()[i].item_info == "철주괴")
				{
					_inven->setInvenItemAmount(i, _inven->getvInven()[i].amount + 1);
					break;
				}
			}
		}
	}

	if (PLAYER->getCurrentSlotNumber() == _isGold) //금조각이 5개 이상일 때 
	{
		if (_inven->getvInven()[_isGold].amount >= 5) 
		{
			tagItem goldIngot;
			goldIngot.item_image = IMAGEMANAGER->findImage("광물아이템");
			goldIngot.item_info = "금주괴";
			goldIngot.indexX = 12;
			goldIngot.indexY = 4;
			goldIngot.isFrame = true;
			goldIngot.amount = 1;
			
			_inven->setInvenItemAmount(_isGold, _inven->getvInven()[_isGold].amount - 5);

			for (int i = 0; i < _inven->getvInven().size(); i++)
			{
				if (_inven->getvInven()[i].item_image == NULL)
				{
					_inven->setInvenItem(i, goldIngot);
					break;
				}
				else if (_inven->getvInven()[i].item_image == IMAGEMANAGER->findImage("광물아이템") && _inven->getvInven()[i].item_info == "금주괴")
				{
					_inven->setInvenItemAmount(i, _inven->getvInven()[i].amount + 1);
					break;
				}
			}
		}
	}
}

void inventoryCraft::release()
{
}

void inventoryCraft::render(HDC hdc)
{
	// IMAGEMANAGER->frameRender("아이템제작", hdc, 225, 30);
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

				IMAGEMANAGER->findImage("아이템정보")->render(hdc, _ptMouse.x + 25, _ptMouse.y + 25);

				SetTextColor(hdc, RGB(0, 0, 0));

				memset(temp_info, 0, sizeof(temp_info));


				if (PtInRect(&_vCraftItem[0].rc, _ptMouse) || PtInRect(&_vCraftItem[6].rc, _ptMouse)) //보관함 렉트에 닿으면
				{
					IMAGEMANAGER->frameRender("열매", hdc, temp2.left + 5, temp2.top - 5, 4, 2);

					sprintf(temp_info[0], "보관함", sizeof("보관함"));
					sprintf(temp_info[1], ": 나무 10개", sizeof(": 나무 10개"));

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
				else if (PtInRect(&_vCraftItem[1].rc, _ptMouse) || PtInRect(&_vCraftItem[7].rc, _ptMouse)) //먹이통 렉트에 닿으면 
				{
					IMAGEMANAGER->frameRender("열매", hdc, temp2.left + 5, temp2.top - 5, 4, 2);

					sprintf(temp_info[0], "먹이통", sizeof("먹이통"));
					sprintf(temp_info[1], ": 나무 15개", sizeof(": 나무 15개"));

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
				else if (PtInRect(&_vCraftItem[2].rc, _ptMouse) || PtInRect(&_vCraftItem[8].rc, _ptMouse)) //양봉장 렉트에 닿으면 
				{
					sprintf(temp_info[0], "양봉장", sizeof("양봉장"));
					sprintf(temp_info[1], ": 나무 20개", sizeof(": 나무 20개"));
					sprintf(temp_info[2], ": 철 조각 10개", sizeof(": 철 조각 10개"));

					IMAGEMANAGER->frameRender("열매", hdc, temp2.left - 5, temp2.top - 5, 4, 2);
					IMAGEMANAGER->frameRender("광물아이템", hdc, temp2.left -5, temp2.top + 35, 8, 3);

				
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
				else if (PtInRect(&_vCraftItem[3].rc, _ptMouse) || PtInRect(&_vCraftItem[9].rc, _ptMouse)) //허수아비 렉트에 닿으면 
				{
					sprintf(temp_info[0], "허수아비", sizeof("허수아비"));
					sprintf(temp_info[1], ": 나무 15개", sizeof(": 나무 15개"));
					sprintf(temp_info[2], ": 돌 5개", sizeof(": 돌 5개"));

					IMAGEMANAGER->frameRender("열매", hdc, temp2.left +5, temp2.top - 5, 4, 2);
					IMAGEMANAGER->frameRender("열매", hdc, temp2.left + 5, temp2.top + 30, 3, 2);

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
				else if (PtInRect(&_vCraftItem[4].rc, _ptMouse) || PtInRect(&_vCraftItem[10].rc, _ptMouse)) //용광로 렉트에 닿으면 
				{
					sprintf(temp_info[0], "용광로", sizeof("용광로"));
					sprintf(temp_info[1], ": 구리조각 15개", sizeof(": 구리조각 15개"));
					sprintf(temp_info[2], ": 돌 20개", sizeof(": 돌 20개"));


					IMAGEMANAGER->frameRender("광물아이템", hdc, temp2.left + 5, temp2.top - 5, 6, 3);
					IMAGEMANAGER->frameRender("열매", hdc, temp2.left + 5, temp2.top + 30, 3, 2);

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
				else if (PtInRect(&_vCraftItem[5].rc, _ptMouse) || PtInRect(&_vCraftItem[11].rc, _ptMouse)) //절임통 렉트에 닿으면 
				{
					sprintf(temp_info[0], "절임통", sizeof("절임통"));
					sprintf(temp_info[1], ": 나무 15개", sizeof(": 나무 15개"));
					sprintf(temp_info[2], ": 돌 20개", sizeof(": 돌 20개"));

					IMAGEMANAGER->frameRender("열매", hdc, temp2.left + 5, temp2.top - 5, 6, 2);
					IMAGEMANAGER->frameRender("열매", hdc, temp2.left + 5, temp2.top + 30, 3, 2);

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
				SetTextColor(hdc, RGB(0, 0, 0));
				DrawText(hdc, temp_info[0], strlen(temp_info[0]), &temp1, NULL);
			}
		}
	}
}
