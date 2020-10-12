#pragma once
#include "gameNode.h"
#include "shop.h"


class npc : gameNode
{
private:

	shop *_shop;

	RECT _rc;
	POINT _pos;
	DIRECTION _dir;
	NPC_KIND _kind;
	image * _npcImg;
	
	bool _isClicked;

	int _frameX;
	int _frameY;

	int random;

	int _count;

	bool _stop;

public:

	HRESULT init(NPC_KIND kind);
	void release();
	void render();
	void update();
	
	image* getImg() { return _npcImg; }
	RECT getRC() { return _rc; }
	POINT getPos() { return _pos; }
	void setPos(LONG x, LONG y) {
		_pos.x = x;
		_pos.y = y;
	}
		
	bool getClick() { return _isClicked; }
	void move();
	void animation();
};

