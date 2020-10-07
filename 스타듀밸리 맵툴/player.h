#pragma once
#include "singletonBase.h"
#include "tileNode.h"
#include "inventory.h"

class player : public singletonBase<player>
{
private:
	RECT rc;
	RECT frontHpBar;
	float centerX, centerY;
	int currentX, currentY;
	int MouseIndexX, MouseIndexY;
	float speed;
	int count;
	int index;
	int playerHp;
	int hpBarX;
	int axDamage;
	int pickaxDamage;
	int hoeDamage;

	bool isShowInventory;

	HBRUSH brush;		
	HBRUSH oBrush;

	tagTile _tile[TILEY][TILEX];
	OBJ_TYPE objType;

	STATE _pState;
	DIRECTION _pDirection;
	TOOL _pTool;
	
	image* move;
	image* state;
	image* backHpBar;

	
	image* _cutdownTree;

	inventory* _inventory;

	
	

public:
	HRESULT init();
	void release();
	void update();
	void render();
	void InventroyRender(HDC hdc);

	void hpBarRender(HDC hdc);

	void setIndex(int inx) { index = inx; }
	float getSpeed() { return speed; }
	float getCenterX() { return centerX; }
	void setCenterX(float cX) { centerX = cX; }
	float getCenterY() { return centerY; }
	void setCenterY(float cY) { centerY = cY; }

	int getCurrentSlotNumber() { return _inventory->getCurrentSlotNumber(); }
	void setCurrentSlotNumber(int a) { _inventory->setCurrentSlotNumber(a); }
	vector<tagItem>* getInven() { return _inventory->getInven(); }
	tagItem* getInven(int a) { return _inventory->getInven(a); }
	tagItem* getCurrentInven() { return _inventory->getInven(_inventory->getCurrentSlotNumber()); }
	void setInvenItem(int i, tagItem item) { _inventory->setInvenItem(i, item); }

	int getCurrentX() { return currentX; }
	int getCurrentY() { return currentY; }

	
	int getHpBarX() { return hpBarX; } // 피통렉트 탑 좌표
	int getAxDamage() { return axDamage; }
	int getPickaxDamage() { return pickaxDamage; }
	int getHoeDamage() { return hoeDamage; }
	RECT getHpBar() { return frontHpBar; } 
	void setHpBar(RECT hpbar) { frontHpBar = hpbar; }

	DIRECTION getDirection() { return _pDirection; }
	void setDirection(DIRECTION dir) { _pDirection = dir; }
	RECT getRc() { return rc; }

	STATE getState() { return _pState; }
	void setState(STATE state) {
		if (state != RUN)
		{
			index = 0;
		}
		_pState = state;
	}

	void playerAnimation();
	void playerRender();
};

