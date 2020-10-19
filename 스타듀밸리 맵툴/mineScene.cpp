#include "stdafx.h"
#include "mineScene.h"

HRESULT mineScene::init()
{
	CAMERAMANAGER->init(TILEX * TILESIZE, TILEY * TILESIZE, 30 * 16, 15 * 16);
	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());

	PLAYER->setCenterX(80.0f);
	PLAYER->setCenterY(80.0f);

	currentFloor = 1;

	checkCurrentTile();
	return S_OK;
}

void mineScene::release()
{
}

void mineScene::update()
{
	if (INPUT->GetKeyDown(VK_F2))
	{
		setRandomObstacles();
	}

	checkCurrentTile();
	ejectItem();

	PLAYER->update();
	PLAYER->playerAnimation();
	playerMove();
}

void mineScene::render()
{
	renderMap();

	CAMERAMANAGER->render(getMemDC());

	PLAYER->playerStatusRender(getMemDC());
}

void mineScene::renderMap()
{
	for (int i = (float)((float)CAMERAMANAGER->getY() / 16) - 1; i < PLAYER->getCurrentY(); i++)
	{
		for (int j = (float)((float)CAMERAMANAGER->getX() / 16) - 1; j < (float)((float)CAMERAMANAGER->getX() / 16) + (float)(WINSIZEX / 40) + 1; j++)
		{
			renderTerrain(i, j);
			renderObject(i, j);
		}
	}

	PLAYER->render();

	for (int i = PLAYER->getCurrentY(); i < (float)((float)CAMERAMANAGER->getY() / 16) + (float)(WINSIZEY / 40) + 7; i++)
	{
		for (int j = (float)((float)CAMERAMANAGER->getX() / 16) - 1; j < (float)((float)CAMERAMANAGER->getX() / 16) + (float)(WINSIZEX / 40) + 1; j++)
		{
			renderTerrain(i, j);
			renderObject(i, j);
		}
	}

	PLAYER->playerStatusRender(getMemDC());
}

void mineScene::renderTerrain(int i, int j)
{
	string str;
	if (currentFloor > 0 && currentFloor <= 5) { str = "광산 노말"; }
	if (currentFloor > 5 && currentFloor <= 10) { str = "광산 노말다크"; }
	if (currentFloor > 10 && currentFloor <= 15) { str = "광산 프로스트"; }
	if (currentFloor > 15 && currentFloor <= 20) { str = "광산 프로스트다크"; }
	IMAGEMANAGER->frameRender(str, CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top, _tile[i][j].terrainFrameX, _tile[i][j].terrainFrameY);
}

void mineScene::renderObject(int i, int j)
{
	string str;
	if (currentFloor > 0 && currentFloor <= 5) { str = "광산오브젝트 노말"; }
	if (currentFloor > 5 && currentFloor <= 10) { str = "광산오브젝트 노말다크"; }
	if (currentFloor > 10 && currentFloor <= 15) { str = "광산오브젝트 프로스트"; }
	if (currentFloor > 15 && currentFloor <= 20) { str = "광산오브젝트 프로스트다크"; }
	if (_tile[i][j].objType == OTY_ORE)
	{
		str = "광물";
	}
	IMAGEMANAGER->frameRender(str, CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top, _tile[i][j].objFrameX, _tile[i][j].objFrameY);
}

