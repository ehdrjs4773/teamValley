#include "stdafx.h"
#include "mineScene.h"

mineScene::mineScene()
{
	currentFloor = 1;  //최초 로드시 초기화 방지 카운트

	//미리 슬라임, 버그, 서펜트 3종류 프리셋 만들어놓음
	//새 몬스터 생성시 위의 프리셋을 vMonster 벡터에 넣어버리면 됨
	setMonsterList();
}

HRESULT mineScene::init()
{
	CAMERAMANAGER->init(TILEX * TILESIZE, TILEY * TILESIZE, 30 * 16, 15 * 16);
	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());

	loadMap();
	checkCurrentTile();

	isShowRect = false;

	for (int i = 0; i < 3; i++)
	{
		setRandomObstacles();
	}

	_vItemOnField.clear();

	//vMonster.push_back(monsterList[0]);

	SOUNDMANAGER->stop("농장");
	SOUNDMANAGER->stop("springDay");
	
	this->update();

	return S_OK;
}

void mineScene::release()
{
}

void mineScene::update()
{
	if (!SOUNDMANAGER->isPlaySound("bugCave"))
	{
		SOUNDMANAGER->play("bugCave", 0.05f);
	}
	if (currentFloor > 0 && currentFloor <= 5) { str = "광산 노말"; objStr = "광산오브젝트 노말"; }
	else if (currentFloor > 5 && currentFloor <= 10) { str = "광산 노말다크"; objStr = "광산오브젝트 노말다크"; }

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

	checkCurrentTile(); 
	PLAYER->update();
	PLAYER->playerAnimation();
	playerInteraction();

	setCurrentSlotNumber(_mouseWheel);

	if (PLAYER->getState() == STAND || PLAYER->getState() == RUN || PLAYER->getState() == CARRY || PLAYER->getState() == CARRYSTAND)
	{
		this->playerMove();
		CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());
	}
	this->ejectItem();

	cout << PLAYER->getCenterX() << "\t" << PLAYER->getCenterY() << endl;
}

void mineScene::render()
{
	renderMap();

	for (int i = 0; i < _vItemOnField.size(); i++)
	{
		_vItemOnField[i].item.item_image->frameRender(CAMERAMANAGER->getMemDC(), _vItemOnField[i].rc.left, _vItemOnField[i].rc.top, _vItemOnField[i].item.indexX, _vItemOnField[i].item.indexY);
	}

	CAMERAMANAGER->render(getMemDC());

	PLAYER->playerStatusRender(getMemDC());
}

void mineScene::setCurrentSlotNumber(int mouseWheel)
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

void mineScene::renderMap()
{
	renderTerrain();

	for (int i = (float)((float)CAMERAMANAGER->getY() / 16) - 1; i < PLAYER->getCurrentY(); i++)
	{
		for (int j = (float)((float)CAMERAMANAGER->getX() / 16) - 1; j < (float)((float)CAMERAMANAGER->getX() / 16) + (float)(WINSIZEX / 40) + 1; j++)
		{
			renderObject(i, j);
			if (isShowRect)
			{
				FrameRect(CAMERAMANAGER->getMemDC(), _tile[i][j].rc, RGB(255, 0, 0));
			}
		}
	}

	PLAYER->render();
	monsterRender();

	for (int i = PLAYER->getCurrentY(); i < (float)((float)CAMERAMANAGER->getY() / 16) + (float)(WINSIZEY / 40) + 7; i++)
	{
		for (int j = (float)((float)CAMERAMANAGER->getX() / 16) - 1; j < (float)((float)CAMERAMANAGER->getX() / 16) + (float)(WINSIZEX / 40) + 1; j++)
		{
			renderObject(i, j);
			if (isShowRect)
			{
				FrameRect(CAMERAMANAGER->getMemDC(), _tile[i][j].rc, RGB(255, 0, 0));
			
			}
		}
	}
	if (isShowRect)
	{
		Rectangle(CAMERAMANAGER->getMemDC(), _tile[currentIndexY][currentIndexX].rc);
		Rectangle(CAMERAMANAGER->getMemDC(), _tile[mouseIndexY][mouseIndexX].rc);
	}
	PLAYER->playerStatusRender(getMemDC());
}

