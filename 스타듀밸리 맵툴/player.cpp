#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	index = 0;
	count = 0;
	centerX = WINSIZEX / 2;
	centerY = WINSIZEY / 2;

	currentX = centerX / 16;
	currentY = (centerY + 8) / 16;

	playerHoldItem = RectMakeCenter(centerX - 8, centerY - 48, 16, 16);

	playerHp = 276;
	Damage= 2;

	boxIndex = 0;
	boxCount = 0;
	isOpenPlayerInvenCover = false;

	frontHpBar = RectMakeCenter(WINSIZEX - 55, WINSIZEY - 88, 20, 138);

	speed = 1.5f;

	IMAGEMANAGER->addFrameImage("playerMove", "Images/플레이어이미지2.bmp", 576, 2176, 12, 34, true, RGB(255, 0, 255));
	move = IMAGEMANAGER->findImage("playerMove");

	IMAGEMANAGER->addImage("backHpBar", "Images/BMP/backHpBar.bmp", 40, 188, true, RGB(255, 0, 255));
	backHpBar = IMAGEMANAGER->findImage("backHpBar");



	playerStorage = IMAGEMANAGER->findImage("플레이어 창고");

	_inventory = new inventory;
	_inventory->init();

	stock = new Stock;
	stock->init();
	stock->addPlayerStock(STOCK_BROWNCOW);
	stock->addPlayerStock(STOCK_WHITECOW);
	stock->addPlayerStock(STOCK_BROWNCHICKEN);
	stock->addPlayerStock(STOCK_WHITECHICKEN);

	currentMap = MAP_FARM;

	isShowInventory = false;

	isOpenPlayerStorageCover = false;

	_pDirection = DOWN;
	_pState = STAND;

	year = 1;
	hour = 6;
	minute = 0;
	money = 500;
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

	if (INPUT->GetKeyDown('E'))
	{
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
		cout << darkAlpha << endl;
	}

	//플레이어 현재 맵 체크
	setCurrentMap();

	//가축 움직임
	stock->update();

	currentX = centerX / 16;
	currentY = (centerY + 8) / 16;

	playerAnimation();

	MouseIndexX = (float)((float)CAMERAMANAGER->getX() / 16) + (float)((float)_ptMouse.x / 40);
	MouseIndexY = (float)((float)CAMERAMANAGER->getY() / 16) + (float)((float)_ptMouse.y / 40);

	


	//rc = RectMakeCenter(centerX, centerY, 16, 32);
	_inventory->update();
	playerInvenCoverAnimation();

	if (!isShowInventory)
	{
		countTime();
		
	}


}

void player::render()
{
	playerRender();

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
	}
	
	//Rectangle(hdc, playerHoldItem);
}


void player::playerStatusRender(HDC hdc)
{
	InventoryRender(hdc);
	hpBarRender(hdc);
	clockRender(hdc);
	moneyRender(hdc);
	arrowRender(hdc);
	weatherRender(hdc);
}

void player::InventoryRender(HDC hdc)
{
	if (isShowInventory)
	{
		_inventory->render(hdc);
		_inventory->inven_item_info(hdc);
	}
	else {
		_inventory->quickSlot(hdc);
		_inventory->quickinven_item_info(hdc);
	}
	//Rectangle(CAMERAMANAGER->getMemDC(), rc);

	if (isOpenPlayerStorageCover)
	{
		_inventory->renderStorageInventory(hdc);
		_inventory->storage_item_info(hdc);
		_inventory->inven_item_info(hdc);
	}
}

void player::hpBarRender(HDC hdc)
{
	int a = 0 + (278 - playerHp);

	IMAGEMANAGER->render("backHpBar", hdc, WINSIZEX - 75, WINSIZEY - 200);
	Rectangle(hdc, frontHpBar);
	brush = CreateSolidBrush(RGB(a, 220, 7));
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



void player::playerInvenAnimation()
{
	boxCount++;
	if (boxCount % 8 == 0)
	{
		boxIndex++;
		if (boxIndex > 2)
		{
			boxIndex = 0;
		}
	}
}

void player::playerInvenCoverAnimation()
{
	if (isOpenPlayerInvenCover)
	{
		boxCount++;
		if (boxCount % 5 == 0)
		{
			boxIndex++;
			if (boxIndex > 12)
			{
				boxIndex = 12;
			}
		}
	}
	else if (!isOpenPlayerInvenCover)
	{
		boxCount++;
		if (boxCount % 5 == 0)
		{
			boxIndex--;
			if (boxIndex < 0)
			{
				boxIndex = 0;
			}
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

void player::openPlayerInvenCover()
{
	//플레이어 보유 아이템 판매상자
	if(MouseIndexX >=30 && MouseIndexX <=32 && MouseIndexY>=15 && MouseIndexY<=16)
	{
		isOpenPlayerInvenCover = false;
	}
}

void player::openPlayerStorageCover()
{
	//플레이어 창고상자
	if (isOpenPlayerStorageCover)
	{
		_inventory->setIsShowTemp(false);
		isOpenPlayerStorageCover = false;
	}
	else
	{
		_inventory->setIsShowTemp(true);
		isOpenPlayerStorageCover = true;
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
