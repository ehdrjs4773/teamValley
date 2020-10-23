#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	isSkill = false;

	index = 0;
	count = 0;
	centerX = WINSIZEX / 2;
	centerY = WINSIZEY / 2;

	currentX = centerX / 16;
	currentY = (centerY + 8) / 16;

	playerHoldItem = RectMakeCenter(centerX - 8, centerY - 48, 16, 16);

	playerHp = 138;
	playerEnergy = 138;
	Damage= 2;

	frontHpBar = RectMakeCenter(WINSIZEX - 95, WINSIZEY - 88, 20, 138);
	frontEnergyBar = RectMakeCenter(WINSIZEX - 55, WINSIZEY - 88, 20, 138);

	speed = 1.5f;

	IMAGEMANAGER->addFrameImage("playerMove", "Images/�÷��̾��̹���2.bmp", 576, 2176, 12, 34, true, RGB(255, 0, 255));
	move = IMAGEMANAGER->findImage("playerMove");

	IMAGEMANAGER->addImage("backHpBar", "Images/BMP/backHpBar.bmp", 40, 188, true, RGB(255, 0, 255));
	backHpBar = IMAGEMANAGER->findImage("backHpBar");

	IMAGEMANAGER->addImage("backEnergyBar", "Images/BMP/backEnergyBar.bmp", 40, 188, true, RGB(255, 0, 255));
	playerStorage = IMAGEMANAGER->findImage("�÷��̾� â��");

	_inventory = new inventory;
	_inventory->init();

	stock = new Stock;
	stock->init();

	_skill = new skill();
	_skill->init();
	//stock->addPlayerStock(STOCK_BROWNCOW);
	//stock->addPlayerStock(STOCK_WHITECOW);
	//stock->addPlayerStock(STOCK_BROWNCHICKEN);
	//stock->addPlayerStock(STOCK_WHITECHICKEN);

	currentMap = MAP_FARM;

	isShowInventory = false;
	isOpenPlayerStorageCover = false;
	isHit = false;

	_pDirection = DOWN;
	_pState = STAND;

	year = 1;
	hour = 6;
	minute = 0;
	money = 5000;
	currentSeason = SPRING;
	currentWeather = SUNNY;
	date = 1;
	day = MON;
	arrowAngle = 18;
	blinkCount = 0;
	darkAlpha = .0f;

	return S_OK;
}

void  player::release()
{
}

void  player::update()
{
	if (!isShowInventory)
	{
		if (INPUT->GetKeyDown(VK_TAB))
		{
			if (isSkill) isSkill = false;
			else {
				_inventory->setCurrentSlotNumber(0);
				isSkill = true;
			}
		}
	}
	
	if (INPUT->GetKeyDown('E'))
	{
		if(!isShowInventory) SOUNDMANAGER->play("menuopen");
		else SOUNDMANAGER->play("menuclose");

		if (!isOpenPlayerStorageCover)
		{
			if (isShowInventory)
			{
				isShowInventory = false;
				_inventory->setInvenToryMove(false);
				_inventory->setInvenPage(false);
			}
			else
			{
				_inventory->setInvenToryMove(true);
				isShowInventory = true;
				_inventory->setInvenPage(true);
			}
		}
	}
	if (INPUT->GetKeyDown('B'))
	{
		hour += 1;
		money -= 33;
		currentSeason = (SEASON)(currentSeason + 1);
		currentWeather = (WEATHER)(currentWeather + 1);
	}
	if (INPUT->GetKey('N'))
	{
		darkAlpha += 0.47222;
		//cout << darkAlpha << endl;
	}


	//�÷��̾� ���� �� üũ
	setCurrentMap();

	//���� ������
	if (currentMap == MAP_BARN)
	{
		stock->update();
	}

	currentX = centerX / 16;
	currentY = (centerY + 8) / 16;

	rc = RectMakeCenter(centerX, centerY + 8.0f, 16, 16);

	playerAnimation();

	MouseIndexX = (float)((float)CAMERAMANAGER->getX() / 16) + (float)((float)_ptMouse.x / 40);
	MouseIndexY = (float)((float)CAMERAMANAGER->getY() / 16) + (float)((float)_ptMouse.y / 40);

	//rc = RectMakeCenter(centerX, centerY, 16, 32);


	_inventory->update();

	if (!isShowInventory)
	{
		countTime();
	}
	_inventory->getInventoryCraft()->materialUpdate();

	closePlayerStorageCover();
}

