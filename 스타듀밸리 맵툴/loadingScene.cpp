#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	//로딩 이미지 및 사운드 초기화
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release()
{
	//로딩클래스 해제
	//_loading->release();
	//SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩완료후 화면 변경
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("스타트화면");
	}

}

void loadingScene::render()
{
	//로딩클래스 렌더
	_loading->render();

	textOut(getMemDC(), 10, 10, "로딩화면");
}

void loadingScene::loadingImage()
{
	//페이드인/아웃용 이미지
	IMAGEMANAGER->addImage("페이드", 1200, 600);

	//농장 이미지
	IMAGEMANAGER->addFrameImage("농장(봄)", "Images/맵툴/농장(봄).bmp", 384, 400, 24, 25);
	IMAGEMANAGER->addFrameImage("농장(여름)", "Images/맵툴/농장(여름).bmp", 384, 400, 24, 25);
	IMAGEMANAGER->addFrameImage("농장(가을)", "Images/맵툴/농장(가을).bmp", 384, 400, 24, 25);
	IMAGEMANAGER->addFrameImage("농장(겨울)", "Images/맵툴/농장(겨울).bmp", 384, 400, 24, 25);
	IMAGEMANAGER->addFrameImage("농장오브젝트(봄)", "Images/맵툴/농장 오브젝트(봄).bmp", 1120, 400, 70, 25);
	IMAGEMANAGER->addFrameImage("농장오브젝트(여름)", "Images/맵툴/농장 오브젝트(여름).bmp", 1120, 400, 70, 25);
	IMAGEMANAGER->addFrameImage("농장오브젝트(가을)", "Images/맵툴/농장 오브젝트(가을).bmp", 1120, 400, 70, 25);
	IMAGEMANAGER->addFrameImage("농장오브젝트(겨울)", "Images/맵툴/농장 오브젝트(겨울).bmp", 1120, 400, 70, 25);
	IMAGEMANAGER->addFrameImage("건물", "Images/맵툴/건물.bmp", 416, 416, 26, 26);
	IMAGEMANAGER->addImage("배경", "Images/background.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("세이브", "Images/save.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("로드", "Images/load.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("오브젝트", "Images/오브젝트.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("지형", "Images/지형.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("지우개", "Images/지우개.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("봄", "Images/spring.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("여름", "Images/summer.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("가을", "Images/fall.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("겨울", "Images/winter.bmp", 50, 30, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("인벤토리_아이템", "Images/shop/inventory.bmp", 750, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("메인화면", "Images/메인화면.bmp", 1200, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("선택", "Images/메인화면선택.bmp", 696, 242, 4, 2);
	IMAGEMANAGER->addFrameImage("씨앗", "Images/BMP/씨앗아이템.bmp", 360, 160, 9, 4);
	IMAGEMANAGER->addFrameImage("도구", "Images/BMP/도구.bmp", 360, 160, 9, 4);

	IMAGEMANAGER->addImage("주전자 바", "Images/BMP/주전자 바.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점인벤토리", "Images/shop/inventory.bmp", 750, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인벤토리 아이템창", "Images/inventory/inventory_item.bmp", 750, 550, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("플레이어 창고", "Images/inventory/playerStorage.bmp", 653, 430, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("농장장애물", "Images/BMP/farmObstacles.bmp", 96, 176, 6, 11);
	IMAGEMANAGER->addFrameImage("작물", "Images/BMP/작물.bmp", 256, 784, 16, 49);

	IMAGEMANAGER->addImage("큰외양간", "Images/맵/대형외양간.bmp", 1600, 1600);
	IMAGEMANAGER->addImage("큰외양간 충돌", "Images/맵/대형외양간 충돌.bmp", 1600, 1600);
	IMAGEMANAGER->addImage("큰양계장", "Images/맵/대형양계장.bmp", 2560, 1440);
	IMAGEMANAGER->addImage("소형집", "Images/맵/아침 소형 집.bmp", 2560, 1440);

	//플레이어
	IMAGEMANAGER->addFrameImage("playerMove", "Images/BMP/playerTemp.bmp", 2000, 1000, 8, 4, true, RGB(255, 0, 255));

	//플레이어 인벤토리
	IMAGEMANAGER->addImage("플레이어 퀵슬롯", "Images/inventory/playerQuickslot.bmp", 565, 69, true, RGB(255, 0, 255));
	
	//가축
	IMAGEMANAGER->addFrameImage("갈색닭", "Images/가축/갈색닭.bmp", 64, 96, 4, 6);
	IMAGEMANAGER->addFrameImage("갈색병아리", "Images/가축/병아리(갈색).bmp", 64, 96, 4, 6);
	IMAGEMANAGER->addFrameImage("흰닭", "Images/가축/흰닭.bmp", 64, 96, 4, 6);
	IMAGEMANAGER->addFrameImage("노란병아리", "Images/가축/병아리(노랑).bmp", 64, 96, 4, 6);
	IMAGEMANAGER->addFrameImage("오리", "Images/가축/오리.bmp", 64, 96, 4, 6);
	IMAGEMANAGER->addFrameImage("어린젖소", "Images/가축/어린젖소.bmp", 128, 192, 4, 6);
	IMAGEMANAGER->addFrameImage("어린황소", "Images/가축/어린황소.bmp", 128, 192, 4, 6);
	IMAGEMANAGER->addFrameImage("젖소", "Images/가축/젖소.bmp", 128, 192, 4, 6);
	IMAGEMANAGER->addFrameImage("황소", "Images/가축/황소.bmp", 128, 192, 4, 6);
	IMAGEMANAGER->addFrameImage("어린양", "Images/가축/어린양.bmp", 128, 192, 4, 6);
	IMAGEMANAGER->addFrameImage("털깎인양", "Images/가축/털깎인양.bmp", 128, 192, 4, 6);
	IMAGEMANAGER->addFrameImage("양", "Images/가축/양.bmp", 128, 192, 4, 6);
	
	//상점
	IMAGEMANAGER->addImage("상점", "Images/shop.bmp", 900, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점닫기", "Images/shop/exit.bmp", 30, 33);
	IMAGEMANAGER->addImage("상점슬롯", "Images/shop_itemslot.bmp", 875, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점슬롯클릭", "Images/shop_itemslot_click.bmp", 875, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아이템정보", "Images/shop/item_info.bmp", 210, 145, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("업버튼", "Images/shop/up_BT.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("다운버튼", "Images/shop/down_BT.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점실내", "Images/shop/shop.bmp", 600, 360, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점실내뒷배경", "Images/shop/shopM.bmp", 600, 360, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점인벤토리1", "Images/shop/inventory1.bmp", 608, 188, true, RGB(255, 0, 255));
}

void loadingScene::loadingSound()
{
	SOUNDMANAGER->addSound("메인음악", "Sounds/opening.mp3", true, true);
	SOUNDMANAGER->addSound("농장", "Sounds/farm.mp3", true, true);
}