void mineScene::renderTerrain()
{
	for (int i = (float)((float)CAMERAMANAGER->getY() / 16) - 1; i < (float)((float)CAMERAMANAGER->getY() / 16) + (float)(WINSIZEY / 40) + 1; i++)
	{
		for (int j = (float)((float)CAMERAMANAGER->getX() / 16) - 1; j < (float)((float)CAMERAMANAGER->getX() / 16) + (float)(WINSIZEX / 40) + 1; j++)
		{
			if (i >= 0 && i < TILEY && j >= 0 && j < TILEX)
			{
				if (_tile[i][j].terrain == TR_GROUND)
				{
					IMAGEMANAGER->frameRender(str, CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
						_tile[i][j].terrainFrameX, _tile[i][j].terrainFrameY);
				}
			}
		}
	}
}

void mineScene::renderObject(int i, int j)
{
	if (_tile[i][j].obj == OBJ_NONE) return;
	
	if (_tile[i][j].objType == OTY_ORE)
	{
		IMAGEMANAGER->frameRender("광물", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
			_tile[i][j].objFrameX, _tile[i][j].objFrameY);
	}
	else
	{
		IMAGEMANAGER->frameRender(objStr, CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
			_tile[i][j].objFrameX, _tile[i][j].objFrameY);
	}
}

void mineScene::playerMove()
{
	if (INPUT->GetKey('W'))
	{
		upIndexX = (float)((float)PLAYER->getCenterX()) / 16;
		upIndexY = (float)((float)PLAYER->getCenterY()) / 16;
		if (upIndexX < TILEX && upIndexY >= 0 && upIndexY < TILEY)
		{
			if (_tile[upIndexY][upIndexX].obj == OBJ_NONE)
			{
				if (!SOUNDMANAGER->isPlaySound("movesoil"))
				{
					SOUNDMANAGER->play("movesoil", 0.2f);
				}
				PLAYER->setDirection(UP);
				if (PLAYER->getCurrentInven()->item_kind == ITEM_SEED)
				{
					PLAYER->setState(CARRY);
				}
				else
				{
					PLAYER->setState(RUN);
				}
				PLAYER->setCenterY(PLAYER->getCenterY() - PLAYER->getSpeed());
			}
		}
	}
	if (INPUT->GetKey('S'))
	{
		downIndexX = (float)((float)PLAYER->getCenterX()) / 16;
		downIndexY = (float)((float)PLAYER->getCenterY() + 16) / 16;
		if (downIndexX < TILEX && downIndexY >= 0 && downIndexY < TILEY)
		{
			if (_tile[downIndexY][downIndexX].obj == OBJ_NONE)
			{
				if (!SOUNDMANAGER->isPlaySound("movesoil"))
				{
					SOUNDMANAGER->play("movesoil", 0.2f);
				}
				PLAYER->setDirection(DOWN);
				if (PLAYER->getCurrentInven()->item_kind == ITEM_SEED)
				{
					PLAYER->setState(CARRY);
				}
				else
				{
					PLAYER->setState(RUN);
				}
				PLAYER->setCenterY(PLAYER->getCenterY() + PLAYER->getSpeed());
			}
		}
	}
	if (INPUT->GetKey('A'))
	{
		leftIndexX = (float)((float)PLAYER->getCenterX() - 8) / 16;
		leftIndexY = (float)((float)PLAYER->getCenterY() + 8) / 16;
		if (leftIndexX < TILEX && leftIndexY >= 0 && leftIndexY < TILEY)
		{
			if (_tile[leftIndexY][leftIndexX].obj == OBJ_NONE)
			{
				if (!SOUNDMANAGER->isPlaySound("movesoil"))
				{
					SOUNDMANAGER->play("movesoil", 0.2f);
				}
				PLAYER->setDirection(LEFT);
				if (PLAYER->getCurrentInven()->item_kind == ITEM_SEED)
				{
					PLAYER->setState(CARRY);
				}
				else
				{
					PLAYER->setState(RUN);
				}
				PLAYER->setCenterX(PLAYER->getCenterX() - PLAYER->getSpeed());
			}
		}
	}
	if (INPUT->GetKey('D'))
	{
		rightIndexX = (float)((float)PLAYER->getCenterX() + 8) / 16;
		rightIndexY = (float)((float)PLAYER->getCenterY() + 8) / 16;
		if (rightIndexX < TILEX && rightIndexY >= 0 && rightIndexY < TILEY)
		{
			if (_tile[rightIndexY][rightIndexX].obj == OBJ_NONE)
			{
				if (!SOUNDMANAGER->isPlaySound("movesoil"))
				{
					SOUNDMANAGER->play("movesoil", 0.2f);
				}
				PLAYER->setDirection(RIGHT);
				if (PLAYER->getCurrentInven()->item_kind == ITEM_SEED)
				{
					PLAYER->setState(CARRY);
				}
				else
				{
					PLAYER->setState(RUN);
				}
				PLAYER->setCenterX(PLAYER->getCenterX() + PLAYER->getSpeed());
			}
		}
	}
	if (!(INPUT->GetKey('W')) && !(INPUT->GetKey('S')) && !(INPUT->GetKey('A')) && !(INPUT->GetKey('D')))
	{
		PLAYER->setState(STAND);
		if (SOUNDMANAGER->isPlaySound("movesoil"))
		{
			SOUNDMANAGER->stop("movesoil");
		}
		if (SOUNDMANAGER->isPlaySound("movegrass"))
		{
			SOUNDMANAGER->stop("movegrass");
		}
	}
}

