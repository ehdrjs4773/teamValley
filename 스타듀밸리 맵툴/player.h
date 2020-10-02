#pragma once
#include "singletonBase.h"
#include "tileNode.h"

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

enum PLAYERTOOL
{
	SHOVEL, //»ð
	AX,     //µµ³¢
	PICKAX, //°î±ªÀÌ
	SICKLE, //³´
	SWORD,  //°Ë
	KETTLE  //ÁÖÀüÀÚ

};

struct tagPlayer
{
	RECT rc;
	int count; 
	int index;
	float _playerX;
	float _playerY;
};

class player : public singletonBase<player>
{
private:
	RECT rc;
	float centerX, centerY;
	int currentX, currentY;
	int MouseIndexX, MouseIndexY;
	float speed;
	int count;
	int index;

	tagTile _tile[TILEY][TILEX];
	OBJ_TYPE objType;

	STATE _pState;
	DIRECTION _pDirection;
	PLAYERTOOL _pTool;
	
	image* move;
	image* state;
	
	image* _cutdownTree;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	float getCenterX() { return centerX; }
	float getCenterY() { return centerY; }

	DIRECTION getDirection() { return _pDirection; }
	RECT getRc() { return rc; }

	void playerMovement();
	void playerAnimation();
	void checkTile();
};

