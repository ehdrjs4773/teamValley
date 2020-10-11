#include "stdafx.h"
#include "inventory.h"

void inventory::init()
{


	for (int i = 0; i < INVENMAX; i++)
	{
		tagItem temp; // E�������� ������ �κ�36ĭ
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
	_isInvenPage = true;

	_vItem[0] = ITEMMANAGER->findItem("�Ľ��� ����");
	_vItem[1] = ITEMMANAGER->findItem("�ϵ��� ����");
	_vItem[3] = ITEMMANAGER->findItem("ȣ��");
	_vItem[4] = ITEMMANAGER->findItem("���");
	_vItem[5] = ITEMMANAGER->findItem("����");
	_vItem[6] = ITEMMANAGER->findItem("������");
	_vItem[6].waterAmount = 100;
	_vItem[7] = ITEMMANAGER->findItem("���ô�");
	_vItem[8] = ITEMMANAGER->findItem("Į");
	_vItem[9] = ITEMMANAGER->findItem("������Ÿ��");
	_vItem[10] = ITEMMANAGER->findItem("�����Ÿ��");

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
	craftObject();
	_vItemUpdate();

	if(_MouseItem.item_image) _MouseItem.rc = RectMake(_ptMouse.x, _ptMouse.y, _MouseItem.item_image->getFrameWidth(), _MouseItem.item_image->getFrameHeight());
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i].rc = RectMake(263 + 55 * (i % 12), 125 + 55 * (i / 12), 55, 45);
	}

	//_vItem[i].rc = RectMake(265 + 55 * (i % 12), 125 + 55 * (i / 12), 50, 45); // â�� �κ��丮
	
	//if (_MouseStorageItem.item_image) _MouseStorageItem.rc = RectMake(_ptMouse.x, _ptMouse.y, _MouseStorageItem.item_image->getFrameWidth(), _MouseStorageItem.item_image->getFrameHeight());
	for (int i = 0; i < _vStorageItem.size(); i++)
	{
		_vStorageItem[i].rc = RectMake(300 + 55 * (i % 12), 70 + 55 * (i / 12), 50, 45);
	}

	
}

void inventory::render(HDC hdc)// �ܼ��� �÷��̾�� ���� �÷��̾� �κ��丮 ����â (�̻��ϰ� ����������)
{

	inventory2_img = IMAGEMANAGER->findImage("�κ��丮 ������â");
	inventory2_img->render(hdc, 225, 30);

	if (_isInvenPage)
	{
		for (int i = 0; i < _vItem.size(); i++)
		{
			if (_vItem[i].item_image != NULL)
			{
				if (_vItem[i].isFrame)
				{
					_vItem[i].item_image->frameRender(hdc, _vItem[i].rc.left + 10, _vItem[i].rc.top + 2, _vItem[i].indexX, _vItem[i].indexY);
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

	}
	else if (_isCraftPage)
	{

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

void inventory::renderSellingInventory(HDC hdc)
{
	//ĳ���Ͱ� ������ ������ �Ĵ� �ǸŻ��� 

	inventory_img = IMAGEMANAGER->findImage("�����κ��丮");
	inventory_img->render(hdc, 250, 375);






}

void inventory::renderStorageInventory(HDC hdc)
{
	//ĳ������ â�� 36ĭ 

	playerStorage_img = IMAGEMANAGER->findImage("�÷��̾� â��");
	playerStorage_img->render(hdc, 225, 30);

	for (int i = 0; i < STORAGEMAX; i++)
	{
		Rectangle(hdc, _vStorageItem[i].rc);
	}

	
	//ĳ������ â�� �ִ� �κ�36ĭ
	for (int i = 0; i < INVENMAX; i++)
	{
		Rectangle(hdc, _vItem[i].rc);
	}






}

void inventory::_vItemUpdate()
{
	if (_isInvenPage)
	{
		if (_MouseItem.item_image) _MouseItem.rc = RectMake(_ptMouse.x, _ptMouse.y, _MouseItem.item_image->getFrameWidth(), _MouseItem.item_image->getFrameHeight());
		for (int i = 0; i < _vItem.size(); i++)
		{
			_vItem[i].rc = RectMake(265 + 55 * (i % 12), 123 + 55 * (i / 12), 50, 45);

		}

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
	

	for (int i = 0; i < _vStorageItem.size(); i++) //â�� ���� �� 
	{
		if (PtInRect(&_vStorageItem[i].rc, _ptMouse))
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				if (_vStorageItem[i].item_image != NULL)
				{
					if (_MouseStorageItem.item_image != NULL)
					{
	
						tagItem storagePushItem;
						storagePushItem = _vStorageItem[i];
						_vStorageItem[i] = _MouseItem;
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

void inventory::craftObject()
{
}

