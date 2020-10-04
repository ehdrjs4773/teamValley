#include "stdafx.h"
#include "shopScene.h"

HRESULT shopScene::init()
{
	_shop = new shop;
	_shop->init();

	return S_OK;
}

void shopScene::release()
{
	_shop->release();
}

void shopScene::update()
{
	_shop->update();
}

void shopScene::render()
{
	_shop->render();

}
