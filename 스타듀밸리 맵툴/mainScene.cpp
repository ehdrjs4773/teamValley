#include "stdafx.h"
#include "mainScene.h"

HRESULT mainScene::init()
{
	IMAGEMANAGER->addImage("메인화면", "Images/메인화면.bmp", 1200, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("선택", "Images/메인화면선택.bmp", 696, 242, 4, 2);

	for (int i = 0; i < 4; i++)
	{
		frameY[i] = 0;
	}
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
				SCENEMANAGER->loadScene("인게임화면");
			}
		}
		else frameY[0] = 0;

		if (PtInRect(&_loadRc, _ptMouse))
		{
			frameY[1] = 1;
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				SCENEMANAGER->loadScene("인게임화면");
			}
		}
		else frameY[1] = 0;

		if (PtInRect(&_mapRc, _ptMouse))
		{
			frameY[2] = 1;	
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				SCENEMANAGER->loadScene("맵툴화면");
			}
		}
		else frameY[2] = 0;

		if (PtInRect(&_exitRc, _ptMouse))
		{
			frameY[3] = 1;
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				exit(0);
			}
		}
		else frameY[3] = 0;
	
}

void mainScene::render()
{
	IMAGEMANAGER->findImage("메인화면")->render(getMemDC(), 0, 0); 


	IMAGEMANAGER->frameRender("선택", getMemDC(), _newRc.left, _newRc.top, 0, frameY[0]);
	IMAGEMANAGER->frameRender("선택", getMemDC(), _loadRc.left, _loadRc.top, 1, frameY[1]);
	IMAGEMANAGER->frameRender("선택", getMemDC(), _mapRc.left, _mapRc.top, 2, frameY[2]);
	IMAGEMANAGER->frameRender("선택", getMemDC(), _exitRc.left, _exitRc.top, 3, frameY[3]);



	if (INPUT->GetToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _newRc);
		
		Rectangle(getMemDC(), _loadRc);

		Rectangle(getMemDC(), _mapRc);

		Rectangle(getMemDC(), _exitRc);
		
	}
}
