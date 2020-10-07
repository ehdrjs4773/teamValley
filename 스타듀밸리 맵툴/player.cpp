#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	index = 0;
	count = 0;
	centerX = WINSIZEX / 2;
	centerY = WINSIZEY / 2;

	speed = 2.0f;

	IMAGEMANAGER->addFrameImage("playerMove", "Images/플레이어이미지.bmp", 576, 1632, 12, 34, true, RGB(255, 0, 255));
	move = IMAGEMANAGER->findImage("playerMove");

	IMAGEMANAGER->addFrameImage("playerState", "Images/BMP/playerState.bmp", 3000, 4250, 12, 17, true, RGB(255, 0, 255));
	state = IMAGEMANAGER->findImage("playerState");

	_inventory = new inventory;
	_inventory->init();

	isShowInventory = false;

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
		_inventory->update();
		if (isShowInventory) isShowInventory = false;
		else isShowInventory = true;
	}
}

void  player::render()
{
	playerRender();
}

void player::InventroyRender(HDC hdc)
{
	if (isShowInventory)
	{
		_inventory->render(hdc);
	}
	else _inventory->quickSlot(hdc);
	//Rectangle(CAMERAMANAGER->getMemDC(), rc);
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
					_pState == STAND;
				}
			}
			break;
		case LEFT:
			if (count % 5 == 0)
			{
				index++;
				if (index > 4)
				{
					_pState == STAND;
				}
			}
			break;
		case UP:
			if (count % 5 == 0)
			{
				index++;
				if (index > 2)
				{
					_pState == STAND;
				}
			}
			break;
		case DOWN:
			if (count % 5 == 0)
			{
				index++;
				if (index > 11)
				{
					_pState == STAND;
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