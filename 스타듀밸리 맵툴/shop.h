#pragma once
#include "gameNode.h"
#include "inventory.h"


struct SLOT {

	RECT rc;
	image* slot_image;
	bool on_cursor;
};

class shop :
	public gameNode
{
private:

	inventory *_inven;
	bool is_click;
	int click_index;

	RECT rc_scroll;
	image *scroll_img;
	image *scrollbar_img;

	RECT down_BT;
	RECT up_BT;
	int current_index;
	RECT rc_shop;
	image *_shop_image;

	vector<SLOT> _vslot;
	typedef vector<tagItem>::iterator vi_SLOT;
	vi_SLOT _viSlot;

	vector<tagItem> _vItem;
	typedef vector<tagItem>::iterator vi_ITEM;
	vi_ITEM _viItem;

	vector<tagItem> _vInven;

public:

	HRESULT init();
	void release();
	void update();
	void render();
	//아이템 팔기 - 마우스 오른쪽 클릭
	void sell();
	
	//아이템 구매 - 마우스 왼쪽 클릭
	void buy();

	//상점 스크롤 및 버튼 클릭
	void shop_scroll();

};

