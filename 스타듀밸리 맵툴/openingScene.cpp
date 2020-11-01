#include "stdafx.h"
#include "openingScene.h"
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")


HRESULT openingScene::init()
{
	SOUNDMANAGER->stop("��������");
	SOUNDMANAGER->play("������");
	//isTalk = false;
	//script[0] = "���� ��Ȱ�ϸ� �� ������ ������ �޷����⸸ �� ��.";
	//script[1] = "�̹� �������� �Ѵ޵��� ������ �޽��� ������ ���� ���� ì���.";
	//script[2] = "���ø� ���� �Ҿƹ��� ������ ��縦 ������\n�����ο� �ð��� ���� �����̴�.";
	if (hWndAVI)
	{
		MCIWndClose(hWndAVI);
		MCIWndDestroy(hWndAVI);
		hWndAVI = 0;
	}

	char szAVIFilename[] = "video/opening.avi";

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
		SetWindowPos(hWndAVI, NULL, 0, 0, rt.right, rt.bottom, SWP_NOZORDER| SWP_NOMOVE);
		MCIWndPlay(hWndAVI);
		//if (isTalk)
		//{
		//	IMAGEMANAGER->render("��ȭâ", getMemDC(), 80, 30);
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
		SOUNDMANAGER->stop("������");
		SCENEMANAGER->loadScene("����ȭ��");
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
