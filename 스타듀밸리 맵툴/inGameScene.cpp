#include "stdafx.h"
#include "inGameScene.h"

TCHAR inGameScene::saveName[MAX_PATH];

HRESULT inGameScene::init()
{
	CAMERAMANAGER->init(TILEX * TILESIZE, TILEY * TILESIZE, 30*16, 15*16);
	load();
	setTileRect();

	changeSeason(SPRING);

	isShowRect = false;


	return S_OK;
}

void inGameScene::release()
{
	//SAFE_DELETE(_playerInventory);
}

void inGameScene::update()
{
	PLAYER->update();

	playerMove();

	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());
	playerInteraction();

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
	if (INPUT->GetKeyDown(VK_F2))
	{
		setRandomObstacles();
	}
	if (INPUT->GetKeyDown(VK_F3))
	{
		changeSeason(SPRING);
	}
	if (INPUT->GetKeyDown(VK_F4))
	{
		changeSeason(SUMMER);
	}
	if (INPUT->GetKeyDown(VK_F5))
	{
		changeSeason(AUTUMN);
	}
	if (INPUT->GetKeyDown(VK_F6))
	{
		changeSeason(WINTER);
	}
}

void inGameScene::render()
{
	renderMap();
	if (isShowRect)
	{
		Rectangle(CAMERAMANAGER->getMemDC(), _tile[currentIndexY][currentIndexX].rc);
		Rectangle(CAMERAMANAGER->getMemDC(), _tile[MouseIndexY][MouseIndexX].rc);
	}

	PLAYER->render();

	CAMERAMANAGER->render(getMemDC());
	
	PLAYER->InventroyRender(getMemDC());
	

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
}

