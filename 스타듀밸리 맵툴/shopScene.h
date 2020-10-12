#pragma once
#include "gameNode.h"
#include "npc.h"
class shopScene : public gameNode
{
	shop* _shop;
	RECT _rc_player;
	POINT _pos;

	npc* _itemNpc;

	npc* _skillNpc;

	bool _isClicked;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

