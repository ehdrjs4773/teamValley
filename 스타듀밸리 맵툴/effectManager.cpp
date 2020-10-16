#include "stdafx.h"
#include "effectManager.h"

HRESULT effectManager::init()
{
	IMAGEMANAGER->addFrameImage("����������", "Images/BMP/treeCollapse.bmp", 3116, 336, 19, 3);
	
	addEffect("����������", "�ҳ���", EFT_PINETREECOL);
	addEffect("����������", "��ǳ����", EFT_MAPLETREECOL);
	addEffect("����������", "������", EFT_OAKTREECOL);
	
	return S_OK;
}

void effectManager::release()
{
}

void effectManager::update()
{
	if (!vEffect.empty())
	{
		for (int i = 0; i < vEffect.size(); i++)
		{
			vEffect[i].count++;
			if (vEffect[i].count % 5 == 0)
			{
				if (vEffect[i].dir == LEFT)
				{
					vEffect[i].indexX--;
				}
				else if (vEffect[i].dir == RIGHT)
				{
					vEffect[i].indexX++;
				}
				if (vEffect[i].indexX < 0 || vEffect[i].indexX > vEffect[i].maxIndex)
				{
					vEffect.erase(vEffect.begin() + i);
				}
			}
		}
	}
}

void effectManager::render(HDC hdc)
{
	if (!vEffect.empty())
	{
		for (int i = 0; i < vEffect.size(); i++)
		{
			if (vEffect[i].effectType == EFT_PINETREECOL
				|| vEffect[i].effectType == EFT_MAPLETREECOL
				|| vEffect[i].effectType == EFT_OAKTREECOL)
			{
				vEffect[i].image->frameRender(
					hdc,
					vEffect[i].centerX - (vEffect[i].image->getFrameWidth() / 2),
					vEffect[i].centerY - 88,
					vEffect[i].indexX,
					vEffect[i].indexY);
			}
		}	
	}
}

void effectManager::addEffect(string imageName, string effectName, EFFECT effectType)
{
	tagEffect temp;
	temp.image = IMAGEMANAGER->findImage(imageName);
	temp.effectType = effectType;
	temp.maxIndex = IMAGEMANAGER->findImage(imageName)->getMaxFrameX();
	if (effectType == EFT_PINETREECOL 
		|| effectType == EFT_MAPLETREECOL
		|| effectType == EFT_OAKTREECOL)
	{
		temp.indexX = 9;
	}
	temp.centerX = 0;
	temp.centerY = 0;
	temp.count = 0;
	effectList.emplace(make_pair(effectName, temp));
}

tagEffect effectManager::findEffect(string effectName)
{
	mapEffectListIter key = effectList.find(effectName);

	if (key != effectList.end())
	{
		return key->second;
	}
}

void effectManager::treeCol(string effectName, int centerX, int centerY)
{
	tagEffect temp;
	temp = this->findEffect(effectName);
	temp.centerX = centerX;
	temp.centerY = centerY;
	if (PLAYER->getCenterX() < centerX)
	{
		temp.dir = RIGHT;
	}
	else if (PLAYER->getCenterX() > centerX)
	{
		temp.dir = LEFT;
	}		
	if (temp.effectType == EFT_PINETREECOL)
	{		
		temp.indexY = 0;
	}		
	if (temp.effectType == EFT_MAPLETREECOL)
	{		
		temp.indexY = 1;
	}		
	if (temp.effectType == EFT_OAKTREECOL)
	{		
		temp.indexY = 2;
	}
	vEffect.emplace_back(temp);
}
