#pragma once
#include "decleration.h"

//게임화면 타일
#define TILESIZE 16
#define TILEX 100
#define TILEY 100
#define DISPLAYX 30
#define DISPLAYY 30
#define TILESIZEX (TILEX * TILESIZE) //640
#define TILESIZEY (TILEY * TILESIZE) //640

//이미지 타일 (화면 우측상단에 붙여놓을 샘플타일)
#define SAMPLEDISPLAYX 20
#define SAMPLEDISPLAYY 20

//맵툴에서 사용할 컨트롤
enum CTRL
{
	CTRL_SAVE, CTRL_LOAD,
	CTRL_TERRAIN, CTRL_OBJECT, CTRL_ERASER,
	CTRL_OBJECTDELETE, 
	CTRL_OBJECT2,
	CTRL_MINETERRAIN,
	CTRL_MINEOBJECT
};

enum MINEMAP
{
	MINE_NORMAL,
	MINE_NORMALDARK,
	MINE_FROST,
	MINE_FROSTDARK
};

enum SEASON
{
	SPRING,
	SUMMER,
	AUTUMN,
	WINTER,
};

//지형
enum TERRAIN
{
	TR_GROUND, TR_GRASS, TR_SOIL, TR_HACKED, TR_WATER, TR_END
};

//오브젝트
enum OBJECT
{
	OBJ_NONE,
	OBJ_SEED,
	OBJ_DESTRUCTIBLE,
	OBJ_INDESTRUCTIBLE,
	OBJ_BUILDING,
	OBJ_EQUIPMENT,
};

enum OBJ_OVERLAPPED
{
	OVR_NONE,
	OVR_OVER
};

enum OBJ_TYPE
{
	OTY_NONE,
	OTY_STONE,
	OTY_LARGESTONE,
	OTY_BRANCH,
	OTY_TREE,
	OTY_TREETRUNK,
	OTY_HARDTREE,
	OTY_CROP,
	OTY_WEED,
	OTY_GRASS,
	OTY_MONSTER,
	OTY_WOODENFENCE,
	OTY_WOODENFENCEDOOROPEN,
	OTY_WOODENFENCEDOOR,
	OTY_STONEFENCE,
	OTY_STONEFENCEDOOR,
	OTY_STONEFENCEDOOROPEN,
	OTY_ORE,
	OTY_SPRINKLER,
	OTY_WELL,
	OTY_BOX,
	OTY_FEEDBUCKET,
	OTY_SCARECROW,
	OTY_PICKLEDBARREL,
	OTY_BEEFARM,
	OTY_BLASTFURNACE,
	OTY_MINELADDER

};

enum PORTAL
{
	PT_NONE,
	PT_HOUSE,
	PT_CHICKENHOUSE,
	PT_BARN,
	PT_SHOP,
	PT_MINE
};

//타일구조체
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	OBJ_TYPE objType;
	OBJ_OVERLAPPED objOver;
	SEED seedType;
	RECT rc;
	tagTree tree;
	PORTAL portal;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
	int ovlFrameX;
	int ovlFrameY;
	int wetFrameX;
	int wetFrameY;
	int grownLevel;

	bool isWet;
	bool isFullyGrown;
};

//이미지 타일 구조체
struct tagSampleTile
{
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
};

//현재타일 구조체
struct tagCurrentTile
{
	int x, y;
};
