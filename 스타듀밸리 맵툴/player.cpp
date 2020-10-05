#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	index = 0;
	count = 0;
	centerX = WINSIZEX / 2;
	centerY = WINSIZEY / 2;

	speed = 2.0f;

	IMAGEMANAGER->addFrameImage("playerMove", "Images/플레이어이미지.bmp", 576, 816, 12, 17, true, RGB(255, 0, 255));
	move = IMAGEMANAGER->findImage("playerMove");

	IMAGEMANAGER->addFrameImage("playerState", "Images/BMP/playerState.bmp", 3000, 4250, 12, 17, true, RGB(255, 0, 255));
	state = IMAGEMANAGER->findImage("playerState");

	_inventory = new inventory;
	_inventory->init();

	isShowInventory = false;

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


	rc = RectMakeCenter(centerX, centerY, 48, 32);

	if (INPUT->GetKeyDown('E'))
	{
		_inventory->update();
		if (isShowInventory) isShowInventory = false;
		else isShowInventory = true;
	}
}

void player::InventroyRender(HDC hdc)
{
	if (isShowInventory)
	{

		_inventory->render(hdc);
	}

	else _inventory->quickSlot(hdc);
}

void  player::render()
{

	//switch (_pState)
	//{
	//case STATE::digGround:
	//	move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 125, centerY - 125, index, 4);
	//	break;
	//case STATE::cutdownTree:
	//	move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 125, centerY - 125, index, 0);
	//	break;
	//case STATE::cutGrass:
	//	move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 125, centerY - 125, index, 7);
	//	break;
	//case STATE::breakStone:
	//	move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 125, centerY - 125, index, 13);
	//	break;
	//case STATE::fillWater:
	//	move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 125, centerY - 125, index, 11);
	//	break;
	//case STATE::attackMonster:
	//	move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 125, centerY - 125, index, 12);
	//	break;
	//}

	//Rectangle(CAMERAMANAGER->getMemDC(), rc);

	switch (_pState)
	{
	case STAND:
		switch (_pDirection)
		{
		case RIGHT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 24, index, 0);
			break;
		case LEFT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 24, index, 1);
			break;
		case UP:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 24, index, 2);
			break;
		case DOWN:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 24, index, 3);
			break;
		}
	case RUN:
		switch (_pDirection)
		{
		case RIGHT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 24, index, 0);
			break;
		case LEFT:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 24, index, 1);
			break;
		case UP:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 24, index, 2);
			break;
		case DOWN:
			move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 24, centerY - 24, index, 3);
			break;
		}
	}
}

void player::playerAnimation()
{
	count++;

	switch (_pState)
	{
	case RUN:
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
	}
	
	


	/*switch (_pState)
	{
	case digGround:
		if (count % 5 == 0)
		{
			index++;
			if (index > 4)
			{
				index = 0;
			}
		}
		break;
	case cutdownTree:
		if (count % 5 == 0)
		{
			index++;
			if (index > 5)
			{
				index = 0;
			}
		}
		break;
	case cutGrass:
		if (count % 5 == 0)
		{
			index++;
			if (index > 5)
			{
				index = 0;
			}
		}
		break;

	case breakStone:
		if (count % 5 == 0)
		{
			index++;
			if (index > 6)
			{
				index = 0;
			}
		}
		break;

	case fillWater:
		if (count % 5 == 0)
		{
			index++;
			if (index > 4)
			{
				index = 0;
			}
		}
		break;

	case attackMonster:
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
			*/
}