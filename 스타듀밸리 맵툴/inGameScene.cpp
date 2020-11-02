#include "stdafx.h"
#include "inGameScene.h"

inGameScene::inGameScene()
{
	loadCount = PLAYER->getLoadCount();  //���� �ε�� �ʱ�ȭ ���� ī��Ʈ
}

HRESULT inGameScene::init()
{
	CAMERAMANAGER->init(TILEX * TILESIZE, TILEY * TILESIZE, 30 * 16, 15 * 16);
	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());

	isShopOpen = false;
	_isTalk = false;
	_isTalked = false;
	if (loadCount == 0) // ���� �ѹ��� �ʱ�ȭ �����..
	{
		load();
		setTileRect();

		changeSeason(SPRING);

		isShowRect = false;

		checkPlayerTile();
		PLAYER->setLoadCount(1);

		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				_tile[i][j].portal = PT_NONE;
			}
		}
		_tile[29][23].portal = PT_HOUSE;
		_tile[27][39].portal = PT_BARN;
		//_tile[0][i + 14].portal = PT_CHICKENHOUSE;
		_tile[12][41].portal = PT_SHOP;
		_tile[12][40].portal = PT_SHOP;
		_tile[3][6].portal = PT_MINE;
		_tile[12][12].portal = PT_TOWER;
		_tile[12][11].portal = PT_TOWER;

		isSprinkled = false;

		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				_tile[i][j].terrain = terrainSelect(_tile[i][j].terrainFrameX, _tile[i][j].terrainFrameY);
			}
		}
	}

	if (SOUNDMANAGER->isPlaySound("��������"))
	{
		SOUNDMANAGER->stop("��������");
	}
	if (SOUNDMANAGER->isPlaySound("bugCave"))
	{
		SOUNDMANAGER->stop("bugCave");
	}
	if (SOUNDMANAGER->isPlaySound("town"))
	{
		SOUNDMANAGER->stop("town");
	}

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			PLAYER->saveTile(i, j, _tile[i][j]);
		}
	}

	if (PLAYER->getDate() == 12)
	{
		setEventGround();
	}
	else if (PLAYER->getDate() == 17)
	{
		resetOriginalGround();
	}
	script_count = 0;
	tagScript temp_script[20];
	temp_script[0] = {IMAGEMANAGER->findImage("�Ҿƹ�������"),"�Ҿƹ���","���� �Ծ�?" };
	temp_script[1] = { IMAGEMANAGER->findImage(""),"�÷��̾�","�Ҿƹ��� ������ �������ó׿�." };
	temp_script[2] = { IMAGEMANAGER->findImage("�Ҿƹ����⺻"),"�Ҿƹ���","���� �׻� �׷��� �� ~ \n�׳����� ���⿡�� ���е��� �����Ŷ�鼭\n �Ǹ����� �Ծ� ?" };
	temp_script[3] = { IMAGEMANAGER->findImage(""),"�÷��̾�","��?" };
	temp_script[4] = { IMAGEMANAGER->findImage("�Ҿƹ����⺻"),"�Ҿƹ���","���� ��� ���� �غ� �ȵƳ� ~ \n�ѹ��� �˷����״� �� �����." };
	temp_script[5] = { IMAGEMANAGER->findImage(""),"�÷��̾�","�Ҿƹ������� ���Ѱ� ȣ�̸� �̴ּ�." };
	temp_script[6] = { IMAGEMANAGER->findImage("�Ҿƹ����⺻"),"�Ҿƹ���","ȣ�� ����? �װɷ� �� ����. �׸��� �� ������ ���̿� ~" };
	temp_script[7] = { IMAGEMANAGER->findImage(""),"�÷��̾�","�Ҿƹ������� ���Ѹ����� �̴ּ�." };
	temp_script[8] = { IMAGEMANAGER->findImage("�Ҿƹ����⺻"),"�Ҿƹ���","�� �ɰ� ���� ���ѷ� ~" };
	temp_script[9] = { IMAGEMANAGER->findImage("�Ҿƹ����⺻"),"�Ҿƹ���","���� �Ѹ��ٺ��� �۹��� �ڶ��ſ�. \n�� �ڶ�� ���ؾ߰ھ�. ��Ȯ�ؾ߰���?" };
	temp_script[10] = { IMAGEMANAGER->findImage(""),"�÷��̾�","�Ҿƹ������� ���� �̴ּ�." };
	temp_script[11] = { IMAGEMANAGER->findImage("�Ҿƹ����⺻"),"�Ҿƹ���","���� ����ϸ� ��. �׸��� ���� �۹��� ������ �Ⱦƹ���. \n�׷� ���� ���ž�." };
	temp_script[12] = { IMAGEMANAGER->findImage("�Ҿƹ����⺻"),"�Ҿƹ���","�ٸ� �۹��� Ű������ ������ �������� �����ؼ� �ɾ�. \n��ȭ�ñ�� �� �ٸ��ϱ� �����ϰ�." };
	temp_script[13] = { IMAGEMANAGER->findImage(""),"�÷��̾�","�Ҿƹ������� ������ �̴ּ�." };
	temp_script[14] = { IMAGEMANAGER->findImage("�Ҿƹ����⺻"),"�Ҿƹ���","�ֺ��� ���� ����? ������ �� �� �־� ~" };
	temp_script[14] = { IMAGEMANAGER->findImage("�Ҿƹ����⺻"),"�Ҿƹ���","�㿡 �����ؼ� ������ ���� ���� �ڸ鼭 ���ؾ� ��.\n�׷��� ���� �������� �Ͼ ��ħ���� ������." };
	temp_script[15] = { IMAGEMANAGER->findImage(""),"�÷��̾�","�����ؿ� �Ҿƹ���!" };
	temp_script[16] = { IMAGEMANAGER->findImage("�Ҿƹ����⺻"),"�Ҿƹ���","���������� �������� �Խ����� �ְŵ�~\n���� �Ѵ� ������ �����Ǿ� �����ϱ� ƴƴ�� ����� ~~" };

	for (int i = 0; i < 17; i++)
	{
		script.push_back(temp_script[i]);
	}
	return S_OK;
}

void inGameScene::release()
{
}

