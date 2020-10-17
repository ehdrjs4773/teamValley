#pragma once
#include "gameNode.h"
#include "tileNode.h"

class mineScene : public gameNode
{
private:
	tagTile _tile[TILEY][TILEX];
	int currentFloor;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	void playerMove();
	void setRandomObstacles();
};

