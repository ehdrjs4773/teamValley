#include "stdafx.h"
#include "maptoolScene.h"

TCHAR maptoolScene::saveName[MAX_PATH];
bool maptoolScene::_isSave;

HRESULT maptoolScene::init()
{
	//타일맵 이미지 초기화 -> 09.22 로딩 씬으로 넘어감
	_isSave = false;

	//맵툴세팅
	sampleTileMaxFrameX = IMAGEMANAGER->findImage("농장(봄)")->getMaxFrameX() + 1;
	sampleTileMaxFrameY = IMAGEMANAGER->findImage("농장(봄)")->getMaxFrameY() + 1;
	this->maptoolSetup();
	this->setScroll();

	//드래그
	first_i = first_j = last_i = last_j = 0;
	_click = false;
	_release = false;
	_isSampleDrag = false;
	_ischange = false;
	_isDragSet = false;
	_prevent_double = false;


	//현재타일 초기화 (지형 = 잔디)
	_currentTile.x = 0;
	_currentTile.y = 6;

	_currentSeason = SPRING;
	_currentMine = MINE_NORMAL;

	sampleTileX = 0;
	sampleTileY = 0;

	tileX = tileY = 0;

	isSelectSeason = isHorLock = isVertLock = isSampleHorLock = isSampleVertLock = false;

	//지형그리기 속성으로 시작하기
	_ctrlSelect = CTRL_TERRAIN;

	return S_OK;
}

void maptoolScene::release()
{
}

void maptoolScene::update()
{
	//드래그
	if (_isDragSet)
	{
		setMap_Drag();
	}
	else if(!_isDragSet/* && !_prevent_double*/)
	{
		//버튼 눌렀을때 컨트롤
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			lockScroll();
			selectSeason();

			if (PtInRect(&_rcobjectDelete, _ptMouse))
			{
				_ctrlSelect = CTRL_OBJECTDELETE;
			}

			if (PtInRect(&_rcSave, _ptMouse))
			{
				_ctrlSelect = CTRL_SAVE;
				_isSave = true;
				this->save();
			}
			if (PtInRect(&_rcLoad, _ptMouse))
			{
				_ctrlSelect = CTRL_LOAD;
				_isSave = false;
				this->load();
			}
			if (PtInRect(&_rcTerrain, _ptMouse))
			{
				//지형 일때 or 계절 창이 없을때, 버튼을 누르면 계절선택 창 사라짐
				if (_ctrlSelect != CTRL_TERRAIN || !isSelectSeason)
				{
					_ctrlSelect = CTRL_TERRAIN;
					_prevCtrl = _ctrlSelect;
					isSelectSeason = true;
					resetSampleScrollBar();
				}
				else isSelectSeason = false;
			}
			if (PtInRect(&_rcObject, _ptMouse))
			{
				//오브젝트 일때 or 계절 창이 없을때, 버튼을 누르면 계절선택 창 사라짐
				if (_ctrlSelect != CTRL_OBJECT || !isSelectSeason)
				{
					_ctrlSelect = CTRL_OBJECT;
					_prevCtrl = _ctrlSelect;
					isSelectSeason = true;
					resetSampleScrollBar();
				}
				else isSelectSeason = false;
			}
			if (PtInRect(&_rcObject2, _ptMouse))
			{
				//오브젝트 일때 or 계절 창이 없을때, 버튼을 누르면 계절선택 창 사라짐
				if (_ctrlSelect != CTRL_OBJECT2 || !isSelectSeason)
				{
					_ctrlSelect = CTRL_OBJECT2;
					_prevCtrl = _ctrlSelect;
					isSelectSeason = true;
					resetSampleScrollBar();
				}
				else isSelectSeason = false;
			}
			if (PtInRect(&_rcEraser, _ptMouse))
			{
				_ctrlSelect = CTRL_ERASER;
				isSelectSeason = false;
			}
			if (PtInRect(&_rcMineTerrain, _ptMouse))
			{
				_ctrlSelect = CTRL_MINETERRAIN;
				_prevCtrl = _ctrlSelect;
				resetSampleScrollBar();
			}
			if (PtInRect(&_rcMineObject, _ptMouse))
			{
				_ctrlSelect = CTRL_MINEOBJECT;
				_prevCtrl = _ctrlSelect;
				resetSampleScrollBar();
			}
			setMineMap();
		}

		//버튼 떼면 스크롤 락 false
		if (INPUT->GetKeyUp(VK_LBUTTON))
		{
			isHorLock = isVertLock = isSampleHorLock = isSampleVertLock = false;
		}
		//누르고 있는 상황
		if (INPUT->GetKey(VK_LBUTTON))
		{
			//스크롤을 누르고 있다면
			if (isHorLock || isVertLock || isSampleHorLock || isSampleVertLock)
			{
				moveScroll();
			}
			else
			{
				this->setMap();
			}
		}
	}

	isChange();

	if (_isSampleDrag && _ctrlSelect != CTRL_ERASER) this->sample_Drag();
	else this->setTerrainMap();

	moveTile();

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			checkHacked(i, j);
			checkFence(i, j);
		}
	}

	//for (int i = 0; i < sampleTileMaxFrameY; i++)
	//{
	//	for (int j = 0; j < sampleTileMaxFrameX; j++)
	//	{
	//		if (PtInRect(&_sampleTile[i][j].rc, _ptMouse))
	//		{
	//			std::cout << _sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameY 
	//				<< "\t" << _sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameX << std::endl;
	//		}
	//	}
	//}
}

void maptoolScene::render()
{
	IMAGEMANAGER->render("배경", getMemDC(), 0, 0);

	if (_ctrlSelect == CTRL_TERRAIN) { showSampleTerrainTile(); } //지형 타일 보여주는 함수
	else if (_ctrlSelect == CTRL_OBJECT) { showSampleObjectTile(); }//오브젝트 타일 보여주는 함수
	else if (_ctrlSelect == CTRL_OBJECT2) { showSampleObjectTile(); }
	else if (_ctrlSelect == CTRL_MINETERRAIN) { showSampleTerrainTile(); }
	else if (_ctrlSelect == CTRL_MINEOBJECT) { showSampleObjectTile(); }
	
	//지우개 누르면 그 전에 떠있던 샘플 그대로 떠있게 유지
	else if (_ctrlSelect == CTRL_ERASER)
	{
		switch (_prevCtrl)
		{
		case CTRL_TERRAIN:
			showSampleTerrainTile();
			break;
		case CTRL_OBJECT:
			showSampleObjectTile();
			break;
		case CTRL_OBJECT2:
			showSampleObjectTile();
			break;
		}
	}

	//인게임 화면 지형을 그린다
	showMapTile();

	//왼쪽 게임화면 및 오른쪽 샘플타일 렉트 보여주기
	if (INPUT->GetToggleKey(VK_F1))
	{
		for (int i = 0; i < DISPLAYY; i++)
		{
			for (int j = 0; j < DISPLAYX; j++)
			{
				FrameRect(getMemDC(), _tile[i][j].rc, RGB(255, 255, 0));
			}
		}
		for (int i = 0; i < SAMPLEDISPLAYY; i++)
		{
			for (int j = 0; j < SAMPLEDISPLAYX; j++)
			{
				if (j < sampleTileMaxFrameX && i < sampleTileMaxFrameY)
				{
					FrameRect(getMemDC(), _sampleTile[i][j].rc, RGB(0, 30, 80));
				}
			}
		}
	}

	//컨트롤 버튼 출력
	showControlButton();

	//스크롤 바 출력
	showScrollBar();

	if (_click)
	{
		//드래그 오른쪽 아래
		if (first_i <= last_i && first_j <= last_j)
		{
			FrameRect(getMemDC(), RectMake(first.left, first.top, last.right - first.left, last.bottom - first.top), RGB(255, 0, 0));
		}
		//드래그 왼쪽 아래
		else if (first_i <= last_i && first_j > last_j)
		{
			FrameRect(getMemDC(), RectMake(last.left, first.top, first.right - last.left, last.bottom - first.top), RGB(255, 0, 0));
		}
		//드래그 왼쪽 위
		else if (first_i > last_i && first_j > last_j)
		{
			FrameRect(getMemDC(), RectMake(last.left, last.top, first.right - last.left, first.bottom - last.top), RGB(255, 0, 0));
		}
		//드래그 오른쪽 위
		else if (first_i > last_i && first_j <= last_j)
		{
			FrameRect(getMemDC(), RectMake(first.left, last.top, last.right - first.left, first.bottom - last.top), RGB(255, 0, 0));
		}
	}

	//복사한 타일 크기만큼 따라다니는 빨간 렉트
	if (_isDragSet && !_prevent_double)
	{
		for (int i = 0; i < DISPLAYX; i++)
		{
			for (int j = 0; j < DISPLAYY; j++)
			{
				if (PtInRect(&_tile[i][j].rc, _ptMouse))
				{
					RECT temp = { _tile[i][j].rc.left, _tile[i][j].rc.top, \
						_tile[i + (last_i - first_i)][j + (last_j - first_j)].rc.right, \
						_tile[i + (last_i - first_i)][j + (last_j - first_j)].rc.bottom };
					FrameRect(getMemDC(), temp, RGB(255, 0, 0));
				}
			}
		}
	}
}

