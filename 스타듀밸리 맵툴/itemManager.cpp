#include "stdafx.h"
#include "itemManager.h"

HRESULT itemManager::init()
{
	IMAGEMANAGER->addImage("rusty_sword", "Images/sword/rusty_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("galaxy_sword", "Images/sword/galaxy_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pencil", "Images/sword/pencil.bmp", 55, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¾¾¾Ñ", "Images/BMP/¾¾¾Ñ¾ÆÀÌÅÛ.bmp", 320, 80, 8, 2);
	IMAGEMANAGER->addFrameImage("¾¾¾Ñhold", "Images/BMP/¾¾¾Ñ¾ÆÀÌÅÛsmall.bmp", 128, 32, 8, 2);
	IMAGEMANAGER->addFrameImage("¿­¸Å", "Images/BMP/¿­¸Å.bmp", 320, 120, 8, 3);
	IMAGEMANAGER->addFrameImage("¿­¸Å(¶¥)", "Images/BMP/¿­¸Åsmall.bmp", 128, 48, 8, 3);
	IMAGEMANAGER->addFrameImage("µµ±¸", "Images/BMP/µµ±¸.bmp", 360, 160, 9, 4);
	IMAGEMANAGER->addFrameImage("³ª¹«", "Images/BMP/³ª¹«2.bmp", 144, 640, 9, 40);
	IMAGEMANAGER->addImage("ºÒ_°Ë", "Images/skill/ºÒ_°Ë.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ºí·¢È¦_°Ë", "Images/skill/ºí·¢È¦_°Ë.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("½ºÆÄÀÌÅ©_°Ë", "Images/skill/½ºÆÄÀÌÅ©_°Ë.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÆÄÀÌ¾îº¼_°Ë", "Images/skill/ÆÄÀÌ¾îº¼_°Ë.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Æø¹ß_°Ë", "Images/skill/Æø¹ß_°Ë.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("±¤¹°", "Images/BMP/±¤¹°.bmp", 256, 80, 16, 5);
	IMAGEMANAGER->addFrameImage("±¤¹°¾ÆÀÌÅÛ", "Images/BMP/±¤¹°¾ÆÀÌÅÛ.bmp", 640, 200, 16, 5);
	IMAGEMANAGER->addFrameImage("½ºÇÁ¸µÅ¬·¯", "Images/BMP/½ºÇÁ¸µÅ¬·¯.bmp", 16, 48, 1, 3);
	IMAGEMANAGER->addFrameImage("½ºÇÁ¸µÅ¬·¯¾ÆÀÌÅÛ", "Images/BMP/½ºÇÁ¸µÅ¬·¯¾ÆÀÌÅÛ.bmp", 40, 120, 1, 3);
	IMAGEMANAGER->addFrameImage("Ææ½º", "Images/Ææ½º/Ææ½º¾ÆÀÌÅÛ.bmp", 80, 40, 2, 1);

	readItemCSV();

	addCSVItem();

	addSkill();
	addWeapon();
	addTool();
	addOre();

	addSprinkler("½ºÇÁ¸µÅ¬·¯¾ÆÀÌÅÛ", ITEM_SPRINKLER1, true, 0, 0, "±âº»½ºÇÁ¸µÅ¬·¯");
	addSprinkler("½ºÇÁ¸µÅ¬·¯¾ÆÀÌÅÛ", ITEM_SPRINKLER2, true, 0, 1, "°­È­½ºÇÁ¸µÅ¬·¯");
	addSprinkler("½ºÇÁ¸µÅ¬·¯¾ÆÀÌÅÛ", ITEM_SPRINKLER3, true, 0, 2, "°í±Þ½ºÇÁ¸µÅ¬·¯");

	return S_OK;
}

void itemManager::release()
{
}

void itemManager::addSeed()
{
	//addSeed("¾¾¾Ñ", ITEM_SEED, 0, 0, SEED_HOPS, "È© ¾¾¾Ñ", 25, 15);
	//addSeed("¾¾¾Ñ", ITEM_SEED, 1, 0, SEED_RADISH, "¹« ¾¾¾Ñ", 40, 25);
	//addSeed("¾¾¾Ñ", ITEM_SEED, 2, 0, SEED_WHEAT, "¹Ð ¾¾¾Ñ", 10, 5);
	//addSeed("¾¾¾Ñ", ITEM_SEED, 3, 0, SEED_TOMATO, "Åä¸¶Åä ¾¾¾Ñ", 50, 40);
	//addSeed("¾¾¾Ñ", ITEM_SEED, 4, 0, SEED_GREENBEAN, "¿ÏµÎÄá ¾¾¾Ñ", 40, 30);
	//addSeed("¾¾¾Ñ", ITEM_SEED, 5, 0, SEED_MELON, "¸á·Ð ¾¾¾Ñ", 80, 60);
	//addSeed("¾¾¾Ñ", ITEM_SEED, 6, 0, SEED_POPPY, "¾ç±Íºñ ¾¾¾Ñ", 140, 120);
	//addSeed("¾¾¾Ñ", ITEM_SEED, 7, 0, SEED_SUMMERSPANGLE, "¿©¸§º°²É ¾¾¾Ñ", 90, 75);
	//addSeed("¾¾¾Ñ", ITEM_SEED, 0, 1, SEED_HOTPEPPER, "°íÃß ¾¾¾Ñ", 90, 75);
	//addSeed("¾¾¾Ñ", ITEM_SEED, 1, 1, SEED_CORN, "¿Á¼ö¼ö ¾¾¾Ñ", 155, 130);
	//addSeed("¾¾¾Ñ", ITEM_SEED, 2, 1, SEED_BLUEBERRY, "ºí·çº£¸® ¾¾¾Ñ", 80, 60);
	//addSeed("¾¾¾Ñ", ITEM_SEED, 3, 1, SEED_SUNFLOWER, "ÇØ¹Ù¶ó±â ¾¾¾Ñ", 80, 60);
	//addSeed("¾¾¾Ñ", ITEM_SEED, 4, 1, SEED_REDCABBAGE, "Àû¾ç¹èÃß ¾¾¾Ñ", 100, 80);
	//addSeed("¾¾¾Ñ", ITEM_SEED, 5, 1, SEED_GRAPE, "Æ÷µµ ¾¾¾Ñ", 150, 125);
	//addSeed("¾¾¾Ñ", ITEM_SEED, 6, 1, SEED_STARFRUIT, "½ºÅ¸ÈÄ¸£Ã÷ ¾¾¾Ñ", 400, 250);

	//addSeed("¿­¸Å", ITEM_SEED, 0, 2, SEED_PINETREE, "¼Ò³ª¹« ¾¾¾Ñ", 0, 20);
	//addSeed("¿­¸Å", ITEM_SEED, 1, 2, SEED_MAPLETREE, "´ÜÇ³³ª¹« ¾¾¾Ñ", 0, 20);
	//addSeed("¿­¸Å", ITEM_SEED, 2, 2, SEED_OAKTREE, "Âü³ª¹« ¾¾¾Ñ", 0, 20);
}

void itemManager::addWeapon()
{
	addWeapon("rusty_sword", ITEM_WEAPON, WEAPON_RUSTYSWORD, false, "³ì½¼ ¼Òµå", 500, 250);
	addWeapon("galaxy_sword", ITEM_WEAPON, WEAPON_GALAXYSWORD, false, "°¶·°½Ã ¼Òµå",1000,500);
	addWeapon("pencil", ITEM_WEAPON, WEAPON_PENCIL, false, "¿¬ÇÊ",100,50);
}

void itemManager::addTool()
{
	addTool("µµ±¸", ITEM_TOOL, true, 0, 0, TOOL_HOE, "È£¹Ì", 300, 150);
	addTool("µµ±¸", ITEM_TOOL, true, 1, 0, TOOL_PICKAX, "°î±ªÀÌ", 300, 150);
	addTool("µµ±¸", ITEM_TOOL, true, 2, 0, TOOL_AX, "µµ³¢", 300, 150);
	addTool("µµ±¸", ITEM_TOOL, true, 3, 0, TOOL_KETTLE, "ÁÖÀüÀÚ", 300, 150);
	addTool("µµ±¸", ITEM_TOOL, true, 4, 0, TOOL_FISHINGROD, "³¬½Ã´ë", 300, 150);
	addTool("µµ±¸", ITEM_TOOL, true, 5, 0, TOOL_SWORD, "Ä®", 300, 150);
	addTool("µµ±¸", ITEM_TOOL, true, 6, 0, TOOL_SICKLE, "³´", 300, 150);
}

void itemManager::addFruit()
{
	//addFruit("¿­¸Å", ITEM_FRUIT, 0, 0, SEED_HOPS, "È©", 0, 20);
	//addFruit("¿­¸Å", ITEM_FRUIT, 1, 0, SEED_RADISH, "¹«", 0, 110);
	//addFruit("¿­¸Å", ITEM_FRUIT, 2, 0, SEED_WHEAT, "¹Ð", 0, 35);
	//addFruit("¿­¸Å", ITEM_FRUIT, 3, 0, SEED_TOMATO, "Åä¸¶Åä", 0, 60);
	//addFruit("¿­¸Å", ITEM_FRUIT, 4, 0, SEED_GREENBEAN, "¿ÏµÎÄá", 0, 35);
	//addFruit("¿­¸Å", ITEM_FRUIT, 5, 0, SEED_MELON, "¸á·Ð", 0, 250);
	//addFruit("¿­¸Å", ITEM_FRUIT, 6, 0, SEED_POPPY, "¾ç±Íºñ", 0, 275);
	//addFruit("¿­¸Å", ITEM_FRUIT, 7, 0, SEED_SUMMERSPANGLE, "¿©¸§º°²É", 0, 220);
	//addFruit("¿­¸Å", ITEM_FRUIT, 0, 1, SEED_HOTPEPPER, "°íÃß", 0, 70);
	//addFruit("¿­¸Å", ITEM_FRUIT, 1, 1, SEED_CORN, "¿Á¼ö¼ö", 0, 80);
	//addFruit("¿­¸Å", ITEM_FRUIT, 2, 1, SEED_BLUEBERRY, "ºí·çº£¸®", 0, 30); 
	//addFruit("¿­¸Å", ITEM_FRUIT, 3, 1, SEED_SUNFLOWER, "ÇØ¹Ù¶ó±â", 0, 250);
	//addFruit("¿­¸Å", ITEM_FRUIT, 4, 1, SEED_REDCABBAGE, "Àû¾ç¹èÃß", 0, 280);
	//addFruit("¿­¸Å", ITEM_FRUIT, 5, 1, SEED_GRAPE, "Æ÷µµ", 0, 100);
	//addFruit("¿­¸Å", ITEM_FRUIT, 6, 1, SEED_STARFRUIT, "½ºÅ¸ÈÄ¸£Ã÷", 0, 750);
}

void itemManager::addObject()
{
	//addObjectItem("¿­¸Å", ITEM_DEBRIS, 3, 2, "µ¹", 0, 5);
	//addObjectItem("¿­¸Å", ITEM_DEBRIS, 4, 2, "³ª¹«", 0, 5);
	//addObjectItem("Ææ½º", ITEM_WOODENFENCE, 0, 0, "³ª¹«¿ïÅ¸¸®", 0, 5);
	//addObjectItem("Ææ½º", ITEM_STONEFENCE, 1, 0, "¼®Àç¿ïÅ¸¸®", 0, 5);
}

void itemManager::addSkill()
{
	addWeapon("Æø¹ß_°Ë", ITEM_SKILL, WEAPON_EXPLOSION, false, "Æø¹ß °Ë", 1000, 500);
	addWeapon("½ºÆÄÀÌÅ©_°Ë", ITEM_SKILL, WEAPON_SPIKES, false, "½ºÆÄÀÌÅ© °Ë", 1000, 500);
	addWeapon("ºÒ_°Ë", ITEM_SKILL, WEAPON_FIRE, false, "ºÒ °Ë", 1000, 500);
	addWeapon("ºí·¢È¦_°Ë", ITEM_SKILL, WEAPON_BLACKHOLE, false, "ºí·¢È¦ °Ë", 1000, 500);
	addWeapon("ÆÄÀÌ¾îº¼_°Ë", ITEM_SKILL, WEAPON_FIREBALL, false, "ÆÄÀÌ¾îº¼ °Ë", 1000, 500);
}

void itemManager::addOre()
{
	//addOre("±¤¹°", ITEM_ORE, true, 6, 3, "±¸¸®Á¶°¢");
	//addOre("±¤¹°", ITEM_ORE, true, 8, 3, "Ã¶Á¶°¢");
	//addOre("±¤¹°", ITEM_ORE, true, 12, 3, "±ÝÁ¶°¢");
}

void itemManager::readItemCSV()
{
	fstream fs;
	string buf;
	int a = 0;
	fs.open("save/itemData.csv", ios::in);

	while (!fs.eof())
	{
		getline(fs, buf, '\n');
		if (a == 0)
		{
			a++;
			continue;
		}
		itemDataLine.push_back(buf);
	}
	tokItemDataLine();
	fs.close();
}

void itemManager::tokItemDataLine()
{
	for (int i = 0; i < itemDataLine.size(); i++)
	{
		vector<string> temp;
		stringTokenize(itemDataLine[i], temp);
	}
}

void itemManager::addCSVItem()
{
	for (int i = 0; i < itemData.size() - 1; i++)
	{
			tagItem temp;
			temp.item_image = IMAGEMANAGER->findImage(itemData[i][0]);
			temp.item_kind = (ITEM)(atoi)(itemData[i][1].c_str());
			temp.toolKind = (TOOL)(atoi)(itemData[i][2].c_str());
			temp.seedKind = (SEED)(atoi)(itemData[i][3].c_str());
			temp.weaponKind = (WEAPON)(atoi)(itemData[i][4].c_str());
			temp.itemName = itemData[i][5].c_str();
			temp.item_info = itemData[i][6].c_str();
			temp.buy_price = (atoi)(itemData[i][7].c_str());
			temp.sell_price = (atoi)(itemData[i][8].c_str());
			temp.waterAmount = (atoi)(itemData[i][9].c_str());
			temp.indexX = (atoi)(itemData[i][10].c_str());
			temp.indexY = (atoi)(itemData[i][11].c_str());
			temp.amount = (atoi)(itemData[i][12].c_str());
			temp.isFrame = (atoi)(itemData[i][13].c_str());

			_vItem.push_back(temp);
	}
}

void itemManager::stringTokenize(const string & str, vector<string>& tokens, const string & delimiters)
{
	//¸Ç Ã¹ ±ÛÀÚ°¡ ±¸ºÐÀÚÀÎ °æ¿ì ¹«½Ã
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	//±¸ºÐÀÚ°¡ ¾Æ´Ñ Ã¹ ±ÛÀÚ¸¦ Ã£´Â´Ù
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		//ÅäÅ«À» Ã£¾Æ º¤ÅÍ¿¡ Ãß°¡
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		//±¸ºÐÀÚ¸¦ ¶Ù¾î³Ñ´Â´Ù
		lastPos = str.find_first_not_of(delimiters, pos);
		//´ÙÀ½ ±¸ºÐÀÚ°¡ ¾Æ´Ñ ±ÛÀÚ¸¦ Ã£´Â´Ù
		pos = str.find_first_of(delimiters, lastPos);
	}
	itemData.push_back(tokens);
}

