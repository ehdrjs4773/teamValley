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
	if (PLAYER->getState() == STAND || PLAYER->getState() == RUN)
	{
		playerMove();
	}

	PLAYER->update();

	playerInteraction();

	//아이템 바닥에 떨어지게 하는거
	ejectItem();

	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());


	setCurrentSlotNumber(_mouseWheel);

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
		changeGrass();
	}
	if (INPUT->GetKeyDown(VK_F4))
	{
		changeSeason(SUMMER);
		changeGrass();
	}
	if (INPUT->GetKeyDown(VK_F5))
	{
		changeSeason(AUTUMN);
		changeGrass();
	}
	if (INPUT->GetKeyDown(VK_F6))
	{
		changeSeason(WINTER);
		changeGrass();
	}
	if (INPUT->GetKeyDown(VK_F7))
	{
		makeCropGrow();
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

	for (int i = 0; i < _vItemOnField.size(); i++)
	{
		_vItemOnField[i].item.item_image->frameRender(CAMERAMANAGER->getMemDC(), _vItemOnField[i].rc.left, _vItemOnField[i].rc.top, _vItemOnField[i].item.indexX, _vItemOnField[i].item.indexY);
	}

	CAMERAMANAGER->render(getMemDC());
	
	PLAYER->InventroyRender(getMemDC());
	PLAYER->hpBarRender(getMemDC());
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
						|| _tile[i][j].objType == OTY_BRANCH || _tile[i][j].objType == OTY_HARDTREE
						|| _tile[i][j].objType == OTY_GRASS || _tile[i][j].objType == OTY_WEED)
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
					if (_tile[i][j].objType == OTY_CROP)
					{
						IMAGEMANAGER->frameRender("작물", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
							_tile[i][j].ovlFrameX, _tile[i][j].ovlFrameY);
					}
					else if (_tile[i + 1][j].objType == OTY_GRASS && i + 1 < TILEY)
					{
						IMAGEMANAGER->frameRender("농장장애물", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
							_tile[i][j].ovlFrameX, _tile[i][j].ovlFrameY);
					}
					else
					{
						IMAGEMANAGER->frameRender(objectImageName, CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
							_tile[i][j].ovlFrameX, _tile[i][j].ovlFrameY);
					}
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
			if (_tile[rightIndexY][rightIndexX].obj == OBJ_NONE || _tile[rightIndexY][rightIndexX].objType == OTY_GRASS
				|| (_tile[rightIndexY][rightIndexX].obj == OBJ_SEED && 
					_tile[rightIndexY][rightIndexX].seedType != SEED_GREENBEAN 
					&& _tile[rightIndexY][rightIndexX].seedType != SEED_HOPS
					&& _tile[rightIndexY][rightIndexX].seedType != SEED_GRAPE))
			{
				PLAYER->setDirection(RIGHT);
				PLAYER->setState(RUN);
				PLAYER->setCenterX(PLAYER->getCenterX() + PLAYER->getSpeed());
			}
		}
	}
	if (INPUT->GetKey('A'))
	{
		leftIndexX = (float)((float)PLAYER->getCenterX() - 8) / 16;
		leftIndexY = (float)((float)PLAYER->getCenterY() + 8) / 16;
		if (leftIndexX >= 0 && leftIndexY >= 0 && leftIndexY < TILEY)
		{
			if (_tile[leftIndexY][leftIndexX].obj == OBJ_NONE || _tile[leftIndexY][leftIndexX].objType == OTY_GRASS
				|| (_tile[leftIndexY][leftIndexX].obj == OBJ_SEED &&
					_tile[leftIndexY][leftIndexX].seedType != SEED_GREENBEAN
					&& _tile[leftIndexY][leftIndexX].seedType != SEED_HOPS
					&& _tile[leftIndexY][leftIndexX].seedType != SEED_GRAPE))
			{
				
				PLAYER->setDirection(LEFT);
				PLAYER->setState(RUN);
				PLAYER->setCenterX(PLAYER->getCenterX() - PLAYER->getSpeed());
			}
		}
	}
	if (INPUT->GetKey('W'))
	{
		upIndexX = (float)((float)PLAYER->getCenterX()) / 16;
		upIndexY = (float)((float)PLAYER->getCenterY()) / 16;
		if (upIndexX >= 0 && upIndexX < TILEX && upIndexY >= 0)
		{
			if (_tile[upIndexY][upIndexX].obj == OBJ_NONE || _tile[upIndexY][upIndexX].objType == OTY_GRASS
				|| (_tile[upIndexY][upIndexX].obj == OBJ_SEED &&
					_tile[upIndexY][upIndexX].seedType != SEED_GREENBEAN
					&& _tile[upIndexY][upIndexX].seedType != SEED_HOPS
					&& _tile[upIndexY][upIndexX].seedType != SEED_GRAPE))
			{
				
				PLAYER->setDirection(UP);
				PLAYER->setState(RUN);
				PLAYER->setCenterY(PLAYER->getCenterY() - PLAYER->getSpeed());
			}
		}
	}
	if (INPUT->GetKey('S'))
	{
		downIndexX = (float)((float)PLAYER->getCenterX()) / 16;
		downIndexY = (float)((float)PLAYER->getCenterY() + 16) / 16;
		if (downIndexX >= 0 && downIndexX < TILEX && downIndexY < TILEY)
		{
			if (_tile[downIndexY][downIndexX].obj == OBJ_NONE || _tile[downIndexY][downIndexX].objType == OTY_GRASS
				|| (_tile[downIndexY][downIndexX].obj == OBJ_SEED &&
					_tile[downIndexY][downIndexX].seedType != SEED_GREENBEAN
					&& _tile[downIndexY][downIndexX].seedType != SEED_HOPS
					&& _tile[downIndexY][downIndexX].seedType != SEED_GRAPE))
			{
				
				PLAYER->setDirection(DOWN);
				PLAYER->setState(RUN);
				PLAYER->setCenterY(PLAYER->getCenterY() + PLAYER->getSpeed());
			}
		}
	}
	if (!INPUT->GetKey('S') && !INPUT->GetKey('A') && !INPUT->GetKey('D') && !INPUT->GetKey('W'))
	{
		if(PLAYER->getState() == RUN)
		{ 
			PLAYER->setIndex(0);
			PLAYER->setState(STAND);
		}
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
		if (MouseIndexY < currentIndexY)
		{
			PLAYER->setDirection(UP);
		}
		if (MouseIndexY > currentIndexY)
		{
			PLAYER->setDirection(DOWN);
		}
		if (MouseIndexX < currentIndexX)
		{
			PLAYER->setDirection(LEFT);
		}
		if (MouseIndexX > currentIndexX)
		{
			PLAYER->setDirection(RIGHT);
		}
		//밭 갈기
		hackGround();

		//나무베기
		cutdownTree();

		//돌, 광석 깨기
		breakStone();

		//풀 베기 
		cutGrass();

		//씨 심기
		plantSeed();

		//물뿌리기
		waterGround();

	}
	if (INPUT->GetKeyDown(VK_RBUTTON))
	{
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //상하좌우 4타일일때
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1)
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1))) //대각선 4 타일일때
		{
			//수확
			harvest();
		}
	}
	checkHacked();
}

