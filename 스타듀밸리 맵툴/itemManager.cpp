#include "stdafx.h"
#include "itemManager.h"

HRESULT itemManager::init()
{
	IMAGEMANAGER->addImage("rusty_sword", "Images/sword/rusty_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("galaxy_sword", "Images/sword/galaxy_sword.bmp", 55, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pencil", "Images/sword/pencil.bmp", 55, 45, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "Images/BMP/���Ѿ�����.bmp", 320, 80, 8, 2);
	IMAGEMANAGER->addFrameImage("����hold", "Images/BMP/���Ѿ�����small.bmp", 128, 32, 8, 2);
	IMAGEMANAGER->addFrameImage("����", "Images/BMP/����.bmp", 320, 120, 8, 3);
	IMAGEMANAGER->addFrameImage("����(��)", "Images/BMP/����small.bmp", 128, 48, 8, 3);
	IMAGEMANAGER->addFrameImage("����", "Images/BMP/����.bmp", 360, 160, 9, 4);
	IMAGEMANAGER->addFrameImage("����", "Images/BMP/����2.bmp", 144, 640, 9, 40);
	IMAGEMANAGER->addImage("��_��", "Images/skill/��_��.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����Ȧ_��", "Images/skill/����Ȧ_��.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������ũ_��", "Images/skill/������ũ_��.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̾_��", "Images/skill/���̾_��.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����_��", "Images/skill/����_��.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "Images/BMP/����.bmp", 256, 80, 16, 5);
	IMAGEMANAGER->addFrameImage("����������", "Images/BMP/����������.bmp", 640, 200, 16, 5);
	IMAGEMANAGER->addFrameImage("������Ŭ��", "Images/BMP/������Ŭ��.bmp", 16, 48, 1, 3);
	IMAGEMANAGER->addFrameImage("������Ŭ��������", "Images/BMP/������Ŭ��������.bmp", 40, 120, 1, 3);
	IMAGEMANAGER->addFrameImage("�潺", "Images/�潺/�潺������.bmp", 80, 40, 2, 1);
	IMAGEMANAGER->addFrameImage("���ͼ���", "Images/monster/���ͼ���.bmp", 160, 40, 4, 1);
	IMAGEMANAGER->addFrameImage("���ͼ���small", "Images/monster/���ͼ���small.bmp", 64, 16, 4, 1);

	readItemCSV();

	addCSVItem();

	addSkill();
	addWeapon();
	addTool();
	addOre();

	//addSprinkler("������Ŭ��������", ITEM_SPRINKLER1, true, 0, 0, "�⺻������Ŭ��");
	//addSprinkler("������Ŭ��������", ITEM_SPRINKLER2, true, 0, 1, "��ȭ������Ŭ��");
	//addSprinkler("������Ŭ��������", ITEM_SPRINKLER3, true, 0, 2, "���޽�����Ŭ��");

	return S_OK;
}

void itemManager::release()
{
}

void itemManager::addSeed()
{
	//addSeed("����", ITEM_SEED, 0, 0, SEED_HOPS, "ȩ ����", 25, 15);
	//addSeed("����", ITEM_SEED, 1, 0, SEED_RADISH, "�� ����", 40, 25);
	//addSeed("����", ITEM_SEED, 2, 0, SEED_WHEAT, "�� ����", 10, 5);
	//addSeed("����", ITEM_SEED, 3, 0, SEED_TOMATO, "�丶�� ����", 50, 40);
	//addSeed("����", ITEM_SEED, 4, 0, SEED_GREENBEAN, "�ϵ��� ����", 40, 30);
	//addSeed("����", ITEM_SEED, 5, 0, SEED_MELON, "��� ����", 80, 60);
	//addSeed("����", ITEM_SEED, 6, 0, SEED_POPPY, "��ͺ� ����", 140, 120);
	//addSeed("����", ITEM_SEED, 7, 0, SEED_SUMMERSPANGLE, "�������� ����", 90, 75);
	//addSeed("����", ITEM_SEED, 0, 1, SEED_HOTPEPPER, "���� ����", 90, 75);
	//addSeed("����", ITEM_SEED, 1, 1, SEED_CORN, "������ ����", 155, 130);
	//addSeed("����", ITEM_SEED, 2, 1, SEED_BLUEBERRY, "���纣�� ����", 80, 60);
	//addSeed("����", ITEM_SEED, 3, 1, SEED_SUNFLOWER, "�عٶ�� ����", 80, 60);
	//addSeed("����", ITEM_SEED, 4, 1, SEED_REDCABBAGE, "������� ����", 100, 80);
	//addSeed("����", ITEM_SEED, 5, 1, SEED_GRAPE, "���� ����", 150, 125);
	//addSeed("����", ITEM_SEED, 6, 1, SEED_STARFRUIT, "��Ÿ�ĸ��� ����", 400, 250);

	//addSeed("����", ITEM_SEED, 0, 2, SEED_PINETREE, "�ҳ��� ����", 0, 20);
	//addSeed("����", ITEM_SEED, 1, 2, SEED_MAPLETREE, "��ǳ���� ����", 0, 20);
	//addSeed("����", ITEM_SEED, 2, 2, SEED_OAKTREE, "������ ����", 0, 20);
}

void itemManager::addWeapon()
{
	addWeapon("rusty_sword", ITEM_WEAPON, WEAPON_RUSTYSWORD, false, "�콼 �ҵ�", 500, 250);
	addWeapon("galaxy_sword", ITEM_WEAPON, WEAPON_GALAXYSWORD, false, "������ �ҵ�",1000,500);
	addWeapon("pencil", ITEM_WEAPON, WEAPON_PENCIL, false, "����",100,50);
}

void itemManager::addTool()
{
	addTool("����", ITEM_TOOL, true, 0, 0, TOOL_HOE, "ȣ��", 300, 150);
	addTool("����", ITEM_TOOL, true, 1, 0, TOOL_PICKAX, "���", 300, 150);
	addTool("����", ITEM_TOOL, true, 2, 0, TOOL_AX, "����", 300, 150);
	addTool("����", ITEM_TOOL, true, 3, 0, TOOL_KETTLE, "������", 300, 150);
	addTool("����", ITEM_TOOL, true, 4, 0, TOOL_FISHINGROD, "���ô�", 300, 150);
	addTool("����", ITEM_TOOL, true, 6, 0, TOOL_SICKLE, "��", 300, 150);
}

void itemManager::addFruit()
{
	//addFruit("����", ITEM_FRUIT, 0, 0, SEED_HOPS, "ȩ", 0, 20);
	//addFruit("����", ITEM_FRUIT, 1, 0, SEED_RADISH, "��", 0, 110);
	//addFruit("����", ITEM_FRUIT, 2, 0, SEED_WHEAT, "��", 0, 35);
	//addFruit("����", ITEM_FRUIT, 3, 0, SEED_TOMATO, "�丶��", 0, 60);
	//addFruit("����", ITEM_FRUIT, 4, 0, SEED_GREENBEAN, "�ϵ���", 0, 35);
	//addFruit("����", ITEM_FRUIT, 5, 0, SEED_MELON, "���", 0, 250);
	//addFruit("����", ITEM_FRUIT, 6, 0, SEED_POPPY, "��ͺ�", 0, 275);
	//addFruit("����", ITEM_FRUIT, 7, 0, SEED_SUMMERSPANGLE, "��������", 0, 220);
	//addFruit("����", ITEM_FRUIT, 0, 1, SEED_HOTPEPPER, "����", 0, 70);
	//addFruit("����", ITEM_FRUIT, 1, 1, SEED_CORN, "������", 0, 80);
	//addFruit("����", ITEM_FRUIT, 2, 1, SEED_BLUEBERRY, "���纣��", 0, 30); 
	//addFruit("����", ITEM_FRUIT, 3, 1, SEED_SUNFLOWER, "�عٶ��", 0, 250);
	//addFruit("����", ITEM_FRUIT, 4, 1, SEED_REDCABBAGE, "�������", 0, 280);
	//addFruit("����", ITEM_FRUIT, 5, 1, SEED_GRAPE, "����", 0, 100);
	//addFruit("����", ITEM_FRUIT, 6, 1, SEED_STARFRUIT, "��Ÿ�ĸ���", 0, 750);
}

void itemManager::addObject()
{
	//addObjectItem("����", ITEM_DEBRIS, 3, 2, "��", 0, 5);
	//addObjectItem("����", ITEM_DEBRIS, 4, 2, "����", 0, 5);
	//addObjectItem("�潺", ITEM_WOODENFENCE, 0, 0, "������Ÿ��", 0, 5);
	//addObjectItem("�潺", ITEM_STONEFENCE, 1, 0, "�����Ÿ��", 0, 5);
}

void itemManager::addSkill()
{
	addWeapon("����_��", ITEM_SKILL, WEAPON_EXPLOSION, false, "����_��", 500, 250);
	addWeapon("������ũ_��", ITEM_SKILL, WEAPON_SPIKES, false, "������ũ_��", 1000, 500);
	addWeapon("��_��", ITEM_SKILL, WEAPON_FIRE, false, "��_��", 1500, 750);
	addWeapon("����Ȧ_��", ITEM_SKILL, WEAPON_BLACKHOLE, false, "����Ȧ_��", 2000, 1000);
	addWeapon("���̾_��", ITEM_SKILL, WEAPON_FIREBALL, false, "���̾_��", 3000, 1500);
}

void itemManager::addOre()
{
	//addOre("����", ITEM_ORE, true, 6, 3, "��������");
	//addOre("����", ITEM_ORE, true, 8, 3, "ö����");
	//addOre("����", ITEM_ORE, true, 12, 3, "������");
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
			temp.grow = (atoi)(itemData[i][14].c_str());
			temp.exp = (atoi)(itemData[i][15].c_str());
			temp.hpRecover = (atoi)(itemData[i][16].c_str());
			temp.energyRecover = (atoi)(itemData[i][17].c_str());
			temp.grade = (atoi)(itemData[i][18].c_str());

			_vItem.push_back(temp);
	}
}

