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
	//농장 이미지
	IMAGEMANAGER->addFrameImage("농장(봄)", "Images/맵툴/농장(봄).bmp", 384, 400, 24, 25);
	IMAGEMANAGER->addFrameImage("농장(여름)", "Images/맵툴/농장(여름).bmp", 384, 400, 24, 25);
	IMAGEMANAGER->addFrameImage("농장(가을)", "Images/맵툴/농장(가을).bmp", 384, 400, 24, 25);
	IMAGEMANAGER->addFrameImage("농장(겨울)", "Images/맵툴/농장(겨울).bmp", 384, 400, 24, 25);
	IMAGEMANAGER->addFrameImage("농장오브젝트(봄)", "Images/맵툴/농장 오브젝트(봄).bmp", 1120, 400, 70, 25);
	IMAGEMANAGER->addFrameImage("농장오브젝트(여름)", "Images/맵툴/농장 오브젝트(여름).bmp", 1120, 400, 70, 25);
	IMAGEMANAGER->addFrameImage("농장오브젝트(가을)", "Images/맵툴/농장 오브젝트(가을).bmp", 1120, 400, 70, 25);
	IMAGEMANAGER->addFrameImage("농장오브젝트(겨울)", "Images/맵툴/농장 오브젝트(겨울).bmp", 1120, 400, 70, 25);
	IMAGEMANAGER->addFrameImage("광산 노말", "Images/맵툴/mineTerrain_Normal.bmp", 160, 160, 10, 10);
	IMAGEMANAGER->addFrameImage("광산 노말다크", "Images/맵툴/mineTerrain_NormalDark.bmp", 160, 160, 10, 10);
	IMAGEMANAGER->addFrameImage("광산 프로스트", "Images/맵툴/mineTerrain_Frost.bmp", 160, 160, 10, 10);
	IMAGEMANAGER->addFrameImage("광산 프로스트다크", "Images/맵툴/mineTerrain_FrostDark.bmp", 160, 160, 10, 10);
	IMAGEMANAGER->addFrameImage("광산오브젝트 노말", "Images/맵툴/mineObject_Normal.bmp", 256, 288, 16, 18);
	IMAGEMANAGER->addFrameImage("광산오브젝트 노말다크", "Images/맵툴/mineObject_NormalDark.bmp", 256, 288, 16, 18);
	IMAGEMANAGER->addFrameImage("광산오브젝트 프로스트", "Images/맵툴/mineObject_Frost.bmp", 256, 288, 16, 18);
	IMAGEMANAGER->addFrameImage("광산오브젝트 프로스트다크", "Images/맵툴/mineObject_FrostDark.bmp", 256, 288, 16, 18);
	IMAGEMANAGER->addFrameImage("건물", "Images/맵툴/건물.bmp", 416, 416, 26, 26);
	IMAGEMANAGER->addImage("배경", "Images/background.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("세이브", "Images/save.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("로드", "Images/load.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("오브젝트", "Images/오브젝트.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("지형", "Images/지형.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("지우개", "Images/지우개.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("오브젝트지우개", "Images/오브젝트지우개.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("건물버튼", "Images/건물.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("던전버튼", "Images/던전.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("봄", "Images/spring.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("여름", "Images/summer.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("가을", "Images/fall.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("겨울", "Images/winter.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("노말버튼", "Images/노말.bmp", 50, 25);
	IMAGEMANAGER->addImage("노말다크버튼", "Images/노말다크.bmp", 50, 25);
	IMAGEMANAGER->addImage("프로스트버튼", "Images/프로스트.bmp", 50, 25);
	IMAGEMANAGER->addImage("프로스트다크버튼", "Images/프로스트다크.bmp", 50, 25);
	IMAGEMANAGER->addImage("광산지형버튼", "Images/광산지형.bmp", 100, 50);
	IMAGEMANAGER->addImage("광산오브젝트버튼", "Images/광산오브젝트.bmp", 100, 50);

	IMAGEMANAGER->addImage("인벤토리_아이템", "Images/shop/inventory.bmp", 750, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("메인화면", "Images/메인화면.bmp", 1200, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("선택", "Images/메인화면선택.bmp", 696, 242, 4, 2);
	IMAGEMANAGER->addFrameImage("씨앗", "Images/BMP/씨앗아이템.bmp", 360, 160, 9, 4);
	IMAGEMANAGER->addFrameImage("도구", "Images/BMP/도구.bmp", 360, 160, 9, 4);

	IMAGEMANAGER->addImage("상점인벤토리", "Images/shop/inventory.bmp", 750, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("인벤토리 아이템창", "Images/inventory/inventory_item.bmp", 750, 550, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("플레이어 창고", "Images/inventory/playerStorage.bmp", 653, 430, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("농장장애물", "Images/BMP/farmObstacles.bmp", 96, 176, 6, 11);
	IMAGEMANAGER->addFrameImage("작물", "Images/BMP/작물.bmp", 256, 784, 16, 49);

	IMAGEMANAGER->addImage("큰외양간", "Images/맵/대형외양간.bmp", 1600, 1600);
	IMAGEMANAGER->addImage("큰외양간 충돌", "Images/맵/대형외양간 충돌.bmp", 1600, 1600);
	IMAGEMANAGER->addImage("큰양계장", "Images/맵/대형양계장.bmp", 2560, 1440);
	IMAGEMANAGER->addImage("소형집", "Images/맵/아침 소형 집.bmp", 2560, 1440);

	IMAGEMANAGER->addImage("인벤토리", "Images/inventory/iteminventory.bmp", 750, 550, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스킬창", "Images/inventory/skill.bmp", 750, 550, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("제작창", "Images/inventory/Craftinven.bmp", 750, 550, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아이템제작", "Images/inventory/CraftObject.bmp", 240, 200, 6, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아이템제작스몰", "Images/inventory/CraftObjectSmall.bmp", 96,80, 6, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아이템", "Images/inventory/Craftitem.bmp", 240, 80, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("아이템제작알파", "Images/inventory/CraftObjectAlpha.bmp", 240, 200, 6, 5, true, RGB(255, 0, 255));

	//플레이어
	IMAGEMANAGER->addImage("아침 집", "Images/맵/아침 집.bmp", 1600, 1600);
	IMAGEMANAGER->addImage("아침 집 충돌", "Images/맵/아침 집 충돌.bmp", 1600, 1600);
	IMAGEMANAGER->addImage("플레이어 이불덮기", "Images/맵/플레이어 이불덮기.bmp", 1600, 1600,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("자는옵션", "Images/맵/자는옵션.bmp", 968, 274,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("자는옵션네", "Images/맵/자는옵션네.bmp", 968, 274, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("자는옵션아니요", "Images/맵/자는옵션아니요.bmp", 968, 274, true, RGB(255, 0, 255));

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
	IMAGEMANAGER->addImage("아이템정보", "Images/shop/item_info.bmp", 260, 145, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("업버튼", "Images/shop/up_BT.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("다운버튼", "Images/shop/down_BT.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점실내", "Images/shop/shop.bmp", 600, 360, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점실내뒷배경", "Images/shop/shopM.bmp", 600, 360, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점인벤토리1", "Images/shop/inventory1.bmp", 608, 188, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("돈통", "Images/shop/돈통.bmp", 185, 55, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점테이블", "Images/shop/shop_table.bmp", 75, 46, true, RGB(255, 0, 255));
	//시계
	IMAGEMANAGER->addFrameImage("계절", "Images/시계/계절.bmp", 35, 92, 1, 4);
	IMAGEMANAGER->addFrameImage("날씨", "Images/시계/날씨.bmp", 34, 138, 1, 6);
	IMAGEMANAGER->addFrameImage("시계바늘", "Images/시계/시계바늘180도.bmp", 1330, 120, 19, 1);
	IMAGEMANAGER->addFrameImage("돈숫자", "Images/시계/돈 숫자.bmp", 140, 20, 10, 1);
	IMAGEMANAGER->addImage("시계", "Images/시계/시계.bmp", 200, 158);

	//마우스 커서
	IMAGEMANAGER->addFrameImage("커서", "Images/마우스커서.bmp", 144, 96, 3, 2);

	//몬스터
	IMAGEMANAGER->addFrameImage("슬라임", "Images/monster/greenSlime.bmp", 128, 32, 8, 2);
	IMAGEMANAGER->addFrameImage("벌레", "Images/monster/bug.bmp", 64, 80, 4, 5);
	IMAGEMANAGER->addFrameImage("바위게", "Images/monster/Rock Crab.bmp", 64, 120, 4, 5);
	IMAGEMANAGER->addFrameImage("도마뱀", "Images/monster/Serpent.bmp", 288, 64, 9, 2);
	IMAGEMANAGER->addImage("몬스터hp바", "Images/monster/monHpbar.bmp", 16, 4);
}

void loadingScene::loadingSound()
{
	SOUNDMANAGER->addSound("메인음악", "Sounds/opening.mp3", true, true);
	SOUNDMANAGER->addSound("농장", "Sounds/farm.mp3", true, true);
	SOUNDMANAGER->addSound("나무찍기", "Sounds/breakTree.mp3", false, false);
	SOUNDMANAGER->addSound("HOE", "Sounds/hoe.mp3", false, false);
	SOUNDMANAGER->addSound("select", "Sounds/menu_select.mp3", false, false);
	SOUNDMANAGER->addSound("menuclose", "Sounds/menuclose.mp3", false, false);
	SOUNDMANAGER->addSound("menuopen", "Sounds/menuopen.mp3", false, false);
	SOUNDMANAGER->addSound("movegrass", "Sounds/move_grass.mp3", false, false);
	SOUNDMANAGER->addSound("moverock", "Sounds/move_rock.mp3", false, false);
	SOUNDMANAGER->addSound("movesoil", "Sounds/move_soil.mp3", false, false);
	SOUNDMANAGER->addSound("movewood", "Sounds/woodyStep.mp3", false, false);
	SOUNDMANAGER->addSound("removeGrass", "Sounds/removeGrass.mp3", false, false);
	SOUNDMANAGER->addSound("removeRock", "Sounds/removeRock.mp3", false, false);
	SOUNDMANAGER->addSound("removeTree", "Sounds/removeTree.mp3", false, false);
	SOUNDMANAGER->addSound("scythe", "Sounds/scythe.mp3", false, false);
	SOUNDMANAGER->addSound("water", "Sounds/watering.mp3", false, false);
	SOUNDMANAGER->addSound("seed", "Sounds/seeds.mp3", false, false);
	SOUNDMANAGER->addSound("doorOpen", "Sounds/doorOpen.mp3", false, false);
	SOUNDMANAGER->addSound("harvest", "Sounds/pickUpItem.mp3", false, false);
	SOUNDMANAGER->addSound("getItem", "Sounds/coin.mp3", false, false);
	SOUNDMANAGER->addSound("springDay", "Sounds/spring_day.mp3", false, false);
	SOUNDMANAGER->addSound("bugCave", "Sounds/bug_cave.mp3", false, false);
}
