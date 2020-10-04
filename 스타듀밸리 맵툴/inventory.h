#pragma once
#include "gameNode.h"
#include "item.h"
#define INVENMAX 36

class inventory :
	public gameNode
{
private:
	image *inventory_img;
	
	vector<tagItem> _vItem;

public:
	HRESULT init();
	void release();
	void update();
	void render();
	vector<tagItem>* getInven() { return &_vItem; }
};

