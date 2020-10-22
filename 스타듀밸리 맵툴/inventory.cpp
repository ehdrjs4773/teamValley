#include "stdafx.h"
#include "inventory.h"

void inventory::init()
{

	_isShopOpen = false;
	currentSkillNumber = 0;

	for (int i = 0; i < INVENMAX; i++)
	{
		tagItem temp; // 플레이어 인벤
		temp.rc = RectMake(265 + 40 * (i % 12), 125 + 55 * (i / 12), 45, 45);
		temp.item_image = NULL;
		_vItem.push_back(temp);
		cout << &_vItem[i] << endl;
	}

	for (int i = 0; i < STORAGEMAX; i++)
	{
		tagItem storageTemp; // 플레이어 창고
		storageTemp.rc = RectMake(265 + 40 * (i % 12), 300 + 55 * (i / 12), 45, 45);
		storageTemp.item_image = NULL;
		_vStorageItem.push_back(storageTemp);
	}

	_isPlayerPage = false;
	_isCraftPage = false;
	_isInvenPage = false;
	isShowTemp = false;
	isShowStorageTemp = false;

	//_vItem[0] = ITEMMANAGER->findItem("파스닙 씨앗");
	//_vItem[1] = ITEMMANAGER->findItem("완두콩 씨앗");
	//_vItem[2] = ITEMMANAGER->findItem("낫");
	//_vItem[3] = ITEMMANAGER->findItem("호미");
	//_vItem[4] = ITEMMANAGER->findItem("곡괭이");
	//_vItem[5] = ITEMMANAGER->findItem("도끼");
	//_vItem[6] = ITEMMANAGER->findItem("주전자");
	//_vItem[7] = ITEMMANAGER->findItem("칼");
	//_vItem[8] = ITEMMANAGER->findItem("나무울타리");
	//_vItem[9] = ITEMMANAGER->findItem("석재울타리");
	//_vItem[10] = ITEMMANAGER->findItem("소나무 씨앗");
	//_vItem[11] = ITEMMANAGER->findItem("참나무 씨앗");

	_inventoryCraft = new inventoryCraft;
	_inventoryCraft->init();
	_inventoryCraft->setInventoryAddress(this);
	_MouseItem.item_image = NULL;
	_MouseStorageItem.item_image = NULL;

	_isInventoryMove = false;
	currentSlotNumber = 0;

	waterAmount = 34; 

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
	if (INPUT->GetKeyDown(VK_F8))
	{
		_vItem[4] = ITEMMANAGER->findItem("기본스프링클러");
	}
	_isInvenRect = RectMake(275, 50, 50, 50);
	_isPlayerRect = RectMake(330, 50, 50, 50);
	_isCraftRect = RectMake(385, 50, 50, 50);
	_vItemUpdate();
	
	if (isShowTemp)
	{
		for (int i = 0; i < _vItem.size(); i++) //창고를 클릭했을때 나오는 플레이어 인벤토리
		{
			_vItem[i].rc = RectMake(301 + 46 * (i % 12), 297 + 50 * (i / 12), 40, 40);
			if (_vItem[i].toolKind == TOOL_KETTLE)
			{
				_kettleBar = RectMake(_vItem[i].rc.left + 3, _vItem[i].rc.bottom - 7, waterAmount, 4);
			}
		}

		for (int i = 0; i < _vStorageItem.size(); i++) //창고 
		{
			_vStorageItem[i].rc = RectMake(301 + 46 * (i % 12), 69 + 50 * (i / 12), 40, 40);
			if (_vStorageItem[i].toolKind == TOOL_KETTLE)
			{
				_kettleBar = RectMake(_vStorageItem[i].rc.left + 3, _vStorageItem[i].rc.bottom - 7, waterAmount, 4);
			}
		}
	}
	else if (_isInvenPage)
	{
		for (int i = 0; i < _vItem.size(); i++) // E누르면 나오는 인벤토리
		{
			_vItem[i].rc = RectMake(270 + 55 * (i % 12), 135 + 65 * (i / 12), 40, 40);
			if (_vItem[i].toolKind == TOOL_KETTLE)
			{
				_kettleBar = RectMake(_vItem[i].rc.left + 3, _vItem[i].rc.bottom - 7, waterAmount, 4);
			}
		}
	}
	else if (_isCraftPage)
	{
		for (int i = 0; i < _vItem.size(); i++) // E누르면 나오는 제작창
		{
			_vItem[i].rc = RectMake(270 + 55 * (i % 12), 405 + 65 * (i / 12), 40, 40);
			if (_vItem[i].toolKind == TOOL_KETTLE)
			{
				_kettleBar = RectMake(_vItem[i].rc.left + 3, _vItem[i].rc.bottom - 7, waterAmount, 4);
			}
		}
	}
	else if (_isShopOpen)
	{
		for (int i = 0; i < _vItem.size(); i++) // 상점에서 나오는 인벤토리
		{
			_vItem[i].rc = RectMake(336 + 46 * (i % 12), 394 + 50 * (i / 12), 40, 40);
			if (_vItem[i].toolKind == TOOL_KETTLE)
			{
				_kettleBar = RectMake(_vItem[i].rc.left + 3, _vItem[i].rc.bottom - 7, waterAmount, 4);
			}
		}
	}
	else
	{
		for (int i = 0; i < _vItem.size(); i++)
		{
			_vItem[i].rc = RectMake(0, 0, 0, 0);
		}
	}

	for (int i = 0; i < _vItem.size(); i++)
	{
		if (_vItem[i].amount == 0)
		{
			tagItem nullitem;
			nullitem.item_image = NULL;
			_vItem[i] = nullitem;
		}
	}


	//if(_vItem[i].item_image == NULL) setInvenImage(i, _vItem[i].itemName);

	if(_MouseItem.item_image) _MouseItem.rc = RectMake(_ptMouse.x, _ptMouse.y, _MouseItem.item_image->getFrameWidth(), _MouseItem.item_image->getFrameHeight());
	
}

