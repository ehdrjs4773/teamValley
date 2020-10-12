#include "stdafx.h"
#include "itemManager.h"

HRESULT itemManager::init()
{
	IMAGEMANAGER->addImage("rusty_sword", "Images/sword/rusty_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("galaxy_sword", "Images/sword/galaxy_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pencil", "Images/sword/pencil.bmp", 55, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¾¾¾Ñ", "Images/BMP/¾¾¾Ñ¾ÆÀÌÅÛ.bmp", 360, 160, 9, 4);
	IMAGEMANAGER->addFrameImage("¿­¸Å", "Images/BMP/¿­¸Å.bmp", 640, 120, 16, 3);
	IMAGEMANAGER->addFrameImage("¿­¸Å(¶¥)", "Images/BMP/¿­¸Å(¶¥).bmp", 256, 48, 16, 3);
	IMAGEMANAGER->addFrameImage("µµ±¸", "Images/BMP/µµ±¸.bmp", 360, 160, 9, 4);
	IMAGEMANAGER->addFrameImage("³ª¹«", "Images/BMP/³ª¹«2.bmp", 144, 640, 9, 40);
	IMAGEMANAGER->addFrameImage("³ª¹«Ææ½º", "Images/Ææ½º/³ª¹«Ææ½º.bmp", 48, 352, 3, 22);
	IMAGEMANAGER->addFrameImage("µ¹Ææ½º", "Images/Ææ½º/µ¹Ææ½º.bmp", 48, 352, 3, 22);
	IMAGEMANAGER->addFrameImage("Ææ½º", "Images/Ææ½º/Ææ½º¾ÆÀÌÅÛ.bmp", 80, 40, 2, 1);
	IMAGEMANAGER->addFrameImage("Ææ½º(¶¥)", "Images/Ææ½º/Ææ½º¾ÆÀÌÅÛ(¶¥).bmp", 32, 16, 2, 1);

	addSeed();
	addFruit();
	addWeapon();
	addTool();
	addObject();

	return S_OK;
}

void itemManager::release()
{
}

