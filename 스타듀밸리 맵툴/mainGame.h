#pragma once
#include "gameNode.h"
/*������ ���ΰ����� ������ ���鸸 ������ �Ѵ�*/
/*������ ������ϸ� �̰��� �߰��Ѵ�*/
#include "loadingScene.h"
#include "maptoolScene.h"
#include "mainScene.h"
#include "inGameScene.h"
#include "shopScene.h"
#include "inBuildingScene.h"

class mainGame : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();
};