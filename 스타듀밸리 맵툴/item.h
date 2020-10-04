#pragma once
#include "stdafx.h"

enum ITEM
{
	ITEM_WEAPON,
	ITEM_TOOL,
	ITEM_BIGCRAFTABLE,
	ITEM_RESOURCE,
	ITEM_FORAGE,
	ITEM_ENDITEM,
	ITEM_SEED
};



struct tagItem {

	RECT rc;
	image *item_image;
	ITEM item_kind;
	const char* item_info;
	int buy_price;
	int sell_price;
	int indexX, indexY;
};

class item 
{
private:
	
	vector<tagItem> _vItem;
public:
	
	HRESULT init();
	void release();
	void update();
	void render();

	vector<tagItem> getItem() { return _vItem; }
};