void itemManager::addSeed()
{
	addSeed("¾¾¾Ñ", ITEM_SEED, 0, 0, SEED_PARSNIP, "ÆÄ½º´Õ ¾¾¾Ñ",100,50);
	addSeed("¾¾¾Ñ", ITEM_SEED, 1, 0, SEED_GREENBEAN, "¿ÏµÎÄá ¾¾¾Ñ", 100, 50);
	addSeed("¾¾¾Ñ", ITEM_SEED, 2, 0, SEED_CAULIFLOWER, "ÄÝ¸®ÇÃ¶ó¿ö ¾¾¾Ñ" , 100, 50);
	addSeed("¾¾¾Ñ", ITEM_SEED, 3, 0, SEED_POTATO, "°¨ÀÚ ¾¾¾Ñ",100,50);
	addSeed("¾¾¾Ñ", ITEM_SEED, 4, 0, SEED_GARLIC, "¸¶´Ã ¾¾¾Ñ",100,50);
	addSeed("¾¾¾Ñ", ITEM_SEED, 5, 0, SEED_KALE, "ÄÉÀÏ ¾¾¾Ñ",100,50);
	addSeed("¾¾¾Ñ", ITEM_SEED, 6, 0, SEED_BEET, "ºñÆ® ¾¾¾Ñ",100,50);
	addSeed("¾¾¾Ñ", ITEM_SEED, 7, 0, SEED_MELON, "¸á·Ð ¾¾¾Ñ", 100, 50);
	addSeed("¾¾¾Ñ", ITEM_SEED, 8, 0, SEED_BLUEJAZZ, "ºí·çÀçÁî ¾¾¾Ñ", 100, 50);
	addSeed("¾¾¾Ñ", ITEM_SEED, 0, 1, SEED_SWEETGEMBERRY, "´ÞÄÞº¸¼®º£¸® ¾¾¾Ñ", 100, 50);
	addSeed("¾¾¾Ñ", ITEM_SEED, 1, 1, SEED_BLUEBERRY, "ºí·çº£¸® ¾¾¾Ñ", 100, 50);
	addSeed("¾¾¾Ñ", ITEM_SEED, 2, 1, SEED_HOTPEPPER, "°íÃß ¾¾¾Ñ", 100, 50);
	addSeed("¾¾¾Ñ", ITEM_SEED, 3, 1, SEED_WHEAT, "¹Ð ¾¾¾Ñ",200,100);
	addSeed("¾¾¾Ñ", ITEM_SEED, 4, 1, SEED_RADISH, "¹« ¾¾¾Ñ", 200, 100);
	addSeed("¾¾¾Ñ", ITEM_SEED, 5, 1, SEED_REDCABBAGE, "Àû¾ç¹èÃß ¾¾¾Ñ", 200, 100);
	addSeed("¾¾¾Ñ", ITEM_SEED, 6, 1, SEED_STARFRUIT, "½ºÅ¸ÈÄ¸£Ã÷ ¾¾¾Ñ", 200, 100);
	addSeed("¾¾¾Ñ", ITEM_SEED, 7, 1, SEED_CORN, "¿Á¼ö¼ö ¾¾¾Ñ", 200, 100);
	addSeed("¾¾¾Ñ", ITEM_SEED, 8, 1, SEED_FAIRYROSE, "¿äÁ¤Àå¹Ì ¾¾¾Ñ", 200, 100);
	addSeed("¾¾¾Ñ", ITEM_SEED, 0, 2, SEED_EGGPLANT, "°¡Áö ¾¾¾Ñ", 200, 100);
	addSeed("¾¾¾Ñ", ITEM_SEED, 1, 2, SEED_ARTICHOKE, "¾ÆÆ¼ÃÊÅ© ¾¾¾Ñ", 200, 100);
	addSeed("¾¾¾Ñ", ITEM_SEED, 2, 2, SEED_PUMPKIN, "È£¹Ú ¾¾¾Ñ", 200, 100);
	addSeed("¾¾¾Ñ", ITEM_SEED, 3, 2, SEED_BOKCHOY, "Ã»°æÃ¤ ¾¾¾Ñ", 200, 100);
	addSeed("¾¾¾Ñ", ITEM_SEED, 4, 2, SEED_YAM, "Âü¸¶ ¾¾¾Ñ", 200, 100);
	addSeed("¾¾¾Ñ", ITEM_SEED, 5, 2, SEED_CRANBERRY, "Å©·£º£¸® ¾¾¾Ñ", 200, 100);
	addSeed("¾¾¾Ñ", ITEM_SEED, 6, 2, SEED_STRAWBERRY, "µþ±â ¾¾¾Ñ", 200, 100);
	addSeed("¾¾¾Ñ", ITEM_SEED, 7, 2, SEED_ANCIENTFRUIT, "°í´ë°úÀÏ ¾¾¾Ñ", 200, 100);
	addSeed("¾¾¾Ñ", ITEM_SEED, 8, 2, SEED_POPPY, "¾ç±Íºñ ¾¾¾Ñ", 200, 100);
	addSeed("¾¾¾Ñ", ITEM_SEED, 0, 3, SEED_TULIP, "Æ«¸³ ¾¾¾Ñ", 200, 100);
	addSeed("¾¾¾Ñ", ITEM_SEED, 1, 3, SEED_AMARANTH, "¾Æ¸¶¶õ½º ¾¾¾Ñ",300,150);
	addSeed("¾¾¾Ñ", ITEM_SEED, 2, 3, SEED_GRAPE, "Æ÷µµ ¾¾¾Ñ", 300, 150);
	addSeed("¾¾¾Ñ", ITEM_SEED, 3, 3, SEED_HOPS, "È© ¾¾¾Ñ", 300, 150);
	addSeed("¾¾¾Ñ", ITEM_SEED, 4, 3, SEED_RANDOM, "¾¾¾Ñ ¸ðÀ½", 300, 150);
	addSeed("¿­¸Å", ITEM_SEED, 3, 1, SEED_COFFEEBEAN, "Ä¿ÇÇÄá ¾¾¾Ñ", 300, 150);
	addSeed("¿­¸Å", ITEM_SEED, 7, 2, SEED_PINETREE, "¼Ò³ª¹« ¾¾¾Ñ", 300, 150);
	addSeed("¿­¸Å", ITEM_SEED, 8, 2, SEED_MAPLETREE, "´ÜÇ³³ª¹« ¾¾¾Ñ", 300, 150);
	addSeed("¿­¸Å", ITEM_SEED, 9, 2, SEED_OAKTREE, "Âü³ª¹« ¾¾¾Ñ", 300, 150);
}

