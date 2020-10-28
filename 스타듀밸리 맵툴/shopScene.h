#pragma once
#include "gameNode.h"
#include "npc.h"
class shopScene : public gameNode
{
	shop* _itemShop;

	RECT _rc_player;
	POINT _pos;

	npc* _itemNpc;
	
	npc* _npcPtr;
	POINT temp;

	bool _isShopClicked;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void playerMove();

};