void mineScene::checkCurrentTile()
{
	currentIndexX = PLAYER->getCurrentX();
	currentIndexY = PLAYER->getCurrentY();

	mouseIndexX = (float)((float)CAMERAMANAGER->getX() / 16) + (float)((float)_ptMouse.x / 40);
	mouseIndexY = (float)((float)CAMERAMANAGER->getY() / 16) + (float)((float)_ptMouse.y / 40);
}

void mineScene::setRandomObstacles()
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (_tile[i][j].obj != OBJ_NONE || (i == PLAYER->getCurrentY() && j == PLAYER->getCurrentX())) { continue; }
			if (i >= 8 && i <= 12 && j >= 22 && j <= 26) continue;
			if (RANDOM->range(20) == 0)
			{
				switch (RANDOM->range(5))
				{
				case 0:
					setStone(i, j);
					break;
				case 1:
					setStone(i, j);
					break;
				case 2:
					setStone(i, j);
					break;
				case 3:
					setWeed(i, j);
					break;
				case 4:
					setOre(i, j);
					break;
				}
			}
		}
	}
}

void mineScene::setStone(int i, int j)
{
	_tile[i][j].obj = OBJ_DESTRUCTIBLE;
	_tile[i][j].objType = OTY_STONE;
	switch (RANDOM->range(4))
	{
	case 0:
		_tile[i][j].objFrameX = 5;
		_tile[i][j].objFrameY = 9;
		break;
	case 1:
		_tile[i][j].objFrameX = 7;
		_tile[i][j].objFrameY = 9;
		break;
	case 2:
		_tile[i][j].objFrameX = 9;
		_tile[i][j].objFrameY = 9;
		break;
	case 3:
		_tile[i][j].objFrameX = 11;
		_tile[i][j].objFrameY = 9;
		break;
	}
}

void mineScene::setWeed(int i, int j)
{
	_tile[i][j].obj = OBJ_DESTRUCTIBLE;
	_tile[i][j].objType = OTY_WEED;
	switch (RANDOM->range(3))
	{
	case 0:
		_tile[i][j].objFrameX = 8;
		_tile[i][j].objFrameY = 11;
		break;
	case 1:
		_tile[i][j].objFrameX = 9;
		_tile[i][j].objFrameY = 11;
		break;
	case 2:
		_tile[i][j].objFrameX = 10;
		_tile[i][j].objFrameY = 11;
		break;
	}
}

void mineScene::setOre(int i, int j)
{
	_tile[i][j].obj = OBJ_DESTRUCTIBLE;
	_tile[i][j].objType = OTY_ORE;
	hpCount[i][j] = 2;
	if (currentFloor > 0 && currentFloor <= 3)
	{
		_tile[i][j].objFrameX = 6;
		_tile[i][j].objFrameY = 0;
	}
	if (currentFloor > 3 && currentFloor <= 6)
	{
		switch (RANDOM->range(2))
		{
		case 0:
			_tile[i][j].objFrameX = 6;
			_tile[i][j].objFrameY = 0;
			break;
		case 1:
			_tile[i][j].objFrameX = 7;
			_tile[i][j].objFrameY = 0;
			break;
		}
	}
	if (currentFloor > 6 && currentFloor <= 10)
	{
		switch (RANDOM->range(3))
		{
		case 0:
			_tile[i][j].objFrameX = 6;
			_tile[i][j].objFrameY = 0;
			break;
		case 1:
			_tile[i][j].objFrameX = 7;
			_tile[i][j].objFrameY = 0;
			break;
		case 2:
			_tile[i][j].objFrameX = 8;
			_tile[i][j].objFrameY = 0;
			break;
		}
	}
}

