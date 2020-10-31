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
	bool _isTalk;
	const char* temp_script[10];
	vector<const char*> script;
	int script_count;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void playerMove();

};