void inGameScene::renderMap()
{
	for (int i = (float)((float)CAMERAMANAGER->getY() / 16) - 1; i < (float)((float)CAMERAMANAGER->getY() / 16) + (float)(WINSIZEY / 40) + 1; i++)
	{
		for (int j = (float)((float)CAMERAMANAGER->getX() / 16) - 1; j < (float)((float)CAMERAMANAGER->getX() / 16) + (float)(WINSIZEX / 40) + 1; j++)
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

				//인게임 화면 오브젝트 그린다
				if (_tile[i][j].obj != OBJ_NONE)
				{
					if (_tile[i][j].objType == OTY_STONE || _tile[i][j].objType == OTY_LARGESTONE
						|| _tile[i][j].objType == OTY_BRANCH || _tile[i][j].objType == OTY_HARDTREE)
					{
						IMAGEMANAGER->frameRender("농장장애물", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
							_tile[i][j].objFrameX, _tile[i][j].objFrameY);
					}
					else if (_tile[i][j].objType == OTY_CROP)
					{
						IMAGEMANAGER->frameRender("작물", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
							_tile[i][j].objFrameX, _tile[i][j].objFrameY);
					}
					else
					{
						IMAGEMANAGER->frameRender(objectImageName, CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
							_tile[i][j].objFrameX, _tile[i][j].objFrameY);
					}
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
	checkPlayerTile();
	if (INPUT->GetKey('D'))
	{
		rightIndexX = (float)((float)PLAYER->getCenterX() + 8) / 16;
		rightIndexY = (float)((float)PLAYER->getCenterY() + 8) / 16;
		if (rightIndexX < TILEX && rightIndexY >= 0 && rightIndexY < TILEY)
		{
			if (_tile[rightIndexY][rightIndexX].obj == OBJ_NONE || _tile[rightIndexY][rightIndexX].obj == OBJ_SEED)
			{
				PLAYER->setCenterX(PLAYER->getCenterX() + PLAYER->getSpeed());
				PLAYER->setDirection(RIGHT);
			}
		}
	}
	if (INPUT->GetKey('A'))
	{
		leftIndexX = (float)((float)PLAYER->getCenterX() - 8) / 16;
		leftIndexY = (float)((float)PLAYER->getCenterY() + 8) / 16;
		if (leftIndexX >= 0 && leftIndexY >= 0 && leftIndexY < TILEY)
		{
			if (_tile[leftIndexY][leftIndexX].obj == OBJ_NONE || _tile[leftIndexY][leftIndexX].obj == OBJ_SEED)
			{
				PLAYER->setCenterX(PLAYER->getCenterX() - PLAYER->getSpeed());
				PLAYER->setDirection(LEFT);
			}
		}
	}
	if (INPUT->GetKey('W'))
	{
		upIndexX = (float)((float)PLAYER->getCenterX()) / 16;
		upIndexY = (float)((float)PLAYER->getCenterY()) / 16;
		if (upIndexX >= 0 && upIndexX < TILEX && upIndexY >= 0)
		{
			if (_tile[upIndexY][upIndexX].obj == OBJ_NONE || _tile[upIndexY][upIndexX].obj == OBJ_SEED)
			{
				PLAYER->setCenterY(PLAYER->getCenterY() - PLAYER->getSpeed());
				PLAYER->setDirection(UP);
			}
		}
	}
	if (INPUT->GetKey('S'))
	{
		downIndexX = (float)((float)PLAYER->getCenterX()) / 16;
		downIndexY = (float)((float)PLAYER->getCenterY() + 16) / 16;
		if (downIndexX >= 0 && downIndexX < TILEX && downIndexY < TILEY)
		{
			if (_tile[downIndexY][downIndexX].obj == OBJ_NONE || _tile[downIndexY][downIndexX].obj == OBJ_SEED)
			{
				PLAYER->setCenterY(PLAYER->getCenterY() + PLAYER->getSpeed());
				PLAYER->setDirection(DOWN);
			}
		}
	}
	if (!INPUT->GetKey(VK_RIGHT) && !INPUT->GetKey(VK_LEFT) && !INPUT->GetKey(VK_UP) && !INPUT->GetKey(VK_DOWN))
	{
		PLAYER->setIndex(0);
		PLAYER->setDirection(IDLE);
	}
}
 
void inGameScene::checkPlayerTile()
{
	currentIndexX = PLAYER->getCurrentX();
	currentIndexY = PLAYER->getCurrentY();
}

void inGameScene::playerInteraction()
{
	MouseIndexX = (float)((float)CAMERAMANAGER->getX() / 16) + (float)((float)_ptMouse.x / 40);
	MouseIndexY = (float)((float)CAMERAMANAGER->getY() / 16) + (float)((float)_ptMouse.y / 40);

	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //상하좌우 4타일일때
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1) //대각선 4 타일일때
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1)))
		{
			//if (PLAYER->getCurrentInven()->item_kind == ITEM_TOOL)
			//{
			//	if (_tile[MouseIndexY][MouseIndexX].obj == OBJ_NONE)
			//	{
					_tile[MouseIndexY][MouseIndexX].terrain = TR_HACKED;
			//	}
			//}
			if (PLAYER->getCurrentInven()->item_kind == ITEM_SEED || _tile[MouseIndexY][MouseIndexX].terrain == TR_HACKED)
			{
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_SEED;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_CROP;
				_tile[MouseIndexY][MouseIndexX].grownLevel = 0;

				switch (PLAYER->getCurrentInven()->seedKind)
				{
				case SEED_PASNIP:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 1;
					break;
				case SEED_CABBAGE:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 3;
					break;
				case SEED_ONION:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 5;
					break;
				case SEED_CARROT:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 7;
					break;
				case SEED_TOMATO:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 9;
					break;
				case SEED_CHILLI:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 11;
					break;
				case SEED_RADISH:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 13;
					break;
				case SEED_STARFRUIT:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 15;
					break;
				case SEED_EGGPLANT:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 17;
					break;
				case SEED_PUMPKIN:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 19;
					break;
				case SEED_TARO:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 21;
					break;
				case SEED_BEET:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 23;
					break;
				case SEED_TULIP:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 25;
					break;
				case SEED_MIN:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 27;
					break;
				case SEED_SUNFLOWER:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 29;
					break;
				case SEED_PEPPER:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 31;
					break;
				case SEED_STRAWBERRY:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 37;
					break;
				case SEED_GRAPE:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 39;
					break;
				case SEED_COFFEEBEAN:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 41;
					break;
				case SEED_BEAN:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 1;
					break;
				case SEED_POTATO:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 3;
					break;
				case SEED_GREEN1:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 5;
					break;
				case SEED_MELON:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 7;
					break;
				case SEED_BLUEBERRY:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 9;
					break;
				case SEED_WHEAT:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 11;
					break;
				case SEED_REDCABBAGE:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 13;
					break;
				case SEED_CORN:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 15;
					break;
				case SEED_SPINICH:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 17;
					break;
				case SEED_CHUNG:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 19;
					break;
				case SEED_RASBERRY:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 21;
					break;
				case SEED_BLUEFLOWER:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 27;
					break;
				case SEED_YELLOWFLOWER:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 29;
					break;
				case SEED_PINKFLOWER:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 31;
					break;
				case SEED_GREENGRAPE:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 37;
					break;
				case SEED_PURPLEWHEAT:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 39;
					break;
				case SEED_CATUS:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 41;
					break;
				}
			}
		}
	}
	if (INPUT->GetKeyDown(VK_RBUTTON))
	{
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //상하좌우 4타일일때
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1)
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1))) //대각선 4 타일일때
		{
			if (_tile[MouseIndexY][MouseIndexX].obj == OBJ_NONE || _tile[MouseIndexY][MouseIndexX].obj == OBJ_SEED)
			{
				if (_tile[MouseIndexY][MouseIndexX].terrain == TR_HACKED)
				{
					_tile[MouseIndexY][MouseIndexX].isWet = true;
				}
			}
			
		}
	}
	checkHacked();
}

