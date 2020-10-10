#include "stdafx.h"
#include "inBuildingScene.h"

HRESULT inBuildingScene::init()
{
	PLAYER->setCenterX(370.0f);
	PLAYER->setCenterY(550.0f);
	CAMERAMANAGER->init(600, 500, 600, 300);
	
	return S_OK;
}

void inBuildingScene::release()
{
}

void inBuildingScene::update()
{
	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());
	playerMove();
	PLAYER->playerAnimation();

}

void inBuildingScene::render()
{
	IMAGEMANAGER->render("큰외양간", CAMERAMANAGER->getMemDC());
	
	PLAYER->render();

	CAMERAMANAGER->render(getMemDC());

	PLAYER->InventroyRender(getMemDC());
	PLAYER->hpBarRender(getMemDC());
}

void inBuildingScene::playerMove()
{
	if (INPUT->GetKey('W'))
	{
		PLAYER->setDirection(UP);
		PLAYER->setState(RUN);
		PLAYER->setCenterY(PLAYER->getCenterY() - PLAYER->getSpeed());
	}
	if (INPUT->GetKey('S'))
	{
		PLAYER->setDirection(DOWN);
		PLAYER->setState(RUN);
		PLAYER->setCenterY(PLAYER->getCenterY() + PLAYER->getSpeed());
	}
	if (INPUT->GetKey('A'))
	{
		PLAYER->setDirection(LEFT);
		PLAYER->setState(RUN);
		PLAYER->setCenterX(PLAYER->getCenterX() - PLAYER->getSpeed());
	}
	if (INPUT->GetKey('D'))
	{
		PLAYER->setDirection(RIGHT);
		PLAYER->setState(RUN);
		PLAYER->setCenterX(PLAYER->getCenterX() + PLAYER->getSpeed());
	}
	if (!(INPUT->GetKey('W')) && !(INPUT->GetKey('S')) && !(INPUT->GetKey('A')) && !(INPUT->GetKey('D')))
	{
		PLAYER->setState(STAND);
	}
}
