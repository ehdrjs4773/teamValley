#include "stdafx.h"
#include "endingScene.h"
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

HRESULT endingScene::init()
{
	SOUNDMANAGER->stop("농장");
	//SOUNDMANAGER->play("오프닝");
	if (hWndAVI)
	{
		MCIWndClose(hWndAVI);
		MCIWndDestroy(hWndAVI);
		hWndAVI = 0;
	}

	char szAVIFilename[] = "video/ending.avi";

	// hWndAVI를 생성
	hWndAVI = MCIWndCreate(_hWnd, _hInstance,
		MCIWNDF_NOTIFYANSI | MCIWNDF_NOMENU |
		MCIWNDF_NOTIFYALL | MCIWNDF_NOPLAYBAR,
		szAVIFilename);

	// 사이즈 맞춰서.. 
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
	//cout << movieCount << endl;
	movieCount++;
	if (movieCount >= 950)
	{
		if (hWndAVI)
		{
			MCIWndClose(hWndAVI);
			MCIWndDestroy(hWndAVI);
			hWndAVI = 0;
		}
		//SOUNDMANAGER->stop("오프닝");
		SWITCHMANAGER->changeScene("스타트화면");
		SWITCHMANAGER->startFade(.0f, .0f);
		movieCount = 0;
	}

	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		movieCount = 950;
	}
}

void endingScene::render()
{
	
}