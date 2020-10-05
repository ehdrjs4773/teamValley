#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	index = 0;
	count = 0;
	centerX = WINSIZEX / 2;
	centerY = WINSIZEY / 2;

	speed = 2.0f;

	IMAGEMANAGER->addFrameImage("playerMove", "Images/BMP/playerTemp.bmp", 2000, 1000, 8, 4, true, RGB(255, 0, 255));
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

	checkTile();

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



	//switch (_pDirection)
	//{
	//case DIRECTION::RIGHT:
	//	move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 125, centerY - 125, index, 0);
	//	break;
	//case DIRECTION::LEFT:
	//	move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 125, centerY - 125, index, 1);
	//	break;
	//case DIRECTION::UP:
	//	move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 125, centerY - 125, index, 2);
	//	break;
	//case DIRECTION::DOWN:
	//	move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 125, centerY - 125, index, 3);
	//	break;
	//case DIRECTION::IDLE:
	//	move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 125, centerY - 125, index, 0);
	//	break;
	//}
	Rectangle(CAMERAMANAGER->getMemDC(), rc);



}

void player::playerAnimation()
{
	count++;

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

void player::checkTile()
{
	switch (_pDirection)
	{
	case RIGHT:

		if (MouseIndexX== currentX + 1 && MouseIndexY== currentY - 1)  // 마우스 위치가 1번 타일일 때
		{
			switch (_tile[currentY - 1][currentX + 1].objType)
			{







			}
			switch (_tile[currentY - 1][currentX + 1].terrain)
			{
			}
		
		}
		else if (MouseIndexX == currentX + 1 && MouseIndexY == currentY)// 마우스 위치가 2번 타일일 때 
		{
			switch (_tile[currentY][currentX + 1].objType)
			{
			case OTY_TREE:
				if (_pTool == TOOL_AX)
				{
					//나무가 잘림 
				}
				break;
			case OTY_BRANCH:
				if (_pTool == TOOL_AX)
				{
					//나뭇가지가 잘림 
				}
				break;
			case  OTY_GRASS:
				if (_pTool == TOOL_SICKLE)
				{
					//풀이 잘림 
				}
				break;
			case  OTY_STONE:
				if (_pTool == TOOL_PICKAX)
				{
					//돌이 깨짐
				}
				break;
			case  OTY_CROP:
				if (_pTool == TOOL_KETTLE)
				{
					//물을 부음 
				}
				break;
			case  OTY_MONSTER:
				if (_pTool == TOOL_SWORD)
				{
					//몬스터를 공격함
				}
				break;
			}
			switch (_tile[currentY][currentX + 1].terrain)
			{
			case  TR_GROUND:
				if (_pTool == TOOL_HOE)
				{
					//땅을 팜 => TR_HACKED가 됨 
				}
				break;
			case  TR_HACKED:
				if (_pTool == TOOL_KETTLE)
				{
					//물 뿌림 => 땅이 WET 됨 
				}
				break;
			case  TR_WATER:
				if (_pTool == TOOL_KETTLE)
				{
					//물을 채움
				}
				break;
			}
		}
		else if (MouseIndexX == currentX + 1 && MouseIndexY == currentY+1) //마우스 위치가 3번 타일일 때  
		{
			switch (_tile[currentY + 1][currentX + 1].objType)
			{
			}
			switch (_tile[currentY + 1][currentX + 1].terrain)
			{
			}
		}

	case LEFT:
		if (MouseIndexX == currentX - 1 && MouseIndexY == currentY + 1)//마우스 위치가 5번 타일일 때  
		{
			switch (_tile[currentY + 1][currentX - 1].objType)
			{
			}
			switch (_tile[currentY + 1][currentX - 1].terrain)
			{
			}
		}
		else if (MouseIndexX == currentX - 1 && MouseIndexY == currentY)//마우스 위치가 6번 타일일 때
		{
			switch (_tile[currentY][currentX - 1].objType)
			{
			}
			switch (_tile[currentY][currentX - 1].terrain)
			{
			}
		}

		else if (MouseIndexX == currentX - 1 && MouseIndexY == currentY-1)// 마우스 위치가 7번 타일일 때 
		{
			switch (_tile[currentY - 1][currentX - 1].objType)
			{
			}
			switch (_tile[currentY - 1][currentX - 1].terrain)
			{
			}
		}
		break;

	case UP:
		if (MouseIndexX == currentX - 1 && MouseIndexY == currentY - 1)// 마우스 위치가 7번 타일일 때 
		{
			switch (_tile[currentY - 1][currentX - 1].objType)
			{
			}
			switch (_tile[currentY - 1][currentX - 1].terrain)
			{
			}
		}
		else if (MouseIndexX == currentX && MouseIndexY == currentY - 1)// 마우스 위치가 8번 타일일 때 
		{
			switch (_tile[currentY - 1][currentX].objType)
			{
			}
			switch (_tile[currentY - 1][currentX].terrain)
			{
			}
		}
		else if (MouseIndexX == currentX + 1 && MouseIndexY == currentY - 1)// 마우스 위치가 1번 타일일 때 
		{
			switch (_tile[currentY - 1][currentX + 1].objType)
			{
			}
			switch (_tile[currentY - 1][currentX + 1].terrain)
			{
			}
		}
		break;

	case DOWN:
		if (MouseIndexX == currentX + 1 && MouseIndexY == currentY + 1)// 마우스 위치가 3번 타일일 때 
		{
			switch (_tile[currentY + 1][currentX + 1].objType)
			{
			}
			switch (_tile[currentY + 1][currentX + 1].terrain)
			{
			}
		}
		else if (MouseIndexX == currentX && MouseIndexY == currentY + 1)// 마우스 위치가 4번 타일일 때 
		{
			switch (_tile[currentY + 1][currentX].objType)
			{
			}
			switch (_tile[currentY + 1][currentX].terrain)
			{
			}
		}
		else if (MouseIndexX == currentX - 1 && MouseIndexY == currentY + 1)// 마우스 위치가 5번 타일일 때 
		{
			switch (_tile[currentY + 1][currentX - 1].objType)
			{
			}
			switch (_tile[currentY + 1][currentX - 1].terrain)
			{
			}
		}
		break;
	}
}