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
	//HP 0 이하로 안떨어지게
	if (currentHp <= 0)
	{
		currentHp = 0;

		isDead = true;
		isMove = false;

	}

	//데미지 받으면 다음 데미지 받을떄까지 딜레이
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

	//거리가 7타일 이하가 되면 길찾기
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
	//길찾았을때 보여주기
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
		IMAGEMANAGER->findImage("슬라임")->frameRender(CAMERAMANAGER->getMemDC(), centerX - 8, centerY - 8, aniIndexX, aniIndexY);
		break;
	case MTYPE_BUG:
		IMAGEMANAGER->findImage("벌레")->frameRender(CAMERAMANAGER->getMemDC(), centerX - 8, centerY - 8, aniIndexX, aniIndexY);
		break;
	case MTYPE_ROCKCRAB:
		IMAGEMANAGER->findImage("바위게")->frameRender(CAMERAMANAGER->getMemDC(), centerX - 8, centerY - 8, aniIndexX, aniIndexY);
		break;
	case MTYPE_SERPENT:
		IMAGEMANAGER->findImage("도마뱀")->frameRender(CAMERAMANAGER->getMemDC(), centerX - 8, centerY - 8, aniIndexX, aniIndexY);
		break;
	default:
		break;
	}

	//cout << _finalList.size() << "   " << _closeList.size() << "    " << _openList.size() << endl;
	//cout << _startNode->rc.left << "    " << _endNode->rc.left << endl;
}

void monster::astarInit()
{
	//노드 초기화
	_startNode = NULL;
	_endNode = NULL;
	_curNode = NULL;

	//전체노드 초기화
	for (int y = 0; y < MINEMAX; y++)
	{
		for (int x = 0; x < MINEMAX; x++)
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
	IMAGEMANAGER->findImage("몬스터hp바")->render(CAMERAMANAGER->getMemDC(), centerX-8,centerY-10);
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

	//종료노드가 없는 경우 길찾기 못함
	if (!_endNode) return;
	cout << "startFind" << endl;
	//길찾기를 해보자
	//검색을 하려면 무조건 오픈리스트에 담는다
	//F와 H값 가장 작은 놈을 찾아서 그놈을 현재노드로 변경한다
	//오픈리스트에서 현재노드는 삭제하고
	//현재노드는 클로즈리스트에 담아둔다
	//길을 다 찾았다면 클로즈리스트 리버스값을 파이널 리스트로 옮긴다

	//1. 시작노드가 있어야 출발이 가능하니
	//시작노드를 오픈리스트에 추가를 해줘야 한다
	_openList.push_back(_startNode);

	//2. 오픈리스트안에 담겨 있는 벡터를 검사해서
	//종료노드에 도착할때까지 무한 루프
	while (_openList.size() > 0)
	{
		_curNode = _openList[0];

		//오픈리스트중 F가 가장 작거나 F가 같다면
		//H가 작은 걸 현재노드로 하고
		//현재노드를 오픈리스트에서 클로즈 리스트로 옮기기
		//비교를 하려고 하면 최소 시작노드에서 주변을 탐색한 이후
		//길찾기가 시작된다

		for (int i = 1; i < _openList.size(); i++)
		{
			if (_openList[i]->F <= _curNode->F && _openList[i]->H < _curNode->H)
			{
				_curNode = _openList[i];
			}
		}

		//클로즈 리스트에 넣어둔다
		for (int i = 0; i < _openList.size(); i++)
		{
			if (_curNode == _openList[i])
			{
				this->delOpenList(i);
				_closeList.push_back(_curNode);
			}
		}

		//현재노드가 마지막 노드와 같냐? (길찾았다)
		if (_curNode == _endNode)
		{
			node* endNode = _endNode;
			vector<node*> tempNode;
			//마지막 노드로부터 시작노드까지 부모노드를 벡터에 담는다
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
			//종료하고 빠져 나온다
			return;
		}

		//상하좌우 (순서는 상관없음 - 어짜피 주변 4개의 노드를 모두 오픈리스트에 담아서 검사할 예정임)
		addOpenList(_curNode->idx, _curNode->idy - 1);	//상
		addOpenList(_curNode->idx, _curNode->idy + 1);	//하
		addOpenList(_curNode->idx - 1, _curNode->idy);	//좌
		addOpenList(_curNode->idx + 1, _curNode->idy);	//우

		//추후에 대각 4방향도 추가하면 대각선 이동 처리도 가능함
		//우상, 좌상, 우하, 좌하
		//예외처리만 잘해주면 된다
		//벽사이로 막가 안되도록 처리한다
	}
}

void monster::addOpenList(int idx, int idy)
{
	//예외처리 인덱스 범위안에서 추가할 수 있어야 한다
	if (idx < 0 || idx >= MINEMAX || idy < 0 || idy >= MINEMAX) return;

	//벽은 오픈리스트에 담을 수 없다
	if (_totalNode[idx][idy]->nodeState == NODE_WALL) return;

	//클로즈리스트(지나온길)에 있다면 오픈리스트에 담으면 안된다
	for (int i = 0; i < _closeList.size(); i++)
	{
		if (_totalNode[idx][idy] == _closeList[i]) return;
	}

	//여기까지 왔으면 문제가 없으니 이제 오픈리스트에 추가를 하자
	//현재노드의 4방향 노드를 이웃노드라고 하고 직선10, 대각은 14비용을 추가한다
	node* neighborNode = _totalNode[idx][idy];
	int moveCost = _curNode->G + ((_curNode->idx - idx == 0 || _curNode->idy - idy == 0) ? 10 : 14);

	//오픈리스트안에 이웃노드가 있으면 안된다
	for (int i = 0; i < _openList.size(); i++)
	{
		if (_openList[i] == neighborNode) return;
	}

	//마지막으로 오픈리스트에도 없는경우
	//G, H, ParentNode 설정후 오픈리스트에 추가
	//F = G + H
	//G = 시작에서 현재
	//H = 현재에서 종료
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
