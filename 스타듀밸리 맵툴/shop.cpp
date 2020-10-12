#include "stdafx.h"
#include "shop.h"

HRESULT shop::init()
{
	_inven = new inventory;
	_inven = PLAYER->getPlayerInven();

	is_click = false;
	click_index = 0;

	_isClose = false;

	_vItem = ITEMMANAGER->getItem();
	_vInven = _inven->getInven();

	current_index = 0;
	down_BT = RectMake(1100, 500, 50, 50);
	up_BT = RectMake(1100, 50, 50, 50);
	rc_scroll = RectMake(up_BT.left+15, up_BT.bottom + 10, 19, 38);

	scroll_img = IMAGEMANAGER->addImage("스크롤","Images/shop/scroll.bmp", (float)up_BT.left, (float)up_BT.bottom+10, 19, 38);
	scrollbar_img = IMAGEMANAGER->addImage("스크롤바","Images/shop/scrollbar.bmp", (float)up_BT.left, (float)up_BT.bottom + 10, 19, 380);
	
	//상점 사이즈
	rc_shop = RectMake(100, 50, 900, 320);
	rc_exit = RectMake(980, 40, 30, 33);
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

	//플레이어 인벤토리 렌더용 렉트 초기화
	for (int i = 0; i < INVENMAX; i++)
	{
		playerItem[i] = RectMake(296 + 46 * (i % 12), 394 + 50 * (i / 12), 40, 40);
	}

	return S_OK;
}

void shop::release()
{
	SAFE_DELETE(_inven);
}

void shop::update()
{
	_inven->update();
	sell();
	buy();
	shop_scroll();
	if (PtInRect(&rc_exit, _ptMouse))
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			_isClose = true;
		}
	}
	else _isClose = false;

}

