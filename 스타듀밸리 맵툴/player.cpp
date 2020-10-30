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

	playerHp = 100.0f;
	playerEnergy = 100.0f;

	MAXHP = 100.0f;
	MAXENERGY = 100.0f;

	totalHpDmg = 0;
	totalEnergyDmg = 0;

	playerFarmingLevel  = playerCombatLevel = 1;
	farmingExp = combatExp = 0;
	MaxFarmingExp = MaxCombatExp = 100;

	speed = 1.5f;

	Damage = 2;

	frontHpBar = RectMakeCenter(WINSIZEX - 95, WINSIZEY - 88, 20, (138 / MAXHP * playerHp));
	frontEnergyBar = RectMakeCenter(WINSIZEX - 55, WINSIZEY - 88, 20, (138 / MAXENERGY * playerEnergy));

	IMAGEMANAGER->addFrameImage("playerMove", "Images/플레이어이미지3.bmp", 576, 2176, 12, 34, true, RGB(255, 0, 255));
	move = IMAGEMANAGER->findImage("playerMove");

	IMAGEMANAGER->addFrameImage("blackholeSword", "Images/마법검/blackholeSword.bmp", 576, 384, 12, 6, true, RGB(255, 0, 255));
	blackholeSword = IMAGEMANAGER->findImage("blackholeSword");

	IMAGEMANAGER->addFrameImage("explosionSword", "Images/마법검/explosionSword.bmp", 576, 384, 12, 6, true, RGB(255, 0, 255));
	explosionSword = IMAGEMANAGER->findImage("explosionSword");

	IMAGEMANAGER->addFrameImage("fireballSword", "Images/마법검/fireballSword.bmp", 576, 384, 12, 6, true, RGB(255, 0, 255));
	fireballSword = IMAGEMANAGER->findImage("fireballSword");

	IMAGEMANAGER->addFrameImage("fireSword", "Images/마법검/fireSword.bmp", 576, 384, 12, 6, true, RGB(255, 0, 255));
	fireSword = IMAGEMANAGER->findImage("fireSword");

	IMAGEMANAGER->addFrameImage("spikeSword", "Images/마법검/spikeSword.bmp", 576, 384, 12, 6, true, RGB(255, 0, 255));
	spikeSword = IMAGEMANAGER->findImage("spikeSword");

	IMAGEMANAGER->addImage("backHpBar", "Images/BMP/backHpBar.bmp", 40, 188, true, RGB(255, 0, 255));
	backHpBar = IMAGEMANAGER->findImage("backHpBar");

	IMAGEMANAGER->addImage("backEnergyBar", "Images/BMP/backEnergyBar.bmp", 40, 188, true, RGB(255, 0, 255));
	playerStorage = IMAGEMANAGER->findImage("플레이어 창고");

	_inventory = new inventory;
	_inventory->init();

	stock = new Stock;
	stock->init();

	_skill = new skill();
	_skill->init();
	stock->addPlayerStock(STOCK_BROWNCOW);
	stock->addPlayerStock(STOCK_BROWNCOW);
	stock->addPlayerStock(STOCK_WHITECOW);
	stock->addPlayerStock(STOCK_WHITECOW);

	currentMap = MAP_HOUSE;

	isShowInventory = false;
	isOpenPlayerStorageCover = false;
	isHit = false;

	_pDirection = DOWN;
	_pState = STAND;

	year = 1;
	hour = 6;
	minute = 0;
	money = 100000;
	currentSeason = SPRING;
	currentWeather = SUNNY;
	date = 1;
	day = MON;
	arrowAngle = 18;
	blinkCount = 0;
	darkAlpha = .0f;
	shopGrade = 3;
	totalSell = 0;
	return S_OK;
}

void  player::release()
{
}

