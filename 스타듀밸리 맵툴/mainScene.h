#pragma once
#include "gameNode.h"

class mainScene : public gameNode
{

private :
	static TCHAR saveName[MAX_PATH];

	RECT _newRc;
	RECT _loadRc;
	RECT _mapRc;
	RECT _exitRc;

public :
	HRESULT init();
	void release();
	void update();
	void render();

};

