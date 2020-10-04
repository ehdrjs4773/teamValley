#pragma once

//����ȭ�� Ÿ��
#define TILESIZE 16
#define TILEX 100
#define TILEY 100
#define DISPLAYX 30
#define DISPLAYY 30
#define TILESIZEX (TILEX * TILESIZE) //640
#define TILESIZEY (TILEY * TILESIZE) //640

//�̹��� Ÿ�� (ȭ�� ������ܿ� �ٿ����� ����Ÿ��)
#define SAMPLEDISPLAYX 20
#define SAMPLEDISPLAYY 20

//�������� ����� ��Ʈ��
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
//����
enum TERRAIN
{
	TR_GROUND, TR_HACKED, TR_WATER, TR_END
};

//������Ʈ
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

//Ÿ�ϱ���ü
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

//�̹��� Ÿ�� ����ü
struct tagSampleTile
{
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
};

//����Ÿ�� ����ü
struct tagCurrentTile
{
	int x, y;
};