void maptoolScene::setMap_Drag()
{
	for (int i = 0; i < DISPLAYY; i++)
	{
		for (int j = 0; j < DISPLAYX; j++)
		{
			if (PtInRect(&_tile[i][j].rc, _ptMouse))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					_prevent_double = true;
					for (int q = first_i; q <= last_i; q++)
					{
						for (int w = first_j; w <= last_j; w++)
						{
							if (_ctrlSelect == CTRL_TERRAIN) 
							{
								_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].terrainFrameX = _sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameX;
								_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].terrainFrameY = _sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameY;
								_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].terrain = terrainSelect(q + sampleTileY, w + sampleTileX);

							}
							else if (_ctrlSelect == CTRL_OBJECT)
							{
								if (overlappedSelect(w + sampleTileX, q + sampleTileY) == OVR_OVER)
								{
									_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].ovlFrameX = _sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameX;
									_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].ovlFrameY = _sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameY;

									_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].objOver = overlappedSelect(w + sampleTileX, q + sampleTileY);
								}
								else if (overlappedSelect(w + sampleTileX, q + sampleTileY) == OVR_NONE)
								{
									_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].objFrameX = _sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameX;
									_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].objFrameY = _sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameY;
									_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].obj = objectSelect(q + sampleTileY, w + sampleTileX);
								}
							}
							else if (_ctrlSelect == CTRL_OBJECT2)
							{
								if (overlappedSelect(w + sampleTileX, q + sampleTileY) == OVR_OVER)
								{
									_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].ovlFrameX = _sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameX;
									_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].ovlFrameY = _sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameY;

									_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].objOver = overlappedSelect(w + sampleTileX, q + sampleTileY);
								}
								else if (overlappedSelect(w + sampleTileX, q + sampleTileY) == OVR_NONE)
								{
									if (_sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameX >= 18 && _sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameX <= 21 &&
										_sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameY >= 5 && _sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameY <= 9)
									{
										_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].objFrameX = _sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameX;
										_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].objFrameY = _sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameY;
										_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].obj = OBJ_BUILDING;
										_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].objOver = OVR_NONE;
										_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].objType = OTY_WELL;
									}
									else
									{ 
									_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].objFrameX = _sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameX;
									_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].objFrameY = _sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameY;
									_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].obj = OBJ_BUILDING;
									_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].objOver = OVR_NONE;
									_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].objType = OTY_NONE;
									}
									_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].seedType = SEED_NONE;
								}
							}
							else if (_ctrlSelect == CTRL_MINETERRAIN)
							{
								_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].terrainFrameX = _sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameX;
								_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].terrainFrameY = _sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameY;
								_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].terrain = terrainSelect(q + sampleTileY, w + sampleTileX);
							}
							else if (_ctrlSelect == CTRL_MINEOBJECT)
							{
								_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].objFrameX = _sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameX;
								_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].objFrameY = _sampleTile[q + sampleTileY][w + sampleTileX].terrainFrameY;
								_tile[i + tileY + (q - first_i)][j + tileX + (w - first_j)].obj = objectSelect(q + sampleTileY, w + sampleTileX);
							}
						}
					}
				}
				if (INPUT->GetKeyUp(VK_LBUTTON))
				{
					_prevent_double = false;
					_isDragSet = false;
				}
			}
		}
	}
}

void maptoolScene::sample_Drag()
{
	if (_ctrlSelect == CTRL_MINEOBJECT || _ctrlSelect == CTRL_MINETERRAIN)
	{
		for (int i = 0; i < sampleTileMaxFrameY; i++)
		{
			for (int j = 0; j < sampleTileMaxFrameX; j++)
			{
				if (PtInRect(&_sampleTile[i][j].rc, _ptMouse))
				{
					if (INPUT->GetKeyDown(VK_RBUTTON))
					{
						_click = true;
						first = _sampleTile[i][j].rc;
						first_i = i;
						first_j = j;
						first_j = j;
					}
					if (INPUT->GetKey(VK_RBUTTON) && _click)
					{
						last = _sampleTile[i][j].rc;
						last_i = i;
						last_j = j;
						if (_ptMouse.x >= _sampleTile[0][sampleTileMaxFrameX - 1].rc.right)
						{
							_click = false;
							_release = true;
							_isDragSet = true;

						}
						if (_ptMouse.y >= _sampleTile[sampleTileMaxFrameY - 1][0].rc.bottom)
						{
							_click = false;
							_release = true;
							_isDragSet = true;
						}
					}
					if (INPUT->GetKeyUp(VK_RBUTTON) && _click)
					{
						last = _sampleTile[i][j].rc;
						last_i = i;
						last_j = j;
						_click = false;
						_release = true;
						_isDragSet = true;
					}
				}
			}
		}
		if (_click)
		{
			if (_ptMouse.x >= _sampleTile[0][sampleTileMaxFrameX - 1].rc.right)
			{
				_click = false;
				_release = true;
				_isDragSet = true;

			}
			if (_ptMouse.y >= _sampleTile[sampleTileMaxFrameY - 1][0].rc.bottom)
			{
				_click = false;
				_release = true;
				_isDragSet = true;
			}
		}

		if (_release)
		{
			if (first_i > last_i)
			{
				swap(first_i, last_i);
			}

			if (first_j > last_j)
			{
				swap(first_j, last_j);
			}
			_release = false;
		}
	}
	else
	{
		for (int i = 0; i < SAMPLEDISPLAYY; i++)
		{
			for (int j = 0; j < SAMPLEDISPLAYX; j++)
			{
				if (PtInRect(&_sampleTile[i][j].rc, _ptMouse))
				{
					if (INPUT->GetKeyDown(VK_RBUTTON))
					{
						_click = true;
						first = _sampleTile[i][j].rc;
						first_i = i;
						first_j = j;
						first_j = j;
					}
					if (INPUT->GetKey(VK_RBUTTON) && _click)
					{
						last = _sampleTile[i][j].rc;
						last_i = i;
						last_j = j;
						if (_ptMouse.x >= _sampleTile[0][SAMPLEDISPLAYX - 1].rc.right)
						{
							_click = false;
							_release = true;
							_isDragSet = true;

						}
						if (_ptMouse.y >= _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom)
						{
							_click = false;
							_release = true;
							_isDragSet = true;
						}
					}
					if (INPUT->GetKeyUp(VK_RBUTTON) && _click)
					{
						last = _sampleTile[i][j].rc;
						last_i = i;
						last_j = j;
						_click = false;
						_release = true;
						_isDragSet = true;
					}
				}
			}
		}
		if (_click)
		{
			if (_ptMouse.x >= _sampleTile[0][SAMPLEDISPLAYX - 1].rc.right)
			{
				_click = false;
				_release = true;
				_isDragSet = true;

			}
			if (_ptMouse.y >= _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom)
			{
				_click = false;
				_release = true;
				_isDragSet = true;
			}
		}

		if (_release)
		{
			if (first_i > last_i)
			{
				swap(first_i, last_i);
			}

			if (first_j > last_j)
			{
				swap(first_j, last_j);
			}
			_release = false;
		}
	}
}

void maptoolScene::isChange()
{
	if (_ptMouse.x < _tile[0][DISPLAYX - 1].rc.right + 50)
	{
		if (_isSampleDrag == true)
		{
			_ischange = true;
		}
		if (_ischange && !_isDragSet)
		{
			first_i = -1;
			first_j = -1;
			last_i = -1;
			last_j = -1;
			_ischange = false;
		}
		_isSampleDrag = false;
	}
	else
	{
		if (_isSampleDrag == false)
		{
			_ischange = true;
		}
		if (_ischange == true && !_isDragSet)
		{
			first_i = -1;
			first_j = -1;
			last_i = -1;
			last_j = -1;
			_ischange = false;
		}
		_isSampleDrag = true;
	}
}

void maptoolScene::maptoolSetup()
{
	//오른쪽 샘플타일 렉트 초기화
	for (int i = 0; i < sampleTileMaxFrameY; i++)
	{
		_sampleTileX.clear();
		for (int j = 0; j < sampleTileMaxFrameX; j++)
		{
			tagTile temp;
			if (j < SAMPLEDISPLAYX && i < SAMPLEDISPLAYY)
			{
				//타일맵 이미지 전체화면 우측상단에 배치하기
				temp.rc = RectMake(660 + j * TILESIZE, 50 + i * TILESIZE, TILESIZE, TILESIZE);
			}
			temp.terrainFrameX = j;
			temp.terrainFrameY = i;

			_sampleTileX.push_back(temp);
		}
		_sampleTile.push_back(_sampleTileX);
	}

	//왼쪽 인게임 화면 모두 잔디가 기본 타일이 되도록 세팅하기
	memset(_tile, 0, sizeof(_tile));
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			//왼쪽 인게임 화면 렉트 초기화
			if (j < DISPLAYX && i < DISPLAYY)
			{
				_tile[i][j].rc = RectMake(50 + j * TILESIZE, 50 + i * TILESIZE, TILESIZE, TILESIZE);
			}
			_tile[i][j].terrainFrameX = 0;
			_tile[i][j].terrainFrameY = 6;
			_tile[i][j].objFrameX = 0;
			_tile[i][j].objFrameY = 0;
			_tile[i][j].terrain = terrainSelect(_tile[i][j].terrainFrameX, _tile[i][j].terrainFrameY);
			_tile[i][j].obj = OBJ_NONE;
			_tile[i][j].objType = OTY_NONE;
			_tile[i][j].objOver = OVR_NONE;
			_tile[i][j].seedType = SEED_NONE;
			_tile[i][j].portal = PT_NONE;
			_tile[i][j].grownLevel = 0;
			_tile[i][j].isWet = false;
			_tile[i][j].isFullyGrown = false;

			_tile[i][j].tree.treeImage = nullptr;
			_tile[i][j].tree.treeType = TREE_NONE;
			_tile[i][j].tree.bodyIndexX = 0;
			_tile[i][j].tree.bodyIndexY = 0;
			_tile[i][j].tree.hp = 0;
		}
	}

	//컨트롤 렉트 위치 초기화
	_rcSave = RectMake(660, 400, 100, 50);
	_rcLoad = RectMake(660 + 100, 400, 100, 50);
	_rcTerrain = RectMake(660, 400 + 100, 100, 50);
	_rcObject = RectMake(660 + 100, 400 + 100, 100, 50);
	_rcEraser = RectMake(660 + 200, 400 + 100, 100, 50);
	_rcobjectDelete = RectMake(860, 400, 100, 50);
	_rcObject2 = RectMake(970, 500, 100, 50);
	_rcMineTerrain = RectMake(970, 400, 70, 50);
	_rcMineObject = RectMake(1050, 400, 70, 50);

	_rcMineNormal = RectMake(1010 - 100, 450, 50, 25);
	_rcMineNormalDark = RectMake(1010 - 50, 450, 50, 25);
	_rcMineFrost = RectMake(1010, 450, 50, 25);
	_rcMineFrostDark = RectMake(1010 + 50, 450, 50, 25);

	_rcSpring = RectMake(660 - 100, 450, 50, 30);
	_rcSummer = RectMake(660 - 50, 450, 50, 30);
	_rcAutumn = RectMake(660, 450, 50, 30);
	_rcWinter = RectMake(660 + 50, 450, 50, 30);
}