void player::render()
{
	if (isHit)
	{
		hitCount++;
		if (hitCount % 5 == 0)
		{
			playerRender();
		}
		if (hitCount > 60)
		{
			isHit = false;
			hitCount = 0;
		}
	}
	else
	{
		playerRender();
	}
	if (currentMap == MAP_BARN)
	{
		stock->render();
	}
}

void player::playerCarryItem(HDC hdc)
{
	if (!isShowInventory && !isOpenPlayerStorageCover)
	{
		playerHoldItem = RectMakeCenter(centerX, centerY - 18, 16, 16);

		if (getCurrentInven()->item_kind == ITEM_SEED && getCurrentInven()->seedKind != SEED_RANDOM)
		{
			if (getCurrentInven()->seedKind == SEED_PINETREE || getCurrentInven()->seedKind == SEED_MAPLETREE || getCurrentInven()->seedKind == SEED_OAKTREE)
			{
				IMAGEMANAGER->findImage("����(��)")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top,
					getCurrentInven()->indexX, getCurrentInven()->indexY);
			}
			else
			{
				IMAGEMANAGER->findImage("����hold")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top,
					getCurrentInven()->indexX, getCurrentInven()->indexY);
			}
		}
		else if (getCurrentInven()->item_kind == ITEM_BOX)
		{
			IMAGEMANAGER->findImage("���������۽���")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top-16,
				getCurrentInven()->indexX, getCurrentInven()->indexY);
			IMAGEMANAGER->findImage("���������۽���")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top,
				getCurrentInven()->indexX, getCurrentInven()->indexY+1);
		}
		else if (getCurrentInven()->item_kind == ITEM_FEEDBUCKET)
		{
			IMAGEMANAGER->findImage("���������۽���")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top - 16,
				getCurrentInven()->indexX, getCurrentInven()->indexY);
			IMAGEMANAGER->findImage("���������۽���")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top,
				getCurrentInven()->indexX, getCurrentInven()->indexY + 1);
		}
		else if (getCurrentInven()->item_kind == ITEM_BEEFARM)
		{
			IMAGEMANAGER->findImage("���������۽���")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top - 16,
				getCurrentInven()->indexX, getCurrentInven()->indexY);
			IMAGEMANAGER->findImage("���������۽���")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top,
				getCurrentInven()->indexX, getCurrentInven()->indexY + 1);
		}
		else if (getCurrentInven()->item_kind == ITEM_SCARECROW)
		{
			IMAGEMANAGER->findImage("���������۽���")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top - 16,
				getCurrentInven()->indexX, getCurrentInven()->indexY);
			IMAGEMANAGER->findImage("���������۽���")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top,
				getCurrentInven()->indexX, getCurrentInven()->indexY + 1);
		}
		else if (getCurrentInven()->item_kind == ITEM_BLASTFURNACE)
		{
			IMAGEMANAGER->findImage("���������۽���")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top - 16,
				getCurrentInven()->indexX, getCurrentInven()->indexY);
			IMAGEMANAGER->findImage("���������۽���")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top,
				getCurrentInven()->indexX, getCurrentInven()->indexY + 1);
		}
		else if (getCurrentInven()->item_kind == ITEM_PICKLEDBARREL)
		{
			IMAGEMANAGER->findImage("���������۽���")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top - 16,
				getCurrentInven()->indexX, getCurrentInven()->indexY);
			IMAGEMANAGER->findImage("���������۽���")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top,
				getCurrentInven()->indexX, getCurrentInven()->indexY + 1);
		}
	}
	
	//Rectangle(hdc, playerHoldItem);
}