void itemManager::addWeapon()
{
	addWeapon("rusty_sword", ITEM_WEAPON, false, "³ì½¼ ¼Òµå", 500, 250);
	addWeapon("galaxy_sword", ITEM_WEAPON, false, "°¶·°½Ã ¼Òµå",1000,500);
	addWeapon("pencil", ITEM_WEAPON, false, "¿¬ÇÊ",100,50);
}

void itemManager::addTool()
{
	addTool("µµ±¸", ITEM_TOOL, true, 0, 0, TOOL_HOE, "È£¹Ì", 300, 150);
	addTool("µµ±¸", ITEM_TOOL, true, 1, 0, TOOL_PICKAX, "°î±ªÀÌ", 300, 150);
	addTool("µµ±¸", ITEM_TOOL, true, 2, 0, TOOL_AX, "µµ³¢", 300, 150);
	addTool("µµ±¸", ITEM_TOOL, true, 3, 0, TOOL_KETTLE, "ÁÖÀüÀÚ", 300, 150);
	addTool("µµ±¸", ITEM_TOOL, true, 4, 0, TOOL_FISHINGROD, "³¬½Ã´ë", 300, 150);
	addTool("µµ±¸", ITEM_TOOL, true, 5, 0, TOOL_SWORD, "Ä®", 300, 150);
}

