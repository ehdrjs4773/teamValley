#include "stdafx.h"
#include "inGameScene.h"

TCHAR inGameScene::saveName[MAX_PATH];

inGameScene::inGameScene()
{
	loadCount = 0;  //���� �ε�� �ʱ�ȭ ���� ī��Ʈ
}

HRESULT inGameScene::init()
{
	CAMERAMANAGER->init(TILEX * TILESIZE, TILEY * TILESIZE, 30 * 16, 15 * 16);
	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());

	isShopOpen = false;

	if (loadCount == 0) // ���� �ѹ��� �ʱ�ȭ �����..
	{
		load();
		setTileRect();

		changeSeason(SPRING);

		SOUNDMANAGER->stop("��������");
		isShowRect = false;

		checkPlayerTile();
		loadCount = 1;

		_tile[56][26].portal = PT_HOUSE;
		_tile[69][37].portal = PT_BARN;
		//_tile[0][i + 14].portal = PT_CHICKENHOUSE;
		_tile[20][50].portal = PT_SHOP;
		_tile[3][18].portal = PT_MINE;

		isSprinkled = false;

		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				_tile[i][j].terrain = terrainSelect(_tile[i][j].terrainFrameX, _tile[i][j].terrainFrameY);
			}
		}
	}

	return S_OK;
}

void inGameScene::release()
{
}

void inGameScene::update()
{
	isSprinkled = PLAYER->getIsSprinkled();
	sprinklerWork();
	if (!SOUNDMANAGER->isPlaySound("����"))
	{
		SOUNDMANAGER->play("����", 0.05f);
	}

	PLAYER->update();


	if (PLAYER->getisSkill())
	{
		PLAYER->skillUpdate();

		PLAYER->getskill()->setSkill(PLAYER->getCurrentSkillNumber());
	}

	checkPlayerTile();

	if (PLAYER->getState() == STAND || PLAYER->getState() == RUN||PLAYER->getState()==CARRY||PLAYER->getState()==CARRYSTAND)
	{
		playerMove();
	}

	playerInteraction();

	//������ �ٴڿ� �������� �ϴ°�
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

	moveScene();
}

void inGameScene::render()
{
	renderMap();

	if (isShowRect)
	{
		Rectangle(CAMERAMANAGER->getMemDC(), _tile[currentIndexY][currentIndexX].rc);
		Rectangle(CAMERAMANAGER->getMemDC(), _tile[MouseIndexY][MouseIndexX].rc);
	}

	for (int i = 0; i < _vItemOnField.size(); i++)
	{
		_vItemOnField[i].item.item_image->frameRender(CAMERAMANAGER->getMemDC(), _vItemOnField[i].rc.left, _vItemOnField[i].rc.top, _vItemOnField[i].item.indexX, _vItemOnField[i].item.indexY);
	}

	if (PLAYER->getisSkill())
	{
		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				if (PLAYER->getskillclick())
				{
					RECT temp;
					float pointX = (float)CAMERAMANAGER->getX() + (float)((float)_ptMouse.x / WINSIZEX * 480);
					float pointY = (float)CAMERAMANAGER->getY() + (float)((float)_ptMouse.y / WINSIZEY * 230);
					POINT pos = { pointX,pointY };

					if (PtInRect(&_tile[i][j].rc, pos))
					{
						for (int k = -1; k <= 1; k++)
						{
							for (int l = -1; l <= 1; l++)
							{
								FrameRect(CAMERAMANAGER->getMemDC(), _tile[i - k][j - l].rc, RGB(255, 0, 0));
							}
						}
					}
				}
			}
		}
	}
	
	//����Ʈ ����
	EFFECTMANAGER->render(CAMERAMANAGER->getMemDC());

	CAMERAMANAGER->render(getMemDC());

	if (PLAYER->getisSkill())
	{
		PLAYER->skill_AniRender(getMemDC());
	}

	PLAYER->playerStatusRender(getMemDC());
}

void inGameScene::load()
{
	//DialogBox(_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), _hWnd, inGameScene::DlgProc);

	HANDLE file;
	DWORD read;

	sprintf(saveName, "save/save.map");
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

void inGameScene::renderMap()
{
	//Ÿ�� ����
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
			}
		}
	}
	//�÷��̾�� �ؿ� �׷����� ������Ʈ ����
	for (int i = (float)((float)CAMERAMANAGER->getY() / 16) - 1; i < currentIndexY; i++)
	{
		for (int j = (float)((float)CAMERAMANAGER->getX() / 16) - 1; j < (float)((float)CAMERAMANAGER->getX() / 16) + (float)(WINSIZEX / 40) + 1; j++)
		{
			renderObjects(i, j);
		}
	}

	//�÷��̾� ����
	PLAYER->render();
	PLAYER->playerCarryItem(CAMERAMANAGER->getMemDC());

	//�÷��̾�� ���� ��������� ������Ʈ ����
	for (int i = currentIndexY; i < (float)((float)CAMERAMANAGER->getY() / 16) + (float)(WINSIZEY / 40) + 7; i++)
	{
		for (int j = (float)((float)CAMERAMANAGER->getX() / 16) - 1; j < (float)((float)CAMERAMANAGER->getX() / 16) + (float)(WINSIZEX / 40) + 1; j++)
		{
			renderObjects(i, j);
		}
	}
}

