#pragma once

//아이템
enum ITEM
{
	ITEM_NONE,
	ITEM_WEAPON,
	ITEM_TOOL,
	ITEM_BIGCRAFTABLE,
	ITEM_RESOURCE,
	ITEM_FORAGE,
	ITEM_SEED,
	ITEM_BOX,
	ITEM_FRUIT,
	ITEM_DEBRIS,
	ITEM_SKILL,
	ITEM_ORE,
	ITEM_SPRINKLER1,
	ITEM_SPRINKLER2,
	ITEM_SPRINKLER3,
	ITEM_WOODENFENCE,
	ITEM_STONEFENCE,
	ITEM_BEEFARM,
	ITEM_PICKLEDBARREL,
	ITEM_FEEDBUCKET,
	ITEM_SCARECROW,
	ITEM_BLASTFURNACE,
	ITEM_EQUIPMENT,
	ITEM_MATERIAL,
	ITEM_INGOT,
	ITEM_ENDITEM
};

enum WEAPON
{
	WEAPON_NONE,
	WEAPON_RUSTYSWORD,
	WEAPON_GALAXYSWORD,
	WEAPON_PENCIL,
	WEAPON_EXPLOSION,
	WEAPON_SPIKES,
	WEAPON_FIRE,
	WEAPON_SHIELD,
	WEAPON_BLACKHOLE,
	WEAPON_FIREBALL
};

enum SEED
{
	SEED_NONE,
	SEED_TOMATO,
	SEED_HOTPEPPER,
	SEED_RADISH,
	SEED_STARFRUIT,
	SEED_POPPY,
	SEED_SUNFLOWER,
	SEED_GRAPE,
	SEED_GREENBEAN,
	SEED_MELON,
	SEED_BLUEBERRY,
	SEED_WHEAT,
	SEED_REDCABBAGE,
	SEED_CORN,
	SEED_SUMMERSPANGLE,
	SEED_HOPS,
	SEED_PINETREE,
	SEED_MAPLETREE,
	SEED_OAKTREE,
	SEED_RANDOM
};

enum TOOL
{
	TOOL_NONE,
	TOOL_HOE, //호미
	TOOL_AX,     //도끼
	TOOL_PICKAX, //곡괭이
	TOOL_SICKLE, //낫
	TOOL_SWORD,  //검
	TOOL_KETTLE,  //주전자
	TOOL_FISHINGROD //낚시대
};

enum SCARECROW
{
	SCARECROW_1=1,
	SCARECROW_2,
	SCARECROW_3,
	SCARECROW_4,
	SCARECROW_5,
	SCARECROW_6,
	SCARECROW_7,
	SCARECROW_8,
	SCARECROW_9,//일반
	SCARECROW_10,
	SCARECROW_11,
	SCARECROW_12 //이벤트 
};

//플레이어
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
	CARRY,
	CARRYSTAND,
	INVEN,
	FARM,
	P_SKILL_EXPLOSION,
	P_SKILL_SPIKES,
	P_SKILL_FIRE,
	P_SKILL_SHIELD,
	P_SKILL_BLACKHOLE,
	P_SKILL_FIRE_BALL,
	P_SKILL_END
};

enum DIRECTION
{
	RIGHT,
	LEFT,
	UP,
	DOWN,
	NONE
};

//나무
enum TREETYPE
{
	TREE_NONE,
	TREE_OAK,
	TREE_MAPLE,
	TREE_PINE
};

//가축
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

//날씨
enum WEATHER
{
	SUNNY,
	RAIN,
	HEAVYRAIN,
	WINDY,
	SNOW
};

//요일
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

//이펙트 종류
enum EFFECT
{
	EFT_PINETREECOL,
	EFT_MAPLETREECOL,
	EFT_OAKTREECOL,
	EFT_SKILL_EXPLOSION,
	EFT_SKILL_SPIKES,
	EFT_SKILL_FIRE,
	EFT_SKILL_SHIELD,
	EFT_SKILL_BLACKHOLE,
	EFT_SKILL_FIRE_BALL
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

//몬스터
enum MONTYPE
{
	MTYPE_NONE,
	MTYPE_SLIME,
	MTYPE_BUG,
	MTYPE_ROCKCRAB,
	MTYPE_SERPENT
};

enum MONSTATE
{
	MSTATE_IDLE,
	MSTATE_MOVE,
	MSTATE_ATTACK
};

struct tagItem {
	RECT rc;
	image* item_image;
	ITEM item_kind;
	TOOL toolKind;
	SEED seedKind;
	SCARECROW scarecrowKind;
	WEAPON weaponKind = WEAPON_NONE;
	const char* itemName;
	const char* item_info;
	int buy_price;
	int sell_price;
	int waterAmount;
	int indexX, indexY;
	int amount;
	int grow;
	int exp;
	int hpRecover;
	int energyRecover;
	int grade;
	bool isFrame;
};

struct tagSaveItem {
	RECT rc;
	ITEM item_kind;
	TOOL toolKind;
	SEED seedKind;
	const char* itemName;

	int buy_price;
	int sell_price;
	int waterAmount;
	int indexX, indexY;
	int amount;
	int hpRecover;
	int energyRecover;
	int grow;
	int exp;
	int grade;
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
	RECT rc;
	int count;
	int indexX, indexY;
	int maxIndex;
	int skillDamage;
	float centerX, centerY;
	float angle;
};

struct tagSkill
{
	image* image;
	RECT rc;
	SKILL skillKind;
	POINT pos;
	const char * skill_info;
	int indexX, indexY;
	int maxindex;
	bool isActive;
};

struct tagScript
{
	image* image;
	const char* name;
	const char* script;
};

enum NPC_KIND {

	ITEM_NPC = 1,
	SKILL_NPC
};