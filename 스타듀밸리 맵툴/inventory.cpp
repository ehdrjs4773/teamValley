#include "stdafx.h"
#include "inventory.h"

void inventory::init()
{

	_isShopOpen = false;

	for (int i = 0; i < INVENMAX; i++)
	{
		tagItem temp; // �÷��̾� �κ�
		temp.rc = RectMake(265 + 40 * (i % 12), 125 + 55 * (i / 12), 45, 45);
		temp.item_image = NULL;
		_vItem.push_back(temp);
		
	}

	for (int i = 0; i < STORAGEMAX; i++)
	{
		tagItem storageTemp; // �÷��̾� â��
		storageTemp.rc = RectMake(265 + 40 * (i % 12), 300 + 55 * (i / 12), 45, 45);
		storageTemp.item_image = NULL;
		_vStorageItem.push_back(storageTemp);
	}

	_isPlayerPage = false;
	_isCraftPage = false;
	_isInvenPage = false;
	isShowTemp = false;
	isShowStorageTemp = false;

	_vItem[0] = ITEMMANAGER->findItem("�Ľ��� ����");
	_vItem[1] = ITEMMANAGER->findItem("�ϵ��� ����");
	_vItem[3] = ITEMMANAGER->findItem("ȣ��");
	_vItem[4] = ITEMMANAGER->findItem("���");
	_vItem[5] = ITEMMANAGER->findItem("����");
	_vItem[6] = ITEMMANAGER->findItem("������");
	_vItem[6].waterAmount = 100;
	_vItem[7] = ITEMMANAGER->findItem("Į");
	_vItem[8] = ITEMMANAGER->findItem("������Ÿ��");
	_vItem[9] = ITEMMANAGER->findItem("�����Ÿ��");
	_vItem[10] = ITEMMANAGER->findItem("�ҳ��� ����");
	_vItem[11] = ITEMMANAGER->findItem("������ ����");
	_inventoryCraft = new inventoryCraft;
	_inventoryCraft->init();
	_inventoryCraft->setInventoryAddress(this);
	_MouseItem.item_image = NULL;
	_MouseStorageItem.item_image = NULL;

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
	_isInvenRect = RectMake(275, 50, 50, 50);
	_isPlayerRect = RectMake(330, 50, 50, 50);
	_isCraftRect = RectMake(385, 50, 50, 50);
	_vItemUpdate();

	if(_MouseItem.item_image) _MouseItem.rc = RectMake(_ptMouse.x, _ptMouse.y, _MouseItem.item_image->getFrameWidth(), _MouseItem.item_image->getFrameHeight());
	
	if (isShowTemp)
	{
		for (int i = 0; i < _vItem.size(); i++) //â�� Ŭ�������� ������ �÷��̾� �κ��丮
		{
			_vItem[i].rc = RectMake(301 + 46 * (i % 12), 297 + 50 * (i / 12), 40, 40);
		}
	}
	else if (_isInvenPage)
	{
		for (int i = 0; i < _vItem.size(); i++) // E������ ������ �κ��丮
		{
			_vItem[i].rc = RectMake(270 + 55 * (i % 12), 135 + 65 * (i / 12), 40, 40);
		}
	}
	else if (_isCraftPage)
	{
		for (int i = 0; i < _vItem.size(); i++) // E������ ������ �κ��丮
		{
			_inventoryCraft->update();
			_vItem[i].rc = RectMake(270 + 55 * (i % 12), 405 + 65 * (i / 12), 40, 40);
		}
	}

	if (_isShopOpen)
	{	
		for (int i = 0; i < _vItem.size(); i++) // E������ ������ �κ��丮
		{
			_vItem[i].rc = RectMake(296 + 46 * (i % 12), 394 + 50 * (i / 12), 40, 40);
		}
	}

	//if (_MouseStorageItem.item_image) _MouseStorageItem.rc = RectMake(_ptMouse.x, _ptMouse.y, _MouseStorageItem.item_image->getFrameWidth(), _MouseStorageItem.item_image->getFrameHeight());
	
	for (int i = 0; i < _vStorageItem.size(); i++) //â�� 
	{
		_vStorageItem[i].rc = RectMake(301 + 46 * (i % 12), 69 + 50 * (i / 12), 40, 40);
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
}

void inventory::render(HDC hdc)// �ܼ��� �÷��̾�� ���� �÷��̾� �κ��丮 ����â (�̻��ϰ� ����������)
{

	if (_isInvenPage)
	{
		inventory2_img = IMAGEMANAGER->findImage("�κ��丮");
		inventory2_img->render(hdc, 225, 40);

		for (int i = 0; i < _vItem.size(); i++)
		{
			if (_vItem[i].item_image != NULL)
			{
				if (_vItem[i].isFrame)
				{
					_vItem[i].item_image->frameRender(hdc, _vItem[i].rc.left , _vItem[i].rc.top, _vItem[i].indexX, _vItem[i].indexY);
					//Rectangle(hdc, _vItem[i].rc);
				}
				else
				{
					_vItem[i].item_image->render(hdc, _vItem[i].rc.left, _vItem[i].rc.top);
				}
			}
		}
	}
	else if (_isPlayerPage)
	{
		IMAGEMANAGER->render("��ų", hdc, 225, 40);
	}
	else if (_isCraftPage)
	{
		_inventoryCraft->update();
		IMAGEMANAGER->render("����â", hdc, 225, 40);
		_inventoryCraft->render(hdc);

		for (int i = 0; i < _vItem.size(); i++)
		{
			if (_vItem[i].item_image != NULL)
			{
				if (_vItem[i].isFrame)
				{
					//Rectangle(hdc, _vItem[i].rc);
					_vItem[i].item_image->frameRender(hdc, _vItem[i].rc.left, _vItem[i].rc.top, _vItem[i].indexX, _vItem[i].indexY);
				}
				else
				{
					_vItem[i].item_image->render(hdc, _vItem[i].rc.left, _vItem[i].rc.top);
				}
			}
		}
	}

	if (_MouseItem.item_image)_MouseItem.item_image->frameRender(hdc, _MouseItem.rc.left, _MouseItem.rc.top, _MouseItem.indexX, _MouseItem.indexY);
}  // �ܼ��� �÷��̾�� ���� �÷��̾� �κ��丮 ����â (�̻��ϰ� ����������)

void inventory::invenToryRender(HDC hdc) // �ؿ� �߰� �ϴ� �κ��丮 (������ ��� �ٸ��� �� �̰ŷ� ó���ϸ� �����ݾ�-_ -);
{
	inventory_img = IMAGEMANAGER->findImage("�����κ��丮");
	inventory_img->render(hdc, 250,375);
}

void inventory::quickSlot(HDC hdc)
{
	// ĳ���� �ؿ� �׻� ���ִ� ������
	if (_isInvenPage || !isShowTemp)
	{
		IMAGEMANAGER->render("�÷��̾� ������", hdc, WINSIZEX / 2 - 282, 520);

		for (int i = 0; i < 12; i++)
		{
			if (_vItem[i].item_image != NULL)
			{
				_vItem[i].item_image->frameRender(hdc, _playerTool[i].left, _playerTool[i].top, _vItem[i].indexX, _vItem[i].indexY);
				if (_vItem[i].amount >= 0)
				{
					char str[64];
					wsprintf(str, "%d", _vItem[i].amount);

					textOut(hdc, _playerTool[i].left + 30, _playerTool[i].top + 30, str, RGB(0, 0, 0));
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


void inventory::renderStorageInventory(HDC hdc) 
{
	//ĳ������ â�� 36ĭ 

	playerStorage_img = IMAGEMANAGER->findImage("�÷��̾� â��");
	playerStorage_img->render(hdc, 225, 30);


	for (int i = 0; i < STORAGEMAX; i++)
	{
		if (_vStorageItem[i].item_image == NULL)continue;
		_vStorageItem[i].item_image->frameRender(hdc, _vStorageItem[i].rc.left, _vStorageItem[i].rc.top, _vStorageItem[i].indexX, _vStorageItem[i].indexY);
	}

	//ĳ������ â�� �ִ� �κ�36ĭ
	for (int i = 0; i < INVENMAX; i++)
	{
		if (_vItem[i].item_image == NULL) continue;
		_vItem[i].item_image->frameRender(hdc, _vItem[i].rc.left, _vItem[i].rc.top, _vItem[i].indexX, _vItem[i].indexY);
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
				IMAGEMANAGER->findImage("����������")->render(hdc, _ptMouse.x + 25, _ptMouse.y + 25);

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
				IMAGEMANAGER->findImage("����������")->render(hdc, _ptMouse.x + 25, _ptMouse.y - 170);

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
				}
				sprintf(temp_info[1], _vItem[i].item_info, sizeof(_vItem[i].item_info));


				DrawText(hdc, temp_info[0], strlen(temp_info[0]), &temp1, NULL);
				DrawText(hdc, temp_info[1], strlen(temp_info[1]), &temp2, NULL);

			}

		}
	}

}

void inventory::_vItemUpdate()
{
	if (PtInRect(&_isInvenRect, _ptMouse))
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			if (_isInvenPage) _isInvenPage = false;
			if (_isCraftPage) _isCraftPage = false;
			_isInvenPage = true;
		}
	}
	else if (PtInRect(&_isPlayerRect, _ptMouse))
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			if (_isInvenPage) _isInvenPage = false;
			if (_isCraftPage) _isCraftPage = false;
			_isPlayerPage = true;
		}
	}
	else if (PtInRect(&_isCraftRect, _ptMouse))
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			if (_isInvenPage) _isInvenPage = false;
			if (_isPlayerPage) _isPlayerPage = false;
			_isCraftPage = true;
		}
	}

	if (_isShopOpen)
	{
		// ������ ������ ���
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
					if (_vItem[i].item_image != NULL) // �������� ������
					{
						if (_MouseItem.item_image != NULL) // ���콺�� �������� ������
						{
							tagItem exchangeItem; // ��ȯ�� ������
							exchangeItem = _vItem[i];
							_vItem[i] = _MouseItem;
							_MouseItem = exchangeItem;
						}

						else if (_MouseItem.item_image == NULL) // ���콺�� �������� ������
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
		 for (int i = 0; i < _vStorageItem.size(); i++) //â�� ���� �� 
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
		 for (int i = 0; i < _vItem.size(); i++) //â�� ���� �� 
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

	 if (_isCraftPage)
	 {
		 for (int i = 0; i < _vItem.size(); i++)
		 {
			 if (PtInRect(&_vItem[i].rc, _ptMouse))
			 {
				 if (INPUT->GetKeyDown(VK_LBUTTON))
				 {
					 if (_vItem[i].item_image != NULL) // �������� ������
					 {
						 if (_MouseItem.item_image != NULL) // ���콺�� �������� ������
						 {
							 tagItem exchangeItem; // ��ȯ�� ������
							 exchangeItem = _vItem[i];
							 _vItem[i] = _MouseItem;
							 _MouseItem = exchangeItem;
						 }

						 else if (_MouseItem.item_image == NULL) // ���콺�� �������� ������
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

}

void inventory::shopInvenRender(HDC hdc)
{
	IMAGEMANAGER->findImage("�����κ��丮1")->render(hdc, 265, 370);
	inven_item_info(hdc);
}