void inGameScene::update()
{
	std::cout << MouseIndexX << "\t" << MouseIndexY << endl;

	if (PLAYER->getstart())
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			script_count++;
			if (script_count == 5)
			{
				for (int i = 0; i < INVENMAX; i++)
				{
					if ((*PLAYER->getInven())[i].item_image == NULL)
					{
						PLAYER->setInvenItem(i, ITEMMANAGER->findItem("ȣ��"));
						PLAYER->setInvenItem(i+1, ITEMMANAGER->findItemByKind(ITEM_SEED,2));
						break;
					}
				}
			}
			if (script_count == 7)
			{
				for (int i = 0; i < INVENMAX; i++)
				{
					if ((*PLAYER->getInven())[i].item_image == NULL)
					{
						PLAYER->setInvenItem(i, ITEMMANAGER->findItem("������"));
						break;
					}
				}
			}
			if (script_count == 10)
			{
				for (int i = 0; i < INVENMAX; i++)
				{
					if ((*PLAYER->getInven())[i].item_image == NULL)
					{
						PLAYER->setInvenItem(i, ITEMMANAGER->findItem("��"));
						break;
					}
				}
			}
			if (script_count == 13)
			{
				for (int i = 0; i < INVENMAX; i++)
				{
					if ((*PLAYER->getInven())[i].item_image == NULL)
					{
						PLAYER->setInvenItem(i, ITEMMANAGER->findItem("����"));
						break;
					}
				}
			}
			if (script_count > 16)
			{
				_isFirstTalk = false;
				PLAYER->setstart(false);
				SWITCHMANAGER->changeScene("����ȭ��");
				SWITCHMANAGER->startFade(820.0f, 860.0f);
			}
		}
	}
	if (_isTalk)
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			_isTalk = false;
		}
	}
	loadCount = PLAYER->getLoadCount();
	isSprinkled = PLAYER->getIsSprinkled();
	sprinklerWork();
	if (!SOUNDMANAGER->isPlaySound("����"))
	{
		SOUNDMANAGER->play("����", 0.05f);
	}
	if (!SOUNDMANAGER->isPlaySound("springDay") && PLAYER->getHour() < 13)
	{
		SOUNDMANAGER->play("springDay", 0.3f);
	}
	if (!SOUNDMANAGER->isPlaySound("night") && (PLAYER->getHour() > 21 || PLAYER->getHour() < 5))
	{
		SOUNDMANAGER->play("night", 0.3f);
	}

	PLAYER->update();
	//cout << "player is met : " << PLAYER->getIsMet() << endl;
	//skillSelect();

	checkPlayerTile();

	if (PLAYER->getState() == STAND || PLAYER->getState() == RUN||PLAYER->getState()==CARRY||PLAYER->getState()==CARRYSTAND)
	{
		if (!PLAYER->getstart() && !_isTalk)
		{
			playerMove();
		}
	}
	if (!_isTalk)
	{
		playerInteraction();
	}

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
	if (INPUT->GetKeyDown(VK_F7))
	{
		makeCropGrow();
	}

	moveScene();

	if (PLAYER->getEnergy() < -10)
	{
		shareTileData();
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

	for (int i = 0; i < _vItemOnField.size(); i++)
	{
		_vItemOnField[i].item.item_image->frameRender(CAMERAMANAGER->getMemDC(), _vItemOnField[i].rc.left, _vItemOnField[i].rc.top, _vItemOnField[i].item.indexX, _vItemOnField[i].item.indexY);
	}

	//skillClick();

	//����Ʈ ����
	EFFECTMANAGER->render(CAMERAMANAGER->getMemDC());
	
	//FrameRect(CAMERAMANAGER->getMemDC(), _tile[MouseIndexY][MouseIndexX].rc, RGB(255, 50, 30));
	IMAGEMANAGER->frameRender("�Ҿƹ���", CAMERAMANAGER->getMemDC(), 350, 472,0,0);
	CAMERAMANAGER->render(getMemDC());

	PLAYER->playerStatusRender(getMemDC());
	if (isShowCalender)
	{
		IMAGEMANAGER->render("�޷�", getMemDC(), WINSIZEX / 2 - 300, WINSIZEY / 2 - 200);
	}

	if (_isTalk)
	{
		IMAGEMANAGER->render("�÷��̾���â", getMemDC(), 80, 275);
		RECT tempRC = RectMake(120, 320, 800, 300);
		const char* tempText = "�� �� ���� ����� ��������.\nƯ���� �ǹ��� ���� �ִ°ɱ�?";
		DrawText(getMemDC(),tempText,strlen(tempText),&tempRC,NULL);
	}

	if (PLAYER->getstart())
	{
		if (script[script_count].name == "�Ҿƹ���")
		{
			IMAGEMANAGER->render("��ȭâ", getMemDC(), 80, 275);
			script[script_count].image->render(getMemDC(), 735, 310);
		}
		else IMAGEMANAGER->render("�÷��̾���â", getMemDC(), 80, 275);
		RECT tempRC = RectMake(120, 320, 800, 300);
		DrawText(getMemDC(), script[script_count].script, strlen(script[script_count].script), &tempRC, NULL);
	}
}

