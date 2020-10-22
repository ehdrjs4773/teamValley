#pragma once


class inventory;

class inventoryCraft
{
public:

	inventory* _inven;
	
	tagItem _CraftItem;
	vector<tagItem> _vCraftItem;

	int initCount = 0;

	int _isWood;
	int _isRock;
	int _isIron;
	int _isCopper;

	bool _isTemp3;
	bool _isTemp4;

public :
	void init();
	void update();
	void release();
	void render(HDC hdc);
	void craftInven_item_info(HDC hdc);


	void setInventoryAddress(inventory* inven) { _inven = inven; }
};

