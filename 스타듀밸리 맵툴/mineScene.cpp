#include "stdafx.h"
#include "mineScene.h"

mineScene::mineScene()
{
	monsterCount = 0;

	//�̸� ������, ����, ����Ʈ 3���� ������ ��������
	//�� ���� ������ ���� �������� vMonster ���Ϳ� �־������ ��
	setMonsterList();
}

HRESULT mineScene::init()
{
	if (loadCount == 0)
	{
		currentFloor = 1;  //���� �ε�� �ʱ�ȭ ���� ī��Ʈ

		loadCount++;
	}
	CAMERAMANAGER->init(TILEX * TILESIZE, TILEY * TILESIZE, 30 * 16, 15 * 16);
	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());

	monsterCount = RANDOM->range(3, 8);
	loadMap();
	checkCurrentTile();

	isShowRect = false;

	for (int i = 0; i < 3; i++)
	{
		setRandomObstacles();
	}

	_vItemOnField.clear();
	vMonster.clear();

	SOUNDMANAGER->stop("����");
	SOUNDMANAGER->stop("springDay");
	
	spawnMonster();

	for (int t = 0; t < MINEMAX; t++)
	{
		for (int j = 0; j < MINEMAX; j++)
		{
			for (auto iter : vMonster)
			{
				iter->setWallNode(j, t, _tile[t][j].obj);
			}
		}
	}

	this->update();

	return S_OK;
}

void mineScene::release()
{
}

void mineScene::update()
{
	MouseIndexX = (float)((float)CAMERAMANAGER->getX() / 16) + (float)((float)_ptMouse.x / 40);
	MouseIndexY = (float)((float)CAMERAMANAGER->getY() / 16) + (float)((float)_ptMouse.y / 40);

	//���� ��ų �浹
	if (!EFFECTMANAGER->getvEffect().empty())
	{
		for (int i = 0; i < EFFECTMANAGER->getvEffect().size(); i++)
		{
			for (auto iter : vMonster)
			{
				RECT temp;
				if (IntersectRect(&temp, &iter->getRc(), &EFFECTMANAGER->getvEffect()[i].rc))
				{
					if (!(iter->getDamage()))
					{
						iter->setHp(iter->getHp() - EFFECTMANAGER->getvEffect()[i].skillDamage);
						iter->setDamage(true);
					}
				}
			}
		}
	}

	//���� ����
	for (int i = 0; i < vMonster.size(); i++)
	{
		if (vMonster[i]->getisDead())
		{
			SOUNDMANAGER->play("monsterdead", 0.2f);
			vMonster.erase(vMonster.begin() + i);
		}
	}

	if (currentFloor > 0 && currentFloor <= 5) { str = "���� �븻"; objStr = "���������Ʈ �븻"; }
	else if (currentFloor > 5 && currentFloor <= 10) { str = "���� �븻��ũ"; objStr = "���������Ʈ �븻��ũ"; }

	if (!SOUNDMANAGER->isPlaySound("bugCave"))
	{
		SOUNDMANAGER->play("bugCave", 0.05f);
	}
	
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

	skillSelect();

	playerInteraction();

	PLAYER->playerAnimation();
	
	playerMonsterCollision();

	setCurrentSlotNumber(_mouseWheel);

	if (PLAYER->getState() == STAND || PLAYER->getState() == RUN || PLAYER->getState() == CARRY || PLAYER->getState() == CARRYSTAND)
	{
		this->playerMove();
		CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());
	}
	this->ejectItem();

	for (auto iter : vMonster)
	{
		iter->update();
	}
	wallMonsterColliison();
}

void mineScene::render()
{
	renderMap();

	for (int i = 0; i < _vItemOnField.size(); i++)
	{
		_vItemOnField[i].item.item_image->frameRender(CAMERAMANAGER->getMemDC(), _vItemOnField[i].rc.left, _vItemOnField[i].rc.top, _vItemOnField[i].item.indexX, _vItemOnField[i].item.indexY);
	}
	for (auto iter : vMonster)
	{
		iter->render();
	}

	FrameRect(CAMERAMANAGER->getMemDC(), _tile[MouseIndexY][MouseIndexX].rc, RGB(255, 50, 30));

	EFFECTMANAGER->render(CAMERAMANAGER->getMemDC());

	CAMERAMANAGER->render(getMemDC());

	PLAYER->playerStatusRender(getMemDC());
}