void itemManager::addFruit()
{

	addFruit("¿­¸Å", ITEM_FRUIT, 0, 0, SEED_PARSNIP, "ÆÄ½º´Õ", 300, 150);
	addFruit("¿­¸Å", ITEM_FRUIT, 1, 0, SEED_CAULIFLOWER, "ÄÝ¸®ÇÃ¶ó¿ö", 300, 150);
	addFruit("¿­¸Å", ITEM_FRUIT, 2, 0, SEED_GARLIC, "¸¶´Ã", 300, 150);
	addFruit("¿­¸Å", ITEM_FRUIT, 3, 0, SEED_RHUBARB, "´ëÈ²", 300, 150);
	addFruit("¿­¸Å", ITEM_FRUIT, 4, 0, SEED_TOMATO, "Åä¸¶Åä", 300, 150);
	addFruit("¿­¸Å", ITEM_FRUIT, 5, 0, SEED_HOTPEPPER, "°íÃß", 300, 150);
	addFruit("¿­¸Å", ITEM_FRUIT, 6, 0, SEED_RADISH, "¹«", 300, 150);
	addFruit("¿­¸Å", ITEM_FRUIT, 7, 0, SEED_STARFRUIT, "½ºÅ¸ÈÄ¸£Ã÷", 300, 150);
	addFruit("¿­¸Å", ITEM_FRUIT, 8, 0, SEED_EGGPLANT, "°¡Áö", 300, 150);
	addFruit("¿­¸Å", ITEM_FRUIT, 9, 0, SEED_PUMPKIN, "È£¹Ú", 300, 150);
	addFruit("¿­¸Å", ITEM_FRUIT, 10, 0, SEED_YAM, "Âü¸¶", 300, 150);
	addFruit("¿­¸Å", ITEM_FRUIT, 11, 0, SEED_BEET, "ºñÆ®", 300, 150);
	addFruit("¿­¸Å", ITEM_FRUIT, 12, 0, SEED_ANCIENTFRUIT, "°í´ë°úÀÏ", 300, 150);
	addFruit("¿­¸Å", ITEM_FRUIT, 13, 0, SEED_TULIP, "Æ«¸³", 300, 150);
	addFruit("¿­¸Å", ITEM_FRUIT, 14, 0, SEED_POPPY, "¾ç±Íºñ", 300, 150);
	addFruit("¿­¸Å", ITEM_FRUIT, 15, 0, SEED_SUNFLOWER, "ÇØ¹Ù¶ó±â", 300, 150);
	addFruit("¿­¸Å", ITEM_FRUIT, 0, 1, SEED_SWEETGEMBERRY, "´ÞÄÞº¸¼®º£¸®", 300, 150);
	addFruit("¿­¸Å", ITEM_FRUIT, 1, 1, SEED_STRAWBERRY, "µþ±â", 300, 150);
	addFruit("¿­¸Å", ITEM_FRUIT, 2, 1, SEED_GRAPE, "Æ÷µµ", 500, 250);
	addFruit("¿­¸Å", ITEM_FRUIT, 3, 1, SEED_COFFEEBEAN, "Ä¿ÇÇÄá", 500, 250);
	addFruit("¿­¸Å", ITEM_FRUIT, 4, 1, SEED_GREENBEAN, "¿ÏµÎÄá", 500, 250);
	addFruit("¿­¸Å", ITEM_FRUIT, 5, 1, SEED_POTATO, "°¨ÀÚ", 500, 250);
	addFruit("¿­¸Å", ITEM_FRUIT, 6, 1, SEED_KALE, "ÄÉÀÏ", 500, 250);
	addFruit("¿­¸Å", ITEM_FRUIT, 7, 1, SEED_MELON, "¸á·Ð", 500, 250);
	addFruit("¿­¸Å", ITEM_FRUIT, 8, 1, SEED_BLUEBERRY, "ºí·çº£¸®", 500, 250);
	addFruit("¿­¸Å", ITEM_FRUIT, 9, 1, SEED_WHEAT, "¹Ð", 500, 250);
	addFruit("¿­¸Å", ITEM_FRUIT, 10, 1, SEED_REDCABBAGE, "Àû¾ç¹èÃß", 500, 250);
	addFruit("¿­¸Å", ITEM_FRUIT, 11, 1, SEED_CORN, "¿Á¼ö¼ö", 750, 370);
	addFruit("¿­¸Å", ITEM_FRUIT, 12, 1, SEED_ARTICHOKE, "¾ÆÆ¼ÃÊÅ©", 750, 370);
	addFruit("¿­¸Å", ITEM_FRUIT, 13, 1, SEED_BOKCHOY, "Ã»°æÃ¤", 750, 370);
	addFruit("¿­¸Å", ITEM_FRUIT, 14, 1, SEED_CRANBERRY, "Å©·£º£¸®", 750, 370);
	addFruit("¿­¸Å", ITEM_FRUIT, 15, 1, SEED_BLUEJAZZ, "ºí·çÀçÁî", 750, 370);
	addFruit("¿­¸Å", ITEM_FRUIT, 0, 2, SEED_SUMMERSPANGLE, "¿©¸§º°²É", 750, 370);
	addFruit("¿­¸Å", ITEM_FRUIT, 1, 2, SEED_FAIRYROSE, "¿äÁ¤Àå¹Ì", 750, 370);
	addFruit("¿­¸Å", ITEM_FRUIT, 2, 2, SEED_HOPS, "È©", 750, 370);
	addFruit("¿­¸Å", ITEM_FRUIT, 3, 2, SEED_AMARANTH, "¾Æ¸¶¶õ½º", 750, 370);
	addFruit("¿­¸Å", ITEM_FRUIT, 4, 2, SEED_CATUS, "¼±ÀÎÀå¿­¸Å", 750, 370);
}

