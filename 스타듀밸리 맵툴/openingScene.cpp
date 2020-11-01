#include "stdafx.h"
#include "openingScene.h"
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")


HRESULT openingScene::init()
{
	SOUNDMANAGER->stop("메인음악");
	SOUNDMANAGER->play("오프닝");
	//isTalk = false;
	//script[0] = "대학 생활하며 돈 버느라 열심히 달려오기만 한 나.";
	//script[1] = "이번 여름방학 한달동안 진정한 휴식을 누리기 위해 짐을 챙겼다.";
	//script[2] = "도시를 떠나 할아버지 집에서 농사를 지으며\n여유로운 시간을 보낼 생각이다.";
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
		//if (isTalk)
		//{
		//	IMAGEMANAGER->render("대화창", getMemDC(), 80, 30);
		//	RECT tempRC = RectMake(120, 80, 800, 300);
		//	DrawText(getMemDC(), script[script_count], strlen(script[script_count]), &tempRC, NULL);
		//}
		
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
	cout << "TALK : " << isTalk <<"\t" << "script_count" << script_count << endl;
	if (movieCount >= 240 && movieCount <= 400)
	{
		script_count = 0;
		isTalk = true;
	}
	else if (movieCount >= 640 && movieCount <= 800)
	{
		script_count = 1;
		isTalk = true;
	}
	else if (movieCount >= 1300 && movieCount <= 1500)
	{
		script_count = 2;
		isTalk = true;
	}
	else isTalk = false;
}

void openingScene::release()
{
	


}

void openingScene::render()
{

}
