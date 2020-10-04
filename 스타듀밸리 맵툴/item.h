#pragma once
#include "stdafx.h"
#include "gameNode.h"

enum ITEM
{
	WEAPON,
	TOOL,
	BIGCRAFTABLE,
	RESOURCE,
	FORAGE,
	ENDITEM
};

struct tagItem {

	RECT rc;
	image *item_image;
	ITEM item_kind;
	const char* item_info;
	int buy_price;
	int sell_price;
};

class item :
	public gameNode
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
