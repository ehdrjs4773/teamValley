#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "monster.h"

class mineScene : public gameNode
{
private:
	TCHAR saveName[MAX_PATH];

	//땅에 떨어진 아이템용 벡터
	vector<tagItemOnField> _vItemOnField;
	RECT getItemRc;
	RECT sickleHitBox;

	tagTile _tile[TILEY][TILEX];
	int hpCount[TILEY][TILEX] = {};

	int currentFloor;
	
	int loadCount = 0;

	int currentIndexX, currentIndexY;
	int mouseIndexX, mouseIndexY;

	int count = 0;
	int leftIndexX, leftIndexY;
	int rightIndexX, rightIndexY;
	int upIndexX, upIndexY;
	int downIndexX, downIndexY;

	//단순 몬스터 리스트
	vector<monster*> monsterList;
	//필드 위 몬스터 벡터
	vector<monster*> vMonster;

	string str;
	string objStr;

	bool isShowRect;
	bool isLoad;
	int monsterCount;

	int MouseIndexX, MouseIndexY;
	bool _isTalk = true;
	int script_count;
	const char* script[3];
public:
	mineScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void savePlayer();

	void setCurrentSlotNumber(int mouseWheel);

	void loadMap();
	void setTileRect();

	void playerMove();
	void checkCurrentTile();

	void playerInteraction();
	void breakStone();
	void cutGrass();
	void useLadder(int i, int j);
	void useElevator(); 
	void eatFruit();

	void renderMap();
	void renderTerrain();
	void renderObject(int i, int j);

	void setRandomObstacles();
	void setStone(int i, int j);
	void setWeed(int i, int j);
	void setOre(int i, int j);
	void getItem(tagItem item);
	void ejectItem();
	void dropItem(tagTile tile, ITEM itemKind, int indexX);
	
	void skillClick();
	void skillSelect();


	void setMonsterList();
	void spawnMonster();
	void spawnSlime();
	void spawnRockCrab();
	void spawnBug();
	void spawnSerpent();

	void playerMonsterCollision();
	void wallMonsterColliison();
};