void inGameScene::hackGround()
{
	if (PLAYER->getCurrentInven()->toolKind == TOOL_HOE)
	{
		PLAYER->setState(DIGGROUND);
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //상하좌우 4타일일때
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1) //대각선 4 타일일때
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1)))
		{
			_tile[MouseIndexY][MouseIndexX].terrain = TR_HACKED;
			_tile[MouseIndexY][MouseIndexX].terrainFrameX = 20;
			_tile[MouseIndexY][MouseIndexX].terrainFrameY = 12;
			//PLAYER->getHpBar().top; -= PLAYER->getHoeDamage();

		}
	}
}

void inGameScene::cutdownTree()
{
	if (PLAYER->getCurrentInven()->toolKind == TOOL_AX)
	{
		PLAYER->setState(CUTDOWNTREE);
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //상하좌우 4타일일때
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1) //대각선 4 타일일때
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1)))

		{
			if (_tile[MouseIndexY][MouseIndexX].objType == OTY_HARDTREE)
			{

			}
			if (_tile[MouseIndexY][MouseIndexX].objType == OTY_TREE)
			{

			}
			if (_tile[MouseIndexY][MouseIndexX].objType == OTY_BRANCH)
			{
				dropItem(_tile[MouseIndexY][MouseIndexX], "나무");
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_NONE;
			}
		}
	}
}

