#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "monster.h"

class mineScene : public gameNode
{
private:
	TCHAR saveName[MAX_PATH];

	//���� ������ �����ۿ� ����
	vector<tagItemOnField> _vItemOnField;
	RECT getItemRc;
	RECT sickleHitBox;

	tagTile _tile[TILEY][TILEX];
	int hpCount[TILEY][TILEX] = {};

	int currentFloor;

	int currentIndexX, currentIndexY;
	int mouseIndexX, mouseIndexY;

	int count = 0;
	int leftIndexX, leftIndexY;
	int rightIndexX, rightIndexY;
	int upIndexX, upIndexY;
	int downIndexX, downIndexY;

	//�ܼ� ���� ����Ʈ
	vector<monster*> monsterList;
	//�ʵ� �� ���� ����
	vector<monster*> vMonster;

	string str;
	string objStr;

	bool isShowRect;
	bool isLoad;
	int monsterCount;

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
	void useLadder();
	void useElevator(); 

	void renderMap();
	void renderTerrain();
	void renderObject(int i, int j);

	void setRandomObstacles();
	void setStone(int i, int j);
	void setWeed(int i, int j);
	void setOre(int i, int j);
	void getItem(tagItem item);
	void ejectItem();
	void dropItem(tagTile tile, const char* itemInfo);
	
	void skillClick();
	void skillSelect();

	void setMonsterList();
	void spawnMonster();
	void playerMonsterCollision();
};