void inGameScene::renderObjects(int i, int j)
{
	if (i >= 0 && i < TILEY && j >= 0 && j < TILEX)
	{
		//�ΰ��� ȭ�� ������Ʈ �׸���
		if (_tile[i][j].obj != OBJ_NONE)
		{
			if (_tile[i][j].obj == OBJ_BUILDING)
			{
				IMAGEMANAGER->frameRender("�ǹ�", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i][j].objFrameX, _tile[i][j].objFrameY);
			}
			else if (_tile[i][j].objType == OTY_STONE || _tile[i][j].objType == OTY_LARGESTONE
				|| _tile[i][j].objType == OTY_BRANCH || _tile[i][j].objType == OTY_HARDTREE
				|| _tile[i][j].objType == OTY_GRASS || _tile[i][j].objType == OTY_WEED)
			{
				IMAGEMANAGER->frameRender("������ֹ�", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i][j].objFrameX, _tile[i][j].objFrameY);
			}
			else if (_tile[i][j].objType == OTY_CROP)
			{
				IMAGEMANAGER->frameRender("�۹�", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i][j].objFrameX, _tile[i][j].objFrameY);
			}
			else if (_tile[i][j].objType == OTY_SPRINKLER)
			{
				IMAGEMANAGER->frameRender("������Ŭ��", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i][j].objFrameX, _tile[i][j].objFrameY);
			}
			else if (_tile[i][j].objType == OTY_WOODENFENCE || _tile[i][j].objType == OTY_WOODENFENCEDOOR || _tile[i][j].objType == OTY_WOODENFENCEDOOROPEN)
			{
				IMAGEMANAGER->findImage("�����潺")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i][j].objFrameX, _tile[i][j].objFrameY);
				IMAGEMANAGER->findImage("�����潺")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 1][j].rc.left, _tile[i - 1][j].rc.top,
					_tile[i][j].objFrameX, _tile[i][j].objFrameY - 1);
			}
			else if (_tile[i][j].objType == OTY_STONEFENCE || _tile[i][j].objType == OTY_STONEFENCEDOOR || _tile[i][j].objType == OTY_STONEFENCEDOOROPEN)
			{
				IMAGEMANAGER->findImage("���潺")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i][j].objFrameX, _tile[i][j].objFrameY);
				IMAGEMANAGER->findImage("���潺")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 1][j].rc.left, _tile[i - 1][j].rc.top,
					_tile[i][j].objFrameX, _tile[i][j].objFrameY - 1);
			}
			else if (_tile[i][j].objType == OTY_TREE || _tile[i][j].objType == OTY_TREETRUNK)
			{
				renderTree(i, j);
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
				IMAGEMANAGER->frameRender("�۹�", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i][j].ovlFrameX, _tile[i][j].ovlFrameY);
			}
			else if (_tile[i + 1][j].objType == OTY_GRASS && i + 1 < TILEY)
			{
				IMAGEMANAGER->frameRender("������ֹ�", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
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

void inGameScene::renderTree(int i, int j)
{
	if (_tile[i][j].objType == OTY_TREE)
	{
		if (_tile[i][j].grownLevel == 4)
		{
			if (i - 5 >= 0 && j - 1 >= 0)
			{
				IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i][j].tree.bodyIndexX, _tile[i][j].tree.bodyIndexY);

				IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 5][j - 1].rc.left, _tile[i - 5][j - 1].rc.top,
					_tile[i][j].tree.bodyIndexX - 2, _tile[i][j].tree.bodyIndexY - 9);
				IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 4][j - 1].rc.left, _tile[i - 4][j - 1].rc.top,
					_tile[i][j].tree.bodyIndexX - 2, _tile[i][j].tree.bodyIndexY - 8);
				IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 3][j - 1].rc.left, _tile[i - 3][j - 1].rc.top,
					_tile[i][j].tree.bodyIndexX - 2, _tile[i][j].tree.bodyIndexY - 7);
				IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 2][j - 1].rc.left, _tile[i - 2][j - 1].rc.top,
					_tile[i][j].tree.bodyIndexX - 2, _tile[i][j].tree.bodyIndexY - 6);
				IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 1][j - 1].rc.left, _tile[i - 1][j - 1].rc.top,
					_tile[i][j].tree.bodyIndexX - 2, _tile[i][j].tree.bodyIndexY - 5);

				IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 5][j].rc.left, _tile[i - 5][j].rc.top,
					_tile[i][j].tree.bodyIndexX - 1, _tile[i][j].tree.bodyIndexY - 9);
				IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 4][j].rc.left, _tile[i - 4][j].rc.top,
					_tile[i][j].tree.bodyIndexX - 1, _tile[i][j].tree.bodyIndexY - 8);
				IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 3][j].rc.left, _tile[i - 3][j].rc.top,
					_tile[i][j].tree.bodyIndexX - 1, _tile[i][j].tree.bodyIndexY - 7);
				IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 2][j].rc.left, _tile[i - 2][j].rc.top,
					_tile[i][j].tree.bodyIndexX - 1, _tile[i][j].tree.bodyIndexY - 6);
				IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 1][j].rc.left, _tile[i - 1][j].rc.top,
					_tile[i][j].tree.bodyIndexX - 1, _tile[i][j].tree.bodyIndexY - 5);

				IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 5][j + 1].rc.left, _tile[i - 5][j + 1].rc.top,
					_tile[i][j].tree.bodyIndexX, _tile[i][j].tree.bodyIndexY - 9);
				IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 4][j + 1].rc.left, _tile[i - 4][j + 1].rc.top,
					_tile[i][j].tree.bodyIndexX, _tile[i][j].tree.bodyIndexY - 8);
				IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 3][j + 1].rc.left, _tile[i - 3][j + 1].rc.top,
					_tile[i][j].tree.bodyIndexX, _tile[i][j].tree.bodyIndexY - 7);
				IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 2][j + 1].rc.left, _tile[i - 2][j + 1].rc.top,
					_tile[i][j].tree.bodyIndexX, _tile[i][j].tree.bodyIndexY - 6);
				IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 1][j + 1].rc.left, _tile[i - 1][j + 1].rc.top,
					_tile[i][j].tree.bodyIndexX, _tile[i][j].tree.bodyIndexY - 5);
			}
		}
		if (_tile[i][j].grownLevel == 3)
		{
			if (i - 1 >= 0)
			{
				IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i][j].tree.bodyIndexX, _tile[i][j].tree.bodyIndexY - 0);
				IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 1][j].rc.left, _tile[i - 1][j].rc.top,
					_tile[i][j].tree.bodyIndexX, _tile[i][j].tree.bodyIndexY - 1);
			}
		}
		if (_tile[i][j].grownLevel >= 0 && _tile[i][j].grownLevel <= 2)
		{
			IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
				_tile[i][j].tree.bodyIndexX, _tile[i][j].tree.bodyIndexY);
		}
	}
	else if (_tile[i][j].objType == OTY_TREETRUNK)
	{
		IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
			_tile[i][j].tree.bodyIndexX, _tile[i][j].tree.bodyIndexY - 0);
		IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 1][j].rc.left, _tile[i - 1][j].rc.top,
			_tile[i][j].tree.bodyIndexX, _tile[i][j].tree.bodyIndexY - 1);
	}
}

void inGameScene::playerMove()
{
	if (!PLAYER->getInventoryMove())
	{
		checkPlayerTile();
		if (INPUT->GetKey('D'))
		{
			rightIndexX = (float)((float)PLAYER->getCenterX() + 8) / 16;
			rightIndexY = (float)((float)PLAYER->getCenterY() + 8) / 16;
			if (rightIndexX < TILEX && rightIndexY >= 0 && rightIndexY < TILEY)
			{
				if (_tile[rightIndexY][rightIndexX].obj == OBJ_NONE || _tile[rightIndexY][rightIndexX].objType == OTY_GRASS
					|| (_tile[rightIndexY][rightIndexX].obj == OBJ_SEED
						&& _tile[rightIndexY][rightIndexX].seedType != SEED_GREENBEAN
						&& _tile[rightIndexY][rightIndexX].seedType != SEED_HOPS
						&& _tile[rightIndexY][rightIndexX].seedType != SEED_GRAPE))
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
					|| (_tile[leftIndexY][leftIndexX].obj == OBJ_SEED
						&& _tile[leftIndexY][leftIndexX].seedType != SEED_GREENBEAN
						&& _tile[leftIndexY][leftIndexX].seedType != SEED_HOPS
						&& _tile[leftIndexY][leftIndexX].seedType != SEED_GRAPE))
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
					|| (_tile[upIndexY][upIndexX].obj == OBJ_SEED
						&& _tile[upIndexY][upIndexX].seedType != SEED_GREENBEAN
						&& _tile[upIndexY][upIndexX].seedType != SEED_HOPS
						&& _tile[upIndexY][upIndexX].seedType != SEED_GRAPE))
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
			downIndexX = (float)((float)PLAYER->getCenterX()) / 16;
			downIndexY = (float)((float)PLAYER->getCenterY() + 16) / 16;
			if (downIndexX >= 0 && downIndexX < TILEX && downIndexY < TILEY)
			{
				if (_tile[downIndexY][downIndexX].obj == OBJ_NONE || _tile[downIndexY][downIndexX].objType == OTY_GRASS
					|| (_tile[downIndexY][downIndexX].obj == OBJ_SEED
						&& _tile[downIndexY][downIndexX].seedType != SEED_GREENBEAN
						&& _tile[downIndexY][downIndexX].seedType != SEED_HOPS
						&& _tile[downIndexY][downIndexX].seedType != SEED_GRAPE))
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
					PLAYER->setCenterY(PLAYER->getCenterY() + PLAYER->getSpeed());
				}
			}
		}
		if (!INPUT->GetKey('S') && !INPUT->GetKey('A') && !INPUT->GetKey('D') && !INPUT->GetKey('W'))
		{
			if (PLAYER->getState() == RUN)
			{
				PLAYER->setIndex(0);
				PLAYER->setState(STAND);
			}
			else if (PLAYER->getState() == CARRY)
			{
				PLAYER->setIndex(0);
				PLAYER->setState(CARRYSTAND);

			}
		}
	}
	
}