void mineScene::playerInteraction()
{
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (mouseIndexY < currentIndexY)
		{
			PLAYER->setDirection(UP);
		}
		if (mouseIndexY > currentIndexY)
		{
			PLAYER->setDirection(DOWN);
		}
		if (mouseIndexX < currentIndexX)
		{
			PLAYER->setDirection(LEFT);
		}
		if (mouseIndexX > currentIndexX)
		{
			PLAYER->setDirection(RIGHT);
		}
		if (PLAYER->getState() == RUN || PLAYER->getState() == STAND)
		{
			//돌, 광석 깨기
			breakStone();

			//풀 베기 
			cutGrass();
		}
	}
	if (INPUT->GetKeyDown(VK_RBUTTON))
	{
		//층 내려가기
		useLadder();

		//마을로 돌아가기
		useElevator();
	}
}

void mineScene::breakStone()
{
	if (PLAYER->getCurrentInven()->toolKind == TOOL_PICKAX)
	{
		SOUNDMANAGER->play("removeRock", 0.2f);
		PLAYER->setState(BREAKSTONE);
		if (((mouseIndexX == currentIndexX + 1 || mouseIndexX == currentIndexX - 1) && mouseIndexY == currentIndexY)
			|| (mouseIndexX == currentIndexX && (mouseIndexY == currentIndexY + 1 || mouseIndexY == currentIndexY - 1)) //상하좌우 4타일일때
			|| ((mouseIndexX == currentIndexX - 1 || mouseIndexX == currentIndexX + 1)
				&& (mouseIndexY == currentIndexY - 1 || mouseIndexY == currentIndexY + 1))) //대각선 4 타일일때
		{
			if (_tile[mouseIndexY][mouseIndexX].objType == OTY_STONE)
			{
				const char* str = {};
				int number = 0;

				number = RANDOM->range(4);
				for (int i = 0; i < number; i++)
				{
					RANDOM->range(1, 5) == 0 ? str = "석탄" : str = "돌";
					dropItem(_tile[mouseIndexY][mouseIndexX], str);
				}
				if (RANDOM->range(20) == 0)
				{
					_tile[mouseIndexY][mouseIndexX].obj = OBJ_INDESTRUCTIBLE;
						_tile[mouseIndexY][mouseIndexX].objType = OTY_MINELADDER;
						_tile[mouseIndexY][mouseIndexX].objFrameX = 6;
						_tile[mouseIndexY][mouseIndexX].objFrameY = 12;
				}
				else
				{
					_tile[mouseIndexY][mouseIndexX].obj = OBJ_NONE;
						_tile[mouseIndexY][mouseIndexX].objType = OTY_NONE;
				}
			}
			else if (_tile[mouseIndexY][mouseIndexX].objType == OTY_ORE)
			{
				hpCount[mouseIndexY][mouseIndexX]--;
				if (hpCount[mouseIndexY][mouseIndexX] <= 0)
				{
					const char* str = {};
					int number = 0;
				
					if (_tile[mouseIndexY][mouseIndexX].objFrameX == 6) { str = "구리조각"; }
					if (_tile[mouseIndexY][mouseIndexX].objFrameX == 7) { str = "철조각"; }
					if (_tile[mouseIndexY][mouseIndexX].objFrameX == 8) { str = "금조각"; }
				
					number = RANDOM->range(1, 4);
				
					for (int i = 0; i < number; i++)
					{
						dropItem(_tile[mouseIndexY][mouseIndexX], str);
					}
					_tile[mouseIndexY][mouseIndexX].obj = OBJ_NONE;
					_tile[mouseIndexY][mouseIndexX].objType = OTY_NONE;
				}
			}
		}
	}
}