void inGameScene::load()
{
	//DialogBox(_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), _hWnd, inGameScene::DlgProc);

	HANDLE file;
	DWORD read;
	//TCHAR saveName[MAX_PATH];
	if (PLAYER->getIsNewGame())
	{
		//sprintf(saveName, "save/newGame.map");
		file = CreateFile("save/newGame1.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		PLAYER->setIsNewGame(false);
	}
	else
	{
		//sprintf(saveName, "save/tomato.map");
		file = CreateFile("save/tomato.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	
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
	for (int i = (float)((float)CAMERAMANAGER->getY() / 16) - 1; i < currentIndexY + 1; i++)
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
	for (int i = currentIndexY + 1; i < (float)((float)CAMERAMANAGER->getY() / 16) + (float)(WINSIZEY / 40) + 7; i++)
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
				if (_tile[i][j].objType == OTY_SHOP)
				{
					for (int y = 6; y < 10; y++)
					{
						if (i - y >= 0)
						{
							IMAGEMANAGER->frameRender("�ǹ�", CAMERAMANAGER->getMemDC(), _tile[i - y][j].rc.left, _tile[i - y][j].rc.top,
								_tile[i][j].objFrameX, _tile[i][j].objFrameY - y);
						}
					}
					IMAGEMANAGER->frameRender("�ǹ�", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
						_tile[i][j].objFrameX, _tile[i][j].objFrameY);
				}
				else if (_tile[i][j].objType == OTY_TOWER && _tile[i][j].objType != _tile[i - 1][j].objType)
				{
					for (int y = 1; y < 10; y++)
					{
						if (i - y >= 0)
						{
							IMAGEMANAGER->frameRender("�ǹ�", CAMERAMANAGER->getMemDC(), _tile[i - y][j].rc.left, _tile[i - y][j].rc.top,
								_tile[i][j].objFrameX, _tile[i][j].objFrameY - y);
						}
					}
					IMAGEMANAGER->frameRender("�ǹ�", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
						_tile[i][j].objFrameX, _tile[i][j].objFrameY);
				}
				else if (_tile[i][j].objType == OTY_HOUSE && _tile[i][j].objType != _tile[i - 1][j].objType)
				{
					for (int y = 1; y < 4; y++)
					{
						if (i - y >= 0)
						{
							IMAGEMANAGER->frameRender("�ǹ�", CAMERAMANAGER->getMemDC(), _tile[i - y][j].rc.left, _tile[i - y][j].rc.top,
								_tile[i][j].objFrameX, _tile[i][j].objFrameY - y);
						}
					}
					IMAGEMANAGER->frameRender("�ǹ�", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
						_tile[i][j].objFrameX, _tile[i][j].objFrameY);
				}
				else if (_tile[i][j].objType == OTY_WELL && _tile[i][j].objType != _tile[i - 1][j].objType)
				{
					for (int y = 1; y < 4; y++)
					{
						if (i - y >= 0)
						{
							IMAGEMANAGER->frameRender("�ǹ�", CAMERAMANAGER->getMemDC(), _tile[i - y][j].rc.left, _tile[i - y][j].rc.top,
								_tile[i][j].objFrameX, _tile[i][j].objFrameY - y);
						}
					}
					IMAGEMANAGER->frameRender("�ǹ�", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
						_tile[i][j].objFrameX, _tile[i][j].objFrameY);
				}
				else if (_tile[i][j].objType == OTY_BARN && _tile[i][j].objType != _tile[i - 1][j].objType)
				{
					for (int y = 1; y < 5; y++)
					{
						if (i - y >= 0)
						{
							IMAGEMANAGER->frameRender("�ǹ�", CAMERAMANAGER->getMemDC(), _tile[i - y][j].rc.left, _tile[i - y][j].rc.top,
								_tile[i][j].objFrameX, _tile[i][j].objFrameY - y);
						}
					}
					IMAGEMANAGER->frameRender("�ǹ�", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
						_tile[i][j].objFrameX, _tile[i][j].objFrameY);
				}
				else
				{
					IMAGEMANAGER->frameRender("�ǹ�", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
						_tile[i][j].objFrameX, _tile[i][j].objFrameY);
				}
				
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
			else if (_tile[i][j].objType == OTY_SPRINKLER1
				|| _tile[i][j].objType == OTY_SPRINKLER2
				|| _tile[i][j].objType == OTY_SPRINKLER3)
			{
				IMAGEMANAGER->frameRender("������Ŭ��", CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i][j].objFrameX, _tile[i][j].objFrameY);
			}
			else if (_tile[i][j].objType == OTY_WOODENFENCE)
			{
				IMAGEMANAGER->findImage("�����潺")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i][j].objFrameX, _tile[i][j].objFrameY);
				IMAGEMANAGER->findImage("�����潺")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 1][j].rc.left, _tile[i - 1][j].rc.top,
					_tile[i][j].objFrameX, _tile[i][j].objFrameY - 1);
			}
			else if (_tile[i][j].objType == OTY_STONEFENCE)
			{
				IMAGEMANAGER->findImage("���潺")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i][j].objFrameX, _tile[i][j].objFrameY);
				IMAGEMANAGER->findImage("���潺")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 1][j].rc.left, _tile[i - 1][j].rc.top,
					_tile[i][j].objFrameX, _tile[i][j].objFrameY - 1);
			}
			else if (_tile[i][j].obj == OBJ_EQUIPMENT)
			{
				IMAGEMANAGER->findImage("���������۽���")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
					_tile[i][j].objFrameX, _tile[i][j].objFrameY);
				
				if (_tile[i][j].objType==OTY_BOX) //����
				{
					IMAGEMANAGER->findImage("���������۽���")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
						0,0);
				}
				else if (_tile[i][j].objType==OTY_BLASTFURNACE) //�뱤��
				{
					IMAGEMANAGER->findImage("���������۽���")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i][j].rc.left, _tile[i][j].rc.top,
						1, 0);
				}
				
				//for(int i=0;i<9;i++)
				//{
				//	if (_tile[i][j].objFrameX == 3 && _tile[i][j].objFrameY == 1) //����ƺ�
				//	{
				//		IMAGEMANAGER->findImage("���������۽���")->frameRender(CAMERAMANAGER->getMemDC(), _tile[i - 1][j].rc.left, _tile[i - 1][j].rc.top,
				//			3, 0);
				//	}

				//}


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
			if (_tile[i + 1][j].objType == OTY_CROP)
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
	if (!PLAYER->getInventoryMove() && !isShowCalender)
	{
		if (_tile[currentIndexY][currentIndexX].terrain == TR_GROUND)
		{
			if (SOUNDMANAGER->isPlaySound("movesoil"))
			{
				SOUNDMANAGER->stop("movesoil");
			}
			if (!SOUNDMANAGER->isPlaySound("movegrass"))
			{
				SOUNDMANAGER->play("movegrass", 0.3f);
			}
		}
		else if (_tile[currentIndexY][currentIndexX].terrain == TR_SOIL)
		{
			if (SOUNDMANAGER->isPlaySound("movegrass"))
			{
				SOUNDMANAGER->stop("movegrass");
			}
			if (!SOUNDMANAGER->isPlaySound("movesoil"))
			{
				SOUNDMANAGER->play("movesoil", 0.3f);
			}
		}
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
						&& _tile[rightIndexY][rightIndexX].seedType != SEED_GRAPE)
					|| (_tile[rightIndexY][rightIndexX].objType == OTY_TREE
						&& !_tile[rightIndexY][rightIndexX].isFullyGrown
						&& _tile[rightIndexY][rightIndexX].grownLevel == 0)
					|| (_tile[rightIndexY][rightIndexX].obj == OBJ_BUILDING 
						&& _tile[rightIndexY][rightIndexX].objType == OTY_HOUSE
						&& ((_tile[rightIndexY][rightIndexX].objFrameX == 13 
							|| _tile[rightIndexY][rightIndexX].objFrameX == 14 
							|| _tile[rightIndexY][rightIndexX].objFrameX == 15)
							&& 
							(_tile[rightIndexY][rightIndexX].objFrameY == 8
							|| _tile[rightIndexY][rightIndexX].objFrameY == 7
							|| _tile[rightIndexY][rightIndexX].objFrameY == 9)
							)) 
							)
				{
					PLAYER->setDirection(RIGHT);

					for (int i = 1; i < 10; i++)
					{
						if (PLAYER->getCurrentInven()->item_kind == ITEM_SEED || PLAYER->getCurrentInven()->item_kind == ITEM_BOX ||
							PLAYER->getCurrentInven()->item_kind == ITEM_BLASTFURNACE || PLAYER->getCurrentInven()->scarecrowKind == i)
						{
							PLAYER->setState(CARRY);
						}
						else
						{
							PLAYER->setState(RUN);
						}
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
						&& _tile[leftIndexY][leftIndexX].seedType != SEED_GRAPE)
					|| (_tile[leftIndexY][leftIndexX].objType == OTY_TREE
						&& !_tile[leftIndexY][leftIndexX].isFullyGrown
						&& _tile[leftIndexY][leftIndexX].grownLevel == 0)
					|| (_tile[leftIndexY][leftIndexX].obj == OBJ_BUILDING
						&& _tile[leftIndexY][leftIndexX].objType == OTY_HOUSE
						&& ((_tile[leftIndexY][leftIndexX].objFrameX == 13
							|| _tile[leftIndexY][leftIndexX].objFrameX == 14
							|| _tile[leftIndexY][leftIndexX].objFrameX == 15)
							&&
							(_tile[leftIndexY][leftIndexX].objFrameY == 8
								|| _tile[leftIndexY][leftIndexX].objFrameY == 7
								|| _tile[leftIndexY][leftIndexX].objFrameY == 9)) 
								))
				{
					PLAYER->setDirection(LEFT);

					for (int i = 1; i < 10; i++)
					{
						if (PLAYER->getCurrentInven()->item_kind == ITEM_SEED || PLAYER->getCurrentInven()->item_kind == ITEM_BOX ||
							PLAYER->getCurrentInven()->item_kind == ITEM_BLASTFURNACE || PLAYER->getCurrentInven()->scarecrowKind == i)
						{
							PLAYER->setState(CARRY);
						}
						else
						{
							PLAYER->setState(RUN);
						}
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
						&& _tile[upIndexY][upIndexX].seedType != SEED_GRAPE) 
					|| (_tile[upIndexY][upIndexX].objType == OTY_TREE
							&& !_tile[upIndexY][upIndexX].isFullyGrown
						&& _tile[upIndexY][upIndexX].grownLevel == 0)
					|| (_tile[upIndexY][upIndexX].obj == OBJ_BUILDING
						&& _tile[upIndexY][upIndexX].objType == OTY_HOUSE
						&& ((_tile[upIndexY][upIndexX].objFrameX == 13
							|| _tile[upIndexY][upIndexX].objFrameX == 14
							|| _tile[upIndexY][upIndexX].objFrameX == 15)
							&&
							(_tile[upIndexY][upIndexX].objFrameY == 8
								|| _tile[upIndexY][upIndexX].objFrameY == 7
								|| _tile[upIndexY][upIndexX].objFrameY == 9)))
					|| (upIndexX == 22 && (upIndexY == 30 || upIndexY == 31)))
				{
					PLAYER->setDirection(UP);

					for (int i = 1; i < 10; i++)
					{
						if (PLAYER->getCurrentInven()->item_kind == ITEM_SEED || PLAYER->getCurrentInven()->item_kind == ITEM_BOX ||
							PLAYER->getCurrentInven()->item_kind == ITEM_BLASTFURNACE || PLAYER->getCurrentInven()->scarecrowKind == i)
						{
							PLAYER->setState(CARRY);
						}
						else
						{
							PLAYER->setState(RUN);
						}
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
						&& _tile[downIndexY][downIndexX].seedType != SEED_GRAPE)
					|| (_tile[downIndexY][downIndexX].objType == OTY_TREE 
						&& !_tile[downIndexY][downIndexX].isFullyGrown
						&& _tile[downIndexY][downIndexX].grownLevel == 0)
					|| (_tile[downIndexY][downIndexX].obj == OBJ_BUILDING
						&& _tile[downIndexY][downIndexX].objType == OTY_HOUSE
						&& ((_tile[downIndexY][downIndexX].objFrameX == 13
							|| _tile[downIndexY][downIndexX].objFrameX == 14
							|| _tile[downIndexY][downIndexX].objFrameX == 15)
							&&
							(_tile[downIndexY][downIndexX].objFrameY == 8
								|| _tile[downIndexY][downIndexX].objFrameY == 7
								|| _tile[downIndexY][downIndexX].objFrameY == 9)))
					|| (downIndexX == 22 && (downIndexY == 30 || downIndexY == 31)))
				{
					PLAYER->setDirection(DOWN);

					for (int i = 1; i < 10; i++)
					{
						if (PLAYER->getCurrentInven()->item_kind == ITEM_SEED || PLAYER->getCurrentInven()->item_kind == ITEM_BOX ||
							PLAYER->getCurrentInven()->item_kind == ITEM_BLASTFURNACE || PLAYER->getCurrentInven()->scarecrowKind == i)
						{
							PLAYER->setState(CARRY);
						}
						else
						{
							PLAYER->setState(RUN);
						}
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
}

void inGameScene::moveScene()
{
	if (_tile[currentIndexY][currentIndexX].portal == PT_BARN)
	{
		shareTileData();
		SOUNDMANAGER->play("doorOpen", 0.2f);
		SWITCHMANAGER->changeScene("�ǹ���ȭ��");
		SWITCHMANAGER->startFade(780.0f, 890.0f);
	}
	else if (_tile[currentIndexY][currentIndexX].portal == PT_SHOP)
	{
		shareTileData();
		SOUNDMANAGER->play("doorOpen", 0.2f);
		isShopOpen = true;
		SWITCHMANAGER->changeScene("������");
		SWITCHMANAGER->startFade(278.0f, 326.0f);
	}
	else if (_tile[currentIndexY][currentIndexX].portal == PT_HOUSE)
	{
		//������ �Ѿ�� Ÿ�� ���� �Ѱ���
		shareTileData();
		SOUNDMANAGER->play("doorOpen", 0.2f);
		SWITCHMANAGER->changeScene("����ȭ��");
		SWITCHMANAGER->startFade(762.0f, 887.0f);
	}
	else if (_tile[currentIndexY][currentIndexX].portal == PT_MINE)
	{
		if (PLAYER->getIsMet())
		{
			//������ �Ѿ�� Ÿ�� ���� �Ѱ���
			shareTileData();
			SWITCHMANAGER->changeScene("����ȭ��");
			SWITCHMANAGER->startFade(390.0f, 166.0f);
		}
		else
		{
			if (_isTalked == false)
			{
				_isTalk = true;
				_isTalked = true;
			}
		}
	}
	else if (_tile[currentIndexY][currentIndexX].portal == PT_TOWER)
	{
		//������ �Ѿ�� Ÿ�� ���� �Ѱ���
		SOUNDMANAGER->play("doorOpen", 0.2f);
		SWITCHMANAGER->changeScene("������Ÿ��ȭ��");
		SWITCHMANAGER->startFade(360.0f, 265.0f);
	}
	else _isTalked = false;
}

void inGameScene::shareTileData()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			PLAYER->saveTile(i, j, _tile[i][j]);
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

	for (int i = 1; i < 10; i++)
	{
		if (PLAYER->getCurrentInven()->item_kind == ITEM_SEED || PLAYER->getCurrentInven()->item_kind == ITEM_BOX ||
			PLAYER->getCurrentInven()->scarecrowKind == i || PLAYER->getCurrentInven()->item_kind == ITEM_BLASTFURNACE)
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
				//���� �Ա�
				if (PLAYER->getCurrentInven()->item_kind == ITEM_FRUIT)
				{
					if (PLAYER->getCurrentInven()->seedKind != SEED_HOPS
						&& PLAYER->getCurrentInven()->seedKind != SEED_WHEAT
						&& PLAYER->getCurrentInven()->seedKind != SEED_POPPY
						&& PLAYER->getCurrentInven()->seedKind != SEED_SUMMERSPANGLE)
					{
						PLAYER->setDirection(DOWN);
						eatFruit();
					}
				}

				//���۾����� ��ġ
				for (int i = 1; i < 10; i++)
				{
					if (PLAYER->getCurrentInven()->item_kind == ITEM_BOX || PLAYER->getCurrentInven()->item_kind == ITEM_BLASTFURNACE ||
						PLAYER->getCurrentInven()->scarecrowKind==i)
					{
						setEquipment();
					}
				}


				//�潺 ��ġ
				if (PLAYER->getCurrentInven()->item_kind == ITEM_WOODENFENCE || PLAYER->getCurrentInven()->item_kind == ITEM_STONEFENCE)
				{

					setFence();
				}

				//���Ѹ���
				if (PLAYER->getCurrentInven()->toolKind == TOOL_KETTLE && _tile[MouseIndexY][MouseIndexX].terrain == TR_HACKED)
				{
					waterGround();
				}
				//��ä���
				if (PLAYER->getCurrentInven()->toolKind == TOOL_KETTLE && _tile[MouseIndexY][MouseIndexX].objType == 17)
				{
					fillWater();
				}
			}

			//������Ŭ�� ��ġ
			setSprinkler();	

			//�޷�â ����
			if (MouseIndexX == 38 && (MouseIndexY == 10 || MouseIndexY == 11))
			{
				isShowCalender = true;
			}

			if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
				|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
				|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1)
					&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1))) //�밢�� 4 Ÿ���϶�
			{
				if (_tile[MouseIndexY][MouseIndexX].objType == OTY_BOX)
				{
					//if (!PLAYER->getIsShowInventory())
					//{
						if (!PLAYER->getIsShowInventory())
						{
							PLAYER->openPlayerStorageCover();
						}
					//}

				}
				else if (_tile[MouseIndexY][MouseIndexX].objType == OTY_BLASTFURNACE)
				{

					PLAYER->getInventory()->getInventoryCraft()->blastFurnace();
				}
			}
		}
		if (isShowCalender)
		{
			if (INPUT->GetKeyDown(VK_ESCAPE))
			{
				isShowCalender = false;
			}
		}
	}

	if (INPUT->GetKeyDown(VK_RBUTTON))
	{
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1)
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1))) //�밢�� 4 Ÿ���϶�
		{
			if (_tile[MouseIndexY][MouseIndexX].objType == OTY_CROP)
			{
				//��Ȯ
				harvest();
				checkHacked();
			}
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
			SOUNDMANAGER->play("HOE", 0.2f);
			_tile[MouseIndexY][MouseIndexX].terrain = TR_HACKED;
			_tile[MouseIndexY][MouseIndexX].terrainFrameX = 20;
			_tile[MouseIndexY][MouseIndexX].terrainFrameY = 12;

			if (PLAYER->getEnergy() > -20)
			{
				PLAYER->setEnergy(PLAYER->getDamage());
			}

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
		//�ڸ� �� �ִ� ����
		if (_tile[MouseIndexY][MouseIndexX].objType == OTY_TREE)
		{
			if (_tile[MouseIndexY][MouseIndexX].obj == OBJ_DESTRUCTIBLE && _tile[MouseIndexY][MouseIndexX].isFullyGrown)
			{
				SOUNDMANAGER->play("�������", 0.2f);
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
								dropFruit(_tile[MouseIndexY][MouseIndexX], ITEM_SEED, SEED_PINETREE);
							}
							if (_tile[MouseIndexY][MouseIndexX].tree.treeType == TREE_MAPLE)
							{
								dropFruit(_tile[MouseIndexY][MouseIndexX], ITEM_SEED, SEED_MAPLETREE);
							}
							if (_tile[MouseIndexY][MouseIndexX].tree.treeType == TREE_OAK)
							{
								dropFruit(_tile[MouseIndexY][MouseIndexX], ITEM_SEED, SEED_OAKTREE);
							}
						}
						dropItem(_tile[MouseIndexY][MouseIndexX], ITEM_DEBRIS, 4);
					}
					_tile[MouseIndexY][MouseIndexX].objType = OTY_TREETRUNK;
					if (_tile[MouseIndexY][MouseIndexX].tree.treeType == TREE_PINE)
					{
						_tile[MouseIndexY][MouseIndexX].tree.bodyIndexX = 8;
						_tile[MouseIndexY][MouseIndexX].tree.bodyIndexY = 7;
						SOUNDMANAGER->play("removeTree", 0.05f);
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
						SOUNDMANAGER->play("removeTree", 0.05f);
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
						SOUNDMANAGER->play("removeTree", 0.05f);
						EFFECTMANAGER->treeCol(
							"������",
							(_tile[MouseIndexY][MouseIndexX].rc.left + (_tile[MouseIndexY][MouseIndexX].rc.right - _tile[MouseIndexY][MouseIndexX].rc.left) / 2),
							(_tile[MouseIndexY][MouseIndexX].rc.top + (_tile[MouseIndexY][MouseIndexX].rc.bottom - _tile[MouseIndexY][MouseIndexX].rc.top) / 2)
						);
					}
					_tile[MouseIndexY][MouseIndexX].tree.hp = 3;
				}
			}
			if (PLAYER->getEnergy() > -20)
			{
				PLAYER->setEnergy(PLAYER->getDamage());
			}
		}

		//���� ��ġ
		if (_tile[MouseIndexY][MouseIndexX].objType == OTY_TREETRUNK)
		{
			SOUNDMANAGER->play("�������", 0.2f);
			if (_tile[MouseIndexY][MouseIndexX].tree.hp > 0)
			{
				_tile[MouseIndexY][MouseIndexX].tree.hp -= 1;
			}
			else if (_tile[MouseIndexY][MouseIndexX].tree.hp == 0)
			{
				for (int i = 0; i < 3; i++)
				{
					dropItem(_tile[MouseIndexY][MouseIndexX], ITEM_DEBRIS, 4);
				}

				_tile[MouseIndexY][MouseIndexX].seedType = SEED_NONE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_NONE;
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
			}
			if (PLAYER->getEnergy() > -20)
			{
				PLAYER->setEnergy(PLAYER->getDamage());
			}
		}

		//��������
		if (_tile[MouseIndexY][MouseIndexX].objType == OTY_BRANCH)
		{
			SOUNDMANAGER->play("�������", 0.2f);
			dropItem(_tile[MouseIndexY][MouseIndexX], ITEM_DEBRIS, 4);
			_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
			_tile[MouseIndexY][MouseIndexX].objType = OTY_NONE;

			if (PLAYER->getEnergy() > -20)
			{
				PLAYER->setEnergy(PLAYER->getDamage());
			}
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
			SOUNDMANAGER->play("removeRock", 0.2f);
			dropItem(_tile[MouseIndexY][MouseIndexX], ITEM_DEBRIS, 3);
			_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
			_tile[MouseIndexY][MouseIndexX].objType = OTY_NONE;

			if (PLAYER->getEnergy() > -20)
			{
				PLAYER->setEnergy(PLAYER->getDamage());
			}
		}
		if (_tile[MouseIndexY][MouseIndexX].objType == OTY_WOODENFENCE)
		{
			SOUNDMANAGER->play("removeRock", 0.2f);
			dropItem(_tile[MouseIndexY][MouseIndexX], ITEM_WOODENFENCE, 0);
			_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
			_tile[MouseIndexY][MouseIndexX].objType = OTY_NONE;

			if (PLAYER->getEnergy() > -20)
			{
				PLAYER->setEnergy(PLAYER->getDamage());
			}
		}
		if (_tile[MouseIndexY][MouseIndexX].objType == OTY_STONEFENCE)
		{
			SOUNDMANAGER->play("removeRock", 0.2f);
			dropItem(_tile[MouseIndexY][MouseIndexX], ITEM_STONEFENCE, 1);
			_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
			_tile[MouseIndexY][MouseIndexX].objType = OTY_NONE;

			if (PLAYER->getEnergy() > -20)
			{
				PLAYER->setEnergy(PLAYER->getDamage());
			}
		}
		if (_tile[MouseIndexY][MouseIndexX].objType == OTY_CROP || _tile[MouseIndexY][MouseIndexX].terrain == TR_HACKED)
		{
			if (PLAYER->getEnergy() > 0)
			{
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_NONE;
				_tile[MouseIndexY][MouseIndexX].terrain = TR_SOIL;
				_tile[MouseIndexY][MouseIndexX].isWet = false;
				_tile[MouseIndexY][MouseIndexX].isFullyGrown = false;
				_tile[MouseIndexY][MouseIndexX].terrainFrameX = 1;
				_tile[MouseIndexY][MouseIndexX].terrainFrameY = 1;
				_tile[MouseIndexY - 1][MouseIndexX].objOver = OVR_NONE;

				checkHacked();
				
				if (PLAYER->getEnergy() > -20)
				{
					PLAYER->setEnergy(PLAYER->getDamage());
				}
			}
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
						SOUNDMANAGER->play("removeGrass", 0.2f);
						_tile[i][j].obj = OBJ_NONE;
						_tile[i][j].objType = OTY_NONE;
						_tile[i][j].seedType = SEED_NONE;
						_tile[i][j].grownLevel = 0;
						_tile[i][j].isFullyGrown = false;

						_tile[i - 1][j].objOver = OVR_NONE;

						if (PLAYER->getEnergy() > -20)
						{
							PLAYER->setEnergy(PLAYER->getDamage());
						}
					}
					if (_tile[i][j].objType == OTY_CROP && _tile[i][j].seedType == SEED_WHEAT
						&& _tile[i][j].isFullyGrown == true)
					{
						SOUNDMANAGER->play("removeGrass", 0.2f);
						dropFruit(_tile[MouseIndexY][MouseIndexX], ITEM_FRUIT, _tile[MouseIndexY][MouseIndexX].seedType);
						_tile[i][j].obj = OBJ_NONE;
						_tile[i][j].objType = OTY_NONE;
						_tile[i][j].seedType = SEED_NONE;
						_tile[i][j].grownLevel = 0;
						_tile[i][j].isFullyGrown = false;

						_tile[i - 1][j].objOver = OVR_NONE;

						if (PLAYER->getEnergy() > -20)
						{
							PLAYER->setEnergy(PLAYER->getDamage());
						}
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
				SOUNDMANAGER->play("movewood", 0.4f);
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_DESTRUCTIBLE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_WOODENFENCE;
				_tile[MouseIndexY][MouseIndexX].objFrameX = 2;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 3;

				PLAYER->setInvenItemAmount(PLAYER->getCurrentSlotNumber(),
					PLAYER->getCurrentInven()->amount - 1);

				if (PLAYER->getEnergy() > -20)
				{
					PLAYER->setEnergy(PLAYER->getDamage());
				}
			}
			if (PLAYER->getCurrentInven()->item_kind == ITEM_STONEFENCE)
			{
				SOUNDMANAGER->play("movewood", 0.4f);
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_DESTRUCTIBLE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_STONEFENCE;
				_tile[MouseIndexY][MouseIndexX].objFrameX = 2;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 3;

				PLAYER->setInvenItemAmount(PLAYER->getCurrentSlotNumber(),
					PLAYER->getCurrentInven()->amount - 1);

				if (PLAYER->getEnergy() > -20)
				{
					PLAYER->setEnergy(PLAYER->getDamage());
				}
			}
		}
	}
	checkFence();
}

