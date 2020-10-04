#include "stdafx.h"
#include "shop.h"

WPARAM shop::wparam;

HRESULT shop::init()
{
	_item = new item;
	_item->init();
	
	_inven = new inventory;
	_inven->init();

	is_click = false;
	click_index = 0;

	_vItem = _item->getItem();

	_vInven = _inven->getInven();

	_shop_image = IMAGEMANAGER->addImage("상점", "Images/shop.bmp", 900, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점슬롯", "Images/shop_itemslot.bmp", 875, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점슬롯클릭", "Images/shop_itemslot_click.bmp", 875, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("업버튼", "Images/shop/up_BT.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("다운버튼", "Images/shop/down_BT.bmp", 50, 50, true, RGB(255, 0, 255));


	current_index = 0;
	down_BT = RectMake(1100, 500, 50, 50);
	up_BT = RectMake(1100, 50, 50, 50);
	rc_scroll = RectMake(up_BT.left+15, up_BT.bottom + 10, 19, 38);

	scroll_img = IMAGEMANAGER->addImage("스크롤","Images/shop/scroll.bmp", (float)up_BT.left, (float)up_BT.bottom+10, 19, 38);
	scrollbar_img = IMAGEMANAGER->addImage("스크롤바","Images/shop/scrollbar.bmp", (float)up_BT.left, (float)up_BT.bottom + 10, 19, 380);
	
	//상점 사이즈
	rc_shop = RectMake(100, 50, 900, 320);
	
	//초기 슬롯

	for (int i = 0; i < 4; i++)
	{
		SLOT slot;
		slot.rc = RectMake(rc_shop.left+15, 60 + (70*i), 875, 70);
		slot.slot_image = IMAGEMANAGER->findImage("상점슬롯");
		slot.on_cursor = false;
		_vslot.push_back(slot);
	}

	//아이템 초기화
	//tagItem 
	for (int i = 0; i < _vslot.size(); i++)
	{
		_vItem[i].rc = RectMake(_vslot[i].rc.left + 16, _vslot[i].rc.top + 13, 55, 45);
	}
	return S_OK;
}

void shop::release()
{

}

void shop::update()
{
	sell();
	buy();
	shop_scroll();

}

void shop::render()
{
	//상점 인벤토리 출력
	_inven->render(getMemDC());

	//마우스 좌표 출력
	char temp[256];
	sprintf(temp, "x : %d", _ptMouse.x);
	TextOut(getMemDC(), 25, 125, temp, strlen(temp));
	sprintf(temp, "y : %d", _ptMouse.y);
	TextOut(getMemDC(), 25, 150, temp, strlen(temp));
	
	//상점 창 테두리 출력
	_shop_image->render(getMemDC(), rc_shop.left, rc_shop.top);

	//상점 슬롯 출력
	for (int i = 0; i < _vslot.size(); i++)
	{
		if (!_vslot[i].on_cursor)
		{
			_vslot[i].slot_image = IMAGEMANAGER->findImage("상점슬롯");
			_vslot[i].slot_image->render(getMemDC(), _vslot[i].rc.left, _vslot[i].rc.top);
		}
		else
		{
			_vslot[i].slot_image = IMAGEMANAGER->findImage("상점슬롯클릭");
			_vslot[i].slot_image->render(getMemDC(), _vslot[i].rc.left, _vslot[i].rc.top);
		}
	}

	//아이템 이미지와 정보 출력
	for (int i = 0; i < _vslot.size(); i++)
	{
		_vItem[i+current_index].item_image->render(getMemDC(), _vslot[i].rc.left+16, _vslot[i].rc.top+13);
		if (_vslot[i].on_cursor)
		{
			RECT temp1 = RectMake(_ptMouse.x + 25, _ptMouse.y + 25, 200, 100);
			RECT temp2 = RectMake(temp1.left, temp1.bottom, 200, 100);

			Rectangle(getMemDC(), temp1);
			Rectangle(getMemDC(), temp2);

			SetTextColor(getMemDC(), RGB(0, 0, 0));
			
			char temp[256];

			switch (_vItem[i + current_index].item_kind)
			{
			case WEAPON:
				memset(temp, 0, sizeof(temp));
				sprintf(temp, "WEAPON", sizeof("WEAPON"));
				break;
			case TOOL:

				memset(temp, 0, sizeof(temp));
				sprintf(temp, "TOOL", sizeof("TOOL"));
				break;
			case BIGCRAFTABLE:

				memset(temp, 0, sizeof(temp));
				sprintf(temp, "BIGCRAFTABLE", sizeof("BIGCRAFTABLE"));
				break;
			case RESOURCE:

				memset(temp, 0, sizeof(temp));
				sprintf(temp, "RESOURCE", sizeof("RESOURCE"));
				break;
			case FORAGE:
				memset(temp, 0, sizeof(temp));
				sprintf(temp, "FORAGE", sizeof("FORAGE"));
				break;
			}

			DrawText(getMemDC(), temp, strlen(temp), &temp1, NULL);
			DrawText(getMemDC(), _vItem[i + current_index].item_info, strlen(_vItem[i + current_index].item_info), &temp2, NULL);
		}

	}
	IMAGEMANAGER->findImage("업버튼")->render(getMemDC(), up_BT.left, up_BT.top);
	IMAGEMANAGER->findImage("다운버튼")->render(getMemDC(), down_BT.left, down_BT.top);
	//Rectangle(getMemDC(), up_BT);
	//Rectangle(getMemDC(), down_BT);
	scrollbar_img->render(getMemDC(),up_BT.left+15, up_BT.bottom+10);
	//Rectangle(getMemDC(),rc_scroll);
	scroll_img->render(getMemDC(),rc_scroll.left, rc_scroll.top);

	if (is_click)
	{
		_vItem[click_index].item_image->render(getMemDC(), _ptMouse.x, _ptMouse.y);
	}


}

void shop::sell()
{
	for (int i = 0; i < INVENMAX; i++)
	{
		if (PtInRect(&(*_vInven)[i].rc, _ptMouse))
		{
			if (INPUT->GetKeyDown(VK_RBUTTON))
			{
				(*_vInven)[i].buy_price = NULL;
				(*_vInven)[i].item_image = NULL;
				(*_vInven)[i].item_info = NULL;
				(*_vInven)[i].item_kind = ENDITEM;
				(*_vInven)[i].sell_price = NULL;
			}
		}
	}

}

void shop::buy()
{
	for (int i = 0; i < _vslot.size(); i++)
	{
		if (PtInRect(&_vslot[i].rc, _ptMouse))
		{
			_vslot[i].on_cursor = true;
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				is_click = true;
				click_index = i + current_index;
			}
		}
		else _vslot[i].on_cursor = false;
	}

	for (int i = 0; i < INVENMAX; i++)
	{
		if (PtInRect(&(*_vInven)[i].rc, _ptMouse))
		{
			if (is_click)
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					(*_vInven)[i].buy_price = _vItem[click_index].buy_price;
					(*_vInven)[i].item_image = _vItem[click_index].item_image;
					(*_vInven)[i].item_info = _vItem[click_index].item_info;
					(*_vInven)[i].item_kind = _vItem[click_index].item_kind;
					(*_vInven)[i].sell_price = _vItem[click_index].sell_price;
				}
			}
		}
	}
}

