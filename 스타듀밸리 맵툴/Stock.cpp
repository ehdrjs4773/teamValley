#include "stdafx.h"
#include "Stock.h"

HRESULT Stock::init()
{
	addStock();
	count = 0;
	return S_OK;
}

void Stock::update()
{
	count++;
	if (count % 300 == 0)
	{
		setStockState();
	}

	stockMove();
	stockAnimation();

	if (count > 10000)
	{
		count = 0;
	}

	cout << _vPlayerStock[0].state << "\t" << _vPlayerStock[0].speed << "\t" << _vPlayerStock[0].indexX << "\t" << count << "\t" << _vPlayerStock[0].isMove << endl;
}

void Stock::render()
{
	for (auto iter : _vPlayerStock)
	{
		switch (iter.stockType)
		{
		case STOCK_WHITECOW:
			if (!iter.isFullyGrown)
			{
				IMAGEMANAGER->findImage("어린젖소")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX - 16, iter.centerY - 16, iter.indexX, iter.indexY);
			}
			else
			{
				IMAGEMANAGER->findImage("젖소")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX - 16, iter.centerY - 16, iter.indexX, iter.indexY);
			}
			break;
		case STOCK_BROWNCOW:
			if (!iter.isFullyGrown)
			{
				IMAGEMANAGER->findImage("어린황소")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX - 16, iter.centerY - 16, iter.indexX, iter.indexY);
			}
			else
			{
				IMAGEMANAGER->findImage("황소")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX - 16, iter.centerY - 16, iter.indexX, iter.indexY);
			}
			break;
		case STOCK_SHEEP:
			if (!iter.isFullyGrown)
			{
				IMAGEMANAGER->findImage("어린양")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX - 16, iter.centerY - 16, iter.indexX, iter.indexY);
			}
			else if (iter.isFullyGrown && iter.isSheared)
			{
				IMAGEMANAGER->findImage("털깎인양")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX - 16, iter.centerY - 16, iter.indexX, iter.indexY);
			}
			else
			{
				IMAGEMANAGER->findImage("양")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX - 16, iter.centerY - 16, iter.indexX, iter.indexY);
			}
			break;
		case STOCK_BROWNCHICKEN:
			if (!iter.isFullyGrown)
			{
				IMAGEMANAGER->findImage("갈색병아리")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX - 8, iter.centerY - 8, iter.indexX, iter.indexY);
			}
			else
			{
				IMAGEMANAGER->findImage("갈색닭")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX - 8, iter.centerY - 8, iter.indexX, iter.indexY);
			}
			break;
		case STOCK_WHITECHICKEN:
			if (!iter.isFullyGrown)
			{
				IMAGEMANAGER->findImage("노란병아리")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX - 8, iter.centerY - 8, iter.indexX, iter.indexY);
			}
			else
			{
				IMAGEMANAGER->findImage("흰닭")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX - 8, iter.centerY - 8, iter.indexX, iter.indexY);
			}
			break;
		case STOCK_DUCK:
				IMAGEMANAGER->findImage("오리")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX - 8, iter.centerY - 8, iter.indexX, iter.indexY);
			break;
		}
	}
}

void Stock::addStock()
{
	for (int i = 0; i < 6; i++)
	{
		tagStock temp;
		temp.stockType = (STOCKTYPE)i;
		temp.direction = DOWN;
		temp.state = SS_STAND;
		temp.speed = 0.4f;
		temp.indexX = 0;
		temp.indexY = 0;
		temp.centerX = 0;
		temp.centerY = 0;
		temp.aniCount = 0;
		temp.isFullyGrown = false;
		temp.isSheared = false;
		temp.isMove = false;
		stockList.push_back(temp);
	}
}

void Stock::addPlayerStock(STOCKTYPE stockType)
{
	tagStock temp;
	temp = findStock(stockType);
	temp.isFullyGrown = true;
	temp.centerX = 800;
	temp.centerY = 800;
	_vPlayerStock.push_back(temp);
}

tagStock Stock::findStock(STOCKTYPE stockType)
{
	for (auto iter : stockList)
	{
		if (iter.stockType == stockType)
		{
			return iter;
		}
	}
}

