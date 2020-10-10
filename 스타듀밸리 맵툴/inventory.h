#pragma once
#define INVENMAX 36
#define STORAGEMAX 36

class inventory 
{
private:
	image *inventory_img;
	image *inventory2_img;
	image *playerStorage_img;
	
	vector<tagItem> _vItem;
	tagItem _MouseItem;

	vector<tagItem> _vStorageItem;
	tagItem _MouseStorageItem;

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
	void _vItemUpdate();
	void renderSellingInventory(HDC hdc);
	void renderStorageInventory(HDC hdc);

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

	void setInvenToryMove(bool move) { _isInventoryMove = move; }
	bool getInvenToryMove() { return _isInventoryMove; }

};