void inventory::render(HDC hdc)// 단순한 플레이어만을 위한 플레이어 인벤토리 정보창 (이상하게 수정하지마)
{

	if (_isInvenPage)
	{
		inventory2_img = IMAGEMANAGER->findImage("인벤토리");
		inventory2_img->render(hdc, 225, 40);

		for (int i = 0; i < _vItem.size(); i++)
		{
			if (_vItem[i].item_image != NULL)
			{
				if (_vItem[i].isFrame)
				{
					_vItem[i].item_image->frameRender(hdc, _vItem[i].rc.left, _vItem[i].rc.top, _vItem[i].indexX, _vItem[i].indexY);

					brush = CreateSolidBrush(RGB(40, 140, 230));
					FillRect(hdc, &_kettleBar, brush);
					DeleteObject(brush);


					if (_vItem[i].item_kind != ITEM_TOOL && _vItem[i].item_kind != ITEM_BOX)
					{

						if (_vItem[i].amount >= 0)
						{
							char str[64];
							wsprintf(str, "%d", _vItem[i].amount);

							textOut(hdc, _vItem[i].rc.left + 30, _vItem[i].rc.top + 30, str, RGB(0, 0, 0));
						}
						//Rectangle(hdc, _vItem[i].rc);
					}
				}
				else
				{
					_vItem[i].item_image->render(hdc, _vItem[i].rc.left, _vItem[i].rc.top);
					if (_vItem[i].amount >= 0)
					{
						char str[64];
						wsprintf(str, "%d", _vItem[i].amount);

						textOut(hdc, _vItem[i].rc.left + 30, _vItem[i].rc.top + 30, str, RGB(0, 0, 0));
					}
				}
			
			}
		}
	}
	else if (_isPlayerPage)
	{
		IMAGEMANAGER->render("스킬창", hdc, 225, 40);
	}
	else if (_isCraftPage)
	{
		_inventoryCraft->update();
		IMAGEMANAGER->render("제작창", hdc, 225, 40);
		_inventoryCraft->render(hdc);

		for (int i = 0; i < _vItem.size(); i++)
		{
			if (_vItem[i].item_image != NULL)
			{

				if (_vItem[i].isFrame)
				{
					//Rectangle(hdc, _vItem[i].rc);
					_vItem[i].item_image->frameRender(hdc, _vItem[i].rc.left, _vItem[i].rc.top, _vItem[i].indexX, _vItem[i].indexY);

					brush = CreateSolidBrush(RGB(40, 140, 230));
					FillRect(hdc, &_kettleBar, brush);
					DeleteObject(brush);
					if (_vItem[i].item_kind != ITEM_TOOL)
					{
						if (_vItem[i].amount >= 0)
						{
							char str[64];
							wsprintf(str, "%d", _vItem[i].amount);

							textOut(hdc, _vItem[i].rc.left + 30, _vItem[i].rc.top + 30, str, RGB(0, 0, 0));
						}
					}
				}
				else
				{
					_vItem[i].item_image->render(hdc, _vItem[i].rc.left, _vItem[i].rc.top);
					if (_vItem[i].item_kind != ITEM_TOOL && _vItem[i].item_kind != ITEM_BOX)
					{
						if (_vItem[i].amount >= 0)
						{
							char str[64];
							wsprintf(str, "%d", _vItem[i].amount);

							textOut(hdc, _vItem[i].rc.left + 30, _vItem[i].rc.top + 30, str, RGB(0, 0, 0));
						}
					}
				}
			}

			if (PtInRect(&_vItem[i].rc, _ptMouse))
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

	if (_MouseItem.item_image)_MouseItem.item_image->frameRender(hdc, _MouseItem.rc.left, _MouseItem.rc.top, _MouseItem.indexX, _MouseItem.indexY);

}  // 단순한 플레이어만을 위한 플레이어 인벤토리 정보창 (이상하게 수정하지마)

void inventory::invenToryRender(HDC hdc) // 밑에 뜨게 하는 인벤토리 (위에꺼 배고 다른걸 다 이거로 처리하면 편하잖아-_ -);
{
	inventory_img = IMAGEMANAGER->findImage("상점인벤토리");
	inventory_img->render(hdc, 250,375);
}

void inventory::quickSlot(HDC hdc)
{
	// 캐릭터 밑에 항상 떠있는 퀵슬롯
	if (_isInvenPage || !isShowTemp)
	{
		_quickSlotRect = RectMake(WINSIZEX / 2 - 282, 520, IMAGEMANAGER->findImage("플레이어 퀵슬롯")->getWidth(), IMAGEMANAGER->findImage("플레이어 퀵슬롯")->getHeight());
		IMAGEMANAGER->render("플레이어 퀵슬롯", hdc, _quickSlotRect.left, _quickSlotRect.top);

		for (int i = 0; i < 12; i++)
		{
			if (_vItem[i].item_image != NULL)
			{
				if (_vItem[i].isFrame)
				{
					_vItem[i].item_image->frameRender(hdc, _playerTool[i].left, _playerTool[i].top, _vItem[i].indexX, _vItem[i].indexY);
					if (_vItem[i].item_kind != ITEM_TOOL)
					{
						if (_vItem[i].amount >= 0)
						{
							char str[64];
							wsprintf(str, "%d", _vItem[i].amount);

							textOut(hdc, _playerTool[i].left + 30, _playerTool[i].top + 30, str, RGB(0, 0, 0));
						}
					}
				}
				else
				{
					_vItem[i].item_image->render(hdc, _playerTool[i].left, _playerTool[i].top);
					if (_vItem[i].item_kind != ITEM_TOOL)
					{
						if (_vItem[i].amount >= 0)
						{
							char str[64];
							wsprintf(str, "%d", _vItem[i].amount);

							textOut(hdc, _playerTool[i].left + 30, _playerTool[i].top + 30, str, RGB(0, 0, 0));
						}
					}
				}
				if (_vItem[i].toolKind == TOOL_KETTLE)
				{
					_kettleBar = RectMake(_playerTool[i].left + 3, _playerTool[i].bottom - 7, waterAmount, 4);

					brush = CreateSolidBrush(RGB(40, 140, 230));
					FillRect(hdc, &_kettleBar, brush);
					DeleteObject(brush);

				}
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
} 

void inventory::quickSkillSlot(HDC hdc)
{
	if (_isInvenPage || !isShowTemp)
	{
		IMAGEMANAGER->render("플레이어 퀵슬롯", hdc, WINSIZEX / 2 - 282, 520);

		PLAYER->skill_slot(hdc);

		for (int i = 0; i < 6; i++)
		{

			if (PtInRect(&_playerTool[i], _ptMouse))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					currentSkillNumber = i;
				}
			}
		}

		if (INPUT->GetKeyDown('1'))
		{
			currentSkillNumber = 0;
		}
		if (INPUT->GetKeyDown('2'))
		{
			currentSkillNumber = 1;
		}
		if (INPUT->GetKeyDown('3'))
		{
			currentSkillNumber = 2;
		}
		if (INPUT->GetKeyDown('4'))
		{
			currentSkillNumber = 3;
		}
		if (INPUT->GetKeyDown('5'))
		{
			currentSkillNumber = 4;
		}
		if (INPUT->GetKeyDown('6'))
		{
			currentSkillNumber = 5;
		}
		RECT temp{ _playerTool[currentSkillNumber].left,_playerTool[currentSkillNumber].top,_playerTool[currentSkillNumber].right,_playerTool[currentSkillNumber].bottom };
		FrameRect(hdc, temp, RGB(255, 0, 0));
	}
}

void inventory::renderStorageInventory(HDC hdc) 
{
	//캐릭터의 창고 36칸 
	playerStorage_img = IMAGEMANAGER->findImage("플레이어 창고");
	playerStorage_img->render(hdc, 225, 30);


	for (int i = 0; i < STORAGEMAX; i++)
	{
		if (_vStorageItem[i].item_image == NULL)continue;
		if (_vStorageItem[i].isFrame)
		{
			_vStorageItem[i].item_image->frameRender(hdc, _vStorageItem[i].rc.left, _vStorageItem[i].rc.top, _vStorageItem[i].indexX, _vStorageItem[i].indexY);
			if (_vStorageItem[i].item_kind != ITEM_TOOL)
			{
				{
					if (_vStorageItem[i].amount >= 0)
					{
						char str[64];
						wsprintf(str, "%d", _vStorageItem[i].amount);

						textOut(hdc, _vStorageItem[i].rc.left + 30, _vStorageItem[i].rc.top + 30, str, RGB(0, 0, 0));
					}
				}
			}
		}
		else
		{
			_vStorageItem[i].item_image->render(hdc, _vStorageItem[i].rc.left, _vStorageItem[i].rc.top);
			if (_vStorageItem[i].item_kind != ITEM_TOOL)
			{
				if (_vStorageItem[i].amount >= 0)
				{
					char str[64];
					wsprintf(str, "%d", _vStorageItem[i].amount);

					textOut(hdc, _vStorageItem[i].rc.left + 30, _vStorageItem[i].rc.top + 30, str, RGB(0, 0, 0));
				}
			}
		}
		if (_vStorageItem[i].toolKind == TOOL_KETTLE)
		{
			_kettleBar = RectMake(_vStorageItem[i].rc.left + 3, _vStorageItem[i].rc.bottom - 7, waterAmount, 4);

			brush = CreateSolidBrush(RGB(40, 140, 230));
			FillRect(hdc, &_kettleBar, brush);
			DeleteObject(brush);

		}
	}

	//캐릭터의 창고에 있는 인벤36칸
	for (int i = 0; i < INVENMAX; i++)
	{
		if (_vItem[i].item_image == NULL) continue;
		if (_vItem[i].isFrame)
		{
			_vItem[i].item_image->frameRender(hdc, _vItem[i].rc.left, _vItem[i].rc.top, _vItem[i].indexX, _vItem[i].indexY);
			if (_vItem[i].item_kind != ITEM_TOOL)
			{
				if (_vItem[i].amount >= 0)
				{
					char str[64];
					wsprintf(str, "%d", _vItem[i].amount);
		
					textOut(hdc, _vItem[i].rc.left + 30, _vItem[i].rc.top + 30, str, RGB(0, 0, 0));
				}
			}
		}
		else
		{
			_vItem[i].item_image->render(hdc, _vItem[i].rc.left, _vItem[i].rc.top);
			if (_vItem[i].item_kind != ITEM_TOOL)
			{
				if (_vItem[i].amount >= 0)
				{
					char str[64];
					wsprintf(str, "%d", _vItem[i].amount);
		
					textOut(hdc, _vItem[i].rc.left + 30, _vItem[i].rc.top + 30, str, RGB(0, 0, 0));
				}
			}
		}
		brush = CreateSolidBrush(RGB(40, 140, 230));
		FillRect(hdc, &_kettleBar, brush);
		DeleteObject(brush);


	

	}
	
}

void inventory::inven_item_info(HDC hdc)
{
	for (int i = 0; i < INVENMAX; i++)
	{
		if (PtInRect(&_vItem[i].rc, _ptMouse))
		{
			if (_vItem[i].item_image != NULL)
			{
				char temp_info[2][256];
				RECT temp1 = RectMake(_ptMouse.x + 35, _ptMouse.y + 45, 200, 50);
				RECT temp2 = RectMake(temp1.left, temp1.bottom, 200, 100);
				IMAGEMANAGER->findImage("아이템정보")->render(hdc, _ptMouse.x + 25, _ptMouse.y + 25);

				SetTextColor(hdc, RGB(0, 0, 0));

				memset(temp_info, 0, sizeof(temp_info));

				switch (_vItem[i].item_kind)
				{
				case ITEM_WEAPON:
					sprintf(temp_info[0], "WEAPON", sizeof("WEAPON"));
					break;
				case ITEM_TOOL:
					sprintf(temp_info[0], "TOOL", sizeof("TOOL"));
					break;
				case ITEM_SEED:
					sprintf(temp_info[0], "SEED", sizeof("SEED"));
					break;
				case ITEM_FRUIT:
					sprintf(temp_info[0], "FRUIT", sizeof("FRUIT"));
					break;
				case ITEM_DEBRIS:
					sprintf(temp_info[0], "DEBRIS", sizeof("DEBRIS"));
					break;
				case ITEM_WOODENFENCE:
					sprintf(temp_info[0], "WOODENFENCE", sizeof("WOODENFENCE"));
					break;
				case ITEM_WOODENFENCEDOOR:
					sprintf(temp_info[0], "WOODENFENCE DOOR", sizeof("WOODENFENCE DOOR"));
					break;
				case ITEM_STONEFENCE:
					sprintf(temp_info[0], "STONEFENCE", sizeof("STONEFENCE"));
					break;
				case ITEM_STONEFENCEDOOR:
					sprintf(temp_info[0], "STONEFENCE DOOR", sizeof("STONEFENCE DOOR"));
					break;
				case ITEM_SKILL:
					sprintf(temp_info[0], "SKILL", sizeof("SKILL"));
					break;
				case ITEM_BOX:
					sprintf(temp_info[0], "BOX", sizeof("BOX"));
					break;
				case ITEM_FEEDBUCKET:
					sprintf(temp_info[0], "FEED BUCKET", sizeof("FEED BUCKET"));
					break;
				case ITEM_BEEFARM:
					sprintf(temp_info[0], "BEE FARM", sizeof("BEE FARM"));
					break;
				case ITEM_SCARECROW:
					sprintf(temp_info[0], "SCARECROW", sizeof("SCARECROW"));
					break;
				case ITEM_BLASTFURNACE:
					sprintf(temp_info[0], "BLAST FURNACE", sizeof("BLAST FURNACE"));
					break;
				case ITEM_PICKLEDBARREL:
					sprintf(temp_info[0], "PICKLED BARREL", sizeof("PICKLED BARREL"));
					break;
				}
				sprintf(temp_info[1], _vItem[i].item_info, sizeof(_vItem[i].item_info));

				DrawText(hdc, temp_info[0], strlen(temp_info[0]), &temp1, NULL);
				DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp2, NULL);
			}
		}
	}
}

void inventory::quickinven_item_info(HDC hdc)
{
	for (int i = 0; i < 12; i++)
	{
		if (PtInRect(&_playerTool[i], _ptMouse))
		{
			if (_vItem[i].item_image != NULL)
			{
				char temp_info[2][256];
				RECT temp1 = RectMake(_ptMouse.x + 35, _ptMouse.y + -150, 200, 50);
				RECT temp2 = RectMake(temp1.left, temp1.bottom, 200, 100);
				IMAGEMANAGER->findImage("아이템정보")->render(hdc, _ptMouse.x + 25, _ptMouse.y - 170);

				SetTextColor(hdc, RGB(0, 0, 0));

				memset(temp_info, 0, sizeof(temp_info));

				switch (_vItem[i].item_kind)
				{
				case ITEM_WEAPON:
					sprintf(temp_info[0], "WEAPON", sizeof("WEAPON"));
					break;
				case ITEM_TOOL:
					sprintf(temp_info[0], "TOOL", sizeof("TOOL"));
					break;
				case ITEM_SEED:
					sprintf(temp_info[0], "SEED", sizeof("SEED"));
					break;
				case ITEM_FRUIT:
					sprintf(temp_info[0], "FRUIT", sizeof("FRUIT"));
					break;
				case ITEM_DEBRIS:
					sprintf(temp_info[0], "DEBRIS", sizeof("DEBRIS"));
					break;
				case ITEM_WOODENFENCE:
					sprintf(temp_info[0], "WOODENFENCE", sizeof("WOODENFENCE"));
					break;
				case ITEM_WOODENFENCEDOOR:
					sprintf(temp_info[0], "WOODENFENCE DOOR", sizeof("WOODENFENCE DOOR"));
					break;
				case ITEM_STONEFENCE:
					sprintf(temp_info[0], "STONEFENCE", sizeof("STONEFENCE"));
					break;
				case ITEM_STONEFENCEDOOR:
					sprintf(temp_info[0], "STONEFENCE DOOR", sizeof("STONEFENCE DOOR"));
					break;
				case ITEM_SKILL:
					sprintf(temp_info[0], "SKILL", sizeof("SKILL"));
					break;
				case ITEM_BOX:
					sprintf(temp_info[0], "BOX", sizeof("BOX"));
					break;
				case ITEM_FEEDBUCKET:
					sprintf(temp_info[0], "FEED BUCKET", sizeof("FEED BUCKET"));
					break;
				case ITEM_BEEFARM:
					sprintf(temp_info[0], "BEE FARM", sizeof("BEE FARM"));
					break;
				case ITEM_SCARECROW:
					sprintf(temp_info[0], "SCARECROW", sizeof("SCARECROW"));
					break;
				case ITEM_BLASTFURNACE:
					sprintf(temp_info[0], "BLAST FURNACE", sizeof("BLAST FURNACE"));
					break;
				case ITEM_PICKLEDBARREL:
					sprintf(temp_info[0], "PICKLED BARREL", sizeof("PICKLED BARREL"));
					break;
				}
				sprintf(temp_info[1], _vItem[i].item_info, sizeof(_vItem[i].item_info));


				DrawText(hdc, temp_info[0], strlen(temp_info[0]), &temp1, NULL);
				DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp2, NULL);

			}

		}
	}
}

void inventory::storage_item_info(HDC hdc)
{
	for (int i = 0; i < INVENMAX; i++)
	{
		if (PtInRect(&_vStorageItem[i].rc, _ptMouse))
		{
			if (_vStorageItem[i].item_image != NULL)
			{
				char temp_info[2][256];
				RECT temp1 = RectMake(_ptMouse.x + 35, _ptMouse.y + 45, 200, 50);
				RECT temp2 = RectMake(temp1.left, temp1.bottom, 200, 100);
				IMAGEMANAGER->findImage("아이템정보")->render(hdc, _ptMouse.x + 25, _ptMouse.y + 25);

				SetTextColor(hdc, RGB(0, 0, 0));

				memset(temp_info, 0, sizeof(temp_info));

				switch (_vStorageItem[i].item_kind)
				{
				case ITEM_WEAPON:
					sprintf(temp_info[0], "WEAPON", sizeof("WEAPON"));
					break;
				case ITEM_TOOL:
					sprintf(temp_info[0], "TOOL", sizeof("TOOL"));
					break;
				case ITEM_SEED:
					sprintf(temp_info[0], "SEED", sizeof("SEED"));
					break;
				case ITEM_FRUIT:
					sprintf(temp_info[0], "FRUIT", sizeof("FRUIT"));
					break;
				case ITEM_DEBRIS:
					sprintf(temp_info[0], "DEBRIS", sizeof("DEBRIS"));
					break;
				case ITEM_WOODENFENCE:
					sprintf(temp_info[0], "WOODENFENCE", sizeof("WOODENFENCE"));
					break;
				case ITEM_WOODENFENCEDOOR:
					sprintf(temp_info[0], "WOODENFENCE DOOR", sizeof("WOODENFENCE DOOR"));
					break;
				case ITEM_STONEFENCE:
					sprintf(temp_info[0], "STONEFENCE", sizeof("STONEFENCE"));
					break;
				case ITEM_STONEFENCEDOOR:
					sprintf(temp_info[0], "STONEFENCE DOOR", sizeof("STONEFENCE DOOR"));
					break;
				case ITEM_SKILL:
					sprintf(temp_info[0], "SKILL", sizeof("SKILL"));
					break;
				case ITEM_BOX:
					sprintf(temp_info[0], "BOX", sizeof("BOX"));
					break;
				case ITEM_FEEDBUCKET:
					sprintf(temp_info[0], "FEED BUCKET", sizeof("FEED BUCKET"));
					break;
				case ITEM_BEEFARM:
					sprintf(temp_info[0], "BEE FARM", sizeof("BEE FARM"));
					break;
				case ITEM_SCARECROW:
					sprintf(temp_info[0], "SCARECROW", sizeof("SCARECROW"));
					break;
				case ITEM_BLASTFURNACE:
					sprintf(temp_info[0], "BLAST FURNACE", sizeof("BLAST FURNACE"));
					break;
				case ITEM_PICKLEDBARREL:
					sprintf(temp_info[0], "PICKLED BARREL", sizeof("PICKLED BARREL"));
					break;
				}
				sprintf(temp_info[1],0,(string)_vStorageItem[i].item_info, sizeof(_vStorageItem[i].item_info));

				DrawText(hdc, temp_info[0], strlen(temp_info[0]), &temp1, NULL);
				DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp2, NULL);
			}
		}
	}
}