void inGameScene::breakStone()
{
	if (PLAYER->getCurrentInven()->toolKind == TOOL_PICKAX)
	{

		PLAYER->setState(BREAKSTONE);
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //상하좌우 4타일일때
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1)
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1))) //대각선 4 타일일때
		{
			if (_tile[MouseIndexY][MouseIndexX].objType == OTY_LARGESTONE)
			{

			}
			if (_tile[MouseIndexY][MouseIndexX].objType == OTY_STONE)
			{
				dropItem(_tile[MouseIndexY][MouseIndexX], "돌");
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_NONE;
			}
		}
	}
}

void inGameScene::cutGrass()
{

	if (PLAYER->getCurrentInven()->toolKind == TOOL_SICKLE || PLAYER->getCurrentInven()->toolKind == TOOL_SWORD)
	{
		PLAYER->setState(CUTGRASS);
		switch (PLAYER->getDirection())
		{
		case RIGHT:
			sickleHitBox = RectMakeCenter(PLAYER->getCenterX() + 8, PLAYER->getCenterY(), 32, 64);
			break;
		case LEFT:
			sickleHitBox = RectMakeCenter(PLAYER->getCenterX() - 8, PLAYER->getCenterY(), 32, 64);
			break;
		case UP:
			sickleHitBox = RectMakeCenter(PLAYER->getCenterX(), PLAYER->getCenterY() - 16, 64, 32);
			break;
		case DOWN:
			sickleHitBox = RectMakeCenter(PLAYER->getCenterX(), PLAYER->getCenterY() + 16, 64, 32);
			break;
		}
		for (int i = (float)((float)CAMERAMANAGER->getY() / 16); i < (float)((float)CAMERAMANAGER->getY() / 16) + (float)(WINSIZEY / 40); i++)
		{
			for (int j = (float)((float)CAMERAMANAGER->getX() / 16); j < (float)((float)CAMERAMANAGER->getX() / 16) + (float)(WINSIZEX / 40); j++)
			{
				RECT temp;
				if (IntersectRect(&temp, &sickleHitBox, &_tile[i][j].rc))
				{
					if (_tile[i][j].objType == OTY_GRASS || _tile[i][j].objType == OTY_WEED)
					{
						//dropFruit(_tile[MouseIndexY][MouseIndexX], _tile[MouseIndexY][MouseIndexX].seedType);
						_tile[i][j].obj = OBJ_NONE;
						_tile[i][j].objType = OTY_NONE;
						_tile[i][j].seedType = SEED_NONE;
						_tile[i][j].grownLevel = 0;
						_tile[i][j].isFullyGrown = false;

						_tile[i - 1][j].objOver = OVR_NONE;
					}
					if (_tile[i][j].objType == OTY_CROP &&
						(_tile[i][j].seedType == SEED_AMARANTH
							|| _tile[i][j].seedType == SEED_WHEAT
							|| _tile[i][j].seedType == SEED_KALE)
						&& _tile[i][j].isFullyGrown == true)
					{
						dropFruit(_tile[MouseIndexY][MouseIndexX], _tile[MouseIndexY][MouseIndexX].seedType);
						_tile[i][j].obj = OBJ_NONE;
						_tile[i][j].objType = OTY_NONE;
						_tile[i][j].seedType = SEED_NONE;
						_tile[i][j].grownLevel = 0;
						_tile[i][j].isFullyGrown = false;

						_tile[i - 1][j].objOver = OVR_NONE;
					}
				}
			}
		}
	}
}

