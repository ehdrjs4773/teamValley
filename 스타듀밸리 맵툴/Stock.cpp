#include "stdafx.h"
#include "Stock.h"

void Stock::addStock()
{
	for (int i = 0; i < 4; i++)
	{
		tagStock temp;
		temp.stockType = (STOCKTYPE)i;
		temp.direction = DOWN;
		temp.speed = 0.4;
		temp.indexX = 0;
		temp.indexY = 0;
		temp.centerX = 0;
		temp.centerY = 0;
		temp.isFullyGrown = false;
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
		_vPlayerStock[i].aniCount++;
		if (_vPlayerStock[i].aniCount % 10 == 0)
		{
			_vPlayerStock[i].indexX++;
			if (_vPlayerStock[i].indexX > 3)
			{
				_vPlayerStock[i].indexX = 0;
				_vPlayerStock[i].isMove = false;
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
		if (!_vPlayerStock[i].isMove)
		{
			_vPlayerStock[i].isMove = RANDOM->range(2);
		}
		else if (_vPlayerStock[i].isMove)
		{
			setStockDirection(i, (DIRECTION)RANDOM->range(4));
			switch (_vPlayerStock[i].direction)
			{
			case RIGHT:

				break;
			case LEFT:

				break;
			case UP:

				break;
			case DOWN:

				break;
			}
		}
	}
}

Stock::Stock()
{
	addStock();
	count = 0;
}

Stock::~Stock()
{

}
