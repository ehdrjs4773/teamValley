#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	HFONT hFont;
	HFONT oldFont;
	AddFontResource("Fonts/DOSGothic.ttf");
	hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("DOSGothic"));
	oldFont = (HFONT)SelectObject(getMemDC(), hFont);
	//DeleteObject(oldFont);
	/*앞으로 메인게임은 각각의 씬들만 관리를 한다*/
	/*이곳에서 각각의 씬들을 추가하고 현재씬을 설정한다*/

	/*씬추가*/
	SCENEMANAGER->addScene("로딩화면", new loadingScene);
	SCENEMANAGER->addScene("맵툴화면", new maptoolScene);
	SCENEMANAGER->addScene("인게임화면", new inGameScene);
	SCENEMANAGER->addScene("상점씬", new shopScene);
	SCENEMANAGER->addScene("스타트화면", new mainScene);
	SCENEMANAGER->addScene("건물안화면", new inBuildingScene);
	SCENEMANAGER->addScene("집안화면", new inHouseScene);
	SCENEMANAGER->addScene("광산화면", new mineScene);
	SCENEMANAGER->addScene("마법사타워화면", new towerScene);
	SCENEMANAGER->addScene("오프닝화면", new openingScene);
	/*현재씬*/
	SCENEMANAGER->loadScene("로딩화면");

	ShowCursor(false);

	return S_OK;
}

//=============================================================
//	## 해제 ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
}

//=============================================================
//	## 업데이트 ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	
	if (!SWITCHMANAGER->getFade())
	{
		//씬매니져 업데이트
		SCENEMANAGER->update();
	}
	else
	{
		SWITCHMANAGER->update();
	}

	EFFECTMANAGER->update();

	//사운드매니져 업데이트 (이게 없으면 사운드매니져 제대로 동작하지 않는다!!!)
	SOUNDMANAGER->update();

	//cout << boolalpha << PLAYER->getIsNewGame() << PLAYER->getLoadCount() << endl;
}

//=============================================================
//	## 렌더 ## render()
//=============================================================
void mainGame::render()
{
	//흰색 빈 비트맵 (이것은 렌더에 그냥 두기)

	if(SCENEMANAGER->getCurrentSceneName() != "오프닝화면")
	{
		PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
		//=============================================================

			//글자색 배경 없애기
		SetBkMode(getMemDC(), TRANSPARENT);

		//씬매니져 렌더
		SCENEMANAGER->render();

		//페이드 렌더
		SWITCHMANAGER->render(getMemDC());

		//타임매니져 렌더
		TIME->render(getMemDC());

		IMAGEMANAGER->findImage("커서")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, 0, 0);

		//=============================================================
			//백버퍼의 내용을 화면DC에 그린다 (이것도 렌더에 그냥 두기)
		this->getBackBuffer()->render(getHDC());
	}

}

