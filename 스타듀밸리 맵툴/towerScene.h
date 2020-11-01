#pragma once
#include "gameNode.h"
#include "npc.h"
class towerScene :
    public gameNode
{
	shop* _skillShop;

	RECT _rc_player;
	POINT _pos;

	npc* _skillNpc;

	npc* _npcPtr;

	POINT temp;

	bool _isSkillClicked;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void playerMove();

	void setCurrentSlotNumber(int mouseWheel);
};

