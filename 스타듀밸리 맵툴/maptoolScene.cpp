#include "stdafx.h"
#include "maptoolScene.h"

HRESULT maptoolScene::init()
{
	//Ÿ�ϸ� �̹��� �ʱ�ȭ -> 09.22 �ε� ������ �Ѿ

	//��������
	sampleTileMaxFrameX = IMAGEMANAGER->findImage("����(��)")->getMaxFrameX() + 1;
	sampleTileMaxFrameY = IMAGEMANAGER->findImage("����(��)")->getMaxFrameY() + 1;
	this->maptoolSetup();
	this->setScroll();

	//�巡��
	first_i = first_j = last_i = last_j = 0;
	_click = false;
	_release = false;
	_isSampleDrag = false;
	_ischange = false;
	_isDragSet = false;
	_prevent_double = false;

	//����Ÿ�� �ʱ�ȭ (���� = �ܵ�)
	_currentTile.x = 0;
	_currentTile.y = 6;

	_currentSeason = SPRING;

	sampleTileX = 0;
	sampleTileY = 0;

	tileX = tileY = 0;

	isSelectSeason = isHorLock = isVertLock = isSampleHorLock = isSampleVertLock = false;

	//�����׸��� �Ӽ����� �����ϱ�
	_ctrlSelect = CTRL_TERRAIN;

	return S_OK;
}

void maptoolScene::release()
{
}

