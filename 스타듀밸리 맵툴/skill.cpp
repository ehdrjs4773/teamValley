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


	for (int i = 0; i < 12; i++)
	{
		_skillSlot[i] = RectMake(333 + i * 45, 535, 40, 40);
	}

}

void skill::render(HDC hdc)
{

}

void skill::update()
{
	MouseIndexX = (float)((float)CAMERAMANAGER->getX() / 16) + (float)((float)_ptMouse.x / 40);
	MouseIndexY = (float)((float)CAMERAMANAGER->getY() / 16) + (float)((float)_ptMouse.y / 40);

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
			if (PLAYER->getInventory()->getvInven()[_num].weaponKind == WEAPON_EXPLOSION) skill_state = SKILL_EXPLOSION;
			if (PLAYER->getInventory()->getvInven()[_num].weaponKind == WEAPON_SPIKES) skill_state = SKILL_SPIKES;
			if (PLAYER->getInventory()->getvInven()[_num].weaponKind == WEAPON_FIRE) skill_state = SKILL_FIRE;
			if (PLAYER->getInventory()->getvInven()[_num].weaponKind == WEAPON_BLACKHOLE) skill_state = SKILL_BLACKHOLE;
			if (PLAYER->getInventory()->getvInven()[_num].weaponKind == WEAPON_FIREBALL) skill_state = SKILL_FIRE_BALL;
		}
	}
	//cout << skill_state << endl;
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

			if (MouseIndexY > PLAYER->getCurrentY())
			{
				PLAYER->setDirection(DOWN);
			}
			if (MouseIndexY < PLAYER->getCurrentY())
			{
				PLAYER->setDirection(UP);
			}
			if (MouseIndexX > PLAYER->getCurrentX())
			{
				PLAYER->setDirection(RIGHT); 
			}
			if (MouseIndexX < PLAYER->getCurrentX())
			{
				PLAYER->setDirection(LEFT);
			}

			switch (skill_state)
			{
			case SKILL_EXPLOSION:
				SOUNDMANAGER->play("explosion", 0.2f);
				EFFECTMANAGER->skillCol("익스플로전", pointX, pointY);
				PLAYER->setState(P_SKILL_EXPLOSION);
				break;
			case SKILL_SPIKES:
				SOUNDMANAGER->play("spike", 0.2f);
				EFFECTMANAGER->skillCol("스파이크", pointX, pointY);
				PLAYER->setState(P_SKILL_SPIKES);
				break;
			case SKILL_FIRE:
				SOUNDMANAGER->play("fireSpell", 0.2f);
				EFFECTMANAGER->skillCol("파이어", pointX, pointY);
				PLAYER->setState(P_SKILL_FIRE);
				break;
			case SKILL_BLACKHOLE:
				SOUNDMANAGER->play("blackHole", 0.2f);
				EFFECTMANAGER->skillCol("블랙홀", pointX, pointY);
				PLAYER->setState(P_SKILL_BLACKHOLE);
				break;
			case SKILL_FIRE_BALL:
				SOUNDMANAGER->play("fireball", 0.2f);
				EFFECTMANAGER->skillCol("파이어볼", pointX, pointY);
				PLAYER->setState(P_SKILL_FIRE_BALL);
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
