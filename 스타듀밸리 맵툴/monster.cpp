#include "stdafx.h"
#include "monster.h"

HRESULT monster::init()
{
	astarInit();
	return S_OK;
}

void monster::release()
{
}

void monster::update()
{
}

void monster::render()
{
}

void monster::astarInit()
{
	//노드 초기화
	_startNode = NULL;
	_endNode = NULL;
	_curNode = NULL;

	//전체노드 초기화
	for (int y = 0; y < 50; y++)
	{
		for (int x = 0; x < 50; x++)
		{
			//새로운 노드와 렉트위치 설정
			_totalNode[x][y] = new node(x, y);
			_totalNode[x][y]->rc = RectMake(x * 16, y * 16, 16, 16);
		}
	}

	//첫클릭이 짝수가 되게 하기 위해서 -1로 초기화
	_count = -1;
	//길 찾았냐?
	_isFind = false;

	//리스타트용
	_openList.clear();
	_closeList.clear();
	_finalList.clear();
}

void monster::searchPlayer(int playerCurrentX, int playerCurrentY)
{
	if (_startNode && _endNode) return;
	_totalNode[currentTileY][currentTileX]->nodeState = NODE_START;
	_startNode = _totalNode[currentTileY][currentTileX];

	_totalNode[playerCurrentY][playerCurrentX]->nodeState = NODE_END;
	_endNode = _totalNode[playerCurrentY][playerCurrentX];
}

void monster::pathFinding()
{
}

void monster::addOpenList(int idx, int idy)
{
}

void monster::delOpenList(int index)
{
}

void monster::setNodeColor(node * node, COLORREF color)
{
}