void maptoolScene::update()
{
	//�巡��
	if (_isDragSet)
	{
		setMap_Drag();
	}
	else if(!_isDragSet/* && !_prevent_double*/)
	{
		//��ư �������� ��Ʈ��
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			lockScroll();
			selectSeason();

			if (PtInRect(&_rcSave, _ptMouse))
			{
				_ctrlSelect = CTRL_SAVE;
				this->save();
			}
			if (PtInRect(&_rcLoad, _ptMouse))
			{
				_ctrlSelect = CTRL_LOAD;
				this->load();
			}
			if (PtInRect(&_rcTerrain, _ptMouse))
			{
				//���� �϶� or ���� â�� ������, ��ư�� ������ �������� â �����
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
				//������Ʈ �϶� or ���� â�� ������, ��ư�� ������ �������� â �����
				if (_ctrlSelect != CTRL_OBJECT || !isSelectSeason)
				{
					_ctrlSelect = CTRL_OBJECT;
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
		}

		//��ư ���� ��ũ�� �� false
		if (INPUT->GetKeyUp(VK_LBUTTON))
		{
			isHorLock = isVertLock = isSampleHorLock = isSampleVertLock = false;
		}
		//������ �ִ� ��Ȳ
		if (INPUT->GetKey(VK_LBUTTON))
		{
			//��ũ���� ������ �ִٸ�
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

	if (_isSampleDrag) this->sample_Drag();
	else this->setTerrainMap();

	moveTile();
	checkHacked();
}

void maptoolScene::render()
{
	IMAGEMANAGER->render("���", getMemDC(), 0, 0);

	if (_ctrlSelect == CTRL_TERRAIN) { showSampleTerrainTile(); } //���� Ÿ�� �����ִ� �Լ�
	else if (_ctrlSelect == CTRL_OBJECT) { showSampleObjectTile(); }//������Ʈ Ÿ�� �����ִ� �Լ�
	
	//���찳 ������ �� ���� ���ִ� ���� �״�� ���ְ� ����
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
		}
	}

	//�ΰ��� ȭ�� ������ �׸���
	showMapTile();

	//���� ����ȭ�� �� ������ ����Ÿ�� ��Ʈ �����ֱ�
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

	//��Ʈ�� ��ư ���
	showControlButton();

	//��ũ�� �� ���
	showScrollBar();

	if (_click)
	{
		//�巡�� ������ �Ʒ�
		if (first_i <= last_i && first_j <= last_j)
		{
			FrameRect(getMemDC(), RectMake(first.left, first.top, last.right - first.left, last.bottom - first.top), RGB(255, 0, 0));
		}
		//�巡�� ���� �Ʒ�
		else if (first_i <= last_i && first_j > last_j)
		{
			FrameRect(getMemDC(), RectMake(last.left, first.top, first.right - last.left, last.bottom - first.top), RGB(255, 0, 0));
		}
		//�巡�� ���� ��
		else if (first_i > last_i && first_j > last_j)
		{
			FrameRect(getMemDC(), RectMake(last.left, last.top, first.right - last.left, first.bottom - last.top), RGB(255, 0, 0));
		}
		//�巡�� ������ ��
		else if (first_i > last_i && first_j <= last_j)
		{
			FrameRect(getMemDC(), RectMake(first.left, last.top, last.right - first.left, first.bottom - last.top), RGB(255, 0, 0));
		}
	}

	//������ Ÿ�� ũ�⸸ŭ ����ٴϴ� ���� ��Ʈ

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
				}
				if (INPUT->GetKey(VK_RBUTTON))
				{
					last = _sampleTile[i][j].rc;
					last_i = i;
					last_j = j;
				}
				if (INPUT->GetKeyUp(VK_RBUTTON))
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
	//������ ����Ÿ�� ��Ʈ �ʱ�ȭ
	for (int i = 0; i < sampleTileMaxFrameY; i++)
	{
		_sampleTileX.clear();
		for (int j = 0; j < sampleTileMaxFrameX; j++)
		{
			tagTile temp;
			if (j < SAMPLEDISPLAYX && i < SAMPLEDISPLAYY)
			{
				//Ÿ�ϸ� �̹��� ��üȭ�� ������ܿ� ��ġ�ϱ�
				temp.rc = RectMake(660 + j * TILESIZE, 50 + i * TILESIZE, TILESIZE, TILESIZE);
			}
			temp.terrainFrameX = j;
			temp.terrainFrameY = i;

			_sampleTileX.push_back(temp);
		}
		_sampleTile.push_back(_sampleTileX);
	}

	//���� �ΰ��� ȭ�� ��� �ܵ� �⺻ Ÿ���� �ǵ��� �����ϱ�
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			//���� �ΰ��� ȭ�� ��Ʈ �ʱ�ȭ
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
			_tile[i][j].objType = OT_ACCESSIBLE;
			_tile[i][j].isWet = false;
		}
	}

	//��Ʈ�� ��Ʈ ��ġ �ʱ�ȭ
	_rcSave = RectMake(660, 400, 100, 50);
	_rcLoad = RectMake(660 + 100, 400, 100, 50);
	_rcTerrain = RectMake(660, 400 + 100, 100, 50);
	_rcObject = RectMake(660 + 100, 400 + 100, 100, 50);
	_rcEraser = RectMake(660 + 200, 400 + 100, 100, 50);

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

	//�ΰ���ȭ�� ��Ʈ�� �浹�߳�?
	for (int i = 0; i < DISPLAYY; i++)
	{
		for (int j = 0; j < DISPLAYX; j++)
		{
			if (PtInRect(&_tile[i][j].rc, _ptMouse))
			{
				//�����ư�� �����̳�?
				if (_ctrlSelect == CTRL_TERRAIN)
				{
					_tile[i + tileY][j + tileX].terrainFrameX = _currentTile.x;
					_tile[i + tileY][j + tileX].terrainFrameY = _currentTile.y;
					_tile[i + tileY][j + tileX].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				//�����ư�� ������Ʈ��?
				if (_ctrlSelect == CTRL_OBJECT)
				{
					_tile[i + tileY][j + tileX].objFrameX = _currentTile.x;
					_tile[i + tileY][j + tileX].objFrameY = _currentTile.y;
					_tile[i + tileY][j + tileX].obj = objectSelect(_currentTile.x, _currentTile.y);
				}
				//�����ư�� ���찳��?
				if (_ctrlSelect == CTRL_ERASER)
				{
					_tile[i + tileY][j + tileX].objFrameX = 0;
					_tile[i + tileY][j + tileX].objFrameY = 0;
					_tile[i + tileY][j + tileX].obj = OBJ_NONE;
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
					if (INPUT->GetKeyUp(VK_RBUTTON))
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
	if (_click)
	{
		if (_ptMouse.x >= _tile[0][DISPLAYX-1].rc.right)
		{
			_click = false;
			_release = true;
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

				if (_ctrlSelect == CTRL_TERRAIN)
				{
					_tile[i + tileY][j + tileX].terrainFrameX = _currentTile.x;
					_tile[i + tileY][j + tileX].terrainFrameY = _currentTile.y;
					_tile[i + tileY][j + tileX].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				else if (_ctrlSelect == CTRL_OBJECT)
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
				}
			}
		}
		_release = false;
	}
}

void maptoolScene::save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("save.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _tile, sizeof(_tile), &write, NULL);
	CloseHandle(file);
}

void maptoolScene::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tile, sizeof(_tile), &read, NULL);
	CloseHandle(file);
}

void maptoolScene::setScroll()
{
	//��ũ�� �� �ʱ�ȭ
	horScroll = RectMake(_tile[0][0].rc.left, _tile[DISPLAYY - 1][0].rc.bottom + 10, TILESIZE * DISPLAYX / 2, 10);
	vertScroll = RectMake(_tile[0][DISPLAYX - 1].rc.right + 10, _tile[0][0].rc.top, 10, TILESIZE * DISPLAYY / 2);

	sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
	sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);
}

