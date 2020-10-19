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
	ITEM_BOX,
	ITEM_FRUIT,
	ITEM_DEBRIS,
	ITEM_WOODENFENCE,
	ITEM_WOODENFENCEDOOR,
	ITEM_STONEFENCE,
	ITEM_STONEFENCEDOOR,
	ITEM_SKILL,
	ITEM_ORE,
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
	SEED_OAKTREE,
	SEED_RANDOM
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
	CARRY,
	CARRYSTAND,
	INVEN,
	FARM,
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
	STOCK_WHITECOW,
	STOCK_BROWNCOW,
	STOCK_SHEEP,
	STOCK_BROWNCHICKEN,
	STOCK_WHITECHICKEN,
	STOCK_DUCK
};

enum STOCKSTATE
{
	SS_MOVE,
	SS_STAND,
	SS_EAT,
	SS_HAPPY
};

enum MAP
{
	MAP_FARM,
	MAP_HOUSE,
	MAP_BARN,
	MAP_CHICKENHOUSE,
	MAP_SHOP,
	MAP_MINE
};

//����
enum WEATHER
{
	SUNNY,
	RAIN,
	HEAVYRAIN,
	WINDY,
	SNOW
};

//����
enum DAYOFWEEK
{
	MON,
	TUE,
	WED,
	THU,
	FRI,
	SAT,
	SUN
};

//����Ʈ ����
enum EFFECT
{
	EFT_PINETREECOL,
	EFT_MAPLETREECOL,
	EFT_OAKTREECOL
};

enum SKILL
{
	SKILL_EXPLOSION,
	SKILL_SPIKES,
	SKILL_FIRE,
	SKILL_SHIELD,
	SKILL_BLACKHOLE,
	SKILL_FIRE_BALL,
	SKILL_END
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
	int bodyIndexX;
	int bodyIndexY;
	int hp;
};

struct tagStock {
	STOCKTYPE stockType;
	DIRECTION direction;
	STOCKSTATE state;
	float speed;
	int aniCount;
	int indexX, indexY;
	float centerX, centerY;
	bool isFullyGrown;
	bool isSheared;
	bool isMove;
};

struct tagEffect 
{
	image* image;
	EFFECT effectType;
	DIRECTION dir;
	int count;
	int indexX, indexY;
	int maxIndex;
	int centerX, centerY;
};

enum NPC_KIND {

	ITEM_NPC = 1,
	SKILL_NPC
};