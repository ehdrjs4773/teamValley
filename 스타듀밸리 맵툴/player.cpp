#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	index = 0;
	count = 0;
	centerX = WINSIZEX / 2;
	centerY = WINSIZEY / 2;
	playerHp = 276;
	pickaxDamage,axDamage,hoeDamage = 2;

	boxIndex = 0;
	boxCount = 0;
	isOpenPlayerInvenCover = false;
	

	frontHpBar = RectMakeCenter(WINSIZEX - 55, WINSIZEY - 88, 20, 138);

	speed = 2.0f;

	IMAGEMANAGER->addFrameImage("playerMove", "Images/플레이어이미지2.bmp", 576, 2176, 12, 34, true, RGB(255, 0, 255));
	move = IMAGEMANAGER->findImage("playerMove");

	IMAGEMANAGER->addImage("backHpBar", "Images/BMP/backHpBar.bmp", 40, 188, true, RGB(255, 0, 255));
	backHpBar = IMAGEMANAGER->findImage("backHpBar");

	IMAGEMANAGER->addFrameImage("플레이어 개인상점", "Images/inventory/playerInven.bmp", 144, 29, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플레이어 상점뚜껑", "Images/inventory/playerInvenCover.bmp", 624, 32, 13, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("플레이어 창고", "Images/inventory/playerStorage.bmp",650, 430, true, RGB(255, 0, 255));
	playerStorage = IMAGEMANAGER->findImage("플레이어 창고");

	_inventory = new inventory;
	_inventory->init();

	isShowInventory = false;
	isOpenPlayerStorageCover = false;

	_pDirection = DOWN;
	_pState = STAND;

	return S_OK;
}

void  player::release()
{
}

void  player::update()
{
	playerAnimation();

	currentX = centerX / 16;
	currentY = (centerY + 8) / 16;

	MouseIndexX = (float)((float)CAMERAMANAGER->getX() / 16) + (float)((float)_ptMouse.x / 40);
	MouseIndexY = (float)((float)CAMERAMANAGER->getY() / 16) + (float)((float)_ptMouse.y / 40);

	rc = RectMakeCenter(centerX, centerY, 16, 32);

	if (INPUT->GetKeyDown('E'))
	{
		
		if (isShowInventory)
		{
			isShowInventory = false;
			_inventory->setInvenToryMove(false);
			_inventory->_vItemUpdate();
		}
		else
		{	
			_inventory->setInvenToryMove(true);
			isShowInventory = true;
		}
	}




	playerInvenCoverAnimation();


	//cout << MouseIndexX<<" "<< MouseIndexY <<" "<< isOpenPlayerInvenCover<< endl;
	cout << _ptMouse.x << " " << _ptMouse.y << endl;
}

void player::render()
{
	playerRender();
}

void player::InventroyRender(HDC hdc)
{
	if(isShowInventory)
	{
		_inventory->render(hdc);
	}
	else _inventory->quickSlot(hdc);
	//Rectangle(CAMERAMANAGER->getMemDC(), rc);

	if (isOpenPlayerInvenCover)
	{
		_inventory->renderSellingInventory(hdc);
	}

	if (isOpenPlayerStorageCover)
	{
		_inventory->renderStorageInventory(hdc);
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

		/*case ATTACK:
			switch (_pDirection)
			{
			case RIGHT:
				if (count % 5 == 0)
				{
					index++;
					if (index > 5)
					{
						index = 0;
					}
				}
				break;
			case LEFT:
				if (count % 5 == 0)
				{
					index++;
					if (index > 5)
					{
						index = 0;
					}
				}
				break;
			case UP:
				if (count % 5 == 0)
				{
					index++;
					if (index > 7)
					{
						index = 0;
					}
				}
				break;
			case DOWN:
				if (count % 5 == 0)
				{
					index++;
					if (index > 6)
					{
						index = 0;
					}
				}
				break;
			}
			break;*/
	}
}

void player::drawPlayerInven(tagTile tile1, tagTile tile2)
{
	IMAGEMANAGER->frameRender("플레이어 개인상점", CAMERAMANAGER->getMemDC(), tile1.rc.left, tile1.rc.top, boxIndex, 0);
	IMAGEMANAGER->frameRender("플레이어 상점뚜껑", CAMERAMANAGER->getMemDC(), tile2.rc.left, tile2.rc.top, boxIndex, 0);
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
	
	}


}

void player::openPlayerInvenCover()
{
	//플레이어 보유 아이템 판매상자

	if(MouseIndexX >=30 && MouseIndexX <=32 && MouseIndexY>=15 && MouseIndexY<=16)
	{
		if(isOpenPlayerInvenCover) isOpenPlayerInvenCover = false;
		else isOpenPlayerInvenCover = true;
	}
}

void player::openPlayerStorageCover()
{
	//플레이어 창고상자
	if (MouseIndexX >= 25 && MouseIndexX <= 26 && MouseIndexY >= 18 && MouseIndexY <= 19)
	{
		if (isOpenPlayerStorageCover) isOpenPlayerStorageCover = false;
		else isOpenPlayerStorageCover = true;
		//_inventory->_vItemUpdate();
	}
}