void shop::render()
{//플레이어 인벤토리 출력

	PLAYER->getInventory()->shopInvenRender(getMemDC());

	for (int i = 0; i < _vInven->size(); i++)
	{
		if (_vInven->at(i).item_image == NULL) continue;
		_vInven->at(i).item_image->frameRender(getMemDC(), playerItem[i].left, playerItem[i].top, _vInven->at(i).indexX, _vInven->at(i).indexY);
	}

	//마우스 좌표 출력
	char temp[256];
	sprintf(temp, "x : %d", _ptMouse.x);
	TextOut(getMemDC(), 25, 125, temp, strlen(temp));
	sprintf(temp, "y : %d", _ptMouse.y);
	TextOut(getMemDC(), 25, 150, temp, strlen(temp));

	//상점 창 테두리 출력
	_shop_image = IMAGEMANAGER->findImage("상점");
	_shop_image->render(getMemDC(), rc_shop.left, rc_shop.top);

	//상점 슬롯 출력
	for (int i = 0; i < _vslot.size(); i++)
	{
		//아이템 이름, 돈 출력
		RECT rc_name = RectMake(_vslot[i].rc.left + 90, _vslot[i].rc.top+25, 150, 50);
		RECT rc_money = RectMake(_vslot[i].rc.left + 790, _vslot[i].rc.top+25, 150, 50);
		char name[256];
		char money[256];
		memset(name, 0, sizeof(name));
		memset(money, 0, sizeof(money));
		sprintf(name, _vItem[i + current_index].item_info, sizeof(_vItem[i + current_index].item_info));
		sprintf(money, "%d", _vItem[i + current_index].buy_price);
		
		SetTextColor(getMemDC(), RGB(0, 0, 0));

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
		DrawText(getMemDC(), name, strlen(name), &rc_name, NULL);
		DrawText(getMemDC(), money, strlen(money), &rc_money, NULL);

	}
	IMAGEMANAGER->findImage("상점닫기")->render(getMemDC(), rc_exit.left, rc_exit.top);

	//아이템 이미지와 정보 출력
	for (int i = 0; i < _vslot.size(); i++)
	{
		if (_vItem[i + current_index].isFrame)
		{
			_vItem[i + current_index].item_image->frameRender(getMemDC(), _vslot[i].rc.left + 23, _vslot[i].rc.top + 15, _vItem[i + current_index].indexX, _vItem[i + current_index].indexY);
		}
		else
		{
			_vItem[i + current_index].item_image->render(getMemDC(), _vslot[i].rc.left + 16, _vslot[i].rc.top + 13);
		}

		if (_vslot[i].on_cursor)
		{
			RECT temp1 = RectMake(_ptMouse.x + 35, _ptMouse.y + 45, 200, 50);
			RECT temp2 = RectMake(temp1.left, temp1.bottom, 200, 100);
			IMAGEMANAGER->findImage("아이템정보")->render(getMemDC(), _ptMouse.x + 25, _ptMouse.y + 25);

			SetTextColor(getMemDC(), RGB(0, 0, 0));

			char temp[256];

			switch (_vItem[i + current_index].item_kind)
			{
			case ITEM_WEAPON:
				memset(temp, 0, sizeof(temp));
				sprintf(temp, "WEAPON", sizeof("WEAPON"));
				break;
			case ITEM_TOOL:

				memset(temp, 0, sizeof(temp));
				sprintf(temp, "TOOL", sizeof("TOOL"));
				break;
			case ITEM_BIGCRAFTABLE:

				memset(temp, 0, sizeof(temp));
				sprintf(temp, "BIGCRAFTABLE", sizeof("BIGCRAFTABLE"));
				break;
			case ITEM_RESOURCE:

				memset(temp, 0, sizeof(temp));
				sprintf(temp, "RESOURCE", sizeof("RESOURCE"));
				break;
			case ITEM_FORAGE:
				memset(temp, 0, sizeof(temp));
				sprintf(temp, "FORAGE", sizeof("FORAGE"));
				break;
			case ITEM_SEED:
				memset(temp, 0, sizeof(temp));
				sprintf(temp, "SEED", sizeof("SEED"));
			case 	ITEM_FRUIT:
				memset(temp, 0, sizeof(temp));
				sprintf(temp, "FRUIT", sizeof("FRUIT"));
				break;
			case ITEM_DEBRIS :
				memset(temp, 0, sizeof(temp));
				sprintf(temp, "DEBRIS", sizeof("DEBRIS"));
				break;
			case ITEM_WOODENFENCE :
				memset(temp, 0, sizeof(temp));
				sprintf(temp, "WOODENFENCE", sizeof("WOODENFENCE"));
				break;
			case ITEM_STONEFENCE : 
				memset(temp, 0, sizeof(temp));
				sprintf(temp, "STONEFENCE", sizeof("STONEFENCE"));
				break;
			case ITEM_WOODENFENCEDOOR:
				memset(temp, 0, sizeof(temp));
				sprintf(temp, "STONEFENCE DOOR", sizeof("STONEFENCE DOOR"));
				break;
			case ITEM_STONEFENCEDOOR:
				memset(temp, 0, sizeof(temp));
				sprintf(temp, "STONEFENCE DOOR", sizeof("STONEFENCE DOOR"));
				break;

			}

			DrawText(getMemDC(), temp, strlen(temp), &temp1, NULL);
			DrawText(getMemDC(), _vItem[i + current_index].item_info, strlen(_vItem[i + current_index].item_info), &temp2, NULL);
		}

	}
	IMAGEMANAGER->findImage("업버튼")->render(getMemDC(), up_BT.left, up_BT.top);
	IMAGEMANAGER->findImage("다운버튼")->render(getMemDC(), down_BT.left, down_BT.top);

	scrollbar_img->render(getMemDC(), up_BT.left + 15, up_BT.bottom + 10);

	scroll_img->render(getMemDC(), rc_scroll.left, rc_scroll.top);

	if (is_click)
	{
		if (_vItem[click_index].isFrame)
		{
			_vItem[click_index].item_image->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _vItem[click_index].indexX, _vItem[click_index].indexY);
		}
		else
		{
			_vItem[click_index].item_image->render(getMemDC(), _ptMouse.x, _ptMouse.y);
		}
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
				(*_vInven)[i].item_kind = ITEM_ENDITEM;
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
		if (PtInRect(&PLAYER->getInven()->at(i).rc, _ptMouse))
		{	
			if ((*_vInven)[i].item_image == NULL)
			{
				if (is_click)
				{
					if (INPUT->GetKeyDown(VK_LBUTTON))
					{
						(*_vInven)[i].buy_price = _vItem[click_index].buy_price;
						(*_vInven)[i].item_image = _vItem[click_index].item_image;
						(*_vInven)[i].indexX = _vItem[click_index].indexX;
						(*_vInven)[i].indexY = _vItem[click_index].indexY;
						(*_vInven)[i].isFrame = _vItem[click_index].isFrame;
						(*_vInven)[i].item_info = _vItem[click_index].item_info;
						(*_vInven)[i].item_kind = _vItem[click_index].item_kind;
						(*_vInven)[i].sell_price = _vItem[click_index].sell_price;
						is_click = false;
					}
				}
			}
			else
			{
				continue;
			}
			
		}
	}
}

void shop::shop_scroll()
{
	//스크롤 누르고 이동
	if (PtInRect(&rc_scroll, _ptMouse))
	{
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
			float result = (float)((((float)rc_scroll.top - ((float)up_BT.bottom + 10)) / (float)342) * (float)(_vItem.size() - _vslot.size()));
			current_index = result;
		}
		//스크롤 계산
	}
	else
	{
		if (_mouseWheel == -1)
		{
			current_index++;
			if (current_index > _vItem.size() - _vslot.size()) current_index = _vItem.size() - _vslot.size();
			_mouseWheel = 0;
		}
		else if (_mouseWheel == 1)
		{
			current_index--;
			if (current_index < 0) current_index = 0;
			_mouseWheel = 0;
		}
		//스크롤 위방향 버튼
		if (PtInRect(&up_BT, _ptMouse))
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				current_index--;
				if (current_index < 0) current_index = 0;
			}
		}
		//스크롤 아래방향 버튼
		if (PtInRect(&down_BT, _ptMouse))
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				current_index++;
				if (current_index > _vItem.size() - _vslot.size()) current_index = _vItem.size() - _vslot.size();
			}
		}
		rc_scroll.top = (up_BT.bottom + 10) + ((float)current_index / (float)(_vItem.size() - _vslot.size())) * (float)342;
		rc_scroll.bottom = rc_scroll.top + 38;
	}
	/*if (_ptMouse.x >= rc_scroll.left && _ptMouse.x <= rc_scroll.right)
	{
		if (_ptMouse.y < rc_scroll.top)
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				current_index--;
			}
		}
		if (_ptMouse.y > rc_scroll.bottom)
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				current_index++;
			}
		}
	}*/
}