void player::playerStatusRender(HDC hdc)
{
	InventoryRender(hdc);
	energyBarRender(hdc);
	clockRender(hdc);
	moneyRender(hdc);
	arrowRender(hdc);
	weatherRender(hdc);

	if (SCENEMANAGER->getCurrentSceneName() == "����ȭ��")
	{
		hpBarRender(hdc);
	}
}

void player::InventoryRender(HDC hdc)
{
	if (isShowInventory)
	{
		_inventory->render(hdc);
		_inventory->inven_item_info(hdc);
	}
	else {
		if (!isSkill && !isOpenPlayerStorageCover)
		{
			_inventory->quickSlot(hdc);
			_inventory->quickinven_item_info(hdc);
		}
		else
		{
			_inventory->quickSkillSlot(hdc);
		}
	}
	//Rectangle(CAMERAMANAGER->getMemDC(), rc);

	if (isOpenPlayerStorageCover)
	{
		_inventory->renderStorageInventory(hdc);
		_inventory->storage_item_info(hdc);
		_inventory->inven_item_info(hdc);
	}
}

void player::energyBarRender(HDC hdc)
{
	int b = 0 + (278 - playerHp);

	IMAGEMANAGER->render("backEnergyBar", hdc, WINSIZEX - 75, WINSIZEY - 200);
	Rectangle(hdc, frontEnergyBar);
	brush = CreateSolidBrush(RGB(b, 220, 7));
	FillRect(hdc, &frontEnergyBar, brush);
	DeleteObject(brush);
}

void player::hpBarRender(HDC hdc)
{
	//int a = 0 + (278 - playerHp);

	IMAGEMANAGER->render("backHpBar", hdc, WINSIZEX - 115, WINSIZEY - 200);
	Rectangle(hdc, frontHpBar);
	brush = CreateSolidBrush(RGB(255, 30, 6));
	FillRect(hdc, &frontHpBar, brush);
	DeleteObject(brush);
}