void mineScene::playerMove()
{
	if (INPUT->GetKey('W'))
	{
		rightIndexX = (float)((float)PLAYER->getCenterX() + 8) / 16;
		rightIndexY = (float)((float)PLAYER->getCenterY() + 8) / 16;
		if (rightIndexX < TILEX && rightIndexY >= 0 && rightIndexY < TILEY)
		{
			if (_tile[rightIndexY][rightIndexX].obj == OBJ_NONE)
			{
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
		downIndexX = (float)((float)PLAYER->getCenterX() + 8) / 16;
		downIndexY = (float)((float)PLAYER->getCenterY() + 8) / 16;
		if (downIndexX < TILEX && downIndexY >= 0 && downIndexY < TILEY)
		{
			if (_tile[downIndexY][downIndexX].obj == OBJ_NONE)
			{
				PLAYER->setDirection(DOWN);
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
	if (INPUT->GetKey('A'))
	{
		leftIndexX = (float)((float)PLAYER->getCenterX() + 8) / 16;
		leftIndexY = (float)((float)PLAYER->getCenterY() + 8) / 16;
		if (leftIndexX < TILEX && leftIndexY >= 0 && leftIndexY < TILEY)
		{
			if (_tile[leftIndexY][leftIndexX].obj == OBJ_NONE)
			{
				PLAYER->setDirection(LEFT);
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
	if (INPUT->GetKey('D'))
	{
		rightIndexX = (float)((float)PLAYER->getCenterX() + 8) / 16;
		rightIndexY = (float)((float)PLAYER->getCenterY() + 8) / 16;
		if (rightIndexX < TILEX && rightIndexY >= 0 && rightIndexY < TILEY)
		{
			if (_tile[rightIndexY][rightIndexX].obj == OBJ_NONE)
			{
				PLAYER->setDirection(RIGHT);
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
	if (!(INPUT->GetKey('W')) && !(INPUT->GetKey('S')) && !(INPUT->GetKey('A')) && !(INPUT->GetKey('D')))
	{
		PLAYER->setState(STAND);
	}
}

void mineScene::checkCurrentTile()
{
	if (currentIndexX != PLAYER->getCurrentX() || currentIndexY != PLAYER->getCurrentY())
	{
		currentIndexX = PLAYER->getCurrentX();
		currentIndexY = PLAYER->getCurrentY();
	}
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
	switch (RANDOM->range(7))
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
	case 4:
		_tile[i][j].objFrameX = 5;
		_tile[i][j].objFrameY = 10;
		break;
	case 5:
		_tile[i][j].objFrameX = 7;
		_tile[i][j].objFrameY = 10;
		break;
	case 6:
		_tile[i][j].objFrameX = 9;
		_tile[i][j].objFrameY = 10;
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
}

void mineScene::breakStone()
{
	if (PLAYER->getCurrentInven()->toolKind == TOOL_PICKAX)
	{
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
				RANDOM->range(3) == 0 ? str = "석탄" : str = "돌";
				RANDOM->range(2) == 0 ? number = 3 : RANDOM->range(2) == 0 ? number = 2 : number = 4;

				for (int i = 0; i < number; i++)
				{
					dropItem(_tile[mouseIndexY][mouseIndexX], str);
				}
				_tile[mouseIndexY][mouseIndexX].obj = OBJ_NONE;
				_tile[mouseIndexY][mouseIndexX].objType = OTY_NONE;
			}
			else if (_tile[mouseIndexY][mouseIndexX].objType == OTY_ORE)
			{
				const char* str = {};
				int number = 0;

				if (_tile[mouseIndexY][mouseIndexX].objFrameX == 6) { str = "구리조각"; }
				if (_tile[mouseIndexY][mouseIndexX].objFrameX == 7) { str = "철조각"; }
				if (_tile[mouseIndexY][mouseIndexX].objFrameX == 8) { str = "금조각"; }
				
				RANDOM->range(2) == 0 ? number = 3 : RANDOM->range(2) == 0 ? number = 2 : number = 4;
					
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

void mineScene::cutGrass()
{
	if (PLAYER->getCurrentInven()->toolKind == TOOL_SICKLE)
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

void mineScene::getItem(tagItem item)
{
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
			if ((*PLAYER->getInven())[i].item_image == NULL)
			{
				PLAYER->setInvenItem(i, ITEMMANAGER->findItem(item.item_info));
				cout << PLAYER->getInven(i)->item_info << endl;
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

