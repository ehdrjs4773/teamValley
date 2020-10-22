#include "stdafx.h"
#include "monster.h"

monster::monster(MONTYPE _monsterType, int _centerX, int _centerY, int _hp, int _dmg, float _speed)
{
	monsterType = _monsterType;
	state = MSTATE_IDLE;
	centerX = _centerX;
	centerY = _centerY;
	currentTileX = 0;
	currentTileY = 0;
	moveCount = 0;
	hp = _hp;
	currentHp = hp;
	dmg = _dmg;
	speed = _speed;
	angle = .0f;
	aniIndexX = 0;
	aniIndexY = 0;
	aniCount = 0;
	dir = NONE;
	lockedAngle = 0.0f;

	isMove = false;

	isDead = false;

	isLocked = false;
}

void monster::move()
{
	if (_finalList.size() > 0)
	{
		float destX = _finalList[0]->rc.left + (_finalList[0]->rc.right - _finalList[0]->rc.left) / 2;
		float destY = _finalList[0]->rc.top + (_finalList[0]->rc.bottom - _finalList[0]->rc.top) / 2;
		angle = getAngle(centerX, centerY, destX, destY);
		centerX += cosf(angle) * speed;
		centerY -= sinf(angle) * speed;
	}
}

void monster::animation()
{
	aniCount++;
	if (aniCount % 5 == 0)
	{
		aniIndexX++;
		switch (monsterType)
		{
		case MTYPE_NONE:
			break;
		case MTYPE_SLIME:
			if (aniIndexX > 7)
			{
				aniIndexX = 0;
				isMove = false;
			}
			break;
		case MTYPE_BUG:
			if (aniIndexX > 3)
			{
				aniIndexX = 0;
				isMove = false;
			}
			break;
		case MTYPE_ROCKCRAB:
			if (aniIndexX > 3)
			{
				aniIndexX = 0;
				isMove = false;
			}
			break;
		case MTYPE_SERPENT:
			if (aniIndexX > 8)
			{
				aniIndexX = 0;
				isMove = false;
			}
			break;
		}

	}
}

void monster::checkAttack()
{
	if (!_finalList.size() && _isFind)
	{
		attackDestX = PLAYER->getCenterX();
		attackDestY = PLAYER->getCenterY() + 8.0f;
		lockedAngle = getAngle(centerX, centerY, attackDestX, attackDestY);
		isMove = false;
		isLocked = true;
	}
}

void monster::attack()
{
	if (isLocked)
	{
		attackCount++;
		if (attackCount > 60)
		{
			centerX += cosf(lockedAngle) * 3.0f;
			centerY -= sinf(lockedAngle) * 3.0f;
		}
		if (attackCount > 80)
		{
			isLocked = false;
			attackCount = 0;
		}
	}
}

void monster::checkDir()
{
	if (monsterType == MTYPE_BUG)
	{
		if (angle >= M_PI / 4 && angle < 3 * (M_PI / 4))
		{
			dir = UP;
		}
		else if (angle >= 3 * (M_PI / 4) && angle < 5 * (M_PI / 4))
		{
			dir = LEFT;
		}
		else if (angle >= 5 * (M_PI / 4) && angle < 7 * (M_PI / 4))
		{
			dir = DOWN;
		}
		else if (angle >= 7 * (M_PI / 4) || angle < M_PI / 4)
		{
			dir = RIGHT;
		}
		switch (dir)
		{
		case RIGHT:
			aniIndexY = 1;
			break;
		case LEFT:
			aniIndexY = 3;
			break;
		case UP:
			aniIndexY = 2;
			break;
		case DOWN:
			aniIndexY = 0;
			break;
		}
	}
}

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
	//HP 0 ���Ϸ� �ȶ�������
	if (currentHp <= 0)
	{
		currentHp = 0;

		isDead = true;
		isMove = false;

	}

	//������ ������ ���� ������ ���������� ������
	if (getdamage)
	{
		DamageDelay++;

		if (DamageDelay % 50 == 0)
		{
			getdamage = false;
		}
	}

	currentTileX = centerX / 16;
	currentTileY = centerY / 16;

	checkDir();

	this->rc = RectMakeCenter(centerX, centerY, 10, 10);

	_startNode = _totalNode[currentTileX][currentTileY];
	_endNode = _totalNode[PLAYER->getCurrentX()][PLAYER->getCurrentY()];

	//�Ÿ��� 7Ÿ�� ���ϰ� �Ǹ� ��ã��
	distance = sqrt(pow(PLAYER->getCenterX() - centerX, 2) + pow(PLAYER->getCenterY() - centerY, 2));
	if (distance < 158.0f && !isMove && !isLocked)
	{
		this->pathFinding();
	}
	if (isMove && !isLocked)
	{
		this->move();
		this->animation();
	}
	
	if (isLocked)
	{
		attack();
		this->animation();
	}
	else
	{
		checkAttack();
	}
}

