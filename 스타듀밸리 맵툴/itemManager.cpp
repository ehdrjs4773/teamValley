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
	addSeed("����", ITEM_SEED, 0, 0, SEED_PARSNIP, "�Ľ��� ����");
	addSeed("����", ITEM_SEED, 1, 0, SEED_GREENBEAN, "�ϵ��� ����");
	addSeed("����", ITEM_SEED, 2, 0, SEED_CAULIFLOWER, "�ݸ��ö�� ����");
	addSeed("����", ITEM_SEED, 3, 0, SEED_POTATO, "���� ����");
	addSeed("����", ITEM_SEED, 4, 0, SEED_GARLIC, "���� ����");
	addSeed("����", ITEM_SEED, 5, 0, SEED_KALE, "���� ����");
	addSeed("����", ITEM_SEED, 6, 0, SEED_BEET, "��Ʈ ����");
	addSeed("����", ITEM_SEED, 7, 0, SEED_MELON, "��� ����");
	addSeed("����", ITEM_SEED, 8, 0, SEED_BLUEJAZZ, "������� ����");
	addSeed("����", ITEM_SEED, 0, 1, SEED_SWEETGEMBERRY, "���޺������� ����");
	addSeed("����", ITEM_SEED, 1, 1, SEED_BLUEBERRY, "��纣�� ����");
	addSeed("����", ITEM_SEED, 2, 1, SEED_HOTPEPPER, "���� ����");
	addSeed("����", ITEM_SEED, 3, 1, SEED_WHEAT, "�� ����");
	addSeed("����", ITEM_SEED, 4, 1, SEED_RADISH, "�� ����");
	addSeed("����", ITEM_SEED, 5, 1, SEED_REDCABBAGE, "������� ����");
	addSeed("����", ITEM_SEED, 6, 1, SEED_STARFRUIT, "��Ÿ�ĸ��� ����");
	addSeed("����", ITEM_SEED, 7, 1, SEED_CORN, "������ ����");
	addSeed("����", ITEM_SEED, 8, 1, SEED_FAIRYROSE, "������� ����");
	addSeed("����", ITEM_SEED, 0, 2, SEED_EGGPLANT, "���� ����");
	addSeed("����", ITEM_SEED, 1, 2, SEED_ARTICHOKE, "��Ƽ��ũ ����");
	addSeed("����", ITEM_SEED, 2, 2, SEED_PUMPKIN, "ȣ�� ����");
	addSeed("����", ITEM_SEED, 3, 2, SEED_BOKCHOY, "û��ä ����");
	addSeed("����", ITEM_SEED, 4, 2, SEED_YAM, "���� ����");
	addSeed("����", ITEM_SEED, 5, 2, SEED_CRANBERRY, "ũ������ ����");
	addSeed("����", ITEM_SEED, 6, 2, SEED_STRAWBERRY, "���� ����");
	addSeed("����", ITEM_SEED, 7, 2, SEED_ANCIENTFRUIT, "������ ����");
	addSeed("����", ITEM_SEED, 8, 2, SEED_POPPY, "��ͺ� ����");
	addSeed("����", ITEM_SEED, 0, 3, SEED_TULIP, "ƫ�� ����");
	addSeed("����", ITEM_SEED, 1, 3, SEED_AMARANTH, "�Ƹ����� ����");
	addSeed("����", ITEM_SEED, 2, 3, SEED_GRAPE, "���� ����");
	addSeed("����", ITEM_SEED, 3, 3, SEED_HOPS, "ȩ ����");
	addSeed("����", ITEM_SEED, 3, 1, SEED_COFFEEBEAN, "Ŀ���� ����");
}

void itemManager::addWeapon()
{
	addWeapon("rusty_sword", ITEM_WEAPON, false, "�콼 �ҵ�");
	addWeapon("galaxy_sword", ITEM_WEAPON, false, "������ �ҵ�");
	addWeapon("pencil", ITEM_WEAPON, false, "����");
}

void itemManager::addTool()
{
	addTool("����", ITEM_TOOL, true, 0, 0, TOOL_HOE, "ȣ��");
	addTool("����", ITEM_TOOL, true, 1, 0, TOOL_PICKAX, "���");
	addTool("����", ITEM_TOOL, true, 2, 0, TOOL_AX, "����");
	addTool("����", ITEM_TOOL, true, 3, 0, TOOL_KETTLE, "������");
	addTool("����", ITEM_TOOL, true, 4, 0, TOOL_FISHINGROD, "���ô�");
	addTool("����", ITEM_TOOL, true, 5, 0, TOOL_SWORD, "Į");
}