void itemManager::addItem(const char* strKey, ITEM _itemKind, bool _isFrame, int _indexX, int _indexY, TOOL _toolKind, SEED _seedKind, const char* _itemInfo, int _buyPrice, int _sellPrice)
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

void itemManager::addSeed(const char* strKey, ITEM _itemKind, int _indexX, int _indexY, SEED _seedKind, const char* _itemInfo, int _buyPrice, int _sellPrice, bool _isFrame)
{
	tagItem temp;
	temp.item_image = IMAGEMANAGER->findImage(strKey);
	temp.item_kind = _itemKind;
	temp.indexX = _indexX;
	temp.indexY = _indexY;
	temp.rc = RectMakeCenter(0, 0, 0, 0);
	temp.toolKind = TOOL_NONE;
	temp.seedKind = _seedKind;
	temp.itemName = _itemInfo;
	temp.item_info = _itemInfo;
	temp.buy_price = _buyPrice;
	temp.sell_price = _sellPrice;
	temp.amount = 1;
	temp.isFrame = _isFrame;
	_vItem.push_back(temp);
}

void itemManager::addFruit(const char* strKey, ITEM _itemKind, int _indexX, int _indexY, SEED _seedKind, const char* _itemInfo, int _buyPrice, int _sellPrice, bool _isFrame)
{
	tagItem temp;
	temp.item_image = IMAGEMANAGER->findImage(strKey);
	temp.item_kind = _itemKind;
	temp.indexX = _indexX;
	temp.indexY = _indexY;
	temp.rc = RectMakeCenter(0, 0, 0, 0);
	temp.seedKind = _seedKind;
	temp.itemName = _itemInfo;
	temp.item_info = _itemInfo;
	temp.buy_price = _buyPrice;
	temp.sell_price = _sellPrice;
	temp.amount = 1;
	temp.isFrame = _isFrame;
	_vItem.push_back(temp);
}