void  player::update()
{
	//cout << MAXENERGY << "\t" << MaxFarmingExp << "\t" << farmingExp << "\t" << dropItemNum << "\t" << playerFarmingLevel << endl;
	//cout << _inventory->getvInven()[1].energyRecover << endl;
	if (INPUT->GetKeyDown(VK_F9))
	{
		//playerEnergy -= 2;
		//totalEnergyDmg += 2;

		playerFarmingLevel++;
		setMaxExp();
	}
	frontHpBar.top = (WINSIZEY - 156 + ((138 / MAXHP) * totalHpDmg));
	frontEnergyBar.top = (WINSIZEY - 156 + ((138 / MAXENERGY) *  totalEnergyDmg));
	
	levelUp();
	//if (!isShowInventory)
	//{
	//	if (INPUT->GetKeyDown(VK_TAB))
	//	{
	//		if (isSkill) isSkill = false;
	//		else {
	//			_inventory->setCurrentSlotNumber(0);
	//			isSkill = true;
	//		}
	//	}
	//}

	if (!isOpenPlayerStorageCover)
	{
		if (!isShowInventory && !isShowSleepingOption)
		{
			if (INPUT->GetKeyDown('E'))
			{
				if (!isShowInventory) SOUNDMANAGER->play("menuopen");
				else SOUNDMANAGER->play("menuclose");

				isShowInventory = true;
				_inventory->setInvenToryMove(true);
				_inventory->setInvenPage(true);
			}
		}
		else if (isShowInventory)
		{
			if (INPUT->GetKeyDown(VK_ESCAPE) || INPUT->GetKeyDown('E'))
			{
				if (!isShowInventory) SOUNDMANAGER->play("menuopen");
				else SOUNDMANAGER->play("menuclose");
				isShowInventory = false;
				_inventory->setInvenToryMove(false);
				_inventory->setInvenPage(false);
				_inventory->setCraftPage(false);
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
		cout << darkAlpha << endl;
	}

	//플레이어 현재 맵 체크
	setCurrentMap();

	//가축 움직임
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

	_inventory->update();

	if (!isShowInventory)
	{
		countTime();
	}
	_inventory->getInventoryCraft()->materialUpdate();

	closePlayerStorageCover();

	limitEnergy();
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
				IMAGEMANAGER->findImage("열매(땅)")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top,
					getCurrentInven()->indexX, getCurrentInven()->indexY);
			}
			else
			{
				IMAGEMANAGER->findImage("씨앗hold")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top,
					getCurrentInven()->indexX, getCurrentInven()->indexY);
			}
		}
		else if (getCurrentInven()->item_kind == ITEM_BOX)
		{
			IMAGEMANAGER->findImage("아이템제작스몰")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top-16,
				getCurrentInven()->indexX, getCurrentInven()->indexY);
			IMAGEMANAGER->findImage("아이템제작스몰")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top,
				getCurrentInven()->indexX, getCurrentInven()->indexY+1);
		}
		else if (getCurrentInven()->item_kind == ITEM_FEEDBUCKET)
		{
			IMAGEMANAGER->findImage("아이템제작스몰")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top - 16,
				getCurrentInven()->indexX, getCurrentInven()->indexY);
			IMAGEMANAGER->findImage("아이템제작스몰")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top,
				getCurrentInven()->indexX, getCurrentInven()->indexY + 1);
		}
		else if (getCurrentInven()->item_kind == ITEM_BEEFARM)
		{
			IMAGEMANAGER->findImage("아이템제작스몰")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top - 16,
				getCurrentInven()->indexX, getCurrentInven()->indexY);
			IMAGEMANAGER->findImage("아이템제작스몰")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top,
				getCurrentInven()->indexX, getCurrentInven()->indexY + 1);
		}
		else if (getCurrentInven()->item_kind == ITEM_SCARECROW)
		{
			IMAGEMANAGER->findImage("아이템제작스몰")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top - 16,
				getCurrentInven()->indexX, getCurrentInven()->indexY);
			IMAGEMANAGER->findImage("아이템제작스몰")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top,
				getCurrentInven()->indexX, getCurrentInven()->indexY + 1);
		}
		else if (getCurrentInven()->item_kind == ITEM_BLASTFURNACE)
		{
			IMAGEMANAGER->findImage("아이템제작스몰")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top - 16,
				getCurrentInven()->indexX, getCurrentInven()->indexY);
			IMAGEMANAGER->findImage("아이템제작스몰")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top,
				getCurrentInven()->indexX, getCurrentInven()->indexY + 1);
		}
		else if (getCurrentInven()->item_kind == ITEM_PICKLEDBARREL)
		{
			IMAGEMANAGER->findImage("아이템제작스몰")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top - 16,
				getCurrentInven()->indexX, getCurrentInven()->indexY);
			IMAGEMANAGER->findImage("아이템제작스몰")->frameRender(hdc, playerHoldItem.left, playerHoldItem.top,
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

	if (SCENEMANAGER->getCurrentSceneName() == "광산화면")
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

void player::recoverHp(int rec)
{
	if (playerHp + rec <= MAXHP)
	{
		playerHp += rec;
		totalHpDmg -= rec / 2;
	}
	else if (playerHp + rec > MAXHP)
	{
		playerHp = MAXHP;
		totalHpDmg = 0;
	}
}

void player::recoverEnergy(int rec)
{
	if (playerEnergy + rec <= MAXENERGY)
	{
		playerEnergy += rec;
		totalEnergyDmg -= rec / 2;
	}
	else if (playerEnergy + rec > MAXENERGY)
	{
		playerEnergy = MAXENERGY;
		totalEnergyDmg = 0;
	}
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
			if (count % aniCountControl == 0)
			{
				index += 1;
				if (index > 5)
				{
					index = 0;
				}
			}
			break;
		case LEFT:
			if (count % aniCountControl == 0)
			{
				index += 1;
				if (index > 5)
				{
					index = 0;
				}
			}
			break;
		case UP:
			if (count % aniCountControl == 0)
			{
				index += 1;
				if (index > 5)
				{
					index = 0;
				}
			}
			break;
		case DOWN:
			if (count % aniCountControl == 0)
			{
				index += 1;
				if (index > 5)
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
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case LEFT:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case UP:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 3)
				{
					_pState = STAND;
				}
			}
			break;
		case DOWN:
			if (count % aniCountControl2 == 0)
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
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case LEFT:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case UP:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 3)
				{
					_pState = STAND;
				}
			}
			break;
		case DOWN:
			if (count % aniCountControl2 == 0)
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
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		case LEFT:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		case UP:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		case DOWN:
			if (count % aniCountControl2 == 0)
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
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case LEFT:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case UP:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case DOWN:
			if (count % aniCountControl2 == 0)
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
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case LEFT:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case UP:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 2)
				{
					_pState = STAND;
				}
			}
			break;
		case DOWN:
			if (count % aniCountControl2 == 0)
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
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case LEFT:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState = STAND;
				}
			}
			break;
		case UP:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 2)
				{
					_pState = STAND;
				}
			}
			break;
		case DOWN:
			if (count % aniCountControl2 == 0)
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
	case P_SKILL_BLACKHOLE:
		
		switch (_pDirection)
		{
		case RIGHT:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		case LEFT:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		case UP:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 2)
				{
					_pState = STAND;
				}
			}
			break;
		case DOWN:
			if (count % aniCountControl2 == 0)
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
	case P_SKILL_EXPLOSION:
		switch (_pDirection)
		{
		case RIGHT:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		case LEFT:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		case UP:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 2)
				{
					_pState = STAND;
				}
			}
			break;
		case DOWN:
			if (count % aniCountControl2 == 0)
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
	case P_SKILL_FIRE_BALL:
		switch (_pDirection)
		{
		case RIGHT:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		case LEFT:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		case UP:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 2)
				{
					_pState = STAND;
				}
			}
			break;
		case DOWN:
			if (count % aniCountControl2 == 0)
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
	case P_SKILL_FIRE:
		switch (_pDirection)
		{
		case RIGHT:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		case LEFT:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		case UP:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 2)
				{
					_pState = STAND;
				}
			}
			break;
		case DOWN:
			if (count % aniCountControl2 == 0)
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
	case P_SKILL_SPIKES:
		switch (_pDirection)
		{
		case RIGHT:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		case LEFT:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 5)
				{
					_pState = STAND;
				}
			}
			break;
		case UP:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 2)
				{
					_pState = STAND;
				}
			}
			break;
		case DOWN:
			if (count % aniCountControl2 == 0)
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
	{
		switch (_pDirection)
		{
		case RIGHT:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 4)
				{
					index = 0;
				}
			}
			break;
		case LEFT:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 4)
				{
					index = 0;
				}
			}
			break;
		case UP:
			if (count % aniCountControl2 == 0)
			{
				index++;
				if (index > 5)
				{
					index = 0;
				}
			}
			break;
		case DOWN:
			if (count % aniCountControl2 == 0)
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
	case P_SKILL_BLACKHOLE:
		switch (_pDirection)
		{
		case RIGHT:
			blackholeSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 1);
			break;
		case LEFT:
			blackholeSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 2);
			break;
		case UP:
			blackholeSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 3);
			break;
		case DOWN:
			blackholeSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 0);
			break;
		}
		break;
	case P_SKILL_EXPLOSION:
		switch (_pDirection)
		{
		case RIGHT:
			explosionSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 1);
			break;
		case LEFT:
			explosionSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 2);
			break;
		case UP:
			explosionSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 3);
			break;
		case DOWN:
			explosionSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 0);
			break;
		}
		break;
	case P_SKILL_FIRE_BALL:
		switch (_pDirection)
		{
		case RIGHT:
			fireballSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 1);
			break;
		case LEFT:
			fireballSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 2);
			break;
		case UP:
			fireballSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 3);
			break;
		case DOWN:
			fireballSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 0);
			break;
		}
		break;
	case P_SKILL_FIRE:
		switch (_pDirection)
		{
		case RIGHT:
			fireSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 1);
			break;
		case LEFT:
			fireSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 2);
			break;
		case UP:
			fireSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 3);
			break;
		case DOWN:
			fireSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 0);
			break;
		}
		break;
	case P_SKILL_SPIKES:
		switch (_pDirection)
		{
		case RIGHT:
			spikeSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 1);
			break;
		case LEFT:
			spikeSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 2);
			break;
		case UP:
			spikeSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 3);
			break;
		case DOWN:
			spikeSword->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 32, index, 0);
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
		break;
	}
}

