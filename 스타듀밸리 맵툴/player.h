#pragma once
#include "singletonBase.h"
#include "tileNode.h"
#include "inventory.h"

class player : public singletonBase<player>
{
private:
	RECT rc;
	float centerX, centerY;
	int currentX, currentY;
	int MouseIndexX, MouseIndexY;
	float speed;
	int count;
	int index;

	item* _item;

	bool isShowInventory;

	tagTile _tile[TILEY][TILEX];
	OBJ_TYPE objType;

	STATE _pState;
	DIRECTION _pDirection;
	TOOL _pTool;
	
	image* move;
	image* state;
	
	image* _cutdownTree;

	inventory* _inventory;

	
	

public:
	HRESULT init();
	void release();
	void update();
	void render();
	void InventroyRender(HDC hdc);
	
	void setIndex(int inx) { index = inx; }
	float getSpeed() { return speed; }
	float getCenterX() { return centerX; }
	void setCenterX(float cX) { centerX = cX; }
	float getCenterY() { return centerY; }
	void setCenterY(float cY) { centerY = cY; }

	int getCurrentSlotNumber() { return _inventory->getCurrentSlotNumber(); }
	void setCurrentSlotNumber(int a) { _inventory->setCurrentSlotNumber(_inventory->getCurrentSlotNumber() + a); }
	tagItem* getCurrentInven() { return _inventory->getInven(_inventory->getCurrentSlotNumber()); }

	int getCurrentX() { return currentX; }
	int getCurrentY() { return currentY; }

	DIRECTION getDirection() { return _pDirection; }
	void setDirection(DIRECTION dir) { _pDirection = dir; }
	RECT getRc() { return rc; }
	

	void playerAnimation();
	void checkTile();
};