void inGameScene::waterGround()
{

	if (PLAYER->getCurrentInven()->toolKind == TOOL_KETTLE && _tile[MouseIndexY][MouseIndexX].terrain == TR_HACKED)
	{
		PLAYER->setState(SPRAYWATER);
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //상하좌우 4타일일때
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1) //대각선 4 타일일때
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1)))
		{
			_tile[MouseIndexY][MouseIndexX].isWet = true;
		}
	}
}

void inGameScene::plantSeed()
{
	if (PLAYER->getCurrentInven()->item_kind == ITEM_SEED && _tile[MouseIndexY][MouseIndexX].terrain == TR_HACKED)
	{
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //상하좌우 4타일일때
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1) //대각선 4 타일일때
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1)))
		{
			_tile[MouseIndexY][MouseIndexX].obj = OBJ_SEED;
			_tile[MouseIndexY][MouseIndexX].objType = OTY_CROP;
			_tile[MouseIndexY][MouseIndexX].seedType = PLAYER->getCurrentInven()->seedKind;
			_tile[MouseIndexY][MouseIndexX].grownLevel = 0;
			_tile[MouseIndexY][MouseIndexX].isFullyGrown = false;

			_tile[MouseIndexY - 1][MouseIndexX].objOver = OVR_OVER;
			_tile[MouseIndexY - 1][MouseIndexX].objType = OTY_CROP;

			switch (PLAYER->getCurrentInven()->seedKind)
			{
			case SEED_NONE:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 0;
				break;
			case SEED_PARSNIP:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 1;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 0;
				break;
			case SEED_CAULIFLOWER:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 3;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 2;
				break;
			case SEED_GARLIC:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 5;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 4;
				break;
			case SEED_RHUBARB:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 7;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 6;
				break;
			case SEED_TOMATO:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 9;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 8;
				break;
			case SEED_HOTPEPPER:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 11;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 10;
				break;
			case SEED_RADISH:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 13;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 12;
				break;
			case SEED_STARFRUIT:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 15;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 14;
				break;
			case SEED_EGGPLANT:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 17;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 16;
				break;
			case SEED_PUMPKIN:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 19;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 18;
				break;
			case SEED_YAM:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 21;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 20;
				break;
			case SEED_BEET:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 23;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 22;
				break;
			case SEED_ANCIENTFRUIT:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 25;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 24;
				break;
			case SEED_TULIP:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 27;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 26;
				break;
			case SEED_POPPY:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 29;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 28;
				break;
			case SEED_SUNFLOWER:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 31;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 30;
				break;
			case SEED_SWEETGEMBERRY:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 33;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 32;
				break;
			case SEED_STRAWBERRY:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 37;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 36;
				break;
			case SEED_GRAPE:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 39;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 38;
				break;
			case SEED_COFFEEBEAN:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 41;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 40;
				break;
			case SEED_GREENBEAN:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 1;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 8;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 0;
				break;
			case SEED_POTATO:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 3;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 8;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 2;
				break;
			case SEED_KALE:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 5;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 8;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 4;
				break;
			case SEED_MELON:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 7;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 8;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 6;
				break;
			case SEED_BLUEBERRY:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 9;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 8;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 8;
				break;
			case SEED_WHEAT:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 11;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 8;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 10;
				break;
			case SEED_REDCABBAGE:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 13;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 8;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 12;
				break;
			case SEED_CORN:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 15;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 8;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 14;
				break;
			case SEED_ARTICHOKE:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 17;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 8;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 16;
				break;
			case SEED_BOKCHOY:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 19;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 8;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 18;
				break;
			case SEED_CRANBERRY:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 21;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 8;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 20;
				break;
			case SEED_BLUEJAZZ:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 27;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 8;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 26;
				break;
			case SEED_SUMMERSPANGLE:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 29;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 8;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 28;
				break;
			case SEED_FAIRYROSE:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 31;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 8;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 30;
				break;
			case SEED_HOPS:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 37;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 8;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 36;
				break;
			case SEED_AMARANTH:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 39;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 8;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 38;
				break;
			case SEED_CATUS:
				_tile[MouseIndexY][MouseIndexX].objFrameX = 8;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 41;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 8;
				_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 40;
				break;
			}
		}
	}
}

