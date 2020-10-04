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


enum SEED
{
	SEED_NONE,
	SEED_PASNIP,
	SEED_CABBAGE,
	SEED_ONION,
	SEED_CARROT,
	SEED_TOMATO,
	SEED_CHILLI,
	SEED_RADISH,
	SEED_STARFRUIT,
	SEED_EGGPLANT,
	SEED_PUMPKIN,
	SEED_TARO,
	SEED_BEET,
	SEED_BULEBERRY,
	SEED_TULIP,
	SEED_MIN,
	SEED_SUNFLOWER,
	SEED_PEPPER,
	SEED_STRAWBERRY,
	SEED_GRAPE,
	SEED_COFFEEBEAN,
	SEED_BEAN,
	SEED_POTATO,
	SEED_GREEN1,
	SEED_MELON,
	SEED_WHEAT,
	SEED_REDCABBAGE,
	SEED_CORN,
	SEED_SPINICH,
	SEED_CHUNG,
	SEED_RASBERRY,
	SEED_BLUEFLOWER,
	SEED_YELLOWFLOWER,
	SEED_PINKFLOWER,
	SEED_GREENGRAPE,
	SEED_PURPLEWHEAT,
	SEED_CATUS

};

struct tagItem {

	RECT rc;
	image *item_image;
	ITEM item_kind;
	SEED seedKind;
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
