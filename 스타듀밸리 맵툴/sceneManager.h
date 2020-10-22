#pragma once
#include "singletonBase.h"
//#include "gameNode.h"
//=============================================================
//	## sceneManager ## (���Ŵ���)
//=============================================================

//�̱����� ��ӹ��� ���̵��� static���� ����� ���⶧����
//�Ϲ�Ŭ������ ���ӳ�带 ����Ϸ��� �ϸ� ������

//���ӳ�� Ŭ���� ���漱��
class gameNode;

class sceneManager : public singletonBase <sceneManager>
{
private:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:	
	//map<string, gameNode*> _mSceneList;			//������ ��(ȭ��)���� ��Ƶ� ��
	mSceneList _mSceneList;			//������ ��(ȭ��)���� ��Ƶ� ��
	gameNode* _currentScene;		//�����
	string _currentSineName;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	//���߰�
	gameNode* addScene(string sceneName, gameNode* scene);
	//������
	HRESULT loadScene(string sceneName);

	mSceneList getSceneList() { return _mSceneList; }
	gameNode* getCurrentScene() { return _currentScene; }
	string getCurrentSceneName() { return _currentSineName;}


	sceneManager() : _currentScene(NULL) {}
	~sceneManager() {}
};