void inGameScene::moveScene()
{
	if (_tile[currentIndexY][currentIndexX].portal == PT_BARN)
	{
		SWITCHMANAGER->changeScene("�ǹ���ȭ��");
		SWITCHMANAGER->startFade(780.0f, 890.0f);
	}
	else if (_tile[currentIndexY][currentIndexX].portal == PT_SHOP)
	{
		isShopOpen = true;
		SWITCHMANAGER->changeScene("������");
		SWITCHMANAGER->startFade(278.0f, 326.0f);
	}
	else if (_tile[currentIndexY][currentIndexX].portal == PT_HOUSE)
	{
		//������ �Ѿ�� Ÿ�� ���� �Ѱ���
		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				PLAYER->saveTile(i, j, _tile[i][j]);
			}
		}
		SWITCHMANAGER->changeScene("����ȭ��");
		SWITCHMANAGER->startFade(762.0f,887.0f);
	}
	else if (_tile[currentIndexY][currentIndexX].portal == PT_MINE)
	{
		SWITCHMANAGER->changeScene("����ȭ��");
		SWITCHMANAGER->startFade(464.0f, 240.0f);
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

	if (PLAYER->getCurrentInven()->item_kind == ITEM_SEED)
	{
		if (!INPUT->GetKey('W') && !INPUT->GetKey('S') && !INPUT->GetKey('A') && !INPUT->GetKey('D'))
		{
			PLAYER->setState(CARRYSTAND);
		}
	}
	else
	{
		if (!INPUT->GetKey('W') && !INPUT->GetKey('S') && !INPUT->GetKey('A') && !INPUT->GetKey('D'))
		{
			if (PLAYER->getState() == STAND || PLAYER->getState() == CARRYSTAND)
			{
				PLAYER->setState(STAND);
			}
		}
	}
	
	if (!PtInRect(&PLAYER->getInventory()->getqucikRect(), _ptMouse))
	{

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
			if (PLAYER->getState() == RUN || PLAYER->getState() == STAND || PLAYER->getState() == CARRYSTAND)
			{
				//�� ����
				if (PLAYER->getCurrentInven()->toolKind == TOOL_HOE)
				{
					hackGround();
				}
				//��������
				if (PLAYER->getCurrentInven()->toolKind == TOOL_AX)
				{
					cutdownTree();
				}
				//��, ���� ����
				if (PLAYER->getCurrentInven()->toolKind == TOOL_PICKAX)
				{
					breakStone();
				}
				//Ǯ ���� 
				if (PLAYER->getCurrentInven()->toolKind == TOOL_SICKLE)
				{
					cutGrass();
				}
				//�� �ɱ�

				if (PLAYER->getCurrentInven()->item_kind == ITEM_SEED)
				{
					plantSeed();

				}

				//�潺 ��ġ
				if (PLAYER->getCurrentInven()->item_kind == ITEM_WOODENFENCE || PLAYER->getCurrentInven()->item_kind == ITEM_STONEFENCE
					|| PLAYER->getCurrentInven()->item_kind == ITEM_WOODENFENCEDOOR
					|| PLAYER->getCurrentInven()->item_kind == ITEM_STONEFENCEDOOR)
				{

					setFence();
				}

				//���Ѹ���
				if (PLAYER->getCurrentInven()->toolKind == TOOL_KETTLE && _tile[MouseIndexY][MouseIndexX].terrain == TR_HACKED)
				{
					waterGround();
				}
				//��ä���
				if (PLAYER->getCurrentInven()->toolKind == TOOL_KETTLE && _tile[MouseIndexY][MouseIndexX].objType == OTY_WELL)
				{

					fillWater();
				}
				//�����ϱ� (�켱�� �����ڸ�)
				if (PLAYER->getCurrentInven()->toolKind == TOOL_SWORD)
				{
					attack();
				}
			}
			//������Ŭ�� ��ġ
			setSprinkler();

			if (MouseIndexX == 35 && MouseIndexY == 53 || MouseIndexY == 54)
			{
				if (!PLAYER->getIsShowInventory())
				{
					if (!PLAYER->getIsShowInventory())
					{
						PLAYER->openPlayerStorageCover();
					}
				}

			}
		}
		cout << MouseIndexX << "\t" << MouseIndexY << "\t" << _ptMouse.x << "\t" << _ptMouse.y << endl;
	}

	

	if (INPUT->GetKeyDown(VK_RBUTTON))
	{
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1)
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1))) //�밢�� 4 Ÿ���϶�
		{
			//��Ȯ
			harvest();
		}
	}
}

void inGameScene::hackGround()
{
	
		PLAYER->setState(DIGGROUND);
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1) //�밢�� 4 Ÿ���϶�
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1)))
		{
			if (_tile[MouseIndexY][MouseIndexX].obj == OBJ_NONE && _tile[MouseIndexY][MouseIndexX].terrain == TR_SOIL)
			{
				_tile[MouseIndexY][MouseIndexX].terrain = TR_HACKED;
				_tile[MouseIndexY][MouseIndexX].terrainFrameX = 20;
				_tile[MouseIndexY][MouseIndexX].terrainFrameY = 12;
				PLAYER->setHpBarX(PLAYER->getHpBarX() + PLAYER->getDamage());

				checkHacked();
			}
		}

}

