#include "stdafx.h"
#include "switchSceneManager.h"

HRESULT switchSceneManager::init()
{
	alpha = 0;
	isFading = false;
	isFadeIn = false;
	isFadeOut = false;

	playerX = playerY = 0;

	//페이드인/아웃용 이미지
	fadeImg = IMAGEMANAGER->addImage("페이드", 1200, 600);

	return S_OK;
}

void switchSceneManager::release()
{
}

void switchSceneManager::update()
{
	if (isFading)
	{
		this->fade();
	}
}

void switchSceneManager::render(HDC hdc)
{
	if (isFading)
	{
		fadeImg->alphaRender(hdc, alpha);
	}
}

void switchSceneManager::fade()
{
	if (isFadeOut && !isFadeIn)
	{
		alpha += 3;
		if (alpha > 250)
		{
			alpha = 255;
			PLAYER->setCenterX(playerX);
			PLAYER->setCenterY(playerY);
			SCENEMANAGER->loadScene(nextScene);
			currentScene = nextScene;
			isFadeOut = false;
			isFadeIn = true;
		}
	}
	else if (!isFadeOut && isFadeIn)
	{
		alpha -= 3;
		if (alpha < 0)
		{
			alpha = 0;
			isFadeIn = false;
			isFading = false;
		}
	}
}

void switchSceneManager::startFade(float _playerX, float _playerY)
{
	playerX = _playerX;
	playerY = _playerY;
	isFading = true;
	isFadeOut = true;
}

void switchSceneManager::changeScene(string sceneName)
{
	nextScene = sceneName;
}
