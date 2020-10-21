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
	//��� �ʱ�ȭ
	_startNode = NULL;
	_endNode = NULL;
	_curNode = NULL;

	//��ü��� �ʱ�ȭ
	for (int y = 0; y < 50; y++)
	{
		for (int x = 0; x < 50; x++)
		{
			//���ο� ���� ��Ʈ��ġ ����
			_totalNode[x][y] = new node(x, y);
			_totalNode[x][y]->rc = RectMake(x * 16, y * 16, 16, 16);
		}
	}

	//ùŬ���� ¦���� �ǰ� �ϱ� ���ؼ� -1�� �ʱ�ȭ
	_count = -1;
	//�� ã�ҳ�?
	_isFind = false;

	//����ŸƮ��
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
