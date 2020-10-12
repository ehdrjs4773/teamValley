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
	
	BOOL _isInventoryMove; //�κ��丮 Ű�� �������̰� �ϴ°�.
	BOOL _isInvenPage;	   //������ �κ�������
	BOOL _isCraftPage;	   //������ ����������
	BOOL _isPlayerPage;	   //������ �÷��̾�������

	RECT _playerTool[12];

	int MouseIndexX, MouseIndexY;
	int currentSlotNumber;

	bool _isShopOpen;

public:
	void init();
	void release();
	void update();
	void render(HDC hdc);
	void invenToryRender(HDC hdc);
	void quickSlot(HDC hdc);
	void _vItemUpdate();
	void renderStorageInventory(HDC hdc);

	void shopInvenRender(HDC hdc);

	bool isShowTemp;
	bool isShowStorageTemp;

	void isShopOpen(bool isOpen) { _isShopOpen = isOpen; }

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


	bool getIsShowTemp() { return isShowTemp; }
	void setIsShowTemp(bool setIsShowTemp) { isShowTemp = setIsShowTemp; }


	//====�κ��丮 ���� ������ ���� ====//
	BOOL getPlayerPage() { return _isPlayerPage; }
	void setPlayerPage(bool click) { _isPlayerPage = click; }
	BOOL getCraftPage() { return _isCraftPage; }
	void setCraftPage(bool click) { _isCraftPage = click; }
	BOOL getInvenPage() { return _isInvenPage; }
	void setInvenPage(bool click) { _isInvenPage = click; }
	


};

