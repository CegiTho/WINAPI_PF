#pragma once

class Goal : public T_Object
{
private:
	bool isGoal;
	bool isMove;
	bool isGoback;
	bool isLoop;

	double times;

	Character* character;

	//Render할때 사용
	vector<Line*> lines;
	Vector2 startPos;
	Vector2 endPos;

	HPEN goalEdge;
	Name name;

public:
	Goal(Character* character,Vector2 pos);
	Goal(Character* character,Vector2 pos,Vector2 endPos,double times,bool isMove,bool isLoop);
	~Goal();

	void CreateElement(Character* character, Vector2 pos);

	void Update();
	void Render(HDC hdc);

	void Collision();
	
	bool GoalCheck() { return isGoal; }
	Name GetName() { return name; }

	void SetIsMove(bool value) { isMove =	 value; }
	void Move();

};


