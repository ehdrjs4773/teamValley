#include "stdafx.h"
#include "itemManager.h"

HRESULT itemManager::init()
{
	IMAGEMANAGER->addImage("rusty_sword", "Images/sword/rusty_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("galaxy_sword", "Images/sword/galaxy_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pencil", "Images/sword/pencil.bmp", 55, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¾¾¾Ñ", "Images/BMP/¾¾¾Ñ¾ÆÀÌÅÛ.bmp", 360, 160, 9, 4);
	
	addSeed();

	addWeapon();

	return S_OK;
}

void itemManager::addSeed()
{
	addSeed("¾¾¾Ñ", ITEM_SEED, 0, 0, SEED_PARSNIP, "ÆÄ½º´Õ ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 1, 0, SEED_GREENBEAN, "¿ÏµÎÄá ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 2, 0, SEED_CAULIFLOWER, "ÄÝ¸®ÇÃ¶ó¿ö ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 3, 0, SEED_POTATO, "°¨ÀÚ ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 4, 0, SEED_GARLIC, "¸¶´Ã ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 5, 0, SEED_KALE, "ÄÉÀÏ ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 6, 0, SEED_BEET, "ºñÆ® ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 7, 0, SEED_MELON, "¸á·Ð ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 8, 0, SEED_BLUEJAZZ, "ºí·çÀçÁî ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 0, 1, SEED_SWEETGEMBERRY, "´ÞÄÞº¸¼®º£¸® ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 1, 1, SEED_BLUEBERRY, "ºí·çº£¸® ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 2, 1, SEED_HOTPEPPER, "°íÃß ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 3, 1, SEED_WHEAT, "¹Ð ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 4, 1, SEED_RADISH, "¹« ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 5, 1, SEED_REDCABBAGE, "Àû¾ç¹èÃß ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 6, 1, SEED_STARFRUIT, "½ºÅ¸ÈÄ¸£Ã÷ ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 7, 1, SEED_CORN, "¿Á¼ö¼ö ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 8, 1, SEED_FAIRYROSE, "¿äÁ¤Àå¹Ì ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 0, 2, SEED_EGGPLANT, "°¡Áö ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 1, 2, SEED_ARTICHOKE, "¾ÆÆ¼ÃÊÅ© ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 2, 2, SEED_PUMPKIN, "È£¹Ú ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 3, 2, SEED_BOKCHOY, "Ã»°æÃ¤ ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 4, 2, SEED_YAM, "Âü¸¶ ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 5, 2, SEED_CRANBERRY, "Å©·£º£¸® ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 6, 2, SEED_STRAWBERRY, "µþ±â ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 7, 2, SEED_ANCIENTFRUIT, "°í´ë°úÀÏ ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 8, 2, SEED_POPPY, "¾ç±Íºñ ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 0, 3, SEED_TULIP, "Æ«¸³ ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 1, 3, SEED_AMARANTH, "¾Æ¸¶¶õ½º ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 2, 3, SEED_GRAPE, "Æ÷µµ ¾¾¾Ñ");
	addSeed("¾¾¾Ñ", ITEM_SEED, 3, 3, SEED_HOPS, "È© ¾¾¾Ñ");
}

void itemManager::addWeapon()
{
	addWeapon("rusty_sword", ITEM_WEAPON, false, "³ì½¼ ¼Òµå");
	addWeapon("galaxy_sword", ITEM_WEAPON, false, "°¶·°½Ã ¼Òµå");
	addWeapon("pencil", ITEM_WEAPON, false, "¿¬ÇÊ");
}

void itemManager::addItem(const char * strKey, ITEM _itemKind, bool _isFrame, int _indexX, int _indexY, RECT rc, TOOL _toolKind, SEED _seedKind, const char * _itemInfo, int _buyPrice, int _sellPrice)
{
	tagItem temp;
	temp.item_image = IMAGEMANAGER->findImage(strKey);
	temp.item_kind = _itemKind;
	temp.isFrame = _isFrame;
	temp.indexX = _indexX;
	temp.indexY = _indexY;
	temp.rc = rc;
	temp.toolKind = _toolKind;
	temp.seedKind = _seedKind;
	temp.item_info = _itemInfo;
	temp.buy_price = _buyPrice;
	temp.sell_price = _sellPrice;
	_vItem.push_back(temp);
}

void itemManager::addSeed(const char * strKey, ITEM _itemKind, int _indexX, int _indexY, SEED _seedKind, const char * _itemInfo, int _buyPrice, int _sellPrice, bool _isFrame)
{
	tagItem temp;
	temp.item_image = IMAGEMANAGER->findImage(strKey);
	temp.item_kind = _itemKind;
	temp.indexX = _indexX;
	temp.indexY = _indexY;
	temp.rc = RectMakeCenter(0, 0, 0, 0);
	temp.toolKind = TOOL_NONE;
	temp.seedKind = _seedKind;
	temp.item_info = _itemInfo;
	temp.buy_price = _buyPrice;
	temp.sell_price = _sellPrice;
	temp.isFrame = _isFrame;
	_vItem.push_back(temp);
}

void itemManager::addTool(const char * strKey, ITEM _itemKind, bool _isFrame, int _indexX, int _indexY, TOOL _toolKind, const char * _itemInfo, int _buyPrice, int _sellPrice)
{
	tagItem temp;
	temp.item_image = IMAGEMANAGER->findImage(strKey);
	temp.item_kind = _itemKind;
	temp.isFrame = _isFrame;
	temp.indexX = _indexX;
	temp.indexY = _indexY;
	temp.rc = RectMakeCenter(0, 0, 0, 0);
	temp.toolKind = _toolKind;
	temp.item_info = _itemInfo;
	temp.buy_price = _buyPrice;
	temp.sell_price = _sellPrice;
	_vItem.push_back(temp);
}

void itemManager::addWeapon(const char * strKey, ITEM _itemKind, bool _isFrame, const char * _itemInfo, int _buyPrice, int _sellPrice)
{
	tagItem temp;
	temp.item_image = IMAGEMANAGER->findImage(strKey);
	temp.item_kind = _itemKind;
	temp.isFrame = _isFrame;
	temp.rc = RectMakeCenter(0, 0, 0, 0);
	temp.item_info = _itemInfo;
	temp.buy_price = _buyPrice;
	temp.sell_price = _sellPrice;
	_vItem.push_back(temp);
}
