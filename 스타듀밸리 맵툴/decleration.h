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
	ITEM_FRUIT,
	ITEM_DEBRIS,
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
	SEED_CATUS,
	SEED_PINETREE,
	SEED_MAPLETREE,
	SEED_OAKTREE
};

enum TOOL
{
	TOOL_NONE,
	TOOL_HOE, //ȣ��
	TOOL_AX,     //����
	TOOL_PICKAX, //���
	TOOL_SICKLE, //��
	TOOL_SWORD,  //��
	TOOL_KETTLE,  //������
	TOOL_FISHINGROD //���ô�
};

//�÷��̾�
enum STATE
{
	STAND,
	RUN,
	DIGGROUND,
	CUTDOWNTREE,
	CUTGRASS,
	BREAKSTONE,
	SPRAYWATER,
	FILLWATER,
	ATTACK,
	CARRY
};

enum DIRECTION
{
	RIGHT,
	LEFT,
	UP,
	DOWN
};

//����
enum TREETYPE
{
	TREE_NONE,
	TREE_OAK,
	TREE_MAPLE,
	TREE_PINE
};

//����
enum STOCKTYPE
{
	STOCK_MILKCOW,
	STOCK_OX,
	STOCK_SHEEP,
	STOCK_CHICKEN,
	STOCK_DUCK
};

struct tagItem {
	RECT rc;
	image* item_image;
	ITEM item_kind;
	TOOL toolKind;
	SEED seedKind;
	const char* item_info;
	int buy_price;
	int sell_price;
	int waterAmount;
	int indexX, indexY;
	int amount;
	bool isFrame;
};

struct tagItemOnField {
	tagItem item;
	RECT rc;
	float origCenterX, origCenterY;
	float centerX, centerY;
	float gravity;
	float speed;
	float angle;
	bool isOnGround;
};

struct tagTree {
	image* treeImage;
	TREETYPE treeType;
	int bodyIndexMinX, bodyIndexMaxX;
	int bodyIndexY;
	int hp;
	int grownLevel;
	bool isFullyGrown;
};

struct tagStock {
	STOCKTYPE stockType;
	DIRECTION direction;
	int speed;
	int aniCount;
	int indexX, indexY;
	float centerX, centerY;
	bool isFullyGrown;
	bool isMove;
};