void inGameScene::setEquipment()
{
	if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
		|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
		|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1)
			&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1))) //�밢�� 4 Ÿ���϶�
	{
		if (_tile[MouseIndexY][MouseIndexX].obj == OBJ_NONE)
		{
			//���۾������϶�
			if (PLAYER->getCurrentInven()->item_kind == ITEM_BOX) //�����϶�
			{
				SOUNDMANAGER->play("movewood", 0.4f);
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_EQUIPMENT;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_BOX;
				_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 0;
			}
			if (PLAYER->getCurrentInven()->item_kind == ITEM_BLASTFURNACE) //�뱤���϶� 
			{
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_EQUIPMENT;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_BLASTFURNACE;
				_tile[MouseIndexY][MouseIndexX].objFrameX = 1;
				_tile[MouseIndexY][MouseIndexX].objFrameY = 0;
			}

			for (int i = 1; i < 10; i++)
			{
				if (PLAYER->getCurrentInven()->scarecrowKind == i) //����ƺ��϶�
				{
					SOUNDMANAGER->play("movewood", 0.4f);
					_tile[MouseIndexY][MouseIndexX].obj = OBJ_EQUIPMENT;
					_tile[MouseIndexY][MouseIndexX].objType = OTY_SCARECROW;
					_tile[MouseIndexY][MouseIndexX].objFrameX = i+1;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 0;
				}
			}
			tagItem temp = {};
			PLAYER->setInvenItem(PLAYER->getCurrentSlotNumber(),temp);
		}
	}
}

