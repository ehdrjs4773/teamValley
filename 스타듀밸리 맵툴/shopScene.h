#pragma once
#include "gameNode.h"
#include "shop.h"

class shopScene : public gameNode
{
	shop *_shop;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

