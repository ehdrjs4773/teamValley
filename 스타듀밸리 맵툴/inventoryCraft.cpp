#include "stdafx.h"
#include "inventoryCraft.h"
#include "inventory.h"

void inventoryCraft::init()
{
	for (int i = 0; i < 11; i++)
	{
		_CraftItem.item_image = IMAGEMANAGER->findImage("아이템제작알파");
		_CraftItem.indexX = i;
		_CraftItem.indexY = 0;
		_CraftItem.rc = RectMake(250 + i % 11 * 50, 130, 40, 80);
		_vCraftItem.push_back(_CraftItem);
	
	}

	if (PLAYER->getDate() >= 12 && PLAYER->getDate() <= 16)
	{
		for (int i = 0; i < 3; i++)
		{
			_CraftEventItem.item_image = IMAGEMANAGER->findImage("토마토아이템제작알파");
			_CraftEventItem.indexX = i;
			_CraftEventItem.indexY = 1;
			_CraftEventItem.rc = RectMake(250 + i % 11 * 50, 210, 40, 80);
			_vCraftEventItem.push_back(_CraftEventItem);
		
		}
	}

	_isWood = NULL;
	_isRock = NULL;
	_isIron = NULL;
	_isCopper = NULL;
	_isGold = NULL;
	_isTomato = NULL;

	_isTemp3 = false;
	_isTemp4 = false;
}

