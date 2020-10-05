#pragma once
#include "gameNode.h"

class mainScene : public gameNode
{
private :

	RECT _newRc;
	RECT _loadRc;
	RECT _mapRc;
	RECT _exitRc;
	int frameY[3]; 

public :
	HRESULT init();
	void release();
	void update();
	void render();
};