void maptoolScene::setMap()
{
	for (int i = 0; i < sampleTileMaxFrameY; i++)
	{
		for (int j = 0; j < sampleTileMaxFrameX; j++)
		{
			if (PtInRect(&_sampleTile[i][j].rc, _ptMouse))
			{
				_currentTile.x = _sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameX;
				_currentTile.y = _sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameY;
				break;
			}
		}
	}

	//인게임화면 렉트와 충돌했냐?
	for (int i = 0; i < DISPLAYY; i++)
	{
		for (int j = 0; j < DISPLAYX; j++)
		{
			if (PtInRect(&_tile[i][j].rc, _ptMouse))
			{
				//현재버튼이 지형이냐?
				if (_ctrlSelect == CTRL_TERRAIN)
				{
					if (_currentTile.x == 20 && _currentTile.y == 14 && _tile[i][j].terrain == TR_HACKED)
					{
						_tile[i + tileY][j + tileX].isWet = true; 
						_tile[i + tileY][j + tileX].wetFrameX = 20;
						_tile[i + tileY][j + tileX].wetFrameY = 14;
					}
					else
					{
						_tile[i + tileY][j + tileX].terrainFrameX = _currentTile.x;
						_tile[i + tileY][j + tileX].terrainFrameY = _currentTile.y;
						_tile[i + tileY][j + tileX].terrain = terrainSelect(_currentTile.x, _currentTile.y);
					}
				}
				//현재버튼이 오브젝트냐?
				if (_ctrlSelect == CTRL_OBJECT)
				{
					if (_currentTile.x == 11 && _currentTile.y == 24)
					{
						_tile[i + tileY][j + tileX].obj = OBJ_DESTRUCTIBLE;
						_tile[i + tileY][j + tileX].objType = OTY_TREE;
						_tile[i + tileY][j + tileX].grownLevel = 4;
						_tile[i + tileY][j + tileX].isFullyGrown = true;

						_tile[i + tileY][j + tileX].tree.bodyIndexX = 8;
						_tile[i + tileY][j + tileX].tree.bodyIndexY = 9;
						_tile[i + tileY][j + tileX].tree.hp = 5;
						_tile[i + tileY][j + tileX].tree.treeImage = IMAGEMANAGER->findImage("나무");
						_tile[i + tileY][j + tileX].tree.treeType = TREE_PINE;
					}
					else if (_currentTile.x == 8 && _currentTile.y == 24)
					{
						_tile[i + tileY][j + tileX].obj = OBJ_DESTRUCTIBLE;
						_tile[i + tileY][j + tileX].objType = OTY_TREE;
						_tile[i + tileY][j + tileX].grownLevel = 4;
						_tile[i + tileY][j + tileX].isFullyGrown = true;

						_tile[i + tileY][j + tileX].tree.bodyIndexX = 5;
						_tile[i + tileY][j + tileX].tree.bodyIndexY = 9;
						_tile[i + tileY][j + tileX].tree.hp = 5;
						_tile[i + tileY][j + tileX].tree.treeImage = IMAGEMANAGER->findImage("나무");
						_tile[i + tileY][j + tileX].tree.treeType = TREE_MAPLE;
					}
					else if (_currentTile.x == 5 && _currentTile.y == 24)
					{
						_tile[i + tileY][j + tileX].obj = OBJ_DESTRUCTIBLE;
						_tile[i + tileY][j + tileX].objType = OTY_TREE;
						_tile[i + tileY][j + tileX].grownLevel = 4;
						_tile[i + tileY][j + tileX].isFullyGrown = true;

						_tile[i + tileY][j + tileX].tree.bodyIndexX = 2;
						_tile[i + tileY][j + tileX].tree.bodyIndexY = 9;
						_tile[i + tileY][j + tileX].tree.hp = 5;
						_tile[i + tileY][j + tileX].tree.treeImage = IMAGEMANAGER->findImage("나무");
						_tile[i + tileY][j + tileX].tree.treeType = TREE_OAK;
					}
					else
					{
						_tile[i + tileY][j + tileX].objOver = overlappedSelect(_currentTile.x, _currentTile.y);

						if (_tile[i + tileY][j + tileX].objOver == OVR_OVER)
						{
							_tile[i + tileY][j + tileX].ovlFrameX = _currentTile.x;
							_tile[i + tileY][j + tileX].ovlFrameY = _currentTile.y;
						}
						else if (_tile[i + tileY][j + tileX].objOver == OVR_NONE)
						{
							_tile[i + tileY][j + tileX].objFrameX = _currentTile.x;
							_tile[i + tileY][j + tileX].objFrameY = _currentTile.y;
							_tile[i + tileY][j + tileX].obj = objectSelect(_currentTile.x, _currentTile.y);
						}
					}
				}
				if (_ctrlSelect == CTRL_OBJECT2)
				{
					if (_currentTile.x == 0 && _currentTile.y == 1)
					{
						_tile[i + tileY][j + tileX].objFrameX = _currentTile.x;
						_tile[i + tileY][j + tileX].objFrameY = _currentTile.y;
						_tile[i + tileY][j + tileX].obj = OBJ_DESTRUCTIBLE;
						_tile[i + tileY][j + tileX].objType = OTY_WOODENFENCE;
					}
					else if (_currentTile.x == 0 && _currentTile.y == 3)
					{
						_tile[i + tileY][j + tileX].objFrameX = _currentTile.x;
						_tile[i + tileY][j + tileX].objFrameY = _currentTile.y;
						_tile[i + tileY][j + tileX].obj = OBJ_DESTRUCTIBLE;
						_tile[i + tileY][j + tileX].objType = OTY_STONEFENCE;
					}
					else if (_currentTile.x == 26 && _currentTile.y == 9)
					{
						_tile[i + tileY][j + tileX].objFrameX = _currentTile.x;
						_tile[i + tileY][j + tileX].objFrameY = _currentTile.y;
						_tile[i + tileY][j + tileX].obj = OBJ_BUILDING;
						_tile[i + tileY][j + tileX].objType = OTY_SHOP;
						
						for (int y = 0; y < 6; y++)
						{
							for (int x = 0; x < 10; x++)
							{
								if (i + tileY - y >= 0 && j + tileX + x < 50)
								{
									_tile[i + tileY - y][j + tileX + x].objFrameX = _currentTile.x + x;
									_tile[i + tileY - y][j + tileX + x].objFrameY = _currentTile.y - y;
									_tile[i + tileY - y][j + tileX + x].obj = OBJ_BUILDING;
									_tile[i + tileY - y][j + tileX + x].objType = OTY_SHOP;
								}
							}
						}
					}
					checkFence(i + tileY, j + tileX);
				}

				//현재버튼이 지우개냐?
				if (_ctrlSelect == CTRL_ERASER)
				{
					_tile[i + tileY][j + tileX].objFrameX = 0;
					_tile[i + tileY][j + tileX].objFrameY = 0;
					_tile[i + tileY][j + tileX].obj = OBJ_NONE;
					_tile[i + tileY][j + tileX].objOver = OVR_NONE;
				}

				if (_ctrlSelect == CTRL_OBJECTDELETE)
				{
					_tile[i + tileY][j + tileX].terrainFrameX = 0;
					_tile[i + tileY][j + tileX].terrainFrameY = 6;
					_tile[i + tileY][j + tileX].objFrameX = 0;
					_tile[i + tileY][j + tileX].objFrameY = 0;
					_tile[i + tileY][j + tileX].terrain = terrainSelect(_tile[i][j].terrainFrameX, _tile[i][j].terrainFrameY);
					_tile[i + tileY][j + tileX].obj = OBJ_NONE;
					_tile[i + tileY][j + tileX].objType = OTY_NONE;
					_tile[i + tileY][j + tileX].objOver = OVR_NONE;
					_tile[i + tileY][j + tileX].seedType = SEED_NONE;
					_tile[i + tileY][j + tileX].portal = PT_NONE;
					_tile[i + tileY][j + tileX].grownLevel = 0;
					_tile[i + tileY][j + tileX].isWet = false;
					_tile[i + tileY][j + tileX].isFullyGrown = false;
						  
					_tile[i + tileY][j + tileX].tree.treeImage = nullptr;
					_tile[i + tileY][j + tileX].tree.treeType = TREE_NONE;
					_tile[i + tileY][j + tileX].tree.bodyIndexX = 0;
					_tile[i + tileY][j + tileX].tree.bodyIndexY = 0;
					_tile[i + tileY][j + tileX].tree.hp = 0;
				}
				if (_ctrlSelect == CTRL_MINETERRAIN)
				{
					_tile[i + tileY][j + tileX].terrainFrameX = _currentTile.x;
					_tile[i + tileY][j + tileX].terrainFrameY = _currentTile.y;
					_tile[i + tileY][j + tileX].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				if (_ctrlSelect == CTRL_MINEOBJECT)
				{
					_tile[i + tileY][j + tileX].objFrameX = _currentTile.x;
					_tile[i + tileY][j + tileX].objFrameY = _currentTile.y;
					_tile[i + tileY][j + tileX].obj = objectSelect(_currentTile.x, _currentTile.y);
				}
			}
		}
	}
}

void maptoolScene::setTerrainMap()
{
	for (int i = 0; i < DISPLAYY; i++)
	{
		for (int j = 0; j < DISPLAYX; j++)
		{
			if (_ctrlSelect != CTRL_MINETERRAIN && _ctrlSelect != CTRL_MINEOBJECT)
			{
				if (PtInRect(&_tile[i][j].rc, _ptMouse))
				{
					if (_ctrlSelect == CTRL_TERRAIN || _ctrlSelect == CTRL_OBJECT || _ctrlSelect == CTRL_ERASER)
					{
						if (INPUT->GetKeyDown(VK_RBUTTON))
						{
							_click = true;
							first = _tile[i][j].rc;
							first_i = i;
							first_j = j;
						}
						if (INPUT->GetKey(VK_RBUTTON))
						{
							last = _tile[i][j].rc;
							last_i = i;
							last_j = j;
						}
						if (INPUT->GetKeyUp(VK_RBUTTON) && _click)
						{
							last = _tile[i][j].rc;
							last_i = i;
							last_j = j;
							_click = false;
							_release = true;
						}
					}
				}
			}
			else
			{
				if (PtInRect(&_tile[i][j].rc, _ptMouse))
				{
					if (INPUT->GetKeyDown(VK_RBUTTON))
					{
						_click = true;
						first = _tile[i][j].rc;
						first_i = i;
						first_j = j;
					}
					if (INPUT->GetKey(VK_RBUTTON))
					{
						last = _tile[i][j].rc;
						last_i = i;
						last_j = j;
					}
					if (INPUT->GetKeyUp(VK_RBUTTON) && _click)
					{
						last = _tile[i][j].rc;
						last_i = i;
						last_j = j;
						_click = false;
						_release = true;
					}
				}
			}
		}
	}
	if (_release)
	{
		if (first_i > last_i)
		{
			swap(first_i, last_i);
		}

		if (first_j > last_j)
		{
			swap(first_j, last_j);
		}

		for (int i = first_i; i <= last_i; i++)
		{
			for (int j = first_j; j <= last_j; j++)
			{
				if (_ctrlSelect == CTRL_TERRAIN || _ctrlSelect == CTRL_MINETERRAIN)
				{
					_tile[i + tileY][j + tileX].terrainFrameX = _currentTile.x;
					_tile[i + tileY][j + tileX].terrainFrameY = _currentTile.y;
					_tile[i + tileY][j + tileX].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				else if (_ctrlSelect == CTRL_OBJECT || _ctrlSelect == CTRL_MINEOBJECT)
				{
					_tile[i + tileY][j + tileX].objFrameX = _currentTile.x;
					_tile[i + tileY][j + tileX].objFrameY = _currentTile.y;
					_tile[i + tileY][j + tileX].obj = objectSelect(_currentTile.x, _currentTile.y);
				}
				if (_ctrlSelect == CTRL_ERASER)
				{
					_tile[i + tileY][j + tileX].objFrameX = 0;
					_tile[i + tileY][j + tileX].objFrameY = 0;
					_tile[i + tileY][j + tileX].obj = OBJ_NONE;
					_tile[i + tileY][j + tileX].objOver = OVR_NONE;
				}
			}
		}
		_release = false;
	}

}

void maptoolScene::save()
{
	DialogBox(_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), _hWnd, maptoolScene::DlgProc);
	
	HANDLE file;
	DWORD write;
	file = CreateFile(saveName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _tile, sizeof(_tile), &write, NULL);
	CloseHandle(file);
}

void maptoolScene::load()
{
	DialogBox(_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), _hWnd, maptoolScene::DlgProc);

	HANDLE file;
	DWORD read;

	file = CreateFile(saveName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tile, sizeof(_tile), &read, NULL);
	CloseHandle(file);

	for (int i = 0; i < TILEY; i++)
	{
		for (int  j = 0; j < TILEX; j++)
		{
			if (j < DISPLAYX && i < DISPLAYY)
			{
				_tile[i][j].rc = RectMake(50 + j * TILESIZE, 50 + i * TILESIZE, TILESIZE, TILESIZE);
			}
			else
			{
				_tile[i][j].rc = RectMake(-50, -50, 0, 0);
			}
		}
	}
	
}

