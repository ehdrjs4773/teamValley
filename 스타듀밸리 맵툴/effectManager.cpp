#include "stdafx.h"
#include "effectManager.h"

HRESULT effectManager::init()
{
	IMAGEMANAGER->addFrameImage("나무쓰러짐", "Images/BMP/treeCollapse.bmp", 3116, 336, 19, 3);
	IMAGEMANAGER->addFrameImage("스킬", "Images/skill/skill_sprite.bmp", 500, 345, 9, 6);

	addEffect("나무쓰러짐", "소나무", EFT_PINETREECOL);
	addEffect("나무쓰러짐", "단풍나무", EFT_MAPLETREECOL);
	addEffect("나무쓰러짐", "참나무", EFT_OAKTREECOL);
	addEffect("스킬", "익스플로전", EFT_SKILL_EXPLOSION);
	addEffect("스킬", "스파이크", EFT_SKILL_SPIKES);
	addEffect("스킬", "파이어", EFT_SKILL_FIRE);
	addEffect("스킬", "쉴드", EFT_SKILL_SHIELD);
	addEffect("스킬", "블랙홀", EFT_SKILL_BLACKHOLE);
	addEffect("스킬", "파이어볼", EFT_SKILL_FIRE_BALL);
	
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
			if (vEffect[i].effectType == EFT_PINETREECOL
				|| vEffect[i].effectType == EFT_MAPLETREECOL
				|| vEffect[i].effectType == EFT_OAKTREECOL)
			{
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
			else if (vEffect[i].effectType == EFT_SKILL_FIRE_BALL)
			{
				if (vEffect[i].count % 5 == 0)
				{
					vEffect[i].indexX++;

					if (vEffect[i].indexX > vEffect[i].maxIndex)
					{
						vEffect.erase(vEffect.begin() + i);
					}
				}
				vEffect[i].centerX += cosf(vEffect[i].angle) * 1.0f;
				vEffect[i].centerY += -sinf(vEffect[i].angle) * 1.0f;
				vEffect[i].rc = RectMake(vEffect[i].centerX, vEffect[i].centerY, 40, 40);
			}
			else if(vEffect[i].effectType == EFT_SKILL_SHIELD)
			{
				if (vEffect[i].count % 5 == 0)
				{
					vEffect[i].indexX++;

					if (vEffect[i].indexX > vEffect[i].maxIndex)
					{
						vEffect.erase(vEffect.begin() + i);
					}
				}
				vEffect[i].rc = RectMake(PLAYER->getCenterX()-20,
					PLAYER->getCenterY()-20, 40, 40);
			}
			else 
			{
				if (vEffect[i].count % 5 == 0)
				{
					vEffect[i].indexX++;

					if (vEffect[i].indexX > vEffect[i].maxIndex)
					{
						vEffect.erase(vEffect.begin() + i);
					}
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
				|| vEffect[i].effectType == EFT_OAKTREECOL
				)
			{
				vEffect[i].image->frameRender(
					hdc,
					vEffect[i].centerX - (vEffect[i].image->getFrameWidth() / 2),
					vEffect[i].centerY - 88,
					vEffect[i].indexX,
					vEffect[i].indexY);
			}
			else if (vEffect[i].effectType == EFT_SKILL_FIRE_BALL)
			{
				Rectangle(hdc, vEffect[i].rc);
				vEffect[i].image->rotateFrameRender(
					hdc,
					vEffect[i].centerX+20,
					vEffect[i].centerY+20,
					vEffect[i].indexX,
					vEffect[i].indexY,
					vEffect[i].angle);
			}
			else if (vEffect[i].effectType == EFT_SKILL_SHIELD)
			{
				Rectangle(hdc, vEffect[i].rc);
				vEffect[i].image->frameRender(
					hdc,
					PLAYER->getCenterX()-30,
					PLAYER->getCenterY()-30,
					vEffect[i].indexX,
					vEffect[i].indexY);
			}
			else
			{
				Rectangle(hdc, vEffect[i].rc);
				vEffect[i].image->frameRender(
					hdc,
					vEffect[i].centerX-30,
					vEffect[i].centerY-30,
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
	if (effectType == EFT_PINETREECOL 
		|| effectType == EFT_MAPLETREECOL
		|| effectType == EFT_OAKTREECOL)
	{
		temp.indexX = 9;
		temp.maxIndex = IMAGEMANAGER->findImage(imageName)->getMaxFrameX();

	}
	else
	{
		temp.indexX = 0;
		temp.maxIndex = 8;
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

void effectManager::skillCol(string effectName, int centerX, int centerY)
{
	tagEffect temp;
	temp = this->findEffect(effectName);
	temp.centerX = centerX;
	temp.centerY = centerY;
	temp.rc = RectMakeCenter(centerX, centerY, 40, 40);
	temp.angle = getAngle(PLAYER->getCenterX(), PLAYER->getCenterY(), centerX, centerY);

	if (temp.effectType == EFT_SKILL_EXPLOSION)
	{
		temp.indexY = 0;
	}
	if (temp.effectType == EFT_SKILL_SPIKES)
	{
		temp.indexY = 1;
	}
	if (temp.effectType == EFT_SKILL_FIRE)
	{
		temp.indexY = 2;
	}
	if (temp.effectType == EFT_SKILL_SHIELD)
	{
		temp.indexY = 3;
	}
	if (temp.effectType == EFT_SKILL_BLACKHOLE)
	{
		temp.indexY = 4;
	}
	if (temp.effectType == EFT_SKILL_FIRE_BALL)
	{
		temp.indexY = 5;
	}
	vEffect.emplace_back(temp);
}