void inGameScene::checkHacked()
{
	for (int i = currentIndexY - 10; i < currentIndexY + 10; i++)
	{
		for (int j = currentIndexX - 20; j < currentIndexX + 20; j++)
		{
			if (i - 1 >= 0 && i + 1 <= TILEY - 1 && j - 1 >= 0 && j + 1 <= TILEX - 1)
			{
				if (_tile[i][j].terrain == TR_HACKED)
				{
					_tile[i][j].terrainFrameX = 20;
					_tile[i][j].terrainFrameY = 12;
					if (_tile[i][j - 1].terrain == TR_HACKED) //왼쪽
					{
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 13;
					}
					if (_tile[i][j + 1].terrain == TR_HACKED) //오른쪽
					{
						_tile[i][j].terrainFrameX = 20;
						_tile[i][j].terrainFrameY = 13;
					}
					if (_tile[i - 1][j].terrain == TR_HACKED) //위
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 13;
					}
					if (_tile[i + 1][j].terrain == TR_HACKED) //아래
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 12;
					}
					if (_tile[i][j - 1].terrain == TR_HACKED && _tile[i][j + 1].terrain == TR_HACKED)			//왼+오
					{
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 20;
					}
					if (_tile[i - 1][j].terrain == TR_HACKED && _tile[i + 1][j].terrain == TR_HACKED)			//위+아래
					{
						_tile[i][j].terrainFrameX = 20;
						_tile[i][j].terrainFrameY = 20;
					}
					if ((_tile[i - 1][j].terrain == TR_HACKED && _tile[i][j - 1].terrain == TR_HACKED)
						|| (_tile[i - 1][j].terrain == TR_HACKED
							&& _tile[i][j - 1].terrain == TR_HACKED
							&& _tile[i - 1][j - 1].terrain == TR_HACKED))	//위+왼 ||  //위+왼+왼대각
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 21;
					}
					if ((_tile[i - 1][j].terrain == TR_HACKED && _tile[i][j + 1].terrain == TR_HACKED)
						|| (_tile[i - 1][j].terrain == TR_HACKED
							&& _tile[i][j + 1].terrain == TR_HACKED
							&& _tile[i + 1][j + 1].terrain == TR_HACKED))	 //위+오 || 위+오+오대각
					{
						_tile[i][j].terrainFrameX = 20;
						_tile[i][j].terrainFrameY = 21;
					}
					if ((_tile[i + 1][j].terrain == TR_HACKED && _tile[i][j - 1].terrain == TR_HACKED)
						|| (_tile[i + 1][j].terrain == TR_HACKED
							&& _tile[i][j - 1].terrain == TR_HACKED
							&& _tile[i + 1][j - 1].terrain == TR_HACKED))	//아래+왼 || 아래+왼+왼대각
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 16;
					}
					if ((_tile[i + 1][j].terrain == TR_HACKED && _tile[i][j + 1].terrain == TR_HACKED)
						|| (_tile[i + 1][j].terrain == TR_HACKED
							&& _tile[i][j + 1].terrain == TR_HACKED
							&& _tile[i + 1][j + 1].terrain == TR_HACKED))	//아래+오 || 아래+오+오대각
					{
						_tile[i][j].terrainFrameX = 20;
						_tile[i][j].terrainFrameY = 16;
					}
					if (_tile[i - 1][j].terrain == TR_HACKED
						&& _tile[i][j - 1].terrain == TR_HACKED
						&& _tile[i + 1][j].terrain == TR_HACKED)		//위+왼+아래
					{
						_tile[i][j].terrainFrameX = 22;
						_tile[i][j].terrainFrameY = 17;
					}
					if (_tile[i - 1][j].terrain == TR_HACKED
						&& _tile[i][j + 1].terrain == TR_HACKED
						&& _tile[i + 1][j].terrain == TR_HACKED)		//위+오+아래
					{
						_tile[i][j].terrainFrameX = 20;
						_tile[i][j].terrainFrameY = 17;
					}
					if (_tile[i - 1][j].terrain == TR_HACKED
						&& _tile[i][j - 1].terrain == TR_HACKED
						&& _tile[i][j + 1].terrain == TR_HACKED)		//위+왼+오
					{
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 21;
					}
					if (_tile[i + 1][j].terrain == TR_HACKED
						&& _tile[i][j - 1].terrain == TR_HACKED
						&& _tile[i][j + 1].terrain == TR_HACKED)		//아래+왼+오 
					{
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 16;
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
						_tile[i][j].terrainFrameX = 21;
						_tile[i][j].terrainFrameY = 17;
					}
				}
				if (_tile[i][j].isWet)
				{
					_tile[i][j].wetFrameX = 20;
					_tile[i][j].wetFrameY = 14;
					if (_tile[i][j - 1].isWet) //왼쪽
					{
						_tile[i][j].wetFrameX = 21;
						_tile[i][j].wetFrameY = 15;
					}
					if (_tile[i][j + 1].isWet) //오른쪽
					{
						_tile[i][j].wetFrameX = 20;
						_tile[i][j].wetFrameY = 15;
					}
					if (_tile[i - 1][j].isWet) //위
					{
						_tile[i][j].wetFrameX = 22;
						_tile[i][j].wetFrameY = 15;
					}
					if (_tile[i + 1][j].isWet) //아래
					{
						_tile[i][j].wetFrameX = 22;
						_tile[i][j].wetFrameY = 14;
					}
					if (_tile[i][j - 1].isWet && _tile[i][j + 1].isWet)			//왼+오
					{
						_tile[i][j].wetFrameX = 21;
						_tile[i][j].wetFrameY = 22;
					}
					if (_tile[i - 1][j].isWet && _tile[i + 1][j].isWet)			//위+아래
					{
						_tile[i][j].wetFrameX = 20;
						_tile[i][j].wetFrameY = 22;
					}
					if ((_tile[i - 1][j].isWet && _tile[i][j - 1].isWet)
						|| (_tile[i - 1][j].isWet
							&& _tile[i][j - 1].isWet
							&& _tile[i - 1][j - 1].isWet))	//위+왼 ||  //위+왼+왼대각
					{
						_tile[i][j].wetFrameX = 22;
						_tile[i][j].wetFrameY = 23;
					}
					if ((_tile[i - 1][j].isWet && _tile[i][j + 1].isWet)
						|| (_tile[i - 1][j].isWet
							&& _tile[i][j + 1].isWet
							&& _tile[i + 1][j + 1].isWet))	 //위+오 || 위+오+오대각
					{
						_tile[i][j].wetFrameX = 20;
						_tile[i][j].wetFrameY = 23;
					}
					if ((_tile[i + 1][j].isWet && _tile[i][j - 1].isWet)
						|| (_tile[i + 1][j].isWet
							&& _tile[i][j - 1].isWet
							&& _tile[i + 1][j - 1].isWet))	//아래+왼 || 아래+왼+왼대각
					{
						_tile[i][j].wetFrameX = 22;
						_tile[i][j].wetFrameY = 18;
					}
					if ((_tile[i + 1][j].isWet && _tile[i][j + 1].isWet)
						|| (_tile[i + 1][j].isWet
							&& _tile[i][j + 1].isWet
							&& _tile[i + 1][j + 1].isWet))	//아래+오 || 아래+오+오대각
					{
						_tile[i][j].wetFrameX = 20;
						_tile[i][j].wetFrameY = 18;
					}
					if (_tile[i - 1][j].isWet
						&& _tile[i][j - 1].isWet
						&& _tile[i + 1][j].isWet)		//위+왼+아래
					{
						_tile[i][j].wetFrameX = 22;
						_tile[i][j].wetFrameY = 19;
					}
					if (_tile[i - 1][j].isWet
						&& _tile[i][j + 1].isWet
						&& _tile[i + 1][j].isWet)		//위+오+아래
					{
						_tile[i][j].wetFrameX = 20;
						_tile[i][j].wetFrameY = 19;
					}
					if (_tile[i - 1][j].isWet
						&& _tile[i][j - 1].isWet
						&& _tile[i][j + 1].isWet)		//위+왼+오
					{
						_tile[i][j].wetFrameX = 21;
						_tile[i][j].wetFrameY = 23;
					}
					if (_tile[i + 1][j].isWet
						&& _tile[i][j - 1].isWet
						&& _tile[i][j + 1].isWet)		//아래+왼+오 
					{
						_tile[i][j].wetFrameX = 21;
						_tile[i][j].wetFrameY = 18;
					}
					if ((_tile[i - 1][j].isWet
						&& _tile[i + 1][j].isWet
						&& _tile[i][j - 1].isWet
						&& _tile[i][j + 1].isWet)		//위아래왼오 (4방)
						|| (_tile[i - 1][j].isWet
							&& _tile[i + 1][j].isWet
							&& _tile[i][j - 1].isWet
							&& _tile[i][j + 1].isWet
							&& _tile[i - 1][j - 1].isWet
							&& _tile[i + 1][j - 1].isWet
							&& _tile[i - 1][j + 1].isWet
							&& _tile[i + 1][j + 1].isWet))	//위아래양옆대각4개 모두	(8방)
					{
						//기본 네모
						_tile[i][j].wetFrameX = 21;
						_tile[i][j].wetFrameY = 19;
					}
				}
			}
		}
	}
}

