#include "stdafx.h"
#include "skill.h"

void skill::init()
{
	IMAGEMANAGER->addFrameImage("��ų�̹���", "Images/skill/skill_image.bmp", 240, 40, 6, 1);
	skill_state = SKILL_END;
	frameX = frameY = 0;

	_num = -1;
	_count = 0;
	_isShield = false;

	_isActive = false;
	_isClick = false;

	addSkill("��ų�̹���", "EXPLOSION", SKILL_EXPLOSION, 8, false);
	addSkill("��ų�̹���", "SPIKES", SKILL_SPIKES, 8, false,1);
	addSkill("��ų�̹���", "FIRE", SKILL_FIRE, 8, false,2);
	addSkill("��ų�̹���", "SHIELD", SKILL_SHIELD, 7, false,3);
	addSkill("��ų�̹���", "BLACKHOLE", SKILL_BLACKHOLE, 7, false,4);
	addSkill("��ų�̹���", "FIRE_BALL", SKILL_FIRE_BALL, 7, false,5);
	_vCurrentSkill.push_back(_vSkill[0]);

	for (int i = 0; i < 12; i++)
	{
		_skillSlot[i] = RectMake(333 + i * 45, 535, 40, 40);
	}

}

void skill::render(HDC hdc)
{
	for (int i = 0; i < _vCurrentSkill.size(); i++)
	{
		_vCurrentSkill[i].image->frameRender(hdc, _skillSlot[i].left, _skillSlot[i].top, _vCurrentSkill[i].indexX, 0);
	}

}

void skill::update()
{
	if (!PLAYER->getIsShowInventory())
	{
		skillSelect();

		skillActive();

	}
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
				skill_state = _vCurrentSkill[i].skillKind;
				if (skill_state == SKILL_SHIELD)
				{
					if (!_isShield)
					{
						_isShield = true;
						_count = 0;
						if (!SOUNDMANAGER->isPlaySound("shield"))
						{
							SOUNDMANAGER->play("shield", 0.2f);
						}
						EFFECTMANAGER->skillCol("����", PLAYER->getCenterX(), PLAYER->getCenterY());
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

		skill_state = _vCurrentSkill[_num].skillKind;

		if (skill_state == SKILL_SHIELD)
		{
			if (!_isShield)
			{
				_isShield = true;
				if (!SOUNDMANAGER->isPlaySound("shield"))
				{
					SOUNDMANAGER->play("shield", 0.2f);
				}
				EFFECTMANAGER->skillCol("����", PLAYER->getCenterX(), PLAYER->getCenterY());
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
				SOUNDMANAGER->play("explosion", 0.2f);
				EFFECTMANAGER->skillCol("�ͽ��÷���", pointX, pointY);
				break;
			case SKILL_SPIKES:
				SOUNDMANAGER->play("spike", 0.2f);
				EFFECTMANAGER->skillCol("������ũ", pointX, pointY);
				break;
			case SKILL_FIRE:
				SOUNDMANAGER->play("fireSpell", 0.2f);
				EFFECTMANAGER->skillCol("���̾�", pointX, pointY);
				break;
			case SKILL_BLACKHOLE:
				SOUNDMANAGER->play("blackHole", 0.2f);
				EFFECTMANAGER->skillCol("��Ȧ", pointX, pointY);
				break;
			case SKILL_FIRE_BALL:
				SOUNDMANAGER->play("fireball", 0.2f);
				EFFECTMANAGER->skillCol("���̾", pointX, pointY);
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