void maptoolScene::setScroll()
{
	//스크롤 바 초기화
	horScroll = RectMake(_tile[0][0].rc.left, _tile[DISPLAYY - 1][0].rc.bottom + 10, TILESIZE * DISPLAYX / 2, 10);
	vertScroll = RectMake(_tile[0][DISPLAYX - 1].rc.right + 10, _tile[0][0].rc.top, 10, TILESIZE * DISPLAYY / 2);

	sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
	sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);
}

void maptoolScene::resetSampleScrollBar()
{
	//샘플 스크롤 바 위치 초기화
	if (_ctrlSelect == CTRL_MINEOBJECT || _ctrlSelect == CTRL_MINETERRAIN)
	{
		sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[sampleTileMaxFrameY - 1][0].rc.bottom + 10, TILESIZE * sampleTileMaxFrameX / 2, 10);
		sampleVertScroll = RectMake(_sampleTile[0][sampleTileMaxFrameX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * sampleTileMaxFrameY / 2);
	}
	else
	{
		sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
		sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);
	}
}

void maptoolScene::lockScroll()
{
	//스크롤 바 눌렀을 때 마우스 위치, 스크롤바 Left, Top 좌표 저장 (스크롤바 이동 거리 산출용)
	if (PtInRect(&horScroll, _ptMouse))
	{
		scrollLock = _ptMouse;
		currentScroll.x = horScroll.left;
		currentScroll.y = horScroll.top;
		isHorLock = true;
	}
	else if (PtInRect(&vertScroll, _ptMouse))
	{
		scrollLock = _ptMouse;
		currentScroll.x = vertScroll.left;
		currentScroll.y = vertScroll.top;
		isVertLock = true;
	}
	else if (PtInRect(&sampleHorScroll, _ptMouse))
	{
		scrollLock = _ptMouse;
		currentScroll.x = sampleHorScroll.left;
		currentScroll.y = sampleHorScroll.top;
		isSampleHorLock = true;
	}
	else if (PtInRect(&sampleVertScroll, _ptMouse))
	{
		scrollLock = _ptMouse;
		currentScroll.x = sampleVertScroll.left;
		currentScroll.y = sampleVertScroll.top;
		isSampleVertLock = true;
	}
}

void maptoolScene::moveScroll()
{
	if (isHorLock)
	{
		horScroll = RectMake(currentScroll.x + (_ptMouse.x - scrollLock.x), _tile[DISPLAYY - 1][0].rc.bottom + 10, TILESIZE * DISPLAYX / 2, 10);
		if (horScroll.left < _tile[0][0].rc.left)
		{
			horScroll.left = _tile[0][0].rc.left;
			horScroll.right = _tile[0][0].rc.left + TILESIZE * DISPLAYX / 2;
		}
		else if (horScroll.left > _tile[0][0].rc.left + TILESIZE * DISPLAYX / 2)
		{
			horScroll.left = _tile[0][0].rc.left + TILESIZE * DISPLAYX / 2;
			horScroll.right = _tile[0][0].rc.left + TILESIZE * DISPLAYX;
		}
	}
	else if (isVertLock)
	{
		vertScroll = RectMake(_tile[0][DISPLAYX - 1].rc.right + 10, currentScroll.y + (_ptMouse.y - scrollLock.y), 10, TILESIZE * DISPLAYY / 2);
		if (vertScroll.top < _tile[0][0].rc.top)
		{
			vertScroll.top = _tile[0][0].rc.top;
			vertScroll.bottom = _tile[0][0].rc.top + TILESIZE * DISPLAYY / 2;
		}
		else if (vertScroll.top > _tile[0][0].rc.top + TILESIZE * DISPLAYY / 2)
		{
			vertScroll.top = _tile[0][0].rc.top + TILESIZE * DISPLAYY / 2;
			vertScroll.bottom = _tile[0][0].rc.top + TILESIZE * DISPLAYY;
		}
	}
	else if (isSampleHorLock)
	{
		sampleHorScroll = RectMake(currentScroll.x + (_ptMouse.x - scrollLock.x), _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
		if (sampleHorScroll.left < _sampleTile[0][0].rc.left)
		{
			sampleHorScroll.left = _sampleTile[0][0].rc.left;
			sampleHorScroll.right = _sampleTile[0][0].rc.left + TILESIZE * SAMPLEDISPLAYX / 2;
		}
		else if (sampleHorScroll.left > _sampleTile[0][0].rc.left + TILESIZE * SAMPLEDISPLAYX / 2)
		{
			sampleHorScroll.left = _sampleTile[0][0].rc.left + TILESIZE * SAMPLEDISPLAYX / 2;
			sampleHorScroll.right = _sampleTile[0][0].rc.left + TILESIZE * SAMPLEDISPLAYX;
		}
	}
	else if (isSampleVertLock)
	{
		sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX- 1].rc.right + 10, currentScroll.y + (_ptMouse.y - scrollLock.y), 10, TILESIZE * SAMPLEDISPLAYY / 2);
		if (sampleVertScroll.top < _sampleTile[0][0].rc.top)
		{
			sampleVertScroll.top = _sampleTile[0][0].rc.top;
			sampleVertScroll.bottom = _sampleTile[0][0].rc.top + TILESIZE * SAMPLEDISPLAYY / 2;
		}
		else if (sampleVertScroll.top > _sampleTile[0][0].rc.top + TILESIZE * SAMPLEDISPLAYY / 2)
		{
			sampleVertScroll.top = _sampleTile[0][0].rc.top + TILESIZE * SAMPLEDISPLAYY / 2;
			sampleVertScroll.bottom = _sampleTile[0][0].rc.top + TILESIZE * SAMPLEDISPLAYY;
		}
	}
}

void maptoolScene::moveTile()
{
	tileX = (float)(horScroll.left - _tile[0][0].rc.left) / (float)((float)(TILESIZE * (float)(DISPLAYX / 2) / (float)(TILEX - DISPLAYX)));
	tileY = (float)(vertScroll.top - _tile[0][0].rc.top) / (float)((float)(TILESIZE * (float)(DISPLAYY / 2) / (float)(TILEX - DISPLAYX)));

	if (sampleTileMaxFrameX > SAMPLEDISPLAYX)
	{
		sampleTileX = (float)(sampleHorScroll.left - _sampleTile[0][0].rc.left) / (float)((float)(TILESIZE * (float)(SAMPLEDISPLAYX / 2) / (float)(sampleTileMaxFrameX - SAMPLEDISPLAYX)));
	}
	if (sampleTileMaxFrameY > SAMPLEDISPLAYY)
	{
		sampleTileY = (float)(sampleVertScroll.top - _sampleTile[0][0].rc.top) / (float)((float)(TILESIZE * (float)(SAMPLEDISPLAYY / 2) / (float)(sampleTileMaxFrameY - SAMPLEDISPLAYY)));
	}
}

