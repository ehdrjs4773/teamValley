#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//�ε�Ŭ���� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�ε� �̹��� �� ���� �ʱ�ȭ
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release()
{
	//�ε�Ŭ���� ����
	//_loading->release();
	//SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	//�ε��Ϸ��� ȭ�� ����
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("��ŸƮȭ��");
	}

}

void loadingScene::render()
{
	//�ε�Ŭ���� ����
	_loading->render();

	textOut(getMemDC(), 10, 10, "�ε�ȭ��");
}

void loadingScene::loadingImage()
{
	//�ε��� �ʹ� ������ ����Ǽ� õõ�� ���ư����� �׽�Ʈ������ �����
	IMAGEMANAGER->addFrameImage("����(��)", "Images/BMP/����(��).bmp", 384, 400, 24, 25);
	IMAGEMANAGER->addFrameImage("����(����)", "Images/BMP/����(����).bmp", 384, 400, 24, 25);
	IMAGEMANAGER->addFrameImage("����(����)", "Images/BMP/����(����).bmp", 384, 400, 24, 25);
	IMAGEMANAGER->addFrameImage("����(�ܿ�)", "Images/BMP/����(�ܿ�).bmp", 384, 400, 24, 25);
	IMAGEMANAGER->addFrameImage("���������Ʈ(��)", "Images/BMP/���� ������Ʈ(��).bmp", 1120, 400, 70, 25);
	IMAGEMANAGER->addFrameImage("���������Ʈ(����)", "Images/BMP/���� ������Ʈ(����).bmp", 1120, 400, 70, 25);
	IMAGEMANAGER->addFrameImage("���������Ʈ(����)", "Images/BMP/���� ������Ʈ(����).bmp", 1120, 400, 70, 25);
	IMAGEMANAGER->addFrameImage("���������Ʈ(�ܿ�)", "Images/BMP/���� ������Ʈ(�ܿ�).bmp", 1120, 400, 70, 25);
	IMAGEMANAGER->addImage("���", "Images/background.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("���̺�", "Images/save.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ε�", "Images/load.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������Ʈ", "Images/������Ʈ.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "Images/����.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���찳", "Images/���찳.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��", "Images/spring.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "Images/summer.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "Images/fall.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ܿ�", "Images/winter.bmp", 50, 30, true, RGB(255, 0, 255));

	//�÷��̾�
	IMAGEMANAGER->addFrameImage("playerMove", "Images/BMP/playerTemp.bmp", 2000, 1000, 8, 4, true, RGB(255, 0, 255));
}

void loadingScene::loadingSound()
{
}