void inGameScene::harvest()
{
	if (PLAYER->getCurrentInven()->toolKind == TOOL_NONE || PLAYER->getCurrentInven()->item_image == NULL)
	{
		if (_tile[MouseIndexY][MouseIndexX].isFullyGrown)
		{
			dropFruit(_tile[MouseIndexY][MouseIndexX], _tile[MouseIndexY][MouseIndexX].seedType);
		}
		_tile[MouseIndexY][MouseIndexX].isFullyGrown = false;
		_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
		_tile[MouseIndexY][MouseIndexX].seedType = SEED_NONE;
		_tile[MouseIndexY][MouseIndexX].grownLevel = 0;

		_tile[MouseIndexY - 1][MouseIndexX].objOver = OVR_NONE;
	}
	else if (PLAYER->getCurrentInven()->toolKind != TOOL_KETTLE && PLAYER->getCurrentInven()->toolKind != TOOL_SICKLE)
	{
		_tile[MouseIndexY][MouseIndexX].isFullyGrown = false;
		_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
		_tile[MouseIndexY][MouseIndexX].seedType = SEED_NONE;
		_tile[MouseIndexY][MouseIndexX].grownLevel = 0;

		_tile[MouseIndexY - 1][MouseIndexX].objOver = OVR_NONE;
	}
}

void inGameScene::makeCropGrow()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			if (_tile[i][j].obj != OBJ_SEED) continue;
			if (_tile[i][j].isFullyGrown == false)
			{
				_tile[i][j].grownLevel += 1;
				_tile[i][j].objFrameX += 1;
				_tile[i - 1][j].ovlFrameX += 1;

				//다자랐는지 확인
				_tile[i][j].isFullyGrown = checkFullyGrown(_tile[i][j]);
			}
		}
	}
}

bool inGameScene::checkFullyGrown(tagTile tile)
{
	switch (tile.seedType)
	{
	case SEED_NONE:
		break;
	case SEED_PARSNIP:
		if (tile.grownLevel == 5) { return true; }
		else { return false; }
		break;
	case SEED_CAULIFLOWER:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_GARLIC:
		if (tile.grownLevel == 5) { return true; }
		else { return false; }
		break;
	case SEED_RHUBARB:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_TOMATO:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_HOTPEPPER:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_RADISH:
		if (tile.grownLevel == 5) { return true; }
		else { return false; }
		break;
	case SEED_STARFRUIT:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_EGGPLANT:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_PUMPKIN:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_YAM:
		if (tile.grownLevel == 5) { return true; }
		else { return false; }
		break;
	case SEED_BEET:
		if (tile.grownLevel == 5) { return true; }
		else { return false; }
		break;
	case SEED_ANCIENTFRUIT:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_TULIP:
		if (tile.grownLevel == 5) { return true; }
		else { return false; }
		break;
	case SEED_POPPY:
		if (tile.grownLevel == 5) { return true; }
		else { return false; }
		break;
	case SEED_SUNFLOWER:
		if (tile.grownLevel == 5) { return true; }
		else { return false; }
		break;
	case SEED_SWEETGEMBERRY:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_STRAWBERRY:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_GRAPE:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_COFFEEBEAN:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_GREENBEAN:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_POTATO:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_KALE:
		if (tile.grownLevel == 5) { return true; }
		else { return false; }
		break;
	case SEED_MELON:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_BLUEBERRY:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_WHEAT:
		if (tile.grownLevel == 5) { return true; }
		else { return false; }
		break;
	case SEED_REDCABBAGE:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_CORN:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_ARTICHOKE:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_BOKCHOY:
		if (tile.grownLevel == 5) { return true; }
		else { return false; }
		break;
	case SEED_CRANBERRY:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_BLUEJAZZ:
		if (tile.grownLevel == 5) { return true; }
		else { return false; }
		break;
	case SEED_SUMMERSPANGLE:
		if (tile.grownLevel == 5) { return true; }
		else { return false; }
		break;
	case SEED_FAIRYROSE:
		if (tile.grownLevel == 5) { return true; }
		else { return false; }
		break;
	case SEED_HOPS:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_AMARANTH:
		if (tile.grownLevel == 5) { return true; }
		else { return false; }
		break;
	case SEED_CATUS:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	}
}