void itemManager::addFruit()
{
	addFruit("����", ITEM_FRUIT, 0, 0, SEED_PARSNIP, "�Ľ���");
	addFruit("����", ITEM_FRUIT, 1, 0, SEED_CAULIFLOWER, "�ݸ��ö��");
	addFruit("����", ITEM_FRUIT, 2, 0, SEED_GARLIC, "����");
	addFruit("����", ITEM_FRUIT, 3, 0, SEED_RHUBARB, "��Ȳ");
	addFruit("����", ITEM_FRUIT, 4, 0, SEED_TOMATO, "�丶��");
	addFruit("����", ITEM_FRUIT, 5, 0, SEED_HOTPEPPER, "����");
	addFruit("����", ITEM_FRUIT, 6, 0, SEED_RADISH, "��");
	addFruit("����", ITEM_FRUIT, 7, 0, SEED_STARFRUIT, "��Ÿ�ĸ���");
	addFruit("����", ITEM_FRUIT, 8, 0, SEED_EGGPLANT, "����");
	addFruit("����", ITEM_FRUIT, 9, 0, SEED_PUMPKIN, "ȣ��");
	addFruit("����", ITEM_FRUIT, 10, 0, SEED_YAM, "����");
	addFruit("����", ITEM_FRUIT, 11, 0, SEED_BEET, "��Ʈ");
	addFruit("����", ITEM_FRUIT, 12, 0, SEED_ANCIENTFRUIT, "������");
	addFruit("����", ITEM_FRUIT, 13, 0, SEED_TULIP, "ƫ��");
	addFruit("����", ITEM_FRUIT, 14, 0, SEED_POPPY, "��ͺ�");
	addFruit("����", ITEM_FRUIT, 15, 0, SEED_SUNFLOWER, "�عٶ��");
	addFruit("����", ITEM_FRUIT, 0, 1, SEED_SWEETGEMBERRY, "���޺�������");
	addFruit("����", ITEM_FRUIT, 1, 1, SEED_STRAWBERRY, "����");
	addFruit("����", ITEM_FRUIT, 2, 1, SEED_GRAPE, "����");
	addFruit("����", ITEM_FRUIT, 3, 1, SEED_COFFEEBEAN, "Ŀ����");
	addFruit("����", ITEM_FRUIT, 4, 1, SEED_GREENBEAN, "�ϵ���");
	addFruit("����", ITEM_FRUIT, 5, 1, SEED_POTATO, "����");
	addFruit("����", ITEM_FRUIT, 6, 1, SEED_KALE, "����");
	addFruit("����", ITEM_FRUIT, 7, 1, SEED_MELON, "���");
	addFruit("����", ITEM_FRUIT, 8, 1, SEED_BLUEBERRY, "��纣��");
	addFruit("����", ITEM_FRUIT, 9, 1, SEED_WHEAT, "��");
	addFruit("����", ITEM_FRUIT, 10, 1, SEED_REDCABBAGE, "�������");
	addFruit("����", ITEM_FRUIT, 11, 1, SEED_CORN, "������");
	addFruit("����", ITEM_FRUIT, 12, 1, SEED_ARTICHOKE, "��Ƽ��ũ");
	addFruit("����", ITEM_FRUIT, 13, 1, SEED_BOKCHOY, "û��ä");
	addFruit("����", ITEM_FRUIT, 14, 1, SEED_CRANBERRY, "ũ������");
	addFruit("����", ITEM_FRUIT, 15, 1, SEED_BLUEJAZZ, "�������");
	addFruit("����", ITEM_FRUIT, 0, 2, SEED_SUMMERSPANGLE, "��������");
	addFruit("����", ITEM_FRUIT, 1, 2, SEED_FAIRYROSE, "�������");
	addFruit("����", ITEM_FRUIT, 2, 2, SEED_HOPS, "ȩ");
	addFruit("����", ITEM_FRUIT, 3, 2, SEED_AMARANTH, "�Ƹ�����");
	addFruit("����", ITEM_FRUIT, 4, 2, SEED_CATUS, "�����忭��");
}

void itemManager::addObject()
{
	addObjectItem("����", ITEM_DEBRIS, 5, 2, "��");
	addObjectItem("����", ITEM_DEBRIS, 6, 2, "����");
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