void maptoolScene::resetSampleScrollBar()
{
	//���� ��ũ�� �� ��ġ �ʱ�ȭ
	sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
	sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);
}

void maptoolScene::lockScroll()
{
	//��ũ�� �� ������ �� ���콺 ��ġ, ��ũ�ѹ� Left, Top ��ǥ ���� (��ũ�ѹ� �̵� �Ÿ� �����)
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
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("����(��)")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("����(��)")->getMaxFrameY() + 1;
				resetSampleTile();
				sampleTileX = sampleTileY = 0;

				//���÷��� ������� ���� �������� ������
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
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("����(����)")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("����(����)")->getMaxFrameY() + 1;
				resetSampleTile();
				sampleTileX = sampleTileY = 0;
			}
			if (PtInRect(&_rcAutumn, _ptMouse))
			{
				sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
				sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);

				_currentSeason = AUTUMN;
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("����(����)")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("����(����)")->getMaxFrameY() + 1;
				resetSampleTile();
				sampleTileX = sampleTileY = 0;
			}
			if (PtInRect(&_rcWinter, _ptMouse))
			{
				sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
				sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);

				_currentSeason = WINTER;
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("����(�ܿ�)")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("����(�ܿ�)")->getMaxFrameY() + 1;
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
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("���������Ʈ(��)")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("���������Ʈ(��)")->getMaxFrameY() + 1;
				resetSampleTile();
			}
			if (PtInRect(&_rcSummer, _ptMouse))
			{
				sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
				sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);

				_currentSeason = SUMMER;
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("���������Ʈ(����)")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("���������Ʈ(����)")->getMaxFrameY() + 1;
				resetSampleTile();
			}
			if (PtInRect(&_rcAutumn, _ptMouse))
			{
				sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
				sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);

				_currentSeason = AUTUMN;
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("���������Ʈ(����)")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("���������Ʈ(����)")->getMaxFrameY() + 1;
				resetSampleTile();
			}
			if (PtInRect(&_rcWinter, _ptMouse))
			{
				sampleHorScroll = RectMake(_sampleTile[0][0].rc.left, _sampleTile[SAMPLEDISPLAYY - 1][0].rc.bottom + 10, TILESIZE * SAMPLEDISPLAYX / 2, 10);
				sampleVertScroll = RectMake(_sampleTile[0][SAMPLEDISPLAYX - 1].rc.right + 10, _sampleTile[0][0].rc.top, 10, TILESIZE * SAMPLEDISPLAYY / 2);

				_currentSeason = WINTER;
				sampleTileMaxFrameX = IMAGEMANAGER->findImage("���������Ʈ(�ܿ�)")->getMaxFrameX() + 1;
				sampleTileMaxFrameY = IMAGEMANAGER->findImage("���������Ʈ(�ܿ�)")->getMaxFrameY() + 1;
				resetSampleTile();
				sampleTileX = sampleTileY = 0;
			}
			break;
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
			if (j < sampleTileMaxFrameX && i < sampleTileMaxFrameY)
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

