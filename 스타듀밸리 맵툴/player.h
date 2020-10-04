#pragma once
#include "singletonBase.h"
#include "tileNode.h"
#include "inventory.h"

enum STATE
{
	digGround,
	cutdownTree,
	cutGrass,
	breakStone,
	pourwater,
	fillWater,
	attackMonster
};

enum DIRECTION
{
	RIGHT,
	LEFT,
	UP,
	DOWN,
	IDLE
};

enum TOOL
{
	TOOL_SHOVEL, //»ð
	TOOL_AX,     //µµ³¢
	TOOL_PICKAX, //°î±ªÀÌ
	TOOL_SICKLE, //³´
	TOOL_SWORD,  //°Ë
	TOOL_KETTLE,  //ÁÖÀüÀÚ
};

enum SEED
{


};




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

	int getCurrentX() { return currentX; }
	int getCurrentY() { return currentY; }

	DIRECTION getDirection() { return _pDirection; }
	void setDirection(DIRECTION dir) { _pDirection = dir; }
	RECT getRc() { return rc; }
	

	void playerAnimation();
	void checkTile();
};

