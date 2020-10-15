#pragma once
#include "gameNode.h"
#include "tileNode.h"

class inHouseScene : public gameNode
{
private:

	RECT playerBed;
	RECT yesBox;
	RECT noBox;

	bool isShowSleepingOption;
	bool isclosed;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void playerMove();


};