void inGameScene::getItem(tagItem item)
{
	bool isAdded = false;
	for (auto iter : PLAYER->getInven())
	{
		if (iter.item_info == item.item_info)
		{
			iter.amount++;
			isAdded = true;
			break;
		}
		isAdded = false;
	}
	if (isAdded == false)
	{
		for (int i = 0; i < INVENMAX; i++)
		{
			if (PLAYER->getInven()[i].item_image == NULL)
			{
				PLAYER->setInvenItem(i, ITEMMANAGER->findItem(item.item_info));
				cout << PLAYER->getInven(i)->item_info << endl;
				break;
			}
		}
	}
	
}

void inGameScene::dropFruit(tagTile tile, SEED seedType)
{
	const char* str;
	switch (seedType)
	{
	case SEED_NONE:
		break;
	case SEED_PARSNIP:
		str = "파스닙";
		break;
	case SEED_CAULIFLOWER:
		str = "콜리플라워";
		break;
	case SEED_GARLIC:
		str = "마늘";
		break;
	case SEED_RHUBARB:
		str = "대황";
		break;
	case SEED_TOMATO:
		str = "토마토";
		break;
	case SEED_HOTPEPPER:
		str = "고추";
		break;
	case SEED_RADISH:
		str = "무";
		break;
	case SEED_STARFRUIT:
		str = "스타후르츠";
		break;
	case SEED_EGGPLANT:
		str = "가지";
		break;
	case SEED_PUMPKIN:
		str = "호박";
		break;
	case SEED_YAM:
		str = "참마";
		break;
	case SEED_BEET:
		str = "비";
		break;
	case SEED_ANCIENTFRUIT:
		str = "고대과일";
		break;
	case SEED_TULIP:
		str = "튤립";
		break;
	case SEED_POPPY:
		str = "양귀비";
		break;
	case SEED_SUNFLOWER:
		str = "해바라기";
		break;
	case SEED_SWEETGEMBERRY:
		str = "달콤보석베리";
		break;
	case SEED_STRAWBERRY:
		str = "딸기";
		break;
	case SEED_GRAPE:
		str = "포도";
		break;
	case SEED_COFFEEBEAN:
		str = "커피콩";
		break;
	case SEED_GREENBEAN:
		str = "완두콩";
		break;
	case SEED_POTATO:
		str = "감자";
		break;
	case SEED_KALE:
		str = "케일";
		break;
	case SEED_MELON:
		str = "멜론";
		break;
	case SEED_BLUEBERRY:
		str = "블루베리";
		break;
	case SEED_WHEAT:
		str = "밀";
		break;
	case SEED_REDCABBAGE:
		str = "적양배추";
		break;
	case SEED_CORN:
		str = "옥수수";
		break;
	case SEED_ARTICHOKE:
		str = "아티초크";
		break;
	case SEED_BOKCHOY:
		str = "청경채";
		break;
	case SEED_CRANBERRY:
		str = "크랜베리";
		break;
	case SEED_BLUEJAZZ:
		str = "블루재즈";
		break;
	case SEED_SUMMERSPANGLE:
		str = "여름별꽃";
		break;
	case SEED_FAIRYROSE:
		str = "요정장미";
		break;
	case SEED_HOPS:
		str = "홉";
		break;
	case SEED_AMARANTH:
		str = "아마란스";
		break;
	case SEED_CATUS:
		str = "선인장열매";
		break;
	}
	tagItemOnField temp;
	temp.item = ITEMMANAGER->findItem(str);
	temp.item.item_image = IMAGEMANAGER->findImage("열매(땅)");
	temp.centerX = (float)tile.rc.left + (tile.rc.right - tile.rc.left);
	temp.origCenterX = temp.centerX;
	temp.centerY = (float)tile.rc.top + (tile.rc.bottom - tile.rc.top);
	temp.origCenterY = temp.centerY;
	temp.rc = RectMakeCenter(temp.centerX, temp.centerY, 16, 16);
	temp.angle = RANDOM->range(M_PI / 4, M_PI * 3 / 4);
	temp.speed = 3.5f;
	temp.gravity = 0.0f;
	temp.isOnGround = false;
	_vItemOnField.push_back(temp);
}