void inGameScene::cutdownTree()
{

		PLAYER->setState(CUTDOWNTREE);
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1) //�밢�� 4 Ÿ���϶�
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1)))
		{
			//�ܴ��� ����
			//if (_tile[MouseIndexY][MouseIndexX].objType == OTY_HARDTREE)
			//{
			//	if (_tile[MouseIndexY][MouseIndexX].obj == OBJ_DESTRUCTIBLE)
			//	{
			//		if (_tile[MouseIndexY][MouseIndexX].tree.hp > 0)
			//		{
			//			_tile[MouseIndexY][MouseIndexX].tree.hp -= 1;
			//		}
			//		else if (_tile[MouseIndexY][MouseIndexX].tree.hp == 0)
			//		{
			//			//�ܴ��� ������ ��� �������� ã�� �κ�
			//			if (_tile[MouseIndexY + 1][MouseIndexX].objType == OTY_HARDTREE)
			//			{
			//				if (_tile[MouseIndexY + 1][MouseIndexX + 1].objType == OTY_HARDTREE)
			//				{
			//					
			//				}
			//				else if (_tile[MouseIndexY + 1][MouseIndexX - 1].objType == OTY_HARDTREE)
			//				{

			//				}
			//			}
			//			else if (_tile[MouseIndexY - 1][MouseIndexX].objType == OTY_HARDTREE)
			//			{
			//				if (_tile[MouseIndexY - 1][MouseIndexX + 1].objType == OTY_HARDTREE)
			//				{

			//				}
			//				else if (_tile[MouseIndexY - 1][MouseIndexX - 1].objType == OTY_HARDTREE)
			//				{

			//				}
			//			}
			//			for (int i = 0; i < 4; i++)
			//			{
			//				dropItem(_tile[MouseIndexY][MouseIndexX], "�ܴ��� ����");
			//			}
			//			_tile[MouseIndexY][MouseIndexX].objType = OTY_NONE;
			//			_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
			//			tagTree temp;
			//			memset(&temp, 0, sizeof(temp));
			//			_tile[MouseIndexY][MouseIndexX].tree = temp;
			//		}
			//	}
			//}
			
			//�ڸ� �� �ִ� ����
			if (_tile[MouseIndexY][MouseIndexX].objType == OTY_TREE)
			{
				if (_tile[MouseIndexY][MouseIndexX].obj == OBJ_DESTRUCTIBLE && _tile[MouseIndexY][MouseIndexX].isFullyGrown)
				{
					if (_tile[MouseIndexY][MouseIndexX].tree.hp > 0)
					{
						_tile[MouseIndexY][MouseIndexX].tree.hp -= 1;
						PLAYER->setHpBarX(PLAYER->getHpBarX() + PLAYER->getDamage());
					}
					else if (_tile[MouseIndexY][MouseIndexX].tree.hp == 0)
					{
						for (int i = 0; i < 5; i++)
						{
							if (RANDOM->range(3) == 0)
							{
								if (_tile[MouseIndexY][MouseIndexX].tree.treeType == TREE_PINE)
								{
									dropItem(_tile[MouseIndexY][MouseIndexX], "�ҳ��� ����");
								}
								if (_tile[MouseIndexY][MouseIndexX].tree.treeType == TREE_MAPLE)
								{
									dropItem(_tile[MouseIndexY][MouseIndexX], "��ǳ���� ����");
								}
								if (_tile[MouseIndexY][MouseIndexX].tree.treeType == TREE_OAK)
								{
									dropItem(_tile[MouseIndexY][MouseIndexX], "������ ����");
								}
							}
							dropItem(_tile[MouseIndexY][MouseIndexX], "����");
						}
						_tile[MouseIndexY][MouseIndexX].objType = OTY_TREETRUNK;
						if (_tile[MouseIndexY][MouseIndexX].tree.treeType == TREE_PINE)
						{
							_tile[MouseIndexY][MouseIndexX].tree.bodyIndexX = 8;
							_tile[MouseIndexY][MouseIndexX].tree.bodyIndexY = 7;
							EFFECTMANAGER->treeCol(
								"�ҳ���",
								(_tile[MouseIndexY][MouseIndexX].rc.left + (_tile[MouseIndexY][MouseIndexX].rc.right - _tile[MouseIndexY][MouseIndexX].rc.left) / 2),
								(_tile[MouseIndexY][MouseIndexX].rc.top + (_tile[MouseIndexY][MouseIndexX].rc.bottom - _tile[MouseIndexY][MouseIndexX].rc.top) / 2)
							);

						}
						if (_tile[MouseIndexY][MouseIndexX].tree.treeType == TREE_MAPLE)
						{
							_tile[MouseIndexY][MouseIndexX].tree.bodyIndexX = 5;
							_tile[MouseIndexY][MouseIndexX].tree.bodyIndexY = 7;
							EFFECTMANAGER->treeCol(
								"��ǳ����",
								(_tile[MouseIndexY][MouseIndexX].rc.left + (_tile[MouseIndexY][MouseIndexX].rc.right - _tile[MouseIndexY][MouseIndexX].rc.left) / 2),
								(_tile[MouseIndexY][MouseIndexX].rc.top + (_tile[MouseIndexY][MouseIndexX].rc.bottom - _tile[MouseIndexY][MouseIndexX].rc.top) / 2)
							);
						}
						if (_tile[MouseIndexY][MouseIndexX].tree.treeType == TREE_OAK)
						{
							_tile[MouseIndexY][MouseIndexX].tree.bodyIndexX = 2;
							_tile[MouseIndexY][MouseIndexX].tree.bodyIndexY = 7;
							EFFECTMANAGER->treeCol(
								"������",
								(_tile[MouseIndexY][MouseIndexX].rc.left + (_tile[MouseIndexY][MouseIndexX].rc.right - _tile[MouseIndexY][MouseIndexX].rc.left) / 2),
								(_tile[MouseIndexY][MouseIndexX].rc.top + (_tile[MouseIndexY][MouseIndexX].rc.bottom - _tile[MouseIndexY][MouseIndexX].rc.top) / 2)
							);
						}
						_tile[MouseIndexY][MouseIndexX].tree.hp = 3;
				
					}
				}
			}

			//���� ��ġ
			if (_tile[MouseIndexY][MouseIndexX].objType == OTY_TREETRUNK)
			{
				if (_tile[MouseIndexY][MouseIndexX].tree.hp > 0)
				{
					_tile[MouseIndexY][MouseIndexX].tree.hp -= 1;
					PLAYER->setHpBarX(PLAYER->getHpBarX() + PLAYER->getDamage());
				}
				else if (_tile[MouseIndexY][MouseIndexX].tree.hp == 0)
				{
					for (int i = 0; i < 3; i++)
					{
						dropItem(_tile[MouseIndexY][MouseIndexX], "����");
					}

					_tile[MouseIndexY][MouseIndexX].objType = OTY_NONE;
					_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
					tagTree temp;
					memset(&temp, 0, sizeof(temp));
					_tile[MouseIndexY][MouseIndexX].tree = temp;
				}
			}

			//��������
			if (_tile[MouseIndexY][MouseIndexX].objType == OTY_BRANCH)
			{
				dropItem(_tile[MouseIndexY][MouseIndexX], "����");
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_NONE;
				PLAYER->setHpBarX(PLAYER->getHpBarX() + PLAYER->getDamage());
			}
		}

}

void inGameScene::breakStone()
{

		PLAYER->setState(BREAKSTONE);
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1)
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1))) //�밢�� 4 Ÿ���϶�
		{
			if (_tile[MouseIndexY][MouseIndexX].objType == OTY_LARGESTONE)
			{

			}
			if (_tile[MouseIndexY][MouseIndexX].objType == OTY_STONE)
			{
				dropItem(_tile[MouseIndexY][MouseIndexX], "��");
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_NONE;
				PLAYER->setHpBarX(PLAYER->getHpBarX() + PLAYER->getDamage());
			}
			if (_tile[MouseIndexY][MouseIndexX].objType == OTY_WOODENFENCE)
			{
				dropItem(_tile[MouseIndexY][MouseIndexX], "������Ÿ��");
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_NONE;
				PLAYER->setHpBarX(PLAYER->getHpBarX() + PLAYER->getDamage());
			}
			if (_tile[MouseIndexY][MouseIndexX].objType == OTY_STONEFENCE)
			{
				dropItem(_tile[MouseIndexY][MouseIndexX], "�����Ÿ��");
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_NONE;
				PLAYER->setHpBarX(PLAYER->getHpBarX() + PLAYER->getDamage());
			}
		}
	
}

void inGameScene::cutGrass()
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
						_tile[i][j].obj = OBJ_NONE;
						_tile[i][j].objType = OTY_NONE;
						_tile[i][j].seedType = SEED_NONE;
						_tile[i][j].grownLevel = 0;
						_tile[i][j].isFullyGrown = false;

						_tile[i - 1][j].objOver = OVR_NONE;

						PLAYER->setHpBarX(PLAYER->getHpBarX() + PLAYER->getDamage());
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