void itemManager::stringTokenize(const string & str, vector<string>& tokens, const string & delimiters)
{
	//�� ù ���ڰ� �������� ��� ����
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	//�����ڰ� �ƴ� ù ���ڸ� ã�´�
	string::size_type pos = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		//��ū�� ã�� ���Ϳ� �߰�
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		//�����ڸ� �پ�Ѵ´�
		lastPos = str.find_first_not_of(delimiters, pos);
		//���� �����ڰ� �ƴ� ���ڸ� ã�´�
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
	temp.itemName = _itemInfo;
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
	temp.amount = 1;
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
	temp.amount = 1;
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
	temp.amount = 1;
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

tagItem itemManager::findItem(WEAPON weaponKind)
{
	for (auto iter : _vItem)
	{
		if (iter.weaponKind == weaponKind)
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
		if (indexX == 6) { return "��������"; }
		if (indexX == 8) { return "ö����"; }
		if (indexX == 12) { return "������"; }
	}
	else if (itemKind == ITEM_DEBRIS)
	{
		if (indexX == 3) { return "��"; }
		if (indexX == 4) { return "����"; }
	}
}

const char * itemManager::findItem(ITEM itemKind)
{
	if (itemKind == ITEM_WOODENFENCE) { return "������Ÿ��"; }
	if (itemKind == ITEM_STONEFENCE) { return "�����Ÿ��"; }
	
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