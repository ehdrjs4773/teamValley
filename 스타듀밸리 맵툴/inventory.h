#pragma once
#define INVENMAX 36

class inventory 
{
private:
	image *inventory_img;
	
	vector<tagItem> _vItem;
	tagItem _MouseItem;

	RECT _playerInventory;
	
	BOOL _isInventoryMove; //인벤토리 키면 못움직이게 하는거.

	RECT _playerTool[12];

	int MouseIndexX, MouseIndexY;
	int currentSlotNumber;

public:
	void init();
	void release();
	void update();
	void render(HDC hdc);
	void quickSlot(HDC hdc);
	void craftObject();
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
	void setInvenItemAmount(int i, int amount) { _vItem[i].amount = amount; }
	vector<tagItem>* getInven() { return &_vItem; }
	tagItem* getInven(int a) { return &_vItem[a]; }
	tagItem getMoveItem() { return _MouseItem; }
	void setMouseItem(tagItem item) { _MouseItem = item; }

	void setInvenToryMove(bool move) { _isInventoryMove = move; }
	bool getInvenToryMove() { return _isInventoryMove; }

};

