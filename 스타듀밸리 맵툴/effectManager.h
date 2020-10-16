#pragma once
#include "singletonBase.h"
#include "tileNode.h"

class effectManager : public singletonBase<effectManager>
{
private:
	typedef map<string, tagEffect> mapEffectList;
	typedef map<string, tagEffect>::iterator mapEffectListIter;
	vector<tagEffect> vEffect;

	mapEffectList effectList;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	void addEffect(
		string imageName,
		string effectName,
		EFFECT effectType);

	tagEffect findEffect(string effectName);
	void treeCol(string effectName, int centerX, int centerY);


};

