#pragma once
#define INVENMAX 36
#define STORAGEMAX 36
#include "inventoryCraft.h"
class inventory 
{
private:
	image *inventory_img;
	image *inventory2_img;
	image *playerStorage_img;
	inventoryCraft* _inventoryCraft;
	vector<tagItem> _vItem;
	tagItem _MouseItem;

	vector<tagItem> _vStorageItem;
	tagItem _MouseStorageItem;

	RECT _playerInventory;
	RECT _kettleBar;
	RECT _closeButton;

	HBRUSH brush;
	HBRUSH oBrush;
	
	BOOL _isInventoryMove; //인벤토리 키면 못움직이게 하는거.
	BOOL _isInvenPage;	   //누르면 인벤페이지
	RECT _isInvenRect;	   //인벤 렉트
	BOOL _isCraftPage;	   //누르면 제작페이지
	RECT _isCraftRect;     //제작 렉트
	BOOL _isPlayerPage;	   //누르면 플레이어페이지
	RECT _isPlayerRect;    //스킬렉트
	RECT _quickSlotRect;   //퀵슬롯 이미지렉트
	RECT _exitRect;		   //나가기 버튼

	RECT _playerTool[12];

	RECT _warningRC;
	RECT _waring_yes;
	RECT _waring_no;

	int MouseIndexX, MouseIndexY;
	int currentSlotNumber;
	int currentSkillNumber;
	int waterAmount;

	bool _isShopOpen;
	bool _isShowCloseButton;
	bool _isWarning;
	bool _isExit;
public:
	void init();
	void release();
	void update();
	void render(HDC hdc);
	void invenToryRender(HDC hdc);
	void quickSlot(HDC hdc);
	void quickSkillSlot(HDC hdc);

	void _vItemUpdate();
	void renderStorageInventory(HDC hdc);
	void inven_item_info(HDC hdc);
	void quickinven_item_info(HDC hdc);
	void storage_item_info(HDC hdc);

	void shopInvenRender(HDC hdc);
	bool getIsWarning() { return _isWarning; }
	void setIsWarning(bool _is) {_isWarning = _is; }

	bool isShowTemp;
	bool isShowStorageTemp;

	void isShopOpen(bool isOpen) { _isShopOpen = isOpen; }
	bool getshopOpen() { return _isShopOpen; }
	int getCurrentSlotNumber() { return currentSlotNumber; }
	int getCurrentSKillNumber() { return currentSkillNumber; }
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

	

	void setInvenItem(int i, tagItem item);
	void setInvenItemAmount(int i, int amount) { _vItem[i].amount = amount; }
	void setInvenResetImage(int i) { _vItem[i].item_image = nullptr; }
	vector<tagItem>* getInven() { return &_vItem; }
	vector<tagItem> getvInven() { return _vItem; }
	vector<tagItem> getVBoxInven() { return _vStorageItem; }
	void setvInven(int i, tagSaveItem item);
	void setvBoxInven(int i, tagItem item);
	void setInven(vector<tagItem> temp) { _vItem = temp; }

	tagItem* getInven(int a) { return &_vItem[a]; }
	tagItem getMoveItem() { return _MouseItem; }
	RECT getPlayerTool(int i ) { return _playerTool[i]; }
	RECT getqucikRect() { return _quickSlotRect; }

	RECT getKettleBar() { return _kettleBar; }
	
	void setMouseItem(tagItem item) { _MouseItem = item; }

	void setInvenToryMove(bool move) { _isInventoryMove = move; }
	bool getInvenToryMove() { return _isInventoryMove; }


	bool getIsShowTemp() { return isShowTemp; }
	void setIsShowTemp(bool setIsShowTemp) { isShowTemp = setIsShowTemp; }

	RECT getCloseButton() { return _closeButton; }

	int getWaterAmount() { return waterAmount; }
	void setWaterAmount(int setWaterAmount) { waterAmount = setWaterAmount; }

	inventoryCraft* getInventoryCraft() { return _inventoryCraft; }


	//====인벤토리 위에 페이지 설정 ====//
	BOOL getPlayerPage() { return _isPlayerPage; }
	void setPlayerPage(bool click) { _isPlayerPage = click; }
	BOOL getCraftPage() { return _isCraftPage; }
	void setCraftPage(bool click) { _isCraftPage = click; }
	BOOL getInvenPage() { return _isInvenPage; }
	void setInvenPage(bool click) { _isInvenPage = click; }
	


};

