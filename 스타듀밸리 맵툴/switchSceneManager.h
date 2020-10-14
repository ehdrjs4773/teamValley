#pragma once
#include "singletonBase.h"

class switchSceneManager : public singletonBase<switchSceneManager>
{
private:
	int count;
	int alpha;

	float playerX, playerY;

	string nextScene;
	string currentScene;
	image* fadeImg;

	bool isFading;
	bool isFadeIn, isFadeOut;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void fade();

	string getCurrentScene() { return currentScene; }
	bool getFade() { return isFading; }
	void startFade(float _playerX, float _playerY);
	void changeScene(string sceneName);
};

