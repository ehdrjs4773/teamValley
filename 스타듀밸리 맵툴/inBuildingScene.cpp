#include "stdafx.h"
#include "inBuildingScene.h"

HRESULT inBuildingScene::init()
{
	CAMERAMANAGER->init(TILEX * TILESIZE, TILEY * TILESIZE, 30 * 16, 15 * 16);
	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());

	this->update();

	return S_OK;
}

void inBuildingScene::release()
{
}

void inBuildingScene::update()
{
	PLAYER->update();
	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());
	playerMove();
}

void inBuildingScene::render()
{
	IMAGEMANAGER->render("큰외양간", CAMERAMANAGER->getMemDC());

	PLAYER->render();

	CAMERAMANAGER->render(getMemDC());

	PLAYER->playerStatusRender(getMemDC());
}

void inBuildingScene::playerMove()
{
	if (INPUT->GetKey('W'))
	{
		if (GetPixel(IMAGEMANAGER->findImage("큰외양간 충돌")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY()) != RGB(255, 0, 0))
		{
			if (!SOUNDMANAGER->isPlaySound("movewood"))
			{
				SOUNDMANAGER->play("movewood", 0.2f);
			}
			PLAYER->setDirection(UP);
			PLAYER->setState(RUN);
			PLAYER->setCenterY(PLAYER->getCenterY() - PLAYER->getSpeed());
		}
	}
	if (INPUT->GetKey('S'))
	{
		if (GetPixel(IMAGEMANAGER->findImage("큰외양간 충돌")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY() + 16) != RGB(255, 0, 0))
		{
			if (!SOUNDMANAGER->isPlaySound("movewood"))
			{
				SOUNDMANAGER->play("movewood", 0.2f);
			}
			PLAYER->setDirection(DOWN);
			PLAYER->setState(RUN);
			PLAYER->setCenterY(PLAYER->getCenterY() + PLAYER->getSpeed());
		}
		if (GetPixel(IMAGEMANAGER->findImage("큰외양간 충돌")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY() + 16) == RGB(0, 0, 255))
		{
			if (!SWITCHMANAGER->getFade())
			{
				SWITCHMANAGER->changeScene("인게임화면");
				SWITCHMANAGER->startFade(592.0f, 1120.0f);
			}
		}
	}
	if (INPUT->GetKey('A'))
	{
		if (GetPixel(IMAGEMANAGER->findImage("큰외양간 충돌")->getMemDC(), PLAYER->getCenterX() - 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
		{
			if (!SOUNDMANAGER->isPlaySound("movewood"))
			{
				SOUNDMANAGER->play("movewood", 0.2f);
			}
			PLAYER->setDirection(LEFT);
			PLAYER->setState(RUN);
			PLAYER->setCenterX(PLAYER->getCenterX() - PLAYER->getSpeed());
		}
	}
	if (INPUT->GetKey('D'))
	{
		if (GetPixel(IMAGEMANAGER->findImage("큰외양간 충돌")->getMemDC(), PLAYER->getCenterX() + 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
		{
			if (!SOUNDMANAGER->isPlaySound("movewood"))
			{
				SOUNDMANAGER->play("movewood", 0.2f);
			}
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