void inGameScene::setFence()
{
	if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
		|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
		|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1)
			&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1))) //�밢�� 4 Ÿ���϶�
	{
		if (_tile[MouseIndexY][MouseIndexX].obj == OBJ_NONE)
		{
			//�潺�϶�
			if (PLAYER->getCurrentInven()->item_kind == ITEM_WOODENFENCE)
			{
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_DESTRUCTIBLE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_WOODENFENCE;
				_tile[MouseIndexY][MouseIndexX].objFrameX = 2;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 3;
			}
			if (PLAYER->getCurrentInven()->item_kind == ITEM_STONEFENCE)
			{
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_DESTRUCTIBLE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_STONEFENCE;
				_tile[MouseIndexY][MouseIndexX].objFrameX = 2;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 3;
			}


			if (PLAYER->getCurrentInven()->item_kind == ITEM_WOODENFENCEDOOR)
			{
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_DESTRUCTIBLE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_WOODENFENCEDOOR;
				_tile[MouseIndexY][MouseIndexX].objFrameX = 2;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 11;
			}
			if (PLAYER->getCurrentInven()->item_kind == ITEM_STONEFENCEDOOR)
			{
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_DESTRUCTIBLE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_STONEFENCEDOOR;
				_tile[MouseIndexY][MouseIndexX].objFrameX = 2;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 11;
			}
		}
	}
	checkFence();
}

void inGameScene::waterGround()
{

		PLAYER->setState(SPRAYWATER);
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1) //�밢�� 4 Ÿ���϶�
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1)))
		{
			if(PLAYER->getWaterAmount()>=2)
			{
				PLAYER->setWaterAmount(PLAYER->getWaterAmount() - 2);
				PLAYER->setHpBarX(PLAYER->getHpBarX() + PLAYER->getDamage());

				_tile[MouseIndexY][MouseIndexX].isWet = true;
				checkHacked();
			}
		}

}

void inGameScene::fillWater()
{

		PLAYER->setState(FILLWATER);
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1) //�밢�� 4 Ÿ���϶�
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1)))
		{
			PLAYER->setWaterAmount(34);

		}
}

void inGameScene::plantSeed()
{
	//�۹� �ɱ�
	if (!(PLAYER->getCurrentInven()->seedKind == SEED_PINETREE || PLAYER->getCurrentInven()->seedKind == SEED_MAPLETREE || PLAYER->getCurrentInven()->seedKind == SEED_OAKTREE)
		&& _tile[MouseIndexY][MouseIndexX].terrain == TR_HACKED)
	{
		
		PLAYER->setState(CARRYSTAND);
	
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1) //�밢�� 4 Ÿ���϶�
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1)))
		{
			if (_tile[MouseIndexY][MouseIndexX].obj == OBJ_NONE)
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

	//���� �ɱ�
	if ((PLAYER->getCurrentInven()->seedKind == SEED_PINETREE || PLAYER->getCurrentInven()->seedKind == SEED_MAPLETREE || PLAYER->getCurrentInven()->seedKind == SEED_OAKTREE)
			&& _tile[MouseIndexY][MouseIndexX].terrain != TR_HACKED)
	{
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1) //�밢�� 4 Ÿ���϶�
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1)))
		{
			if (_tile[MouseIndexY][MouseIndexX].obj == OBJ_NONE)
			{
				if (PLAYER->getCurrentInven()->seedKind == SEED_PINETREE)
				{
					_tile[MouseIndexY][MouseIndexX].tree.bodyIndexX = 8;
					_tile[MouseIndexY][MouseIndexX].tree.bodyIndexY = 8;
					_tile[MouseIndexY][MouseIndexX].tree.treeType = TREE_PINE;
				}
				if (PLAYER->getCurrentInven()->seedKind == SEED_MAPLETREE)
				{
					_tile[MouseIndexY][MouseIndexX].tree.bodyIndexX = 5;
					_tile[MouseIndexY][MouseIndexX].tree.bodyIndexY = 8;
					_tile[MouseIndexY][MouseIndexX].tree.treeType = TREE_MAPLE;
				}
				if (PLAYER->getCurrentInven()->seedKind == SEED_OAKTREE)
				{
					_tile[MouseIndexY][MouseIndexX].tree.bodyIndexX = 2;
					_tile[MouseIndexY][MouseIndexX].tree.bodyIndexY = 8;
					_tile[MouseIndexY][MouseIndexX].tree.treeType = TREE_OAK;
				}

				_tile[MouseIndexY][MouseIndexX].grownLevel = 0;
				_tile[MouseIndexY][MouseIndexX].isFullyGrown = false;
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_DESTRUCTIBLE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_TREE;
				_tile[MouseIndexY][MouseIndexX].seedType = PLAYER->getCurrentInven()->seedKind;
				_tile[MouseIndexY][MouseIndexX].tree.treeImage = IMAGEMANAGER->findImage("����");
				_tile[MouseIndexY][MouseIndexX].tree.hp = 5;
			}
		}
	}
}

void inGameScene::harvest()
{
	if (_tile[MouseIndexY][MouseIndexX].isFullyGrown)
	{
		dropFruit(_tile[MouseIndexY][MouseIndexX], _tile[MouseIndexY][MouseIndexX].seedType);
		if (_tile[MouseIndexY][MouseIndexX].seedType == SEED_TOMATO
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_HOTPEPPER
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_STARFRUIT
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_EGGPLANT
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_ANCIENTFRUIT
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_SWEETGEMBERRY
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_STRAWBERRY
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_GRAPE
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_COFFEEBEAN)	//������ ��Ȯ�� �� �ִ� �۹���
		{
			_tile[MouseIndexY][MouseIndexX].isFullyGrown = false;
			_tile[MouseIndexY][MouseIndexX].grownLevel = 5;
			_tile[MouseIndexY][MouseIndexX].objFrameX = 7;
			_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 7;
		}
		else if (_tile[MouseIndexY][MouseIndexX].seedType == SEED_GREENBEAN
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_BLUEBERRY
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_CORN
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_ARTICHOKE
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_CRANBERRY
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_HOPS
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_CATUS)	//������ ��Ȯ�� �� �ִ� �۹���
		{
			_tile[MouseIndexY][MouseIndexX].isFullyGrown = false;
			_tile[MouseIndexY][MouseIndexX].grownLevel = 5;
			_tile[MouseIndexY][MouseIndexX].objFrameX = 15;
			_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 15;
		}
		else
		{
			_tile[MouseIndexY][MouseIndexX].isFullyGrown = false;
			_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
			_tile[MouseIndexY][MouseIndexX].seedType = SEED_NONE;
			_tile[MouseIndexY][MouseIndexX].grownLevel = 0;

			_tile[MouseIndexY - 1][MouseIndexX].objOver = OVR_NONE;
		}
	}
}

