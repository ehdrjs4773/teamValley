#pragma once
#include "singletonBase.h"
#include "tileNode.h"
#include "inventory.h"
#include "Stock.h"

class player : public singletonBase<player>
{
private:
	RECT rc;
	RECT frontHpBar;
	RECT playerInven;
	RECT playerHoldItem;

	Stock* stock;
	MAP currentMap;

	int timeCount, hour, minute, date, money, year, blinkCount;
	int arrowAngle;
	DAYOFWEEK day;
	SEASON currentSeason;
	WEATHER currentWeather;
	float darkAlpha;

	float centerX, centerY;
	int currentX, currentY;
	int MouseIndexX, MouseIndexY;
	float speed;
	int count;
	int index;
	int playerHp;
	int hpBarX;
	int axDamage, pickaxDamage, hoeDamage;

	int boxCount;
	int boxIndex;
	bool isOpenPlayerInvenCover;

	bool isShowInventory;

	bool isOpenPlayerStorageCover;

	HBRUSH brush;		
	HBRUSH oBrush;

	STATE _pState;
	DIRECTION _pDirection;
	TOOL _pTool;
	
	image* move;
	image* state;
	image* backHpBar;
	image* playerStorage;
	image* _cutdownTree;

	inventory* _inventory;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void playerStatusRender(HDC hdc);
	void InventoryRender(HDC hdc);
	void hpBarRender(HDC hdc);
	void clockRender(HDC hdc);
	void moneyRender(HDC hdc);
	void arrowRender(HDC hdc);
	void weatherRender(HDC hdc);

	void setIndex(int inx) { index = inx; }
	float getSpeed() { return speed; }
	float getCenterX() { return centerX; }
	void setCenterX(float cX) { centerX = cX; }
	float getCenterY() { return centerY; }
	void setCenterY(float cY) { centerY = cY; }

	inventory* getInventory() { return _inventory; }
	bool getInventoryMove() { return _inventory->getInvenToryMove(); }
	int getCurrentSlotNumber() { return _inventory->getCurrentSlotNumber(); }
	void setCurrentSlotNumber(int a) { _inventory->setCurrentSlotNumber(a); }
	vector<tagItem>* getInven() { return _inventory->getInven(); }
	inventory* getPlayerInven() { return _inventory; }
	tagItem* getInven(int a) { return _inventory->getInven(a); }
	tagItem* getCurrentInven() { return _inventory->getInven(_inventory->getCurrentSlotNumber()); }
	void setInvenItem(int i, tagItem item) { _inventory->setInvenItem(i, item); }
	void setInvenItemAmount(int i, int amount) { _inventory->setInvenItemAmount(i, amount); }

	bool getIsShowInventory() { return isShowInventory; }
	bool getIsOpenStorageCover() { return isOpenPlayerStorageCover; }
	void setIsOpenStorageCover(bool SetIsOpenStorageCover) { isOpenPlayerStorageCover=SetIsOpenStorageCover; }

	int getCurrentX() { return currentX; }
	int getCurrentY() { return currentY; }

	int getHpBarX() { return frontHpBar.top; }
	int getAxDamage() { return axDamage; }
	int getPickaxDamage() { return pickaxDamage; }
	int getHoeDamage() { return hoeDamage; }
	void setHpBarX(int hpbar) { frontHpBar.top = hpbar; }

	int getWaterAmount() { return _inventory->getWaterAmount(); }
	void setWaterAmount(int waterAmount) { _inventory->setWaterAmount(waterAmount); }



	DIRECTION getDirection() { return _pDirection; }
	void setDirection(DIRECTION dir) { _pDirection = dir; }
	RECT getRc() { return rc; }

	STATE getState() { return _pState; }
	void setState(STATE state) {
		if (state != RUN && state!=CARRY)
		{
			index = 0;
		}
		_pState = state;
	}

	void playerAnimation();
	void playerRender();
	void playerInvenAnimation();
	void playerInvenCoverAnimation();
	void openPlayerInvenCover();
	void openPlayerStorageCover();
	void playerCarryItem(HDC hdc);

	void setCurrentMap();

	void countTime();
	void resetClock();
	
	SEASON getSeason() { return currentSeason; }
	WEATHER getWeather() { return currentWeather; }
	int getHour() { return hour; }
	int getMinute() { return minute; }
	void setMoney(int Item_money) { money = Item_money; }
	int getMoney() { return money; }
	int getDate() { return date; }
	DAYOFWEEK getDay() { return day; }

	player getPlayerData();
	void setPlayerData();
};