void inGameScene::dropItem(tagTile tile, const char * itemInfo)
{
	tagItemOnField temp;
	temp.item = ITEMMANAGER->findItem(itemInfo);
	temp.item.item_image = IMAGEMANAGER->findImage("열매(땅)");
	temp.centerX = (float)tile.rc.left + (tile.rc.right - tile.rc.left);
	temp.origCenterX = temp.centerX;
	temp.centerY = (float)tile.rc.top + (tile.rc.bottom - tile.rc.top);
	temp.origCenterY = temp.centerY;
	temp.rc = RectMakeCenter(temp.centerX, temp.centerY, 16, 16);
	temp.angle = RANDOM->range(M_PI / 4, M_PI * 3 / 4);
	temp.speed = 3.5f;
	temp.gravity = 0.0f;
	temp.isOnGround = false;
	_vItemOnField.push_back(temp);
}

void inGameScene::ejectItem()
{
	getItemRc = RectMakeCenter(PLAYER->getCenterX(), PLAYER->getCenterY(), 5, 5);
	for (int i = 0; i < _vItemOnField.size(); i++)
	{
		if (!_vItemOnField[i].isOnGround)
		{
			_vItemOnField[i].gravity += 0.15f;
			_vItemOnField[i].centerX += cosf(_vItemOnField[i].angle) * _vItemOnField[i].speed;
			_vItemOnField[i].centerY += -sinf(_vItemOnField[i].angle) * _vItemOnField[i].speed + _vItemOnField[i].gravity;
			_vItemOnField[i].rc = RectMakeCenter(_vItemOnField[i].centerX, _vItemOnField[i].centerY, 16, 16);
			if (_vItemOnField[i].centerY > _vItemOnField[i].origCenterY)
			{
				_vItemOnField[i].gravity = 0.0f;
				_vItemOnField[i].speed = 0.0f;
				_vItemOnField[i].isOnGround = true;
			}
		}
		if (_vItemOnField[i].isOnGround)
		{
			if (getDistance(_vItemOnField[i].centerX, _vItemOnField[i].centerY, PLAYER->getCenterX(), PLAYER->getCenterY()) < 100)
			{
				_vItemOnField[i].speed += 0.05f;
				_vItemOnField[i].angle = -atan2f(PLAYER->getCenterY() - _vItemOnField[i].centerY, PLAYER->getCenterX() - _vItemOnField[i].centerX);
				_vItemOnField[i].centerX += cosf(_vItemOnField[i].angle) * _vItemOnField[i].speed;
				_vItemOnField[i].centerY += -sinf(_vItemOnField[i].angle) * _vItemOnField[i].speed;
				_vItemOnField[i].rc = RectMakeCenter(_vItemOnField[i].centerX, _vItemOnField[i].centerY, 16, 16);
			}
		}
		
		if (PtInRect(&getItemRc, PointMake(_vItemOnField[i].centerX, _vItemOnField[i].centerY)))
		{
			getItem(_vItemOnField[i].item);
			_vItemOnField.erase(_vItemOnField.begin() + i);
		}
	}
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
			if (_tile[i][j].obj != OBJ_NONE || _tile[i][j].terrain == TR_HACKED || _tile[i][j].terrain != TR_SOIL) { continue; }
			if (RANDOM->range(20) == 0)
			{
				switch (RANDOM->range(6))
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
					if (i + 1 < TILEY && j + 1 < TILEX && RANDOM->range(20) == 0)
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
					if (i + 1 < TILEY && j + 1 < TILEX && RANDOM->range(20) == 0)
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
				case 4:
					_tile[i][j].obj = OBJ_DESTRUCTIBLE;
					_tile[i][j].objType = OTY_WEED;
					switch (RANDOM->range(3))
					{
					case 0:
						_tile[i][j].objFrameX = 4;
						_tile[i][j].objFrameY = 1;
						break;
					case 1:
						_tile[i][j].objFrameX = 5;
						_tile[i][j].objFrameY = 1;
						break;
					case 2:
						_tile[i][j].objFrameX = 5;
						_tile[i][j].objFrameY = 2;
						break;
					}
					break;
				case 5:
					if (i - 1 >= 0 && _tile[i - 1][j].objOver != OVR_OVER)
					{
						switch (RANDOM->range(3))
						{
						case 0:
							_tile[i - 1][j].objOver = OVR_OVER;
							_tile[i - 1][j].ovlFrameX = 0;
							_tile[i - 1][j].ovlFrameY = 3;

							_tile[i][j].objType = OTY_GRASS;
							_tile[i][j].obj = OBJ_DESTRUCTIBLE;
							_tile[i][j].objFrameX = 0;
							_tile[i][j].objFrameY = 4;
							break;
						case 1:
							_tile[i - 1][j].objOver = OVR_OVER;
							_tile[i - 1][j].ovlFrameX = 1;
							_tile[i - 1][j].ovlFrameY = 3;

							_tile[i][j].objType = OTY_GRASS;
							_tile[i][j].obj = OBJ_DESTRUCTIBLE;
							_tile[i][j].objFrameX = 1;
							_tile[i][j].objFrameY = 4;
							break;
						case 2:
							_tile[i - 1][j].objOver = OVR_OVER;
							_tile[i - 1][j].ovlFrameX = 2;
							_tile[i - 1][j].ovlFrameY = 3;

							_tile[i][j].objType = OTY_GRASS;
							_tile[i][j].obj = OBJ_DESTRUCTIBLE;
							_tile[i][j].objFrameX = 2;
							_tile[i][j].objFrameY = 4;
							break;
						}
						break;
					}
					break;
				}
			}
		}
	}
}

