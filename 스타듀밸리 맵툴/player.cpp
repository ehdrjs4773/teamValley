#include "stdafx.h"
#include "player.h"

HRESULT player::init()
{
	index = 0;
	count = 0;
	centerX = WINSIZEX / 2;
	centerY = WINSIZEY / 2;

	speed = 2.0f;

	rc = RectMakeCenter(centerX, centerY, 16, 32);

	IMAGEMANAGER->addFrameImage("playerMove", "Images/BMP/playerTemp.bmp", 2000, 1000, 8, 4, true, RGB(255, 0, 255));
	move = IMAGEMANAGER->findImage("playerMove");

	return S_OK;
}

void  player::release()
{
}

void  player::update()
{
	playerMovement();
	playerAnimation(); 
	rc = RectMakeCenter(centerX, centerY, 16, 32);
	//if (_pState == RIGHT && //플레이어의 오른쪽 타일이 나무밑둥 프레임일때 )
	//{
	//	if(_ptInRect(//나무..와 충돌하면  )
	//		{
	//			STATE = cutdownTree; 
	//		}
	//}

	//if (_pState == RIGHT)
	//{
	//	if(//오른쪽 타일이 나무)
	//		{

	//		}

	//		if(//오른쪽 타일이 돌이)
	//			{

	//			}
	//			if (//오른쪽 타일이 잔디)
	//				{

	//				}
	//				if (//오른쪽 타일이 돌)
	//					{

	//					}
	//}
}

void  player::render()
{
	switch (_pDirection)
	{
	case DIRECTION::RIGHT:
		move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 125, centerY - 125, index, 0);
		break;
	case DIRECTION::LEFT:
		move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 125, centerY - 125, index, 1);
		break;
	case DIRECTION::UP:
		move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 125, centerY - 125, index, 2);
		break;
	case DIRECTION::DOWN:
		move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 125, centerY - 125, index, 3);
		break;
	case DIRECTION::IDLE:
		move->frameRender(CAMERAMANAGER->getMemDC(), centerX - 125, centerY - 125, index, 0);
		break;
	}
}

void  player::playerMovement()
{
	if (INPUT->GetKey(VK_RIGHT))  //좌표이동이 아니라 타일이동... 
	{
		centerX += speed;
		_pDirection = RIGHT;
	}
	if (INPUT->GetKey(VK_LEFT))
	{
		centerX -= speed;
		_pDirection = LEFT;
	}
	if (INPUT->GetKey(VK_UP))
	{
		centerY -= speed;
		_pDirection = UP;
	}
	if (INPUT->GetKey(VK_DOWN))
	{
		centerY += speed;
		_pDirection = DOWN;
	}
	if (!INPUT->GetKey(VK_RIGHT) && !INPUT->GetKey(VK_LEFT) && !INPUT->GetKey(VK_UP) && !INPUT->GetKey(VK_DOWN))
	{
		index = 0;
		_pDirection = IDLE;
	}
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
	
}