void player::playerAnimation()
{
	count++;

	switch (_pState)
	{
	case STAND:
		index = 0;
		break;
	case RUN:
		switch (_pDirection)
		{
		case RIGHT:
			if (count % 10 == 0)
			{
				index += 1;
				if (index > 5)
				{
					index = 0;
				}
			}
			break;
		case LEFT:
			if (count % 10 == 0)
			{
				index += 1;
				if (index > 5)
				{
					index = 0;
				}
			}
			break;
		case UP:
			if (count % 10 == 0)
			{
				index += 1;
				if (index > 7)
				{
					index = 0;
				}
			}
			break;
		case DOWN:
			if (count % 10 == 0)
			{
				index += 1;
				if (index > 6)
				{
					index = 0;
				}				
			}
			break;
		}
		break;
	case DIGGROUND:
		switch (_pDirection)
		{
		case RIGHT:
			if (count % 5 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case LEFT:
			if (count % 5 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case UP:
			if (count % 5 == 0)
			{
				index++;
				if (index > 3)
				{
					_pState = STAND;
				}
			}
			break;
		case DOWN:
			if (count % 5 == 0)
			{
				index++;
				if (index > 2)
				{
					_pState = STAND;
				}
			}
			break;
		}
		break;

	case CUTDOWNTREE:
		switch (_pDirection)
		{
		case RIGHT:
			if (count % 5 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case LEFT:
			if (count % 5 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case UP:
			if (count % 5 == 0)
			{
				index++;
				if (index > 3)
				{
					_pState = STAND;
				}
			}
			break;
		case DOWN:
			if (count % 5 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		}
		break;

	case CUTGRASS:
		switch (_pDirection)
		{
		case RIGHT:
			if (count % 5 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		case LEFT:
			if (count % 5 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		case UP:
			if (count % 5 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		case DOWN:
			if (count % 5 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		}
		break;
	case BREAKSTONE:
		switch (_pDirection)
		{
		case RIGHT:
			if (count % 5 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case LEFT:
			if (count % 5 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case UP:
			if (count % 5 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case DOWN:
			if (count % 5 == 0)
			{
				index++;
				if (index > 6)
				{
					_pState = STAND;
				}
			}
			break;
		}
		break;
	case SPRAYWATER:
		switch (_pDirection)
		{
		case RIGHT:
			if (count % 5 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case LEFT:
			if (count % 5 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case UP:
			if (count % 5 == 0)
			{
				index++;
				if (index > 2)
				{
					_pState = STAND;
				}
			}
			break;
		case DOWN:
			if (count % 5 == 0)
			{
				index++;
				if (index > 11)
				{
					_pState = STAND;
				}
			}
			break;
		}
		break;
	case FILLWATER:
		switch (_pDirection)
		{
		case RIGHT:
			if (count % 5 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case LEFT:
			if (count % 5 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case UP:
			if (count % 5 == 0)
			{
				index++;
				if (index > 2)
				{
					_pState = STAND;
				}
			}
			break;
		case DOWN:
			if (count % 5 == 0)
			{
				index++;
				if (index > 11)
				{
					_pState = STAND;
				}
			}
			break;
		}
		break;
	case ATTACK:
		switch (_pDirection)
		{
		case RIGHT:
			if (count % 5 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		case LEFT:
			if (count % 5 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		case UP:
			if (count % 5 == 0)
			{
				index++;
				if (index > 2)
				{
					_pState = STAND;
				}
			}
			break;
		case DOWN:
			if (count % 5 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		}
		break;
	case CARRY:
		switch (_pDirection)
		{
		case RIGHT:
			if (count % 5 == 0)
			{
				index++;
				if (index > 4)
				{
					index = 0;
				}
			}
			break;
		case LEFT:
			if (count % 5 == 0)
			{
				index++;
				if (index > 4)
				{
					index = 0;
				}
			}
			break;
		case UP:
			if (count % 5 == 0)
			{
				index++;
				if (index > 5)
				{
					index = 0;
				}
			}
			break;
		case DOWN:
			if (count % 5 == 0)
			{
				index++;
				if (index > 5)
				{
					index = 0;
				}
			}
			break;
		}
		break;
	case CARRYSTAND:
		index = 0;
		break;
	}

}

void player::playerRender()
{
	switch (_pState)
	{
	case STAND:
		switch (_pDirection)
		{
		case RIGHT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 0);
			break;
		case LEFT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 1);
			break;
		case UP:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 2);
			break;
		case DOWN:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 3);
			break;
		}
		break;
	case RUN:
		switch (_pDirection)
		{
		case RIGHT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 0);
			break;
		case LEFT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 1);
			break;
		case UP:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 2);
			break;
		case DOWN:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 3);
			break;
		}
		break;
	case DIGGROUND:
		switch (_pDirection)
		{
		case RIGHT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 10);
			break;
		case LEFT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 11);
			break;
		case UP:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 9);
			break;
		case DOWN:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 8);
			break;
		}
		break;
	case CUTDOWNTREE:
		switch (_pDirection)
		{
		case RIGHT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 5);
			break;
		case LEFT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 6);
			break;
		case UP:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 7);
			break;
		case DOWN:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 4);
			break;
		}
		break;
	case CUTGRASS:
		switch (_pDirection)
		{
		case RIGHT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 13);
			break;
		case LEFT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 14);
			break;
		case UP:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 15);
			break;
		case DOWN:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 12);
			break;
		}
		break;
	case BREAKSTONE:
		switch (_pDirection)
		{
		case RIGHT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 26);
			break;
		case LEFT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 27);
			break;
		case UP:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 25);
			break;
		case DOWN:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 24);
			break;
		}
		break;
	case SPRAYWATER:
		switch (_pDirection)
		{
		case RIGHT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 16);
			break;
		case LEFT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 17);
			break;
		case UP:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 19);
			break;
		case DOWN:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 18);
			break;
		}
		break;
	case FILLWATER:
		break;
	case ATTACK:
		switch (_pDirection)
		{
		case RIGHT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 29);
			break;
		case LEFT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 30);
			break;
		case UP:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 31);
			break;
		case DOWN:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 28);
			break;
		}
		break;
	case CARRY:
		switch (_pDirection)
		{
		case RIGHT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 22);
			break;
		case LEFT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 21);
			break;
		case UP:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 23);
			break;
		case DOWN:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 20);
			break;
		}
		break;
	case CARRYSTAND:
		switch (_pDirection)
		{
		case RIGHT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 22);
			break;
		case LEFT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 21);
			break;
		case UP:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 23);
			break;
		case DOWN:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 20);
			break;
		}

	}
}

