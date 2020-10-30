#include "stdafx.h"
#include "mainScene.h"

HRESULT mainScene::init()
{

	for (int i = 0; i < 4; i++)
	{
		frameY[i] = 0;
	}

	SOUNDMANAGER->play("¸ÞÀÎÀ½¾Ç",0.3f);
	if (SOUNDMANAGER->isPlaySound("³óÀå")) { SOUNDMANAGER->stop("³óÀå");	}
	if (SOUNDMANAGER->isPlaySound("springDay")) { SOUNDMANAGER->stop("springDay");	}
	if (SOUNDMANAGER->isPlaySound("night")) { SOUNDMANAGER->stop("night");	}
	if (SOUNDMANAGER->isPlaySound("bugCave")) { SOUNDMANAGER->stop("bugCave");	}
	if (SOUNDMANAGER->isPlaySound("town")) { SOUNDMANAGER->stop("town");	}

	return S_OK;
}

void mainScene::release()
{
}

void mainScene::update()
{
	_newRc = RectMake(225, 463, 173, 121);
	_loadRc = RectMake(417, 463, 173, 121);
	_mapRc = RectMake(610, 463, 173, 121);
	_exitRc = RectMake(803, 463, 173, 121);

		if (PtInRect(&_newRc, _ptMouse))
		{
			frameY[0] = 1;
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				PLAYER->setIsNewGame(true);
				PLAYER->init();
				SWITCHMANAGER->changeScene("¿ÀÇÁ´×È­¸é");
				SWITCHMANAGER->startFade(820.0f, 865.0f);
			}
		}
		else frameY[0] = 0;

		if (PtInRect(&_loadRc, _ptMouse))
		{
			frameY[1] = 1;
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				PLAYER->setIsNewGame(false);
				PLAYER->loadPlayerData();
				PLAYER->closeInvenPage();
				SWITCHMANAGER->changeScene("Áý¾ÈÈ­¸é");
				SWITCHMANAGER->startFade(820.0f, 865.0f);
			}
		}
		else frameY[1] = 0;

		if (PtInRect(&_mapRc, _ptMouse))
		{
			frameY[2] = 1;	
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				SCENEMANAGER->loadScene("¸ÊÅøÈ­¸é");
			}
		}
		else frameY[2] = 0;

		if (PtInRect(&_exitRc, _ptMouse))
		{
			frameY[3] = 1;
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				PostQuitMessage(0);
				//exit(0);
			}
		}
		else frameY[3] = 0;
	
		SWITCHMANAGER->fade();
}

void mainScene::render()
{
	IMAGEMANAGER->findImage("¸ÞÀÎÈ­¸é")->render(getMemDC(), 0, 0); 

	IMAGEMANAGER->frameRender("¼±ÅÃ", getMemDC(), _newRc.left, _newRc.top, 0, frameY[0]);
	IMAGEMANAGER->frameRender("¼±ÅÃ", getMemDC(), _loadRc.left, _loadRc.top, 1, frameY[1]);
	IMAGEMANAGER->frameRender("¼±ÅÃ", getMemDC(), _mapRc.left, _mapRc.top, 2, frameY[2]);
	IMAGEMANAGER->frameRender("¼±ÅÃ", getMemDC(), _exitRc.left, _exitRc.top, 3, frameY[3]);



	if (INPUT->GetToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _newRc);
		
		Rectangle(getMemDC(), _loadRc);

		Rectangle(getMemDC(), _mapRc);

		Rectangle(getMemDC(), _exitRc);
		
	}
}
