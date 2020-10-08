#include "stdafx.h"
#include "Stock.h"

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
				IMAGEMANAGER->findImage("¾î¸°Á¥¼Ò")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX, iter.centerY, iter.indexX, iter.indexY);
			}
			else
			{
				IMAGEMANAGER->findImage("Á¥¼Ò")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX, iter.centerY, iter.indexX, iter.indexY);
			}
			break;
		case STOCK_BROWNCOW:
			if (!iter.isFullyGrown)
			{
				IMAGEMANAGER->findImage("¾î¸°È²¼Ò")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX, iter.centerY, iter.indexX, iter.indexY);
			}
			else
			{
				IMAGEMANAGER->findImage("È²¼Ò")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX, iter.centerY, iter.indexX, iter.indexY);
			}
			break;
		case STOCK_SHEEP:
			if (!iter.isFullyGrown)
			{
				IMAGEMANAGER->findImage("¾î¸°¾ç")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX, iter.centerY, iter.indexX, iter.indexY);
			}
			else if (iter.isFullyGrown && iter.isSheared)
			{
				IMAGEMANAGER->findImage("ÅÐ±ðÀÎ¾ç")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX, iter.centerY, iter.indexX, iter.indexY);
			}
			else
			{
				IMAGEMANAGER->findImage("¾ç")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX, iter.centerY, iter.indexX, iter.indexY);
			}
			break;
		case STOCK_BRONCHICKEN:
			if (!iter.isFullyGrown)
			{
				IMAGEMANAGER->findImage("°¥»öº´¾Æ¸®")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX, iter.centerY, iter.indexX, iter.indexY);
			}
			else
			{
				IMAGEMANAGER->findImage("°¥»ö´ß")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX, iter.centerY, iter.indexX, iter.indexY);
			}
			break;
		case STOCK_WHITECHICKEN:
			if (!iter.isFullyGrown)
			{
				IMAGEMANAGER->findImage("³ë¶õº´¾Æ¸®")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX, iter.centerY, iter.indexX, iter.indexY);
			}
			else
			{
				IMAGEMANAGER->findImage("Èò´ß")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX, iter.centerY, iter.indexX, iter.indexY);
			}
			break;
		case STOCK_DUCK:
				IMAGEMANAGER->findImage("¿À¸®")->frameRender(CAMERAMANAGER->getMemDC(), iter.centerX, iter.centerY, iter.indexX, iter.indexY);
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
		temp.speed = 0.4;
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
	temp.centerX = RANDOM->range(400, 800);
	temp.centerY = RANDOM->range(150, 450);
	stockList.push_back(temp);
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
			if (_vPlayerStock[i].aniCount % 10 == 0)
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
		}
		else if (_vPlayerStock[i].state == SS_EAT)
		{
			if (_vPlayerStock[i].aniCount % 10 == 0)
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
				else
				{
					_vPlayerStock[i].indexX++;
					if (_vPlayerStock[i].indexX > 3)
					{
						_vPlayerStock[i].indexX = 2;
					}
				}
			}
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
	for (auto iter : _vPlayerStock)
	{
		if (!(iter.isMove && iter.state == SS_MOVE)) continue;
		switch (iter.direction)
		{
		case RIGHT:
			iter.centerX += iter.speed;
			break;
		case LEFT:
			iter.centerX -= iter.speed;
			break;
		case UP:
			iter.centerY -= iter.speed;
			break;
		case DOWN:
			iter.centerY += iter.speed;
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

Stock::Stock()
{
	addStock();
	count = 0;
}

Stock::~Stock()
{

}