void maptoolScene::selectSeason()
{
	if (isSelectSeason)
	{
		switch (_ctrlSelect)
		{
		case CTRL_TERRAIN:
			if (PtInRect(&_rcSpring, _ptMouse))
			{
				_currentSeason = SPRING;
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("농장(봄)")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("농장(봄)")->getMaxFrameY() + 1;
				resetSampleTile();
				sampleTileX = sampleTileY = 0;

				//디스플레이 사이즈보다 파일 프레임이 작을때
				/*if (sampleTileMaxFrameX > SAMPLEDISPLAYX)
				{
					if (sampleTileMaxFrameY > SAMPLEDISPLAYY)
					{
						sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
					}
					else
					{
						sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[sampleTileMaxFrameY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
					}
				}
				if (sampleTileMaxFrameY > SAMPLEDISPLAYY)
				{
					if (sampleTileMaxFrameX > SAMPLEDISPLAYX)
					{
						sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);
					}
					else
					{
						sampleVertScroll = RectMake(_sampleTile[0][sampleTileMaxFrameX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);
					}
				}*/
			}
			if (PtInRect(&_rcSummer, _ptMouse))
			{
				sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
				sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);

				_currentSeason = SUMMER;
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("농장(여름)")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("농장(여름)")->getMaxFrameY() + 1;
				resetSampleTile();
				sampleTileX = sampleTileY = 0;
			}
			if (PtInRect(&_rcAutumn, _ptMouse))
			{
				sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
				sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);

				_currentSeason = AUTUMN;
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("농장(가을)")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("농장(가을)")->getMaxFrameY() + 1;
				resetSampleTile();
				sampleTileX = sampleTileY = 0;
			}
			if (PtInRect(&_rcWinter, _ptMouse))
			{
				sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
				sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);

				_currentSeason = WINTER;
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("농장(겨울)")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("농장(겨울)")->getMaxFrameY() + 1;
				resetSampleTile();
				sampleTileX = sampleTileY = 0;
			}
			break;
		case CTRL_OBJECT:
			if (PtInRect(&_rcSpring, _ptMouse))
			{
				sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
				sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);

				_currentSeason = SPRING;
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("농장오브젝트(봄)")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("농장오브젝트(봄)")->getMaxFrameY() + 1;
				resetSampleTile();
			}
			if (PtInRect(&_rcSummer, _ptMouse))
			{
				sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
				sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);

				_currentSeason = SUMMER;
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("농장오브젝트(여름)")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("농장오브젝트(여름)")->getMaxFrameY() + 1;
				resetSampleTile();
			}
			if (PtInRect(&_rcAutumn, _ptMouse))
			{
				sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
				sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);

				_currentSeason = AUTUMN;
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("농장오브젝트(가을)")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("농장오브젝트(가을)")->getMaxFrameY() + 1;
				resetSampleTile();
			}
			if (PtInRect(&_rcWinter, _ptMouse))
			{
				sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
				sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);

				_currentSeason = WINTER;
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("농장오브젝트(겨울)")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("농장오브젝트(겨울)")->getMaxFrameY() + 1;
				resetSampleTile();
				sampleTileX = sampleTileY = 0;
			}
			break;
		case CTRL_OBJECT2:
			if (PtInRect(&_rcSpring, _ptMouse))
			{
				sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
				sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);

				_currentSeason = SPRING;
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("건물")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("건물")->getMaxFrameY() + 1;
				resetSampleTile();
			}
			if (PtInRect(&_rcSummer, _ptMouse))
			{
				sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
				sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);

				_currentSeason = SUMMER;
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("건물")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("건물")->getMaxFrameY() + 1;
				resetSampleTile();
			}
			if (PtInRect(&_rcAutumn, _ptMouse))
			{
				sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
				sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);

				_currentSeason = AUTUMN;
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("건물")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("건물")->getMaxFrameY() + 1;
				resetSampleTile();
			}
			if (PtInRect(&_rcWinter, _ptMouse))
			{
				sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
				sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);

				_currentSeason = WINTER;
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("건물")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("건물")->getMaxFrameY() + 1;
				resetSampleTile();
				sampleTileX = sampleTileY = 0;
			}
			break;
		case CTRL_MINETERRAIN:
			_currentSeason = SPRING;
			sampleTileMaxFrameX = IMAGEMANAGER->findImage("광산 노말")->getMaxFrameX() + 1;
			sampleTileMaxFrameY = IMAGEMANAGER->findImage("광산 노말")->getMaxFrameY() + 1;
			resetSampleTile();
			sampleTileX = sampleTileY = 0;
			break;
		case CTRL_MINEOBJECT:
			_currentSeason = SPRING;
			sampleTileMaxFrameX = IMAGEMANAGER->findImage("광산오브젝트 노말")->getMaxFrameX() + 1;
			sampleTileMaxFrameY = IMAGEMANAGER->findImage("광산오브젝트 노말")->getMaxFrameY() + 1;
			resetSampleTile();
			sampleTileX = sampleTileY = 0;
		}
	}
}

void maptoolScene::resetSampleTile()
{
	_sampleTile.clear();
	for (int i = 0; i < sampleTileMaxFrameY; i++)
	{
		_sampleTileX.clear();
		for (int j = 0; j < sampleTileMaxFrameX; j++)
		{
			tagTile temp;
			if (j < SAMPLEDISPLAYX && i < SAMPLEDISPLAYY)
			{
				temp.rc = RectMake(660 + j * TILESIZE, 50 + i * TILESIZE, TILESIZE, TILESIZE);
			}
			temp.terrainFrameX = j;
			temp.terrainFrameY = i;

			_sampleTileX.push_back(temp);
		}
		_sampleTile.push_back(_sampleTileX);
	}
}

//갈린 농지 체크
void maptoolScene::checkHacked(int i, int j)
{
	if (i - 1 >= 0 && i + 1 <= TILEY - 1 && j - 1 >= 0 && j + 1 <= TILEX - 1)
	{
		if (_tile[i][j].terrain == TR_HACKED)
		{
			if (_tile[i][j].isWet)
			{
				_tile[i][j].wetFrameX = 20;
				_tile[i][j].wetFrameY = 14;
			}
			else
			{
				_tile[i][j].terrainFrameX = 20;
				_tile[i][j].terrainFrameY = 12;
			}
			if (_tile[i][j - 1].terrain == TR_HACKED) //왼쪽
			{
				if (_tile[i][j].isWet)
				{
					_tile[i][j].wetFrameX = 21;
					_tile[i][j].wetFrameY = 15;
				}
				else
				{
					_tile[i][j].terrainFrameX = 21;
					_tile[i][j].terrainFrameY = 13;
				}
			}
			if (_tile[i][j + 1].terrain == TR_HACKED) //오른쪽
			{
				if (_tile[i][j].isWet)
				{
					_tile[i][j].wetFrameX = 20;
					_tile[i][j].wetFrameY = 15;
				}
				else
				{
					_tile[i][j].terrainFrameX = 20;
					_tile[i][j].terrainFrameY = 13;
				}
			}
			if (_tile[i - 1][j].terrain == TR_HACKED) //위
			{
				if (_tile[i][j].isWet)
				{
					_tile[i][j].wetFrameX = 22;
					_tile[i][j].wetFrameY = 15;
				}
				else
				{
					_tile[i][j].terrainFrameX = 22;
					_tile[i][j].terrainFrameY = 13;
				}
			}
			if (_tile[i + 1][j].terrain == TR_HACKED) //아래
			{
				if (_tile[i][j].isWet)
				{
					_tile[i][j].wetFrameX = 22;
					_tile[i][j].wetFrameY = 14;
				}
				else
				{
					_tile[i][j].terrainFrameX = 22;
					_tile[i][j].terrainFrameY = 12;
				}
			}
			if (_tile[i][j - 1].terrain == TR_HACKED && _tile[i][j + 1].terrain == TR_HACKED)			//왼+오
			{
				if (_tile[i][j].isWet)
				{
					_tile[i][j].wetFrameX = 21;
					_tile[i][j].wetFrameY = 22;
				}
				else
				{
					_tile[i][j].terrainFrameX = 21;
					_tile[i][j].terrainFrameY = 20;
				}
			}
			if (_tile[i - 1][j].terrain == TR_HACKED && _tile[i + 1][j].terrain == TR_HACKED)			//위+아래
			{
				if (_tile[i][j].isWet)
				{
					_tile[i][j].wetFrameX = 20;
					_tile[i][j].wetFrameY = 22;
				}
				else
				{
					_tile[i][j].terrainFrameX = 20;
					_tile[i][j].terrainFrameY = 20;
				}
			}
			if ((_tile[i - 1][j].terrain == TR_HACKED && _tile[i][j - 1].terrain == TR_HACKED)
				|| (_tile[i - 1][j].terrain == TR_HACKED
					&& _tile[i][j - 1].terrain == TR_HACKED
					&& _tile[i - 1][j - 1].terrain == TR_HACKED))	//위+왼 ||  //위+왼+왼대각
			{
				if (_tile[i][j].isWet)
				{
					_tile[i][j].wetFrameX = 22;
					_tile[i][j].wetFrameY = 23;
				}
				else
				{
					_tile[i][j].terrainFrameX = 22;
					_tile[i][j].terrainFrameY = 21;
				}
			}
			if ((_tile[i - 1][j].terrain == TR_HACKED && _tile[i][j + 1].terrain == TR_HACKED)
				|| (_tile[i - 1][j].terrain == TR_HACKED
					&& _tile[i][j + 1].terrain == TR_HACKED
					&& _tile[i + 1][j + 1].terrain == TR_HACKED))	 //위+오 || 위+오+오대각
			{
				if (_tile[i][j].isWet)
				{
					_tile[i][j].wetFrameX = 20;
					_tile[i][j].wetFrameY = 23;
				}
				else
				{
					_tile[i][j].terrainFrameX = 20;
					_tile[i][j].terrainFrameY = 21;
				}
			}
			if ((_tile[i + 1][j].terrain == TR_HACKED && _tile[i][j - 1].terrain == TR_HACKED)
				|| (_tile[i + 1][j].terrain == TR_HACKED
					&& _tile[i][j - 1].terrain == TR_HACKED
					&& _tile[i + 1][j - 1].terrain == TR_HACKED))	//아래+왼 || 아래+왼+왼대각
			{
				if (_tile[i][j].isWet)
				{
					_tile[i][j].wetFrameX = 22;
					_tile[i][j].wetFrameY = 18;
				}
				else
				{
					_tile[i][j].terrainFrameX = 22;
					_tile[i][j].terrainFrameY = 16;
				}
			}
			if ((_tile[i + 1][j].terrain == TR_HACKED && _tile[i][j + 1].terrain == TR_HACKED)
				|| (_tile[i + 1][j].terrain == TR_HACKED
					&& _tile[i][j + 1].terrain == TR_HACKED
					&& _tile[i + 1][j + 1].terrain == TR_HACKED))	//아래+오 || 아래+오+오대각
			{
				if (_tile[i][j].isWet)
				{
					_tile[i][j].wetFrameX = 20;
					_tile[i][j].wetFrameY = 18;
				}
				else
				{
					_tile[i][j].terrainFrameX = 20;
					_tile[i][j].terrainFrameY = 16;
				}
			}
			if (_tile[i - 1][j].terrain == TR_HACKED
				&& _tile[i][j - 1].terrain == TR_HACKED
				&& _tile[i + 1][j].terrain == TR_HACKED)		//위+왼+아래
			{
				if (_tile[i][j].isWet)
				{
					_tile[i][j].wetFrameX = 22;
					_tile[i][j].wetFrameY = 19;
				}
				else
				{
					_tile[i][j].terrainFrameX = 22;
					_tile[i][j].terrainFrameY = 17;
				}
			}
			if (_tile[i - 1][j].terrain == TR_HACKED
				&& _tile[i][j + 1].terrain == TR_HACKED
				&& _tile[i + 1][j].terrain == TR_HACKED)		//위+오+아래
			{
				if (_tile[i][j].isWet)
				{
					_tile[i][j].wetFrameX = 20;
					_tile[i][j].wetFrameY = 19;
				}
				else
				{
					_tile[i][j].terrainFrameX = 20;
					_tile[i][j].terrainFrameY = 17;
				}
			}
			if (_tile[i - 1][j].terrain == TR_HACKED
				&& _tile[i][j - 1].terrain == TR_HACKED
				&& _tile[i][j + 1].terrain == TR_HACKED)		//위+왼+오
			{
				if (_tile[i][j].isWet)
				{
					_tile[i][j].wetFrameX = 21;
					_tile[i][j].wetFrameY = 23;
				}
				else
				{
					_tile[i][j].terrainFrameX = 21;
					_tile[i][j].terrainFrameY = 21;
				}
			}
			if (_tile[i + 1][j].terrain == TR_HACKED
				&& _tile[i][j - 1].terrain == TR_HACKED
				&& _tile[i][j + 1].terrain == TR_HACKED)		//아래+왼+오 
			{
				if (_tile[i][j].isWet)
				{
					_tile[i][j].wetFrameX = 21;
					_tile[i][j].wetFrameY = 18;
				}
				else
				{
					_tile[i][j].terrainFrameX = 21;
					_tile[i][j].terrainFrameY = 16;
				}
			}
			if ((_tile[i - 1][j].terrain == TR_HACKED
				&& _tile[i + 1][j].terrain == TR_HACKED
				&& _tile[i][j - 1].terrain == TR_HACKED
				&& _tile[i][j + 1].terrain == TR_HACKED)		//위아래왼오 (4방)
				|| (_tile[i - 1][j].terrain == TR_HACKED
					&& _tile[i + 1][j].terrain == TR_HACKED
					&& _tile[i][j - 1].terrain == TR_HACKED
					&& _tile[i][j + 1].terrain == TR_HACKED
					&& _tile[i - 1][j - 1].terrain == TR_HACKED
					&& _tile[i + 1][j - 1].terrain == TR_HACKED
					&& _tile[i - 1][j + 1].terrain == TR_HACKED
					&& _tile[i + 1][j + 1].terrain == TR_HACKED))	//위아래양옆대각4개 모두	(8방)
			{
				//기본 네모
				if (_tile[i][j].isWet)
				{
					_tile[i][j].wetFrameX = 21;
					_tile[i][j].wetFrameY = 19;
				}
				else
				{
					_tile[i][j].terrainFrameX = 21;
					_tile[i][j].terrainFrameY = 17;
				}
			}
		}
	}
}

