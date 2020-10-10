#pragma once

class Stock
{
private:
	vector<tagStock> stockList;
	vector<tagStock> _vPlayerStock;

	int count;

public:
	HRESULT init();
	void update();
	void render();
	void addStock();
	void addPlayerStock(STOCKTYPE stockType);
	tagStock findStock(STOCKTYPE stockType);

	void stockAnimation();
	void setStockDirection(int stockNumber, DIRECTION dir);
	void stockMove();
	void setStockState();
	void setStockIndex(int i);
};