void inGameScene::setRandomObstacles()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			if (_tile[i][j].obj != OBJ_NONE || _tile[i][j].terrain == TR_HACKED) { continue; }
			if (RANDOM->range(20) == 0)
			{
				switch (RANDOM->range(4))
				{
				case 0:
					_tile[i][j].obj = OBJ_DESTRUCTIBLE;
					_tile[i][j].objType = OTY_STONE;
					switch (RANDOM->range(4))
					{
					case 0:
						_tile[i][j].objFrameX = 2;
						_tile[i][j].objFrameY = 0;
						break;
					case 1:
						_tile[i][j].objFrameX = 3;
						_tile[i][j].objFrameY = 0;
						break;
					case 2:
						_tile[i][j].objFrameX = 4;
						_tile[i][j].objFrameY = 0;
						break;
					case 3:
						_tile[i][j].objFrameX = 5;
						_tile[i][j].objFrameY = 0;
						break;
					}
					break;
				case 1:
					if (i + 1 < TILEY && j + 1 < TILEX)
					{
						if (_tile[i + 1][j].obj == OBJ_NONE && _tile[i][j + 1].obj == OBJ_NONE && _tile[i + 1][j + 1].obj == OBJ_NONE
							&& _tile[i + 1][j].terrain != TR_HACKED && _tile[i][j + 1].terrain != TR_HACKED && _tile[i + 1][j + 1].terrain != TR_HACKED)
						{
							_tile[i][j].objType = OTY_LARGESTONE;
							_tile[i][j].obj = OBJ_DESTRUCTIBLE;
							_tile[i][j].objFrameX = 2;
							_tile[i][j].objFrameY = 1;

							_tile[i + 1][j].objType = OTY_LARGESTONE;
							_tile[i + 1][j].obj = OBJ_DESTRUCTIBLE;
							_tile[i + 1][j].objFrameX = 2;
							_tile[i + 1][j].objFrameY = 2;

							_tile[i][j + 1].objType = OTY_LARGESTONE;
							_tile[i][j + 1].obj = OBJ_DESTRUCTIBLE;
							_tile[i][j + 1].objFrameX = 3;
							_tile[i][j + 1].objFrameY = 1;

							_tile[i + 1][j + 1].objType = OTY_LARGESTONE;
							_tile[i + 1][j + 1].obj = OBJ_DESTRUCTIBLE;
							_tile[i + 1][j + 1].objFrameX = 3;
							_tile[i + 1][j + 1].objFrameY = 2;
						}
					}
					break;
				case 2:
					_tile[i][j].obj = OBJ_DESTRUCTIBLE;
					_tile[i][j].objType = OTY_BRANCH;
					switch (RANDOM->range(2))
					{
					case 0:
						_tile[i][j].objFrameX = 0;
						_tile[i][j].objFrameY = 0;
						break;
					case 1:
						_tile[i][j].objFrameX = 1;
						_tile[i][j].objFrameY = 0;
						break;
					}
					break;
				case 3:
					if (i + 1 < TILEY && j + 1 < TILEX)
					{
						if (_tile[i + 1][j].obj == OBJ_NONE && _tile[i][j + 1].obj == OBJ_NONE && _tile[i + 1][j + 1].obj == OBJ_NONE
							&& _tile[i + 1][j].terrain != TR_HACKED && _tile[i][j + 1].terrain != TR_HACKED && _tile[i + 1][j + 1].terrain != TR_HACKED)
						{
							_tile[i][j].objType = OTY_HARDTREE;
							_tile[i][j].obj = OBJ_DESTRUCTIBLE;
							_tile[i][j].objFrameX = 0;
							_tile[i][j].objFrameY = 1;

							_tile[i + 1][j].objType = OTY_HARDTREE;
							_tile[i + 1][j].obj = OBJ_DESTRUCTIBLE;
							_tile[i + 1][j].objFrameX = 0;
							_tile[i + 1][j].objFrameY = 2;

							_tile[i][j + 1].objType = OTY_HARDTREE;
							_tile[i][j + 1].obj = OBJ_DESTRUCTIBLE;
							_tile[i][j + 1].objFrameX = 1;
							_tile[i][j + 1].objFrameY = 1;

							_tile[i + 1][j + 1].objType = OTY_HARDTREE;
							_tile[i + 1][j + 1].obj = OBJ_DESTRUCTIBLE;
							_tile[i + 1][j + 1].objFrameX = 1;
							_tile[i + 1][j + 1].objFrameY = 2;
						}
					}
					break;
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
