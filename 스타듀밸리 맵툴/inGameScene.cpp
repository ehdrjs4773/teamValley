#include "stdafx.h"
#include "inGameScene.h"

TCHAR inGameScene::saveName[MAX_PATH];

HRESULT inGameScene::init()
{
	CAMERAMANAGER->init(TILEX * TILESIZE, TILEY * TILESIZE, 30*16, 15*16);
	load();
	setTileRect();
	
	playerCenterX = WINSIZEX / 2;
	playerCenterY = WINSIZEY / 2;
	playerRc = RectMakeCenter(playerCenterX, playerCenterY, 16, 32);

	checkPlayerTile();
	changeSeason(SPRING);

	isShowRect = false;

	return S_OK;
}

void inGameScene::release()
{
}

void inGameScene::update()
{
	playerMove();
	CAMERAMANAGER->cameraMove(playerCenterX, playerCenterY);
	hackGround();

	if (INPUT->GetKeyDown(VK_F1))
	{
		if (isShowRect)
		{
			isShowRect = false;
		}
		else
		{
			isShowRect = true;
		}
	}
}

void inGameScene::render()
{
	showEntireMap();
	Rectangle(CAMERAMANAGER->getMemDC(), playerRc);
	
	if (isShowRect)
	{
		for (int i = _currentY - 8; i < _currentY + 8; i++)
		{
			for (int j = _currentX - 16; j < _currentX + 16; j++)
			{
				if (i >= 0 && i < TILEY && j >= 0 && j < TILEX)
				{
					Rectangle(CAMERAMANAGER->getMemDC(), _tile[i][j].rc);
				}
			}
		}
	}

	CAMERAMANAGER->render(getMemDC());
}

void inGameScene::load()
{
	DialogBox(_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), _hWnd, inGameScene::DlgProc);

	HANDLE file;
	DWORD read;

	file = CreateFile(saveName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tile, sizeof(_tile), &read, NULL);
	CloseHandle(file);
}

void inGameScene::setTileRect()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tile[i][j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
		}
	}
}

void inGameScene::changeSeason(SEASON season)
{
	_currentSeason = season;
	switch (_currentSeason)
	{
	case SPRING:
		imageName = "����(��)";
		objectImageName = "���������Ʈ(��)";
		break;
	case SUMMER:
		imageName = "����(����)";
		objectImageName = "���������Ʈ(����)";
		break;
	case AUTUMN:
		imageName = "����(����)";
		objectImageName = "���������Ʈ(����)";
		break;
	case WINTER:
		imageName = "����(�ܿ�)";
		objectImageName = "���������Ʈ(�ܿ�)";
		break;
	}
}

void inGameScene::showEntireMap()
{
	for (int i = _currentY - 8; i < _currentY + 8; i++)
	{
		for (int j = _currentX - 16; j < _currentX + 16; j++)
		{
			if (i >= 0 && i < TILEY && j >= 0 && j < TILEX)
			{
				IMAGEMANAGER->frameRender(imageName, CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i][j].terrainFrameX, _tile[i][j].terrainFrameY);

				if (_tile[i][j].isWet)
				{
					IMAGEMANAGER->frameRender(imageName, CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
						_tile[i][j].wetFrameX, _tile[i][j].wetFrameY);
				}
				//�ΰ��� ȭ�� ������Ʈ �׸���
				if (_tile[i][j].obj != OBJ_NONE)
				{
					IMAGEMANAGER->frameRender(objectImageName, CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
						_tile[i][j].objFrameX, _tile[i][j].objFrameY);
				}
				if (_tile[i][j].objOver != OVR_NONE)
				{
					IMAGEMANAGER->frameRender(objectImageName, CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
						_tile[i][j].ovlFrameX, _tile[i][j].ovlFrameY);
				}
			}
		}
	}
}

void inGameScene::playerMove()
{
	if (INPUT->GetKey(VK_LEFT))
	{
		playerCenterX -= 2.0f;
	}
	if (INPUT->GetKey(VK_RIGHT))
	{
		playerCenterX += 2.0f;
	}
	if (INPUT->GetKey(VK_UP))
	{
		playerCenterY -= 2.0f;
	}
	if (INPUT->GetKey(VK_DOWN))
	{
		playerCenterY += 2.0f;
	}
	playerRc = RectMakeCenter(playerCenterX, playerCenterY, 16, 32);
	checkPlayerTile();
}

void inGameScene::checkPlayerTile()
{
	_currentX = playerCenterX / 16;
	_currentY = playerCenterY / 16;
}

void inGameScene::hackGround()
{
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		int MouseIndexX, MouseIndexY;
		MouseIndexX = _ptMouse.x / 16;
		MouseIndexY = _ptMouse.y / 16;
		_tile[MouseIndexY][MouseIndexX].terrain = TR_HACKED;
		checkHacked();
	}
}

