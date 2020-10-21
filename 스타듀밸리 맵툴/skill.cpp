#include "stdafx.h"
#include "skill.h"

void skill::init()
{
	IMAGEMANAGER->addFrameImage("스킬", "Images/skill/skill_sprite.bmp", 500, 345, 9, 6);
	IMAGEMANAGER->addFrameImage("스킬이미지", "Images/skill/skill_image.bmp", 240, 40, 6, 1);
	skill_state = SKILL_END;
	frameX = frameY = 0;

	_num = -1;
	_count = 0;

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
		//Rectangle(hdc, _skillSlot[i]);
		_vSkill[i].image->frameRender(hdc, _skillSlot[i].left, _skillSlot[i].top, _vSkill[i].indexX, 0);
	}
}

void skill::animationRender(HDC hdc)
{
	for (int i = 0; i < _vSkill.size(); i++)
	{
		if (skill_state == _vSkill[i].skillKind && _isActive)
		{
			_skillRc = RectMakeCenter(pointX, pointY, 40, 40);
			//Rectangle(CAMERAMANAGER->getMemDC(), _skillRc);
			IMAGEMANAGER->findImage("스킬")->frameRender(CAMERAMANAGER->getMemDC(), pointX - 30, pointY - 30, frameX, _vSkill[i].indexX);
		}
	}
	CAMERAMANAGER->render(hdc);
}

void skill::update()
{
	if (_isActive == false)
	{
		for (int i = 0; i < _vSkill.size(); i++)
		{
			if (PtInRect(&_skillSlot[i], _ptMouse))
			{
				if (INPUT->GetKeyDown(VK_LBUTTON))
				{
					_isClick = true;
					skill_state = _vSkill[i].skillKind;
					cout << "skill " << i << "is activated !" << "\n";
				}
			}
		}

		if (_num >= 0)
		{
			skill_state = _vSkill[_num].skillKind;
		}

	}
	
	if (skill_state != SKILL_END)
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			_isActive = true;
			_isClick = false;
			frameX = 0;
			pointX = (float)CAMERAMANAGER->getX() + (float)((float)_ptMouse.x/WINSIZEX *480);
			pointY = (float)CAMERAMANAGER->getY() + (float)((float)_ptMouse.y/WINSIZEY *230);
		}
	}

	if (_isActive)
	{
		_count++;
		if (_count % 5 == 0)
		{
			frameX++;
			if (frameX > 8)
			{
				frameX = 0;
				_isActive = false;
				_isClick = true;
			}
		}
	}
	

	//skillAnimation();
}

void skill::skillAnimation()
{
	_count++;

	switch (skill_state)
	{
	case SKILL_EXPLOSION:

		break;
//	case SKILL_SPIKES:
//		frameX++;
//		if (frameX > 8) frameX = 0;
//		break;
//	case SKILL_FIRE:
//		frameX++;
//		if (frameX > 8) frameX = 0;
//		break;
//	case SKILL_SHIELD:
//		frameX++;
//		if (frameX > 7) frameX = 0;
//		break;
//	case SKILL_BLACKHOLE:
//		frameX++;
//		if (frameX > 7) frameX = 0;
//		break;
//	case SKILL_FIRE_BALL:
//		frameX++;
//		if (frameX > 7) frameX = 0;
//		break;
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