void player::openPlayerStorageCover()
{
	//�÷��̾� â�����
	if(!isOpenPlayerStorageCover)
	{
		_inventory->setIsShowTemp(true);
		isOpenPlayerStorageCover = true;
		_inventory->setInvenToryMove(true);
	}
}

void player::closePlayerStorageCover()
{
	if(PtInRect(&_inventory->getCloseButton(),_ptMouse))
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			if (isOpenPlayerStorageCover)
			{
				_inventory->setIsShowTemp(false);
				isOpenPlayerStorageCover = false;
				_inventory->setInvenToryMove(false);
			}
		}
	}
}

void player::setCurrentMap()
{
	if (SWITCHMANAGER->getCurrentScene() == "������")
	{
		currentMap = MAP_SHOP;
	}
	else if (SWITCHMANAGER->getCurrentScene() == "�ΰ���ȭ��")
	{
		currentMap = MAP_FARM;
	}
	else if (SWITCHMANAGER->getCurrentScene() == "�ǹ���ȭ��")
	{
		currentMap = MAP_BARN;
	}
	else if (SWITCHMANAGER->getCurrentScene() == "����ȭ��")
	{
		currentMap = MAP_HOUSE;
	}
	else if (SWITCHMANAGER->getCurrentScene() == "����ȭ��")
	{
		currentMap = MAP_MINE;
	}
}

void player::countTime()
{
	timeCount++;
	if (timeCount % 120 == 0)
	{
		minute++;
		if (hour > 17 || hour < 4)
		{
			darkAlpha += 0.47222;
			if (darkAlpha > 180)
			{
				darkAlpha = 180;
			}
		}
		else
		{
			darkAlpha = 0;
		}
		if (minute >= 60)
		{
			hour += 1;
			minute = 0;
		}
	}
	if (hour >= 24)
	{
		//date += 1;
		day = (DAYOFWEEK)(day + 1);
		hour = 0;
	}
	if (date > 30)
	{
		currentSeason = (SEASON)(currentSeason + 1);
		date = 1;
	}
	if (currentSeason > 3)
	{
		year += 1;
		currentSeason = (SEASON)0;
	}
	if (day > 6)
	{
		day = (DAYOFWEEK)0;
	}
}

void player::resetClock()
{
	date++;
	hour < 24 ? day = (DAYOFWEEK)(day + 1) : day = day;
	hour = 6;
	minute = 0;
	currentWeather = (WEATHER)RANDOM->range(5);
	darkAlpha = .0f;
}

bool player::checkFullyGrown(tagTile tile)
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