void inGameScene::checkHacked()
{
	for (int i = _currentY - 8; i < _currentY + 8; i++)
	{
		for (int j = _currentX - 16; j < _currentX + 16; j++)
		{
			if (i - 1 >= 0 && i + 1 <= TILEY - 1 && j - 1 >= 0 && j + 1 <= TILEX - 1)
			{
				if (_tile[i][j].terrain == TR_HACKED)
				{
					_tile[i][j].terrainFrameX = 20;
					_tile[i][j].terrainFrameY = 12;
					if (_tile[i][j - 1].terrain == TR_HACKED) //����
					{
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 13;
					}
					if (_tile[i][j + 1].terrain == TR_HACKED) //������
					{
						_tile[i][j].terrainFrameX = 20;
						_tile[i][j].terrainFrameY = 13;
					}
					if (_tile[i - 1][j].terrain == TR_HACKED) //��
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 13;
					}
					if (_tile[i + 1][j].terrain == TR_HACKED) //�Ʒ�
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 12;
					}
					if (_tile[i][j - 1].terrain == TR_HACKED && _tile[i][j + 1].terrain == TR_HACKED)			//��+��
					{
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 20;
					}
					if (_tile[i - 1][j].terrain == TR_HACKED && _tile[i + 1][j].terrain == TR_HACKED)			//��+�Ʒ�
					{
						_tile[i][j].terrainFrameX = 20;
						_tile[i][j].terrainFrameY = 20;
					}
					if ((_tile[i - 1][j].terrain == TR_HACKED && _tile[i][j - 1].terrain == TR_HACKED)
						|| (_tile[i - 1][j].terrain == TR_HACKED
							&& _tile[i][j - 1].terrain == TR_HACKED
							&& _tile[i - 1][j - 1].terrain == TR_HACKED))	//��+�� ||  //��+��+�޴밢
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 21;
					}
					if ((_tile[i - 1][j].terrain == TR_HACKED && _tile[i][j + 1].terrain == TR_HACKED)
						|| (_tile[i - 1][j].terrain == TR_HACKED
							&& _tile[i][j + 1].terrain == TR_HACKED
							&& _tile[i + 1][j + 1].terrain == TR_HACKED))	 //��+�� || ��+��+���밢
					{
						_tile[i][j].terrainFrameX = 20;
						_tile[i][j].terrainFrameY = 21;
					}
					if ((_tile[i + 1][j].terrain == TR_HACKED && _tile[i][j - 1].terrain == TR_HACKED)
						|| (_tile[i + 1][j].terrain == TR_HACKED
							&& _tile[i][j - 1].terrain == TR_HACKED
							&& _tile[i + 1][j - 1].terrain == TR_HACKED))	//�Ʒ�+�� || �Ʒ�+��+�޴밢
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 16;
					}
					if ((_tile[i + 1][j].terrain == TR_HACKED && _tile[i][j + 1].terrain == TR_HACKED)
						|| (_tile[i + 1][j].terrain == TR_HACKED
							&& _tile[i][j + 1].terrain == TR_HACKED
							&& _tile[i + 1][j + 1].terrain == TR_HACKED))	//�Ʒ�+�� || �Ʒ�+��+���밢
					{
						_tile[i][j].terrainFrameX = 20;
						_tile[i][j].terrainFrameY = 16;
					}
					if (_tile[i - 1][j].terrain == TR_HACKED
						&& _tile[i][j - 1].terrain == TR_HACKED
						&& _tile[i + 1][j].terrain == TR_HACKED)		//��+��+�Ʒ�
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 17;
					}
					if (_tile[i - 1][j].terrain == TR_HACKED
						&& _tile[i][j + 1].terrain == TR_HACKED
						&& _tile[i + 1][j].terrain == TR_HACKED)		//��+��+�Ʒ�
					{
						_tile[i][j].terrainFrameX = 20;
						_tile[i][j].terrainFrameY = 17;
					}
					if (_tile[i - 1][j].terrain == TR_HACKED
						&& _tile[i][j - 1].terrain == TR_HACKED
						&& _tile[i][j + 1].terrain == TR_HACKED)		//��+��+��
					{
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 21;
					}
					if (_tile[i + 1][j].terrain == TR_HACKED
						&& _tile[i][j - 1].terrain == TR_HACKED
						&& _tile[i][j + 1].terrain == TR_HACKED)		//�Ʒ�+��+�� 
					{
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 16;
					}
					if ((_tile[i - 1][j].terrain == TR_HACKED
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
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 17;
					}
				}
			}
		}
	}
}


INT_PTR inGameScene::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SetWindowText(hWnd, "�ε�");
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