void inventoryCraft::materialUpdate()
{
	cout << _isWood << "\t" << _inven->getvInven()[_isWood].amount<< endl;
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
		//	else if (_inven->getvInven()[i].item_kind == ITEM_FRUIT)
		//	{
		//		if (_isTomato == NULL)
		//		{
		//			if (_inven->getvInven()[i].indexX == 12 && _inven->getvInven()[i].indexY == 3)
		//			{
		//				_isTomato = i;

		//			}
		//		}
		//		else
		//		{
		//			if (_inven->getvInven()[_isTomato].amount <= 0)
		//			{
		//				_isTomato = NULL;
		//			}
		//		}

		//	}
		//}

		//cout << _isWood << "  " << _isRock << "  " << _isCopper << "  " << _isIron << "  " << _isGold << endl;
	}
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
			_vCraftItem[i].rc = RectMake(250 + i % 11 * 50, 130, 40, 80);
		}

		if (PLAYER->getDate() >= 12 && PLAYER->getDate() <= 16)
		{
			for (int i = 0; i < _vCraftEventItem.size(); i++)
			{
				if (_vCraftEventItem[i].item_image == NULL)
				{
					_vCraftEventItem[i].item_image = IMAGEMANAGER->findImage("토마토아이템제작알파");
				}
				else
				{
				}
				_vCraftEventItem[i].rc = RectMake(250 + i % 11 * 50, 210, 40, 80);
			}
		}
		initCount = 1;
	}

	//상자 만들기 

	if (_isWood != NULL)
	{
		if (_inven->getvInven()[_isWood].amount >= 10)
		{
			cout << "상자 만들기 들어왔다" << endl;
			_vCraftItem[0].item_image = IMAGEMANAGER->findImage("아이템제작");
			if (PtInRect(&_vCraftItem[0].rc, _ptMouse))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					tagItem box;
					box.item_image = IMAGEMANAGER->findImage("아이템");
					box.item_info = "상자";
					box.itemName = "상자";
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
			if (_vCraftItem[0].item_image != IMAGEMANAGER->findImage("아이템제작알파"))
			{
				_vCraftItem[0].item_image = IMAGEMANAGER->findImage("아이템제작알파");
			}
		}
	}

	//용광로 만들기 
	if (_isCopper != NULL && _isRock != NULL)
	{
		if (_inven->getvInven()[_isCopper].amount >= 15 && _inven->getvInven()[_isRock].amount >= 20)
		{
			_vCraftItem[1].item_image = IMAGEMANAGER->findImage("아이템제작");

			if (PtInRect(&_vCraftItem[1].rc, _ptMouse))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					tagItem blastfurnace;
					blastfurnace.item_image = IMAGEMANAGER->findImage("아이템");
					blastfurnace.item_info = "용광로";
					blastfurnace.itemName = "용광로";
					blastfurnace.indexX = 1;
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
			if (_vCraftItem[1].item_image != IMAGEMANAGER->findImage("아이템제작알파"))
			{
				_vCraftItem[1].item_image = IMAGEMANAGER->findImage("아이템제작알파");
			}
		}
	}
	
	//허수아비 1-9번
	//if (_isWood != NULL && _isRock != NULL)
	//{
	//	for (int i = 1; i < 10; i++)
	//	{
	//		if (_inven->getvInven()[_isWood].amount >= 2 * i + 8 && _inven->getvInven()[_isRock].amount >= i + 3)
	//		{
	//			_vCraftItem[i + 1].item_image = IMAGEMANAGER->findImage("아이템제작");

	//			if (PtInRect(&_vCraftItem[i + 1].rc, _ptMouse))
	//			{
	//				if (INPUT->GetKeyDown(VK_LBUTTON))
	//				{
	//					tagItem scarecrow;
	//					scarecrow.item_image = IMAGEMANAGER->findImage("아이템");
	//					scarecrow.item_info = "허수아비";
	//					scarecrow.indexX = i + 1;
	//					scarecrow.indexY = 0;
	//					scarecrow.scarecrowKind = i+1;
	//					scarecrow.isFrame = true;
	//					scarecrow.amount = 1;

	//					_inven->setMouseItem(scarecrow);
	//					_inven->setInvenItemAmount(_isWood, _inven->getvInven()[_isWood].amount - 2 * i + 8);
	//					_inven->setInvenItemAmount(_isRock, _inven->getvInven()[_isRock].amount - i + 3);
	//				}
	//			}
	//		}
	//		else if (_inven->getvInven()[_isWood].amount < 2 * i + 8 || _inven->getvInven()[_isRock].amount < i + 3)
	//		{
	//			if (_vCraftItem[i + 1].item_image != IMAGEMANAGER->findImage("아이템제작알파"))
	//			{
	//				_vCraftItem[i + 1].item_image = IMAGEMANAGER->findImage("아이템제작알파");
	//			}
	//		}
	//	}
	//}

	//허수아비 1번
	if (_isWood != NULL && _isRock != NULL)
	{
		if (_inven->getvInven()[_isWood].amount >=10 && _inven->getvInven()[_isRock].amount >= 4)
		{
			_vCraftItem[2].item_image = IMAGEMANAGER->findImage("아이템제작");

			if (PtInRect(&_vCraftItem[2].rc, _ptMouse))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					tagItem scarecrow;
					scarecrow.item_image = IMAGEMANAGER->findImage("아이템");
					scarecrow.item_info = "허수아비";
					scarecrow.itemName = "허수아비";
					scarecrow.indexX = 2;
					scarecrow.indexY = 0;
					scarecrow.scarecrowKind = SCARECROW_1;
					scarecrow.isFrame = true;
					scarecrow.amount = 1;

					_inven->setMouseItem(scarecrow);
					_inven->setInvenItemAmount(_isWood, _inven->getvInven()[_isWood].amount - 10);
					_inven->setInvenItemAmount(_isRock, _inven->getvInven()[_isRock].amount - 4);
					if (PLAYER->getEnergy() > -20)
					{
						PLAYER->setEnergy(PLAYER->getDamage());
					}
				}
			}
		}
		else if (_inven->getvInven()[_isWood].amount < 10 || _inven->getvInven()[_isRock].amount < 4)
		{
			if (_vCraftItem[2].item_image != IMAGEMANAGER->findImage("아이템제작알파"))
			{
				_vCraftItem[2].item_image = IMAGEMANAGER->findImage("아이템제작알파");
			}
		}
	}

	//허수아비 2번
	if (_isWood != NULL && _isRock != NULL)
	{
		if (_inven->getvInven()[_isWood].amount >= 12 && _inven->getvInven()[_isRock].amount >= 5)
		{
			_vCraftItem[3].item_image = IMAGEMANAGER->findImage("아이템제작");

			if (PtInRect(&_vCraftItem[3].rc, _ptMouse))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					tagItem scarecrow;
					scarecrow.item_image = IMAGEMANAGER->findImage("아이템");
					scarecrow.item_info = "허수아비";
					scarecrow.itemName = "허수아비";
					scarecrow.indexX = 3;
					scarecrow.indexY = 0;
					scarecrow.scarecrowKind = SCARECROW_2;
					scarecrow.isFrame = true;
					scarecrow.amount = 1;

					_inven->setMouseItem(scarecrow);
					_inven->setInvenItemAmount(_isWood, _inven->getvInven()[_isWood].amount - 10);
					_inven->setInvenItemAmount(_isRock, _inven->getvInven()[_isRock].amount - 4);
					if (PLAYER->getEnergy() > -20)
					{
						PLAYER->setEnergy(PLAYER->getDamage()+1);
					}
				}
			}
		}
		else if (_inven->getvInven()[_isWood].amount < 12 || _inven->getvInven()[_isRock].amount < 5)
		{
			if (_vCraftItem[3].item_image != IMAGEMANAGER->findImage("아이템제작알파"))
			{
				_vCraftItem[3].item_image = IMAGEMANAGER->findImage("아이템제작알파");
			}
		}
	}

	//허수아비 3번
	if (_isWood != NULL && _isRock != NULL)
	{
		if (_inven->getvInven()[_isWood].amount >= 14 && _inven->getvInven()[_isRock].amount >= 6)
		{
			_vCraftItem[4].item_image = IMAGEMANAGER->findImage("아이템제작");

			if (PtInRect(&_vCraftItem[4].rc, _ptMouse))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					tagItem scarecrow;
					scarecrow.item_image = IMAGEMANAGER->findImage("아이템");
					scarecrow.item_info = "허수아비";
					scarecrow.itemName = "허수아비";
					scarecrow.indexX = 4;
					scarecrow.indexY = 0;
					scarecrow.scarecrowKind = SCARECROW_3;
					scarecrow.isFrame = true;
					scarecrow.amount = 1;

					_inven->setMouseItem(scarecrow);
					_inven->setInvenItemAmount(_isWood, _inven->getvInven()[_isWood].amount - 14);
					_inven->setInvenItemAmount(_isRock, _inven->getvInven()[_isRock].amount - 6);

					if (PLAYER->getEnergy() > -20)
					{
						PLAYER->setEnergy(PLAYER->getDamage() + 2);
					}
				}
			}
		}
		else if (_inven->getvInven()[_isWood].amount < 14 || _inven->getvInven()[_isRock].amount < 6)
		{
			if (_vCraftItem[4].item_image != IMAGEMANAGER->findImage("아이템제작알파"))
			{
				_vCraftItem[4].item_image = IMAGEMANAGER->findImage("아이템제작알파");
			}
		}
	}

	//허수아비 4번
	if (_isWood != NULL && _isRock != NULL)
	{
		if (_inven->getvInven()[_isWood].amount >= 16 && _inven->getvInven()[_isRock].amount >= 7)
		{
			_vCraftItem[5].item_image = IMAGEMANAGER->findImage("아이템제작");

			if (PtInRect(&_vCraftItem[5].rc, _ptMouse))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					tagItem scarecrow;
					scarecrow.item_image = IMAGEMANAGER->findImage("아이템");
					scarecrow.item_info = "허수아비";
					scarecrow.indexX = 5;
					scarecrow.indexY = 0;
					scarecrow.scarecrowKind = SCARECROW_4;
					scarecrow.isFrame = true;
					scarecrow.amount = 1;

					_inven->setMouseItem(scarecrow);
					_inven->setInvenItemAmount(_isWood, _inven->getvInven()[_isWood].amount - 16);
					_inven->setInvenItemAmount(_isRock, _inven->getvInven()[_isRock].amount - 7);

					if (PLAYER->getEnergy() > -20)
					{
						PLAYER->setEnergy(PLAYER->getDamage() + 3);
					}
				}
			}
		}
		else if (_inven->getvInven()[_isWood].amount < 16 || _inven->getvInven()[_isRock].amount < 7)
		{
			if (_vCraftItem[5].item_image != IMAGEMANAGER->findImage("아이템제작알파"))
			{
				_vCraftItem[5].item_image = IMAGEMANAGER->findImage("아이템제작알파");
			}
		}
	}

	//허수아비 5번
	if (_isWood != NULL && _isRock != NULL)
	{
		if (_inven->getvInven()[_isWood].amount >= 18 && _inven->getvInven()[_isRock].amount >= 8)
		{
			_vCraftItem[6].item_image = IMAGEMANAGER->findImage("아이템제작");

			if (PtInRect(&_vCraftItem[6].rc, _ptMouse))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					tagItem scarecrow;
					scarecrow.item_image = IMAGEMANAGER->findImage("아이템");
					scarecrow.item_info = "허수아비";
					scarecrow.indexX = 6;
					scarecrow.indexY = 0;
					scarecrow.scarecrowKind = SCARECROW_5;
					scarecrow.isFrame = true;
					scarecrow.amount = 1;

					_inven->setMouseItem(scarecrow);
					_inven->setInvenItemAmount(_isWood, _inven->getvInven()[_isWood].amount - 18);
					_inven->setInvenItemAmount(_isRock, _inven->getvInven()[_isRock].amount - 8);

					if (PLAYER->getEnergy() > -20)
					{
						PLAYER->setEnergy(PLAYER->getDamage() + 4);
					}
				}
			}
		}
		else if (_inven->getvInven()[_isWood].amount < 18 || _inven->getvInven()[_isRock].amount < 8)
		{
			if (_vCraftItem[6].item_image != IMAGEMANAGER->findImage("아이템제작알파"))
			{
				_vCraftItem[6].item_image = IMAGEMANAGER->findImage("아이템제작알파");
			}
		}
	}

	//허수아비 6번
	if (_isWood != NULL && _isRock != NULL)
	{
		if (_inven->getvInven()[_isWood].amount >= 20 && _inven->getvInven()[_isRock].amount >= 9)
		{
			_vCraftItem[7].item_image = IMAGEMANAGER->findImage("아이템제작");

			if (PtInRect(&_vCraftItem[7].rc, _ptMouse))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					tagItem scarecrow;
					scarecrow.item_image = IMAGEMANAGER->findImage("아이템");
					scarecrow.item_info = "허수아비";
					scarecrow.indexX = 7;
					scarecrow.indexY = 0;
					scarecrow.scarecrowKind = SCARECROW_6;
					scarecrow.isFrame = true;
					scarecrow.amount = 1;

					_inven->setMouseItem(scarecrow);
					_inven->setInvenItemAmount(_isWood, _inven->getvInven()[_isWood].amount - 20);
					_inven->setInvenItemAmount(_isRock, _inven->getvInven()[_isRock].amount - 9);

					if (PLAYER->getEnergy() > -20)
					{
						PLAYER->setEnergy(PLAYER->getDamage() + 5);
					}
				}
			}
		}
		else if (_inven->getvInven()[_isWood].amount < 20 || _inven->getvInven()[_isRock].amount < 9)
		{
			if (_vCraftItem[7].item_image != IMAGEMANAGER->findImage("아이템제작알파"))
			{
				_vCraftItem[7].item_image = IMAGEMANAGER->findImage("아이템제작알파");
			}
		}
	}

	//허수아비 7번
	if (_isWood != NULL && _isRock != NULL)
	{
		if (_inven->getvInven()[_isWood].amount >= 22 && _inven->getvInven()[_isRock].amount >= 10)
		{
			_vCraftItem[8].item_image = IMAGEMANAGER->findImage("아이템제작");

			if (PtInRect(&_vCraftItem[8].rc, _ptMouse))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					tagItem scarecrow;
					scarecrow.item_image = IMAGEMANAGER->findImage("아이템");
					scarecrow.item_info = "허수아비";
					scarecrow.indexX = 8;
					scarecrow.indexY = 0;
					scarecrow.scarecrowKind = SCARECROW_7;
					scarecrow.isFrame = true;
					scarecrow.amount = 1;

					_inven->setMouseItem(scarecrow);
					_inven->setInvenItemAmount(_isWood, _inven->getvInven()[_isWood].amount - 22);
					_inven->setInvenItemAmount(_isRock, _inven->getvInven()[_isRock].amount - 10);

					if (PLAYER->getEnergy() > -20)
					{
						PLAYER->setEnergy(PLAYER->getDamage() + 6);
					}
				}
			}
		}
		else if (_inven->getvInven()[_isWood].amount < 22 || _inven->getvInven()[_isRock].amount < 10)
		{
			if (_vCraftItem[8].item_image != IMAGEMANAGER->findImage("아이템제작알파"))
			{
				_vCraftItem[8].item_image = IMAGEMANAGER->findImage("아이템제작알파");
			}
		}
	}

	//허수아비 8번
	if (_isWood != NULL && _isRock != NULL)
	{
		if (_inven->getvInven()[_isWood].amount >= 24 && _inven->getvInven()[_isRock].amount >= 11)
		{
			_vCraftItem[9].item_image = IMAGEMANAGER->findImage("아이템제작");

			if (PtInRect(&_vCraftItem[9].rc, _ptMouse))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					tagItem scarecrow;
					scarecrow.item_image = IMAGEMANAGER->findImage("아이템");
					scarecrow.item_info = "허수아비";
					scarecrow.indexX = 9;
					scarecrow.indexY = 0;
					scarecrow.scarecrowKind = SCARECROW_8;
					scarecrow.isFrame = true;
					scarecrow.amount = 1;

					_inven->setMouseItem(scarecrow);
					_inven->setInvenItemAmount(_isWood, _inven->getvInven()[_isWood].amount - 24);
					_inven->setInvenItemAmount(_isRock, _inven->getvInven()[_isRock].amount - 11);

					if (PLAYER->getEnergy() > -20)
					{
						PLAYER->setEnergy(PLAYER->getDamage() + 7);
					}
				}
			}
		}
		else if (_inven->getvInven()[_isWood].amount < 24 || _inven->getvInven()[_isRock].amount < 11)
		{
			if (_vCraftItem[9].item_image != IMAGEMANAGER->findImage("아이템제작알파"))
			{
				_vCraftItem[9].item_image = IMAGEMANAGER->findImage("아이템제작알파");
			}
		}
	}

	//허수아비 9번
	if (_isWood != NULL && _isRock != NULL)
	{
		if (_inven->getvInven()[_isWood].amount >= 26 && _inven->getvInven()[_isRock].amount >= 12)
		{
			_vCraftItem[10].item_image = IMAGEMANAGER->findImage("아이템제작");

			if (PtInRect(&_vCraftItem[10].rc, _ptMouse))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					tagItem scarecrow;
					scarecrow.item_image = IMAGEMANAGER->findImage("아이템");
					scarecrow.item_info = "허수아비";
					scarecrow.indexX = 10;
					scarecrow.indexY = 0;
					scarecrow.scarecrowKind = SCARECROW_9;
					scarecrow.isFrame = true;
					scarecrow.amount = 1;

					_inven->setMouseItem(scarecrow);
					_inven->setInvenItemAmount(_isWood, _inven->getvInven()[_isWood].amount - 26);
					_inven->setInvenItemAmount(_isRock, _inven->getvInven()[_isRock].amount - 12);

					if (PLAYER->getEnergy() > -20)
					{
						PLAYER->setEnergy(PLAYER->getDamage() + 8);
					}
				}
			}
		}
		else if (_inven->getvInven()[_isWood].amount < 26 || _inven->getvInven()[_isRock].amount < 12)
		{
			if (_vCraftItem[10].item_image != IMAGEMANAGER->findImage("아이템제작알파"))
			{
				_vCraftItem[10].item_image = IMAGEMANAGER->findImage("아이템제작알파");
			}
		}
	}
		




	//이벤트용 허수아비 1-3번
	if (PLAYER->getDate() >= 12 && PLAYER->getDate() <= 16)
	{
		if (_isWood != NULL && _isRock != NULL && _isTomato != NULL)
		{
			for (int i = 0; i < 3; i++)
			{
				if (_inven->getvInven()[_isWood].amount >= 10 * i + 20 && _inven->getvInven()[_isRock].amount >= 5 * i + 10 && _inven->getvInven()[_isTomato].amount >= 5 * i + 20)
				{
					_vCraftEventItem[i].item_image = IMAGEMANAGER->findImage("토마토아이템제작");

					if (PtInRect(&_vCraftEventItem[i].rc, _ptMouse))
					{
						if (INPUT->GetKeyDown(VK_LBUTTON))
						{
							tagItem scarecrow;
							scarecrow.item_image = IMAGEMANAGER->findImage("아이템");
							scarecrow.item_info = "허수아비";
							scarecrow.indexX = i;
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
				else if (_inven->getvInven()[_isWood].amount < 2 * i + 8 || _inven->getvInven()[_isRock].amount < 5 * i + 10 || _inven->getvInven()[_isTomato].amount < 5 * i + 20)
				{
					if (_vCraftEventItem[i].item_image != IMAGEMANAGER->findImage("토마토아이템제작알파"))
					{
						_vCraftEventItem[i].item_image = IMAGEMANAGER->findImage("토마토아이템제작알파");
					}
				}
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
			tagItem copperIngot = ITEMMANAGER->findItemByKind(ITEM_INGOT, 6);

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
			tagItem ironIngot = ITEMMANAGER->findItemByKind(ITEM_INGOT, 8);

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
			tagItem goldIngot = ITEMMANAGER->findItemByKind(ITEM_INGOT, 12);
			
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

	if (PLAYER->getDate() >= 12 && PLAYER->getDate() <= 16)
	{
		for (int i = 0; i < _vCraftEventItem.size(); i++)
		{
			if (_vCraftEventItem[i].item_image != NULL)
			{
				_vCraftEventItem[i].item_image->frameRender(hdc, _vCraftEventItem[i].rc.left, _vCraftEventItem[i].rc.top, _vCraftEventItem[i].indexX, _vCraftEventItem[i].indexY);
				craftEventInven_item_info(hdc);
			}
			//Rectangle(hdc, _vCraftEventItem[i].rc); 
		}
	}

	if (INPUT->GetToggleKey(VK_F9))
	{
		for (int i = 0; i < _vCraftItem.size(); i++)
		{
			Rectangle(hdc, _vCraftItem[i].rc);
		}
		for (int i = 0; i < _vCraftEventItem.size(); i++)
		{
			Rectangle(hdc, _vCraftEventItem[i].rc);
		}
	}
	
}

void inventoryCraft::craftInven_item_info(HDC hdc)
{
	for (int i = 0; i < _vCraftItem.size(); i++)
	{
		if (PtInRect(&_vCraftItem[i].rc, _ptMouse))
		{
			if (_vCraftItem[i].item_image != NULL)
			{
				char temp_info[4][256];
				RECT temp1 = RectMake(_ptMouse.x + 35, _ptMouse.y + 45, 200, 50);
				RECT temp2 = RectMake(temp1.left, temp1.bottom, 200, 100);
				RECT temp3 = RectMake(temp2.left + 40, temp2.top, 160, 40);
				RECT temp4 = RectMake(temp2.left + 40, temp3.bottom, 160, 40);

				IMAGEMANAGER->findImage("아이템정보")->render(hdc, _ptMouse.x + 25, _ptMouse.y + 25);

				SetTextColor(hdc, RGB(0, 0, 0));

				memset(temp_info, 0, sizeof(temp_info));

				if (PtInRect(&_vCraftItem[0].rc, _ptMouse)) //보관함 렉트에 닿으면
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
				else if (PtInRect(&_vCraftItem[1].rc, _ptMouse)) //용광로 렉트에 닿으면 
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
				else if (PtInRect(&_vCraftItem[i].rc, _ptMouse) && i >= 11 && i <= 13)
				{
					sprintf(temp_info[0], "이벤트 허수아비 %d", i - 10);
					sprintf(temp_info[1], ": 나무 %d개", (i - 10) * 10 + 10);
					sprintf(temp_info[2], ": 돌 %d개", ((i - 10) + 1) * 5);
					sprintf(temp_info[3], ": 토마토 %d개", ((i - 10) * 5) + 15);

					IMAGEMANAGER->frameRender("열매", hdc, temp2.left + 5, temp2.top - 5, 4, 2);
					IMAGEMANAGER->frameRender("열매", hdc, temp2.left + 5, temp2.top + 30, 3, 2);

					if (_isWood != NULL || _isRock != NULL)
					{
						if (_inven->getvInven()[_isWood].amount < 2 * (i - 2) + 10)
						{
							SetTextColor(hdc, RGB(255, 0, 0));
							DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						}
						else if (_inven->getvInven()[_isWood].amount >= 2 * (i - 2) + 10)
						{
							SetTextColor(hdc, RGB(0, 0, 0));
							DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						}

						if (_inven->getvInven()[_isRock].amount < i + 2)
						{
							SetTextColor(hdc, RGB(255, 0, 0));
							DrawText(hdc, temp_info[2], strlen(temp_info[1]), &temp4, NULL);
						}
						else if (_inven->getvInven()[_isRock].amount >= i + 2)
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
				else if (PtInRect(&_vCraftItem[i].rc, _ptMouse)) //허수아비 렉트에 닿으면 
				{
					sprintf(temp_info[0], "허수아비 %d", i - 2);
					sprintf(temp_info[1], ": 나무 %d개",  2* (i-2) + 10);
					sprintf(temp_info[2], ": 돌 %d개", i+2);

					IMAGEMANAGER->frameRender("열매", hdc, temp2.left +5, temp2.top - 5, 4, 2);
					IMAGEMANAGER->frameRender("열매", hdc, temp2.left + 5, temp2.top + 30, 3, 2);

					if (_isWood != NULL || _isRock != NULL)
					{
						if (_inven->getvInven()[_isWood].amount < 2 * (i - 2) + 10)
						{
							SetTextColor(hdc, RGB(255, 0, 0));
							DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						}
						else if (_inven->getvInven()[_isWood].amount >= 2 * (i - 2) + 10)
						{
							SetTextColor(hdc, RGB(0, 0, 0));
							DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						}

						if (_inven->getvInven()[_isRock].amount < i + 2)
						{
							SetTextColor(hdc, RGB(255, 0, 0));
							DrawText(hdc, temp_info[2], strlen(temp_info[1]), &temp4, NULL);
						}
						else if (_inven->getvInven()[_isRock].amount >= i + 2)
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

void inventoryCraft::craftEventInven_item_info(HDC hdc)
{

	for (int i = 0; i < _vCraftEventItem.size(); i++)
	{
		if (PtInRect(&_vCraftEventItem[i].rc, _ptMouse))
		{
			if (_vCraftEventItem[i].item_image != NULL)
			{
				char temp_info[4][256];
				RECT temp1 = RectMake(_ptMouse.x + 35, _ptMouse.y + 45, 200, 50);
				RECT temp2 = RectMake(temp1.left, temp1.bottom, 200, 100);
				RECT temp3 = RectMake(temp2.left + 40, temp2.top, 160, 30); //재료1
				RECT temp4 = RectMake(temp2.left + 40, temp3.bottom, 160, 30); //재료2
				RECT temp5 = RectMake(temp2.left + 40, temp4.bottom, 160, 30); //재료3

				IMAGEMANAGER->findImage("아이템정보")->render(hdc, _ptMouse.x + 25, _ptMouse.y + 25);

				SetTextColor(hdc, RGB(0, 0, 0));

				memset(temp_info, 0, sizeof(temp_info));

				if (PtInRect(&_vCraftEventItem[0].rc, _ptMouse)) //토마토 허수아비 렉트에 닿으면
				{
					IMAGEMANAGER->frameRender("열매", hdc, temp2.left + 5, temp2.top - 5, 4, 2);
					IMAGEMANAGER->frameRender("열매", hdc, temp2.left + 5, temp2.top + 30, 3, 2);
					//토마토이미지 IMAGEMANAGER->frameRender("열매", hdc, temp2.left + 5, temp2.top + 30, 3, 2);

					sprintf(temp_info[0], "허수아비", sizeof("허수아비"));
					sprintf(temp_info[1], ": 나무 %d개", i*10+ 20);
					sprintf(temp_info[2], ": 돌 %d개", i*5 + 10);
					sprintf(temp_info[3], ": 토마토 %d개", i * 5 + 20);

					if (_isWood != NULL || _isRock != NULL)
					{
						if (_inven->getvInven()[_isWood].amount < i * 10 + 20) //나무
						{
							SetTextColor(hdc, RGB(255, 0, 0));
							DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						}
						else if (_inven->getvInven()[_isWood].amount >= i * 10 + 20)
						{
							SetTextColor(hdc, RGB(0, 0, 0));
							DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						}

						if (_inven->getvInven()[_isRock].amount < i * 5 + 10) //돌 
						{
							SetTextColor(hdc, RGB(255, 0, 0));
							DrawText(hdc, temp_info[2], strlen(temp_info[1]), &temp4, NULL);
						}
						else if (_inven->getvInven()[_isRock].amount >= i * 5 + 10)
						{
							SetTextColor(hdc, RGB(0, 0, 0));
							DrawText(hdc, temp_info[2], strlen(temp_info[1]), &temp4, NULL);
						}

						if (_inven->getvInven()[_isTomato].amount < i * 5 + 20) //토마토 
						{
							SetTextColor(hdc, RGB(255, 0, 0));
							DrawText(hdc, temp_info[3], strlen(temp_info[1]), &temp4, NULL);
						}
						else if (_inven->getvInven()[_isTomato].amount >= i * 5 + 10)
						{
							SetTextColor(hdc, RGB(0, 0, 0));
							DrawText(hdc, temp_info[3], strlen(temp_info[1]), &temp4, NULL);
						}
					}
					else
					{
						SetTextColor(hdc, RGB(255, 0, 0));
						DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp3, NULL);
						DrawText(hdc, temp_info[2], strlen(temp_info[2]), &temp4, NULL);
						DrawText(hdc, temp_info[3], strlen(temp_info[3]), &temp5, NULL);
					}
				}
				SetTextColor(hdc, RGB(0, 0, 0));
				DrawText(hdc, temp_info[0], strlen(temp_info[0]), &temp1, NULL);
			}
		}
	}
}