void maptoolScene::checkFence(int i, int j)
{
	if (i - 1 >= 0 && i + 1 <= TILEY - 1 && j - 1 >= 0 && j + 1 <= TILEX - 1)
	{
		if (_tile[i][j].objType == OTY_WOODENFENCE || _tile[i][j].objType == OTY_STONEFENCE)
		{
			if (_tile[i][j].objType == _tile[i - 1][j].objType)	//위
			{
				_tile[i][j].objFrameX = 0;
				_tile[i][j].objFrameY = 3;
			}
			if (_tile[i][j].objType == _tile[i][j - 1].objType)	//왼
			{
				_tile[i][j].objFrameX = 2;
				_tile[i][j].objFrameY = 1;
			}
			if (_tile[i][j].objType == _tile[i][j + 1].objType)	//오
			{
				_tile[i][j].objFrameX = 0;
				_tile[i][j].objFrameY = 1;
			}
			if (_tile[i][j].objType == _tile[i][j + 1].objType
				&& _tile[i][j].objType == _tile[i][j - 1].objType)	//양쪽
			{
				_tile[i][j].objFrameX = 1;
				_tile[i][j].objFrameY = 3;
			}
			if (_tile[i][j].objType == _tile[i][j - 1].objType
				&& _tile[i][j].objType == _tile[i - 1][j].objType)	//좌상
			{
				_tile[i][j].objFrameX = 2;
				_tile[i][j].objFrameY = 5;
			}
			if (_tile[i][j].objType == _tile[i][j + 1].objType
				&& _tile[i][j].objType == _tile[i - 1][j].objType)	//우상
			{
				_tile[i][j].objFrameX = 0;
				_tile[i][j].objFrameY = 5;
			}
			if (_tile[i][j].objType == _tile[i][j + 1].objType
				&& _tile[i][j].objType == _tile[i][j - 1].objType
				&& _tile[i][j].objType == _tile[i - 1][j].objType)	//위 + 양옆
			{
				_tile[i][j].objFrameX = 1;
				_tile[i][j].objFrameY = 5;
			}
		}
	}
}