void itemManager::addObjectItem(const char* strKey, ITEM _itemKind, int _indexX, int _indexY, const char* _itemInfo, int _buyPrice, int _sellPrice, bool _isFrame)
{
	tagItem temp;
	temp.item_image = IMAGEMANAGER->findImage(strKey);
	temp.item_kind = _itemKind;
	temp.indexX = _indexX;
	temp.indexY = _indexY;
	temp.rc = RectMakeCenter(0, 0, 0, 0);
	temp.seedKind = SEED_NONE;
	temp.itemName = _itemInfo;
	temp.item_info = _itemInfo;
	temp.buy_price = _buyPrice;
	temp.sell_price = _sellPrice;
	temp.amount = 1;
	temp.isFrame = _isFrame;
	_vItem.push_back(temp);
}

void itemManager::addTool(const char* strKey, ITEM _itemKind, bool _isFrame, int _indexX, int _indexY, TOOL _toolKind, const char* _itemInfo, int _buyPrice, int _sellPrice)
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
	temp.itemName = _itemInfo;
	temp.item_info = _itemInfo;
	temp.buy_price = _buyPrice;
	temp.waterAmount = 0;
	temp.sell_price = _sellPrice;
	_vItem.push_back(temp);
}

void itemManager::addWeapon(const char* strKey, ITEM _itemKind, WEAPON _weaponKind, bool _isFrame, const char* _itemInfo, int _buyPrice, int _sellPrice)
{
	tagItem temp;
	temp.item_image = IMAGEMANAGER->findImage(strKey);
	temp.item_kind = _itemKind;
	temp.weaponKind = _weaponKind;
	temp.isFrame = _isFrame;
	temp.rc = RectMakeCenter(0, 0, 0, 0);
	temp.itemName = _itemInfo;
	temp.item_info = _itemInfo;
	temp.buy_price = _buyPrice;
	temp.sell_price = _sellPrice;
	_vItem.push_back(temp);
}

