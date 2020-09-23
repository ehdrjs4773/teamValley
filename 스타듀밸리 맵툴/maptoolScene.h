#pragma once
#include "gameNode.h"
#include "tileNode.h"

class maptoolScene : public gameNode
{
private:
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

	RECT horScroll;
	RECT vertScroll;
	RECT sampleHorScroll;
	RECT sampleVertScroll;

	CTRL _ctrlSelect;	//���� � ��Ʈ�� ��������
	CTRL _prevCtrl;		//���찳 �������� ���� ������� �ʰ� �ϱ� ���� ����

	RECT first, last;
	int first_i, first_j;
	int last_i, last_j;
	bool _click;
	bool _release;

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

	void checkHacked();

	void showMapTile();
	void showControlButton();
	void showScrollBar();
	void showSampleTerrainTile();
	void showSampleObjectTile();

	//����, ������Ʈ �����ϱ�
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

};

