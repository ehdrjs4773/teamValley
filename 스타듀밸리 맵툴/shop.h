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

	//�÷��̾� �κ��丮 ������ ��Ʈ
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

	//�Ǹ�â ���� �κ�
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
	
	//���� �� �κ�
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

	//������ �ȱ� - ���콺 ������ Ŭ��
	void sell();
	
	//������ ���� - ���콺 ���� Ŭ��
	void buy();

	//���� ��ũ�� �� ��ư Ŭ��
	void shop_scroll();

};

