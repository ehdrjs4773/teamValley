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
	IMAGEMANAGER->addFrameImage("���� �븻", "Images/����/mineTerrain_Normal.bmp", 160, 160, 10, 10);
	IMAGEMANAGER->addFrameImage("���� �븻��ũ", "Images/����/mineTerrain_NormalDark.bmp", 160, 160, 10, 10);
	IMAGEMANAGER->addFrameImage("���� ���ν�Ʈ", "Images/����/mineTerrain_Frost.bmp", 160, 160, 10, 10);
	IMAGEMANAGER->addFrameImage("���� ���ν�Ʈ��ũ", "Images/����/mineTerrain_FrostDark.bmp", 160, 160, 10, 10);
	IMAGEMANAGER->addFrameImage("���������Ʈ �븻", "Images/����/mineObject_Normal.bmp", 256, 288, 16, 18);
	IMAGEMANAGER->addFrameImage("���������Ʈ �븻��ũ", "Images/����/mineObject_NormalDark.bmp", 256, 288, 16, 18);
	IMAGEMANAGER->addFrameImage("���������Ʈ ���ν�Ʈ", "Images/����/mineObject_Frost.bmp", 256, 288, 16, 18);
	IMAGEMANAGER->addFrameImage("���������Ʈ ���ν�Ʈ��ũ", "Images/����/mineObject_FrostDark.bmp", 256, 288, 16, 18);
	IMAGEMANAGER->addFrameImage("�ǹ�", "Images/����/�ǹ�.bmp", 416, 416, 26, 26);
	IMAGEMANAGER->addImage("���", "Images/background.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("���̺�", "Images/save.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ε�", "Images/load.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������Ʈ", "Images/������Ʈ.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "Images/����.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���찳", "Images/���찳.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������Ʈ���찳", "Images/������Ʈ���찳.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ǹ���ư", "Images/�ǹ�.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������ư", "Images/����.bmp", 100, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��", "Images/spring.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "Images/summer.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "Images/fall.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ܿ�", "Images/winter.bmp", 50, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�븻��ư", "Images/�븻.bmp", 50, 25);
	IMAGEMANAGER->addImage("�븻��ũ��ư", "Images/�븻��ũ.bmp", 50, 25);
	IMAGEMANAGER->addImage("���ν�Ʈ��ư", "Images/���ν�Ʈ.bmp", 50, 25);
	IMAGEMANAGER->addImage("���ν�Ʈ��ũ��ư", "Images/���ν�Ʈ��ũ.bmp", 50, 25);
	IMAGEMANAGER->addImage("����������ư", "Images/��������.bmp", 100, 50);
	IMAGEMANAGER->addImage("���������Ʈ��ư", "Images/���������Ʈ.bmp", 100, 50);

	IMAGEMANAGER->addImage("�κ��丮_������", "Images/shop/inventory.bmp", 750, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ȭ��", "Images/����ȭ��.bmp", 1200, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "Images/����ȭ�鼱��.bmp", 696, 242, 4, 2);
	IMAGEMANAGER->addFrameImage("����", "Images/BMP/���Ѿ�����.bmp", 360, 160, 9, 4);
	IMAGEMANAGER->addFrameImage("����", "Images/BMP/����.bmp", 360, 160, 9, 4);

	IMAGEMANAGER->addImage("�����κ��丮", "Images/shop/inventory.bmp", 750, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�κ��丮 ������â", "Images/inventory/inventory_item.bmp", 750, 550, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�÷��̾� â��", "Images/inventory/playerStorage.bmp", 653, 430, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("������ֹ�", "Images/BMP/farmObstacles.bmp", 96, 176, 6, 11);
	IMAGEMANAGER->addFrameImage("�۹�", "Images/BMP/�۹�.bmp", 256, 784, 16, 49);

	IMAGEMANAGER->addImage("ū�ܾ簣", "Images/��/�����ܾ簣.bmp", 1600, 1600);
	IMAGEMANAGER->addImage("ū�ܾ簣 �浹", "Images/��/�����ܾ簣 �浹.bmp", 1600, 1600);
	IMAGEMANAGER->addImage("ū�����", "Images/��/���������.bmp", 2560, 1440);
	IMAGEMANAGER->addImage("������", "Images/��/��ħ ���� ��.bmp", 2560, 1440);

	IMAGEMANAGER->addImage("�κ��丮", "Images/inventory/iteminventory.bmp", 750, 550, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ųâ", "Images/inventory/skill.bmp", 750, 550, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����â", "Images/inventory/Craftinven.bmp", 750, 550, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����������", "Images/inventory/CraftObject.bmp", 240, 200, 6, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���������۽���", "Images/inventory/CraftObjectSmall.bmp", 96,80, 6, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "Images/inventory/Craftitem.bmp", 240, 80, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���������۾���", "Images/inventory/CraftObjectAlpha.bmp", 240, 200, 6, 5, true, RGB(255, 0, 255));

	//�÷��̾�
	IMAGEMANAGER->addImage("��ħ ��", "Images/��/��ħ ��.bmp", 1600, 1600);
	IMAGEMANAGER->addImage("��ħ �� �浹", "Images/��/��ħ �� �浹.bmp", 1600, 1600);
	IMAGEMANAGER->addImage("�÷��̾� �̺ҵ���", "Images/��/�÷��̾� �̺ҵ���.bmp", 1600, 1600,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("�ڴ¿ɼ�", "Images/��/�ڴ¿ɼ�.bmp", 968, 274,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("�ڴ¿ɼǳ�", "Images/��/�ڴ¿ɼǳ�.bmp", 968, 274, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ڴ¿ɼǾƴϿ�", "Images/��/�ڴ¿ɼǾƴϿ�.bmp", 968, 274, true, RGB(255, 0, 255));

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
	
	//����
	IMAGEMANAGER->addImage("����", "Images/shop.bmp", 900, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ݱ�", "Images/shop/exit.bmp", 30, 33);
	IMAGEMANAGER->addImage("��������", "Images/shop_itemslot.bmp", 875, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������Ŭ��", "Images/shop_itemslot_click.bmp", 875, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����������", "Images/shop/item_info.bmp", 260, 145, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ư", "Images/shop/up_BT.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ٿ��ư", "Images/shop/down_BT.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ǳ�", "Images/shop/shop.bmp", 600, 360, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ǳ��޹��", "Images/shop/shopM.bmp", 600, 360, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����κ��丮1", "Images/shop/inventory1.bmp", 608, 188, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "Images/shop/����.bmp", 185, 55, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�������̺�", "Images/shop/shop_table.bmp", 75, 46, true, RGB(255, 0, 255));
	//�ð�
	IMAGEMANAGER->addFrameImage("����", "Images/�ð�/����.bmp", 35, 92, 1, 4);
	IMAGEMANAGER->addFrameImage("����", "Images/�ð�/����.bmp", 34, 138, 1, 6);
	IMAGEMANAGER->addFrameImage("�ð�ٴ�", "Images/�ð�/�ð�ٴ�180��.bmp", 1330, 120, 19, 1);
	IMAGEMANAGER->addFrameImage("������", "Images/�ð�/�� ����.bmp", 140, 20, 10, 1);
	IMAGEMANAGER->addImage("�ð�", "Images/�ð�/�ð�.bmp", 200, 158);

	//���콺 Ŀ��
	IMAGEMANAGER->addFrameImage("Ŀ��", "Images/���콺Ŀ��.bmp", 144, 96, 3, 2);

	//����
	IMAGEMANAGER->addFrameImage("������", "Images/monster/greenSlime.bmp", 128, 32, 8, 2);
	IMAGEMANAGER->addFrameImage("����", "Images/monster/bug.bmp", 64, 80, 4, 5);
	IMAGEMANAGER->addFrameImage("������", "Images/monster/Rock Crab.bmp", 64, 120, 4, 5);
	IMAGEMANAGER->addFrameImage("������", "Images/monster/Serpent.bmp", 288, 64, 9, 2);
	IMAGEMANAGER->addImage("����hp��", "Images/monster/monHpbar.bmp", 16, 4);
}

void loadingScene::loadingSound()
{
	SOUNDMANAGER->addSound("��������", "Sounds/opening.mp3", true, true);
	SOUNDMANAGER->addSound("����", "Sounds/farm.mp3", true, true);
	SOUNDMANAGER->addSound("�������", "Sounds/breakTree.mp3", false, false);
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
