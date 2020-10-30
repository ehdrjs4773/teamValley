#pragma once
#include "singletonBase.h"
#include "tileNode.h"
#include "inventory.h"
#include "Stock.h"
#include "skill.h"

class player : public singletonBase<player>
{
private:
	//인게임 맵 저장용 타일
	tagTile _tile[TILEY][TILEX];

	RECT rc;
	RECT frontEnergyBar;
	RECT frontHpBar;
	RECT playerInven;
	RECT playerHoldItem;

	skill* _skill;
	bool isSkill;

	Stock* stock;
	MAP currentMap;

	float MAXHP, MAXENERGY;
	float playerHp, playerEnergy;

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
	
	int totalHpDmg = 0;
	int totalEnergyDmg = 0;
	int hpBarX;
	int Damage;
	int aniCountControl = 10;
	int aniCountControl2 = 5;

	bool isShowInventory;

	bool isOpenPlayerStorageCover;

	HBRUSH brush;		
	HBRUSH oBrush;

	STATE _pState;
	DIRECTION _pDirection;
	TOOL _pTool;
	SKILL _pSkill;
	
	image* move;
	image* state;
	image* backHpBar;
	image* backEnergyBar;
	image* playerStorage;
	image* _cutdownTree;
	image* blackholeSword;
	image* explosionSword;
	image* fireballSword;
	image* fireSword;
	image* spikeSword;

	inventory* _inventory;

	bool isShowSleepingOption =false;
	bool isSprinkled;
	bool isNewGame = true;
	bool isHit;
	int hitCount = 0;
	int inGameLoadCount = 0;

	int playerFarmingLevel;
	int playerCombatLevel;
	int farmingExp;
	int MaxFarmingExp;
	int combatExp;
	int MaxCombatExp;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	bool getIsSprinkled() { return isSprinkled; }
	void setIsSprinkled(bool isSprink) { isSprinkled = isSprink; }
	void playerStatusRender(HDC hdc);
	void InventoryRender(HDC hdc);
	void energyBarRender(HDC hdc);
	void hpBarRender(HDC hdc);
	void clockRender(HDC hdc);
	void moneyRender(HDC hdc);
	void arrowRender(HDC hdc);
	void weatherRender(HDC hdc);

	void limitEnergy();
	void setMaxExp();
	void levelUp();

	bool getIsNewGame() { return isNewGame; }
	void setIsNewGame(bool a) { isNewGame = a; }
	int getLoadCount() { return inGameLoadCount; }
	void setLoadCount(int a) { inGameLoadCount = a; }

	void setIsShowSleepingOption(bool a) { isShowSleepingOption = a; }

	void skill_slot(HDC hdc) { _skill->render(hdc); }
	void skillUpdate() { _skill->update(); }

	void closeInvenPage() { isShowInventory = false; }

	skill* getskill() { return _skill; }
	vector<tagSkill> getvSkill() { return _skill->getvSkill(); }
	vector<tagSkill>& getvCurrentSkill() { return _skill->getvCurrentSkill(); }
	float getskillX() { return _skill->getPointX(); }
	float getskillY() { return _skill->getPointY(); }
	RECT getskillRc() { return _skill->getRect(); }
	bool getskillActive() { return _skill->isActive(); }
	bool getskillclick() { return _skill->isClick(); }
	bool getisSkill() { return isSkill; }

	void setIndex(int inx) { index = inx; }
	float getSpeed() { return speed; }
	float getCenterX() { return centerX; }
	void setCenterX(float cX) { centerX = cX; }
	float getCenterY() { return centerY; }
	void setCenterY(float cY) { centerY = cY; }

	inventory* getInventory() { return _inventory; }
	bool getInventoryMove() { return _inventory->getInvenToryMove(); }
	int getCurrentSlotNumber() { return _inventory->getCurrentSlotNumber(); }
	int getCurrentSkillNumber() { return _inventory->getCurrentSKillNumber(); }
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

	bool getIsHit() { return isHit; }
	void setIsHit(bool hit) { isHit = hit; }

	int getCurrentX() { return currentX; }
	int getCurrentY() { return currentY; }

	int getEnergyBarX() { return frontEnergyBar.top; }
	int getHpBarX() { return frontHpBar.top; }
	int getHp() { return playerHp; }
	int getEnergy() { return playerEnergy; }
	int getHpBarBot() { return frontHpBar.bottom; }
	int getDamage() { return Damage; }

	void setEnergyBarX(int energyBar) { frontEnergyBar.top = energyBar; }
	void setHpBarX(int hpbar) { frontHpBar.top = hpbar; }
	void recoverHp(int rec);
	void setHp(int dmg) { playerHp -= dmg; totalHpDmg += dmg / 2; }
	void recoverEnergy(int rec);
	void setEnergy(int dmg) { playerEnergy -= dmg; totalEnergyDmg += dmg / 2; }
	void setHpBarBot(int barBot) { frontHpBar.bottom = barBot; }
	void resetHpBar() { playerHp = MAXHP, totalHpDmg = 0; }
	void resetEnergy() { playerEnergy = MAXENERGY; totalEnergyDmg = 0; }

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
	void openPlayerStorageCover();
	void closePlayerStorageCover();
	void playerCarryItem(HDC hdc);

	void setCurrentMap();

	void countTime();
	void resetClock();

	void resetPlayer();

	bool checkFullyGrown(tagTile tile);
	
	SEASON getSeason() { return currentSeason; }
	WEATHER getWeather() { return currentWeather; }
	int getHour() { return hour; }
	int getMinute() { return minute; }
	void setMoney(int Item_money) { money = Item_money; }
	int getMoney() { return money; }
	int getDate() { return date; }
	DAYOFWEEK getDay() { return day; }

	void loadPlayerData();
	void loadInven();
	void loadBoxInven();
	void loadStock();
	void savePlayerData();
	void savePlayerInven();
	void savePlayerStock();
	void saveMap();
	void saveBox();
	void saveTile(int i, int j, tagTile tile);
};

