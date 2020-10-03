#pragma once
#include "gameNode.h"
#include "player.h"

class playerInventory:public gameNode
{
private:


	RECT _playerInventory;

	RECT _playerTool[12];

	int MouseIndexX, MouseIndexY;

	






public:




	HRESULT init();
	void release();
	void update();
	void render();

};

