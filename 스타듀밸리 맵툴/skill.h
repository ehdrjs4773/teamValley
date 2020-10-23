#pragma once
class skill
{
private:
	int frameX, frameY;
	
	float pointX;
	float pointY;
	bool _isActive;
	bool _isClick;
	
	bool _isShield;

	int _num;
	int _save_i;

	SKILL skill_state;
	RECT _skillRc;
	RECT _skillSlot[12];

	vector<tagSkill> _vSkill;
	vector<tagSkill> _vCurrentSkill;
	int _count;

public:
	void init();
	void render(HDC hdc);

	void update();

	vector<tagSkill> getvSkill() { return _vSkill; }

	void skillSelect();
	void skillActive();
	vector<tagSkill>& getvCurrentSkill() { return _vCurrentSkill; }

	float getPointX() { return pointX; }
	float getPointY() { return pointY; }
	RECT getRect() { return _skillRc; }
	void setSkill(int num) { _num = num; }
	bool isActive() { return _isActive; }
	bool isClick() { return _isClick; }
	void addSkill(const char* _key,
		const char* _skill_info,
		SKILL _skillkind,
		int _maxindex,
		bool _isActive,
		int _indexX = 0,
		int _indexY = 0);

};

