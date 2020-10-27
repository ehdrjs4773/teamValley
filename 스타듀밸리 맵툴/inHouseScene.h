#pragma once
#include "gameNode.h"
#include "tileNode.h"

class inHouseScene : public gameNode
{
private:

	RECT playerBed;
	RECT yesBox;
	RECT noBox;

	int checkCount;

	bool isShowSleepingOption;

	TCHAR saveName[MAX_PATH];

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void playerMove();
	void blanket();

	void savePlayer();
};


