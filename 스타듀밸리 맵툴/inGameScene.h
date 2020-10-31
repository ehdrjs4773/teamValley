#pragma once
#include "gameNode.h"
#include "tileNode.h"


class inGameScene : public gameNode
{
private:
	tagTile _tile[TILEY][TILEX]; 
	tagTile tileSave[TILEY][TILEX];

	//∂•ø° ∂≥æÓ¡¯ æ∆¿Ã≈€øÎ ∫§≈Õ
	vector<tagItemOnField> _vItemOnField;

	float playerCenterX, playerCenterY;
	RECT getItemRc;
	RECT sickleHitBox;


	SEASON _currentSeason;

	int loadCount;
	string imageName;
	string objectImageName;

	int currentIndexX;
	int currentIndexY;
	int MouseIndexX, MouseIndexY;

	int leftIndexX, leftIndexY;
	int rightIndexX, rightIndexY;
	int upIndexX, upIndexY;
	int downIndexX, downIndexY;

	bool isShowRect;
	bool isShopOpen;
	bool isSprinkled;
	bool isShowCalender = false;

public:
	inGameScene();
	
	HRESULT init();
	void release();
	void update();
	void render();

	void load();
	void setTileRect();
	void changeSeason(SEASON season);

	void renderMap();
	void renderObjects(int i, int j);
	void renderTree(int i, int j);

	void playerMove();
	void moveScene();
	void shareTileData();

	void checkPlayerTile();
	void playerInteraction();
	void hackGround();
	void waterGround();
	void setEquipment();
	void fillWater();
	void plantSeed();
	void harvest();
	void cutdownTree();
	void breakStone();
	void cutGrass();
	void setFence();
	void setSprinkler();
	void sprinklerWork();
	void eatFruit();

	void makeCropGrow();
	bool checkFullyGrown(tagTile tile);
	void getItem(tagItem item);
	void dropFruit(tagTile tile, ITEM itemKind, SEED seedType);
	void dropItem(tagTile tile, ITEM itemKind, int indexX);
	void ejectItem();

	void skillClick();
	void skillSelect();

	void checkHacked();
	void checkFence();

	void setRandomObstacles();
	void changeGrass();

	void setEventGround();
	void resetOriginalGround();

	void setCurrentSlotNumber(int mouseWheel);
	TERRAIN terrainSelect(int frameX, int frameY);
	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