void inGameScene::changeGrass()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			if (_tile[i][j].objType != OTY_GRASS) continue;
			switch (_currentSeason)
			{
			case SPRING:
				if (_tile[i][j].obj == OBJ_DESTRUCTIBLE)
				{
					_tile[i][j].objFrameY = 4;
					_tile[i - 1][j].ovlFrameY = 3;
				}
				break;
			case SUMMER:
				if (_tile[i][j].obj == OBJ_DESTRUCTIBLE)
				{
					_tile[i][j].objFrameY = 6;
					_tile[i - 1][j].ovlFrameY = 5;
				}
				break;
			case AUTUMN:
				if (_tile[i][j].obj == OBJ_DESTRUCTIBLE)
				{
					_tile[i][j].objFrameY = 8;
					_tile[i - 1][j].ovlFrameY = 7;
				}
				break;
			case WINTER:
				if (_tile[i][j].obj == OBJ_DESTRUCTIBLE)
				{
					_tile[i][j].objFrameY = 10;
					_tile[i - 1][j].ovlFrameY = 9;
				}
				break;
			}
		}
	}
	
}

void inGameScene::setCurrentSlotNumber(int mouseWheel)
{
	if (mouseWheel > 0)
	{
		PLAYER->setCurrentSlotNumber(PLAYER->getCurrentSlotNumber() - 1);
		_mouseWheel = 0;
	}
	else if (mouseWheel < 0)
	{
		PLAYER->setCurrentSlotNumber(PLAYER->getCurrentSlotNumber() + 1);
		_mouseWheel = 0;
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