void monster::render()
{
	//��ã������ �����ֱ�
	if (_isFind)
	{
		for (int i = 0; i < _finalList.size(); i++)
		{
			setNodeColor(_finalList[i], RGB(255, 255, 0));
		}
	}

	//FrameRect(CAMERAMANAGER->getMemDC(), _startNode->rc, RGB(0, 255, 0));
	//FrameRect(CAMERAMANAGER->getMemDC(), _endNode->rc, RGB(255, 0, 0));
	for (int i = 0; i < _finalList.size(); i++)
	{
		FrameRect(CAMERAMANAGER->getMemDC(), _finalList[i]->rc, RGB(255, 0, 255));
	}
	
	hpBarRender();

	switch (monsterType)
	{
	case MTYPE_NONE:
		break;
	case MTYPE_SLIME:
		IMAGEMANAGER->findImage("������")->frameRender(CAMERAMANAGER->getMemDC(), centerX - 8, centerY - 8, aniIndexX, aniIndexY);
		break;
	case MTYPE_BUG:
		IMAGEMANAGER->findImage("����")->frameRender(CAMERAMANAGER->getMemDC(), centerX - 8, centerY - 8, aniIndexX, aniIndexY);
		break;
	case MTYPE_ROCKCRAB:
		IMAGEMANAGER->findImage("������")->frameRender(CAMERAMANAGER->getMemDC(), centerX - 8, centerY - 8, aniIndexX, aniIndexY);
		break;
	case MTYPE_SERPENT:
		IMAGEMANAGER->findImage("������")->frameRender(CAMERAMANAGER->getMemDC(), centerX - 8, centerY - 8, aniIndexX, aniIndexY);
		break;
	default:
		break;
	}

	//cout << _finalList.size() << "   " << _closeList.size() << "    " << _openList.size() << endl;
	//cout << _startNode->rc.left << "    " << _endNode->rc.left << endl;
}

