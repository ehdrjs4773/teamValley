#include "stdafx.h"
#include "endingScene.h"
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

HRESULT endingScene::init()
{
	SOUNDMANAGER->stop("����");
	//SOUNDMANAGER->play("������");
	if (hWndAVI)
	{
		MCIWndClose(hWndAVI);
		MCIWndDestroy(hWndAVI);
		hWndAVI = 0;
	}

	char szAVIFilename[] = "video/ending.avi";

	// hWndAVI�� ����
	hWndAVI = MCIWndCreate(_hWnd, _hInstance,
		MCIWNDF_NOTIFYANSI | MCIWNDF_NOMENU |
		MCIWNDF_NOTIFYALL | MCIWNDF_NOPLAYBAR,
		szAVIFilename);

	// ������ ���缭.. 
	if (hWndAVI)
	{
		RECT rt;
		GetClientRect(_hWnd, &rt);
		SetWindowPos(hWndAVI, NULL, 0, 0, rt.right, rt.bottom, SWP_NOZORDER | SWP_NOMOVE);
		MCIWndPlay(hWndAVI);
	}

	return S_OK;
}

void endingScene::release()
{
}

void endingScene::update()
{
	movieCount++;
	if (movieCount >= 1700)
	{
		if (hWndAVI)
		{
			MCIWndClose(hWndAVI);
			MCIWndDestroy(hWndAVI);
			hWndAVI = 0;
		}
		//SOUNDMANAGER->stop("������");
		SCENEMANAGER->loadScene("��ŸƮȭ��");
		movieCount = 0;
	}

	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		movieCount = 1700;
	}
}

void endingScene::render()
{
	
}