void inGameScene::attack()
{

		PLAYER->setState(ATTACK);
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1) //�밢�� 4 Ÿ���϶�
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1)))
		{
			if (_tile[MouseIndexY][MouseIndexX].objType == OTY_TREE)
			{
				if (_tile[MouseIndexY][MouseIndexX].obj == OBJ_DESTRUCTIBLE && _tile[MouseIndexY][MouseIndexX].isFullyGrown)
				{
					if (_tile[MouseIndexY][MouseIndexX].tree.hp > 0)
					{
						_tile[MouseIndexY][MouseIndexX].tree.hp -= 1;
					}
					else if (_tile[MouseIndexY][MouseIndexX].tree.hp == 0)
					{
						for (int i = 0; i < 5; i++)
						{
							if (RANDOM->range(3) == 0)
							{
								if (_tile[MouseIndexY][MouseIndexX].tree.treeType == TREE_PINE)
								{
									dropItem(_tile[MouseIndexY][MouseIndexX], "�ҳ��� ����");
								}
								if (_tile[MouseIndexY][MouseIndexX].tree.treeType == TREE_MAPLE)
								{
									dropItem(_tile[MouseIndexY][MouseIndexX], "��ǳ���� ����");
								}
								if (_tile[MouseIndexY][MouseIndexX].tree.treeType == TREE_OAK)
								{
									dropItem(_tile[MouseIndexY][MouseIndexX], "������ ����");
								}
							}
							dropItem(_tile[MouseIndexY][MouseIndexX], "����");
						}
						_tile[MouseIndexY][MouseIndexX].objType = OTY_TREETRUNK;
						if (_tile[MouseIndexY][MouseIndexX].tree.treeType == TREE_PINE)
						{
							_tile[MouseIndexY][MouseIndexX].tree.bodyIndexX = 8;
							_tile[MouseIndexY][MouseIndexX].tree.bodyIndexY = 7;
						}
						if (_tile[MouseIndexY][MouseIndexX].tree.treeType == TREE_MAPLE)
						{
							_tile[MouseIndexY][MouseIndexX].tree.bodyIndexX = 5;
							_tile[MouseIndexY][MouseIndexX].tree.bodyIndexY = 7;
						}
						if (_tile[MouseIndexY][MouseIndexX].tree.treeType == TREE_OAK)
						{
							_tile[MouseIndexY][MouseIndexX].tree.bodyIndexX = 2;
							_tile[MouseIndexY][MouseIndexX].tree.bodyIndexY = 7;
						}
						_tile[MouseIndexY][MouseIndexX].tree.hp = 3;
					}
				}
			}

			//���� ��ġ
			if (_tile[MouseIndexY][MouseIndexX].objType == OTY_TREETRUNK)
			{
				if (_tile[MouseIndexY][MouseIndexX].tree.hp > 0)
				{
					_tile[MouseIndexY][MouseIndexX].tree.hp -= 1;
				}
				else if (_tile[MouseIndexY][MouseIndexX].tree.hp == 0)
				{
					for (int i = 0; i < 3; i++)
					{
						dropItem(_tile[MouseIndexY][MouseIndexX], "����");
					}

					_tile[MouseIndexY][MouseIndexX].objType = OTY_NONE;
					_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
					tagTree temp;
					memset(&temp, 0, sizeof(temp));
					_tile[MouseIndexY][MouseIndexX].tree = temp;
				}
			}

			//��������
			if (_tile[MouseIndexY][MouseIndexX].objType == OTY_BRANCH)
			{
				dropItem(_tile[MouseIndexY][MouseIndexX], "����");
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_NONE;
			}
		}
}

void inGameScene::setSprinkler()
{
	if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
		|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
		|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1)
			&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1))) //�밢�� 4 Ÿ���϶�
	{
		if (_tile[MouseIndexY][MouseIndexX].obj == OBJ_NONE && _tile[MouseIndexY][MouseIndexX].terrain == TR_SOIL)
		{
			//������Ŭ��
			if (PLAYER->getCurrentInven()->item_kind == ITEM_SPRINKLER)
			{
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_DESTRUCTIBLE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_SPRINKLER;
				_tile[MouseIndexY][MouseIndexX].objFrameX = PLAYER->getCurrentInven()->indexX;
				_tile[MouseIndexY][MouseIndexX].objFrameY = PLAYER->getCurrentInven()->indexY;
			}
		}
	}
}

void inGameScene::sprinklerWork()
{
	if (!isSprinkled)
	{
		cout << "work" << endl;
		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				if (_tile[i][j].objType == OTY_SPRINKLER)
				{
					if (_tile[i - 1][j - 1].terrain == TR_HACKED) { _tile[i - 1][j - 1].isWet = true; }
					if (_tile[i - 1][j].terrain == TR_HACKED) { _tile[i - 1][j].isWet = true; }
					if (_tile[i - 1][j + 1].terrain == TR_HACKED) { _tile[i - 1][j + 1].isWet = true; }
					if (_tile[i][j - 1].terrain == TR_HACKED) { _tile[i][j - 1].isWet = true; }
					if (_tile[i][j + 1].terrain == TR_HACKED) { _tile[i][j + 1].isWet = true; }
					if (_tile[i + 1][j - 1].terrain == TR_HACKED) { _tile[i + 1][j - 1].isWet = true; }
					if (_tile[i + 1][j].terrain == TR_HACKED) { _tile[i + 1][j].isWet = true; }
					if (_tile[i + 1][j + 1].terrain == TR_HACKED) { _tile[i + 1][j + 1].isWet = true; }
				}
				checkHacked();
			}
		}
		PLAYER->setIsSprinkled(true);
		isSprinkled = true;
		cout << "end" << endl;
	}
}

void inGameScene::makeCropGrow()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			if (_tile[i][j].obj != OBJ_SEED && _tile[i][j].objType != OTY_TREE) continue;
			if (!_tile[i][j].isFullyGrown)
			{
				if ((_tile[MouseIndexY][MouseIndexX].seedType == SEED_TOMATO
					|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_HOTPEPPER
					|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_STARFRUIT
					|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_EGGPLANT
					|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_ANCIENTFRUIT
					|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_SWEETGEMBERRY
					|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_STRAWBERRY
					|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_GRAPE
					|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_COFFEEBEAN
					|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_GREENBEAN
					|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_BLUEBERRY
					|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_CORN
					|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_ARTICHOKE
					|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_CRANBERRY
					|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_HOPS
					|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_CATUS)
					&& (_tile[i][j].objFrameX == 7 || _tile[i][j].objFrameX == 15))
				{
					_tile[i][j].grownLevel += 1;
					_tile[i][j].objFrameX -= 1;
					_tile[i - 1][j].ovlFrameX -= 1;
				}
				else if (_tile[i][j].seedType == SEED_PINETREE)
				{
					_tile[i][j].grownLevel += 1;
					if (_tile[i][j].grownLevel == 1)
					{
						_tile[i][j].tree.bodyIndexX = 6;
						_tile[i][j].tree.bodyIndexY = 8;
					}
					else if (_tile[i][j].grownLevel == 2)
					{
						_tile[i][j].tree.bodyIndexX = 7;
						_tile[i][j].tree.bodyIndexY = 8;
					}
					else if (_tile[i][j].grownLevel == 3)
					{
						_tile[i][j].tree.bodyIndexX = 6;
						_tile[i][j].tree.bodyIndexY = 7;
					}
					else if (_tile[i][j].grownLevel == 4)
					{
						_tile[i][j].tree.bodyIndexX = 8;
						_tile[i][j].tree.bodyIndexY = 9;
					}
				}
				else if (_tile[i][j].seedType == SEED_MAPLETREE)
				{
					_tile[i][j].grownLevel += 1;
					if (_tile[i][j].grownLevel == 1)
					{
						_tile[i][j].tree.bodyIndexX = 3;
						_tile[i][j].tree.bodyIndexY = 8;
					}
					else if (_tile[i][j].grownLevel == 2)
					{
						_tile[i][j].tree.bodyIndexX = 4;
						_tile[i][j].tree.bodyIndexY = 8;
					}
					else if (_tile[i][j].grownLevel == 3)
					{
						_tile[i][j].tree.bodyIndexX = 3;
						_tile[i][j].tree.bodyIndexY = 7;
					}
					else if (_tile[i][j].grownLevel == 4)
					{
						_tile[i][j].tree.bodyIndexX = 5;
						_tile[i][j].tree.bodyIndexY = 9;
					}
				}
				else if (_tile[i][j].seedType == SEED_OAKTREE)
				{
					_tile[i][j].grownLevel += 1;
					if (_tile[i][j].grownLevel == 1)
					{
						_tile[i][j].tree.bodyIndexX = 0;
						_tile[i][j].tree.bodyIndexY = 8;
					}
					else if (_tile[i][j].grownLevel == 2)
					{
						_tile[i][j].tree.bodyIndexX = 1;
						_tile[i][j].tree.bodyIndexY = 8;
					}
					else if (_tile[i][j].grownLevel == 3)
					{
						_tile[i][j].tree.bodyIndexX = 0;
						_tile[i][j].tree.bodyIndexY = 7;
					}
					else if (_tile[i][j].grownLevel == 4)
					{
						_tile[i][j].tree.bodyIndexX = 2;
						_tile[i][j].tree.bodyIndexY = 9;
					}
				}
				else
				{
					_tile[i][j].grownLevel += 1;
					_tile[i][j].objFrameX += 1;
					_tile[i - 1][j].ovlFrameX += 1;
				}

				//���ڶ����� Ȯ��
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
	case SEED_PINETREE:
		if (tile.grownLevel == 4) { return true; }
		else { return false; }
		break;
	case SEED_MAPLETREE:
		if (tile.grownLevel == 4) { return true; }
		else { return false; }
		break;
	case SEED_OAKTREE:
		if (tile.grownLevel == 4) { return true; }
		else { return false; }
		break;
	default:
		break;
	}
}

