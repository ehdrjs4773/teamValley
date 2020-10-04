#pragma once
#include "stdafx.h"
#include "decleration.h"

class item 
{
private:
	
	vector<tagItem> _vItem;
public:
	
	HRESULT init();
	void release();
	void update();
	void render();

	vector<tagItem> getItem() { return _vItem; }
};