void itemManager::addObject()
{
	addObjectItem("¿­¸Å", ITEM_DEBRIS, 5, 2, "µ¹", 1000, 500);
	addObjectItem("¿­¸Å", ITEM_DEBRIS, 6, 2, "³ª¹«", 1000, 500);
	addObjectItem("¿­¸Å", ITEM_DEBRIS, 10, 2, "´Ü´ÜÇÑ³ª¹«", 1000, 500);
	addObjectItem("Ææ½º", ITEM_WOODENFENCE, 0, 0, "³ª¹«¿ïÅ¸¸®", 1000, 500);
	addObjectItem("Ææ½º", ITEM_STONEFENCE, 1, 0, "¼®Àç¿ïÅ¸¸®", 1000, 500);
	addObjectItem("Ææ½º", ITEM_WOODENFENCEDOOR, 0, 0, "³ª¹«¿ïÅ¸¸®¹®", 1000, 500);
	addObjectItem("Ææ½º", ITEM_STONEFENCEDOOR, 1, 0, "¼®Àç¿ïÅ¸¸®¹®", 1000, 500);
}

void itemManager::addItem(const char * strKey, ITEM _itemKind, bool _isFrame, int _indexX, int _indexY, TOOL _toolKind, SEED _seedKind, const char * _itemInfo, int _buyPrice, int _sellPrice)
{
	tagItem temp;
	temp.item_image = IMAGEMANAGER->findImage(strKey);
	temp.item_kind = _itemKind;
	temp.isFrame = _isFrame;
	temp.indexX = _indexX;
	temp.indexY = _indexY;
	temp.toolKind = _toolKind;
	temp.seedKind = _seedKind;
	temp.item_info = _itemInfo;
	temp.buy_price = _buyPrice;
	temp.sell_price = _sellPrice;
	temp.amount = 1;
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
	temp.amount = 1;
	temp.isFrame = _isFrame;
	_vItem.push_back(temp);
}

void itemManager::addFruit(const char * strKey, ITEM _itemKind, int _indexX, int _indexY, SEED _seedKind, const char * _itemInfo, int _buyPrice, int _sellPrice, bool _isFrame)
{
	tagItem temp;
	temp.item_image = IMAGEMANAGER->findImage(strKey);
	temp.item_kind = _itemKind;
	temp.indexX = _indexX;
	temp.indexY = _indexY;
	temp.rc = RectMakeCenter(0, 0, 0, 0);
	temp.seedKind = _seedKind;
	temp.item_info = _itemInfo;
	temp.buy_price = _buyPrice;
	temp.sell_price = _sellPrice;
	temp.amount = 1;
	temp.isFrame = _isFrame;
	_vItem.push_back(temp);
}

void itemManager::addObjectItem(const char * strKey, ITEM _itemKind, int _indexX, int _indexY, const char * _itemInfo, int _buyPrice, int _sellPrice, bool _isFrame)
{
	tagItem temp;
	temp.item_image = IMAGEMANAGER->findImage(strKey);
	temp.item_kind = _itemKind;
	temp.indexX = _indexX;
	temp.indexY = _indexY;
	temp.rc = RectMakeCenter(0, 0, 0, 0);
	temp.seedKind = SEED_NONE;
	temp.item_info = _itemInfo;
	temp.buy_price = _buyPrice;
	temp.sell_price = _sellPrice;
	temp.amount = 1;
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
	temp.seedKind = SEED_NONE;
	temp.item_info = _itemInfo;
	temp.buy_price = _buyPrice;
	temp.waterAmount = 0;
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

tagItem itemManager::findItem(const char * strKey)
{
	for (auto iter : _vItem)
	{
		if (iter.item_info == strKey)
		{
			return iter;
		}
	}
}