void inGameScene::getItem(tagItem item)
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

void inGameScene::dropFruit(tagTile tile, SEED seedType)
{
	const char* str = nullptr;
	switch (seedType)
	{
	case SEED_NONE:
		break;
	case SEED_PARSNIP:
		str = "�Ľ���";
		break;
	case SEED_CAULIFLOWER:
		str = "�ݸ��ö��";
		break;
	case SEED_GARLIC:
		str = "����";
		break;
	case SEED_RHUBARB:
		str = "��Ȳ";
		break;
	case SEED_TOMATO:
		str = "�丶��";
		break;
	case SEED_HOTPEPPER:
		str = "����";
		break;
	case SEED_RADISH:
		str = "��";
		break;
	case SEED_STARFRUIT:
		str = "��Ÿ�ĸ���";
		break;
	case SEED_EGGPLANT:
		str = "����";
		break;
	case SEED_PUMPKIN:
		str = "ȣ��";
		break;
	case SEED_YAM:
		str = "����";
		break;
	case SEED_BEET:
		str = "��";
		break;
	case SEED_ANCIENTFRUIT:
		str = "������";
		break;
	case SEED_TULIP:
		str = "ƫ��";
		break;
	case SEED_POPPY:
		str = "��ͺ�";
		break;
	case SEED_SUNFLOWER:
		str = "�عٶ��";
		break;
	case SEED_SWEETGEMBERRY:
		str = "���޺�������";
		break;
	case SEED_STRAWBERRY:
		str = "����";
		break;
	case SEED_GRAPE:
		str = "����";
		break;
	case SEED_COFFEEBEAN:
		str = "Ŀ����";
		break;
	case SEED_GREENBEAN:
		str = "�ϵ���";
		break;
	case SEED_POTATO:
		str = "����";
		break;
	case SEED_KALE:
		str = "����";
		break;
	case SEED_MELON:
		str = "���";
		break;
	case SEED_BLUEBERRY:
		str = "��纣��";
		break;
	case SEED_WHEAT:
		str = "��";
		break;
	case SEED_REDCABBAGE:
		str = "�������";
		break;
	case SEED_CORN:
		str = "������";
		break;
	case SEED_ARTICHOKE:
		str = "��Ƽ��ũ";
		break;
	case SEED_BOKCHOY:
		str = "û��ä";
		break;
	case SEED_CRANBERRY:
		str = "ũ������";
		break;
	case SEED_BLUEJAZZ:
		str = "�������";
		break;
	case SEED_SUMMERSPANGLE:
		str = "��������";
		break;
	case SEED_FAIRYROSE:
		str = "�������";
		break;
	case SEED_HOPS:
		str = "ȩ";
		break;
	case SEED_AMARANTH:
		str = "�Ƹ�����";
		break;
	case SEED_CATUS:
		str = "�����忭��";
		break;
	}
	tagItemOnField temp;
	temp.item = ITEMMANAGER->findItem(str);
	temp.item.item_image = IMAGEMANAGER->findImage("����(��)");
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
	if (temp.item.item_kind == ITEM_WOODENFENCE || temp.item.item_kind == ITEM_STONEFENCE)
	{
		temp.item.item_image = IMAGEMANAGER->findImage("�潺(��)");
	}
	else
	{
		temp.item.item_image = IMAGEMANAGER->findImage("����(��)");
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
	//ȭ�� �����ŭ�� üũ
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
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
				if (_tile[i][j].isWet)
				{
					_tile[i][j].wetFrameX = 20;
					_tile[i][j].wetFrameY = 14;
					if (_tile[i][j - 1].isWet) //����
					{
						_tile[i][j].wetFrameX = 21;
						_tile[i][j].wetFrameY = 15;
					}
					if (_tile[i][j + 1].isWet) //������
					{
						_tile[i][j].wetFrameX = 20;
						_tile[i][j].wetFrameY = 15;
					}
					if (_tile[i - 1][j].isWet) //��
					{
						_tile[i][j].wetFrameX = 22;
						_tile[i][j].wetFrameY = 15;
					}
					if (_tile[i + 1][j].isWet) //�Ʒ�
					{
						_tile[i][j].wetFrameX = 22;
						_tile[i][j].wetFrameY = 14;
					}
					if (_tile[i][j - 1].isWet && _tile[i][j + 1].isWet)			//��+��
					{
						_tile[i][j].wetFrameX = 21;
						_tile[i][j].wetFrameY = 22;
					}
					if (_tile[i - 1][j].isWet && _tile[i + 1][j].isWet)			//��+�Ʒ�
					{
						_tile[i][j].wetFrameX = 20;
						_tile[i][j].wetFrameY = 22;
					}
					if ((_tile[i - 1][j].isWet && _tile[i][j - 1].isWet)
						|| (_tile[i - 1][j].isWet
							&& _tile[i][j - 1].isWet
							&& _tile[i - 1][j - 1].isWet))	//��+�� ||  //��+��+�޴밢
					{
						_tile[i][j].wetFrameX = 22;
						_tile[i][j].wetFrameY = 23;
					}
					if ((_tile[i - 1][j].isWet && _tile[i][j + 1].isWet)
						|| (_tile[i - 1][j].isWet
							&& _tile[i][j + 1].isWet
							&& _tile[i + 1][j + 1].isWet))	 //��+�� || ��+��+���밢
					{
						_tile[i][j].wetFrameX = 20;
						_tile[i][j].wetFrameY = 23;
					}
					if ((_tile[i + 1][j].isWet && _tile[i][j - 1].isWet)
						|| (_tile[i + 1][j].isWet
							&& _tile[i][j - 1].isWet
							&& _tile[i + 1][j - 1].isWet))	//�Ʒ�+�� || �Ʒ�+��+�޴밢
					{
						_tile[i][j].wetFrameX = 22;
						_tile[i][j].wetFrameY = 18;
					}
					if ((_tile[i + 1][j].isWet && _tile[i][j + 1].isWet)
						|| (_tile[i + 1][j].isWet
							&& _tile[i][j + 1].isWet
							&& _tile[i + 1][j + 1].isWet))	//�Ʒ�+�� || �Ʒ�+��+���밢
					{
						_tile[i][j].wetFrameX = 20;
						_tile[i][j].wetFrameY = 18;
					}
					if (_tile[i - 1][j].isWet
						&& _tile[i][j - 1].isWet
						&& _tile[i + 1][j].isWet)		//��+��+�Ʒ�
					{
						_tile[i][j].wetFrameX = 22;
						_tile[i][j].wetFrameY = 19;
					}
					if (_tile[i - 1][j].isWet
						&& _tile[i][j + 1].isWet
						&& _tile[i + 1][j].isWet)		//��+��+�Ʒ�
					{
						_tile[i][j].wetFrameX = 20;
						_tile[i][j].wetFrameY = 19;
					}
					if (_tile[i - 1][j].isWet
						&& _tile[i][j - 1].isWet
						&& _tile[i][j + 1].isWet)		//��+��+��
					{
						_tile[i][j].wetFrameX = 21;
						_tile[i][j].wetFrameY = 23;
					}
					if (_tile[i + 1][j].isWet
						&& _tile[i][j - 1].isWet
						&& _tile[i][j + 1].isWet)		//�Ʒ�+��+�� 
					{
						_tile[i][j].wetFrameX = 21;
						_tile[i][j].wetFrameY = 18;
					}
					if ((_tile[i - 1][j].isWet
						&& _tile[i + 1][j].isWet
						&& _tile[i][j - 1].isWet
						&& _tile[i][j + 1].isWet)		//���Ʒ��޿� (4��)
						|| (_tile[i - 1][j].isWet
							&& _tile[i + 1][j].isWet
							&& _tile[i][j - 1].isWet
							&& _tile[i][j + 1].isWet
							&& _tile[i - 1][j - 1].isWet
							&& _tile[i + 1][j - 1].isWet
							&& _tile[i - 1][j + 1].isWet
							&& _tile[i + 1][j + 1].isWet))	//���Ʒ��翷�밢4�� ���	(8��)
					{
						//�⺻ �׸�
						_tile[i][j].wetFrameX = 21;
						_tile[i][j].wetFrameY = 19;
					}
				}
			}
		}
	}
}

