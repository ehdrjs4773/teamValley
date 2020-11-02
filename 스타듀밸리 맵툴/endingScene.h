#pragma once
#include "gameNode.h"

class endingScene : public gameNode
{
public:
	int movieCount = 0;
	HWND g_hMCIWnd;
	HWND hWndAVI = 0;//AVI

public:
	HRESULT init();
	void update();
	void release();
	void render();
};
