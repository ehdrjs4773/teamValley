#pragma once
#include "gameNode.h"

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
	DOWN
};


struct tagPlayer
{

	RECT rc;
	//float x, y;
	//float speed;
	int count; 
	int index;

};

class player
{


	tagPlayer _player;

	STATE _pState;
	DIRECTION _pDirection;
	
	image* _right;
	image* _left;
	image* _up;
	image* _down;
	image* _cutdownTree;



	HRESULT init();
	void release();
	void update();
	void render();
	void playerMovement();
	void playerAnimation();


};

