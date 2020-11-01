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
	
	SOUNDMANAGER->stop("메인음악");

	this->update();
	return S_OK;
}

void inHouseScene::release()
{
}

void inHouseScene::update()
{
	if (!SOUNDMANAGER->isPlaySound("springDay"))
	{
		SOUNDMANAGER->play("springDay", 0.2f);
	}
	if (PLAYER->getCenterY() >= 888.0f)
	{
		if (!SWITCHMANAGER->getFade())
		{
			SOUNDMANAGER->play("doorOpen", 0.2f);
			SWITCHMANAGER->changeScene("인게임화면");
			//SWITCHMANAGER->startFade(376.0f, 472.0f); // 플레이어가 인게임에서 호출될 장소 
			//SWITCHMANAGER->startFade(650.0f, 192.0f); // 상점 디버그용 
			SWITCHMANAGER->startFade(208.0f, 208.0f); // 성 디버그용 

		}
	}

	PLAYER->update();

	CAMERAMANAGER->cameraMove(PLAYER->getCenterX(), PLAYER->getCenterY());
	playerMove();
	PLAYER->playerAnimation();

	//cout << _ptMouse.x << " " << _ptMouse.y << endl;
	//cout << PLAYER->getCenterX() << " " << PLAYER->getCenterY() << endl;
	//cout<<endl;
	
	blanket();
}

void inHouseScene::render()
{
	IMAGEMANAGER->render("아침 집", CAMERAMANAGER->getMemDC());
	PLAYER->render();

	IMAGEMANAGER->render("플레이어 이불덮기", CAMERAMANAGER->getMemDC());
	CAMERAMANAGER->render(getMemDC());

	PLAYER->playerStatusRender(getMemDC());

	if (PLAYER->getCenterX() >= 855.0f && 
		PLAYER->getCenterX() <= 880.0f && 
		PLAYER->getCenterY() >= 855.0f && 
		PLAYER->getCenterY() <= 880.0f)
	{
		if (!PLAYER->getIsShowInventory()) //인벤토리가 안떠있을때 
		{
			if (isShowSleepingOption)
			{
				IMAGEMANAGER->render("자는옵션", getMemDC(), 116, WINSIZEY - 374);

				if (PtInRect(&noBox, _ptMouse)) //아니요에 닿으면 
				{
					IMAGEMANAGER->render("자는옵션아니요", getMemDC(), 116, WINSIZEY - 374);
					RECT temp{ noBox.left,noBox.top,noBox.right,noBox.bottom };
					FrameRect(getMemDC(), temp, RGB(255, 0, 0));
				}
				if (PtInRect(&yesBox, _ptMouse))
				{
					IMAGEMANAGER->render("자는옵션네", getMemDC(), 116, WINSIZEY - 374);
					RECT temp{ yesBox.left,yesBox.top,yesBox.right,yesBox.bottom };
					FrameRect(getMemDC(), temp, RGB(255, 0, 0));
				}
			}
		}
	}
}

void inHouseScene::playerMove()
{
	if (!PLAYER->getIsShowInventory()) //인벤토리가 안떠있을때 
	{
		if (INPUT->GetKey('W'))
		{
			if (GetPixel(IMAGEMANAGER->findImage("아침 집 충돌")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY()) != RGB(255, 0, 0))

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
			if (GetPixel(IMAGEMANAGER->findImage("아침 집 충돌")->getMemDC(), PLAYER->getCenterX(), PLAYER->getCenterY() + 16) != RGB(255, 0, 0))
			{
				if (!SOUNDMANAGER->isPlaySound("movewood"))
				{
					SOUNDMANAGER->play("movewood", 0.2f);
				}
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
			if (GetPixel(IMAGEMANAGER->findImage("아침 집 충돌")->getMemDC(), PLAYER->getCenterX() + 8, PLAYER->getCenterY() + 8) != RGB(255, 0, 0))
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
}

void inHouseScene::savePlayer()
{
	PLAYER->savePlayerInven();
	PLAYER->savePlayerStock();
	PLAYER->savePlayerData();
	PLAYER->saveMap();
	PLAYER->saveBox();
	PLAYER->setLoadCount(0);
}

void inHouseScene::blanket()
{

	if (PLAYER->getCenterX() >= 855.0f && PLAYER->getCenterX() <= 880.0f && PLAYER->getCenterY() >= 855.0f && PLAYER->getCenterY() <= 880.0f)
	{
		if (checkCount == 0) //안닿으면
		{
			isShowSleepingOption = true; //트루? 
		}

		PLAYER->setIsShowSleepingOption(true);

		if (PtInRect(&noBox, _ptMouse)) //아니요에 닿으면 
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				isShowSleepingOption = false; //폴스다
			}
		}
		if (PtInRect(&yesBox, _ptMouse)) //예스에 닿으면
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				PLAYER->setIsSprinkled(false);
				if (!SWITCHMANAGER->getFade())
				{
					SWITCHMANAGER->startFade(855.0f, 865.0f);
				}
				PLAYER->resetClock();
				savePlayer();
				isShowSleepingOption = false; //폴스다.
			}
		}
		checkCount++;
	}
	else //범위밖이면 
	{
		isShowSleepingOption = false;
		PLAYER->setIsShowSleepingOption(false);
		checkCount = 0;
	}
}