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
			_vCraftItem[i].item_image = IMAGEMANAGER->findImage("����������");
		}
		_vCraftItem[i].rc = RectMake(250 + i % 6 * 50, 130 + i / 6 * 40, 40, 40);

		// ��Ʈ �ʱ�ȭ �� �̹��� �ʱ�ȭ ~


		if(PtInRect(&_vCraftItem[i].rc, _ptMouse))
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				if (i == 0 || i == 6) // �����ΰ��
				{
					for (int i = 0; i < _inven->getvInven().size(); i++)
					{
						if (_inven->getvInven()[i].item_kind == ITEM_DEBRIS && _inven->getvInven()[i].indexX == 6 && _inven->getvInven()[i].indexY == 2)
						{
							if (_inven->getvInven()[i].amount == 10)
							{
								tagItem box;
								box.item_image = IMAGEMANAGER->findImage("������");
								box.indexX = 0;
								box.indexY = 0;
								box.item_kind = ITEM_BOX;
								
								_inven->setMouseItem(box);
								_inven->setInvenItemAmount(i, _inven->getvInven()[i].amount - 10);
							}
						}
					}
				}

				else if (i == 1 || i == 7) // ������?
				{

				}

				else if (i == 2 || i == 8) // �����
				{

				}
				else if (i == 3 || i == 9) //����ƺ�
				{

				}
				else if (i == 4 || i == 10) //�뱤��
				{

				}
				else if (i == 5 || i == 11)//��ȿ��
				{

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
	// IMAGEMANAGER->frameRender("����������", hdc, 225, 30);
	for (int i = 0; i < _vCraftItem.size(); i++)
	{
		if (_vCraftItem[i].item_image != NULL)
		{
			
			_vCraftItem[i].item_image->frameRender(hdc, _vCraftItem[i].rc.left, _vCraftItem[i].rc.top, _vCraftItem[i].indexX, _vCraftItem[i].indexY);

		}
		//Rectangle(hdc, _vCraftItem[i].rc); 
	}
	
}
