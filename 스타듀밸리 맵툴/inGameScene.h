#pragma once
#include "gameNode.h"
#include "tileNode.h"


class inGameScene : public gameNode
{
private:
	static TCHAR saveName[MAX_PATH];
	tagTile _tile[TILEY][TILEX]; //�ΰ���ȭ��(����ȭ��)�� ���Ǵ� Ÿ�� �� 400��

	//���� ������ �����ۿ� ����
	vector<tagItem*> vItemOnField;

	float playerCenterX, playerCenterY;

	SEASON _currentSeason;

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

	HRESULT init();
	void release();
	void update();
	void render();

	void load();
	void setTileRect();
	void changeSeason(SEASON season);

	void renderMap();

	void playerMove();

	void checkPlayerTile();
	void playerInteraction();
	void hackGround();
	void waterGround();
	void plantSeed();
	void harvest();
	void cutdownTree();
	void breakStone();
	void cutGrass();

	void makeCropGrow();
	bool checkFullyGrown(tagTile tile);
	void getItem(SEED seedType);

	void checkHacked();

	void setRandomObstacles();
	void changeGrass();

	void setCurrentSlotNumber(int mouseWheel);

	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

