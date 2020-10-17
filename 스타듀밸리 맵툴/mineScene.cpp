#include "stdafx.h"
#include "mineScene.h"

HRESULT mineScene::init()
{
	CAMERAMANAGER->init(TILEX * TILESIZE, TILEY * TILESIZE, 30 * 16, 15 * 16);
	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());

	currentFloor = 1;

	return S_OK;
}

void mineScene::release()
{
}

void mineScene::update()
{
	PLAYER->update();
	PLAYER->playerAnimation();
}

void mineScene::render()
{
	PLAYER->render();

	CAMERAMANAGER->render(getMemDC());


	PLAYER->playerStatusRender(getMemDC());
}

void mineScene::playerMove()
{
	if (INPUT->GetKey('W'))
	{
		if (GetPixel(IMAGEMANAGER->findImage("큰외양간 충돌")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY()) != RGB(255, 0, 0))
		{
			PLAYER->setDirection(UP);
			PLAYER->setState(RUN);
			PLAYER->setCenterY(PLAYER->getCenterY() - PLAYER->getSpeed());
		}
	}
	if (INPUT->GetKey('S'))
	{
		if (GetPixel(IMAGEMANAGER->findImage("큰외양간 충돌")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY() + 16) != RGB(255, 0, 0))
		{
			PLAYER->setDirection(DOWN);
			PLAYER->setState(RUN);
			PLAYER->setCenterY(PLAYER->getCenterY() + PLAYER->getSpeed());
		}
	}
	if (INPUT->GetKey('A'))
	{
		if (GetPixel(IMAGEMANAGER->findImage("큰외양간 충돌")->getMemDC(), PLAYER->getCenterX() - 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
		{
			PLAYER->setDirection(LEFT);
			PLAYER->setState(RUN);
			PLAYER->setCenterX(PLAYER->getCenterX() - PLAYER->getSpeed());
		}
	}
	if (INPUT->GetKey('D'))
	{
		if (GetPixel(IMAGEMANAGER->findImage("큰외양간 충돌")->getMemDC(), PLAYER->getCenterX() + 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
		{
			PLAYER->setDirection(RIGHT);
			PLAYER->setState(RUN);
			PLAYER->setCenterX(PLAYER->getCenterX() + PLAYER->getSpeed());
		}
	}
	if (!(INPUT->GetKey('W')) && !(INPUT->GetKey('S')) && !(INPUT->GetKey('A')) && !(INPUT->GetKey('D')))
	{
		PLAYER->setState(STAND);
	}
}

void mineScene::setRandomObstacles()
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (_tile[i][j].obj != OBJ_NONE) { continue; }
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
					
					break;
				case 2:
					
					break;
				case 3:
					
					break;
				case 4:
					
					break;
				case 5:

					break;
				}
			}
		}
	}
}