void mineScene::savePlayer()
{
	PLAYER->savePlayerInven();
	PLAYER->savePlayerStock();
	PLAYER->savePlayerData();
	PLAYER->saveMap();
	PLAYER->saveBox();
	PLAYER->setLoadCount(0);
}

void mineScene::setCurrentSlotNumber(int mouseWheel)
{
	if (mouseWheel > 0)
	{
		SOUNDMANAGER->play("toolSwap", 0.2f);
		PLAYER->setCurrentSlotNumber(PLAYER->getCurrentSlotNumber() - 1);
		_mouseWheel = 0;
	}
	else if (mouseWheel < 0)
	{
		SOUNDMANAGER->play("toolSwap", 0.2f);
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
			if (i >= 0 && i < TILEY && j >= 0 && j < TILEX)
			{
				renderObject(i, j);
				if (isShowRect)
				{
					FrameRect(CAMERAMANAGER->getMemDC(), _tile[i][j].rc, RGB(255, 0, 0));
				}
			}
		}
	}
	PLAYER->render();

	for (int i = PLAYER->getCurrentY(); i < (float)((float)CAMERAMANAGER->getY() / 16) + (float)(WINSIZEY / 40) + 7; i++)
	{
		for (int j = (float)((float)CAMERAMANAGER->getX() / 16) - 1; j < (float)((float)CAMERAMANAGER->getX() / 16) + (float)(WINSIZEX / 40) + 1; j++)
		{
			if (i >= 0 && i < TILEY && j >= 0 && j < TILEX)
			{
				renderObject(i, j);
				if (isShowRect)
				{
					FrameRect(CAMERAMANAGER->getMemDC(), _tile[i][j].rc, RGB(255, 0, 0));

				}
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
		IMAGEMANAGER->frameRender("����", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
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
			else if (_tile[upIndexY][upIndexX].objFrameX == 0 && _tile[upIndexY][upIndexX].objFrameY == 7)
			{
				loadCount = 0;
				SWITCHMANAGER->changeScene("�ΰ���ȭ��");
				SWITCHMANAGER->startFade(96.0f, 96.0f);

			}
			else
			{
				useLadder(upIndexY, upIndexX);
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
			else
			{
				useLadder(downIndexY, downIndexX);
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
			else
			{
				useLadder(leftIndexY, leftIndexX);
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
			else
			{
				useLadder(rightIndexY, rightIndexX);
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
	else if (currentFloor > 3 && currentFloor <= 6)
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
	else if (currentFloor > 6 && currentFloor < 10)
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
			//��, ���� ����
			breakStone();

			//Ǯ ���� 
			cutGrass();
		}
	}
	if (INPUT->GetKeyDown(VK_RBUTTON))
	{
		////�� �̵��ϱ�
		//useLadder();
		//
		////������ ���ư���
		//useElevator();
	}
}

void mineScene::breakStone()
{
	if (PLAYER->getCurrentInven()->toolKind == TOOL_PICKAX)
	{
		SOUNDMANAGER->play("removeRock", 0.2f);
		PLAYER->setState(BREAKSTONE);
		if (((mouseIndexX == currentIndexX + 1 || mouseIndexX == currentIndexX - 1) && mouseIndexY == currentIndexY)
			|| (mouseIndexX == currentIndexX && (mouseIndexY == currentIndexY + 1 || mouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
			|| ((mouseIndexX == currentIndexX - 1 || mouseIndexX == currentIndexX + 1)
				&& (mouseIndexY == currentIndexY - 1 || mouseIndexY == currentIndexY + 1))) //�밢�� 4 Ÿ���϶�
		{
			if (_tile[mouseIndexY][mouseIndexX].objType == OTY_STONE)
			{
				if (PLAYER->getEnergy() > -20)
				{
					PLAYER->setEnergy(PLAYER->getDamage());
				}

				int number = 0;

				number = RANDOM->range(4);
				for (int i = 0; i < number; i++)
				{
					dropItem(_tile[mouseIndexY][mouseIndexX], ITEM_DEBRIS, 3);
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
					for (auto iter : vMonster)
					{
						iter->setWallNode(mouseIndexY, mouseIndexX, _tile[mouseIndexY][mouseIndexX].obj);
					}
				}
			}
			else if (_tile[mouseIndexY][mouseIndexX].objType == OTY_ORE)
			{
				if (PLAYER->getEnergy() > -20)
				{
					PLAYER->setEnergy(PLAYER->getDamage());
				}

				hpCount[mouseIndexY][mouseIndexX]--;
				if (hpCount[mouseIndexY][mouseIndexX] <= 0)
				{
					int tempIndexX = 0;
					int number = 0;
				
					if (_tile[mouseIndexY][mouseIndexX].objFrameX == 6) { tempIndexX = 6; }
					if (_tile[mouseIndexY][mouseIndexX].objFrameX == 7) { tempIndexX = 8; }
					if (_tile[mouseIndexY][mouseIndexX].objFrameX == 8) { tempIndexX = 12; }
				
					number = RANDOM->range(1, 4);
				
					for (int i = 0; i < number; i++)
					{
						dropItem(_tile[mouseIndexY][mouseIndexX], ITEM_ORE, tempIndexX);
					}
					_tile[mouseIndexY][mouseIndexX].obj = OBJ_NONE;
					_tile[mouseIndexY][mouseIndexX].objType = OTY_NONE;
					for (auto iter : vMonster)
					{
						iter->setWallNode(mouseIndexY, mouseIndexX, _tile[mouseIndexY][mouseIndexX].obj);
					}
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
						if (PLAYER->getEnergy() > -20)
						{
							PLAYER->setEnergy(PLAYER->getDamage());
						}

						_tile[i][j].obj = OBJ_NONE;
						_tile[i][j].objType = OTY_NONE;
						_tile[i][j].seedType = SEED_NONE;
						_tile[i][j].grownLevel = 0;
						_tile[i][j].isFullyGrown = false;

						_tile[i - 1][j].objOver = OVR_NONE;

						for (auto iter : vMonster)
						{
							iter->setWallNode(i, j, _tile[i][j].obj);
						}
					}
				}
			}
		}
	}
}

void mineScene::useLadder(int i, int j)
{
	if (_tile[i][j].objType == OTY_MINELADDER)
	{
		SOUNDMANAGER->play("stairDown", 0.2f);
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
				tempX = 435.0f;
				tempY = 222.0f;
				break;
			case 3:
				tempX = 520.0f;
				tempY = 255.0f;
				break;
			case 4:
				tempX = 440.0f;
				tempY = 295.0f;
				break;
			case 5:
				tempX = 535.0f;
				tempY = 190.0f;
				break;
			case 6:
				tempX = 635.0f;
				tempY = 120.0f;
				break;
			case 7:
				tempX = 505.0f;
				tempY = 110.0f;
				break;
			case 8:
				tempX = 490.0f;
				tempY = 105.0f;
				break;
			case 9:
				tempX = 500.0f;
				tempY = 65.0f;
				break;
			default:
				break;
			}
		SWITCHMANAGER->changeScene("����ȭ��");
		SWITCHMANAGER->startFade(tempX, tempY);
	}
	else if (_tile[i][j].objFrameX == 3 && _tile[i][j].objFrameY == 7)
	{
		loadCount = 0;
		SOUNDMANAGER->play("stairDown", 0.2f);
		SWITCHMANAGER->changeScene("�ΰ���ȭ��");
		SWITCHMANAGER->startFade(96.0f, 96.0f);
	}
}

void mineScene::useElevator()
{
	if (((mouseIndexX == currentIndexX + 1 || mouseIndexX == currentIndexX - 1) && mouseIndexY == currentIndexY)
		|| (mouseIndexX == currentIndexX && (mouseIndexY == currentIndexY + 1 || mouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
		|| ((mouseIndexX == currentIndexX - 1 || mouseIndexX == currentIndexX + 1)
			&& (mouseIndexY == currentIndexY - 1 || mouseIndexY == currentIndexY + 1))) //�밢�� 4 Ÿ���϶�
	{
		if (_tile[mouseIndexY][mouseIndexX].objFrameX == 0 && _tile[mouseIndexY][mouseIndexX].objFrameY == 7)
		{
			loadCount = 0;
			SWITCHMANAGER->changeScene("�ΰ���ȭ��");
			SWITCHMANAGER->startFade(96.0f, 96.0f);
		}
	}
}

void mineScene::loadMap()
{
	HANDLE file;
	DWORD read;
	sprintf(saveName, "save/dungeon%d.map", currentFloor);
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
		if (PLAYER->getInven()->at(i).item_kind == item.item_kind
			&& PLAYER->getInven()->at(i).indexX == item.indexX)
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
				tagItem temp;
				temp = item;
				if (item.item_kind == ITEM_DEBRIS)
				{
					temp.item_image = IMAGEMANAGER->findImage("����");
				}
				else if (item.item_kind == ITEM_ORE)
				{
					temp.item_image = IMAGEMANAGER->findImage("����������");
				}
				PLAYER->setInvenItem(i, temp);
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
			int a = 0;
			for (int i = 0; i < 36; i++)
			{
				if (PLAYER->getInven(i)->item_image != NULL) a++;
			}
			if (a != 36)
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
		}

		if (PtInRect(&getItemRc, PointMake(_vItemOnField[i].centerX, _vItemOnField[i].centerY)))
		{
			int a = 0;
			for (int i = 0; i < 36; i++)
			{
				if (PLAYER->getInven(i)->item_image != NULL) a++;
			}
			if (a != 36)
			{
				getItem(_vItemOnField[i].item);
				_vItemOnField.erase(_vItemOnField.begin() + i);
			}
		}
	}
}

void mineScene::dropItem(tagTile tile, ITEM itemKind, int indexX)
{
	tagItemOnField temp;
	temp.item = ITEMMANAGER->findDropItem(itemKind, indexX);
	if (itemKind == ITEM_DEBRIS)
	{
		temp.item.item_image = IMAGEMANAGER->findImage("����(��)");
	}
	else if(itemKind == ITEM_ORE)
	{
		temp.item.item_image = IMAGEMANAGER->findImage("����");
	}
	//���� �߰�
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

void mineScene::skillClick()
{
}

void mineScene::skillSelect()
{
	PLAYER->skillUpdate();
	PLAYER->getskill()->setSkill(PLAYER->getCurrentSlotNumber());
}

void mineScene::setMonsterList()
{
	monster* presetSlime = new monster(MTYPE_SLIME, 0, 0, 30, 5, .8f);
	presetSlime->init();
	monsterList.push_back(presetSlime);

	monster* presetBug = new monster(MTYPE_BUG, 0, 0, 70, 7, .4f);
	presetBug->init();
	monsterList.push_back(presetBug);

	monster* presetRockCrab = new monster(MTYPE_ROCKCRAB, 0, 0, 150, 9, .4f);
	presetRockCrab->init();
	monsterList.push_back(presetRockCrab);

	monster* presetSerpent = new monster(MTYPE_SERPENT, 0, 0, 220, 10, .6f);
	presetSerpent->init();
	monsterList.push_back(presetSerpent);
}

void mineScene::spawnMonster()
{
	int idxX, idxY;
	float x, y;
	while (vMonster.size() < monsterCount)
	{
		int rand = RANDOM->range(10);
		
		if (rand >= 0 && rand < 4)
		{
		ONE:
			idxX = RANDOM->range(0, 50);
			idxY = RANDOM->range(0, 50);

			if (_tile[idxY][idxX].obj == OBJ_NONE)
			{
				monster* temp = new monster(*monsterList[0]);
				temp->setCenterX((float)idxX * 16.0f - 8.0f);
				temp->setCenterY((float)idxY * 16.0f - 8.0f);
				temp->setRc((float)idxX * 16.0f - 8.0f, (float)idxY * 16.0f - 8.0f);
				temp->setSpeed(0.8f);
				vMonster.push_back(temp);
			}
			else
			{
				goto ONE;
			}
		}
		else if (rand >= 4 && rand < 7)
		{
		TWO:
			idxX = RANDOM->range(0, 50);
			idxY = RANDOM->range(0, 50);

			if (_tile[idxY][idxX].obj == OBJ_NONE)
			{
				monster* temp = new monster(*monsterList[1]);
				temp->setCenterX((float)idxX * 16.0f - 8.0f);
				temp->setCenterY((float)idxY * 16.0f - 8.0f);
				temp->setRc((float)idxX * 16.0f - 8.0f, (float)idxY * 16.0f - 8.0f);
				temp->setSpeed(0.8f);
				vMonster.push_back(temp);
			}
			else
			{
				goto TWO;
			}
		}
		else if (rand >= 7 && rand < 10)
		{
		THREE:
			idxX = RANDOM->range(0, 50);
			idxY = RANDOM->range(0, 50);

			if (_tile[idxY][idxX].obj == OBJ_NONE)
			{
				monster* temp = new monster(*monsterList[2]);
				temp->setCenterX((float)idxX * 16.0f - 8.0f);
				temp->setCenterY((float)idxY * 16.0f - 8.0f);
				temp->setRc((float)idxX * 16.0f - 8.0f, (float)idxY * 16.0f - 8.0f);
				temp->setSpeed(0.8f);
				vMonster.push_back(temp);
			}
			else
			{
				goto THREE;
			}
		}
		else
		{
		FOUR:
			idxX = RANDOM->range(0, 50);
			idxY = RANDOM->range(0, 50);

			if (_tile[idxY][idxX].obj == OBJ_NONE)
			{
				monster* temp = new monster(*monsterList[3]);
				temp->setCenterX((float)idxX * 16.0f - 8.0f);
				temp->setCenterY((float)idxY * 16.0f - 8.0f);
				temp->setRc((float)idxX * 16.0f - 8.0f, (float)idxY * 16.0f - 8.0f);
				temp->setSpeed(2.0f);
				vMonster.push_back(temp);
			}
			else
			{
				goto FOUR;
			}
		}
	}
}

void mineScene::playerMonsterCollision()
{
	for (auto iter : vMonster)
	{
		RECT temp;
		if (IntersectRect(&temp, &PLAYER->getRc(), &iter->getRc()) && !PLAYER->getIsHit())
		{
			if (PLAYER->getHpBarX() + iter->getDmg() * 2 > 580)
			{
				SOUNDMANAGER->play("death", 0.2f);

				loadCount = 0;
				PLAYER->setIsSprinkled(false);
				savePlayer();
				PLAYER->resetClock();
				SWITCHMANAGER->changeScene("����ȭ��");
				SWITCHMANAGER->startFade(838.0f, 864.0f);
			}
			else
			{
				SOUNDMANAGER->play("hitPlayer", 0.3f);
				PLAYER->setHp(iter->getDmg() * 2);
				PLAYER->setIsHit(true);
			}
		}
	}
}

void mineScene::wallMonsterColliison()
{
	for (auto iter : vMonster)
	{
		if (iter->getIsLocked())
		{
			RECT temp;
			for (int i = 0; i < 50; i++)
			{
				for (int j = 0; j < 50; j++)
				{
					if (IntersectRect(&temp, &iter->getRc(), &_tile[i][j].rc))
					{
						if (_tile[i][j].obj != OBJ_NONE)
						{
							float x, y;
							x = _tile[iter->getCurrentY()][iter->getCurrentX()].rc.left +
								(_tile[iter->getCurrentY()][iter->getCurrentX()].rc.right -
									_tile[iter->getCurrentY()][iter->getCurrentX()].rc.left);
							y = _tile[iter->getCurrentY()][iter->getCurrentX()].rc.top +
								(_tile[iter->getCurrentY()][iter->getCurrentX()].rc.bottom -
									_tile[iter->getCurrentY()][iter->getCurrentX()].rc.top);

							iter->setCenterX(x);
							iter->setCenterY(y);
							iter->setIsLocked(false);
						}
					}
				}
			}
		}
	}
	
}