void player::loadPlayerData()
{
	//�÷��̾� ������ �ҷ�����
	date = INIDATA->loadDataInteger("save/playerData", "PLAYER", "date");
	year = INIDATA->loadDataInteger("save/playerData", "PLAYER", "year");
	day = (DAYOFWEEK)INIDATA->loadDataInteger("save/playerData", "PLAYER", "day");
	darkAlpha = INIDATA->loadDataInteger("save/playerData", "PLAYER", "darkAlpha");
	currentSeason = (SEASON)INIDATA->loadDataInteger("save/playerData", "PLAYER", "currentSeason");
	currentWeather = (WEATHER)INIDATA->loadDataInteger("save/playerData", "PLAYER", "currentWeather");
	money = INIDATA->loadDataInteger("save/playerData", "PLAYER", "money");
	
	loadInven();
	loadStock();
	loadBoxInven();
}

void player::loadInven()
{
	//�κ� �ҷ�����
	HANDLE file1;
	DWORD read1;
	tagSaveItem LoadItem[36] = {};
	
	TCHAR saveName3[MAX_PATH] = {};
	sprintf(saveName3, "save/playerInven.data");
	file1 = CreateFile(saveName3, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file1, LoadItem, sizeof(LoadItem)+sizeof(tagSaveItem), &read1, NULL);
	CloseHandle(file1);

	for (int i = 0; i < 36; i++)
	{
		_inventory->setvInven(i, LoadItem[i]);
	}
}

void player::loadBoxInven()
{
	//�ڽ� �ҷ�����
	HANDLE file1;
	DWORD read1;
	tagItem LoadItem[36] = {};

	TCHAR saveName3[MAX_PATH] = {};
	sprintf(saveName3, "save/playerBoxInven.data");
	file1 = CreateFile(saveName3, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file1, LoadItem, sizeof(LoadItem) + sizeof(tagSaveItem), &read1, NULL);
	CloseHandle(file1);

	for (int i = 0; i < 36; i++)
	{
		_inventory->setvBoxInven(i, LoadItem[i]);
	}
}

void player::loadStock()
{
	//���� �ҷ�����
	HANDLE file;
	DWORD read;
	tagStock tempStock[5];
	TCHAR saveName2[MAX_PATH] = {};
	sprintf(saveName2, "save/playerStock.data");
	file = CreateFile(saveName2, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, tempStock, sizeof(tempStock), &read, NULL);
	CloseHandle(file);

	stock->getStock().clear();

	for (int i = 0; i < 4; i++)
	{
		//if (tempStock[i].speed == 0) break;
		stock->setStock(tempStock[i]);
	}
}

void player::savePlayerData()
{
	char dateStr[64], yearStr[64], dayStr[64], mapStr[64], seasonStr[64], weatherStr[64], darkStr[64], moneyStr[64];
	INIDATA->addData("PLAYER", "date", _itoa(date, dateStr, 10));
	INIDATA->addData("PLAYER", "year", _itoa(year, yearStr, 10));
	INIDATA->addData("PLAYER", "day", _itoa(day, dayStr, 10));
	INIDATA->addData("PLAYER", "darkAlpha", _itoa(darkAlpha, darkStr, 10));
	INIDATA->addData("PLAYER", "currentSeason", _itoa((int)currentSeason, seasonStr, 10));
	INIDATA->addData("PLAYER", "currentWeather", _itoa((int)currentWeather, weatherStr, 10));
	INIDATA->addData("PLAYER", "money", _itoa(money, moneyStr, 10));
	INIDATA->saveINI();
}

