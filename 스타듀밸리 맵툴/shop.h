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
	NPC_KIND _npcKind;

	int shopLevel;
	int total_sell;

	bool buyFail;
	int buy_count;

	//플레이어 인벤토리 렌더용 렉트
	RECT playerItem[INVENMAX];
	int money;
	bool _isClose;
	RECT rc_exit;

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

	//판매창 관련 부분
	bool sell_ispopup;
	bool sell_isok;
	RECT sell_popup;
	RECT sell_ok;
	RECT sell_cancel;
	RECT sell_plus;
	RECT sell_minus;
	RECT sell_max;
	RECT sell_min;
	image* sell_item_img;
	
	int sell_amount;
	int sell_amount_max;
	int sell_index;
	int sell_item_frameX, sell_item_frameY;
	//
	
	//상점 텝 부분
	RECT tab[2];
	bool tab_sel;
	vector<tagItem> _vSeed;
	vector<tagItem> _vTool;

	HBRUSH brush;
	HBRUSH oBrush;

	vector<SLOT> _vslot;
	typedef vector<tagItem>::iterator vi_SLOT;
	vi_SLOT _viSlot;

	vector<tagItem> _vItem;
	typedef vector<tagItem>::iterator vi_ITEM;
	vi_ITEM _viItem;
	vector<tagItem>* _vInven;

public:

	HRESULT init(NPC_KIND npckind);
	void release();
	void update();
	void render();

	bool shopClose() { return _isClose; }

	//아이템 팔기 - 마우스 오른쪽 클릭
	void sell();
	
	//아이템 구매 - 마우스 왼쪽 클릭
	void buy();

	//상점 스크롤 및 버튼 클릭
	void shop_scroll();

};

