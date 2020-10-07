#pragma once
#include "singletonBase.h"
#include "decleration.h"

class itemManager :
	public singletonBase <itemManager>
{

private:
	vector<tagItem> _vItem;

public:
	HRESULT init();
	void release();

	void addSeed();
	void addWeapon();
	void addTool();
	void addFruit();
	void addObject();

	//아이템 추가하는 함수
	void addItem(
		const char* strKey,
		ITEM _itemKind,
		bool _isFrame,
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
		int _sellPrice = 0,
		bool _isFrame = true);

	void addFruit(
		const char* strKey,
		ITEM _itemKind,
		int _indexX,
		int _indexY,
		SEED _seedKind = SEED_NONE,
		const char* _itemInfo = " ",
		int _buyPrice = 0,
		int _sellPrice = 0,
		bool _isFrame = true);

	void addObjectItem(
		const char* strKey,
		ITEM _itemKind,
		int _indexX,
		int _indexY,
		const char* _itemInfo = " ",
		int _buyPrice = 0,
		int _sellPrice = 0,
		bool _isFrame = true);

	void addTool(
		const char* strKey,
		ITEM _itemKind,
		bool _isFrame,
		int _indexX,
		int _indexY,
		TOOL _toolKind,
		const char* _itemInfo = " ",
		int _buyPrice = 0,
		int _sellPrice = 0);

	void addWeapon(
		const char* strKey,
		ITEM _itemKind,
		bool _isFrame,
		const char* _itemInfo = " ",
		int _buyPrice = 0,
		int _sellPrice = 0);

	vector<tagItem> getItem() { return _vItem; }
	tagItem findItem(const char* strKey);
	
};