void inventory::_vItemUpdate()
{
	if (!isShowTemp)
	{
		if (PtInRect(&_isInvenRect, _ptMouse) && !_isShopOpen)
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				SOUNDMANAGER->play("select");
				if (_isInvenPage) _isInvenPage = false;
				if (_isCraftPage) _isCraftPage = false;
				_isInvenPage = true;
			}
		}
		else if (PtInRect(&_isPlayerRect, _ptMouse))
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				SOUNDMANAGER->play("select");
				if (_isInvenPage) _isInvenPage = false;
				if (_isCraftPage) _isCraftPage = false;
				_isPlayerPage = true;
			}
		}
		else if (PtInRect(&_isCraftRect, _ptMouse) && !_isShopOpen)
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				SOUNDMANAGER->play("select");
				if (_isInvenPage) _isInvenPage = false;
				if (_isPlayerPage) _isPlayerPage = false;
				_isCraftPage = true;
			}
		}
	}
	

	if (_isShopOpen)
	{
		// 상점이 켜졌을 경우
	}
	else if (_isInvenPage)
	{
		if (_MouseItem.item_image) _MouseItem.rc = RectMake(_ptMouse.x, _ptMouse.y, _MouseItem.item_image->getFrameWidth(), _MouseItem.item_image->getFrameHeight());


		for (int i = 0; i < _vItem.size(); i++)
		{
			if (PtInRect(&_vItem[i].rc, _ptMouse))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					if (_vItem[i].item_image != NULL) // 아이템이 있으면
					{
						if (_MouseItem.item_image != NULL) // 마우스에 아이템이 있으면
						{
							if (_MouseItem.item_info == _vItem[i].item_info)
							{
								_vItem[i].amount += _MouseItem.amount;
								tagItem nullItem = { 0 };
								_MouseItem = nullItem;
							}
							else
							{
								tagItem exchangeItem; // 교환용 아이템
								exchangeItem = _vItem[i];
								_vItem[i] = _MouseItem;
								_MouseItem = exchangeItem;
							}
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
	 else if(isShowTemp)
	 {
		 for (int i = 0; i < _vStorageItem.size(); i++) //창고 벡터 식 
		 {
			 if (PtInRect(&_vStorageItem[i].rc, _ptMouse))
			 {
				 if (INPUT->GetKeyDown(VK_LBUTTON))
				 {
					 if (_vStorageItem[i].item_image != NULL)
					 {
						 for (int j = 0; j < _vItem.size(); j++)
						 {

							 if (_vItem[j].item_image == NULL)
							 {
								 _vItem[j] = _vStorageItem[i];
								 _vStorageItem[i] = _MouseItem;
							 }


						 }
					 }
				 }
			 }
		 }
		 for (int i = 0; i < _vItem.size(); i++) //창고 벡터 식 
		 {
			 if (PtInRect(&_vItem[i].rc, _ptMouse))
			 {
				 if (INPUT->GetKeyDown(VK_LBUTTON))
				 {
					 if (_vItem[i].item_image != NULL)
					 {
						 for (int j = 0; j < _vStorageItem.size(); j++)
						 {

							 if (_vStorageItem[j].item_image == NULL)
							 {
								 _vStorageItem[j] = _vItem[i];
								 _vItem[i] = _MouseItem;
							 }

						 }
					 }
				 }
			 }
		 }

		 for (int i = 0; i < _vStorageItem.size(); i++)
		 {
			 if (i > 0 && _vStorageItem[i - 1].item_image == NULL)
			 {
				 _vStorageItem[i - 1] = _vStorageItem[i];
				 _vStorageItem[i] = _MouseItem;
			 }
		 }
	 }

}

void inventory::shopInvenRender(HDC hdc)
{
	IMAGEMANAGER->findImage("상점인벤토리1")->render(hdc, 305, 370);
}

void inventory::setInvenItem(int i, tagItem item)
{
	_vItem[i] = item;
	if (item.item_info == "구리조각" || item.item_info == "철조각" || item.item_info == "금조각" || item.item_info == "석탄")
	{
		_vItem[i].item_image = IMAGEMANAGER->findImage("광물아이템");
	}
}

void inventory::setvInven(int i, tagSaveItem item)
{
	_vItem[i].amount = item.amount;
	_vItem[i].buy_price = item.buy_price;
	_vItem[i].indexX = item.indexX;
	_vItem[i].indexY = item.indexY;
	_vItem[i].isFrame = item.isFrame;
	_vItem[i].item_kind = item.item_kind;
	_vItem[i].rc = item.rc;
	_vItem[i].seedKind = item.seedKind;
	_vItem[i].sell_price = item.sell_price;
	_vItem[i].toolKind = item.toolKind;
	_vItem[i].waterAmount = item.waterAmount;


	if (_vItem[i].item_kind == ITEM_TOOL)
	{
		_vItem[i].item_image = IMAGEMANAGER->findImage("도구");
		_vItem[i].item_info = ITEMMANAGER->findItem(_vItem[i].toolKind);
		_vItem[i].itemName = _vItem[i].item_info;
	}
	else if (_vItem[i].item_kind == ITEM_SEED)
	{
		_vItem[i].item_image = IMAGEMANAGER->findImage("씨앗");
		if (_vItem[i].seedKind == SEED_COFFEEBEAN || _vItem[i].seedKind == SEED_PINETREE || _vItem[i].seedKind == SEED_MAPLETREE || _vItem[i].seedKind == SEED_OAKTREE)
		{
			_vItem[i].item_image = IMAGEMANAGER->findImage("열매");
		}
		_vItem[i].item_info = ITEMMANAGER->findItem(_vItem[i].item_kind, _vItem[i].seedKind);
		_vItem[i].itemName = _vItem[i].item_info;
	}
	else if (_vItem[i].item_kind == ITEM_FRUIT)
	{
		_vItem[i].item_image = IMAGEMANAGER->findImage("열매");
		_vItem[i].item_info = ITEMMANAGER->findItem(_vItem[i].item_kind, _vItem[i].seedKind);
		_vItem[i].itemName = _vItem[i].item_info;
	}
	else if (_vItem[i].item_kind == ITEM_ORE)
	{
		_vItem[i].item_image = IMAGEMANAGER->findImage("광물");
		_vItem[i].item_info = ITEMMANAGER->findItem(_vItem[i].item_kind, _vItem[i].indexX);
		_vItem[i].itemName = _vItem[i].item_info;
	}
	else if (_vItem[i].item_kind == ITEM_DEBRIS)
	{
		_vItem[i].item_image = IMAGEMANAGER->findImage("열매");
		_vItem[i].item_info = ITEMMANAGER->findItem(_vItem[i].item_kind, _vItem[i].indexX);
		_vItem[i].itemName = _vItem[i].item_info;
	}
	else if (_vItem[i].item_kind == ITEM_WOODENFENCE || _vItem[i].item_kind == ITEM_STONEFENCE
		|| _vItem[i].item_kind == ITEM_WOODENFENCEDOOR || _vItem[i].item_kind == ITEM_STONEFENCEDOOR)
	{
		_vItem[i].item_image = IMAGEMANAGER->findImage("펜스");
		_vItem[i].item_info = ITEMMANAGER->findItem(_vItem[i].item_kind);
		_vItem[i].itemName = _vItem[i].item_info;
	}
	else if (_vItem[i].item_kind == ITEM_SKILL || _vItem[i].item_kind == ITEM_WEAPON)
	{
		switch (_vItem[i].weaponKind)
		{
		case WEAPON_NONE:
			break;
		case WEAPON_RUSTYSWORD:
			_vItem[i].item_image = IMAGEMANAGER->findImage("rusty_sword");
			_vItem[i].item_info = "녹슨 소드";
			break;
		case WEAPON_GALAXYSWORD:
			_vItem[i].item_image = IMAGEMANAGER->findImage("galaxy_sword");
			_vItem[i].item_info = "갤럭시 소드";
			break;
		case WEAPON_PENCIL:
			_vItem[i].item_image = IMAGEMANAGER->findImage("pencil");
			_vItem[i].item_info = "연필";
			break;
		case WEAPON_EXPLOSION:
			_vItem[i].item_image = IMAGEMANAGER->findImage("스킬북");
			_vItem[i].item_info = "EXPLOSION";
			break;
		case WEAPON_SPIKES:
			_vItem[i].item_image = IMAGEMANAGER->findImage("스킬북");
			_vItem[i].item_info = "SPIKES";
			break;
		case WEAPON_FIRE:
			_vItem[i].item_image = IMAGEMANAGER->findImage("스킬북");
			_vItem[i].item_info = "FIRE";
			break;
		case WEAPON_SHIELD:
			_vItem[i].item_image = IMAGEMANAGER->findImage("스킬북");
			_vItem[i].item_info = "SHIELD";
			break;
		case WEAPON_BLACKHOLE:
			_vItem[i].item_image = IMAGEMANAGER->findImage("스킬북");
			_vItem[i].item_info = "BLACKHOLE";
			break;
		case WEAPON_FIREBALL:
			_vItem[i].item_image = IMAGEMANAGER->findImage("스킬북");
			_vItem[i].item_info = "FIRE_BALL";
			break;
		}
		_vItem[i].itemName = _vItem[i].item_info;
	}
	else if (_vItem[i].item_kind == ITEM_SPRINKLER)
	{
		_vItem[i].item_image = IMAGEMANAGER->findImage("스프링클러");
		switch (_vItem[i].indexY)
		{
		case 0:
			_vItem[i].item_info = "기본스프링클러";
			break;
		case 1:
			_vItem[i].item_info = "강화스프링클러";
			break;
		case 2:
			_vItem[i].item_info = "고급스프링클러";
			break;
		}
		_vItem[i].itemName = _vItem[i].item_info;
	}
}
