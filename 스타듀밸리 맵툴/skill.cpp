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

	addSkill("스킬이미지", "EXPLOSION", SKILL_EXPLOSION, 8, false);
	addSkill("스킬이미지", "SPIKES", SKILL_SPIKES, 8, false,1);
	addSkill("스킬이미지", "FIRE", SKILL_FIRE, 8, false,2);
	addSkill("스킬이미지", "SHIELD", SKILL_SHIELD, 7, false,3);
	addSkill("스킬이미지", "BLACKHOLE", SKILL_BLACKHOLE, 7, false,4);
	addSkill("스킬이미지", "FIRE_BALL", SKILL_FIRE_BALL, 7, false,5);
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
	if (!PLAYER->getIsShowInventory() && !PtInRect(&PLAYER->getInventory()->getqucikRect(), _ptMouse))
	{
		skillSelect();

		skillActive();
	}
}

void skill::skillSelect()
{

	skill_state = SKILL_END;
	if (_num >= 0)
	{
		if (PLAYER->getInventory()->getvInven()[_num].item_kind == ITEM_SKILL)
		{
			_isClick = true;
			if (PLAYER->getInventory()->getvInven()[_num].item_info == "폭발 검") skill_state = SKILL_EXPLOSION;
			if (PLAYER->getInventory()->getvInven()[_num].item_info == "스파이크 검") skill_state = SKILL_SPIKES;
			if (PLAYER->getInventory()->getvInven()[_num].item_info == "불 검") skill_state = SKILL_FIRE;
			if (PLAYER->getInventory()->getvInven()[_num].item_info == "블랙홀 검") skill_state = SKILL_BLACKHOLE;
			if (PLAYER->getInventory()->getvInven()[_num].item_info == "파이어볼 검") skill_state = SKILL_FIRE_BALL;
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
				EFFECTMANAGER->skillCol("익스플로전", pointX, pointY);
				break;
			case SKILL_SPIKES:
				SOUNDMANAGER->play("spike", 0.2f);
				EFFECTMANAGER->skillCol("스파이크", pointX, pointY);
				break;
			case SKILL_FIRE:
				SOUNDMANAGER->play("fireSpell", 0.2f);
				EFFECTMANAGER->skillCol("파이어", pointX, pointY);
				break;
			case SKILL_BLACKHOLE:
				SOUNDMANAGER->play("blackHole", 0.2f);
				EFFECTMANAGER->skillCol("블랙홀", pointX, pointY);
				break;
			case SKILL_FIRE_BALL:
				SOUNDMANAGER->play("fireball", 0.2f);
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