void mineScene::cutGrass()
{
	if (PLAYER->getCurrentInven()->toolKind == TOOL_SICKLE)
	{
		SOUNDMANAGER->play("removeGrass", 0.2f);
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
					if (_tile[i][j].objType == OTY_WEED)
					{
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

void mineScene::useLadder()
{
	if (((mouseIndexX == currentIndexX + 1 || mouseIndexX == currentIndexX - 1) && mouseIndexY == currentIndexY)
		|| (mouseIndexX == currentIndexX && (mouseIndexY == currentIndexY + 1 || mouseIndexY == currentIndexY - 1)) //상하좌우 4타일일때
		|| ((mouseIndexX == currentIndexX - 1 || mouseIndexX == currentIndexX + 1)
			&& (mouseIndexY == currentIndexY - 1 || mouseIndexY == currentIndexY + 1))) //대각선 4 타일일때
	{
		if (_tile[mouseIndexY][mouseIndexX].objType == OTY_MINELADDER)
		{
			currentFloor++;
			this->init();
			float tempX, tempY;
			switch (currentFloor)
			{
			case 0:
				break;
			case 1: 
				break;
			case 2:
				tempX = 390.0f;
				tempY = 240.0f;
				break;
			case 3:


			default:
				break;
			}
			SWITCHMANAGER->changeScene("광산화면");
			SWITCHMANAGER->startFade(tempX, tempY);
		}
	}
}

void mineScene::useElevator()
{
	if (((mouseIndexX == currentIndexX + 1 || mouseIndexX == currentIndexX - 1) && mouseIndexY == currentIndexY)
		|| (mouseIndexX == currentIndexX && (mouseIndexY == currentIndexY + 1 || mouseIndexY == currentIndexY - 1)) //상하좌우 4타일일때
		|| ((mouseIndexX == currentIndexX - 1 || mouseIndexX == currentIndexX + 1)
			&& (mouseIndexY == currentIndexY - 1 || mouseIndexY == currentIndexY + 1))) //대각선 4 타일일때
	{
		if (_tile[mouseIndexY][mouseIndexX].objFrameX == 0 && _tile[mouseIndexY][mouseIndexX].objFrameY == 7)
		{
			SWITCHMANAGER->changeScene("인게임화면");
			SWITCHMANAGER->startFade(288.0f, 64.0f);
		}
	}
}

void mineScene::monsterMove()
{
}

void mineScene::monsterRender()
{
}

void mineScene::loadMap()
{
	HANDLE file;
	DWORD read;
	sprintf(saveName, "save/dungeon%d.map", currentFloor);
	cout << saveName << endl;
	file = CreateFile(saveName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tile, sizeof(_tile), &read, NULL);
	CloseHandle(file);
	setTileRect();
}

void mineScene::setTileRect()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tile[i][j].rc = RectMake(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE);
		}
	}
}

void mineScene::getItem(tagItem item)
{
	SOUNDMANAGER->play("getItem", 0.2f);
	bool isAdded = false;
	for (int i = 0; i < INVENMAX; i++)
	{
		if (PLAYER->getInven()->at(i).item_info == item.item_info)
		{
			PLAYER->setInvenItemAmount(i, PLAYER->getInven()->at(i).amount + 1);
			isAdded = true;
			break;
		}
		isAdded = false;
	}
	if (isAdded == false)
	{
		for (int i = 0; i < INVENMAX; i++)
		{
			if (PLAYER->getInven()->at(i).item_image == NULL)
			{
				PLAYER->setInvenItem(i, ITEMMANAGER->findItem(item.item_info));
				break;
			}
		}
	}
}

void mineScene::ejectItem()
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

void mineScene::dropItem(tagTile tile, const char * itemInfo)
{
	tagItemOnField temp;
	temp.item = ITEMMANAGER->findItem(itemInfo);
	if (itemInfo == "석탄")
	{
		temp.item.item_image = IMAGEMANAGER->findImage("광물");
	}
	else if(itemInfo == "구리조각")
	{
		temp.item.item_image = IMAGEMANAGER->findImage("광물");
	}
	else if (itemInfo == "철조각")
	{
		temp.item.item_image = IMAGEMANAGER->findImage("광물");
	}
	else if (itemInfo == "금조각")
	{
		temp.item.item_image = IMAGEMANAGER->findImage("광물");
	}
	else if (itemInfo == "돌")
	{
		temp.item.item_image = IMAGEMANAGER->findImage("열매(땅)");
	}
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

void mineScene::setMonsterList()
{
	monster* presetSlime = new monster(MTYPE_SLIME, 0, 0, 10, 5, 4);
	monsterList.push_back(presetSlime);

	monster* presetBug = new monster(MTYPE_BUG, 0, 0, 5, 5, 4);
	monsterList.push_back(presetBug);

	monster* presetSerpent = new monster(MTYPE_SERPENT, 0, 0, 20, 15, 4);
	monsterList.push_back(presetSerpent);
}


