#pragma once

//������
enum ITEM
{
	ITEM_WEAPON,
	ITEM_TOOL,
	ITEM_BIGCRAFTABLE,
	ITEM_RESOURCE,
	ITEM_FORAGE,
	ITEM_SEED,
	ITEM_ENDITEM
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

enum TOOL
{
	TOOL_NONE,
<<<<<<< HEAD
=======
	TOOL_HOE, //ȣ��
>>>>>>> 33b353bfd3c2938572e2a07c2a36aed6d1d31ae1
	TOOL_SHOVEL, //��
	TOOL_AX,     //����
	TOOL_PICKAX, //���
	TOOL_SICKLE, //��
	TOOL_SWORD,  //��
<<<<<<< HEAD
	TOOL_KETTLE  //������
};


struct tagItem {
=======
	TOOL_KETTLE,  //������
	TOOL_FISHINGROD //���ô�
};

struct tagItem 
{
>>>>>>> 33b353bfd3c2938572e2a07c2a36aed6d1d31ae1

	RECT rc;
	image *item_image;
	bool isFrame;
	ITEM item_kind;
	TOOL toolKind;
	SEED seedKind;
	const char* item_info;
	int buy_price;
	int sell_price;
	int indexX, indexY;
};

//�÷��̾�
enum STATE
{
	DIGGROUND,
	CUTDOWNTREE,
	CUTGRASS,
	BREAKSTONE,
	SPRAYWATER,
	FILLWATER,
	ATTACK
};

enum DIRECTION
{
	RIGHT,
	LEFT,
	UP,
	DOWN,
	IDLE
};

<<<<<<< HEAD


=======
struct tagItem {
>>>>>>> 33b353bfd3c2938572e2a07c2a36aed6d1d31ae1

	RECT rc;
	image* item_image;
	ITEM item_kind;
	TOOL toolKind;
	SEED seedKind;
	const char* item_info;
	int buy_price;
	int sell_price;
	int indexX, indexY;
};