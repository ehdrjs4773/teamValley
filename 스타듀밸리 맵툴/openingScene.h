#pragma once
#include "gameNode.h"


class openingScene : public gameNode
{
public:
	int movieCount = 0;
	HWND g_hMCIWnd;
	HWND hWndAVI = 0;//AVI
	const char* script[3];
	int script_count = 0;
	bool isTalk;
public: 
	HRESULT init();
	void update();
	void release();
	void render();
};
