#pragma once


class inventory;

class inventoryCraft
{
public:

	inventory* _inven;
	
	tagItem _CraftItem;
	vector<tagItem> _vCraftItem;

	tagItem _CraftEventItem;
	vector<tagItem> _vCraftEventItem;

	RECT goodsInProgress;

	int initCount = 0;

	int _isWood;
	int _isRock;
	int _isIron;
	int _isCopper;
	int _isGold;
	INT _isTomato;

	bool _isTemp3;
	bool _isTemp4;
	bool isadded = false;

public :
	void init();
	void update();
	void release();
	void render(HDC hdc);
	void craftInven_item_info(HDC hdc);
	void craftEventInven_item_info(HDC hdc);
	void blastFurnace();
	void materialUpdate();


	void setInventoryAddress(inventory* inven) { _inven = inven; }
};

