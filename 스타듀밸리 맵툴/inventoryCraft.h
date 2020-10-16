#pragma once


class inventory;

class inventoryCraft
{
public:

	inventory* _inven;
	
	tagItem _CraftItem;
	vector<tagItem> _vCraftItem;

public :
	void init();
	void update();
	void release();
	void render(HDC hdc);


	void setInventoryAddress(inventory* inven) { _inven = inven; }
};