void maptoolScene::showMapTile()
{
	//인게임 화면 지형을 그린다
	if (_ctrlSelect != CTRL_MINETERRAIN && _ctrlSelect != CTRL_MINEOBJECT)
	{
		for (int i = 0; i < DISPLAYY; i++)
		{
			for (int j = 0; j < DISPLAYX; j++)
			{
				//if (i + tileY < 50 && j + tileX < 50)
				//{
					switch (_currentSeason)
					{
					case SPRING:
						IMAGEMANAGER->frameRender("농장(봄)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
							_tile[i + tileY][j + tileX].terrainFrameX, _tile[i + tileY][j + tileX].terrainFrameY);

						if (_tile[i + tileY][j + tileX].isWet)
						{
							IMAGEMANAGER->frameRender("농장(봄)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
								_tile[i + tileY][j + tileX].wetFrameX, _tile[i + tileY][j + tileX].wetFrameY);
						}

						//인게임 화면 오브젝트 그린다
						if (_tile[i + tileY][j + tileX].obj != OBJ_NONE)
						{
							if (_tile[i + tileY][j + tileX].obj == OBJ_BUILDING)
							{
								if (_tile[i + tileY][j + tileX].objType == OTY_SHOP)
								{
									for (int y = 6; y < 10; y++)
									{
										if (i - y >= 0)
										{
											IMAGEMANAGER->frameRender("건물", getMemDC(), _tile[i - y][j].rc.left, _tile[i - y][j].rc.top,
												_tile[i + tileY][j + tileX].objFrameX, _tile[i + tileY][j + tileX].objFrameY - y);
										}
										
									}
									IMAGEMANAGER->frameRender("건물", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
										_tile[i + tileY][j + tileX].objFrameX, _tile[i + tileY][j + tileX].objFrameY);
								}
								else
								{
									IMAGEMANAGER->frameRender("건물", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
										_tile[i + tileY][j + tileX].objFrameX, _tile[i + tileY][j + tileX].objFrameY);
								}
							}
							else if (_tile[i][j].objType == OTY_WOODENFENCE)
							{
								IMAGEMANAGER->findImage("나무펜스")->frameRender(getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
									_tile[i][j].objFrameX, _tile[i][j].objFrameY);
								IMAGEMANAGER->findImage("나무펜스")->frameRender(getMemDC(), _tile[i - 1][j].rc.left, _tile[i - 1][j].rc.top,
									_tile[i][j].objFrameX, _tile[i][j].objFrameY - 1);
							}
							else if (_tile[i][j].objType == OTY_STONEFENCE)
							{
								IMAGEMANAGER->findImage("돌펜스")->frameRender(getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
									_tile[i][j].objFrameX, _tile[i][j].objFrameY);
								IMAGEMANAGER->findImage("돌펜스")->frameRender(getMemDC(), _tile[i - 1][j].rc.left, _tile[i - 1][j].rc.top,
									_tile[i][j].objFrameX, _tile[i][j].objFrameY - 1);
							}
							else
							{
								IMAGEMANAGER->frameRender("농장오브젝트(봄)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
									_tile[i + tileY][j + tileX].objFrameX, _tile[i + tileY][j + tileX].objFrameY);
							}
							if (_tile[i + tileY][j + tileX].objType == OTY_TREE)
							{
								if (i - 5 >= 0 && j - 1 >= 0)
								{
									IMAGEMANAGER->findImage("나무")->frameRender(getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
										_tile[i + tileY][j + tileX].tree.bodyIndexX, _tile[i + tileY][j + tileX].tree.bodyIndexY);
									for (int y = 5; y > 0; y--)
									{
										for (int x = 1; x > -2; x--)
										{
											IMAGEMANAGER->findImage("나무")->frameRender(getMemDC(), _tile[i - y][j - x].rc.left, _tile[i - y][j - x].rc.top,
												_tile[i + tileY][j + tileX].tree.bodyIndexX - 1 - x, _tile[i + tileY][j + tileX].tree.bodyIndexY - 4 - y);
										}
									}
								}
							}
						}
						if (_tile[i + tileY][j + tileX].objOver != OVR_NONE)
						{
							IMAGEMANAGER->frameRender("농장오브젝트(봄)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
								_tile[i + tileY][j + tileX].ovlFrameX, _tile[i + tileY][j + tileX].ovlFrameY);
						}

						break;
					case SUMMER:
						IMAGEMANAGER->frameRender("농장(여름)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
							_tile[i + tileY][j + tileX].terrainFrameX, _tile[i + tileY][j + tileX].terrainFrameY);

						if (_tile[i + tileY][j + tileX].isWet)
						{
							IMAGEMANAGER->frameRender("농장(여름)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
								_tile[i + tileY][j + tileX].wetFrameX, _tile[i + tileY][j + tileX].wetFrameY);
						}

						//인게임 화면 오브젝트 그린다
						if (_tile[i + tileY][j + tileX].obj != OBJ_NONE)
						{
							if (_tile[i + tileY][j + tileX].obj == OBJ_BUILDING)
							{
								IMAGEMANAGER->frameRender("건물", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
									_tile[i + tileY][j + tileX].objFrameX, _tile[i + tileY][j + tileX].objFrameY);
							}
							else if (_tile[i][j].objType == OTY_WOODENFENCE)
							{
								IMAGEMANAGER->findImage("나무펜스")->frameRender(getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
									_tile[i][j].objFrameX, _tile[i][j].objFrameY);
								IMAGEMANAGER->findImage("나무펜스")->frameRender(getMemDC(), _tile[i - 1][j].rc.left, _tile[i - 1][j].rc.top,
									_tile[i][j].objFrameX, _tile[i][j].objFrameY - 1);
							}
							else if (_tile[i][j].objType == OTY_STONEFENCE)
							{
								IMAGEMANAGER->findImage("돌펜스")->frameRender(getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
									_tile[i][j].objFrameX, _tile[i][j].objFrameY);
								IMAGEMANAGER->findImage("돌펜스")->frameRender(getMemDC(), _tile[i - 1][j].rc.left, _tile[i - 1][j].rc.top,
									_tile[i][j].objFrameX, _tile[i][j].objFrameY - 1);
							}
							else
							{
								IMAGEMANAGER->frameRender("농장오브젝트(여름)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
									_tile[i + tileY][j + tileX].objFrameX, _tile[i + tileY][j + tileX].objFrameY);
							}
							if (_tile[i + tileY][j + tileX].objType == OTY_TREE)
							{
								if (i - 5 >= 0 && j - 1 >= 0)
								{
									IMAGEMANAGER->findImage("나무")->frameRender(getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
										_tile[i + tileY][j + tileX].tree.bodyIndexX, _tile[i + tileY][j + tileX].tree.bodyIndexY);
									for (int y = 5; y > 0; y--)
									{
										for (int x = 1; x > -2; x--)
										{
											IMAGEMANAGER->findImage("나무")->frameRender(getMemDC(), _tile[i - y][j - x].rc.left, _tile[i - y][j - x].rc.top,
												_tile[i + tileY][j + tileX].tree.bodyIndexX - 1 - x, _tile[i + tileY][j + tileX].tree.bodyIndexY - 4 - y);
										}
									}
								}
							}
						}
						if (_tile[i + tileY][j + tileX].objOver != OVR_NONE)
						{
							IMAGEMANAGER->frameRender("농장오브젝트(여름)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
								_tile[i + tileY][j + tileX].ovlFrameX, _tile[i + tileY][j + tileX].ovlFrameY);
						}
						break;
					case AUTUMN:
						IMAGEMANAGER->frameRender("농장(가을)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
							_tile[i + tileY][j + tileX].terrainFrameX, _tile[i + tileY][j + tileX].terrainFrameY);

						if (_tile[i + tileY][j + tileX].isWet)
						{
							IMAGEMANAGER->frameRender("농장(가을)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
								_tile[i + tileY][j + tileX].wetFrameX, _tile[i + tileY][j + tileX].wetFrameY);
						}

						//인게임 화면 오브젝트 그린다
						if (_tile[i + tileY][j + tileX].obj != OBJ_NONE)
						{
							if (_tile[i + tileY][j + tileX].obj == OBJ_BUILDING)
							{
								IMAGEMANAGER->frameRender("건물", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
									_tile[i + tileY][j + tileX].objFrameX, _tile[i + tileY][j + tileX].objFrameY);
							}
							else if (_tile[i][j].objType == OTY_WOODENFENCE)
							{
								IMAGEMANAGER->findImage("나무펜스")->frameRender(getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
									_tile[i][j].objFrameX, _tile[i][j].objFrameY);
								IMAGEMANAGER->findImage("나무펜스")->frameRender(getMemDC(), _tile[i - 1][j].rc.left, _tile[i - 1][j].rc.top,
									_tile[i][j].objFrameX, _tile[i][j].objFrameY - 1);
							}
							else if (_tile[i][j].objType == OTY_STONEFENCE)
							{
								IMAGEMANAGER->findImage("돌펜스")->frameRender(getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
									_tile[i][j].objFrameX, _tile[i][j].objFrameY);
								IMAGEMANAGER->findImage("돌펜스")->frameRender(getMemDC(), _tile[i - 1][j].rc.left, _tile[i - 1][j].rc.top,
									_tile[i][j].objFrameX, _tile[i][j].objFrameY - 1);
							}
							else
							{
								IMAGEMANAGER->frameRender("농장오브젝트(가을)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
									_tile[i + tileY][j + tileX].objFrameX, _tile[i + tileY][j + tileX].objFrameY);
							}
							if (_tile[i + tileY][j + tileX].objType == OTY_TREE)
							{
								if (i - 5 >= 0 && j - 1 >= 0)
								{
									IMAGEMANAGER->findImage("나무")->frameRender(getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
										_tile[i + tileY][j + tileX].tree.bodyIndexX, _tile[i + tileY][j + tileX].tree.bodyIndexY);
									for (int y = 5; y > 0; y--)
									{
										for (int x = 1; x > -2; x--)
										{
											IMAGEMANAGER->findImage("나무")->frameRender(getMemDC(), _tile[i - y][j - x].rc.left, _tile[i - y][j - x].rc.top,
												_tile[i + tileY][j + tileX].tree.bodyIndexX - 1 - x, _tile[i + tileY][j + tileX].tree.bodyIndexY - 4 - y);
										}
									}
								}
							}
						}
						if (_tile[i + tileY][j + tileX].objOver != OVR_NONE)
						{
							IMAGEMANAGER->frameRender("농장오브젝트(가을)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
								_tile[i + tileY][j + tileX].ovlFrameX, _tile[i + tileY][j + tileX].ovlFrameY);
						}
						break;
					case WINTER:
						IMAGEMANAGER->frameRender("농장(겨울)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
							_tile[i + tileY][j + tileX].terrainFrameX, _tile[i + tileY][j + tileX].terrainFrameY);

						if (_tile[i + tileY][j + tileX].isWet)
						{
							IMAGEMANAGER->frameRender("농장(겨울)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
								_tile[i + tileY][j + tileX].wetFrameX, _tile[i + tileY][j + tileX].wetFrameY);
						}

						//인게임 화면 오브젝트 그린다
						if (_tile[i + tileY][j + tileX].obj != OBJ_NONE)
						{
							if (_tile[i + tileY][j + tileX].obj == OBJ_BUILDING)
							{
								IMAGEMANAGER->frameRender("건물", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
									_tile[i + tileY][j + tileX].objFrameX, _tile[i + tileY][j + tileX].objFrameY);
							}
							else if (_tile[i][j].objType == OTY_WOODENFENCE)
							{
								IMAGEMANAGER->findImage("나무펜스")->frameRender(getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
									_tile[i][j].objFrameX, _tile[i][j].objFrameY);
								IMAGEMANAGER->findImage("나무펜스")->frameRender(getMemDC(), _tile[i - 1][j].rc.left, _tile[i - 1][j].rc.top,
									_tile[i][j].objFrameX, _tile[i][j].objFrameY - 1);
							}
							else if (_tile[i][j].objType == OTY_STONEFENCE)
							{
								IMAGEMANAGER->findImage("돌펜스")->frameRender(getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
									_tile[i][j].objFrameX, _tile[i][j].objFrameY);
								IMAGEMANAGER->findImage("돌펜스")->frameRender(getMemDC(), _tile[i - 1][j].rc.left, _tile[i - 1][j].rc.top,
									_tile[i][j].objFrameX, _tile[i][j].objFrameY - 1);
							}
							else
							{
								IMAGEMANAGER->frameRender("농장오브젝트(겨울)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
									_tile[i + tileY][j + tileX].objFrameX, _tile[i + tileY][j + tileX].objFrameY);
							}
							if (_tile[i + tileY][j + tileX].objType == OTY_TREE)
							{
								if (i - 5 >= 0 && j - 1 >= 0)
								{
									IMAGEMANAGER->findImage("나무")->frameRender(getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
										_tile[i + tileY][j + tileX].tree.bodyIndexX, _tile[i + tileY][j + tileX].tree.bodyIndexY);
									for (int y = 5; y > 0; y--)
									{
										for (int x = 1; x > -2; x--)
										{
											IMAGEMANAGER->findImage("나무")->frameRender(getMemDC(), _tile[i - y][j - x].rc.left, _tile[i - y][j - x].rc.top,
												_tile[i + tileY][j + tileX].tree.bodyIndexX - 1 - x, _tile[i + tileY][j + tileX].tree.bodyIndexY - 4 - y);
										}
									}
								}
							}
						}
						if (_tile[i + tileY][j + tileX].objOver != OVR_NONE)
						{
							IMAGEMANAGER->frameRender("농장오브젝트(겨울)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
								_tile[i + tileY][j + tileX].ovlFrameX, _tile[i + tileY][j + tileX].ovlFrameY);
						}
						break;
					}
				//}
			}
		}
	}
	else
	{
		char str[64];
		char objstr[64];
		switch (_currentMine)
		{
		case MINE_NORMAL:
			sprintf(str, "광산 노말");
			sprintf(objstr, "광산오브젝트 노말");
			break;
		case MINE_NORMALDARK:
			sprintf(str, "광산 노말다크");
			sprintf(objstr, "광산오브젝트 노말다크");
			break;
		case MINE_FROST:
			sprintf(str, "광산 프로스트");
			sprintf(objstr, "광산오브젝트 프로스트");
			break;
		case MINE_FROSTDARK:
			sprintf(str, "광산 프로스트다크");
			sprintf(objstr, "광산오브젝트 프로스트다크");
			break;
		}

		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				if (i + tileY < 50 && j + tileX < 50)
				{
					IMAGEMANAGER->frameRender(str, getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
						_tile[i + tileY][j + tileX].terrainFrameX, _tile[i + tileY][j + tileX].terrainFrameY);

					if (_tile[i + tileY][j + tileX].obj != OBJ_NONE)
					{
						IMAGEMANAGER->frameRender(objstr, getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
							_tile[i + tileY][j + tileX].objFrameX, _tile[i + tileY][j + tileX].objFrameY);
					}
				}
			}
		}
	}
}

void maptoolScene::showControlButton()
{
	//Rectangle(getMemDC(), _rcSave);
	IMAGEMANAGER->findImage("세이브")->render(getMemDC(), _rcSave.left, _rcSave.top);
	//Rectangle(getMemDC(), _rcLoad);
	IMAGEMANAGER->findImage("로드")->render(getMemDC(), _rcLoad.left, _rcLoad.top);
	//Rectangle(getMemDC(), _rcTerrain);
	IMAGEMANAGER->findImage("지형")->render(getMemDC(), _rcTerrain.left, _rcTerrain.top);
	//Rectangle(getMemDC(), _rcObject);
	IMAGEMANAGER->findImage("오브젝트")->render(getMemDC(), _rcObject.left, _rcObject.top);
	//Rectangle(getMemDC(), _rcEraser);
	IMAGEMANAGER->findImage("지우개")->render(getMemDC(), _rcEraser.left, _rcEraser.top);
	//Rectangle(getMemDC(), _rcobjectDelete);
	IMAGEMANAGER->findImage("오브젝트지우개")->render(getMemDC(), _rcobjectDelete.left, _rcobjectDelete.top);
	//Rectangle(getMemDC(), _rcObject2);
	IMAGEMANAGER->findImage("건물버튼")->render(getMemDC(), _rcObject2.left, _rcObject2.top);
	Rectangle(getMemDC(), _rcMineTerrain);
	Rectangle(getMemDC(), _rcMineObject);
	IMAGEMANAGER->findImage("광산지형버튼")->render(getMemDC(), _rcMineTerrain.left, _rcMineTerrain.top);
	IMAGEMANAGER->findImage("광산오브젝트버튼")->render(getMemDC(), _rcMineObject.left, _rcMineObject.top);
	//Rectangle(getMemDC(), _rcMineNormal);
	//Rectangle(getMemDC(), _rcMineNormalDark);
	//Rectangle(getMemDC(), _rcMineFrost);
	//Rectangle(getMemDC(), _rcMineFrostDark);
	IMAGEMANAGER->findImage("노말버튼")->render(getMemDC(), _rcMineNormal.left, _rcMineNormal.top);
	IMAGEMANAGER->findImage("노말다크버튼")->render(getMemDC(), _rcMineNormalDark.left, _rcMineNormalDark.top);
	IMAGEMANAGER->findImage("프로스트버튼")->render(getMemDC(), _rcMineFrost.left, _rcMineFrost.top);
	IMAGEMANAGER->findImage("프로스트다크버튼")->render(getMemDC(), _rcMineFrostDark.left, _rcMineFrostDark.top);

	if (isSelectSeason)
	{
		Rectangle(getMemDC(), _rcSpring);
		IMAGEMANAGER->render("봄", getMemDC(), _rcSpring.left, _rcSpring.top);
		Rectangle(getMemDC(), _rcSummer);
		IMAGEMANAGER->render("여름", getMemDC(), _rcSummer.left, _rcSummer.top);
		Rectangle(getMemDC(), _rcAutumn);
		IMAGEMANAGER->render("가을", getMemDC(), _rcAutumn.left, _rcAutumn.top);
		Rectangle(getMemDC(), _rcWinter);
		IMAGEMANAGER->render("겨울", getMemDC(), _rcWinter.left, _rcWinter.top);
	}
}