//���� ���� üũ
void maptoolScene::checkHacked()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			if (_tile[i][j].terrain == TR_HACKED)
			{
				if (_tile[i][j].isWet)
				{
					_tile[i][j].terrainFrameX = 20;
					_tile[i][j].terrainFrameY = 14;
				}
				else
				{
					_tile[i][j].terrainFrameX = 20;
					_tile[i][j].terrainFrameY = 12;
				}
				if (_tile[i][j - 1].terrain == TR_HACKED) //����
				{
					if (_tile[i][j].isWet)
					{
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 15;
					}
					else
					{
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 13;
					}
				}
				if (_tile[i][j + 1].terrain == TR_HACKED) //������
				{
					if (_tile[i][j].isWet)
					{
						_tile[i][j].terrainFrameX = 20;
						_tile[i][j].terrainFrameY = 15;
					}
					else
					{
						_tile[i][j].terrainFrameX = 20;
						_tile[i][j].terrainFrameY = 13;
					}
				}
				if (_tile[i - 1][j].terrain == TR_HACKED) //��
				{
					if (_tile[i][j].isWet)
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 15;
					}
					else
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 13;
					}
				}
				if (_tile[i + 1][j].terrain == TR_HACKED) //�Ʒ�
				{
					if (_tile[i][j].isWet)
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 14;
					}
					else
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 12;
					}
				}
				if (_tile[i][j - 1].terrain == TR_HACKED && _tile[i][j + 1].terrain == TR_HACKED)			//��+��
				{
					if (_tile[i][j].isWet)
					{
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 22;
					}
					else
					{
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 20;
					}
				}
				if (_tile[i - 1][j].terrain == TR_HACKED && _tile[i + 1][j].terrain == TR_HACKED)			//��+�Ʒ�
				{
					if (_tile[i][j].isWet)
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 20;
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
						&& _tile[i - 1][j - 1].terrain == TR_HACKED))	//��+�� ||  //��+��+�޴밢
				{
					if (_tile[i][j].isWet)
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 23;
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
						&& _tile[i + 1][j + 1].terrain == TR_HACKED))	 //��+�� || ��+��+���밢
				{
					if (_tile[i][j].isWet)
					{
						_tile[i][j].terrainFrameX = 20;
						_tile[i][j].terrainFrameY = 23;
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
						&& _tile[i + 1][j - 1].terrain == TR_HACKED))	//�Ʒ�+�� || �Ʒ�+��+�޴밢
				{
					if (_tile[i][j].isWet)
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 18;
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
						&& _tile[i + 1][j + 1].terrain == TR_HACKED))	//�Ʒ�+�� || �Ʒ�+��+���밢
				{
					if (_tile[i][j].isWet)
					{
						_tile[i][j].terrainFrameX = 20;
						_tile[i][j].terrainFrameY = 18;
					}
					else
					{
						_tile[i][j].terrainFrameX = 20;
						_tile[i][j].terrainFrameY = 16;
					}
				}
				if (_tile[i - 1][j].terrain == TR_HACKED
					&& _tile[i][j - 1].terrain == TR_HACKED
					&& _tile[i + 1][j].terrain == TR_HACKED)		//��+��+�Ʒ�
				{
					if (_tile[i][j].isWet)
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 19;
					}
					else
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 17;
					}
				}
				if (_tile[i - 1][j].terrain == TR_HACKED
					&& _tile[i][j + 1].terrain == TR_HACKED
					&& _tile[i + 1][j].terrain == TR_HACKED)		//��+��+�Ʒ�
				{
					if (_tile[i][j].isWet)
					{
						_tile[i][j].terrainFrameX = 20;
						_tile[i][j].terrainFrameY = 19;
					}
					else
					{
						_tile[i][j].terrainFrameX = 20;
						_tile[i][j].terrainFrameY = 17;
					}
				}
				if (_tile[i - 1][j].terrain == TR_HACKED
					&& _tile[i][j - 1].terrain == TR_HACKED
					&& _tile[i][j + 1].terrain == TR_HACKED)		//��+��+��
				{
					if (_tile[i][j].isWet)
					{
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 23;
					}
					else
					{
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 21;
					}
				}
				if (_tile[i + 1][j].terrain == TR_HACKED
					&& _tile[i][j - 1].terrain == TR_HACKED
					&& _tile[i][j + 1].terrain == TR_HACKED)		//�Ʒ�+��+�� 
				{
					if (_tile[i][j].isWet)
					{
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 18;
					}
					else
					{
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 16;
					}
				}
				if (	(_tile[i - 1][j].terrain == TR_HACKED
						&& _tile[i + 1][j].terrain == TR_HACKED
						&& _tile[i][j - 1].terrain == TR_HACKED
						&& _tile[i][j + 1].terrain == TR_HACKED)		//���Ʒ��޿� (4��)
					|| (_tile[i - 1][j].terrain == TR_HACKED			
						&& _tile[i + 1][j].terrain == TR_HACKED			
						&& _tile[i][j - 1].terrain == TR_HACKED			
						&& _tile[i][j + 1].terrain == TR_HACKED			
						&& _tile[i - 1][j - 1].terrain == TR_HACKED		
						&& _tile[i + 1][j - 1].terrain == TR_HACKED		
						&& _tile[i - 1][j + 1].terrain == TR_HACKED		
						&& _tile[i + 1][j + 1].terrain == TR_HACKED))	//���Ʒ��翷�밢4�� ���	(8��)
				{
					//�⺻ �׸�
					if (_tile[i][j].isWet)
					{
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 19;
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
}

void maptoolScene::showMapTile()
{
	//�ΰ��� ȭ�� ������ �׸���
	for (int i = 0; i < DISPLAYY; i++)
	{
		for (int j = 0; j < DISPLAYX; j++)
		{
			switch (_currentSeason)
			{
			case SPRING:
				IMAGEMANAGER->frameRender("����(��)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i + tileY][j + tileX].terrainFrameX, _tile[i + tileY][j + tileX].terrainFrameY);

				//�ΰ��� ȭ�� ������Ʈ �׸���
				if (_tile[i + tileY][j + tileX].obj == OBJ_NONE) continue;
				IMAGEMANAGER->frameRender("���������Ʈ(��)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i + tileY][j + tileX].objFrameX, _tile[i + tileY][j + tileX].objFrameY);
				break;
			case SUMMER:
				IMAGEMANAGER->frameRender("����(����)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i + tileY][j + tileX].terrainFrameX, _tile[i + tileY][j + tileX].terrainFrameY);

				//�ΰ��� ȭ�� ������Ʈ �׸���
				if (_tile[i + tileY][j + tileX].obj == OBJ_NONE) continue;
				IMAGEMANAGER->frameRender("���������Ʈ(����)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i + tileY][j + tileX].objFrameX, _tile[i + tileY][j + tileX].objFrameY);
				break;
			case AUTUMN:
				IMAGEMANAGER->frameRender("����(����)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
				_tile[i + tileY][j + tileX].terrainFrameX, _tile[i + tileY][j + tileX].terrainFrameY);

				//�ΰ��� ȭ�� ������Ʈ �׸���
				if (_tile[i + tileY][j + tileX].obj == OBJ_NONE) continue;
				IMAGEMANAGER->frameRender("���������Ʈ(����)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i + tileY][j + tileX].objFrameX, _tile[i + tileY][j + tileX].objFrameY);
				break;
			case WINTER:
				IMAGEMANAGER->frameRender("����(�ܿ�)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i + tileY][j + tileX].terrainFrameX, _tile[i + tileY][j + tileX].terrainFrameY);

				//�ΰ��� ȭ�� ������Ʈ �׸���
				if (_tile[i + tileY][j + tileX].obj == OBJ_NONE) continue;
				IMAGEMANAGER->frameRender("���������Ʈ(�ܿ�)", getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i + tileY][j + tileX].objFrameX, _tile[i + tileY][j + tileX].objFrameY);
				break;
			}
		}
	}
}

void maptoolScene::showControlButton()
{
	Rectangle(getMemDC(), _rcSave);
	IMAGEMANAGER->findImage("���̺�")->render(getMemDC(), _rcSave.left, _rcSave.top);
	Rectangle(getMemDC(), _rcLoad);
	IMAGEMANAGER->findImage("�ε�")->render(getMemDC(), _rcLoad.left, _rcLoad.top);
	Rectangle(getMemDC(), _rcTerrain);
	IMAGEMANAGER->findImage("����")->render(getMemDC(), _rcTerrain.left, _rcTerrain.top);
	Rectangle(getMemDC(), _rcObject);
	IMAGEMANAGER->findImage("������Ʈ")->render(getMemDC(), _rcObject.left, _rcObject.top);
	Rectangle(getMemDC(), _rcEraser);
	IMAGEMANAGER->findImage("���찳")->render(getMemDC(), _rcEraser.left, _rcEraser.top);

	if (isSelectSeason)
	{
		Rectangle(getMemDC(), _rcSpring);
		Rectangle(getMemDC(), _rcSummer);
		Rectangle(getMemDC(), _rcAutumn);
		Rectangle(getMemDC(), _rcWinter);

		textOut(getMemDC(), _rcSpring.left + 10, _rcSpring.top + 5, "��");
		textOut(getMemDC(), _rcSummer.left + 10, _rcSummer.top + 5, "����");
		textOut(getMemDC(), _rcAutumn.left + 10, _rcAutumn.top + 5, "����");
		textOut(getMemDC(), _rcWinter.left + 10, _rcWinter.top + 5, "�ܿ�");
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
	switch (_currentSeason)
	{
	case SPRING:
		for (int i = 0; i < SAMPLEDISPLAYY; i++)
		{
			for (int j = 0; j < SAMPLEDISPLAYX; j++)
			{
				if (j < sampleTileMaxFrameX && i < sampleTileMaxFrameY)
				{
					IMAGEMANAGER->frameRender("����(��)", getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
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
					IMAGEMANAGER->frameRender("����(����)", getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
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
					IMAGEMANAGER->frameRender("����(����)", getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
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
					IMAGEMANAGER->frameRender("����(�ܿ�)", getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
						_sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameX, _sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameY);
				}
			}
		}
		break;
	}
}

void maptoolScene::showSampleObjectTile()
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
					IMAGEMANAGER->frameRender("���������Ʈ(��)", getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
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
					IMAGEMANAGER->frameRender("���������Ʈ(����)", getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
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
					IMAGEMANAGER->frameRender("���������Ʈ(����)", getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
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
					IMAGEMANAGER->frameRender("���������Ʈ(�ܿ�)", getMemDC(), _sampleTile[i][j].rc.left, _sampleTile[i][j].rc.top,
						_sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameX, _sampleTile[i + sampleTileY][j + sampleTileX].terrainFrameY);
				}
			}
		}
		break;
	}
}

TERRAIN maptoolScene::terrainSelect(int frameX, int frameY)
{
	//�ø�Ʈ
	if (frameX == 1 && frameY == 0)
	{
		return TR_GROUND;
	}
	//��
	if (frameX == 2 && frameY == 0)
	{
		return TR_GROUND;
	}
	//��
	if ((frameX == 7 || frameX == 8 || frameX == 9 || frameX == 10) && frameY == 6)
	{
		return TR_WATER;
	}
	//������
	if (frameX == 20 && frameY == 12)
	{
		return TR_HACKED;
	}
	//��Ÿ
	return TR_GROUND;
}

OBJECT maptoolScene::objectSelect(int frameX, int frameY)
{
	return OBJ_INDESTRUCTIBLE;
}
