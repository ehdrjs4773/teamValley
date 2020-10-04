#pragma once
#include "item.h"
#define INVENMAX 36

class inventory 
{
private:
	image *inventory_img;
	
	vector<tagItem> _vItem;

	RECT _playerInventory;

	RECT _playerTool[12];

	int MouseIndexX, MouseIndexY;
	int currentSlotNumber;

public:
	void init();
	void release();
	void update();
	void render(HDC hdc);
	void quickSlot(HDC hdc);

	int getCurrentSlotNumber() { return currentSlotNumber; }
	tagItem* getInven(int a) { return &_vItem[a]; }
	vector<tagItem>* getInven() { return &_vItem; }
};