void player::savePlayerInven()
{
	vector<tagItem> temp;
	temp = _inventory->getvInven();
	tagSaveItem tempItem[36];

	memset(tempItem, 0, sizeof(tempItem));

	for (int i = 0; i < 36; i++)
	{
		if (temp[i].itemName == "")
		{
			tempItem[i].amount = 0;
			tempItem[i].buy_price = 0;
			tempItem[i].indexX = 0;
			tempItem[i].indexY = 0;
			tempItem[i].isFrame = false;
			tempItem[i].itemName = "";
			tempItem[i].item_kind = (ITEM)0;
			tempItem[i].rc = RectMake(0,0,0,0);
			tempItem[i].seedKind = (SEED)0;
			tempItem[i].sell_price = 0;
			tempItem[i].toolKind = (TOOL)0;
			tempItem[i].waterAmount = 0;
		}
		else
		{
			tempItem[i].amount = temp[i].amount;
			tempItem[i].buy_price = temp[i].buy_price;
			tempItem[i].indexX = temp[i].indexX;
			tempItem[i].indexY = temp[i].indexY;
			tempItem[i].isFrame = temp[i].isFrame;
			tempItem[i].itemName = temp[i].itemName;
			tempItem[i].item_kind = temp[i].item_kind;
			tempItem[i].rc = temp[i].rc;
			tempItem[i].seedKind = temp[i].seedKind;
			tempItem[i].sell_price = temp[i].sell_price;
			tempItem[i].toolKind = temp[i].toolKind;
			tempItem[i].waterAmount = temp[i].waterAmount;
		}
	}

	HANDLE file;
	DWORD write;
	TCHAR saveName[MAX_PATH] = {};
	sprintf(saveName, "save/playerInven.data");
	file = CreateFile(saveName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, tempItem, sizeof(tempItem), &write, NULL);
	CloseHandle(file);
}

void player::savePlayerStock()
{
	vector<tagStock> temp;
	temp = stock->getStock();

	tagStock tempStock[5];
	memset(tempStock, 0, sizeof(tempStock));

	for (int i = 0; i < stock->getStock().size(); i++)
	{
		tempStock[i] = temp[i];
	}

	HANDLE file;
	DWORD write;
	TCHAR saveName[MAX_PATH] = {};
	sprintf(saveName, "save/playerStock.data");
	file = CreateFile(saveName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, tempStock, sizeof(tempStock), &write, NULL);
	CloseHandle(file);
}

void player::saveMap()
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
					|| _tile[i][j].seedType == SEED_STARFRUIT
					|| _tile[i][j].seedType == SEED_EGGPLANT
					|| _tile[i][j].seedType == SEED_ANCIENTFRUIT
					|| _tile[i][j].seedType == SEED_SWEETGEMBERRY
					|| _tile[i][j].seedType == SEED_STRAWBERRY
					|| _tile[i][j].seedType == SEED_GRAPE
					|| _tile[i][j].seedType == SEED_COFFEEBEAN)
					&& _tile[i][j].objFrameX == 7)
				{
					if (_tile[i][j].isWet)
					{
						_tile[i][j].grownLevel += 1;
						_tile[i][j].objFrameX -= 1;
						_tile[i - 1][j].ovlFrameX -= 1;
					}
				}
				else if ((_tile[i][j].seedType == SEED_GREENBEAN
					|| _tile[i][j].seedType == SEED_BLUEBERRY
					|| _tile[i][j].seedType == SEED_CORN
					|| _tile[i][j].seedType == SEED_ARTICHOKE
					|| _tile[i][j].seedType == SEED_CRANBERRY
					|| _tile[i][j].seedType == SEED_HOPS
					|| _tile[i][j].seedType == SEED_CATUS)
					&& _tile[i][j].objFrameX == 15)
				{
					if (_tile[i][j].isWet)
					{
						_tile[i][j].grownLevel += 1;
						_tile[i][j].objFrameX -= 1;
						_tile[i - 1][j].ovlFrameX -= 1;
					}
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
					if (_tile[i][j].isWet)
					{
						_tile[i][j].grownLevel += 1;
						_tile[i][j].objFrameX += 1;
						_tile[i - 1][j].ovlFrameX += 1;
					}
				}
				_tile[i][j].isWet = false;

				//���ڶ����� Ȯ��
				_tile[i][j].isFullyGrown = checkFullyGrown(_tile[i][j]);
			}
		}
	}

	HANDLE file;
	DWORD write;
	TCHAR saveMapName[MAX_PATH] = "save/save.map";
	file = CreateFile(saveMapName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _tile, sizeof(_tile), &write, NULL);
	CloseHandle(file);
}

