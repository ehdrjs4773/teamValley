#include "stdafx.h"
#include "inventoryCraft.h"
#include "inventory.h"

void inventoryCraft::init()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			_CraftItem.item_image = IMAGEMANAGER->findImage("아이템제작");
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
			_vCraftItem[i].item_image = IMAGEMANAGER->findImage("아이템제작");
		}
		_vCraftItem[i].rc = RectMake(250 + i % 6 * 50, 130 + i / 6 * 40, 40, 40);

		// 렉트 초기화 및 이미지 초기화 ~


		if(PtInRect(&_vCraftItem[i].rc, _ptMouse))
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				if (i == 0 || i == 6) // 상자인경우
				{
					for (int i = 0; i < _inven->getvInven().size(); i++)
					{
						if (_inven->getvInven()[i].item_kind == ITEM_DEBRIS && _inven->getvInven()[i].indexX == 6 && _inven->getvInven()[i].indexY == 2)
						{
							if (_inven->getvInven()[i].amount == 10)
							{
								tagItem box;
								box.item_image = IMAGEMANAGER->findImage("아이템");
								box.indexX = 0;
								box.indexY = 0;
								box.item_kind = ITEM_BOX;
								
								_inven->setMouseItem(box);
								_inven->setInvenItemAmount(i, _inven->getvInven()[i].amount - 10);
							}
						}
					}
				}

				else if (i == 1 || i == 7) // 뭐더라?
				{

				}

				else if (i == 2 || i == 8) // 양봉장
				{

				}
				else if (i == 3 || i == 9) //허수아비
				{

				}
				else if (i == 4 || i == 10) //용광로
				{

				}
				else if (i == 5 || i == 11)//발효통
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
	// IMAGEMANAGER->frameRender("아이템제작", hdc, 225, 30);
	for (int i = 0; i < _vCraftItem.size(); i++)
	{
		if (_vCraftItem[i].item_image != NULL)
		{
			
			_vCraftItem[i].item_image->frameRender(hdc, _vCraftItem[i].rc.left, _vCraftItem[i].rc.top, _vCraftItem[i].indexX, _vCraftItem[i].indexY);

		}
		//Rectangle(hdc, _vCraftItem[i].rc); 
	}
	
}
