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

	RECT rc;
	MONTYPE monsterType;
	MONSTATE state;
	DIRECTION dir;
	int currentTileX, currentTileY;
	int moveCount;
	
	RECT hpBar;

	float hp, dmg;
	float currentHp;

	float centerX, centerY;
	float speed;
	float angle;

	bool isMove;
	bool isAttack;
	
	bool getdamage;
	
	int DamageDelay;

	int aniCount;
	int aniIndexX, aniIndexY;

	float distance;

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
	monster() {};
	monster(MONTYPE _monsterType, int _centerX, int _centerY, int _hp, int _dmg, float _speed);
	~monster() {};

	void move();
	void animation();

	void checkDir();

	void setCenterX(float cX) { centerX = cX; }
	void setCenterY(float cY) { centerY = cY; }
	RECT getRc() { return rc; }
	void setRc(float x, float y) { rc = RectMakeCenter(x, y, 16, 16); }
	bool getIsFind() { return _isFind; }
	void setSpeed(float spd) { speed = spd; }
	float getSpeed() { return speed; }

	float getHp() { return currentHp; }
	void setHp(float _hp) { currentHp = _hp; }
	void setDamage(bool _bool) { getdamage = _bool; }
	bool getDamage() { return getdamage; }
	void hpBarRender();

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

