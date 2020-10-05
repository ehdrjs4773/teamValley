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

	void addSeed();

	//아이템 추가하는 함수
	void addItem(
		const char* strKey,
		ITEM _itemKind,
		int _indexX,
		int _indexY,
		RECT rc = RectMakeCenter(0, 0, 0, 0),
		TOOL _toolKind = TOOL_NONE,
		SEED _seedKind = SEED_NONE,
		const char* _itemInfo = " ",
		int _buyPrice = 0,
		int _sellPrice = 0);

	void addSeed(
		const char* strKey,
		ITEM _itemKind,
		int _indexX,
		int _indexY,
		SEED _seedKind = SEED_NONE,
		const char* _itemInfo = " ",
		int _buyPrice = 0,
		int _sellPrice = 0);

	void addTool(
		const char* strKey,
		ITEM _itemKind,
		int _indexX,
		int _indexY,
		TOOL _toolKind,
		const char* _itemInfo = " ",
		int _buyPrice = 0,
		int _sellPrice = 0);

	vector<tagItem> getItem() { return _vItem; }
};