void itemManager::addOre(const char* strKey, ITEM _itemKind, bool _isFrame, int _indexX, int _indexY, const char* _itemInfo, int _buyPrice, int _sellPrice)
{
	tagItem temp;
	temp.item_image = IMAGEMANAGER->findImage(strKey);
	temp.item_kind = ITEM_ORE;
	temp.indexX = _indexX;
	temp.indexY = _indexY;
	temp.rc = RectMakeCenter(0, 0, 0, 0);
	temp.seedKind = SEED_NONE;
	temp.itemName = _itemInfo;
	temp.item_info = _itemInfo;
	temp.buy_price = _buyPrice;
	temp.sell_price = _sellPrice;
	temp.amount = 1;
	temp.isFrame = _isFrame;
	_vItem.push_back(temp);
}

void itemManager::addSprinkler(const char * strKey, ITEM _ITEMKIND, bool _isFrame, int _indexX, int _indexY, const char * _itemInfo, int _buyPrice, int _sellPrice)
{
	tagItem temp;
	temp.item_image = IMAGEMANAGER->findImage(strKey);
	temp.item_kind = ITEM_SPRINKLER1;
	temp.isFrame = _isFrame;
	temp.indexX = _indexX;
	temp.indexY = _indexY;
	temp.item_info = _itemInfo;
	temp.itemName = _itemInfo;
	temp.buy_price = _buyPrice;
	temp.sell_price = _sellPrice;
	_vItem.push_back(temp);
}

