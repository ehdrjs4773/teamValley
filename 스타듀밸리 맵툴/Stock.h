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

	vector<tagStock> getStock() { return _vPlayerStock; }
	void setStock(tagStock stock) { _vPlayerStock.push_back(stock); }
	void setStock(vector<tagStock> temp) { _vPlayerStock = temp; }
};

