#pragma once
#include "gameNode.h"
#include "tileNode.h"

class maptoolScene : public gameNode
{
private:
	static TCHAR saveName[MAX_PATH];
	static bool _isSave;

	tagTile _tile[TILEY][TILEX]; //�ΰ���ȭ��(����ȭ��)�� ���Ǵ� Ÿ�� �� 400��
	std::vector<std::vector<tagTile>> _sampleTile;
	std::vector<tagTile> _sampleTileX;
	tagCurrentTile _currentTile; //����Ÿ��
	
	RECT _rcSave;		//���̺�
	RECT _rcLoad;		//�ε�
	RECT _rcTerrain;	//����
	RECT _rcObject;		//������Ʈ
	RECT _rcEraser;		//���찳 (������Ʈ�� �����, ������ ������)
	RECT _rcSpring;
	RECT _rcSummer;
	RECT _rcAutumn;
	RECT _rcWinter;
	RECT _rcobjectDelete;

	RECT horScroll;
	RECT vertScroll;
	RECT sampleHorScroll;
	RECT sampleVertScroll;

	CTRL _ctrlSelect;	//���� � ��Ʈ�� ��������
	CTRL _prevCtrl;		//���찳 �������� ���� ������� �ʰ� �ϱ� ���� ����

	//�巡��
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

	//����Ÿ�Ͽ��� �巡�� �� �κ��� �׷��ִ� �Լ�
	void setMap_Drag();

	// ����Ÿ�� �巡�� �ϴ� �Լ�
	void sample_Drag();

	/*
	���콺�� ���ʿ��� ����������
	�����ʿ��� �������� ���������� �ʱ�ȭ ���ִ� �Լ�
	*/
	void isChange();

	//��������
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

	//����, ������Ʈ �����ϱ�
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);
	OBJ_OVERLAPPED overlappedSelect(int frameX, int frameY);
	OBJ_TYPE objectTypeSelect(int frameX, int frameY);

	static INT_PTR CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

