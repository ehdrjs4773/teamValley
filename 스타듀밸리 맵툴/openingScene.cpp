#include "stdafx.h"
#include "openingScene.h"
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")


HRESULT openingScene::init()
{
	SOUNDMANAGER->stop("메인음악");
	SOUNDMANAGER->play("오프닝");
	if (hWndAVI)
	{
		MCIWndClose(hWndAVI);
		MCIWndDestroy(hWndAVI);
		hWndAVI = 0;
	}

	char szAVIFilename[] = "video/opening.avi";

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
		SetWindowPos(hWndAVI, NULL, 0, 0, rt.right, rt.bottom, SWP_NOZORDER| SWP_NOMOVE);
		MCIWndPlay(hWndAVI);
		
	}


	return S_OK;
}

void openingScene::update()
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
		SOUNDMANAGER->stop("오프닝");
		SCENEMANAGER->loadScene("집안화면");
		movieCount = 0;
	}

	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		movieCount = 1700;
	}

}

void openingScene::release()
{
	


}
