#pragma once
#include "gameNode.h"

#define MINEMAX 50

//������
enum NODESTATE
{
	NODE_START,
	NODE_END,
	NODE_WALL,
	NODE_EMPTY
};

//��� Ŭ����
class node
{
public:
	RECT rc;				//��Ʈ
	int idx, idy;			//�ε���
	int F, G, H;			//F = G + H, G => ���� to ����, H = ���� to ����
	node* parentNode;		//�θ� ����ų ���(���� ���)
	NODESTATE nodeState;	//������ (����, ����, ��, ����)

	//��� ������
	node() {}
	//��� ������ (������ �����ε�)
	node(int _idx, int _idy)
	{
		idx = _idx;
		idy = _idy;
		F = G = H = 0;
		nodeState = NODE_EMPTY;
		parentNode = NULL;
	}
};

class monster : gameNode
{
private:
	RECT rc;
	MONTYPE monsterType;
	MONSTATE state;
	int currentTileX, currentTileY;
	int moveCount;
	int hp, dmg;
	float centerX, centerY;
	float speed;
	float angle;

	int aniCount;
	int aniIndexX, aniIndexY;


	//���̽�Ÿ
	node* _totalNode[50][50];		//��ü��� 25��(������ ����)
	node* _startNode;					//���۳��
	node* _endNode;						//������
	node* _curNode;						//������

	vector<node*> _openList;			//���¸���Ʈ (ž���� ������ ��Ƶ� ����)
	vector<node*> _closeList;			//���� ã�� ������ ��Ƶ� ����
	vector<node*> _finalList;			//Ŭ�����Ʈ�� ����ִ� ������ ���������Ѽ� ��Ƶ� ����

	int _count;							//���۳��, �����带 �ѹ����� �����ϱ� ���� ����
	bool _isFind;						//�� ã�ҳ�?

public:
	HRESULT init();
	void release();

	void update();
	void render();
	void astarInit();
	void startSearchPlayer(int playerCurrentX, int playerCurrentY);
	void searchPlayer(int playerCurrentX, int playerCurrentY);
	void setWallNode(int i, int j, OBJECT obj);

	//������
	monster(MONTYPE _monsterType, int _centerX, int _centerY, int _hp, int _dmg, float _speed);
	~monster() {};

	/*�߿��Լ�*/
		//��ã�� �Լ�
	void pathFinding();
	//���¸���Ʈ �߰�
	void addOpenList(int idx, int idy);
	//���¸���Ʈ ����
	void delOpenList(int index);

	//���Ǹ� ���� �Լ�
	void setNodeColor(node* node, COLORREF color);
};

