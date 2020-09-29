#include "stdafx.h"
#include "inGameScene.h"

TCHAR inGameScene::saveName[MAX_PATH];

HRESULT inGameScene::init()
{
	CAMERAMANAGER->init(WINSIZEX, WINSIZEY, 20*16, 11*16);
	load();
	setTileRect();
	
	playerCenterX = WINSIZEX / 2;
	playerCenterY = WINSIZEY / 2;
	playerRc = RectMakeCenter(playerCenterX, playerCenterY, 16, 32);
	_currentSeason = SPRING;
	return S_OK;
}

void inGameScene::release()
{
}

void inGameScene::update()
{
	playerMove();
	//CAMERAMANAGER->cameraMove(playerCenterX, playerCenterY);
}

void inGameScene::render()
{
	showEntireMap();
	Rectangle(getMemDC(), playerRc);
	
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

void inGameScene::showEntireMap()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			string imageName;
			string objectImageName;
			switch (_currentSeason)
			{
			case SPRING:
				imageName = "농장(봄)";
				objectImageName = "농장오브젝트(봄)";
				break;
			case SUMMER:
				imageName = "농장(여름)";
				objectImageName = "농장오브젝트(여름)";
				break;
			case AUTUMN:
				imageName = "농장(가을)";
				objectImageName = "농장오브젝트(가을)";
				break;
			case WINTER:
				imageName = "농장(겨울)";
				objectImageName = "농장오브젝트(겨울)";
				break;
			}

			IMAGEMANAGER->frameRender(imageName, getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
				_tile[i][j].terrainFrameX, _tile[i][j].terrainFrameY);

			if (_tile[i][j].isWet)
			{
				IMAGEMANAGER->frameRender(imageName, getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i][j].wetFrameX, _tile[i][j].wetFrameY);
			}

			//인게임 화면 오브젝트 그린다
			if (_tile[i][j].obj != OBJ_NONE)
			{
				IMAGEMANAGER->frameRender(objectImageName, getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i][j].objFrameX, _tile[i][j].objFrameY);
			}
			if (_tile[i][j].objOver != OVR_NONE)
			{
				IMAGEMANAGER->frameRender(objectImageName, getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i][j].ovlFrameX, _tile[i][j].ovlFrameY);
			}
		}
	}
}

void inGameScene::playerMove()
{
	if (INPUT->GetKey(VK_LEFT))
	{
		playerCenterX -= 5.0f;
	}
	if (INPUT->GetKey(VK_RIGHT))
	{
		playerCenterX += 5.0f;
	}
	if (INPUT->GetKey(VK_UP))
	{
		playerCenterY -= 5.0f;
	}
	if (INPUT->GetKey(VK_DOWN))
	{
		playerCenterY += 5.0f;
	}
	playerRc = RectMakeCenter(playerCenterX, playerCenterY, 16, 32);
}


INT_PTR inGameScene::DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SetWindowText(hWnd, "로드");
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
