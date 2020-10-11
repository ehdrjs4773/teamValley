#pragma once
#include "gameNode.h"
#include "tileNode.h"


class inGameScene : public gameNode
{
private:
	static TCHAR saveName[MAX_PATH];
	tagTile _tile[TILEY][TILEX]; //인게임화면(왼쪽화면)에 사용되는 타일 총 400개

	//땅에 떨어진 아이템용 벡터
	vector<tagItemOnField> _vItemOnField;

	float playerCenterX, playerCenterY;
	RECT getItemRc;
	RECT sickleHitBox;

	SEASON _currentSeason;

	int loadCount;
	string imageName;
	string objectImageName;

	int currentIndexX;
	int currentIndexY;
	int MouseIndexX, MouseIndexY;

	int leftIndexX, leftIndexY;
	int rightIndexX, rightIndexY;
	int upIndexX, upIndexY;
	int downIndexX, downIndexY;

	bool isShowRect;

public:
	inGameScene();
	

	HRESULT init();
	void release();
	void update();
	void render();

	void load();
	void setTileRect();
	void changeSeason(SEASON season);

	void renderMap();
	void renderObjects(int i, int j);
	void renderTree(int i, int j);

	void playerMove();
	void portal();

	void checkPlayerTile();
	void playerInteraction();
	void hackGround();
	void waterGround();
	void plantSeed();
	void harvest();
	void cutdownTree();
	void breakStone();
	void cutGrass();
	void setFence();

	void makeCropGrow();
	bool checkFullyGrown(tagTile tile);
	void getItem(tagItem item);
	void dropFruit(tagTile tile, SEED seedType);
	void dropItem(tagTile tile, const char* itemInfo);
	void ejectItem();

	void checkHacked();
	void checkFence();

	void setRandomObstacles();
	void changeGrass();

	void setCurrentSlotNumber(int mouseWheel);

	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

