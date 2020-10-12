#include "stdafx.h"
#include "npc.h"

HRESULT npc::init(NPC_KIND kind)
{
	_stop = false;

	_count = 0;

	_isClicked = false;

	_rc = RectMake(_pos.x, _pos.y, 16, 32);

	if (kind == ITEM_NPC)
	{
		IMAGEMANAGER->addFrameImage("아이템NPC", "Images/NPC/npc_item.bmp", 64, 128, 4, 4);
		_npcImg = IMAGEMANAGER->findImage("아이템NPC");
	}
	else
	{
		IMAGEMANAGER->addFrameImage("스킬NPC", "Images/NPC/npc_skill.bmp", 64, 128, 4, 4);
		_npcImg = IMAGEMANAGER->findImage("스킬NPC");
	}

	_dir = DOWN;

	_frameX = 0;
	_frameY = 0;

	return S_OK;
}

void npc::release()
{
}

void npc::update()
{
	_rc = RectMake(_pos.x, _pos.y, 16, 32);
	//move();
}

void npc::render()
{
	Rectangle(CAMERAMANAGER->getMemDC(), _rc);
	_npcImg->frameRender(CAMERAMANAGER->getMemDC(), _rc.left, _rc.top, _frameX, _frameY);
}

void npc::move()
{

	_count++;
	static int random = 0;
	
	if (_count % 41 == 0)
	{
		if (_stop == false)
		{
			random = RANDOM->range(1, 4);
			_stop = true;
		}
	}

	if (_stop == true)
	{
		if (_count % 82 == 0)
		{
			_stop = false;
		}
	}

	if (_stop == false)
	{
		switch (random)
		{
		case 1:
			_dir = DOWN;
			_pos.y += 1;
			break;
		case 2:
			_dir = RIGHT;
			_pos.x += 1;
			break;
		case 3:
			_dir = UP;
			_pos.y -= 1;
			break;
		case 4:
			_dir = LEFT;
			_pos.x -= 1;
			break;
		}

		animation();
	}


}

void npc::animation()
{
	static int _ani_count = 0;
	_ani_count++;

	switch (_dir)
	{
	case DOWN:
		_frameY = 0;
		if (_ani_count % 10 == 0)
		{
			_frameX++;
			if (_frameX > 3) _frameX = 0;
		}
		break;
	case RIGHT:
		_frameY = 1;
		if (_ani_count % 10 == 0)
		{
			_frameX++;
			if (_frameX > 3) _frameX = 0;
		}
		break;
	case UP:
		_frameY = 2;
		if (_ani_count % 10 == 0)
		{
			_frameX++;
			if (_frameX > 3) _frameX = 0;
		}
		break;
	case LEFT:
		_frameY = 3;
		if (_ani_count % 10 == 0)
		{
			_frameX++;
			if (_frameX > 3) _frameX = 0;
		}
		break;
	}
}
