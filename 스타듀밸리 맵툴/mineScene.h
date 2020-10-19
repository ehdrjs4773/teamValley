#pragma once
#include "gameNode.h"
#include "tileNode.h"

class mineScene : public gameNode
{
private:
	//∂•ø° ∂≥æÓ¡¯ æ∆¿Ã≈€øÎ ∫§≈Õ
	vector<tagItemOnField> _vItemOnField;
	RECT getItemRc;
	RECT sickleHitBox;

	tagTile _tile[TILEY][TILEX];
	int currentFloor;

	int currentIndexX, currentIndexY;
	int mouseIndexX, mouseIndexY;

	int leftIndexX, leftIndexY;
	int rightIndexX, rightIndexY;
	int upIndexX, upIndexY;
	int downIndexX, downIndexY;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void playerMove();
	void checkCurrentTile();

	void playerInteraction();
	void breakStone();
	void cutGrass();

	void renderMap();
	void renderTerrain(int i, int j);
	void renderObject(int i, int j);

	void setRandomObstacles();
	void setStone(int i, int j);
	void setWeed(int i, int j);
	void setOre(int i, int j);
	void getItem(tagItem item);
	void ejectItem();
	void dropItem(tagTile tile, const char* itemInfo);
	
};

