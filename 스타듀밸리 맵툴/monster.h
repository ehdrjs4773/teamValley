#pragma once
#include "gameNode.h"

#define MINEMAX 50

//노드상태
enum NODESTATE
{
	NODE_START,
	NODE_END,
	NODE_WALL,
	NODE_EMPTY
};

//노드 클래스
class node
{
public:
	RECT rc;				//렉트
	int idx, idy;			//인덱스
	int F, G, H;			//F = G + H, G => 시작 to 현재, H = 현재 to 종료
	node* parentNode;		//부모를 가리킬 노드(이전 노드)
	NODESTATE nodeState;	//노드상태 (시작, 종료, 벽, 빈노드)

	//노드 생성자
	node() {}
	//노드 생성자 (생성자 오버로딩)
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
	//에이스타
	node* _totalNode[50][50];		//전체노드 25개(보드판 역할)
	node* _startNode;					//시작노드
	node* _endNode;						//종료노드
	node* _curNode;						//현재노드

	vector<node*> _openList;			//오픈리스트 (탑색할 노드들을 담아둘 벡터)
	vector<node*> _closeList;			//길을 찾은 노드들을 담아둘 벡터
	vector<node*> _finalList;			//클로즈리스트에 담겨있는 노드들을 리버스시켜서 담아둘 벡터

	int _count;							//시작노드, 종료노드를 한번씩만 선택하기 위한 변수
	bool _isFind;						//길 찾았냐?

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
	int currentX, currentY;
	float speed;
	float angle;

	bool isMove;
	bool isLocked;
	
	bool getdamage;	
	bool isDead;
	int DamageDelay;

	int aniCount;
	int aniIndexX, aniIndexY;

	float distance;

	int attackCount = 0;
	float attackDestX, attackDestY;
	float lockedAngle;
	bool isShowRect = false;

public:
	HRESULT init();
	void release();

	void update();
	void render();
	void astarInit();
	void startSearchPlayer(int playerCurrentX, int playerCurrentY);
	void searchPlayer(int playerCurrentX, int playerCurrentY);
	void setWallNode(int i, int j, OBJECT obj);

	//생성자
	monster() {};
	monster(MONTYPE _monsterType, int _centerX, int _centerY, int _hp, int _dmg, float _speed);
	~monster() {};

	void move();
	void animation();
	void checkAttack();
	void attack();

	void checkDir();

	float getCenterX() { return centerX; }
	float getCenterY() { return centerY; }
	int getCurrentX() { return currentX; }
	int getCurrentY() { return currentY; }
	void setCenterX(float cX) { centerX = cX; }
	void setCenterY(float cY) { centerY = cY; }
	RECT getRc() { return rc; }
	void setRc(float x, float y) { rc = RectMakeCenter(x, y, 16, 16); }
	bool getIsFind() { return _isFind; }
	void setSpeed(float spd) { speed = spd; }
	float getSpeed() { return speed; }
	int getDmg() { return dmg; }

	float getHp() { return currentHp; }
	void setHp(float _hp) { currentHp = _hp; }
	void setDamage(bool _bool) { getdamage = _bool; }
	bool getDamage() { return getdamage; }
	bool getisDead() { return isDead; }
	void hpBarRender();

	bool getIsLocked() { return isLocked; }
	void setIsLocked(bool locked) { isLocked = locked; }


	/*중요함수*/
		//길찾기 함수
	void pathFinding();
	//오픈리스트 추가
	void addOpenList(int idx, int idy);
	//오픈리스트 삭제
	void delOpenList(int index);

	//편의를 위한 함수
	void setNodeColor(node* node, COLORREF color);
};

