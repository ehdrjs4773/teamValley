#pragma once
#include "gameNode.h"
#include "tileNode.h"

class inGameScene : public gameNode
{
private:
	static TCHAR saveName[MAX_PATH];
	tagTile _tile[TILEY][TILEX]; //인게임화면(왼쪽화면)에 사용되는 타일 총 400개

	RECT playerRc;
	float playerCenterX, playerCenterY;

	SEASON _currentSeason;


public:

	HRESULT init();
	void release();
	void update();
	void render();

	void load();
	void setTileRect();

	void showEntireMap();

	void playerMove();

	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

