#include "stdafx.h"
#include "item.h"

HRESULT item::init()
{
	for (int i = 0; i < 7; i++)
	{
		tagItem temp;
		_vItem.push_back(temp);
	}

	_vItem[0].item_image = IMAGEMANAGER->addImage("rusty_sword", "Images/sword/rusty_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	_vItem[0].item_info = " Damage : 2-5";
	_vItem[0].sell_price = 50;
	_vItem[0].item_kind = ITEM_WEAPON;

	_vItem[1].item_image = IMAGEMANAGER->addImage("galaxy_sword", "Images/sword/galaxy_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	_vItem[1].item_info = " Damage : 60-80\n Speed : 4";
	_vItem[1].sell_price = 1300;
	_vItem[1].buy_price = 50000;
	_vItem[1].item_kind = ITEM_WEAPON;

	_vItem[2].item_image = IMAGEMANAGER->addImage("pencil", "Images/sword/pencil.bmp", 55, 45, true, RGB(255, 0, 255));
	_vItem[2].item_info = " Damage : 1-3 \n Speed : 3";
	_vItem[2].item_kind = ITEM_WEAPON;

	_vItem[3].item_image = IMAGEMANAGER->addImage("rusty_sword", "Images/sword/rusty_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	_vItem[3].item_info = " Damage : 2-5";
	_vItem[3].sell_price = 50;
	_vItem[3].item_kind = ITEM_WEAPON;

	_vItem[4].item_image = IMAGEMANAGER->addImage("rusty_sword", "Images/sword/rusty_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	_vItem[4].item_info = " Damage : 2-5";
	_vItem[4].sell_price = 50;
	_vItem[4].item_kind = ITEM_WEAPON;

	_vItem[5].item_image = IMAGEMANAGER->addImage("rusty_sword", "Images/sword/rusty_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	_vItem[5].item_info = " Damage : 2-5";
	_vItem[5].sell_price = 50;
	_vItem[5].item_kind = ITEM_WEAPON;

	_vItem[6].item_image = IMAGEMANAGER->addImage("rusty_sword", "Images/sword/rusty_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	_vItem[6].item_info = " Damage : 2-5";
	_vItem[6].sell_price = 50;
	_vItem[6].item_kind = ITEM_WEAPON;

	addSeed();

	return S_OK;
}

void item::release()
{
}

void item::update()
{
}

void item::render()
{
}

void item::addSeed()
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

void item::addItem(const char * strKey, ITEM _itemKind, int _indexX, int _indexY, RECT rc, TOOL _toolKind, SEED _seedKind, const char * _itemInfo, int _buyPrice, int _sellPrice)
{
	tagItem temp;
	temp.item_image = IMAGEMANAGER->findImage(strKey);
	temp.item_kind = _itemKind;
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

void item::addSeed(const char * strKey, ITEM _itemKind, int _indexX, int _indexY, SEED _seedKind, const char * _itemInfo, int _buyPrice, int _sellPrice)
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
	_vItem.push_back(temp);
}

void item::addTool(const char * strKey, ITEM _itemKind, int _indexX, int _indexY, TOOL _toolKind, const char * _itemInfo, int _buyPrice, int _sellPrice)
{
	tagItem temp;
	temp.item_image = IMAGEMANAGER->findImage(strKey);
	temp.item_kind = _itemKind;
	temp.indexX = _indexX;
	temp.indexY = _indexY;
	temp.rc = RectMakeCenter(0, 0, 0, 0);
	temp.toolKind = _toolKind;
	temp.item_info = _itemInfo;
	temp.buy_price = _buyPrice;
	temp.sell_price = _sellPrice;
	_vItem.push_back(temp);
}
