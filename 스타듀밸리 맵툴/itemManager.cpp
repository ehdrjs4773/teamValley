#include "stdafx.h"
#include "itemManager.h"

HRESULT itemManager::init()
{
	IMAGEMANAGER->addImage("rusty_sword", "Images/sword/rusty_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("galaxy_sword", "Images/sword/galaxy_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pencil", "Images/sword/pencil.bmp", 55, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "Images/BMP/���Ѿ�����.bmp", 360, 160, 9, 4);
	IMAGEMANAGER->addFrameImage("����", "Images/BMP/����.bmp", 640, 120, 16, 3);
	IMAGEMANAGER->addFrameImage("����(��)", "Images/BMP/����(��).bmp", 256, 48, 16, 3);
	IMAGEMANAGER->addFrameImage("����", "Images/BMP/����.bmp", 360, 160, 9, 4);
	IMAGEMANAGER->addFrameImage("����", "Images/BMP/����2.bmp", 144, 640, 9, 40);
	IMAGEMANAGER->addFrameImage("�����潺", "Images/�潺/�����潺.bmp", 48, 352, 3, 22);
	IMAGEMANAGER->addFrameImage("���潺", "Images/�潺/���潺.bmp", 48, 352, 3, 22);
	IMAGEMANAGER->addFrameImage("�潺", "Images/�潺/�潺������.bmp", 80, 40, 2, 1);
	IMAGEMANAGER->addFrameImage("�潺(��)", "Images/�潺/�潺������(��).bmp", 32, 16, 2, 1);

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
	addSeed("����", ITEM_SEED, 0, 0, SEED_PARSNIP, "�Ľ��� ����",100,50);
	addSeed("����", ITEM_SEED, 1, 0, SEED_GREENBEAN, "�ϵ��� ����", 100, 50);
	addSeed("����", ITEM_SEED, 2, 0, SEED_CAULIFLOWER, "�ݸ��ö�� ����" , 100, 50);
	addSeed("����", ITEM_SEED, 3, 0, SEED_POTATO, "���� ����",100,50);
	addSeed("����", ITEM_SEED, 4, 0, SEED_GARLIC, "���� ����",100,50);
	addSeed("����", ITEM_SEED, 5, 0, SEED_KALE, "���� ����",100,50);
	addSeed("����", ITEM_SEED, 6, 0, SEED_BEET, "��Ʈ ����",100,50);
	addSeed("����", ITEM_SEED, 7, 0, SEED_MELON, "��� ����", 100, 50);
	addSeed("����", ITEM_SEED, 8, 0, SEED_BLUEJAZZ, "������� ����", 100, 50);
	addSeed("����", ITEM_SEED, 0, 1, SEED_SWEETGEMBERRY, "���޺������� ����", 100, 50);
	addSeed("����", ITEM_SEED, 1, 1, SEED_BLUEBERRY, "��纣�� ����", 100, 50);
	addSeed("����", ITEM_SEED, 2, 1, SEED_HOTPEPPER, "���� ����", 100, 50);
	addSeed("����", ITEM_SEED, 3, 1, SEED_WHEAT, "�� ����",200,100);
	addSeed("����", ITEM_SEED, 4, 1, SEED_RADISH, "�� ����", 200, 100);
	addSeed("����", ITEM_SEED, 5, 1, SEED_REDCABBAGE, "������� ����", 200, 100);
	addSeed("����", ITEM_SEED, 6, 1, SEED_STARFRUIT, "��Ÿ�ĸ��� ����", 200, 100);
	addSeed("����", ITEM_SEED, 7, 1, SEED_CORN, "������ ����", 200, 100);
	addSeed("����", ITEM_SEED, 8, 1, SEED_FAIRYROSE, "������� ����", 200, 100);
	addSeed("����", ITEM_SEED, 0, 2, SEED_EGGPLANT, "���� ����", 200, 100);
	addSeed("����", ITEM_SEED, 1, 2, SEED_ARTICHOKE, "��Ƽ��ũ ����", 200, 100);
	addSeed("����", ITEM_SEED, 2, 2, SEED_PUMPKIN, "ȣ�� ����", 200, 100);
	addSeed("����", ITEM_SEED, 3, 2, SEED_BOKCHOY, "û��ä ����", 200, 100);
	addSeed("����", ITEM_SEED, 4, 2, SEED_YAM, "���� ����", 200, 100);
	addSeed("����", ITEM_SEED, 5, 2, SEED_CRANBERRY, "ũ������ ����", 200, 100);
	addSeed("����", ITEM_SEED, 6, 2, SEED_STRAWBERRY, "���� ����", 200, 100);
	addSeed("����", ITEM_SEED, 7, 2, SEED_ANCIENTFRUIT, "������ ����", 200, 100);
	addSeed("����", ITEM_SEED, 8, 2, SEED_POPPY, "��ͺ� ����", 200, 100);
	addSeed("����", ITEM_SEED, 0, 3, SEED_TULIP, "ƫ�� ����", 200, 100);
	addSeed("����", ITEM_SEED, 1, 3, SEED_AMARANTH, "�Ƹ����� ����",300,150);
	addSeed("����", ITEM_SEED, 2, 3, SEED_GRAPE, "���� ����", 300, 150);
	addSeed("����", ITEM_SEED, 3, 3, SEED_HOPS, "ȩ ����", 300, 150);
	addSeed("����", ITEM_SEED, 4, 3, SEED_RANDOM, "���� ����", 300, 150);
	addSeed("����", ITEM_SEED, 3, 1, SEED_COFFEEBEAN, "Ŀ���� ����", 300, 150);
	addSeed("����", ITEM_SEED, 7, 2, SEED_PINETREE, "�ҳ��� ����", 300, 150);
	addSeed("����", ITEM_SEED, 8, 2, SEED_MAPLETREE, "��ǳ���� ����", 300, 150);
	addSeed("����", ITEM_SEED, 9, 2, SEED_OAKTREE, "������ ����", 300, 150);
}

void itemManager::addWeapon()
{
	addWeapon("rusty_sword", ITEM_WEAPON, false, "�콼 �ҵ�", 500, 250);
	addWeapon("galaxy_sword", ITEM_WEAPON, false, "������ �ҵ�",1000,500);
	addWeapon("pencil", ITEM_WEAPON, false, "����",100,50);
}

void itemManager::addTool()
{
	addTool("����", ITEM_TOOL, true, 0, 0, TOOL_HOE, "ȣ��", 300, 150);
	addTool("����", ITEM_TOOL, true, 1, 0, TOOL_PICKAX, "���", 300, 150);
	addTool("����", ITEM_TOOL, true, 2, 0, TOOL_AX, "����", 300, 150);
	addTool("����", ITEM_TOOL, true, 3, 0, TOOL_KETTLE, "������", 300, 150);
	addTool("����", ITEM_TOOL, true, 4, 0, TOOL_FISHINGROD, "���ô�", 300, 150);
	addTool("����", ITEM_TOOL, true, 5, 0, TOOL_SWORD, "Į", 300, 150);
}

void itemManager::addFruit()
{

	addFruit("����", ITEM_FRUIT, 0, 0, SEED_PARSNIP, "�Ľ���", 300, 150);
	addFruit("����", ITEM_FRUIT, 1, 0, SEED_CAULIFLOWER, "�ݸ��ö��", 300, 150);
	addFruit("����", ITEM_FRUIT, 2, 0, SEED_GARLIC, "����", 300, 150);
	addFruit("����", ITEM_FRUIT, 3, 0, SEED_RHUBARB, "��Ȳ", 300, 150);
	addFruit("����", ITEM_FRUIT, 4, 0, SEED_TOMATO, "�丶��", 300, 150);
	addFruit("����", ITEM_FRUIT, 5, 0, SEED_HOTPEPPER, "����", 300, 150);
	addFruit("����", ITEM_FRUIT, 6, 0, SEED_RADISH, "��", 300, 150);
	addFruit("����", ITEM_FRUIT, 7, 0, SEED_STARFRUIT, "��Ÿ�ĸ���", 300, 150);
	addFruit("����", ITEM_FRUIT, 8, 0, SEED_EGGPLANT, "����", 300, 150);
	addFruit("����", ITEM_FRUIT, 9, 0, SEED_PUMPKIN, "ȣ��", 300, 150);
	addFruit("����", ITEM_FRUIT, 10, 0, SEED_YAM, "����", 300, 150);
	addFruit("����", ITEM_FRUIT, 11, 0, SEED_BEET, "��Ʈ", 300, 150);
	addFruit("����", ITEM_FRUIT, 12, 0, SEED_ANCIENTFRUIT, "������", 300, 150);
	addFruit("����", ITEM_FRUIT, 13, 0, SEED_TULIP, "ƫ��", 300, 150);
	addFruit("����", ITEM_FRUIT, 14, 0, SEED_POPPY, "��ͺ�", 300, 150);
	addFruit("����", ITEM_FRUIT, 15, 0, SEED_SUNFLOWER, "�عٶ��", 300, 150);
	addFruit("����", ITEM_FRUIT, 0, 1, SEED_SWEETGEMBERRY, "���޺�������", 300, 150);
	addFruit("����", ITEM_FRUIT, 1, 1, SEED_STRAWBERRY, "����", 300, 150);
	addFruit("����", ITEM_FRUIT, 2, 1, SEED_GRAPE, "����", 500, 250);
	addFruit("����", ITEM_FRUIT, 3, 1, SEED_COFFEEBEAN, "Ŀ����", 500, 250);
	addFruit("����", ITEM_FRUIT, 4, 1, SEED_GREENBEAN, "�ϵ���", 500, 250);
	addFruit("����", ITEM_FRUIT, 5, 1, SEED_POTATO, "����", 500, 250);
	addFruit("����", ITEM_FRUIT, 6, 1, SEED_KALE, "����", 500, 250);
	addFruit("����", ITEM_FRUIT, 7, 1, SEED_MELON, "���", 500, 250);
	addFruit("����", ITEM_FRUIT, 8, 1, SEED_BLUEBERRY, "��纣��", 500, 250);
	addFruit("����", ITEM_FRUIT, 9, 1, SEED_WHEAT, "��", 500, 250);
	addFruit("����", ITEM_FRUIT, 10, 1, SEED_REDCABBAGE, "�������", 500, 250);
	addFruit("����", ITEM_FRUIT, 11, 1, SEED_CORN, "������", 750, 370);
	addFruit("����", ITEM_FRUIT, 12, 1, SEED_ARTICHOKE, "��Ƽ��ũ", 750, 370);
	addFruit("����", ITEM_FRUIT, 13, 1, SEED_BOKCHOY, "û��ä", 750, 370);
	addFruit("����", ITEM_FRUIT, 14, 1, SEED_CRANBERRY, "ũ������", 750, 370);
	addFruit("����", ITEM_FRUIT, 15, 1, SEED_BLUEJAZZ, "�������", 750, 370);
	addFruit("����", ITEM_FRUIT, 0, 2, SEED_SUMMERSPANGLE, "��������", 750, 370);
	addFruit("����", ITEM_FRUIT, 1, 2, SEED_FAIRYROSE, "�������", 750, 370);
	addFruit("����", ITEM_FRUIT, 2, 2, SEED_HOPS, "ȩ", 750, 370);
	addFruit("����", ITEM_FRUIT, 3, 2, SEED_AMARANTH, "�Ƹ�����", 750, 370);
	addFruit("����", ITEM_FRUIT, 4, 2, SEED_CATUS, "�����忭��", 750, 370);
}

void itemManager::addObject()
{
	addObjectItem("����", ITEM_DEBRIS, 5, 2, "��", 1000, 500);
	addObjectItem("����", ITEM_DEBRIS, 6, 2, "����", 1000, 500);
	addObjectItem("����", ITEM_DEBRIS, 10, 2, "�ܴ��ѳ���", 1000, 500);
	addObjectItem("�潺", ITEM_WOODENFENCE, 0, 0, "������Ÿ��", 1000, 500);
	addObjectItem("�潺", ITEM_STONEFENCE, 1, 0, "�����Ÿ��", 1000, 500);
	addObjectItem("�潺", ITEM_WOODENFENCEDOOR, 0, 0, "������Ÿ����", 1000, 500);
	addObjectItem("�潺", ITEM_STONEFENCEDOOR, 1, 0, "�����Ÿ����", 1000, 500);
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
