#include "stdafx.h"
#include "mainScene.h"

HRESULT mainScene::init()
{
	IMAGEMANAGER->addImage("����ȭ��", "Images/����ȭ��.bmp", 1200, 600, true, RGB(255, 0, 255));
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

	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_mapRc, _ptMouse))
		{

			SCENEMANAGER->loadScene("�ε�ȭ��");
		}

		if (PtInRect(&_newRc, _ptMouse))
		{

		}

		if (PtInRect(&_loadRc, _ptMouse))
		{

		}
		if (PtInRect(&_exitRc, _ptMouse))
		{
			exit(0);
		}
		
	}

}

void mainScene::render()
{
	IMAGEMANAGER->findImage("����ȭ��")->render(getMemDC(), 0, 0);
	
	if (INPUT->GetToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _newRc);
		Rectangle(getMemDC(), _loadRc);
		Rectangle(getMemDC(), _mapRc);
		Rectangle(getMemDC(), _exitRc);
	}

}
