#pragma once

class Stock
{
private:
	vector<tagStock> stockList;
	vector<tagStock> _vPlayerStock;

	int count;

public:
	void addStock();
	void addPlayerStock(STOCKTYPE stockType);
	tagStock findStock(STOCKTYPE stockType);

	void stockAnimation();
	void setStockDirection(int stockNumber, DIRECTION dir);
	void stockMove();

	Stock();
	~Stock();
};