void player::openPlayerStorageCover()
{
	//플레이어 창고상자
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
				isOpenPlayerStorageCover = false;
				_inventory->setIsShowTemp(false);
				_inventory->setInvenToryMove(false);
			}
		}
	}
}

void player::setCurrentMap()
{
	if (SWITCHMANAGER->getCurrentScene() == "상점씬")
	{
		currentMap = MAP_SHOP;
	}
	else if (SWITCHMANAGER->getCurrentScene() == "인게임화면")
	{
		currentMap = MAP_FARM;
	}
	else if (SWITCHMANAGER->getCurrentScene() == "건물안화면")
	{
		currentMap = MAP_BARN;
	}
	else if (SWITCHMANAGER->getCurrentScene() == "집안화면")
	{
		currentMap = MAP_HOUSE;
	}
	else if (SWITCHMANAGER->getCurrentScene() == "광산화면")
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

void player::resetPlayer()
{
	this->init();
	/*_tile[TILEY][TILEX] = {};
	currentMap = MAP_HOUSE;
	timeCount = 0;
	hour = 0;
	minute = 0;
	date = 0;
	money = 0;
	year = 0;
	blinkCount = 0;
	arrowAngle = 0;
	day = MON;
	currentSeason = SPRING;
	currentWeather = SUNNY;
	speed = darkAlpha = centerY = centerX = .0f;
	currentX = currentY = MouseIndexX = MouseIndexY = count = index = playerEnergy = energyBarX = 0;
	playerHp = hpBarX = Damage = 0;*/
}

bool player::checkFullyGrown(tagTile tile)
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

void player::loadPlayerData()
{
	//플레이어 데이터 리셋
	resetPlayer();

	//플레이어 데이터 불러오기
	date = INIDATA->loadDataInteger("save/playerData", "PLAYER", "date");
	year = INIDATA->loadDataInteger("save/playerData", "PLAYER", "year");
	day = (DAYOFWEEK)INIDATA->loadDataInteger("save/playerData", "PLAYER", "day");
	darkAlpha = INIDATA->loadDataInteger("save/playerData", "PLAYER", "darkAlpha");
	currentSeason = (SEASON)INIDATA->loadDataInteger("save/playerData", "PLAYER", "currentSeason");
	currentWeather = (WEATHER)INIDATA->loadDataInteger("save/playerData", "PLAYER", "currentWeather");
	money = INIDATA->loadDataInteger("save/playerData", "PLAYER", "money");
	playerFarmingLevel = INIDATA->loadDataInteger("save/playerData", "PLAYER", "farmingLV");
	farmingExp = INIDATA->loadDataInteger("save/playerData", "PLAYER", "farmingExp");
	playerCombatLevel = INIDATA->loadDataInteger("save/playerData", "PLAYER", "combatLv");
	combatExp = INIDATA->loadDataInteger("save/playerData", "PLAYER", "combatExp");
	shopGrade = INIDATA->loadDataInteger("save/playerData", "PLAYER", "shopGrade");
	totalSell = INIDATA->loadDataInteger("save/playerData", "PLAYER", "totalSell");
	loadInven();
	loadStock();
	loadBoxInven();

	setMaxExp();
	playerHp = MAXHP;
	playerEnergy = MAXENERGY;
}

void player::loadInven()
{
	//인벤 불러오기
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
	//박스 불러오기
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
	//가축 불러오기
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
	char fLvStr[64],fExpStr[64], cLvStr[64], cExpStr[64], arrShopGrade[64], arrTotalSell[64];
	INIDATA->addData("PLAYER", "date", _itoa(date, dateStr, 10));
	INIDATA->addData("PLAYER", "year", _itoa(year, yearStr, 10));
	INIDATA->addData("PLAYER", "day", _itoa(day, dayStr, 10));
	INIDATA->addData("PLAYER", "darkAlpha", _itoa(darkAlpha, darkStr, 10));
	INIDATA->addData("PLAYER", "currentSeason", _itoa((int)currentSeason, seasonStr, 10));
	INIDATA->addData("PLAYER", "currentWeather", _itoa((int)currentWeather, weatherStr, 10));
	INIDATA->addData("PLAYER", "money", _itoa(money, moneyStr, 10));
	INIDATA->addData("PLAYER", "farmingLv", _itoa(playerFarmingLevel, fLvStr, 10));
	INIDATA->addData("PLAYER", "farmingExp", _itoa(farmingExp, fExpStr, 10));
	INIDATA->addData("PLAYER", "combatLv", _itoa(playerCombatLevel, cLvStr, 10));
	INIDATA->addData("PLAYER", "combatExp", _itoa(combatExp, cExpStr, 10));
	INIDATA->addData("PLAYER", "shopGrade", _itoa(shopGrade, arrShopGrade, 10));
	INIDATA->addData("PLAYER", "totalSell", _itoa(totalSell, arrTotalSell, 10));
	INIDATA->saveINI();
}

void player::savePlayerInven()
{
	resetHpBar();
	resetEnergy();

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
			tempItem[i].hpRecover = 0;
			tempItem[i].energyRecover = 0;
			tempItem[i].grow = 0;
			tempItem[i].exp = 0;
			tempItem[i].grade = 0;

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
			tempItem[i].hpRecover = temp[i].hpRecover;
			tempItem[i].energyRecover = temp[i].energyRecover;
			tempItem[i].grow = temp[i].grow;
			tempItem[i].exp = temp[i].exp;
			tempItem[i].grade = temp[i].grade;

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

	for (int i = 0; i < stock->getStock().size() - 1; i++)
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
					|| _tile[i][j].seedType == SEED_GRAPE
					||_tile[i][j].seedType == SEED_GREENBEAN
					|| _tile[i][j].seedType == SEED_BLUEBERRY
					|| _tile[i][j].seedType == SEED_CORN
					|| _tile[i][j].seedType == SEED_HOPS)
					&& _tile[i][j].objFrameX == 7)
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

				//다자랐는지 확인
				_tile[i][j].isFullyGrown = checkFullyGrown(_tile[i][j]);
			}
		}
	}

	HANDLE file;
	DWORD write;
	TCHAR saveMapName[MAX_PATH] = "save/tomato.map";
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
	IMAGEMANAGER->render("시계", hdc, 980, 20);

	char dayStr[64];	
	char hourStr[64];
	char minStr[64];
	char yearStr[64];
	char dateStr[64];

	switch (day)
	{
	case MON:
		sprintf(dayStr, "월");
		break;
	case TUE:
		sprintf(dayStr, "화");
		break;
	case WED:
		sprintf(dayStr, "수");
		break;
	case THU:
		sprintf(dayStr, "목");
		break;
	case FRI:
		sprintf(dayStr, "금");
		break;
	case SAT:
		sprintf(dayStr, "토");
		break;
	case SUN:
		sprintf(dayStr, "일");
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

	sprintf(yearStr, "%d년", year);
	sprintf(dateStr, "%d일", date);
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
		IMAGEMANAGER->frameRender("돈숫자", hdc, 1144 - (17 * i), 148, a, 0);

		b /= 10;
		i++;
	}
	if (money <= 0)
	{
		IMAGEMANAGER->frameRender("돈숫자", hdc, 1144, 148, 0, 0);
	}

	//돈 0보다 작으면 0으로 고정
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

	IMAGEMANAGER->frameRender("시계바늘", hdc, 984, 14, arrowAngle, 0);
}

