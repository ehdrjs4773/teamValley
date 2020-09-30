#pragma once
#include "singletonBase.h"

enum STATE
{
	digGround,
	cutdownTree,
	cutGrass,
	fillWater,
};

enum DIRECTION
{
	RIGHT,
	LEFT,
	UP,
	DOWN,
	IDLE
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
	float speed;
	int count;
	int index;

	STATE _pState;
	DIRECTION _pDirection;
	
	image* move;
	
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
};