void inGameScene::checkFence()
{
	//ȭ�� �����ŭ�� üũ
	for (int i = (float)((float)CAMERAMANAGER->getY() / 16) - 1; i < (float)((float)CAMERAMANAGER->getY() / 16) + (float)(WINSIZEY / 40) + 1; i++)
	{
		for (int j = (float)((float)CAMERAMANAGER->getX() / 16) - 1; j < (float)((float)CAMERAMANAGER->getX() / 16) + (float)(WINSIZEX / 40) + 1; j++)
		{
			if (i - 1 >= 0 && i + 1 <= TILEY - 1 && j - 1 >= 0 && j + 1 <= TILEX - 1)
			{
				if (_tile[i][j].objType == OTY_WOODENFENCE || _tile[i][j].objType == OTY_STONEFENCE)
				{
					if (_tile[i][j].objType == _tile[i - 1][j].objType)	//��
					{
						_tile[i][j].objFrameX = 0;
						_tile[i][j].objFrameY = 3;
					}
					if (_tile[i][j].objType == _tile[i][j - 1].objType)	//��
					{
						_tile[i][j].objFrameX = 2;
						_tile[i][j].objFrameY = 1;
					}
					if (_tile[i][j].objType == _tile[i][j + 1].objType)	//��
					{
						_tile[i][j].objFrameX = 0;
						_tile[i][j].objFrameY = 1;
					}
					if (_tile[i][j].objType == _tile[i][j + 1].objType
						&& _tile[i][j].objType == _tile[i][j - 1].objType)	//����
					{
						_tile[i][j].objFrameX = 1;
						_tile[i][j].objFrameY = 3;
					}
					if (_tile[i][j].objType == _tile[i][j - 1].objType
						&& _tile[i][j].objType == _tile[i - 1][j].objType)	//�»�
					{
						_tile[i][j].objFrameX = 2;
						_tile[i][j].objFrameY = 5;
					}
					if (_tile[i][j].objType == _tile[i][j + 1].objType
						&& _tile[i][j].objType == _tile[i - 1][j].objType)	//���
					{
						_tile[i][j].objFrameX = 0;
						_tile[i][j].objFrameY = 5;
					}
					if (_tile[i][j].objType == _tile[i][j + 1].objType
						&& _tile[i][j].objType == _tile[i][j - 1].objType
						&& _tile[i][j].objType == _tile[i - 1][j].objType)	//�� + �翷
					{
						_tile[i][j].objFrameX = 1;
						_tile[i][j].objFrameY = 5;
					}
				}
				//if (_tile[i][j].objType == OTY_WOODENFENCEDOOR || _tile[i][j].objType == OTY_STONEFENCEDOOR)
				//{
				//	if (_tile[i][j].objType == _tile[i][j + 1].objType) //��
				//	{
				//		_tile[i][j].objFrameX = 0;
				//		_tile[i][j].objFrameY = 14;
				//	}
				//	if (_tile[i][j].objType == _tile[i][j - 1].objType) //��
				//	{
				//		_tile[i][j].objFrameX = 1;
				//		_tile[i][j].objFrameY = 17;
				//	}
				//	if (_tile[i][j].objType == _tile[i - 1][j].objType) //��
				//	{
				//		_tile[i][j].objFrameX = 0;
				//		_tile[i][j].objFrameY = 11;
				//	}
				//	if (_tile[i][j].objType == _tile[i + 1][j].objType) //�Ʒ�
				//	{
				//		_tile[i][j].objFrameX = 0;
				//		_tile[i][j].objFrameY = 10;
				//	}
				//}
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
			if (_tile[i][j].obj != OBJ_NONE || _tile[i][j].terrain == TR_HACKED
				|| (i == PLAYER->getCurrentY() && j == PLAYER->getCurrentX())) { continue; }
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

TERRAIN inGameScene::terrainSelect(int frameX, int frameY)
{
	if ((frameX == 1 && frameY == 1) || (frameX == 7 && frameY == 0)
		|| ((frameX == 1 || frameX == 2) && frameY == 3) || (frameX == 3 && frameY == 0)
		|| (frameX == 5 && frameY == 0) || (frameX == 7 && frameY == 1)
		|| (frameX == 6 && frameY == 2) || (frameX == 1 && frameY == 1)
		|| (frameX == 0 && (frameY >= 15 && frameY <= 17)))
	{
		return TR_SOIL;
	}
	//��
	if ((frameX == 7 || frameX == 8 || frameX == 9 || frameX == 10) && frameY == 6)
	{
		return TR_WATER;
	}
	//������
	if ((frameX == 20 && frameY == 12) || (frameX == 20 && frameY == 14)
		|| (frameX == 21 && frameY == 13) || (frameX == 20 && frameY == 13)
		|| (frameX == 22 && frameY == 13) || (frameX == 22 && frameY == 12)
		|| (frameX == 21 && frameY == 20) || (frameX == 20 && frameY == 20)
		|| (frameX == 22 && frameY == 21) || (frameX == 20 && frameY == 21)
		|| (frameX == 22 && frameY == 16) || (frameX == 20 && frameY == 16)
		|| (frameX == 22 && frameY == 17) || (frameX == 20 && frameY == 17)
		|| (frameX == 21 && frameY == 21) || (frameX == 21 && frameY == 16)
		|| (frameX == 21 && frameY == 17))
	{
		return TR_HACKED;
	}
	//��Ÿ
	return TR_GROUND;
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
		return TRUE;
	}
	return FALSE;
}
