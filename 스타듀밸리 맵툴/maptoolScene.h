#pragma once
#include "gameNode.h"
#include "tileNode.h"

class maptoolScene : public gameNode
{
private:
	static TCHAR saveName[MAX_PATH];
	static bool _isSave;

	tagTile _tile[TILEY][TILEX]; //인게임화면(왼쪽화면)에 사용되는 타일 총 400개
	std::vector<std::vector<tagTile>> _sampleTile;
	std::vector<tagTile> _sampleTileX;
	tagCurrentTile _currentTile; //현재타일
	
	RECT _rcSave;		//세이브
	RECT _rcLoad;		//로드
	RECT _rcTerrain;	//지형
	RECT _rcObject;		//오브젝트
	RECT _rcEraser;		//지우개 (오브젝트만 지운다, 지형은 덮어씌운다)
	RECT _rcSpring;
	RECT _rcSummer;
	RECT _rcAutumn;
	RECT _rcWinter;
	RECT _rcobjectDelete;

	RECT horScroll;
	RECT vertScroll;
	RECT sampleHorScroll;
	RECT sampleVertScroll;

	CTRL _ctrlSelect;	//현재 어떤 컨트롤 상태인지
	CTRL _prevCtrl;		//지우개 눌렀을때 샘플 사라지지 않게 하기 위한 변수

	//드래그
	RECT first, last;
	int first_i, first_j;
	int last_i, last_j;
	bool _click;
	bool _release;
	bool _isSampleDrag;
	bool _ischange;
	bool _isDragSet;
	bool _prevent_double;


	bool isSelectSeason;
	SEASON _currentSeason;

	bool isHackedTile;

	int tileX, tileY;
	int sampleTileX, sampleTileY;
	int sampleTileMaxFrameX, sampleTileMaxFrameY;
	POINT scrollLock;
	POINT currentScroll;
	bool isHorLock, isVertLock, isSampleHorLock, isSampleVertLock;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//샘플타일에서 드래그 한 부분을 그려주는 함수
	void setMap_Drag();

	// 샘플타일 드래그 하는 함수
	void sample_Drag();

	/*
	마우스가 왼쪽에서 오른쪽으로
	오른쪽에서 왼쪽으로 움직였을때 초기화 해주는 함수
	*/
	void isChange();

	//맵툴세팅
	void maptoolSetup();
	void setMap();
	void setTerrainMap();
	void save();
	void load();

	void setScroll();
	void resetSampleScrollBar();
	void lockScroll();
	void moveScroll();
	void moveTile();
	void selectSeason();
	void resetSampleTile();

	void checkHacked(int i, int j);
	void checkFence(int i, int j);

	void showMapTile();
	void showControlButton();
	void showScrollBar();
	void showSampleTerrainTile();
	void showSampleObjectTile();

	//지형, 오브젝트 선택하기
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);
	OBJ_OVERLAPPED overlappedSelect(int frameX, int frameY);
	OBJ_TYPE objectTypeSelect(int frameX, int frameY);

	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