void shop::shop_scroll()
{
	//스크롤 위방향 버튼
	if (PtInRect(&up_BT, _ptMouse))
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			current_index--;
			cout << current_index << endl;

			if (current_index < 0) current_index = 0;
			rc_scroll.top = (up_BT.bottom + 10) + ((float)current_index / (float)(_vItem.size() - _vslot.size())) * (float)342;
			rc_scroll.bottom = rc_scroll.top + 38;
		}
	}
	//스크롤 아래방향 버튼
	if (PtInRect(&down_BT, _ptMouse))
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			cout << current_index << endl;
			current_index++;
			cout << current_index << endl;

			if (current_index > _vItem.size() - _vslot.size()) current_index = _vItem.size() - _vslot.size();

			rc_scroll.top = (up_BT.bottom + 10) + ((float)current_index / (float)(_vItem.size() - _vslot.size())) * (float)342;
			rc_scroll.bottom = rc_scroll.top + 38;
		}
	}

	//스크롤 누르고 이동
	if (PtInRect(&rc_scroll, _ptMouse))
	{
		static int save_point = 0;
		static int change = 0;
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			save_point = _ptMouse.y;
		}
		if (INPUT->GetKey(VK_LBUTTON))
		{
			//change = _ptMouse.y - save_point;
			rc_scroll.top = _ptMouse.y - 20;
			rc_scroll.bottom = _ptMouse.y + 19;
			if (rc_scroll.top <= up_BT.bottom + 10)
			{
				rc_scroll.top = up_BT.bottom + 10;
				rc_scroll.bottom = rc_scroll.top + 38;
			}
			if (rc_scroll.bottom >= down_BT.top - 10)
			{
				rc_scroll.bottom = down_BT.top - 10;
				rc_scroll.top = rc_scroll.bottom - 38;
			}
		}

		//스크롤 계산
		float result = (float)(((float)rc_scroll.top - (float)up_BT.bottom + 10) / (float)342 * (float)(_vItem.size() - _vslot.size()));
		current_index = result;
	}
}