void monster::astarInit()
{
	//��� �ʱ�ȭ
	_startNode = NULL;
	_endNode = NULL;
	_curNode = NULL;

	//��ü��� �ʱ�ȭ
	for (int y = 0; y < MINEMAX; y++)
	{
		for (int x = 0; x < MINEMAX; x++)
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

void monster::startSearchPlayer(int playerCurrentX, int playerCurrentY)
{
	if (_startNode && _endNode) return;

	_totalNode[currentTileY][currentTileX]->nodeState = NODE_START;
	_startNode = _totalNode[currentTileY][currentTileX];
	cout << "setStartNode" << endl;

	_totalNode[playerCurrentY][playerCurrentX]->nodeState = NODE_END;
	_endNode = _totalNode[playerCurrentY][playerCurrentX];
	cout << "setEndNode" << endl;
}

void monster::searchPlayer(int playerCurrentX, int playerCurrentY)
{
	_openList.clear();
	_closeList.clear();
	_finalList.clear();

	_totalNode[currentTileY][currentTileX]->nodeState = NODE_START;
	_startNode = _totalNode[currentTileY][currentTileX];

	_totalNode[playerCurrentY][playerCurrentX]->nodeState = NODE_END;
	_endNode = _totalNode[playerCurrentY][playerCurrentX];
}

void monster::setWallNode(int i, int j, OBJECT obj)
{
	if (obj != OBJ_NONE)
	{
		if (_totalNode[i][j]->nodeState == NODE_START) return;
		if (_totalNode[i][j]->nodeState == NODE_END) return;
		_totalNode[i][j]->nodeState = NODE_WALL;
	}
	else
	{
		if (_totalNode[i][j]->nodeState == NODE_START) return;
		if (_totalNode[i][j]->nodeState == NODE_END) return;
		_totalNode[i][j]->nodeState = NODE_EMPTY;
	}
}

void monster::hpBarRender()
{	
	int b = 255 - (currentHp / hp) * 255;
	hpBar = RectMake(centerX - 7, centerY - 10, (currentHp / hp) * 14, 3);
	IMAGEMANAGER->findImage("����hp��")->render(CAMERAMANAGER->getMemDC(), centerX-8,centerY-10);
	Rectangle(CAMERAMANAGER->getMemDC(), hpBar);
	HBRUSH brush = CreateSolidBrush(RGB(b, 220, 7));
	FillRect(CAMERAMANAGER->getMemDC(), &hpBar, brush);
	DeleteObject(brush);
}

void monster::pathFinding()
{
	_openList.clear();
	_closeList.clear();
	_finalList.clear();

	//�����尡 ���� ��� ��ã�� ����
	if (!_endNode) return;
	cout << "startFind" << endl;
	//��ã�⸦ �غ���
	//�˻��� �Ϸ��� ������ ���¸���Ʈ�� ��´�
	//F�� H�� ���� ���� ���� ã�Ƽ� �׳��� ������� �����Ѵ�
	//���¸���Ʈ���� ������� �����ϰ�
	//������� Ŭ�����Ʈ�� ��Ƶд�
	//���� �� ã�Ҵٸ� Ŭ�����Ʈ ���������� ���̳� ����Ʈ�� �ű��

	//1. ���۳�尡 �־�� ����� �����ϴ�
	//���۳�带 ���¸���Ʈ�� �߰��� ����� �Ѵ�
	_openList.push_back(_startNode);

	//2. ���¸���Ʈ�ȿ� ��� �ִ� ���͸� �˻��ؼ�
	//�����忡 �����Ҷ����� ���� ����
	while (_openList.size() > 0)
	{
		_curNode = _openList[0];

		//���¸���Ʈ�� F�� ���� �۰ų� F�� ���ٸ�
		//H�� ���� �� ������� �ϰ�
		//�����带 ���¸���Ʈ���� Ŭ���� ����Ʈ�� �ű��
		//�񱳸� �Ϸ��� �ϸ� �ּ� ���۳�忡�� �ֺ��� Ž���� ����
		//��ã�Ⱑ ���۵ȴ�

		for (int i = 1; i < _openList.size(); i++)
		{
			if (_openList[i]->F <= _curNode->F && _openList[i]->H < _curNode->H)
			{
				_curNode = _openList[i];
			}
		}

		//Ŭ���� ����Ʈ�� �־�д�
		for (int i = 0; i < _openList.size(); i++)
		{
			if (_curNode == _openList[i])
			{
				this->delOpenList(i);
				_closeList.push_back(_curNode);
			}
		}

		//�����尡 ������ ���� ����? (��ã�Ҵ�)
		if (_curNode == _endNode)
		{
			node* endNode = _endNode;
			vector<node*> tempNode;
			//������ ���κ��� ���۳����� �θ��带 ���Ϳ� ��´�
			while (endNode != _startNode)
			{
				tempNode.push_back(endNode);
				endNode = endNode->parentNode;
			}

			for (int i = tempNode.size() - 1; i > 0; i--)
			{
				_finalList.push_back(tempNode[i]);
			}

			_isFind = true;
			isMove = true;
			//�����ϰ� ���� ���´�
			return;
		}

		//�����¿� (������ ������� - ��¥�� �ֺ� 4���� ��带 ��� ���¸���Ʈ�� ��Ƽ� �˻��� ������)
		addOpenList(_curNode->idx, _curNode->idy - 1);	//��
		addOpenList(_curNode->idx, _curNode->idy + 1);	//��
		addOpenList(_curNode->idx - 1, _curNode->idy);	//��
		addOpenList(_curNode->idx + 1, _curNode->idy);	//��

		//���Ŀ� �밢 4���⵵ �߰��ϸ� �밢�� �̵� ó���� ������
		//���, �»�, ����, ����
		//����ó���� �����ָ� �ȴ�
		//�����̷� ���� �ȵǵ��� ó���Ѵ�
	}
}

void monster::addOpenList(int idx, int idy)
{
	//����ó�� �ε��� �����ȿ��� �߰��� �� �־�� �Ѵ�
	if (idx < 0 || idx >= MINEMAX || idy < 0 || idy >= MINEMAX) return;

	//���� ���¸���Ʈ�� ���� �� ����
	if (_totalNode[idx][idy]->nodeState == NODE_WALL) return;

	//Ŭ�����Ʈ(�����±�)�� �ִٸ� ���¸���Ʈ�� ������ �ȵȴ�
	for (int i = 0; i < _closeList.size(); i++)
	{
		if (_totalNode[idx][idy] == _closeList[i]) return;
	}

	//������� ������ ������ ������ ���� ���¸���Ʈ�� �߰��� ����
	//�������� 4���� ��带 �̿������ �ϰ� ����10, �밢�� 14����� �߰��Ѵ�
	node* neighborNode = _totalNode[idx][idy];
	int moveCost = _curNode->G + ((_curNode->idx - idx == 0 || _curNode->idy - idy == 0) ? 10 : 14);

	//���¸���Ʈ�ȿ� �̿���尡 ������ �ȵȴ�
	for (int i = 0; i < _openList.size(); i++)
	{
		if (_openList[i] == neighborNode) return;
	}

	//���������� ���¸���Ʈ���� ���°��
	//G, H, ParentNode ������ ���¸���Ʈ�� �߰�
	//F = G + H
	//G = ���ۿ��� ����
	//H = ���翡�� ����
	neighborNode->G = moveCost;
	neighborNode->H = (abs(neighborNode->idx - _endNode->idx) + abs(neighborNode->idy - _endNode->idy)) * 10;
	neighborNode->F = neighborNode->G + neighborNode->H;
	neighborNode->parentNode = _curNode;
	_openList.push_back(neighborNode);
}

void monster::delOpenList(int index)
{
	_openList.erase(_openList.begin() + index);
}

void monster::setNodeColor(node * node, COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	FillRect(getMemDC(), &node->rc, brush);
	DeleteObject(brush);
	FrameRect(getMemDC(), node->rc, RGB(0, 0, 0));
}
