#pragma once
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
	void setCurrentSlotNumber(int a)
	{ 
		if (a < 0)
		{
			currentSlotNumber = 11;
		}
		else if (a > 11)
		{
			currentSlotNumber = 0;
		}
		else
		{
			currentSlotNumber = a;
		}
	}

	void setInvenItem(int i, tagItem item) { _vItem[i] = item; }
	vector<tagItem>* getInven() { return &_vItem; }
	tagItem* getInven(int a) { return &_vItem[a]; }
};

