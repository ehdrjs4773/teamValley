#include "stdafx.h"
#include "inBuildingScene.h"

HRESULT inBuildingScene::init()
{
	PLAYER->setCenterX(780.0f);
	PLAYER->setCenterY(890.0f);
	CAMERAMANAGER->init(TILEX * TILESIZE, TILEY * TILESIZE, 30 * 16, 15 * 16);

	return S_OK;
}

void inBuildingScene::release()
{
}

void inBuildingScene::update()
{
	PLAYER->fade();
	PLAYER->update();
	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());
	playerMove();
	PLAYER->playerAnimation();

	if (PLAYER->getFade("FadeOut"))
	{
		if (PLAYER->getAlpha() >= 255)
		{
			PLAYER->setCenterX(96.0f);
			PLAYER->setCenterY(20.0f);
			SCENEMANAGER->loadScene("인게임화면");
		}
	}
}

void inBuildingScene::render()
{
	IMAGEMANAGER->render("큰외양간", CAMERAMANAGER->getMemDC());

	PLAYER->render();

	CAMERAMANAGER->render(getMemDC());

	PLAYER->InventroyRender(getMemDC());
	PLAYER->hpBarRender(getMemDC());

	PLAYER->renderFade(getMemDC());
}

void inBuildingScene::playerMove()
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
		if (GetPixel(IMAGEMANAGER->findImage("큰외양간 충돌")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY() + 16) == RGB(0, 0, 255))
		{
			PLAYER->setFade("FadeOut", true);
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