void inGameScene::waterGround()
{
	PLAYER->setState(SPRAYWATER);
	if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
		|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
		|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1) //�밢�� 4 Ÿ���϶�
			&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1)))
	{
		if (PLAYER->getWaterAmount() >= 2)
		{
			SOUNDMANAGER->play("water", 0.2f);
			PLAYER->setWaterAmount(PLAYER->getWaterAmount() - 2);

			if (PLAYER->getEnergy() > -20)
			{
				PLAYER->setEnergy(PLAYER->getDamage());
			}

			_tile[MouseIndexY][MouseIndexX].isWet = true;
			checkHacked();
		}
	}
}

void inGameScene::fillWater()
{

	if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
		|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
		|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1) //�밢�� 4 Ÿ���϶�
			&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1)))
	{
		SOUNDMANAGER->play("water", 0.2f);
		PLAYER->setWaterAmount(34);
	}
}

void inGameScene::plantSeed()
{
	//�۹� �ɱ�
	if (!(PLAYER->getCurrentInven()->seedKind == SEED_PINETREE || PLAYER->getCurrentInven()->seedKind == SEED_MAPLETREE || PLAYER->getCurrentInven()->seedKind == SEED_OAKTREE)
		&& _tile[MouseIndexY][MouseIndexX].terrain == TR_HACKED && _tile[MouseIndexY][MouseIndexX].objType == OTY_NONE)
	{
		PLAYER->setState(CARRYSTAND);
		if (((MouseIndexX == currentIndexX + 1 || MouseIndexX == currentIndexX - 1) && MouseIndexY == currentIndexY)
			|| (MouseIndexX == currentIndexX && (MouseIndexY == currentIndexY + 1 || MouseIndexY == currentIndexY - 1)) //�����¿� 4Ÿ���϶�
			|| ((MouseIndexX == currentIndexX - 1 || MouseIndexX == currentIndexX + 1) //�밢�� 4 Ÿ���϶�
				&& (MouseIndexY == currentIndexY - 1 || MouseIndexY == currentIndexY + 1)))
		{
			SOUNDMANAGER->play("seed", 0.2f);
			PLAYER->setInvenItemAmount(PLAYER->getCurrentSlotNumber(),
				PLAYER->getCurrentInven()->amount - 1);
			if (_tile[MouseIndexY][MouseIndexX].obj == OBJ_NONE)
			{
				_tile[MouseIndexY][MouseIndexX].obj = OBJ_SEED;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_CROP;
				_tile[MouseIndexY][MouseIndexX].seedType = PLAYER->getCurrentInven()->seedKind;
				_tile[MouseIndexY][MouseIndexX].grownLevel = 0;
				_tile[MouseIndexY][MouseIndexX].isFullyGrown = false;

				_tile[MouseIndexY - 1][MouseIndexX].objOver = OVR_OVER;

				switch (PLAYER->getCurrentInven()->seedKind)
				{
				case SEED_NONE:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 0;
					break;
				case SEED_TOMATO:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 7;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 6;
					break;
				case SEED_HOTPEPPER:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 19;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 18;
					break;
				case SEED_RADISH:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 3;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 2;
					break;
				case SEED_STARFRUIT:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 29;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 28;
					break;
				case SEED_POPPY:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 13;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 12;
					break;
				case SEED_SUNFLOWER:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 17;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 16;
					break;
				case SEED_GRAPE:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 27;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 26;
					break;
				case SEED_GREENBEAN:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 9;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 8;
					break;
				case SEED_MELON:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 11;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 10;
					break;
				case SEED_BLUEBERRY:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 23;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 22;
					break;
				case SEED_WHEAT:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 5;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 4;
					break;
				case SEED_REDCABBAGE:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 25;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 24;
					break;
				case SEED_CORN:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 21;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 20;
					break;
				case SEED_SUMMERSPANGLE:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 15;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 14;
					break;
				case SEED_HOPS:
					_tile[MouseIndexY][MouseIndexX].objFrameX = 0;
					_tile[MouseIndexY][MouseIndexX].objFrameY = 1;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX = 0;
					_tile[MouseIndexY - 1][MouseIndexX].ovlFrameY = 0;
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
			SOUNDMANAGER->play("seed", 0.2f);
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

				PLAYER->setInvenItemAmount(PLAYER->getCurrentSlotNumber(),
					PLAYER->getCurrentInven()->amount - 1);

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
		SOUNDMANAGER->play("harvest", 0.2f);

		//�÷��̾� ��ų ��ŭ ���� �þ
		if (_tile[MouseIndexY][MouseIndexX].seedType == SEED_BLUEBERRY)
		{
			for (int i = 0; i < 3 * PLAYER->getDropItemNum(); i++)
			{
				dropFruit(_tile[MouseIndexY][MouseIndexX], ITEM_FRUIT, _tile[MouseIndexY][MouseIndexX].seedType);
			}
		}
		else
		{
			for (int i = 0; i < PLAYER->getDropItemNum(); i++)
			{
				dropFruit(_tile[MouseIndexY][MouseIndexX], ITEM_FRUIT, _tile[MouseIndexY][MouseIndexX].seedType);
			}
		}

		//����ġ ���
		if (_tile[MouseIndexY][MouseIndexX].seedType != SEED_NONE)
		{
			PLAYER->setFarmingExp(ITEMMANAGER->findDropItem(ITEM_FRUIT, _tile[MouseIndexY][MouseIndexX].seedType).exp);
		}
		if (_tile[MouseIndexY][MouseIndexX].seedType == SEED_TOMATO
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_HOTPEPPER
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_GRAPE
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_GREENBEAN
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_BLUEBERRY
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_CORN
			|| _tile[MouseIndexY][MouseIndexX].seedType == SEED_HOPS)	//������ ��Ȯ�� �� �ִ� �۹���
		{
			_tile[MouseIndexY][MouseIndexX].isFullyGrown = false;
			_tile[MouseIndexY][MouseIndexX].grownLevel -= 1;
			_tile[MouseIndexY][MouseIndexX].objFrameX += 1;
			_tile[MouseIndexY - 1][MouseIndexX].ovlFrameX += 1;
		}
		else
		{
			_tile[MouseIndexY][MouseIndexX].isFullyGrown = false;
			_tile[MouseIndexY][MouseIndexX].obj = OBJ_NONE;
			_tile[MouseIndexY][MouseIndexX].seedType = SEED_NONE;
			_tile[MouseIndexY][MouseIndexX].grownLevel = 0;

			_tile[MouseIndexY - 1][MouseIndexX].objOver = OVR_NONE;
		}
		checkFullyGrown(_tile[MouseIndexY][MouseIndexX]);
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
			if (PLAYER->getCurrentInven()->item_kind == ITEM_SPRINKLER1)
			{
				PLAYER->setInvenItemAmount(PLAYER->getCurrentSlotNumber(),
					PLAYER->getCurrentInven()->amount - 1);

				_tile[MouseIndexY][MouseIndexX].obj = OBJ_DESTRUCTIBLE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_SPRINKLER1;
				_tile[MouseIndexY][MouseIndexX].objFrameX = PLAYER->getCurrentInven()->indexX;
				_tile[MouseIndexY][MouseIndexX].objFrameY = PLAYER->getCurrentInven()->indexY;
			}
			else if (PLAYER->getCurrentInven()->item_kind == ITEM_SPRINKLER2)
			{
				PLAYER->setInvenItemAmount(PLAYER->getCurrentSlotNumber(),
					PLAYER->getCurrentInven()->amount - 1);

				_tile[MouseIndexY][MouseIndexX].obj = OBJ_DESTRUCTIBLE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_SPRINKLER2;
				_tile[MouseIndexY][MouseIndexX].objFrameX = PLAYER->getCurrentInven()->indexX;
				_tile[MouseIndexY][MouseIndexX].objFrameY = PLAYER->getCurrentInven()->indexY;
			}
			else if (PLAYER->getCurrentInven()->item_kind == ITEM_SPRINKLER3)
			{
				PLAYER->setInvenItemAmount(PLAYER->getCurrentSlotNumber(),
					PLAYER->getCurrentInven()->amount - 1);

				_tile[MouseIndexY][MouseIndexX].obj = OBJ_DESTRUCTIBLE;
				_tile[MouseIndexY][MouseIndexX].objType = OTY_SPRINKLER3;
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
		for (int i = 0; i < TILEY; i++)
		{
			for (int j = 0; j < TILEX; j++)
			{
				if (_tile[i][j].objType == OTY_SPRINKLER1)
				{
					for (int y = -1; y < 2; y++)
					{
						for (int x = -1; x < 2; x++)
						{
							if (_tile[i + y][j + x].terrain == TR_HACKED) { _tile[i + y][j + x].isWet = true; }
						}
					}
				}
				else if (_tile[i][j].objType == OTY_SPRINKLER2)
				{
					for (int y = -2; y < 3; y++)
					{
						for (int x = -2; x < 3; x++)
						{
							if (_tile[i + y][j + x].terrain == TR_HACKED) { _tile[i + y][j + x].isWet = true; }
						}
					}
				}
				else if (_tile[i][j].objType == OTY_SPRINKLER3)
				{
					for (int y = -3; y < 4; y++)
					{
						for (int x = -3; x < 4; x++)
						{
							if (_tile[i + y][j + x].terrain == TR_HACKED) { _tile[i + y][j + x].isWet = true; }
						}
					}
				}
					/*
					if (_tile[i - 1][j - 1].terrain == TR_HACKED) { _tile[i - 1][j - 1].isWet = true; }
					if (_tile[i - 1][j].terrain == TR_HACKED) { _tile[i - 1][j].isWet = true; }
					if (_tile[i - 1][j + 1].terrain == TR_HACKED) { _tile[i - 1][j + 1].isWet = true; }
					if (_tile[i][j - 1].terrain == TR_HACKED) { _tile[i][j - 1].isWet = true; }
					if (_tile[i][j + 1].terrain == TR_HACKED) { _tile[i][j + 1].isWet = true; }
					if (_tile[i + 1][j - 1].terrain == TR_HACKED) { _tile[i + 1][j - 1].isWet = true; }
					if (_tile[i + 1][j].terrain == TR_HACKED) { _tile[i + 1][j].isWet = true; }
					if (_tile[i + 1][j + 1].terrain == TR_HACKED) { _tile[i + 1][j + 1].isWet = true; }
					*/
				checkHacked();
			}
		}
		PLAYER->setIsSprinkled(true);
		isSprinkled = true;
		cout << "end" << endl;
	}
}

void inGameScene::eatFruit()
{
	if (!SOUNDMANAGER->isPlaySound("eat"))
	{
		SOUNDMANAGER->play("eat");
	}
	PLAYER->recoverHp(PLAYER->getCurrentInven()->hpRecover);
	PLAYER->recoverEnergy(PLAYER->getCurrentInven()->energyRecover);

	PLAYER->setInvenItemAmount(PLAYER->getCurrentSlotNumber(),
		PLAYER->getCurrentInven()->amount - 1);
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
				if ((_tile[i][j].seedType == SEED_TOMATO
					|| _tile[i][j].seedType == SEED_HOTPEPPER
					|| _tile[i][j].seedType == SEED_GRAPE
					|| _tile[i][j].seedType == SEED_GREENBEAN
					|| _tile[i][j].seedType == SEED_BLUEBERRY
					|| _tile[i][j].seedType == SEED_CORN
					|| _tile[i][j].seedType == SEED_HOPS)
					&& _tile[i][j].objFrameX == 7)
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
	case SEED_POPPY:
		if (tile.grownLevel == 5) { return true; }
		else { return false; }
		break;
	case SEED_SUNFLOWER:
		if (tile.grownLevel == 5) { return true; }
		else { return false; }
		break;
	case SEED_GRAPE:
		if (tile.grownLevel == 6) { return true; }
		else { return false; }
		break;
	case SEED_GREENBEAN:
		if (tile.grownLevel == 6) { return true; }
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
	case SEED_SUMMERSPANGLE:
		if (tile.grownLevel == 5) { return true; }
		else { return false; }
		break;
	case SEED_HOPS:
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
	SOUNDMANAGER->play("getItem", 0.2f);
	bool isAdded = false;
	for (int i = 0; i < INVENMAX; i++)
	{
		if (PLAYER->getInven(i)->item_kind == item.item_kind && PLAYER->getInven(i)->indexX == item.indexX)
		{
			PLAYER->setInvenItemAmount(i, PLAYER->getInven(i)->amount + 1);
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
				if (item.item_kind == ITEM_SEED)
				{
					PLAYER->setInvenItem(i, ITEMMANAGER->findDropItem(item.item_kind, item.seedKind));
					break;
				}
				else
				{
					PLAYER->setInvenItem(i, ITEMMANAGER->findDropItem(item.item_kind, item.indexX));
					break;
				}
			}
		}
	}
}

void inGameScene::dropFruit(tagTile tile, ITEM itemKind, SEED seedType)
{
	tagItemOnField temp;
	temp.item = ITEMMANAGER->findDropItem(itemKind, seedType);
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

void inGameScene::dropItem(tagTile tile, ITEM itemKind, int indexX)
{
	tagItemOnField temp;
	temp.item = ITEMMANAGER->findDropItem(itemKind, indexX);
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

void inGameScene::skillClick()
{

	//if (PLAYER->getisSkill())
	//{
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
//	}

}

void inGameScene::skillSelect()
{
	//if (PLAYER->getisSkill())
	//{
		PLAYER->skillUpdate();

		PLAYER->getskill()->setSkill(PLAYER->getCurrentSlotNumber());
	//}
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

void inGameScene::setEventGround()
{
	for (int i = 16; i < 25; i++)
	{
		for (int j = 2; j < 22; j++)
		{
			tileSave[i][j] = _tile[i][j];
			_tile[i][j].obj = OBJ_NONE;
			_tile[i][j].objType = OTY_NONE;
			_tile[i][j].grownLevel = 0;
			_tile[i][j].isFullyGrown = false;
			_tile[i][j].objOver = OVR_NONE;
			_tile[i][j].seedType = SEED_NONE;
			tagTree temp;
			memset(&temp, 0, sizeof(tagTree));
			_tile[i][j].tree = temp;

			if (j == 2 && i == 16)
			{
				_tile[i][j].terrainFrameX = 0;
				_tile[i][j].terrainFrameY = 2;
			}
			else if ((j >= 3 && j <= 20) && i == 16)
			{
				_tile[i][j].terrainFrameX = 1;
				_tile[i][j].terrainFrameY = 2;
			}
			else if (j == 21 && i == 16)
			{
				_tile[i][j].terrainFrameX = 3;
				_tile[i][j].terrainFrameY = 2;
			}
			else if (j == 21 && i >= 17 && i <= 24)
			{
				_tile[i][j].terrainFrameX = 3;
				_tile[i][j].terrainFrameY = 3;
			}
			else if (j == 2 && i == 24)
			{
				_tile[i][j].terrainFrameX = 0;
				_tile[i][j].terrainFrameY = 4;
			}
			else if (j == 2)
			{
				_tile[i][j].terrainFrameX = 0;
				_tile[i][j].terrainFrameY = 3;
			}
			else if ((j >= 3 && j < 10) && i == 24)
			{
				_tile[i][j].terrainFrameX = 1;
				_tile[i][j].terrainFrameY = 4;
			}
			else if (j == 10 && i == 24)
			{
				_tile[i][j].terrainFrameX = 3;
				_tile[i][j].terrainFrameY = 0;
			}
			else if (j == 12 && i == 24)
			{
				_tile[i][j].terrainFrameX = 3;
				_tile[i][j].terrainFrameY = 1;
			}
			else if (j >= 13 && j <= 20 && i == 24)
			{
				_tile[i][j].terrainFrameX = 1;
				_tile[i][j].terrainFrameY = 4;
			}
			else
			{
				_tile[i][j].terrainFrameX = 1;
				_tile[i][j].terrainFrameY = 1;
			}

			_tile[i][j].terrain = terrainSelect(_tile[i][j].terrainFrameX, _tile[i][j].terrainFrameY);
		}
	}
	for (int i = 25; i < 35; i++)
	{
		for (int j = 10; j < 13; j++)
		{
			tileSave[i][j] = _tile[i][j];
			_tile[i][j].obj = OBJ_NONE;
			_tile[i][j].objType = OTY_NONE;
			_tile[i][j].grownLevel = 0;
			_tile[i][j].isFullyGrown = false;
			_tile[i][j].objOver = OVR_NONE;
			_tile[i][j].seedType = SEED_NONE;
			tagTree temp;
			memset(&temp, 0, sizeof(tagTree));
			_tile[i][j].tree = temp;
			if (j == 10 && i == 34)
			{
				_tile[i][j].terrainFrameX = 2;
				_tile[i][j].terrainFrameY = 2;
			}
			else if (j == 10)
			{
				_tile[i][j].terrainFrameX = 0;
				_tile[i][j].terrainFrameY = 3;
			}
			else if (j == 12 && i == 34)
			{
				_tile[i][j].terrainFrameX = 4;
				_tile[i][j].terrainFrameY = 0;
			}
			else if (j == 12)
			{
				_tile[i][j].terrainFrameX = 3;
				_tile[i][j].terrainFrameY = 3;
			}
			else
			{
				_tile[i][j].terrainFrameX = 1;
				_tile[i][j].terrainFrameY = 1;
			}

			_tile[i][j].terrain = terrainSelect(_tile[i][j].terrainFrameX, _tile[i][j].terrainFrameY);
		}
	}
}

void inGameScene::resetOriginalGround()
{
	for (int i = 16; i < 25; i++)
	{
		for (int j = 2; j < 22; j++)
		{
			_tile[i][j] = tileSave[i][j];
			_tile[i][j].terrain = terrainSelect(_tile[i][j].terrainFrameX, _tile[i][j].terrainFrameY);
		}
	}
	for (int i = 25; i < 35; i++)
	{
		for (int j = 10; j < 13; j++)
		{
			_tile[i][j] = tileSave[i][j];
			_tile[i][j].terrain = terrainSelect(_tile[i][j].terrainFrameX, _tile[i][j].terrainFrameY);
		}
	}
}

void inGameScene::setCurrentSlotNumber(int mouseWheel)
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
			//memset(saveName, 0, sizeof(saveName));
			//GetDlgItemText(hWnd, IDC_EDIT1, saveName, MAX_PATH);
		case IDCANCEL:
			EndDialog(hWnd, IDOK);
			return TRUE;
		}
		return TRUE;
	}
	return FALSE;
}
