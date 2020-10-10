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
	//���� �̹���
	IMAGEMANAGER->addFrameImage("����(��)", "Images/����/����(��).bmp", 384, 400, 24, 25);
	IMAGEMANAGER->addFrameImage("����(����)", "Images/����/����(����).bmp", 384, 400, 24, 25);
	IMAGEMANAGER->addFrameImage("����(����)", "Images/����/����(����).bmp", 384, 400, 24, 25);
	IMAGEMANAGER->addFrameImage("����(�ܿ�)", "Images/����/����(�ܿ�).bmp", 384, 400, 24, 25);
	IMAGEMANAGER->addFrameImage("���������Ʈ(��)", "Images/����/���� ������Ʈ(��).bmp", 1120, 400, 70, 25);
	IMAGEMANAGER->addFrameImage("���������Ʈ(����)", "Images/����/���� ������Ʈ(����).bmp", 1120, 400, 70, 25);
	IMAGEMANAGER->addFrameImage("���������Ʈ(����)", "Images/����/���� ������Ʈ(����).bmp", 1120, 400, 70, 25);
	IMAGEMANAGER->addFrameImage("���������Ʈ(�ܿ�)", "Images/����/���� ������Ʈ(�ܿ�).bmp", 1120, 400, 70, 25);
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
	IMAGEMANAGER->addImage("�κ��丮_������", "Images/shop/inventory.bmp", 750, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ȭ��", "Images/����ȭ��.bmp", 1200, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "Images/����ȭ�鼱��.bmp", 696, 242, 4, 2);
	
	IMAGEMANAGER->addFrameImage("������ֹ�", "Images/BMP/farmObstacles.bmp", 96, 176, 6, 11);
	IMAGEMANAGER->addFrameImage("�۹�", "Images/BMP/�۹�.bmp", 256, 784, 16, 49);

	IMAGEMANAGER->addImage("ū�ܾ簣", "Images/��/�����ܾ簣1.bmp", 600, 500);
	IMAGEMANAGER->addImage("ū�����", "Images/��/���������.bmp", 2560, 1440);
	IMAGEMANAGER->addImage("������", "Images/��/��ħ ���� ��.bmp", 2560, 1440);

	//�÷��̾�
	IMAGEMANAGER->addFrameImage("playerMove", "Images/BMP/playerTemp.bmp", 2000, 1000, 8, 4, true, RGB(255, 0, 255));

	//�÷��̾� �κ��丮
	IMAGEMANAGER->addImage("�÷��̾� ������", "Images/inventory/playerQuickslot.bmp", 565, 69, true, RGB(255, 0, 255));
	
	//����
	IMAGEMANAGER->addFrameImage("������", "Images/����/������.bmp", 64, 96, 4, 6);
	IMAGEMANAGER->addFrameImage("�������Ƹ�", "Images/����/���Ƹ�(����).bmp", 64, 96, 4, 6);
	IMAGEMANAGER->addFrameImage("���", "Images/����/���.bmp", 64, 96, 4, 6);
	IMAGEMANAGER->addFrameImage("������Ƹ�", "Images/����/���Ƹ�(���).bmp", 64, 96, 4, 6);
	IMAGEMANAGER->addFrameImage("����", "Images/����/����.bmp", 64, 96, 4, 6);
	IMAGEMANAGER->addFrameImage("�����", "Images/����/�����.bmp", 128, 192, 4, 6);
	IMAGEMANAGER->addFrameImage("�Ȳ��", "Images/����/�Ȳ��.bmp", 128, 192, 4, 6);
	IMAGEMANAGER->addFrameImage("����", "Images/����/����.bmp", 128, 192, 4, 6);
	IMAGEMANAGER->addFrameImage("Ȳ��", "Images/����/Ȳ��.bmp", 128, 192, 4, 6);
	IMAGEMANAGER->addFrameImage("���", "Images/����/���.bmp", 128, 192, 4, 6);
	IMAGEMANAGER->addFrameImage("�б��ξ�", "Images/����/�б��ξ�.bmp", 128, 192, 4, 6);
	IMAGEMANAGER->addFrameImage("��", "Images/����/��.bmp", 128, 192, 4, 6);
}

void loadingScene::loadingSound()
{
	SOUNDMANAGER->addSound("��������", "Sounds/opening.mp3", true, true);
	SOUNDMANAGER->addSound("����", "Sounds/farm.mp3", true, true);
}
