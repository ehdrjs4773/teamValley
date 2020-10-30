#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init()
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
	/*������ ���ΰ����� ������ ���鸸 ������ �Ѵ�*/
	/*�̰����� ������ ������ �߰��ϰ� ������� �����Ѵ�*/

	/*���߰�*/
	SCENEMANAGER->addScene("�ε�ȭ��", new loadingScene);
	SCENEMANAGER->addScene("����ȭ��", new maptoolScene);
	SCENEMANAGER->addScene("�ΰ���ȭ��", new inGameScene);
	SCENEMANAGER->addScene("������", new shopScene);
	SCENEMANAGER->addScene("��ŸƮȭ��", new mainScene);
	SCENEMANAGER->addScene("�ǹ���ȭ��", new inBuildingScene);
	SCENEMANAGER->addScene("����ȭ��", new inHouseScene);
	SCENEMANAGER->addScene("����ȭ��", new mineScene);
	SCENEMANAGER->addScene("������Ÿ��ȭ��", new towerScene);
	SCENEMANAGER->addScene("������ȭ��", new openingScene);
	/*�����*/
	SCENEMANAGER->loadScene("�ε�ȭ��");

	ShowCursor(false);

	return S_OK;
}

//=============================================================
//	## ���� ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
}

//=============================================================
//	## ������Ʈ ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	
	if (!SWITCHMANAGER->getFade())
	{
		//���Ŵ��� ������Ʈ
		SCENEMANAGER->update();
	}
	else
	{
		SWITCHMANAGER->update();
	}

	EFFECTMANAGER->update();

	//����Ŵ��� ������Ʈ (�̰� ������ ����Ŵ��� ����� �������� �ʴ´�!!!)
	SOUNDMANAGER->update();

	//cout << boolalpha << PLAYER->getIsNewGame() << PLAYER->getLoadCount() << endl;
}

//=============================================================
//	## ���� ## render()
//=============================================================
void mainGame::render()
{
	//��� �� ��Ʈ�� (�̰��� ������ �׳� �α�)

	if(SCENEMANAGER->getCurrentSceneName() != "������ȭ��")
	{
		PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
		//=============================================================

			//���ڻ� ��� ���ֱ�
		SetBkMode(getMemDC(), TRANSPARENT);

		//���Ŵ��� ����
		SCENEMANAGER->render();

		//���̵� ����
		SWITCHMANAGER->render(getMemDC());

		//Ÿ�ӸŴ��� ����
		TIME->render(getMemDC());

		IMAGEMANAGER->findImage("Ŀ��")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, 0, 0);

		//=============================================================
			//������� ������ ȭ��DC�� �׸��� (�̰͵� ������ �׳� �α�)
		this->getBackBuffer()->render(getHDC());
	}

}

