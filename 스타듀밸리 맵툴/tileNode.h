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
//#define SAMPLETILEX 25
//#define SAMPLETILEY 80
#define SAMPLEDISPLAYX 20
#define SAMPLEDISPLAYY 20

//�������� ����� ��Ʈ��
enum CTRL
{
	CTRL_SAVE, CTRL_LOAD,
	CTRL_TERRAIN, CTRL_OBJECT, CTRL_ERASER
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
	TR_GROUND, TR_HACKED, TR_END
};

//������Ʈ
enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_TANK1, OBJ_TANK2,
	OBJ_NONE
};

//Ÿ�ϱ���ü
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

enum HACK_DIRRECTION
{
	HDIR_LEFT,
	HDIR_RIGHT,
	HDIR_UP,
	HDIR_DOWN,
	HDIR_UPLEFT,
	HDIR_UPRIGHT,
	HDIR_UPLEFTDOWN,
	HDIR_UPRIGHTDOWN,
	HDIR_DOWNLEFT,
	HDIR_DOWNRIGHT,
	HDIR_UPLEFTLEFT,
	HDIR_UPRIGHTRIGHT,
	HDIR_DOWNLEFTLEFT,
	HDIR_DOWNRIGHTRIGHT
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