void player::weatherRender(HDC hdc)
{
	IMAGEMANAGER->frameRender("날씨", hdc, 1061, 64, 0, currentSeason);
	IMAGEMANAGER->frameRender("계절", hdc, 1127, 64, 0, currentWeather);

	if (currentMap != MAP_MINE)
	{
		IMAGEMANAGER->alphaRender("페이드", hdc, 0, 0, darkAlpha);
	}
}

void player::limitEnergy()
{
	if (playerEnergy <= 20 && playerEnergy > 0)
	{
		speed = 0.5f;
		aniCountControl = 15;
		aniCountControl2 = 10;
	}
	else if (playerEnergy <= 0)
	{
		savePlayerData();
		savePlayerInven();
		savePlayerStock();
		saveMap();
		saveBox();
		SWITCHMANAGER->changeScene("집안화면");
		SWITCHMANAGER->startFade(762.0f, 887.0f);
	}
	else
	{
		speed = 1.5f;
		aniCountControl = 10;
		aniCountControl2 = 5;
	}
}

void player::setMaxExp()
{
	switch (playerFarmingLevel)
	{
	case 1:
		MaxFarmingExp = 100;
		MAXENERGY = 100;
		dropItemNum = 1;
		break;
	case 2:
		MaxFarmingExp = 300;
		MAXENERGY = 110;
		dropItemNum = 1;
		break;		  
	case 3:			  
		MaxFarmingExp = 500;
		MAXENERGY = 120;
		dropItemNum = 1;
		break;		  
	case 4:			  
		MaxFarmingExp = 700;
		MAXENERGY = 130;
		dropItemNum = 1;
		break;		  
	case 5:			  
		MaxFarmingExp = 900;
		MAXENERGY = 140;
		dropItemNum = 2;
		break;		  
	case 6:			  
		MaxFarmingExp = 1100;
		MAXENERGY = 150;
		dropItemNum = 2;
		break;		  
	case 7:			  
		MaxFarmingExp = 1300;
		MAXENERGY = 160;
		dropItemNum = 2;
		break;		  
	case 8:			  
		MaxFarmingExp = 1500;
		MAXENERGY = 170;
		dropItemNum = 2;
		break;		  
	case 9:			  
		MaxFarmingExp = 1700;
		MAXENERGY = 180;
		dropItemNum = 2;
		break;		  
	case 10:		  
		MaxFarmingExp = 1900;
		MAXENERGY = 190;
		dropItemNum = 3;
		break;
	}
	switch (playerCombatLevel)
	{
	case 1:
		MaxCombatExp = 100;
		MAXHP = 100;
		break;
	case 2:
		MaxCombatExp = 300;
		MAXHP = 110;
		break;
	case 3:
		MaxCombatExp = 500;
		MAXHP = 120;
		break;
	case 4:
		MaxCombatExp = 700;
		MAXHP = 130;
		break;
	case 5:
		MaxCombatExp = 900;
		MAXHP = 140;
		break;
	case 6:
		MaxCombatExp = 1100;
		MAXHP = 150;
		break;
	case 7:
		MaxCombatExp = 1300;
		MAXHP = 160;
		break;
	case 8:
		MaxCombatExp = 1500;
		MAXHP = 170;
		break;
	case 9:
		MaxCombatExp = 1700;
		MAXHP = 180;
		break;
	case 10:
		MaxCombatExp = 1900;
		MAXHP = 190;
		break;
	}
}

void player::levelUp()
{
	if (farmingExp >= MaxFarmingExp && playerFarmingLevel < 10)
	{
		playerFarmingLevel += 1;
		farmingExp = 0;
		setMaxExp();
	}
	else if (combatExp >= MaxCombatExp && playerCombatLevel < 10)
	{
		playerCombatLevel += 1;
		combatExp = 0;
		setMaxExp();
	}
}