tagItem itemManager::findDropItem(ITEM itemKind, int indexX)
{
	for (auto iter : _vItem)
	{
		if (iter.item_kind == itemKind && iter.indexX == indexX)
		{
			return iter;
		}
	}
}

tagItem itemManager::findDropItem(ITEM itemKind, SEED seedKind)
{
	for (auto iter : _vItem)
	{
		if (iter.item_kind == itemKind && iter.seedKind == seedKind)
		{
			return iter;
		}
	}
}

tagItem itemManager::findItem(const char* strKey)
{
	for (auto iter : _vItem)
	{
		if (iter.item_info == strKey)
		{
			return iter;
		}
	}
}

tagItem itemManager::findItemByKind(ITEM itemKind, int indexX)
{
	for (auto iter : _vItem)
	{
		if (iter.item_kind == itemKind && iter.indexX == indexX)
		{
			return iter;
		}
	}
}

const char * itemManager::findItem(ITEM itemKind, SEED seedKind)
{
	if (itemKind == ITEM_SEED)
	{
		for (auto iter : _vItem)
		{
			if (iter.seedKind == seedKind && iter.item_kind == ITEM_SEED)
			{
				return iter.item_info;
			}
		}
		return nullptr;
	}
	else if (itemKind == ITEM_FRUIT)
	{
		for (auto iter : _vItem)
		{
			if (iter.seedKind == seedKind && iter.item_kind == ITEM_FRUIT)
			{
				return iter.item_info;
			}
		}
		return nullptr;
	}	
}

const char * itemManager::findItem(ITEM itemKind, int indexX)
{
	if (itemKind == ITEM_ORE)
	{
		if (indexX == 6) { return "±¸¸®Á¶°¢"; }
		if (indexX == 8) { return "Ã¶Á¶°¢"; }
		if (indexX == 12) { return "±ÝÁ¶°¢"; }
	}
	else if (itemKind == ITEM_DEBRIS)
	{
		if (indexX == 3) { return "µ¹"; }
		if (indexX == 4) { return "³ª¹«"; }
	}
}

const char * itemManager::findItem(ITEM itemKind)
{
	if (itemKind == ITEM_WOODENFENCE) { return "³ª¹«¿ïÅ¸¸®"; }
	if (itemKind == ITEM_STONEFENCE) { return "¼®Àç¿ïÅ¸¸®"; }
	
	return nullptr;
}

const char * itemManager::findItem(TOOL toolKind)
{
	for (auto iter : _vItem)
	{
		if (iter.toolKind == toolKind)
		{
			return iter.item_info;
		}
	}
	return nullptr;
}