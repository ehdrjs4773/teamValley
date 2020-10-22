#include "stdafx.h"
#include "skill.h"

void skill::init()
{
	IMAGEMANAGER->addFrameImage("스킬이미지", "Images/skill/skill_image.bmp", 240, 40, 6, 1);
	skill_state = SKILL_END;
	frameX = frameY = 0;

	_num = -1;
	_count = 0;
	_isShield = false;

	_isActive = false;
	_isClick = false;

	addSkill("스킬이미지", "익스플로전", SKILL_EXPLOSION, 8, false);
	addSkill("스킬이미지", "스파이크", SKILL_SPIKES, 8, false,1);
	addSkill("스킬이미지", "파이어", SKILL_FIRE, 8, false,2);
	addSkill("스킬이미지", "쉴드", SKILL_SHIELD, 7, false,3);
	addSkill("스킬이미지", "블랙홀", SKILL_BLACKHOLE, 7, false,4);
	addSkill("스킬이미지", "파이어볼", SKILL_FIRE_BALL, 7, false,5);

	for (int i = 0; i < 12; i++)
	{
		_skillSlot[i] = RectMake(333 + i * 45, 535, 40, 40);
	}
}

void skill::render(HDC hdc)
{
	for (int i = 0; i < _vSkill.size(); i++)
	{
		_vSkill[i].image->frameRender(hdc, _skillSlot[i].left, _skillSlot[i].top, _vSkill[i].indexX, 0);
	}

}

void skill::update()
{
	
	if (!PLAYER->getIsShowInventory())
	{
	skillSelect();

	skillActive();

	}

	//EFFECTMANAGER->skillCol("익스플로전", PLAYER->getCenterX(), PLAYER->getCenterY());
}

void skill::skillSelect()
{
	if (_isShield)
	{
		_count++;
		if (_count % 180 == 0)
		{
			_isShield = false;
		}
	}
	for (int i = 0; i < _vSkill.size(); i++)
	{
		if (PtInRect(&_skillSlot[i], _ptMouse))
		{
			if (INPUT->GetKeyDown(VK_LBUTTON))
			{
				_isClick = true;
				skill_state = _vSkill[i].skillKind;
				if (skill_state == SKILL_SHIELD)
				{
					if (!_isShield)
					{
						_isShield = true;
						_count = 0;
						EFFECTMANAGER->skillCol("쉴드", PLAYER->getCenterX(), PLAYER->getCenterY());
					}
				}
				_save_i = i;
				cout << "skill " << i << "is activated !" << "\n";
			}
		}
	}
	if (_num >= 0)
	{
		_isClick = true;

		skill_state = _vSkill[_num].skillKind;

		if (skill_state == SKILL_SHIELD)
		{
			if (!_isShield)
			{
				_isShield = true;
				EFFECTMANAGER->skillCol("쉴드", PLAYER->getCenterX(), PLAYER->getCenterY());
			}
		}
	}
}

void skill::skillActive()
{
	if(_isClick == true)
	{

		if (INPUT->GetKeyDown(VK_LBUTTON))
		{

			_isClick = false;
			pointX = (float)CAMERAMANAGER->getX() + (float)((float)_ptMouse.x / WINSIZEX * 480);
			pointY = (float)CAMERAMANAGER->getY() + (float)((float)_ptMouse.y / WINSIZEY * 230);
			switch (skill_state)
			{
			case SKILL_EXPLOSION:

				EFFECTMANAGER->skillCol("익스플로전", pointX, pointY);
				break;
			case SKILL_SPIKES:
				EFFECTMANAGER->skillCol("스파이크", pointX, pointY);

				break;
			case SKILL_FIRE:
				EFFECTMANAGER->skillCol("파이어", pointX, pointY);

				break;
			case SKILL_BLACKHOLE:
				EFFECTMANAGER->skillCol("블랙홀", pointX, pointY);

				break;
			case SKILL_FIRE_BALL:
				EFFECTMANAGER->skillCol("파이어볼", pointX, pointY);
				break;
			}
		}
	}
}

void skill::addSkill(const char * _key, const char* _skill_info, SKILL _skillkind, int _maxindex, bool _isActive, int _indexX, int _indexY)
{
	tagSkill temp;
	temp.image = IMAGEMANAGER->findImage(_key);
	temp.skill_info = _skill_info;
	temp.indexX = _indexX;
	temp.indexY = _indexY;
	temp.isActive = false;
	temp.skillKind = _skillkind;
	temp.maxindex = _maxindex;

	_vSkill.push_back(temp);
}