void player::saveBox()
{
	vector<tagItem> temp;
	temp = _inventory->getVBoxInven();
	tagItem tempItem[36];
	memset(tempItem, 0, sizeof(tempItem));

	for (int i = 0; i < 36; i++)
	{
		tempItem[i] = temp[i];
	}
	HANDLE file;
	DWORD write;
	TCHAR saveName[MAX_PATH] = {};
	sprintf(saveName, "save/playerBoxInven.data");
	file = CreateFile(saveName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, tempItem, sizeof(tempItem), &write, NULL);
	CloseHandle(file);
}

void player::saveTile(int i, int j, tagTile tile)
{
	_tile[i][j] = tile;
}

void player::clockRender(HDC hdc)
{
	IMAGEMANAGER->render("�ð�", hdc, 980, 20);

	char dayStr[64];	
	char hourStr[64];
	char minStr[64];
	char yearStr[64];
	char dateStr[64];

	switch (day)
	{
	case MON:
		sprintf(dayStr, "��");
		break;
	case TUE:
		sprintf(dayStr, "ȭ");
		break;
	case WED:
		sprintf(dayStr, "��");
		break;
	case THU:
		sprintf(dayStr, "��");
		break;
	case FRI:
		sprintf(dayStr, "��");
		break;
	case SAT:
		sprintf(dayStr, "��");
		break;
	case SUN:
		sprintf(dayStr, "��");
		break;
	}
	textOut(hdc, 1055, 98, dayStr, RGB(0, 0, 0));

	sprintf(hourStr, "%d", hour);
	sprintf(minStr, ": %d", minute);
	if (!isShowInventory)
	{
		textOut(hdc, 1090, 98, hourStr, RGB(0, 0, 0));
		textOut(hdc, 1110, 98, minStr, RGB(0, 0, 0));
		blinkCount = 0;
	}
	else if (isShowInventory)
	{
		blinkCount++;
		if ((blinkCount / 40) % 2 == 0)
		{
			textOut(hdc, 1090, 98, hourStr, RGB(120, 120, 120));
			textOut(hdc, 1110, 98, minStr, RGB(120, 120, 120));
		}
		else
		{
			textOut(hdc, 1090, 98, hourStr, RGB(0, 0, 0));
			textOut(hdc, 1110, 98, minStr, RGB(0, 0, 0));
		}
	}

	sprintf(yearStr, "%d��", year);
	sprintf(dateStr, "%d��", date);
	textOut(hdc, 1065, 34, yearStr, RGB(0, 0, 0));
	textOut(hdc, 1120, 34, dateStr, RGB(0, 0, 0));
}

void player::moneyRender(HDC hdc)
{
	int i = 0;
	int a;
	int b = money;
	while (b > 0)
	{
		a = b % 10;
		IMAGEMANAGER->frameRender("������", hdc, 1144 - (17 * i), 148, a, 0);

		b /= 10;
		i++;
	}
	if (money <= 0)
	{
		IMAGEMANAGER->frameRender("������", hdc, 1144, 148, 0, 0);
	}

	//�� 0���� ������ 0���� ����
	if (money < 0)
	{
		money = 0;
	}
}

void player::arrowRender(HDC hdc)
{
	hour < 6 ? arrowAngle = 0 : arrowAngle = 18 - (hour - 6);
	/*if (hour < 6)
	{
		arrowAngle = 0;
	}
	else
	{
		arrowAngle = 18 - (hour - 6);
	}*/

	IMAGEMANAGER->frameRender("�ð�ٴ�", hdc, 984, 14, arrowAngle, 0);
}

void player::weatherRender(HDC hdc)
{
	IMAGEMANAGER->frameRender("����", hdc, 1061, 64, 0, currentSeason);
	IMAGEMANAGER->frameRender("����", hdc, 1127, 64, 0, currentWeather);

	if (currentMap != MAP_MINE)
	{
		IMAGEMANAGER->alphaRender("���̵�", hdc, 0, 0, darkAlpha);
	}
}
