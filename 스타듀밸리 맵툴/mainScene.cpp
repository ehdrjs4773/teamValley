#include "stdafx.h"
#include "mainScene.h"

HRESULT mainScene::init()
{

	for (int i = 0; i < 4; i++)
	{
		frameY[i] = 0;
	}

	SOUNDMANAGER->play("��������",0.3f);

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
				SCENEMANAGER->loadScene("�ΰ���ȭ��");
			}
		}
		else frameY[0] = 0;

		if (PtInRect(&_loadRc, _ptMouse))
		{
			frameY[1] = 1;
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				SWITCHMANAGER->changeScene("����ȭ��");
				SWITCHMANAGER->startFade(855.0f, 865.0f);
			}
		}
		else frameY[1] = 0;

		if (PtInRect(&_mapRc, _ptMouse))
		{
			frameY[2] = 1;	
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				SCENEMANAGER->loadScene("����ȭ��");
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
	
		SWITCHMANAGER->fade();
}

void mainScene::render()
{
	IMAGEMANAGER->findImage("����ȭ��")->render(getMemDC(), 0, 0); 


	IMAGEMANAGER->frameRender("����", getMemDC(), _newRc.left, _newRc.top, 0, frameY[0]);
	IMAGEMANAGER->frameRender("����", getMemDC(), _loadRc.left, _loadRc.top, 1, frameY[1]);
	IMAGEMANAGER->frameRender("����", getMemDC(), _mapRc.left, _mapRc.top, 2, frameY[2]);
	IMAGEMANAGER->frameRender("����", getMemDC(), _exitRc.left, _exitRc.top, 3, frameY[3]);



	if (INPUT->GetToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _newRc);
		
		Rectangle(getMemDC(), _loadRc);

		Rectangle(getMemDC(), _mapRc);

		Rectangle(getMemDC(), _exitRc);
		
	}
}

void mainScene::load()
{
	HANDLE file;
	DWORD read;
	sprintf(saveName, "save/playerData.data");
	file = CreateFile(saveName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, saveName, sizeof(saveName), &read, NULL);
	CloseHandle(file);
}