void Stock::stockAnimation()
{
	for (int i = 0; i < _vPlayerStock.size(); i++)
	{
		if (!_vPlayerStock[i].isMove) continue;
		if (_vPlayerStock[i].state == SS_MOVE)
		{
			_vPlayerStock[i].aniCount++;
			if (_vPlayerStock[i].aniCount % 20 == 0)
			{
				_vPlayerStock[i].indexX++;
				if (_vPlayerStock[i].indexX > 3)
				{
					_vPlayerStock[i].indexX = 0;
					_vPlayerStock[i].isMove = false;
					_vPlayerStock[i].aniCount = 0;
				}
			}
		}
		else if (_vPlayerStock[i].state == SS_STAND)
		{
			_vPlayerStock[i].aniCount++;
			if (_vPlayerStock[i].direction == DOWN)
			{
				if (_vPlayerStock[i].aniCount % 20 == 0)
				{
					if (_vPlayerStock[i].indexX == 0)
					{
						_vPlayerStock[i].indexX = 1;
						continue;
					}
					if (_vPlayerStock[i].indexX == 1)
					{
						_vPlayerStock[i].indexX = 0;
						_vPlayerStock[i].isMove = false;
						_vPlayerStock[i].aniCount = 0;
					}
				}
			}
			else if (_vPlayerStock[i].direction == UP)
			{
				if (_vPlayerStock[i].aniCount % 20 == 0)
				{
					if (_vPlayerStock[i].indexX == 0)
					{
						_vPlayerStock[i].indexX = 3;
						_vPlayerStock[i].indexY = 4;
						continue;
					}
					if (_vPlayerStock[i].indexX == 3)
					{
						_vPlayerStock[i].indexX = 0;
						_vPlayerStock[i].indexY = 1;
						_vPlayerStock[i].isMove = false;
						_vPlayerStock[i].aniCount = 0;
					}
				}
			}
			else
			{
				_vPlayerStock[i].isMove = false;
			}
		}
		else if (_vPlayerStock[i].state == SS_EAT)
		{
			/*if (_vPlayerStock[i].aniCount % 10 == 0)
			{
				if (_vPlayerStock[i].aniCount > 40)
				{
					_vPlayerStock[i].indexX--;
					if (_vPlayerStock[i].indexX < 0)
					{
						_vPlayerStock[i].isMove = false;
						_vPlayerStock[i].aniCount = 0;
					}
				}
				else if(_vPlayerStock[i].aniCount <= 40)
				{
					_vPlayerStock[i].indexX++;
					if (_vPlayerStock[i].indexX > 3)
					{
						_vPlayerStock[i].indexX = 2;
					}
				}
			}*/
			_vPlayerStock[i].isMove = false;
		}
		else if (_vPlayerStock[i].state == SS_HAPPY)
		{
			_vPlayerStock[i].aniCount++;
			if (_vPlayerStock[i].aniCount > 180)
			{
				_vPlayerStock[i].state = SS_STAND;
				_vPlayerStock[i].isMove = false;
				_vPlayerStock[i].aniCount = 0;
			}
		}
	}
}

void Stock::setStockDirection(int stockNumber, DIRECTION dir)
{
	_vPlayerStock[stockNumber].direction = dir;
}

void Stock::stockMove()
{
	for (int i = 0; i < _vPlayerStock.size(); i++)
	{
		if (!_vPlayerStock[i].isMove || _vPlayerStock[i].state != SS_MOVE) continue;
		switch (_vPlayerStock[i].direction)
		{
		case RIGHT:
			if (GetPixel(IMAGEMANAGER->findImage("큰외양간 충돌")->getMemDC(), _vPlayerStock[i].centerX + 16, _vPlayerStock[i].centerY) != RGB(255, 0, 0))
			{
				_vPlayerStock[i].centerX += _vPlayerStock[i].speed;
			}
			break;
		case LEFT:
			if (GetPixel(IMAGEMANAGER->findImage("큰외양간 충돌")->getMemDC(), _vPlayerStock[i].centerX - 16, _vPlayerStock[i].centerY) != RGB(255, 0, 0))
			{
				_vPlayerStock[i].centerX -= _vPlayerStock[i].speed;
			}
			break;
		case UP:
			if (GetPixel(IMAGEMANAGER->findImage("큰외양간 충돌")->getMemDC(), _vPlayerStock[i].centerX, _vPlayerStock[i].centerY - 16) != RGB(255, 0, 0))
			{
				_vPlayerStock[i].centerY -= _vPlayerStock[i].speed;
			}
			break;
		case DOWN:
			if (GetPixel(IMAGEMANAGER->findImage("큰외양간 충돌")->getMemDC(), _vPlayerStock[i].centerX , _vPlayerStock[i].centerY + 16) != RGB(255, 0, 0))
			{
				_vPlayerStock[i].centerY += _vPlayerStock[i].speed;
			}
			break;
		}
	}
}

void Stock::setStockState()
{
	for (int i = 0; i < _vPlayerStock.size(); i++)
	{
		if (_vPlayerStock[i].isMove) continue;
		else if (!_vPlayerStock[i].isMove)
		{
			_vPlayerStock[i].state = (STOCKSTATE)RANDOM->range(4);
			setStockIndex(i);
		}
	}
}

void Stock::setStockIndex(int i)
{
	if (_vPlayerStock[i].state == SS_MOVE)
	{
		setStockDirection(i, (DIRECTION)RANDOM->range(4));
		switch (_vPlayerStock[i].direction)
		{
		case RIGHT:
			_vPlayerStock[i].indexY = 3;
			break;
		case LEFT:
			_vPlayerStock[i].indexY = 2;
			break;
		case UP:
			_vPlayerStock[i].indexY = 1;
			break;
		case DOWN:
			_vPlayerStock[i].indexY = 0;
			break;
		}
	}
	else if (_vPlayerStock[i].state == SS_STAND)
	{
		if (_vPlayerStock[i].direction == DOWN)
		{
			_vPlayerStock[i].indexX = 0;
			_vPlayerStock[i].indexY = 4;
		}
		else if (_vPlayerStock[i].direction == UP)
		{
			_vPlayerStock[i].indexX = 0;
			_vPlayerStock[i].indexY = 1;
		}
	}
	else if (_vPlayerStock[i].state == SS_EAT)
	{
		_vPlayerStock[i].indexX = 0;
		_vPlayerStock[i].indexY = 5;
	}
	else if (_vPlayerStock[i].state == SS_HAPPY)
	{
		_vPlayerStock[i].indexX = 2;
		_vPlayerStock[i].indexY = 4;
	}
	_vPlayerStock[i].isMove = true;
}