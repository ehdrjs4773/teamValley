#include "stdafx.h"
#include "inHouseScene.h"

HRESULT inHouseScene::init()
{
	CAMERAMANAGER->init(TILEX * TILESIZE, TILEY * TILESIZE, 30 * 16, 15 * 16);
	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());

	yesBox = RectMakeCenter(WINSIZEX/2, WINSIZEY-240, 910, 60);
	noBox = RectMakeCenter(WINSIZEX/2, WINSIZEY-180 , 910, 60);

	isShowSleepingOption = false;
	checkCount = 0;

	this->update();
	return S_OK;
}

void inHouseScene::release()
{
}

void inHouseScene::update()
{
	if (PLAYER->getCenterY() >= 888.0f)
	{
		if (!SWITCHMANAGER->getFade())
		{
			SWITCHMANAGER->changeScene("인게임화면");
			SWITCHMANAGER->startFade(416.0f, 912.0f); // 플레이어가 인게임에서 호출될 장소 
		}
	}

	PLAYER->update();
	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());
	playerMove();
	PLAYER->playerAnimation();

	cout << _ptMouse.x << " " << _ptMouse.y << endl;
	cout << PLAYER->getCenterX() << " " << PLAYER->getCenterY() << endl;
	cout<<endl;
}

void inHouseScene::render()
{
	IMAGEMANAGER->render("아침 집", CAMERAMANAGER->getMemDC());
	PLAYER->render();

	IMAGEMANAGER->render("플레이어 이불덮기", CAMERAMANAGER->getMemDC());
	CAMERAMANAGER->render(getMemDC());

	PLAYER->InventroyRender(getMemDC());
	PLAYER->hpBarRender(getMemDC());

	if (PLAYER->getCenterX() >= 855.0f && PLAYER->getCenterX() <= 880.0f && PLAYER->getCenterY() >= 855.0f && PLAYER->getCenterY() <= 880.0f)
	{
		if (isShowSleepingOption)
		{
			IMAGEMANAGER->render("자는옵션", getMemDC(), 116, WINSIZEY - 374);

			if (PtInRect(&noBox, _ptMouse))
			{
				RECT temp{ noBox.left,noBox.top,noBox.right,noBox.bottom };
				FrameRect(getMemDC(), temp, RGB(255, 0, 0));

				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					isShowSleepingOption = false;
				}
			}
			if (PtInRect(&yesBox, _ptMouse))
			{
				RECT temp{ yesBox.left,yesBox.top,yesBox.right,yesBox.bottom };
				FrameRect(getMemDC(), temp, RGB(255, 0, 0));

				if (PtInRect(&yesBox, _ptMouse))
				{
					if (INPUT->GetKeyDown(VK_LBUTTON))
					{
						if (!SWITCHMANAGER->getFade())
						{
							SWITCHMANAGER->startFade(855.0f, 865.0f);
						}
						isShowSleepingOption = false;
					}
				}
			}
		}
		else if (!isShowSleepingOption)
		{
			if (checkCount == 0 || INPUT->GetKeyDown(VK_LBUTTON))
			{
				isShowSleepingOption = true;
			}
		}
		checkCount++;
	}
	else
	{
		checkCount = 0;
	}
	//Rectangle(getMemDC(), yesBox);
	//Rectangle(getMemDC(), noBox);
}

void inHouseScene::playerMove()
{
	if (INPUT->GetKey('W'))
	{
		if (GetPixel(IMAGEMANAGER->findImage("아침 집 충돌")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY()) != RGB(255, 0, 0))
		{
			PLAYER->setDirection(UP);
			PLAYER->setState(RUN);
			PLAYER->setCenterY(PLAYER->getCenterY() - PLAYER->getSpeed());
		}
	}
	if (INPUT->GetKey('S'))
	{
		if (GetPixel(IMAGEMANAGER->findImage("아침 집 충돌")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY() + 16) != RGB(255, 0, 0))
		{
			PLAYER->setDirection(DOWN);
			PLAYER->setState(RUN);
			PLAYER->setCenterY(PLAYER->getCenterY() + PLAYER->getSpeed());
		}
		if (GetPixel(IMAGEMANAGER->findImage("아침 집 충돌")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY() + 16) == RGB(0, 0, 255))
		{
			if (!SWITCHMANAGER->getFade())
			{
				SWITCHMANAGER->changeScene("인게임화면");
				SWITCHMANAGER->startFade(416.0f, 912.0f); // 플레이어가 인게임에서 호출될 장소 
			}
		}
	}
	if (INPUT->GetKey('A'))
	{
		if (GetPixel(IMAGEMANAGER->findImage("아침 집 충돌")->getMemDC(), PLAYER->getCenterX() - 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
		{
			PLAYER->setDirection(LEFT);
			PLAYER->setState(RUN);
			PLAYER->setCenterX(PLAYER->getCenterX() - PLAYER->getSpeed());
		}
	}
	if (INPUT->GetKey('D'))
	{
		if (GetPixel(IMAGEMANAGER->findImage("아침 집 충돌")->getMemDC(), PLAYER->getCenterX() + 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
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
