#include "stdafx.h"
#include "player.h"


HRESULT player::init()
{

	_player.count = _player.index - 0;
	int _playerX = WINSIZEX / 2;
	int _playerY = WINSIZEY / 2;


	IMAGEMANAGER->addFrameImage("right", "player", 3000, 4250, 6, 1,true,RGB(255,0,255));
	_right = IMAGEMANAGER->findImage("right");

	IMAGEMANAGER->addFrameImage("left", "player", 3000, 4250, 6, 1, true, RGB(255, 0, 255));
	_left = IMAGEMANAGER->findImage("left");

	IMAGEMANAGER->addFrameImage("up", "player", 3000, 4250, 6, 1, true, RGB(255, 0, 255));
	_up = IMAGEMANAGER->findImage("up");

	IMAGEMANAGER->addFrameImage("down", "player", 3000, 4250, 6, 1, true, RGB(255, 0, 255));
	_down = IMAGEMANAGER->findImage("down");




	_player.rc = RectMakeCenter(_playerX, _playerY, 16, 32);

	return S_OK;
}

void  player::release()
{



}

void  player::update()
{


	//if (_pState == RIGHT && //플레이어의 오른쪽 타일이 나무밑둥 프레임일때 )
	//{
	//	if(_ptInRect(//나무..와 충돌하면  )
	//		{
	//			STATE = cutdownTree; 
	//		}
	//}


	//if (_pState == RIGHT)
	//{
	//	if(//오른쪽 타일이 나무)
	//		{

	//		}

	//		if(//오른쪽 타일이 돌이)
	//			{

	//			}
	//			if (//오른쪽 타일이 잔디)
	//				{

	//				}
	//				if (//오른쪽 타일이 돌)
	//					{

	//					}
	//}



	







}

void  player::render()
{
	switch (_pDirection)
	{
	case DIRECTION::RIGHT:
		IMAGEMANAGER->frameRender("right", getMemDC(), _player.rc.left, _player.rc.top);
		break;
	case DIRECTION::LEFT:
		IMAGEMANAGER->frameRender("left", getMemDC(), _player.rc.left, _player.rc.top);
		break;
	case DIRECTION::UP:
		IMAGEMANAGER->frameRender("up", getMemDC(), _player.rc.left, _player.rc.top);
		break;
	case DIRECTION::DOWN:
		IMAGEMANAGER->frameRender("down", getMemDC(), _player.rc.left, _player.rc.top);
		break;
	}

}

void  player::playerMovement()
{


	//if (INPUT->GetKeyDown('D'))  //좌표이동이 아니라 타일 이동... 
	//{
	//	_player.rc.left +=
	//		_player.rc.right +=
	//		_pState = RIGHT;
	//}
	//if (INPUT->GetKeyDown('A'))
	//{
	//	_player.rc.left -=
	//		_player.rc.right -=
	//		_pState = LEFT;
	//}

	//if (INPUT->GetKeyDown('W'))
	//{
	//	_player.rc.top -=
	//		_player.rc.bottom -=
	//		_pState = UP;
	//}

	//if (INPUT->GetKeyDown('S'))
	//{
	//	_player.rc.top +=
	//		_player.rc.bottom +=
	//		_pState = DOWN;
	//}


}

void player::playerAnimation()
{
	_player.count++;

	switch (_pState)
	{
	case RIGHT:
		if (_player.count & 10 == 0)
		{
			_player.index++;
			_right->setFrameY(0);

			if (_player.index > 6)
			{
				_player.index = 0;
			}
			_right->setFrameX(_player.index);
		}
		break;
	case LEFT:
		if (_player.count & 10 == 0)
		{
			_player.index++;
			_right->setFrameY(0);

			if (_player.index > 12)
			{
				_player.index = 7;
			}
			_right->setFrameX(_player.index);
		}
		break;
	case UP:
		if (_player.count & 10 == 0)
		{
			_player.index++;
			_right->setFrameY(1);

			if (_player.index > 8)
			{
				_player.index = 0;
			}
			_right->setFrameX(_player.index);
		}
		break;
	case DOWN:
		if (_player.count & 10 == 0)
		{
			_player.index++;
			_right->setFrameY(1);

			if (_player.index > 12)
			{
				_right->setFrameY(2);
				_player.index = 0;
				if (_player.index > 3)
				{
					_right->setFrameY(1);
					_player.index = 9;
				}
			}
			_right->setFrameX(_player.index);
		}
		break;
	}


}
