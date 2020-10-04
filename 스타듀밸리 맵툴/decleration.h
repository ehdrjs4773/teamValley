#pragma once

//������
enum ITEM
{
	ITEM_WEAPON,
	ITEM_TOOL,
	ITEM_BIGCRAFTABLE,
	ITEM_RESOURCE,
	ITEM_FORAGE,
	ITEM_ENDITEM,
	ITEM_SEED
};

enum SEED
{
	SEED_NONE,
	SEED_PARSNIP,
	SEED_CAULIFLOWER,
	SEED_GARLIC,
	SEED_RHUBARB,
	SEED_TOMATO,
	SEED_HOTPEPPER,
	SEED_RADISH,
	SEED_STARFRUIT,
	SEED_EGGPLANT,
	SEED_PUMPKIN,
	SEED_YAM,
	SEED_BEET,
	SEED_ANCIENTFRUIT,
	SEED_TULIP,
	SEED_POPPY,
	SEED_SUNFLOWER,
	SEED_SWEETGEMBERRY,
	SEED_STRAWBERRY,
	SEED_GRAPE,
	SEED_COFFEEBEAN,
	SEED_GREENBEAN,
	SEED_POTATO,
	SEED_KALE,
	SEED_MELON,
	SEED_BLUEBERRY,
	SEED_WHEAT,
	SEED_REDCABBAGE,
	SEED_CORN,
	SEED_ARTICHOKE,
	SEED_BOKCHOY,
	SEED_CRANBERRY,
	SEED_BLUEJAZZ,
	SEED_SUMMERSPANGLE,
	SEED_FAIRYROSE,
	SEED_HOPS,
	SEED_AMARANTH,
	SEED_CATUS

};

struct tagItem {

	RECT rc;
	image *item_image;
	ITEM item_kind;
	SEED seedKind;
	const char* item_info;
	int buy_price;
	int sell_price;
	int indexX, indexY;
};

//�÷��̾�
enum STATE
{
	digGround,
	cutdownTree,
	cutGrass,
	breakStone,
	pourwater,
	fillWater,
	attackMonster
};

enum DIRECTION
{
	RIGHT,
	LEFT,
	UP,
	DOWN,
	IDLE
};

enum TOOL
{
	TOOL_SHOVEL, //��
	TOOL_AX,     //����
	TOOL_PICKAX, //���
	TOOL_SICKLE, //��
	TOOL_SWORD,  //��
	TOOL_KETTLE,  //������
};