void maptoolScene::showScrollBar()
{
	Rectangle(getMemDC(), horScroll);
	Rectangle(getMemDC(), vertScroll);
	if (sampleTileMaxFrameX > SAMPLEDISPLAYX) { Rectangle(getMemDC(), sampleHorScroll); }
	if (sampleTileMaxFrameY > SAMPLEDISPLAYY) { Rectangle(getMemDC(), sampleVertScroll); }
}

void maptoolScene::showSampleTerrainTile()
{
	if (_ctrlSelect == CTRL_TERRAIN)
	{
		switch (_currentSeason)
		{
		case SPRING:
			for (int i = 0; i < SAMPLEDISPLAYY; i++)
			{
				for (int j = 0; j < SAMPLEDISPLAYX; j++)
				{
					if (j < sampleTileMaxFrameX && i < sampleTileMaxFrameY)
					{
						IMAGEMANAGER->frameRender("농장(봄)", getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
							_sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameX, _sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameY);
					}
				}
			}
			break;
		case SUMMER:
			for (int i = 0; i < SAMPLEDISPLAYY; i++)
			{
				for (int j = 0; j < SAMPLEDISPLAYX; j++)
				{
					if (j < sampleTileMaxFrameX && i < sampleTileMaxFrameY)
					{
						IMAGEMANAGER->frameRender("농장(여름)", getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
							_sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameX, _sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameY);
					}
				}
			}
			break;
		case AUTUMN:
			for (int i = 0; i < SAMPLEDISPLAYY; i++)
			{
				for (int j = 0; j < SAMPLEDISPLAYX; j++)
				{
					if (j < sampleTileMaxFrameX && i < sampleTileMaxFrameY)
					{
						IMAGEMANAGER->frameRender("농장(가을)", getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
							_sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameX, _sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameY);
					}
				}
			}
			break;
		case WINTER:
			for (int i = 0; i < SAMPLEDISPLAYY; i++)
			{
				for (int j = 0; j < SAMPLEDISPLAYX; j++)
				{
					if (j < sampleTileMaxFrameX && i < sampleTileMaxFrameY)
					{
						IMAGEMANAGER->frameRender("농장(겨울)", getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
							_sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameX, _sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameY);
					}
				}
			}
			break;
		}
	}
	else if (_ctrlSelect == CTRL_MINETERRAIN)
	{
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (j < sampleTileMaxFrameX && i < sampleTileMaxFrameY)
				{
					char str[64];
					switch (_currentMine)
					{
					case MINE_NORMAL:
						sprintf(str, "광산 노말");
						break;
					case MINE_NORMALDARK:
						sprintf(str, "광산 노말다크");
						break;
					case MINE_FROST:
						sprintf(str, "광산 프로스트");
						break;
					case MINE_FROSTDARK:
						sprintf(str, "광산 프로스트다크");
						break;
					}
					IMAGEMANAGER->frameRender(str, getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
						_sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameX, _sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameY);
				}
			}
		}
	}
}
	
void maptoolScene::showSampleObjectTile()
{
	if (_ctrlSelect == CTRL_OBJECT)
	{
		switch (_currentSeason)
		{
		case SPRING:
			for (int i = 0; i < SAMPLEDISPLAYY; i++)
			{
				for (int j = 0; j < SAMPLEDISPLAYX; j++)
				{
					if (j < sampleTileMaxFrameX && i < sampleTileMaxFrameY)
					{
						IMAGEMANAGER->frameRender("농장오브젝트(봄)", getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
							_sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameX, _sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameY);
					}
				}
			}
			break;
		case SUMMER:
			for (int i = 0; i < SAMPLEDISPLAYY; i++)
			{
				for (int j = 0; j < SAMPLEDISPLAYX; j++)
				{
					if (j < sampleTileMaxFrameX && i < sampleTileMaxFrameY)
					{
						IMAGEMANAGER->frameRender("농장오브젝트(여름)", getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
							_sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameX, _sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameY);
					}
				}
			}
			break;
		case AUTUMN:
			for (int i = 0; i < SAMPLEDISPLAYY; i++)
			{
				for (int j = 0; j < SAMPLEDISPLAYX; j++)
				{
					if (j < sampleTileMaxFrameX && i < sampleTileMaxFrameY)
					{
						IMAGEMANAGER->frameRender("농장오브젝트(가을)", getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
							_sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameX, _sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameY);
					}
				}
			}
			break;
		case WINTER:
			for (int i = 0; i < SAMPLEDISPLAYY; i++)
			{
				for (int j = 0; j < SAMPLEDISPLAYX; j++)
				{
					if (j < sampleTileMaxFrameX && i < sampleTileMaxFrameY)
					{
						IMAGEMANAGER->frameRender("농장오브젝트(겨울)", getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
							_sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameX, _sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameY);
					}
				}
			}
			break;
		}
	}
	if (_ctrlSelect == CTRL_OBJECT2)
	{
		for (int i = 0; i < SAMPLEDISPLAYY; i++)
		{
			for (int j = 0; j < SAMPLEDISPLAYX; j++)
			{
				if (j < sampleTileMaxFrameX && i < sampleTileMaxFrameY)
				{
					IMAGEMANAGER->frameRender("건물", getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
						_sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameX, _sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameY);
				}
			}
		}
	}
	if (_ctrlSelect == CTRL_MINEOBJECT)
	{
		for (int i = 0; i < 18; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (j < 16 && i < 18)
				{
					char str[64];
					switch (_currentMine)
					{
					case MINE_NORMAL:
						sprintf(str, "광산오브젝트 노말");
						break;
					case MINE_NORMALDARK:
						sprintf(str, "광산오브젝트 노말다크");
						break;
					case MINE_FROST:
						sprintf(str, "광산오브젝트 프로스트");
						break;
					case MINE_FROSTDARK:
						sprintf(str, "광산오브젝트 프로스트다크");
						break;
					}
					IMAGEMANAGER->frameRender(str, getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
						_sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameX, _sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameY);
				}
			}
		}
	}
}

void maptoolScene::setMineMap()
{
	if (PtInRect(&_rcMineNormal, _ptMouse))
	{
		_currentMine = MINE_NORMAL;
		resetSampleScrollBar();
	}
	if (PtInRect(&_rcMineNormalDark, _ptMouse))
	{
		_currentMine = MINE_NORMALDARK;
		resetSampleScrollBar();
	}
	if (PtInRect(&_rcMineFrost, _ptMouse))
	{
		_currentMine = MINE_FROST;
		resetSampleScrollBar();
	}
	if (PtInRect(&_rcMineFrostDark, _ptMouse))
	{
		_currentMine = MINE_FROSTDARK;
		resetSampleScrollBar();
	}
}

TERRAIN maptoolScene::terrainSelect(int frameX, int frameY)
{
	if (_ctrlSelect != CTRL_MINETERRAIN)
	{
		if ((frameX == 1 && frameY == 1) || (frameX == 31 && (frameY == 0 || frameY == 1))
			|| ((frameX == 1 || 2) && frameY == 3) || (frameX == 3 && frameY == 0)
			|| (frameX == 5 && frameY == 0) || (frameX == 7 && frameY == 1)
			|| (frameX == 6 && frameY == 2))
		{
			return TR_SOIL;
		}
		//물
		if ((frameX == 7 || frameX == 8 || frameX == 9 || frameX == 10) && frameY == 6)
		{
			return TR_WATER;
		}
		//경작지
		if ((frameX == 20 && frameY == 12) || (frameX == 20 && frameY == 14))
		{
			return TR_HACKED;
		}
		//기타
		return TR_GROUND;
	}
	else if (_ctrlSelect == CTRL_MINETERRAIN)
	{
		return TR_GROUND;
	}
}

OBJECT maptoolScene::objectSelect(int frameX, int frameY)
{
	return OBJ_INDESTRUCTIBLE;
}

OBJ_OVERLAPPED maptoolScene::overlappedSelect(int frameX, int frameY)
{
	if (frameX > 24 && frameX < 42 && frameY == 18)						//다리 손잡이
	{
		return OVR_OVER;
	}
	if ((frameX == 30 || frameX == 33) && frameY == 24)					//다리 끊어진 손잡이
	{
		return OVR_OVER;
	}
	if (frameX >= 17 && frameX <= 21 && frameY >= 18 && frameY <= 22)	//벛나무
	{
		return OVR_OVER;
	}
	if (frameX >= 4 && frameX <= 6 && frameY >= 19 && frameY <= 23)	//나무1
	{
		return OVR_OVER;
	}
	if (frameX >= 7 && frameX <= 9 && frameY >= 19 && frameY <= 23)	//나무2
	{
		return OVR_OVER;
	}
	if (frameX >= 10 && frameX <= 12 && frameY >= 19 && frameY <= 23)	//나무3
	{
		return OVR_OVER;
	}
	if (frameX >= 13 && frameX <= 16 && frameY >= 18 && frameY <= 22)	//나무4
	{
		return OVR_OVER;
	}

	return OVR_NONE;
}

OBJ_TYPE maptoolScene::objectTypeSelect(int frameX, int frameY)
{
	return OBJ_TYPE();
}

INT_PTR maptoolScene::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		if (_isSave)
		{
			SetWindowText(hWnd, "세이브");
		}
		else
		{
			SetWindowText(hWnd, "로드");
		}
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			memset(saveName, 0, sizeof(saveName));
			GetDlgItemText(hWnd, IDC_EDIT1, saveName, MAX_PATH);
		case IDCANCEL:
			EndDialog(hWnd, IDOK);
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}
