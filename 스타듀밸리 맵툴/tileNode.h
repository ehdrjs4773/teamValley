#pragma once

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
	CTRL_OBJECTDELETE
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
	TR_GROUND, TR_HACKED, TR_WATER, TR_END
};

//오브젝트
enum OBJECT
{
	OBJ_DESTRUCTIBE,
	OBJ_INDESTRUCTIBLE,
	OBJ_NONE
};

enum OBJ_OVERLAPPED
{
	OVR_NONE,
	OVR_OVER
};

enum OBJ_TYPE
{
	OTY_STONE,
	OTY_LARGESTONE,
	OTY_BRANCH,
	OTY_TREE,
	OTY_HARDTREE,
	OTY_CROP,
	OTY_WEED,
	OTY_GRASS,
	OTY_MONSTER,
	OTY_NONE
};

//타일구조체
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	OBJ_TYPE objType;
	OBJ_OVERLAPPED objOver;
	RECT rc;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
	int ovlFrameX;
	int ovlFrameY;
	int wetFrameX;
	int wetFrameY;

	bool isWet;
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
