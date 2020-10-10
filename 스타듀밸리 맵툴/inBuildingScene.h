#pragma once
#include "gameNode.h"
#include "tileNode.h"

class inBuildingScene :	public gameNode
{
private:



public:
	HRESULT init();
	void release();
	void update();
	void render();

	void playerMove();


};

